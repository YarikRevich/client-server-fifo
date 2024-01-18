#include "clientmanager.hpp"

int ClientManager::clientInputQueueFd;

int ClientManager::clientOutputQueueFd;

bool ClientManager::isDataValid(std::vector<std::vector<int>>& src) {
    int colomn = src.size();

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

    return (row < MAX_DATA_NUM) && row == colomn;
};

int ClientManager::getDataSize(std::vector<std::vector<int>>& src) {
    return sizeof(int) * src.size() * src[0].size();
};

ClientManager::ClientManager(std::string clientInputQueueName, std::string clientOutputQueueName) {    
    this->clientInputQueueFd = open(clientInputQueueName.c_str(), O_RDWR, 0);
    this->clientOutputQueueFd = open(clientOutputQueueName.c_str(), O_RDWR, 0);

    SignalManager::handleSignal(&ClientManagerHelper::handleExit);
}

int ClientManager::start(std::string src) {
    std::vector<int> chunks = Processor::separateDataByDelimeter(src);

    int chunkNum = (int)sqrt(chunks.size());

    std::vector<std::vector<int>> dst;

    for (int i = 0; i < chunks.size(); i += chunkNum) {
        std::vector<int> chunk;
        for (int j = 0; j < chunkNum; j++) {
            chunk.push_back(chunks[i + j]);
        }
        dst.push_back(chunk);
    }

    if (!isDataValid(dst)) {
        Logger::SetError("Given data is not valid!");
        return EXIT_FAILURE;
    }

    int buff[dst.size()][dst[0].size()];

    for (int i = 0; i < dst.size(); i++) {
        for (int j = 0; j < dst[i].size(); j++) {
            buff[i][j] = dst[i][j];
        }
    }

    write(clientInputQueueFd, &buff, getDataSize(dst));

    int result;
    read(clientOutputQueueFd, &result, sizeof(result));
    
    State::setSum(result);

    return EXIT_SUCCESS;
};

void ClientManagerHelper::handleExit(int s) {
    if ((close(ClientManager::clientInputQueueFd)) < 0) {
        printf("Failed to close client read queue\n");
    }

    if ((close(ClientManager::clientOutputQueueFd)) < 0) {
        printf("Failed to close client write queue\n");
    }
}