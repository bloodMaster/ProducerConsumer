#include "application.hpp"

#include "consumer.hpp"
#include "producer.hpp"

// STD
#include <csignal>

Application::
Application(unsigned int prods, unsigned int consums, const std::string& fileName)
	: m_numOfProducers(prods)
	, m_numOfConsumers(consums)
	, m_fileName(fileName)
{}

void Application::
run()
{
	validateState();
	init();
	runProdusers();
	runLogger();
	runConsumers();
	joinWorkers();
}

void Application::
validateState()
{
	if (static_cast<bool>(m_numOfProducers) ^ static_cast<bool>(m_numOfConsumers)) {
		throw std::exception("The combination of number of workers will cause deadlock.");
	}
}

void Application::
init()
{
	signal(SIGINT, &Worker::signalHandler);
	m_out.open(m_fileName.c_str());
	if (!m_out.is_open()) 
	{
		const std::string msg = "Failed to open file with name " + m_fileName;
		throw std::exception(msg.c_str());
	}
}

void Application::
runProdusers()
{
	for (int i = 0; i < m_numOfProducers; ++i) {
		m_workers.push_back(Worker::Ptr(new Producer()));
		m_workers.back()->start();
	}
}

void Application::
runLogger()
{
	m_workers.push_back(Worker::Ptr(new Logger()));
	m_workers.back()->start();
}

void Application::
runConsumers()
{
	for (int i = 0; i < m_numOfConsumers; ++i) {
		m_workers.push_back(Worker::Ptr(new Consumer (m_out)));
		m_workers.back()->start();
	}
}

void Application::
joinWorker(Worker::Ptr worker)
{
	worker->join();
}

void Application::
joinWorkers()
{
	std::for_each(m_workers.begin(), m_workers.end(), std::bind(&Application::joinWorker, this, std::placeholders::_1));
}
