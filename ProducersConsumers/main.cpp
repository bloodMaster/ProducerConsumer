
// user define
#include "client.hpp"

namespace {

static bool check_consumer_produces_nums(short producer_number,
                                         short consumer_number)
{
    std::string error_message;
    if ( producer_number < 1 || producer_number > 10 ) {
        error_message = "Procuder number must be in [1:10] range.";
    } else if ( consumer_number  < 1 || consumer_number > 10 ) {
        error_message = "Consumer number must be in [1:10] range.";
    }
    std::cout << error_message << std::endl;
    return error_message.empty();
}

}

int main(int argc, const char* argv[])
{
    if ( 3 != argc ) {
        std::cout << "Number of argument invalid, must me two numbers" << std::endl;
        return -1;
    }
    int producer = std::atoi(argv[1]);
    int consumer = std::atoi(argv[2]);
    std::cout << producer << "  " << consumer << std::endl;
    if ( !check_consumer_produces_nums(producer, consumer) ) {
        return -1;
    }
    try {
        antel::client c("data.txt", producer, consumer);
        c.run();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}