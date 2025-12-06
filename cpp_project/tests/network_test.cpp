#include <gtest/gtest.h>
#include "cpp_project/network/network.h"

class NetworkTest : public ::testing::Test {
protected:
    NetworkClient* client;
    
    void SetUp() override {
        client = new NetworkClient("localhost", 8080);
    }
    
    void TearDown() override {
        delete client;
    }
};

TEST_F(NetworkTest, TestConnect) {
    EXPECT_FALSE(client->isConnected());
    EXPECT_TRUE(client->connect());
    EXPECT_TRUE(client->isConnected());
}

TEST_F(NetworkTest, TestDisconnect) {
    client->connect();
    EXPECT_TRUE(client->isConnected());
    client->disconnect();
    EXPECT_FALSE(client->isConnected());
}

TEST_F(NetworkTest, TestSendRequestWhenConnected) {
    client->connect();
    std::string response = client->sendRequest("test");
    EXPECT_NE(response.find("Response"), std::string::npos);
}

TEST_F(NetworkTest, TestSendRequestWhenNotConnected) {
    std::string response = client->sendRequest("test");
    EXPECT_NE(response.find("Error"), std::string::npos);
}
