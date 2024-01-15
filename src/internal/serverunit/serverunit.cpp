#include "serverunit.hpp"

#include <iostream>

std::string ServerUnit::serverQueueName;

ServerUnit::ServerUnit(std::vector<int>& chunk) : chunk(chunk), thread(&ServerUnit::startRaw, this) {
    // ServerUnit::serverQueueName = std::to_string(rand()).append(SERVER_QUEUE_SUFFIX);
    
    // if ((mkfifo(ServerManager::clientQueueName.c_str(), 0666)) < 0) {
    //     printf("Failed to initialize entry queue\n");
    // };

    // this->serverQueueName = open(ServerManager::clientQueueName.c_str(), O_RDWR, 0);

    SignalManager::handleSignal(&ServerUnitHelper::handleExit);
}

void ServerUnit::startRaw() {
    std::cout << "exists" << std::endl;
}

void ServerUnit::start() {
    thread.detach();
}

ServerUnit::~ServerUnit() { 

}

void ServerUnitHelper::handleExit(int s) {
    std::cout << "server exit" << std::endl;
}