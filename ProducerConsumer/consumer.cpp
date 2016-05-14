#include "consumer.hpp"

const int Consumer::s_consumersMaxWaitTime = 200;
std::mutex Consumer::s_ofstreamMutex;

Consumer::
Consumer(std::ofstream& out)
	: Worker()
	, m_out(out)
{}

void Consumer::
work()
{
	while (s_shouldWork || 0 != s_numOfActiveProducers) 
	{
		int item = 0;
		if (tryConsume(item)) 
		{
			writeData(item);
		}
		sleep();
	}
}

bool Consumer::
tryConsume(int& item)
{
	std::unique_lock<std::mutex> uniqueLock(s_mutex);
	while (s_dataContainer.empty()) 
	{
		if (!s_consumers.wait_for(uniqueLock, 
				std::chrono::milliseconds(s_consumersMaxWaitTime))) {
			return false;
		}
	}
	item = s_dataContainer.front();
	s_dataContainer.pop();
	if(s_dataContainer.size() <= s_allowedSizeForProduction) 
	{
		s_producers.notify_all();
	}
	return true;
}

void Consumer::
writeData(int item)
{
	std::lock_guard<std::mutex> locker(s_ofstreamMutex);
	m_out<<item<<", ";
}