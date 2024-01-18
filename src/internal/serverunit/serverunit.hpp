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
 
/**
 * Represents single server unit.
*/
class ServerUnit {
private:
    /**
     * Represents selected data chunk.
    */
    std::vector<int> chunk;

    /**
     * Represents server unit current thread.
    */
    std::thread thread;
public:
    /**
     * Represents server manager input queue opened in write only mode.
    */
    static int serverManagerInputQueueFd;

    ServerUnit(std::string serverManagerInputQueueName, std::vector<int>& chunk);
    
    /**
     * Starts server unit internal calculation.
    */
    void startRaw();

    /**
     * Initializes server unit.
    */
    void start();
};