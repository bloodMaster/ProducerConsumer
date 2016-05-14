#ifndef WORKER_HPP
#define WORKER_HPP


#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>

class Worker
{
public:
	typedef std::shared_ptr<Worker> Ptr;

public:
	static void signalHandler(int sigNum);

public:
	virtual void work() = 0;

public:
	void start();
	void join();

protected:
	int randNumber(int lowerBound = 1, int upperBound = 100);
	void sleep();

protected:
	static std::atomic<bool> s_shouldWork;
	static std::atomic<int> s_numOfActiveProducers;

protected:
	typedef std::queue<int> DataContainer;
	static DataContainer s_dataContainer;
	static const unsigned int s_maxSizeOfQueue;
	static const unsigned int s_allowedSizeForProduction;

protected:
	static std::mutex s_mutex;
	static std::condition_variable s_producers;
	static std::condition_variable s_consumers;

protected:
	std::thread m_thread;
};


class Logger
	: public Worker
{
public:
	virtual void work();

private:
	void log();
};

#endif