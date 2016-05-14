//
//

// user define
#include "client.hpp"
#include "consumer.hpp"
#include "logger.hpp"
#include "producer.hpp"

// standard

namespace  antel
{

    void client::run()
    {
        open_file();
        register_signal_handler();
        create_producer_threads();
        create_consumer_threads();
        create_logger_thread();
        join_producer_threads();
        join_consumer_threads();
        join_logger();
    }

    void client::open_file()
    {
        m_file_opener.open();
    }

    void client::register_signal_handler()
    {
        signal(SIGINT, thread_manager::signal_handler);
    }

    void client::create_producer_threads()
    {
        for ( short i = 0; i < m_producers_num; ++i ) {
            m_producers.emplace_back( thread_manager::ptr(new producer()) );
            m_producers.back()->run();
        }
    }

    void client::create_consumer_threads()
    {
        std::fstream& f = m_file_opener.get_file_handler();
        assert( f.is_open() );
        for ( short i = 0; i < m_consumers_num; ++i ) {
            m_consumers.emplace_back( thread_manager::ptr(new consumer(f)) );
            m_consumers.back()->run();
        }
    }

    void client::create_logger_thread()
    {
        m_logger.reset(new logger());
        m_logger->run();
    }

    void client::join_producer_threads()
    {
        for ( auto& p : m_producers ) {
            p->stop();
        }
    }

    void client::join_consumer_threads()
    {
        for ( auto& p : m_consumers ) {
            p->stop();
        }
    }

    void client::join_logger()
    {
        m_logger->stop();
    }

}; // end antel namespacing
