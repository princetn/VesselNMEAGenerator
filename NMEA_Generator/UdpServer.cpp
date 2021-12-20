/*******************************************************************************
Date

PURPOSE: Provide udp server utility for NMEA simulator.

CREATED: 5/05/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#include "UdpServer.h"
#include <stdexcept>

UDP::UdpServer::UdpServer()
{
	Init();
}

UDP::UdpServer::UdpServer(const UdpServer& udps)
{
	_SRV_IP = udps._SRV_IP;
	_SRV_PORT = udps._SRV_PORT;

	_rcv_buff = udps._rcv_buff;

	//_io_service = udps._io_service;
	_socket = udps._socket;

	_remote_endpoint = udps._remote_endpoint;
}

UDP::UdpServer::~UdpServer()
{
	_socket->close();
}

void UDP::UdpServer::Connect()
{
	if (_SRV_PORT == 0)
		throw std::exception("Please set server Port before trying to connect");
	if(_SRV_IP == "")
		throw std::exception("Please set server IP before trying to connect");

	_remote_endpoint = udp::endpoint(address::from_string(_SRV_IP), _SRV_PORT);
	
	_socket->open(udp::v4());
	_connected = true;
}

void UDP::UdpServer::Connect(std::string IP, unsigned short PORT)
{
	setIP(IP);
	setPort(PORT);
	_remote_endpoint = udp::endpoint(address::from_string(_SRV_IP), _SRV_PORT);

	_socket->open(udp::v4());
	_connected = true;
}

void UDP::UdpServer::End()
{
	_socket->close();
	_connected = false;
}

int UDP::UdpServer::Send(std::string msg)
{
	if (!_connected)
		throw std::exception("Please Establish connection first!");
	boost::system::error_code err;

	return _socket->send_to(boost::asio::buffer(msg),_remote_endpoint,0,err);

}

void UDP::UdpServer::setIP(std::string IP)
{
	_SRV_IP = IP;
}

std::string UDP::UdpServer::getIP()
{
	return _SRV_IP;
}

void UDP::UdpServer::setPort(unsigned short port)
{
	_SRV_PORT = port;
}

unsigned short UDP::UdpServer::getPort()
{
	return _SRV_PORT;
}

void UDP::UdpServer::Init()
{
	_socket = new udp::socket(_io_service);

}
