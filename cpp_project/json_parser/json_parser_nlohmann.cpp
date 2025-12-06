#include "json_parser_nlohmann.h"

using json = nlohmann::json;

JsonParserNlohmann::JsonParserNlohmann() {}

JsonParserNlohmann::~JsonParserNlohmann() {}

std::string JsonParserNlohmann::createPerson(const std::string& name, int age, const std::string& city) {
    json j;
    j["name"] = name;
    j["age"] = age;
    j["city"] = city;
    return j.dump(2); // Pretty print with 2 space indentation
}

std::string JsonParserNlohmann::createArray(const std::vector<int>& numbers) {
    json j = numbers;
    return j.dump();
}

nlohmann::json JsonParserNlohmann::parse(const std::string& jsonString) {
    return json::parse(jsonString);
}

std::string JsonParserNlohmann::getValue(const std::string& jsonString, const std::string& key) {
    try {
        json j = json::parse(jsonString);
        if (j.contains(key)) {
            return j[key].dump();
        }
        return "Key not found";
    } catch (const json::exception& e) {
        return std::string("Parse error: ") + e.what();
    }
}
