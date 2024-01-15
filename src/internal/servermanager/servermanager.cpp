#include "servermanager.hpp"

std::string ServerManager::clientInputQueueName;

std::string ServerManager::clientOutputQueueName;

std::string ServerManager::serverManagerQueueName;

ServerManager::ServerManager() {
    ServerManager::clientInputQueueName = std::to_string(rand()).append(CLIENT_INPUT_QUEUE_SUFFIX);
    
    if ((mkfifo(ServerManager::clientInputQueueName.c_str(), 0666)) < 0) {
        printf("Failed to initialize input client queue\n");
    };

    ServerManager::clientOutputQueueName = std::to_string(rand()).append(CLIENT_OUTPUT_QUEUE_SUFFIX);
    
    if ((mkfifo(ServerManager::clientOutputQueueName.c_str(), 0666)) < 0) {
        printf("Failed to initialize output client queue\n");
    };

    this->clientInputQueueFd = open(ServerManager::clientInputQueueName.c_str(), O_RDONLY);
    this->clientOutputQueueFd = open(ServerManager::clientOutputQueueName.c_str(), O_WRONLY);

    SignalManager::handleSignal(&ServerManagerHelper::handleExit);
}

std::string ServerManager::getClientInputQueueName() {
    return clientInputQueueName;
}

std::string ServerManager::getClientOutputQueueName() {
    return clientOutputQueueName;
}

void ServerManager::start() {
    int dst[MAX_DATA_NUM][MAX_DATA_NUM];

    while ((read(clientInputQueueFd, &dst, sizeof(int) * MAX_DATA_NUM * MAX_DATA_NUM)) > 0) {
        std::vector<ServerUnit*> servers;

        // for (int i = 0; i < MAX_DATA_NUM; i++) {
        //     ServerUnit* server = new ServerUnit(chunk);

        //     servers.push_back(server);
        // }

        // for (ServerUnit* server : servers) {
        //     server->start();
        // }

        // for (int i = i)
        int result = 15;

        write(clientOutputQueueFd, &result, sizeof(result));
    };
}

void ServerManagerHelper::handleExit(int s) {
    if ((remove(ServerManager::clientInputQueueName.c_str())) < 0) {
        printf("Failed to remove input client queue\n");
    }

    if ((remove(ServerManager::clientOutputQueueName.c_str())) < 0) {
        printf("Failed to remove output client queue\n");
    }

    if ((remove(ServerManager::serverManagerQueueName.c_str())) < 0) {
        printf("Failed to remove servermanager queue\n");
    }
}