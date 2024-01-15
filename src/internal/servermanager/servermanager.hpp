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

    // Represents opened servermanager queue used for client-servermanager communication.
    int serverManagerQueueFd;

    // std::thread thread;

    // std::vector<std::vector>

    
public:
    // Represents generated client input queue name used for client-servermanager communication.
    static std::string clientInputQueueName;

    // Represents generated client output queue name used for client-servermanager communication.
    static std::string clientOutputQueueName;

    // Represents generated servermanager queue name used for client-servermanager communication.
    static std::string serverManagerQueueName;

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
