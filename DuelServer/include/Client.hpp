#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include "Player.hpp"
#include <iostream>

using namespace std;

class CClient
{
    public:
        CClient (sf::TcpSocket *pSocket);
        ~CClient ();
        CPlayer* GetPlayer ();
        void Send (sf::Packet packet);
        void Receive ();

    private:
        sf::IpAddress m_RemoteIp;
        unsigned short m_sLocalPort;
        unsigned short m_sRemotePort;
        sf::TcpSocket *m_pSocket;
        CPlayer m_Player;
};

#endif // CLIENT_HPP_INCLUDED
