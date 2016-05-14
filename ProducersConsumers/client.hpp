//
//

#ifndef PRODUCERCONSUMER_CLIENT_H
#define PRODUCERCONSUMER_CLIENT_H

// user define
#include "thread_manager.hpp"
#include "file_opener.hpp"

// standard
#include <vector>

namespace antel
{
    class client;
};

namespace antel {

    class client
    {

    public:
        client(const std::string& filename, const short producers_number,
                                            const short consumers_number)
            : m_producers_num(producers_number)
            , m_consumers_num(consumers_number)
            , m_logger()
            , m_file_opener(filename)
        {
            m_producers.reserve(producers_number);
            m_consumers.reserve(consumers_number);
        }

    public:
        /// @brief run application
        void run();
    private:
        /// @brief open file
        void open_file();

        /// @brief register singlal handler
        void register_signal_handler();

        /// @brief create producer threads
        void create_producer_threads();

        /// @brief create consumer threads
        void create_consumer_threads();

        /// @brief create logger thread
        void create_logger_thread();

        /// @brief join procures threads
        void join_producer_threads();

        /// @brief join consumer threads
        void join_consumer_threads();

        /// @brief join logger threads
        void join_logger();

    private:
        short m_producers_num;
        short m_consumers_num;

    private:
        std::vector<thread_manager::ptr> m_consumers;
        std::vector<thread_manager::ptr> m_producers;
        thread_manager::ptr m_logger;

    private:
        file_opener m_file_opener;
    };
};

#endif //PRODUCERCONSUMER_CLIENT_H
