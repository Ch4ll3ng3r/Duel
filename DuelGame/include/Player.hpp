#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Weapon.hpp"
#include <string>

using namespace std;

class CPlayer
{
    public:
        CPlayer (sf::Vector2f fPos, float fDirection, sf::Sprite *pSprite);
        ~CPlayer ();
        void MoveUp (unsigned int elapsed);
        void MoveDown (unsigned int elapsed);
        void MoveRight (unsigned int elapsed);
        void MoveLeft (unsigned int elapsed);
        bool CheckCollision (sf::Vector2f fSpot);
        sf::Vector2f GetPos ();
        float GetDirection ();
        int GetHeight ();
        int GetWidth ();
        void SetPos (sf::Vector2f fPos);
        void SetDirection (float fDirection);
        void SetName (string strName);
        string GetName ();

    private:
        sf::Vector2f m_fPos;
        float m_fDirection;
        sf::Sprite *m_pSprite;
        float m_fVelocity;
        int m_Height;
        int m_Width;
        string m_strName;
};

#endif // PLAYER_HPP_INCLUDED
