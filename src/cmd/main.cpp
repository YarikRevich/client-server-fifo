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