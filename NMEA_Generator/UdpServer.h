/*******************************************************************************
UdpServer

PURPOSE: Provide udp server utility for NMEA simulator.

CREATED: 5/05/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once
#include <string>
#include "boost/asio.hpp"
#include "boost/array.hpp"


namespace UDP
{
	using boost::asio::ip::udp;
	using boost::asio::ip::address;

	class UdpServer
	{
	public:
		UdpServer();
		UdpServer(const UdpServer& udps);
		~UdpServer();
		
		void Connect();
		void Connect(std::string IP, unsigned short PORT);
		void End();
		int Send(std::string msg);
		
		void setIP(std::string IP);
		std::string getIP();

		void setPort(unsigned short port);
		unsigned short getPort();


	private:
		void Init();

		std::string _SRV_IP ="";
		unsigned short _SRV_PORT = 0;

		boost::array<char, 1024> _rcv_buff;

		boost::asio::io_service _io_service;
		udp::socket* _socket;// = udp::socket(boost::asio::io_service());

		udp::endpoint _remote_endpoint;
		
		bool _connected = false;



		

	protected:
	};
}

