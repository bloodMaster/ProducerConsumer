//
//

// user define
#include "shared_data.hpp"

namespace antel
{
    // init static members
    std::mutex shared_data::m_mutex;

    bool shared_data::get_data(value_type& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        value = m_container.front();
        bool is_empty = m_container.empty();
        m_container.pop();
        return !is_empty;
    }

    void shared_data::set_data(const value_type &value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_container.push(value);
    }

    shared_data::value_type shared_data::size() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_container.size();
    }

    bool shared_data::empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_container.empty();
    }

    bool shared_data::is_min_range() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_container.size() <  m_allowed_size_for_production;
    }

    bool  shared_data::is_max_range() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_container.size() <= m_max_queue_size;
    }
};