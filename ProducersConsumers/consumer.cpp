//
//

// user define
#include "consumer.hpp"
#include "utilities.hpp"

//standard

namespace  antel
{
    // init static members
    std::mutex consumer::m_mutex;

    void consumer::deploy()
    {
        while (m_consumers_should_work) {
            std::unique_lock<std::mutex> lock(m_mutex);

            if ( m_consumers.wait_for(lock, std::chrono::milliseconds(100), [&]() { return !m_shared_container.empty(); }) ) {
                value_type v;
                if (m_shared_container.get_data(v)) {
                    write_to_file(v);
                }
                if (m_shared_container.is_min_range()) {
                    m_producers.notify_all();
                }
                utilities::sleep_time(utilities::generate_number());
            }
            m_clean_consumers.notify_one();
        }
    }

    void consumer::write_to_file(const value_type &v)
    {
        assert(m_file.is_open());
        m_file << v << ", ";
    }

}; // end namespace antel
