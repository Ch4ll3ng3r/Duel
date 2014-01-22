#include "../include/Game.hpp"

CGame::CGame()
{
    Connect ();
    LoadTextures ();
    LoadSprites ();
    InitPlayer ();
    m_pWindow = nullptr;
    m_pWindow = new sf::RenderWindow (sf::VideoMode::getDesktopMode (), "Duel", sf::Style::Fullscreen);
    m_uiElapsed = 0;
    m_uiNow = 0;
    m_uiLastElapsed = 0;
    m_uiLastTick = 0;
}

CGame::~CGame()
{
    vector<sf::Sprite*>::iterator i;
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        SAFE_DELETE (*i);
    }
    SAFE_DELETE (m_pPlayerLocal);
    SAFE_DELETE (m_pPlayerConnected);
    SAFE_DELETE (m_pWindow);
}

void CGame::Run ()
{
    while (m_pWindow->isOpen ())
    {
        m_uiNow = m_Clock.getElapsedTime ().asMilliseconds ();
        m_uiElapsed = m_uiNow - m_uiLastElapsed;
        m_uiLastElapsed = m_uiNow;
        ProcessWindowEvents ();
        ProcessKeyboardEvents ();
        CheckCollisions ();
        if (m_uiNow >= m_uiLastTick + 1000 / m_iTickRate)
        {
            SendPackets ();
            m_uiLastTick = m_uiNow;
        }
        ReceivePackets ();
        RenderSprites ();
        sf::sleep (sf::milliseconds (1));
    }
}

void CGame::LoadTextures ()
{
    pair<string, sf::Texture> Texture;
    sf::Texture _Texture;
    _Texture.loadFromFile ("Graphics/Background.bmp");
    Texture = make_pair ("Background", _Texture);
    m_Textures.insert (Texture);
    _Texture.loadFromFile ("Graphics/Player.bmp");
    Texture = make_pair ("Player", _Texture);
    m_Textures.insert (Texture);
    _Texture.loadFromFile ("Graphics/Bullet.bmp");
    Texture = make_pair ("Bullet", _Texture);
    m_Textures.insert (Texture);
}

void CGame::LoadSprites ()
{
    sf::Sprite *pSprite = nullptr;
    pSprite = new sf::Sprite (m_Textures.at ("Background"));
    m_vpSprites.push_back (pSprite);
    pSprite = nullptr;
    pSprite = new sf::Sprite (m_Textures.at ("Player"));
    m_vpSprites.push_back (pSprite);
    m_pPlayerLocal = new CPlayer (sf::Vector2f (30.f, 540.f), 0.f, pSprite);
    pSprite = nullptr;
    pSprite = new sf::Sprite (m_Textures.at ("Player"));
    m_vpSprites.push_back (pSprite);
    m_pPlayerConnected = new CPlayer (sf::Vector2f (1890.f, 540.f), 180.f, pSprite);
    pSprite = nullptr;
}

void CGame::RenderSprites ()
{
    vector<sf::Sprite*>::iterator i;
    m_pWindow->clear ();
    for (i = m_vpSprites.begin (); i < m_vpSprites.end (); i++)
    {
        m_pWindow->draw (**i);
    }
    m_pWindow->display ();
}

void CGame::ProcessWindowEvents ()
{
    sf::Event event;
    while (m_pWindow->pollEvent (event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_pWindow->close ();
            } break;
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        m_pWindow->close ();
                    }
                    default:
                    {
                        // nothing
                    }
                }
            } break;
            default:
            {
                // nothing
            }
        }
    }
}

void CGame::ProcessKeyboardEvents ()
{
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))
        m_pPlayerLocal->MoveUp (m_uiElapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))
        m_pPlayerLocal->MoveDown (m_uiElapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
        m_pPlayerLocal->MoveRight (m_uiElapsed);
    else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))
        m_pPlayerLocal->MoveLeft (m_uiElapsed);
}

void CGame::CheckCollisions ()
{
    sf::Vector2f fPos = m_pPlayerLocal->GetPos ();
    int Height = m_pPlayerLocal->GetHeight ();
    int Width = m_pPlayerLocal->GetWidth ();
    if (fPos.x < static_cast<float> (Width / 2))
    {
        fPos.x = static_cast<float> (Width / 2);
        m_pPlayerLocal->SetPos (fPos);
    }
    if (fPos.x > static_cast<float> (m_pWindow->getSize ().x - Width / 2))
    {
        fPos.x = static_cast<float> (m_pWindow->getSize ().x - Width / 2);
        m_pPlayerLocal->SetPos (fPos);
    }
    if (fPos.y < static_cast<float> (Height / 2))
    {
        fPos.y = static_cast<float> (Height / 2);
        m_pPlayerLocal->SetPos (fPos);
    }
    if (fPos.y > static_cast<float> (m_pWindow->getSize ().y - Height / 2))
    {
        fPos.y = static_cast<float> (m_pWindow->getSize ().y - Height / 2);
        m_pPlayerLocal->SetPos (fPos);
    }
}

void CGame::InitPlayer ()
{
    char cName[30];
    cout << "Name: ";
    cin.getline (cName, 29);
    m_pPlayerLocal->SetName (cName);
}

void CGame::Connect ()
{
    m_iTickRate = 128;
    m_usPort = 53000;
    cout << "Ip: ";
    cin >> m_Ip;
    if (m_Socket.connect (m_Ip, m_usPort) != sf::Socket::Done)
        cout << "failed to connect to " << m_Ip << "on port " << m_usPort << endl;
    else
        cout << "connection established" << endl;
    m_Socket.setBlocking (false);
}

void CGame::SendPackets ()
{
    sf::Packet packet;
    packet << m_pPlayerLocal->GetPos ().x << m_pPlayerLocal->GetPos ().y << m_pPlayerLocal->GetDirection ();
    if (m_Socket.send (packet) != sf::Socket::Done)
        cout << "failed to send packet" << endl;
}

void CGame::ReceivePackets ()
{
    sf::Packet packet;
    if (m_Socket.receive (packet) != sf::Socket::Done)
        cout << "failed to receive packet" << endl;
    else
    {
        sf::Vector2f fPos;
        float fDirection;
        if (packet >> fPos.x >> fPos.y >> fDirection)
        {
            m_pPlayerConnected->SetPos (fPos);
            m_pPlayerConnected->SetDirection (fDirection);
        }
        else
            cout << "failed to extract packet" << endl;
    }
}
