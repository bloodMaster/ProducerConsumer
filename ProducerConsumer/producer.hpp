#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "worker.hpp"

class Producer
	: public Worker
{
public:
	virtual void work();

private:
	void produce();
};

#endif