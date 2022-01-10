#ifndef WATCH_H
#define WATCH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>



class Watch
{
    private:
        sf::Clock watch;
        sf::Texture watch_texture[11];
        sf::Sprite watch_sprite[5];
        int current_time = 0;
        bool is_active = false;
    public:
        explicit Watch(const std::string & img_path);
        void startWatch();
        void stopWatch();
        float getCurrentTime() const;
        void drawWatch(sf::RenderWindow & window, int x_offset, int y_offset);
        
};

#endif