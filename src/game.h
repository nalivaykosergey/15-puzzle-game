#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "table.h"
#include "watch.h"

using sf::Keyboard;
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;

class Game
{
    private:
        RenderWindow game_window{sf::VideoMode(421, 595), "15", sf::Style::Close};
        Table table{"img/field1.png", 84, 85, 5};
        Watch watch{"img/clock/"};

        Texture t_logo;
        Texture t_button_reset;
        Texture t_button_start;
        Texture t_timer_rect;

        Sprite s_logo;
        Sprite s_button_reset;
        Sprite s_button_start;
        Sprite s_timer_rect;

        int n_shuffles;
        bool is_started = false;

    public:
        explicit Game(int n_shuffles = 10);
        void processingGameEvent(const sf::Event & event);
        void processingMenuEvent(const sf::Event & event);
        void drawGame();
        int startGame();

};

#endif