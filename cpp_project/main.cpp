#include <iostream>
#include <string>
#include <vector>
#include "cpp_project/calculator.h"
#include "cpp_project/logger/logger.h"
#include "cpp_project/json_parser/json_parser.h"
#include "cpp_project/json_parser/json_parser_nlohmann.h"
#include "cpp_project/network/network.h"

int main() {
    std::cout << "=====================================" << std::endl;
    std::cout << "C++ Project - Integrated Demo" << std::endl;
    std::cout << "=====================================" << std::endl << std::endl;
    
    // 1. Calculator
    Calculator calc;
    double x = 15.5, y = 4.5;
    std::cout << "1. Calculator:" << std::endl;
    std::cout << "   " << x << " + " << y << " = " << calc.add(x, y) << std::endl;
    std::cout << "   " << x << " * " << y << " = " << calc.multiply(x, y) << std::endl;
    
    // 2. Logger
    std::cout << "\n2. Logger:" << std::endl;
    Logger logger("app.log", LogLevel::INFO);
    logger.info("Application started");
    logger.warning("This is a warning message");
    logger.error("This is an error message");
    
    // 3. JSON Parser (simple)
    std::cout << "\n3. JSON Parser (Simple):" << std::endl;
    JsonParser jsonParser;
    std::string personJson = jsonParser.createPersonJson("Alice", 30, "New York");
    std::cout << "   Person JSON:\n" << personJson << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::string arrayJson = jsonParser.createArrayJson(numbers);
    std::cout << "   Array JSON: " << arrayJson << std::endl;
    
    // 4. JSON Parser with nlohmann (third-party)
    std::cout << "\n4. JSON Parser (nlohmann/json - Third-party):" << std::endl;
    JsonParserNlohmann nlohmannParser;
    std::string nlohmannPerson = nlohmannParser.createPerson("Bob", 25, "London");
    std::cout << "   Person JSON:\n" << nlohmannPerson << std::endl;
    
    std::string value = nlohmannParser.getValue(nlohmannPerson, "name");
    std::cout << "   Name field: " << value << std::endl;
    
    // 5. Network Client
    std::cout << "\n5. Network Client:" << std::endl;
    NetworkClient client("localhost", 8080);
    client.connect();
    std::cout << "   Connected: " << (client.isConnected() ? "Yes" : "No") << std::endl;
    std::string response = client.sendRequest("GET /api/data");
    std::cout << "   Response: " << response << std::endl;
    client.disconnect();
    
    logger.info("Application completed");
    
    std::cout << "\n=====================================" << std::endl;
    return 0;
}
