/*******************************************************************************
Sonar

PURPOSE: Provide water depth NMEA API. Create a water depth sensor to generate NMEA 183 messages.

CREATED: 4/26/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#include "Sonar.h"
#include <sstream>
#include "Format.h"
#pragma optimize( "", off )
using namespace Formatter;

Sonar::Sonar::Sonar()
{
	Init();
}

Sonar::Sonar::Sonar(const Sonar& sn)
{
	
	_depth = sn._depth;
	_offset = sn._offset;
	_MaxRange = sn._MaxRange;
	
	_mtx = sn._mtx;
	_NMEABuf = sn._NMEABuf;


	_refresh = sn._refresh;

}

Sonar::Sonar::~Sonar()
{
}

void Sonar::Sonar::setDepth(float v)
{
	_depth = v;
}

float Sonar::Sonar::getDepth()
{
	return _depth;
}

void Sonar::Sonar::setOffset(float v)
{
	_offset = v;

}

float Sonar::Sonar::getOffset()
{
	return _offset;
}

void Sonar::Sonar::setMaxRange(float v)
{
	_MaxRange = v;
}

float Sonar::Sonar::getMaxRange()
{
	return _MaxRange;
}

void Sonar::Sonar::setRefreshRate(float f)
{
	_refresh = f;
}

float Sonar::Sonar::getRefreshRate()
{
	return _refresh;
}

void Sonar::Sonar::LoadData()
{
	setDepth(300.0f);
	setOffset(0.0f);
	setMaxRange(0.0f);
}

void Sonar::Sonar::AddNMEAmessages()
{
	
	std::lock_guard<std::mutex>(*_mtx);
	
	/// <summary>
	/// DPT sentence
	/// </summary>
	std::string str = DPT();
	str = MakeNMEASentence(str);
	_NMEABuf->push(str);
	if (event != NULL)
	{
		event->Invoke();
	}
	
	
	


}

std::string Sonar::Sonar::NMEAMessage()
{
	std::string str = "";

	bool isBuffEmpty = false;
	const int MaxIt = 2 * ceil(1 / _refresh) * 1000 / 100;
	int it = 0;
	while (!isBuffEmpty && it < MaxIt) // wait until buffer is filled.
	{
		std::lock_guard<std::mutex>(*_mtx); // lock buffer before we check so bizarre behavior!
		if (!_NMEABuf->empty())
		{
			str = _NMEABuf->front();
			_NMEABuf->pop();
			isBuffEmpty = true;

		}
		else
		{

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a little bit and try again.
	}

	return str;
}

void Sonar::Sonar::Init()
{
	_mtx = new std::mutex();
	_NMEABuf = new std::queue<std::string>();

}

std::string Sonar::Sonar::MakeNMEASentence(std::string str)
{
	std::ostringstream ss;
	ss << "IN" << str;
	str = ss.str();
	unsigned int n = str.length();
	char* s = new char[n + (unsigned int)1];
	strcpy_s(s, (n + (unsigned int)1) * sizeof(char), str.c_str());
	ss << "*" << checksum(s) << "\r\n";

	str = "$" + ss.str();
	/*std::cout << s;
	std::cout << str;*/
	delete[] s;



	return str;
}

std::string Sonar::Sonar::DPT()
{
	std::ostringstream ss;
	std::string delimiter = ",";
	Format format1(1);


	ss << "DPT" << delimiter << format1(getDepth()) << delimiter << format1(getOffset()) << delimiter << format1(getMaxRange());


	return ss.str();
}
