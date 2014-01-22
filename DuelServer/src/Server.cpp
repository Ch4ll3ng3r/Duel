#include "../include/Server.hpp"

CServer::CServer ()
{
    cout << "Starting Server" << endl;

    // bind listening socket on port 53000
    if (m_ListeningSocket.listen (53000) != sf::Socket::Done)
        cout << "failed to listen on port 53000" << endl;
    m_ListeningSocket.setBlocking (false);
    m_bRun = true;
    m_iTickRate = 128;
}

void CServer::Run ()
{
    while (m_bRun)
    {
        if (static_cast<int> (m_vpClients.size ()) > 1)
        {
            ReceivePackets ();
            if (m_Clock.getElapsedTime () >= sf::milliseconds (1000 / m_iTickRate))
            {
                SendPackets ();
                m_Clock.restart ();
            }
        }
        else
            ListenOnIncomingConnections ();
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape))
            m_bRun = false;
        sf::sleep (sf::milliseconds (1));
    }
}

CServer::~CServer ()
{
    cout << "Server is shutting down" << endl;

    // delete clients
    vector<CClient*>::iterator i;
    for (i = m_vpClients.begin (); i < m_vpClients.end (); i++)
    {
        SAFE_DELETE (*i);
    }

    // delete sockets
    vector<sf::TcpSocket*>::iterator j;
    for (j = m_vpSockets.begin (); j < m_vpSockets.end (); i++)
    {
        SAFE_DELETE (*j);
    }
}

void CServer::SendPackets ()
{
    sf::Packet packet;
    vector<CClient*>::iterator i;
    for (i = m_vpClients.begin (); i < m_vpClients.end (); i++)
    {
        if ((*i) == m_vpClients.at (0))
            packet << m_vpClients.at (1)->GetPlayer ()->GetPos ().x << m_vpClients.at (1)->GetPlayer ()->GetPos ().y << m_vpClients.at (1)->GetPlayer ()->GetDirection ();
        else
             packet << m_vpClients.at (0)->GetPlayer ()->GetPos ().x << m_vpClients.at (0)->GetPlayer ()->GetPos ().y << m_vpClients.at (0)->GetPlayer ()->GetDirection ();
        (*i)->Send (packet);
    }
}

void CServer::ReceivePackets ()
{
    vector<CClient*>::iterator i;
    for (i = m_vpClients.begin (); i < m_vpClients.end (); i++)
    {
        (*i)->Receive ();
    }
}

void CServer::ListenOnIncomingConnections ()
{
    sf::TcpSocket *pSocket = nullptr;
    pSocket = new sf::TcpSocket;

    // Check, if a new client has connected
    if (m_ListeningSocket.accept (*pSocket) == sf::Socket::Done)
    {
        CClient *pClient = nullptr;
        pClient = new CClient (pSocket);
        m_vpClients.push_back (pClient);
        m_vpSockets.push_back (pSocket);
        pClient = nullptr;
        pSocket = nullptr;
    }
    else
        SAFE_DELETE (pSocket);
}
