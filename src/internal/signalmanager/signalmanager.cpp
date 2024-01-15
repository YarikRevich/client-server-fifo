#include "signalmanager.hpp"

std::vector<void (*)(int)> SignalManager::callbacks;

void SignalManager::init() {
    signal(SIGINT, handleExit);
}

void SignalManager::handleSignal(void (*callback)(int)) {
    callbacks.push_back(callback);
}

void SignalManager::handleExit(int s) {
    for (void (*value)(int) : callbacks) {
        value(s);
    }

    exit(1);
}