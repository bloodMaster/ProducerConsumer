//
//

#include "thread_manager.hpp"

namespace  antel
{
    // static members initialization
    shared_data thread_manager::m_shared_container;
    std::atomic<bool> thread_manager::m_producers_should_work(true);
    std::atomic<bool> thread_manager::m_consumers_should_work(true);
    std::condition_variable thread_manager::m_clean_consumers;
    std::condition_variable thread_manager::m_consumers;
    std::condition_variable thread_manager::m_producers;
    std::mutex thread_manager::m_cleaning_mutex;

    void thread_manager::run()
    {
        m_thread = std::thread(&thread_manager::deploy, this);
    }

    void thread_manager::stop()
    {
        m_thread.join();
    }

    void thread_manager::signal_handler(int)
    {
        std::cout <<" .................. Signal handler ................" << std::endl;
        make_sanity_cleaning();
    }

    void thread_manager::make_sanity_cleaning()
    {
        std::cout << " ***** SANITY  CLEANING **** " << std::endl;
        m_producers_should_work = false;
        m_consumers_should_work = true;
        m_consumers.notify_all();
        std::thread last(&thread_manager::clean_consumers);
        last.join();
    }

    void thread_manager::clean_consumers()
    {
        std::lock_guard<std::mutex> lock(m_cleaning_mutex);
        m_consumers_should_work = false;
    }

}; // end antel

