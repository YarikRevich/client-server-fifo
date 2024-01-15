#include "client.hpp"

Client::Client(args::ArgumentParser* argumentParser) {
    this->command = new args::Command(*argumentParser, "client", "Run client side");
    args::Group* group = new args::Group(*command, "");
    this->input = new args::ValueFlag<std::string>(*group, "input", "Input FIFO to connect to", {"input"});
    this->output = new args::ValueFlag<std::string>(*group, "output", "Output FIFO to connect to", {"output"});
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

    ClientManager clientManager(input->Get(), output->Get());

    std::vector<std::vector<int>> src = {
        {30, 30, 30, 30}, 
        {20, 20, 20, 20}};

    std::cout << "Starting client calculation!" << std::endl;

    int result = clientManager.start(src);

    std::cout << result << std::endl;

    return EXIT_SUCCESS;
};