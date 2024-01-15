#include "server.hpp"

Server::Server(args::ArgumentParser* argumentParser) {
    this->command = new args::Command(*argumentParser, "server", "Run server side");
}

bool Server::isCalled() {
    return command->Matched();
}

int Server::handle() {
    srand(time(0));
    SignalManager::init();

    std::cout << "Running server side!" << std::endl;

    ServerManager serverManager;

    std::cout << "Queues are spawned: \n" << 
        "    Input: " << serverManager.getClientInputQueueName() << 
        std::endl << "    Output: " << serverManager.getClientOutputQueueName() << std::endl;

    serverManager.start();

    return EXIT_SUCCESS;
};