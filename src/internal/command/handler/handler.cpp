#include "handler.hpp"
#include <iostream>

Handler::Handler(int argc, char **argv) : argc(argc), argv(argv) {
    this->argumentParser = new args::ArgumentParser("A client-server application based on IPC FIFO used to perform calculations.\nStand with Ukraine! https://github.com/vshymanskyy/StandWithUkraine/blob/main/docs/README.md");

    this->client = new Client(argumentParser);
    this->server = new Server(argumentParser);
    this->validator = new Validator(argumentParser);
}

int Handler::run() {
    try
    {
        argumentParser->ParseCLI(argc, argv);
    }
    catch (...)
    {
        if (validator->handleArgumentParser(std::current_exception()) != EXIT_SUCCESS){
            return EXIT_FAILURE;
        };
    }

    if (client->isCalled()) {
        return client->handle();
    }

    if (server->isCalled()) {
        return server->handle();
    }

    return EXIT_SUCCESS;
}