//
//

// user define
#include "utilities.hpp"

// standard
#include <chrono>
#include <thread>
#include <cstdlib>

namespace  antel
{
    namespace utilities
    {
        int generate_number()
        {
            return rand() % 100 + 1;
        }

        void sleep_time(int time)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }

    }; // end utilities namespace

}; // end antel namespace
