#include "AnimatedSprite.h"
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
    move(speedx * elapsed.asSeconds(), speedy * elapsed.asSeconds());
}
void AnimatedSprite::add_hp()
{
    hp += 1;
}
void AnimatedSprite::remove_hp()
{
    hp -= 1;
}
void AnimatedSprite::set_hp(int x)
{
    hp = x;
}
int AnimatedSprite::get_hp()
{
    return hp;
}
void AnimatedSprite::set_speedy(int x)
{
    speedy = x;
}
double AnimatedSprite::get_speedy()
{
    return speedy;
}
void AnimatedSprite::set_speedx(int x)
{
    speedx = x;
}
double AnimatedSprite::get_speedx()
{
    return speedx;
}
void AnimatedSprite::add_animation_frame(sf::IntRect rect)
{
    ani_frames.emplace_back(rect);
}
void AnimatedSprite::step(double time)
{
    elapsed_time += time;
    double frametime = 2 / ani_fps;
    while (elapsed_time >= frametime)
    {
        current_frame = (current_frame + 1) % ani_frames.size();
        elapsed_time -= frametime;
    }
    setTextureRect(ani_frames[current_frame]);
}
int AnimatedSprite::get_points_amount()
{
    return points_amount;
}
void AnimatedSprite::set_points_amount(int pts)
{
    points_amount = pts;
}
void AnimatedSprite::set_ani_fps(int x)
{
    ani_fps = x;
}
void AnimatedSprite::set_cant_animation(bool x)
{
    cant_animation = x;
}
bool AnimatedSprite::get_cant_animation()
{
    return cant_animation;
}
void AnimatedSprite::set_is_asteroid(bool x)
{
    is_asteroid = x;
}
bool AnimatedSprite::get_is_asteroid()
{
    return is_asteroid;
}
void AnimatedSprite::set_time_to_shoot(double x)
{
    time_to_shoot = x;
}
double AnimatedSprite::get_time_to_shoot()
{
    return time_to_shoot;
}
void AnimatedSprite::shoot(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    counter_to_shoot += elapsed.asSeconds();
    if (counter_to_shoot >= get_time_to_shoot())
    {
        counter_to_shoot = 0;
        std::unique_ptr<Ammunition> a = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2, getGlobalBounds().top + getGlobalBounds().height));
        ammo.emplace_back(std::move(a));
    }
}