#include "Player.h"

Player::Player(double x, double y) : GameObject(x, y) { 
    setType(PLAYER); 
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
    m_animation.x = move * 33;
}

void Player::goRight(double diff) {
    setRect(diff, getRect()->y);
}

void Player::goLeft(double diff) {
    setRect(diff, getRect()->y);
}

void Player::goUp(double diff) {
    setRect(getRect()->x, diff);
}

void Player::goDown(double diff) {
    setRect(getRect()->x, diff);
}

double Player::getNextPosition(double diff) {
    switch(getMove()) {
        case LEFT:
            return getRect()->x + getVelocity() * diff;
        case RIGHT:
            return getRect()->x + getVelocity() * diff + 1; // +1, bo SDL_Rect x jest liczba calkowita, czyli zaokrlaga
        case UP:
            return getRect()->y + getVelocity() * diff;
        case DOWN:
            return getRect()->y + getVelocity() * diff + 1;
    }

    return 0;
}