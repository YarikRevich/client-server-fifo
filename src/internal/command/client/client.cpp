#include "client.hpp"

Client::Client(args::ArgumentParser* argumentParser) {
    this->command = new args::Command(*argumentParser, "client", "Run client side");
    args::Group* group = new args::Group(*command, "");
    this->input = new args::ValueFlag<std::string>(*group, "input", "Input FIFO to connect to", {"input"});
    this->output = new args::ValueFlag<std::string>(*group, "output", "Output FIFO to connect to", {"output"});
    this->data = new args::ValueFlag<std::string>(*group, "data", "Input data to be calculated", {"data"});
}

bool Client::isCalled() {
    return command->Matched();
}

int Client::handle() {
    srand(time(0));
    SignalManager::init();

    if (!input->Matched()){
        Validator::throwValueFlagRequiredException("input");
        return EXIT_FAILURE;
    }

    if (!output->Matched()){
        Validator::throwValueFlagRequiredException("output");
        return EXIT_FAILURE;
    }

    if (!data->Matched()){
        Validator::throwValueFlagRequiredException("data");
        return EXIT_FAILURE;
    }

    ClientManager clientManager(input->Get(), output->Get());
    
    int result = clientManager.start(data->Get());
    if (result == EXIT_SUCCESS) {
        std::cout << "Result: " << State::getSum() << std::endl;
    }

    return EXIT_FAILURE;
};