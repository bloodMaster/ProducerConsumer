//
//

// user define
#include "producer.hpp"
#include "utilities.hpp"

namespace  antel
{
   // init static members
   std::mutex producer::m_mutex;

    void producer::deploy()
    {
        while (m_producers_should_work) {
            std::unique_lock <std::mutex> lock(m_mutex);
            m_producers.wait(lock, [&]() { return m_shared_container.is_max_range(); });
            m_shared_container.set_data(utilities::generate_number());
            utilities::sleep_time(utilities::generate_number());
        }
    }

}; // end namespace antel
