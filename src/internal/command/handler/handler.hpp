#pragma once

#include <args/args.hxx>
#include "../client/client.hpp"
#include "../server/server.hpp"
#include "../validator/validator.hpp"

using namespace std;

/**
 * Provides access to operate CLI command handlers.
*/
class Handler {
private:
    /**
     * Represents internal argument parser.
    */
    args::ArgumentParser* argumentParser = NULL;

    /**
     * Represents server command.
    */
    Server* server = NULL;

    /**
     * Represents client command.
    */
    Client* client = NULL;

    /**
     * Represents validator instance.
    */
    Validator* validator = NULL;

    /**
     * Represents CLI argument number.
    */
    int argc;

    /**
     * Represents CLI argument array.
    */
    char **argv;
public:
    Handler(int argc, char **argv);

    /**
     * Starts command handler execution. 
     * 
     * @return result of command execution.
    */
    int run();
};