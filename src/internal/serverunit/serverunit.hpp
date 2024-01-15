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
 
// Represents single server unit.
class ServerUnit {
private:
    std::vector<int> chunk;

    std::thread thread;
public:
    static int serverManagerInputQueueFd;

    ServerUnit(std::string serverManagerInputQueueName, std::vector<int>& chunk);
    
    // Starts server unit internal calculation.
    void startRaw();

    // Initializes server unit.
    void start();
};