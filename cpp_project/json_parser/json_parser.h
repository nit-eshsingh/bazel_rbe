#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <map>
#include <vector>

class JsonParser {
public:
    JsonParser();
    ~JsonParser();
    
    // Create JSON from data
    std::string createPersonJson(const std::string& name, int age, const std::string& city);
    std::string createArrayJson(const std::vector<int>& numbers);
    
    // Simulate parsing (without actual nlohmann/json for simplicity)
    std::map<std::string, std::string> parseSimpleJson(const std::string& json);
    
    // Format JSON string
    std::string prettyPrint(const std::string& json);
};

#endif // JSON_PARSER_H
