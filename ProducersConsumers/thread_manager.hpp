//
//

#ifndef PRODUCERCONSUMER_GENERAL_H
#define PRODUCERCONSUMER_GENERAL_H

// user defined
#include "shared_data.hpp"

// standard
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include <iostream>

namespace antel
{
    class thread_manager;
};

namespace  antel
{
    class thread_manager
    {
    public:
        typedef std::shared_ptr<thread_manager> ptr;

    private:
        /// @brief deploy thread
        virtual void deploy() = 0;

    public:

        /// @brief run thread
        /// @note call deploy function, use as PVF idom
        void run();
        // @brief join current thread
        void stop();

    public:
        /// @brief user interaction handler,
        /// i.e callable function from signal
        static void signal_handler(int);

    private:
        /// @brief stop producers thread
        /// and waint until producer stops
        static void make_sanity_cleaning();

        /// @brief consumers thread waiting
        static void clean_consumers();

    private:
        std::thread m_thread;
    protected:
        static shared_data m_shared_container;
        static std::condition_variable m_producers;
        static std::condition_variable m_consumers;
    protected:
        static std::atomic<bool> m_producers_should_work;
        static std::atomic<bool> m_consumers_should_work;
    private:
        static std::mutex m_cleaning_mutex;
    protected:
        static std::condition_variable m_clean_consumers;

    };

}; // end namespace antel

#endif //PRODUCERCONSUMER_GENERAL_H
