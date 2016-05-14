//
//

#ifndef ANTEL_LOGGER_HPP
#define ANTEL_LOGGER_HPP

// user define
#include "thread_manager.hpp"

// standard
#include <mutex>

namespace antel
{
    class logger;
}

namespace  antel
{
    class logger : public thread_manager
    {
    private:
        /// @brief deploy current class thread
        virtual void deploy();

    protected:
        static std::mutex m_mutex;

    }; // end logger class

}; // end antel namespace

#endif //ANTEL_LOGGER_HPP
