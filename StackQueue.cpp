#include <iostream>
// StackQueues.cpp : Defines the exported functions for the DLL application.
//

#include "StackQueue.h"


ArrayBasedStack::ArrayBasedStack()
{
	int size = 10; // Configurable size

	m_size = size;
	m_values = new int[size];
	m_count = 0;
}

int ArrayBasedStack::peek() const
{
	if (this->isEmpty())
	{
		throw "ADT is emtpy";
	}
	else
	{
		return m_values[m_count - 1];
	}
}

bool ArrayBasedStack::isEmpty() const
{
	return (m_count == 0);
}

bool ArrayBasedStack::push(const int &val)
{

	if (m_count >= m_size)
	{
		return false;
	}

	m_values[m_count] = val;
	m_count += 1;
	return true;
}

bool ArrayBasedStack::pop()
{

	if (m_count == 0)
	{
		return false;
	}

	m_values[m_count] = 0;
	m_count -= 1;
	return true;
}

std::string ArrayBasedStack::toString() const
{
	std::string str = "";

	for (int i = 0; i < m_count; i++)
	{
		str += std::to_string(m_values[i]);

		if (i != m_count - 1)
		{
			str += " ";
		}
	}
	return str;
}

int * ArrayBasedStack::getArray() const{
	return m_values;
}

int ArrayBasedStack::getCount() const {
	return m_count;
}


ArrayBasedStack::~ArrayBasedStack()
{
	m_values = NULL;
	delete m_values;
}




// QUEUE

ArrayBasedQueue::ArrayBasedQueue()
{
	int size = 10;

	m_size = size;
	m_values = new std::string[size];
	m_count = 0;
}

std::string ArrayBasedQueue::peekFront() const
{
	if (this->isEmpty())
	{
		throw "ADT is emtpy";
	}
	else
	{
		return m_values[0];
	}
}

bool ArrayBasedQueue::isEmpty() const
{
	return (m_count == 0);
}

bool ArrayBasedQueue::deQueue()
{

	if (m_count == 0){
		return false;
	}

	for (int i = 0; i < m_count - 1; i++)
	{
		m_values[i] = m_values[i+1];
	}
	for (int i = m_count; i < m_size; i++){
		m_values[i] = "";
	}

	m_count--;
	return true;
}

bool ArrayBasedQueue::enQueue(const std::string &val)
{

	if (m_count == m_size)
	{
		return false;
	}

	m_values[m_count++] = val;
	return true;
}

std::string ArrayBasedQueue::toString() const
{
	std::string str = "";

	for (int i = 0; i < m_count; i++)
	{
		str += m_values[i];

		if (i != m_count - 1)
		{
			str += " ";
		}
	}
	return str;
}

ArrayBasedQueue::~ArrayBasedQueue()
{
	m_values = NULL;
	delete m_values;
}

std::string * ArrayBasedQueue::getArray() const{
	return m_values;
}

int ArrayBasedQueue::getCount() const {
	return m_count;
}