#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

class NetworkClient {
private:
    std::string serverAddress;
    int port;
    bool connected;

public:
    NetworkClient(const std::string& address, int port);
    ~NetworkClient();
    
    bool connect();
    void disconnect();
    bool isConnected() const;
    
    // Simulated network operations
    std::string sendRequest(const std::string& request);
    std::vector<std::string> fetchData();
    bool uploadData(const std::string& data);
};

#endif // NETWORK_H
