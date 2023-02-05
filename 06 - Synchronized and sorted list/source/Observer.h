#pragma once

class Observer
{
public:
	Observer() = default;
	Observer(const Observer&) = delete;
	Observer(Observer&&) = delete;
	Observer& operator=(const Observer&) = delete;
	Observer& operator=(Observer&&) = delete;

	virtual ~Observer() = default;
	virtual void update() = 0;
};