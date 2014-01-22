#include "../include/Client.hpp"

CClient::CClient (sf::TcpSocket *pSocket)
{
    m_pSocket = pSocket;
    m_pSocket->setBlocking (false);
    m_RemoteIp = pSocket->getRemoteAddress ();
    m_sLocalPort = pSocket->getLocalPort ();
    m_sRemotePort = pSocket->getRemotePort ();
    cout << "a new player has connected" << endl;
}

CClient::~CClient ()
{
    m_pSocket = nullptr;
}

CPlayer* CClient::GetPlayer ()
{
    return &m_Player;
}

void CClient::Send (sf::Packet packet)
{
    if (m_pSocket->send (packet) != sf::Socket::Done)
        cout << "failed to send packet to " << m_RemoteIp << endl;
}

void CClient::Receive ()
{
    sf::Packet packet;
    sf::Vector2<float> fPlayerPos;
    float fPlayerDirection = 0.f;

    // Receive Packet
    if (m_pSocket->receive (packet) != sf::Socket::Done)
        cout << "failed to receive packet from " << m_RemoteIp << endl;
    else
    {
        // Extract Packet
        if (packet >> fPlayerPos.x >> fPlayerPos.y >> fPlayerDirection)
        {
            m_Player.SetPos (fPlayerPos);
            m_Player.SetDirection (fPlayerDirection);
        }
        else
            cout << "failed to extract packet received from " << m_RemoteIp << endl;
    }

}
