#include "../include/Player.hpp"

CPlayer::CPlayer (sf::Vector2f fPos, float fDirection, sf::Sprite *pSprite)
{
    m_fVelocity = 0.5f;
    m_fPos = fPos;
    m_pSprite = pSprite;
    m_fDirection = fDirection;
    m_pSprite->setOrigin (30.f, 30.f);
    m_pSprite->setPosition (m_fPos);
    m_pSprite->setRotation (m_fDirection);
    m_Height = m_pSprite->getTextureRect().height;
    m_Width = m_pSprite->getTextureRect().width;
}

CPlayer::~CPlayer()
{
    m_pSprite = nullptr;
}

void CPlayer::MoveUp (unsigned int elapsed)
{
    m_fPos.y -= m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::MoveDown (unsigned int elapsed)
{
    m_fPos.y += m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::MoveRight (unsigned int elapsed)
{
    m_fPos.x += m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::MoveLeft (unsigned int elapsed)
{
    m_fPos.x -= m_fVelocity * static_cast<float> (elapsed);
    m_pSprite->setPosition (m_fPos);
}

sf::Vector2f CPlayer::GetPos ()
{
    return m_fPos;
}

bool CPlayer::CheckCollision (sf::Vector2f fSpot)
{
    return (fSpot.x >= m_fPos.x - static_cast<float> (m_Width)) &&
           (fSpot.x <= m_fPos.x + static_cast<float> (m_Width)) &&
           (fSpot.y >= m_fPos.y + static_cast<float> (m_Height)) &&
           (fSpot.y <= m_fPos.y - static_cast<float> (m_Height));
}

int CPlayer::GetHeight ()
{
    return m_Height;
}

int CPlayer::GetWidth ()
{
    return m_Width;
}

void CPlayer::SetPos (sf::Vector2f fPos)
{
    m_fPos = fPos;
    m_pSprite->setPosition (m_fPos);
}

void CPlayer::SetName (string strName)
{
    m_strName = strName;
}

string CPlayer::GetName ()
{
    return m_strName;
}

float CPlayer::GetDirection ()
{
    return m_fDirection;
}

void CPlayer::SetDirection (float fDirection)
{
    m_fDirection = fDirection;
}
