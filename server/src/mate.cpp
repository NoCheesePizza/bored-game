#include "mate.h"
#include "utility.h"

Mate Mate::fromJson(const Json::Value &json) {
    Mate mate;
    mate.name = VALIDATE_KEY(json, "name", String, "New Player");
    mate.id = VALIDATE_KEY(json, "id", String, uti::generateId());
    mate.isWinner = VALIDATE_KEY(json, "isWinner", Bool, false);
    mate.score = VALIDATE_KEY(json, "score", Int, 0);
    return mate;
}