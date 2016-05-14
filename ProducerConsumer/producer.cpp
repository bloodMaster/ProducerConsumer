#include "producer.hpp"

void Producer::
work()
{
	++s_numOfActiveProducers;
	while (s_shouldWork) 
	{
		produce();
		sleep();
	}
	--s_numOfActiveProducers;
}

void Producer::
produce()
{
	std::unique_lock<std::mutex> uniqueLock(s_mutex);
	while (s_dataContainer.size() >= s_maxSizeOfQueue) 
	{
		s_producers.wait(uniqueLock);
	}
	s_dataContainer.push(randNumber());
	if(s_dataContainer.size() == 1) 
	{
		s_consumers.notify_all();
	}
}