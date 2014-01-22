#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include "Client.hpp"
#include <vector>
#include "SafeDelete.hpp"
#include <SFML/Window.hpp>

class CServer
{
    public:
        CServer ();
        ~CServer ();
        void Run ();

    private:
        void SendPackets ();
        void ReceivePackets ();
        void ListenOnIncomingConnections ();
        bool m_bRun;
        sf::Clock m_Clock;
        vector<sf::TcpSocket*> m_vpSockets;
        vector<CClient*> m_vpClients;
        sf::TcpListener m_ListeningSocket;
        int m_iTickRate;
};

#endif // SERVER_HPP_INCLUDED
