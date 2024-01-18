#pragma once

#include <string>
#include <iostream>
#include <math.h>

#include <thread>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include "../signalmanager/signalmanager.hpp"
#include "../serverunit/serverunit.hpp"

/**
 * Represents server manager used to orchistrate spawned servers.
*/
class ServerManager {
private:
    /**
     * Represents client input queue in write only mode.
    */
    int clientInputQueueFd;
    
    /**
     * Represents client output queue in write only mode.
    */
    int clientOutputQueueFd;

    /**
     * Represents servermanager input queue in write only mode.
    */
    int serverManagerInputQueueFd;

    /**
     * Converts given buffer to data structure.
     * 
     * @param src - given input buffer.
     * @return converter data structure.
    */
    std::vector<std::vector<int>> getDataFromBuff(int src[MAX_DATA_NUM][MAX_DATA_NUM]);
public:
    /**
     * Represents generated input client queue name used for client-servermanager communication.
    */
    static std::string clientInputQueueName;

    /**
     * Represents generated output client queue name used for client-servermanager communication.
    */
    static std::string clientOutputQueueName;

    /**
     * Represents generated servermanager input queue name used for client-servermanager communication.
    */
    static std::string serverManagerInputQueueName;

    ServerManager();

    /**
     * Returns client input queue name.
     * 
     * @return client input queue name.
    */
    std::string getClientInputQueueName();

    /**
     * Returns client output queue name.
     * 
     * @return client output queue name.
    */
    std::string getClientOutputQueueName();

    /**
     * Starts input listening process.
    */
    void start();

    /**
     * Handles exit signal.
     * 
     * @param s - signal identification.
    */
    static void handleExit(int s);
};

/**
 * Represents wrapper used for graceful exit procedure registration purposes.
*/
namespace ServerManagerHelper {
    /**
     * Handles exit signal.
     * 
     * @param s - signal identification.
    */
    void handleExit(int s);
}
