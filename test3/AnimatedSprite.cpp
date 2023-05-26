#include "AnimatedSprite.h"
#include <iostream>
AnimatedSprite::AnimatedSprite(std::string path)
{
    srand(time(NULL));
    if (!texture.loadFromFile(path)) {
        std::cout << "Could not load texture" << std::endl;
    }
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