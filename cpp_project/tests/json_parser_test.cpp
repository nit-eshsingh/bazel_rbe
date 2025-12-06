#include <gtest/gtest.h>
#include "cpp_project/json_parser/json_parser.h"

class JsonParserTest : public ::testing::Test {
protected:
    JsonParser parser;
};

TEST_F(JsonParserTest, TestCreatePersonJson) {
    std::string json = parser.createPersonJson("Alice", 30, "NYC");
    EXPECT_NE(json.find("Alice"), std::string::npos);
    EXPECT_NE(json.find("30"), std::string::npos);
    EXPECT_NE(json.find("NYC"), std::string::npos);
}

TEST_F(JsonParserTest, TestCreateArrayJson) {
    std::vector<int> numbers = {1, 2, 3};
    std::string json = parser.createArrayJson(numbers);
    EXPECT_NE(json.find("1"), std::string::npos);
    EXPECT_NE(json.find("2"), std::string::npos);
    EXPECT_NE(json.find("3"), std::string::npos);
}

TEST_F(JsonParserTest, TestParseSimpleJson) {
    std::string json = "{\"key\": \"value\"}";
    auto result = parser.parseSimpleJson(json);
    EXPECT_EQ(result["status"], "parsed");
    EXPECT_GT(std::stoi(result["length"]), 0);
}
