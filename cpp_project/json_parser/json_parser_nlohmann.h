#ifndef JSON_PARSER_NLOHMANN_H
#define JSON_PARSER_NLOHMANN_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class JsonParserNlohmann {
public:
    JsonParserNlohmann();
    ~JsonParserNlohmann();
    
    // Create JSON objects using nlohmann/json
    std::string createPerson(const std::string& name, int age, const std::string& city);
    std::string createArray(const std::vector<int>& numbers);
    
    // Parse JSON
    nlohmann::json parse(const std::string& jsonString);
    
    // Get value from JSON
    std::string getValue(const std::string& jsonString, const std::string& key);
};

#endif // JSON_PARSER_NLOHMANN_H
