#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "worker.hpp"

// STD
#include <list>
#include <string>
#include <fstream>

class Application
{
public:
	Application(unsigned int prods, unsigned int consums, const std::string& fileName);
public:
	void run();

private:
	void validateState();
	void init();
	void runProdusers();
	void runLogger();
	void runConsumers();
	void joinWorker(Worker::Ptr worker);
	void joinWorkers();

private:
	const unsigned int m_numOfProducers;
	const unsigned int m_numOfConsumers;
	const std::string m_fileName;
	std::list<Worker::Ptr> m_workers;
	std::ofstream m_out;
};

#endif