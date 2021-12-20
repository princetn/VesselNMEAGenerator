/*******************************************************************************
Timer

PURPOSE: Provide trigger timer functionality for running in the background updating gps coordinates.

CREATED: 2/22/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once
#include <thread>
#include <iostream>
namespace Timer
{
	template<class T>
	class Timer
	{
	public:
		typedef void (T::* fn)(void);

		Timer(const T& trg, fn delegate, int interval);
		Timer(const Timer& t);
		~Timer();
		void Start();
		void Pause();
		void Resume();
		void Stop();
	private:
		T _target;
		fn _delegate = NULL;
		int _interval;
		bool _Enabled = false;
		bool _Paused = false;
	protected:


	};
}




template<class T>
Timer::Timer<T>::Timer(const T& trg, fn delegate, int interval)
	:_target(trg), _delegate(delegate), _interval(interval)
{
}

template<class T>
Timer::Timer<T>::Timer(const Timer& t)
{
	this->_delegate = t._delegate;
	//this->
}

template<class T>
Timer::Timer<T>::~Timer()
{
}

template<class T>
void Timer::Timer<T>::Start()
{
	_Enabled = true;
	//TODO: need to verify that threading will work this way!
	std::thread([this]() {
		while (_Enabled) // Stops the delegate execution
		{
			//std::cout << "Inside the separate thread!, I am running and doing well!" << std::endl;
			(_target.*_delegate)();
			std::this_thread::sleep_for(std::chrono::milliseconds(_interval));
			while (_Paused) // Pauses the delegate execution
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));// no need to have cpu running at 100%
			}
		}
		}).detach();
}

template<class T>
void Timer::Timer<T>::Pause()
{
	_Paused = true;
}

template<class T>
void Timer::Timer<T>::Resume()
{
	_Paused = false;
}

template<class T>
void Timer::Timer<T>::Stop()
{
	_Enabled = false;
}

