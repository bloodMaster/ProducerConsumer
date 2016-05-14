//
//

#ifndef ANTEL_PRODUCER_HPP
#define ANTEL_PRODUCER_HPP

// user define
#include "thread_manager.hpp"

namespace antel
{
    class producer;
};

namespace  antel
{
    class producer : public thread_manager
    {
    private:
        /// @brief deploy current class thread
        virtual void deploy();

    private:
        static std::mutex m_mutex;
    };

}; // end namespace antel

#endif //ANTEL_PRODUCER_HPP
