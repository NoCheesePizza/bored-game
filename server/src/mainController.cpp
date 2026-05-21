#include <drogon/drogon.h>

#include "room.h"
#include "utility.h"
#include "monitor.h"

class MainController : public drogon::HttpController<MainController> {
    void handleInvalidJson(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k400BadRequest);
        resp->setBody("Invalid JSON");
        callback(resp);
    }

    void handleJoinError(const std::shared_ptr<drogon::HttpResponse> &resp, JoinErr err) {
        switch (err) {
            case JoinErr::PLAYER_EXISTS:
                resp->setBody("Player already exists in the room");
                resp->setStatusCode(drogon::k409Conflict);
                break;
        }
    }

    void handleLeaveError(const std::shared_ptr<drogon::HttpResponse> &resp, LeaveErr err) {
        switch (err) {
            case LeaveErr::PLAYER_NOT_FOUND:
                resp->setBody("Player not found in the room");
                resp->setStatusCode(drogon::k409Conflict);
                break;
            case LeaveErr::ROOM_NOT_FOUND:
                resp->setBody("Room not found");
                resp->setStatusCode(drogon::k409Conflict);
                break;
        }
    }

public:

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(MainController::ping, "/ping", drogon::Get);
        ADD_METHOD_TO(MainController::join, "/join", drogon::Post);
        ADD_METHOD_TO(MainController::leave, "/leave", drogon::Post);
        ADD_METHOD_TO(MainController::leaveAndDestroy, "/leaveAndDestroy", drogon::Post);
    METHOD_LIST_END

    void ping(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setBody("pong");
        callback(resp);
    }

    void join(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        auto json = req->getJsonObject();

        if (!json) {
            handleInvalidJson(req, std::move(callback));
            return;
        }

        std::string roomId = VALIDATE_KEY(*json, "roomId", String, "Purgatory");
        Mate mate = Mate::fromJson(json->get("mate", Json::Value()));
        
        Monitor &monitor = Monitor::instance();
        handleJoinError(resp, monitor.addMate(roomId, mate));
        callback(resp);
    }

    void leave(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        auto json = req->getJsonObject();

        if (!json) {
            handleInvalidJson(req, std::move(callback));
            return;
        }

        std::string roomId = VALIDATE_KEY(*json, "roomId", String, "Purgatory");
        std::string mateId = VALIDATE_KEY(*json, "mateId", String, "");

        Monitor &monitor = Monitor::instance();
        handleLeaveError(resp, monitor.removeMate(roomId, mateId));
        callback(resp);
    }

    void leaveAndDestroy(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        auto json = req->getJsonObject();

        if (!json) {
            handleInvalidJson(req, std::move(callback));
            return;
        }

        std::string roomId = VALIDATE_KEY(*json, "roomId", String, "Purgatory");

        Monitor &monitor = Monitor::instance();
        handleLeaveError(resp, monitor.removeRoom(roomId));
        callback(resp);
    }
};
