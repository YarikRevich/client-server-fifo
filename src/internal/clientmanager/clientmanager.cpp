#include "clientmanager.hpp"

int ClientManager::clientInputQueueFd;

int ClientManager::clientOutputQueueFd;

int** ClientManager::convertDataToBuff(std::vector<std::vector<int>>& src) {
    int** result = new int*[src.size()];

    for (int i = 0; i < src.size(); i++) {
        result[i] = new int[src[i].size()];
    }

    for (int i = 0; i < src.size(); i++) {
        for (int j = 0; j < src[i].size(); j++) {
            result[i][j] = src[i][j];
        }
    }

    return result;
};

bool ClientManager::isDataValid(std::vector<std::vector<int>>& src) {
    int row = -1;

    for (int i = 0; i < src.size(); i++) {
        for (int j = 0; j < src[i].size(); j++) {
            if (row == -1 || row == src[i].size()) {
                row = src[i].size();
            } else {
                return false;
            }
        }
    }

    return row < MAX_DATA_NUM;
};

int ClientManager::getDataSize(std::vector<std::vector<int>>& src) {
    return sizeof(int) * src.size() * src[0].size();
};

ClientManager::ClientManager(std::string clientInputQueueName, std::string clientOutputQueueName) {    
    this->clientInputQueueFd = open(clientInputQueueName.c_str(), O_WRONLY, 0);
    this->clientOutputQueueFd = open(clientOutputQueueName.c_str(), O_RDONLY, 0);

    SignalManager::handleSignal(&ClientManagerHelper::handleExit);
}

int ClientManager::start(std::vector<std::vector<int>>& src) {
    if (!isDataValid(src)) {
        return 0;
    }

    int buff[src.size()][src[0].size()];

    for (int i = 0; i < src.size(); i++) {
        for (int j = 0; j < src[i].size(); j++) {
            buff[i][j] = src[i][j];
        }
    }

    write(clientInputQueueFd, &buff, getDataSize(src));

    int result;

    read(clientOutputQueueFd, &result, sizeof(result));
    // int result, dst;

    // for (int i = 0; i < src.size(); i++) {
    //     while ((read(clientQueueFd, &dst, sizeof(dst))) > 0) {
    //         result += dst;
    //     };
    // }

    return result;
};

void ClientManagerHelper::handleExit(int s) {
    if ((close(ClientManager::clientInputQueueFd)) < 0) {
        printf("Failed to close client read queue\n");
    }

    if ((close(ClientManager::clientOutputQueueFd)) < 0) {
        printf("Failed to close client write queue\n");
    }
}