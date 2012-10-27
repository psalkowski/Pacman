#include "Player.h"

Player::Player(double x, double y) : Monster(PLAYER, x, y) {
    setDefaultPos(x, y);
    setMove(STAND); 
    initAnimation();
    m_time = 0;
    m_life = 3;
    m_score = 0;
}

void Player::update(double diff) {
    Monster::update(diff);

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

void Player::lostLife() {
    m_life--; 
    resetPos();
    setMove(STAND);
}