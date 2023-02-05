#pragma once
#include "Observer.h"

class Subject
{
public:
	Subject() = default;
	Subject(const Subject&) = delete;
	Subject(Subject&&) = delete;
	Subject& operator=(const Subject&) = delete;
	Subject& operator=(Subject&&) = delete;

	virtual ~Subject() = default;
	virtual void attach(Observer* observer) = 0;
	virtual void detach(Observer* observer) = 0;
	virtual void notify() = 0;
};
