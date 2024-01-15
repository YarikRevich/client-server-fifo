#include "servermanager.hpp"

std::string ServerManager::clientInputQueueName;

std::string ServerManager::clientOutputQueueName;

std::string ServerManager::serverManagerInputQueueName;

std::vector<std::vector<int>> ServerManager::getDataFromBuff(int src[MAX_DATA_NUM][MAX_DATA_NUM]) {
    std::vector<std::vector<int>> result;

    for (int i = 0; i < MAX_DATA_NUM; i++) {
        if (result.size() <= i) {
            result.push_back(std::vector<int>());
        }

        for (int j = 0; j < MAX_DATA_NUM; j++) {
            result[i].push_back(0);
        }
    }
    
    for (int i = 0; i < MAX_DATA_NUM; i++) {
        for (int j = 0; j < MAX_DATA_NUM; j++) {
            result[i][j] = src[i][j];
        }   
    }

    // for (auto v1 : result) {
    //     for (auto v2 : v1) {
    //         std::cout << v2 << std::endl;
    //     }
    // }

    return result;
};

ServerManager::ServerManager() {
    ServerManager::clientInputQueueName = std::to_string(rand()).append(CLIENT_INPUT_QUEUE_SUFFIX);
    
    if ((mkfifo(ServerManager::clientInputQueueName.c_str(), 0666)) < 0) {
        printf("Failed to initialize input client queue\n");
    };

    ServerManager::clientOutputQueueName = std::to_string(rand()).append(CLIENT_OUTPUT_QUEUE_SUFFIX);
    
    if ((mkfifo(ServerManager::clientOutputQueueName.c_str(), 0666)) < 0) {
        printf("Failed to initialize output client queue\n");
    };

    ServerManager::serverManagerInputQueueName = std::to_string(rand()).append(SERVER_MANAGER_INPUT_QUEUE_SUFFIX);
    if ((mkfifo(ServerManager::serverManagerInputQueueName.c_str(), 0666)) < 0) {
        printf("Failed to initialize input servermanager queue\n");
    };

    this->clientInputQueueFd = open(ServerManager::clientInputQueueName.c_str(), O_RDWR, 0);
    this->clientOutputQueueFd = open(ServerManager::clientOutputQueueName.c_str(), O_RDWR, 0);
    this->serverManagerInputQueueFd = open(ServerManager::serverManagerInputQueueName.c_str(), O_RDWR, 0);

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
        std::vector<std::vector<int>> data = getDataFromBuff(dst);

        std::vector<ServerUnit*> servers;

        for (std::vector<int> chunk : data) {
            servers.push_back(new ServerUnit(serverManagerInputQueueName, chunk));
        }

        int result = 0;
        int dst;

        for (int i = 0;  i < data.size(); i++) {
            read(serverManagerInputQueueFd, &dst, sizeof(dst));

            result += dst;
        }

        std::cout << result << std::endl;

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

    if ((remove(ServerManager::serverManagerInputQueueName.c_str())) < 0) {
        printf("Failed to remove input servermanager queue\n");
    }
}