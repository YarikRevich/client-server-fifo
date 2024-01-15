#pragma once

#include <string>
#include <iostream>

#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "../signalmanager/signalmanager.hpp"

// Represents client manager used for the server based calculation.
class ClientManager {
private:
    int** convertDataToBuff(std::vector<std::vector<int>>& src);

    bool isDataValid(std::vector<std::vector<int>>& src);

    int getDataSize(std::vector<std::vector<int>>& src);
public:
    static int clientInputQueueFd;

    static int clientOutputQueueFd;

    ClientManager(std::string clientInputQueueName, std::string clientOutputQueueName);

    // Performs sum calculation for the given array. Seperates
    // given N*N array into N parts to be calculated on N external
    // servers.
    int start(std::vector<std::vector<int>>& src);
};

namespace ClientManagerHelper {
    //
    static void handleExit(int s);
}