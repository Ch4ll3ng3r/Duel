#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Player.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "SafeDelete.hpp"
#include <SFML/Network.hpp>

class CGame
{
    public:
        CGame();
        ~CGame();
        void Run ();

    private:
        void LoadTextures ();
        void LoadSprites ();
        void RenderSprites ();
        void ProcessWindowEvents ();
        void ProcessKeyboardEvents ();
        void CheckCollisions ();
        void InitPlayer ();
        void Connect ();
        void SendPackets ();
        void ReceivePackets ();
        map<string, sf::Texture> m_Textures;
        vector<sf::Sprite*> m_vpSprites;
        sf::RenderWindow *m_pWindow;
        CPlayer *m_pPlayerLocal;
        CPlayer *m_pPlayerConnected;
        sf::Clock m_Clock;
        int m_iTickRate;
        sf::TcpSocket m_Socket;
        sf::IpAddress m_Ip;
        unsigned short m_usPort;
        unsigned int m_uiNow;
        unsigned int m_uiLastTick;
        unsigned int m_uiElapsed;
        unsigned int m_uiLastElapsed;
};

#endif // GAME_HPP_INCLUDED
