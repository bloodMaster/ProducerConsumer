#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include "worker.hpp"

// STD
#include <fstream>

class Consumer
	: public Worker
{
public:
	Consumer(std::ofstream& out);

public:
	virtual void work();

private:
	bool tryConsume(int& item);
	void writeData(int item);

private:
	static const int s_consumersMaxWaitTime;

private:
	static std::mutex s_ofstreamMutex;
	
private:
	std::ofstream& m_out;

};

#endif