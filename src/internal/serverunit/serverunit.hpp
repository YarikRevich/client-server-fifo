#pragma once

#include <iostream>
#include <thread>

#include <thread>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include "../signalmanager/signalmanager.hpp"

// Represents 
class ServerUnit {
private:
    std::vector<int> chunk;

    std::thread thread;
public:
    // Represents generated server queue name used for client-servermanager communication.
    static std::string serverQueueName;

    ServerUnit(std::vector<int>& chunk);

    // //
    // std::string getServerQueueName();

    // void write(std::vector<int>& src);
    
    void startRaw();

    //
    void start();

    ~ServerUnit();
};

namespace ServerUnitHelper {
    // Handles graceful exit for the server.
    void handleExit(int s);
}