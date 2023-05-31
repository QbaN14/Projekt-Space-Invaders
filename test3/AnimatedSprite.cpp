#include "AnimatedSprite.h"
#include <iostream>
AnimatedSprite::AnimatedSprite(std::string path,sf::IntRect rect)
{
    srand(time(NULL));
    if (!texture.loadFromFile(path)) {
        std::cout << "Could not load texture" << std::endl;
    }
    setTextureRect(rect);
    setTexture(texture);
}
void AnimatedSprite::animate(sf::Time elapsed)
{
    move(0,speedy * elapsed.asSeconds());
}
void AnimatedSprite::add_hp()
{
    hp += 1;
}
void AnimatedSprite::remove_hp()
{
    hp -= 1;
    if (hp <= 0)
    {

    }
}
void AnimatedSprite::set_hp(int x)
{
    hp = x;
}
void AnimatedSprite::set_speedy(int x)
{
    speedy = x;
}
double AnimatedSprite::get_speedy()
{
    return speedy;
}
bool AnimatedSprite::check_x()
{
    if (getPosition().x+getTextureRect().width > 800|| getPosition().x - getTextureRect().width < 0)
    {
        return false;
    }
    return true;
}
bool AnimatedSprite::check_y()
{
    if (getPosition().y + getTextureRect().height > 600)
    {
        return false;
    }
    return true;
}