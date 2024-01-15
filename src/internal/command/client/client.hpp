#pragma once

#include <args/args.hxx>
#include <string>
#include <chrono>
#include <time.h>

#include "../../clientmanager/clientmanager.hpp"
#include "../validator/validator.hpp"
// #include "../../clientmanager/clientmanager.hpp"

class Client {
private:
    args::Command* command = NULL;
    args::ValueFlag<std::string>* input = NULL;
    args::ValueFlag<std::string>* output = NULL;

public:
    Client(args::ArgumentParser*);

    bool isCalled();

    int handle();
};