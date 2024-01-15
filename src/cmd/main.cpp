// #include <chrono>
// #include <time.h>

// #include "../internal/client/client.hpp"
// #include "../internal/servermanager/servermanager.hpp"

// // Represents input entity for entry queue.
// struct EntryQueueInputEntity {
// private:
//     std::vector<std::vector<int>> data;

// public:
//     EntryQueueInputEntity() {};

//     EntryQueueInputEntity(std::vector<std::vector<int>> data) : data(data) {}
// };

// void init() {
//     srand(time(0));

//     SignalManager::init();
// }

// int main() {
//     init();

//     ServerManager serverManager(NULL, 0, 0);
//     serverManager.start();
    
//     Client client(serverManager.getEntryQueueName());

//     std::vector<std::vector<int>> src = {
//         {10, 10, 10, 10}, 
//         {20, 20, 20, 20}};

//     client.calculateSum(src);

//     return -1;
// }

#include "../internal/logger/logger.hpp"
#include "../internal/command/handler/handler.hpp"

using namespace std;

/**
 * Entrypoint, to propogate logic to the handler.
*/
int main(int argc, char **argv) {
    Handler* handler = new Handler(argc, argv);

    if (handler->run() != EXIT_SUCCESS) {
        if (Logger::IsErrorExist()) {
            std::cout << Logger::GetError() << std::endl;
        }

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}