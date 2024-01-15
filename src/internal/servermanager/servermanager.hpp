#pragma once

#include <string>
#include <iostream>

#include <thread>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include "../signalmanager/signalmanager.hpp"
#include "../serverunit/serverunit.hpp"

// Represents server manager used to orchistrate spawned servers.
class ServerManager {
private:
    // Represents opened input client queue used for client-servermanager communication.
    int clientInputQueueFd;
    
    // Represents opened output client queue used for client-servermanager communication.
    int clientOutputQueueFd;

    // Represents opened servermanager input queue used for client-servermanager communication.
    int serverManagerInputQueueFd;

    std::vector<std::vector<int>> getDataFromBuff(int src[MAX_DATA_NUM][MAX_DATA_NUM]);
public:
    // Represents generated client input queue name used for client-servermanager communication.
    static std::string clientInputQueueName;

    // Represents generated client output queue name used for client-servermanager communication.
    static std::string clientOutputQueueName;

    // Represents generated servermanager input queue name used for client-servermanager communication.
    static std::string serverManagerInputQueueName;

    ServerManager();

    // 
    std::string getClientInputQueueName();

    //
    std::string getClientOutputQueueName();

    // 
    void start();

    // 
    static void handleExit(int s);
};

namespace ServerManagerHelper {
    void handleExit(int s);
}
