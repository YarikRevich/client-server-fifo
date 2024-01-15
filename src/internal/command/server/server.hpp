#pragma once

#include <args/args.hxx>
#include <string>
#include <iostream>
#include <chrono>
#include <time.h>

#include "../../servermanager/servermanager.hpp"

class Server {
private:
    args::Command* command = NULL;

public:
    Server(args::ArgumentParser*);

    bool isCalled();

    int handle();
};