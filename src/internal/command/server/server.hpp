#pragma once

#include <args/args.hxx>
#include <string>
#include <iostream>
#include <chrono>
#include <time.h>

#include "../../servermanager/servermanager.hpp"

/**
 * Represents server command.
*/
class Server {
private:
    /**
     * Represents internal server command.
    */
    args::Command* command = NULL;

public:
    Server(args::ArgumentParser*);

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