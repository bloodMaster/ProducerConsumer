//
//

// user define
#include "logger.hpp"
#include "utilities.hpp"

namespace  antel
{
    // init static members
    std::mutex logger::m_mutex;

    void logger::deploy()
    {
        while (m_producers_should_work || m_consumers_should_work) {
            std::unique_lock<std::mutex> lock(m_mutex);
            utilities::sleep_time(60);
            std::cout << " Logger : shared data size : " << m_shared_container.size() << std::endl;
        }
    }

}; // end antel namespace
