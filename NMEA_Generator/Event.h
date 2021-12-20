/*******************************************************************************
Event

PURPOSE: Provide event handling support in C++ standard.

CREATED: 4/26/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include <cstddef>
#include "Object.h"

template<class T>
class Event
{
public:
	typedef void (T::* fn)(void);
	Event(const T& obj, fn delegate);
	~Event();


	void Invoke();

private:
	T _target;
	fn _delegate = NULL;




};


template<class T>
Event<T>::Event(const T& obj, fn delegate)
	:_target(obj), _delegate(delegate)
{
}
template<class T>
Event<T>::~Event()
{
}

template<class T>
void Event<T>::Invoke()
{

	(_target.*_delegate)();

}