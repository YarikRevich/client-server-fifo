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
    args::ArgumentParser* argumentParser = NULL;

    Server* server = NULL;
    Client* client = NULL;
    Validator* validator = NULL;

    int argc;
    char **argv;

public:
    Handler(int argc, char **argv);

    /**
     * Starts command handler execution. 
    */
    int run();
};