#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(std::string path,sf::IntRect rect)
{
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
void AnimatedSprite::set_time_to_shoot(double x)
{
    time_to_shoot = x;
}
double AnimatedSprite::get_time_to_shoot()
{
    return time_to_shoot;
}
void AnimatedSprite::shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
}
double AnimatedSprite::get_counter_to_shoot()
{
    return counter_to_shoot;
}
void AnimatedSprite::set_counter_to_shoot(double x)
{
    counter_to_shoot=x;
}
void AnimatedSprite::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    animate(elapsed);
    shoot(elapsed, ammo);
    step(elapsed.asSeconds());
}