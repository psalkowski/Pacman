#include "Player.h"

Player::Player(double x, double y) : Monster(PLAYER, x, y) { 
    setMove(STAND); 
    initAnimation();
    m_time = 0;
}

void Player::update(double diff) {
    double ds = getNextPosition(diff);

    switch(getMove()) { 
        case LEFT:  setVelocity(-2.0); goLeft(ds);   break;
        case RIGHT: setVelocity(2.0); goRight(ds);  break;
        case DOWN:  setVelocity(2.0); goDown(ds);   break;
        case UP:    setVelocity(-2.0); goUp(ds);     break;
    }

    m_time += diff;

    if(m_time < 0.2)
        updateAnimation(STAND);
    else if(m_time < 0.4)
        updateAnimation(getMove());
    else m_time = 0;
}

void Player::initAnimation() {
    m_animation.h = m_height;
    m_animation.w = m_width;
    m_animation.y = 0;
}

void Player::updateAnimation(Move move) {
    m_animation.x = move * m_width;
}