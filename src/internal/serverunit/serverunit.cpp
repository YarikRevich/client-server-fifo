#include "serverunit.hpp"

#include <iostream>

int ServerUnit::serverManagerInputQueueFd;

ServerUnit::ServerUnit(std::string serverManagerInputQueueName, std::vector<int>& chunk) : chunk(chunk), thread(&ServerUnit::startRaw, this) {
    this->serverManagerInputQueueFd = open(serverManagerInputQueueName.c_str(), O_RDWR, 0);
}

void ServerUnit::startRaw() {
    int result = 0;

    for (int value : chunk) {
        result += value;
    }

    std::cout << result << std::endl;

    write(serverManagerInputQueueFd, &result, sizeof(result));
}

void ServerUnit::start() {
    thread.detach();
}