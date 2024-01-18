#pragma once

#include <vector>
#include <signal.h>
#include <iostream>

/**
 * Represents global signal manager.
*/
class SignalManager {
private:
    /**
     * Represents collection of registered callbacks.
    */
    static std::vector<void (*)(int)> callbacks;

public:
    /**
     * Initializes signal manager.
    */
    static void init();

    /**
     * Adds signal handler to the storage.
    */
    static void handleSignal(void (*callback)(int));

    /**
     * Gathers all the exit handlers and manages graceful exit.
    */
    static void handleExit(int s);
};