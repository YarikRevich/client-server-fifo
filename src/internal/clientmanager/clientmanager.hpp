#pragma once

#include <string>
#include <iostream>

#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "../state/state.hpp"
#include "../logger/logger.hpp"
#include "../processor/processor.hpp"
#include "../signalmanager/signalmanager.hpp"

/**
 * Represents client manager used for the server based calculation.
*/
class ClientManager {
private:
    /**
     * Checks if the given data is correct according to the
     * predefined validation rules.
     * 
     * @param src - given input data.
     * @return result of the validation.
    */
    bool isDataValid(std::vector<std::vector<int>>& src);

    /**
     * Calculates size of the given input data.
     * 
     * @param src - given input data.
     * @return size of the given input data.
    */
    int getDataSize(std::vector<std::vector<int>>& src);
public:
    /**
     * Represents client input queue opened for in read only mode.
    */
    static int clientInputQueueFd;

    /**
     * Represents client input queue opened for in write only mode.
    */
    static int clientOutputQueueFd;

    ClientManager(std::string clientInputQueueName, std::string clientOutputQueueName);

    /**
     * Starts calculation process.
     * 
     * @param src - given input data.
     * @return status of the performed operation.
    */
    int start(std::string src);
};

/**
 * Represents wrapper used for graceful exit procedure registration purposes.
*/
namespace ClientManagerHelper {
    /**
     * Handles exit signal.
     * 
     * @param s - signal identification.
    */
    static void handleExit(int s);
}