#include "worker.hpp"

#include <iostream>
#include <random>

std::mutex s_mutex;
std::atomic<int> Worker::s_numOfActiveProducers;

std::atomic<bool> Worker::s_shouldWork = true;

Worker::DataContainer Worker::s_dataContainer;
const unsigned int Worker::s_maxSizeOfQueue = 100;
const unsigned int Worker::s_allowedSizeForProduction = 80;

std::mutex Worker::s_mutex;
std::condition_variable Worker::s_producers;
std::condition_variable Worker::s_consumers;


void Worker::
signalHandler(int sigNum)
{
	s_shouldWork = false;
}

void Worker::
start()
{
	m_thread = std::thread(&Worker::work, this);
}

void Worker::
join()
{
	m_thread.join();
}

int Worker::
randNumber(int lowerBound, int upperBound)
{
	static thread_local std::mt19937 gen;
	std::uniform_int_distribution<int> d(lowerBound, upperBound);
	return d(gen);
}

void Worker::
sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(randNumber(0, 100)));
}

void Logger::
work()
{
	while (s_shouldWork || 0 != s_numOfActiveProducers) 
	{
		log();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Logger::
log()
{
	std::unique_lock<std::mutex> uniqueLock(s_mutex);
	std::cout << "Num of elements: " << s_dataContainer.size() << "\n";
}