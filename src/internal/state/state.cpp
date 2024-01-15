#include "state.hpp"

int State::sum;

int State::getSum() {
    return sum;
}

void State::setSum(int value) {
    State::sum = value;
}