#include "json_parser.h"
#include <sstream>

JsonParser::JsonParser() {}

JsonParser::~JsonParser() {}

std::string JsonParser::createPersonJson(const std::string& name, int age, const std::string& city) {
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"name\": \"" << name << "\",\n";
    ss << "  \"age\": " << age << ",\n";
    ss << "  \"city\": \"" << city << "\"\n";
    ss << "}";
    return ss.str();
}

std::string JsonParser::createArrayJson(const std::vector<int>& numbers) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < numbers.size(); i++) {
        ss << numbers[i];
        if (i < numbers.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

std::map<std::string, std::string> JsonParser::parseSimpleJson(const std::string& json) {
    std::map<std::string, std::string> result;
    // Simple parsing simulation
    result["status"] = "parsed";
    result["length"] = std::to_string(json.length());
    return result;
}

std::string JsonParser::prettyPrint(const std::string& json) {
    // Simple pretty printing (adds newlines for demonstration)
    return "Pretty printed JSON:\n" + json;
}
