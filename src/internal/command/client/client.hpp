#pragma once

#include <args/args.hxx>
#include <iostream>
#include <string>
#include <chrono>
#include <time.h>

#include "../../state/state.hpp"
#include "../validator/validator.hpp"
#include "../../clientmanager/clientmanager.hpp"

/**
 * Represents client command.
*/
class Client {
private:
    /**
     * Represents internal client command.
    */
    args::Command* command = NULL;

    /**
     * Represents client input parameter.
    */
    args::ValueFlag<std::string>* input = NULL;

    /**
     * Represents client output parameter.
    */
    args::ValueFlag<std::string>* output = NULL;

    /**
     * Represents client data parameter.
    */
    args::ValueFlag<std::string>* data = NULL;

public:
    Client(args::ArgumentParser*);

    /**
     * Checks if the command is called.
     * 
     * @return result of the check.
    */
    bool isCalled();

    /**
     * Handles the command.
     * 
     * @return result of command execution.
    */
    int handle();
};