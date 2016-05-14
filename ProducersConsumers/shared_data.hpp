//
//

#ifndef PRODUCERCONSUMER_SHARED_DATA_H
#define PRODUCERCONSUMER_SHARED_DATA_H

// standard
#include <queue>
#include <mutex>

#define max_queue_size 100
#define allow_size_for_production 80

namespace  antel
{
    class shared_data;
};

namespace  antel
{
    class shared_data
    {

    public:
        typedef std::queue<int> container_type;
        typedef container_type::value_type value_type;

    public:
        shared_data()
                : m_container()
        {
        }
        /// @brief get data from container
        /// @param[out] value from container
        /// @return true, if container non empty, otherwise false
        bool get_data(value_type&);

        /// @brief set data to container
        /// @param[in] value
        void set_data(const value_type&);

        /// @brief get container size
        value_type size() const;

        /// @brief container is empty or not
        /// @return true, if non empty, otherwise false
        bool empty() const;

        /// @brief indicate whether container in lower bound
        /// @return true if container in lower bound, otherwise false
        bool is_min_range() const;

        /// @brief indicate whether container in upper bound
        /// @return true if container in upper bound, otherwise false
        bool is_max_range() const;

    private:
        container_type m_container;
        static std::mutex m_mutex;

    private:
        static const unsigned int m_max_queue_size = max_queue_size;
        static const unsigned int m_allowed_size_for_production = allow_size_for_production;

    }; // end class shared_data

}; // end namespace antel

#endif //PRODUCERCONSUMER_SHARED_DATA_H
