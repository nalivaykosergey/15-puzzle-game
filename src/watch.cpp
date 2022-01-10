#include "watch.h"

Watch::Watch(const std::string & img_path)
{
    std::string file_name("_.png");
    watch_texture[10].loadFromFile(img_path + file_name);
    for(int i = 0; i < 10; i++)
    {
        file_name.replace(0, 1, std::to_string(i));
        watch_texture[i].loadFromFile(img_path + file_name);
    }
    watch_sprite[2].setTexture(watch_texture[10]);
}

void Watch::startWatch()
{
    is_active = true;
    current_time = 0;
    watch.restart();
}
void Watch::stopWatch()
{
    is_active = false;
}

float Watch::getCurrentTime() const
{
    return watch.getElapsedTime().asSeconds();
}

void Watch::drawWatch(sf::RenderWindow & window, int x_offset, int y_offset)
{
    if(current_time >= 3600)
        stopWatch();
    if (is_active)
        current_time = static_cast<int>(getCurrentTime());

    int second1, second2, min1, min2;
    second1 = current_time % 60 / 10;
    second2 = current_time % 10 ;
    min1 = current_time / 60 / 10;
    min2 = current_time / 60 % 10;
    
    watch_sprite[0].setTexture(watch_texture[min1]);
    watch_sprite[1].setTexture(watch_texture[min2]);
    watch_sprite[3].setTexture(watch_texture[second1]);
    watch_sprite[4].setTexture(watch_texture[second2]);


    for(int i = 0; i < 5; i++)
    {
        watch_sprite[i].setPosition(static_cast<float>(i * 31 + x_offset),
                                    static_cast<float>(y_offset));
        window.draw(watch_sprite[i]);
    }
}