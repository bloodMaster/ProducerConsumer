//
//

#ifndef ANTEL_CONSUMER_HPP
#define ANTEL_CONSUMER_HPP

// user define
#include "thread_manager.hpp"
#include "shared_data.hpp"

// standard
#include <fstream>
#include <mutex>
#include <cassert>

namespace  antel
{
    class consumer;
};

namespace  antel
{
    class consumer : public thread_manager
    {
    private:
        typedef shared_data::value_type value_type;

    public:
        consumer(std::fstream &file)
                : m_file(file)
        {
            assert(file.is_open());
        }

    private:
        /// @brief deploy current thread
        virtual void deploy();

    private:
        /// @brief write to file
        /// @param[in] value for file writing
        void write_to_file(const value_type &v);

    private:
        std::fstream &m_file;
        static std::mutex m_mutex;

    }; // end class consumer

}; // end namespace antel

#endif //ANTEL_CONSUMER_HPP
