#include <iostream>
#include <drogon/drogon.h>
#include <json/json.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    drogon::app().addListener("0.0.0.0", 8000).run();
    return 0;
}