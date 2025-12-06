#include "network.h"
#include <iostream>

NetworkClient::NetworkClient(const std::string& address, int port)
    : serverAddress(address), port(port), connected(false) {}

NetworkClient::~NetworkClient() {
    if (connected) {
        disconnect();
    }
}

bool NetworkClient::connect() {
    std::cout << "Connecting to " << serverAddress << ":" << port << std::endl;
    connected = true;
    return true;
}

void NetworkClient::disconnect() {
    if (connected) {
        std::cout << "Disconnecting from " << serverAddress << std::endl;
        connected = false;
    }
}

bool NetworkClient::isConnected() const {
    return connected;
}

std::string NetworkClient::sendRequest(const std::string& request) {
    if (!connected) {
        return "Error: Not connected";
    }
    return "Response to: " + request;
}

std::vector<std::string> NetworkClient::fetchData() {
    if (!connected) {
        return {"Error: Not connected"};
    }
    return {"data1", "data2", "data3"};
}

bool NetworkClient::uploadData(const std::string& data) {
    if (!connected) {
        return false;
    }
    std::cout << "Uploading data: " << data << std::endl;
    return true;
}
