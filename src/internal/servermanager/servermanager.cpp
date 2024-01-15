#include "servermanager.hpp"

std::string ServerManager::clientInputQueueName;

std::string ServerManager::clientOutputQueueName;

std::string ServerManager::serverManagerInputQueueName;

std::vector<std::vector<int>> ServerManager::getDataFromBuff(int src[MAX_DATA_NUM][MAX_DATA_NUM]) {
    std::vector<std::vector<int>> result;

    std::vector<int> chunks;
    
    for (int i = 0; i < MAX_DATA_NUM; i++) {
        for (int j = 0; j < MAX_DATA_NUM; j++) {
            if (src[i][j] != INT_MIN) {
                chunks.push_back(src[i][j]);
            }
        }
    }
    
    int chunkNum = (int)sqrt(chunks.size());

    for (int i = 0; i < chunks.size(); i += chunkNum) {
        std::vector<int> chunk;
        for (int j = 0; j < chunkNum; j++) {
            chunk.push_back(chunks[i + j]);
        }
        result.push_back(chunk);
    }

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

    for (int i = 0; i < MAX_DATA_NUM; i++) {
        for (int j = 0; j < MAX_DATA_NUM; j++) {
            dst[i][j] = INT_MIN;
        }
    }

    while ((read(clientInputQueueFd, &dst, sizeof(int) * MAX_DATA_NUM * MAX_DATA_NUM)) > 0) {
        std::vector<std::vector<int>> data = getDataFromBuff(dst);

        std::vector<ServerUnit*> servers;

        for (std::vector<int> chunk : data) {
            servers.push_back(new ServerUnit(serverManagerInputQueueName, chunk));
        }

        std::cout << "Allocated " << servers.size() << " server units" << std::endl;

        for (ServerUnit *server : servers) {
            server->start();
        }

        int result = 0;
        int dst;

        for (int i = 0;  i < data.size(); i++) {
            read(serverManagerInputQueueFd, &dst, sizeof(dst));

            result += dst;
        }

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