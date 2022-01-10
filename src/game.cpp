#include "game.h"

Game::Game(int n_shuffles) : n_shuffles(n_shuffles) 
{
    t_logo.loadFromFile("img/logo.png");
    s_logo.setTexture(t_logo);
    s_logo.setPosition(35,25);

    t_button_start.loadFromFile("img/start.png");
    s_button_start.setTexture(t_button_start);
    s_button_start.setPosition(35,518);

    t_button_reset.loadFromFile("img/reset.png");
    s_button_reset.setTexture(t_button_reset);
    s_button_reset.setPosition(210,518);

    t_timer_rect.loadFromFile("img/timer_rect.png");
    s_timer_rect.setTexture(t_timer_rect);
    s_timer_rect.setPosition(212,35);

    game_window.setKeyRepeatEnabled(false);
    game_window.setFramerateLimit(30);
}


void Game::processingGameEvent(const sf::Event & event)
{
    switch(event.key.code)
    {
        case Keyboard::Left:
            table.moveLeft();
            break;
        case Keyboard::Right:
            table.moveRight();
            break;
        case Keyboard::Up:
            table.moveUp();
            break;
        case Keyboard::Down:
            table.moveDown();
            break;
        default:
            break;
    }
    if(table.isCorrectOrder())
    {
        is_started = false;
        watch.stopWatch();
    }
}

void Game::processingMenuEvent(const sf::Event & event)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if(!is_started && sf::IntRect(32, 518, 173,42).contains(sf::Mouse::getPosition(game_window)))
        {
            is_started = true;
            table.shuffleFields(n_shuffles);
            watch.startWatch();
        }
            
        if(is_started && sf::IntRect(210, 518, 173,42).contains(sf::Mouse::getPosition(game_window)))
        {
            is_started = false;
            table.rollback();
            watch.stopWatch();
        }
    }
}

void Game::drawGame()
{
    game_window.draw(s_logo);
    game_window.draw(s_button_start);
    game_window.draw(s_button_reset);
    game_window.draw(s_timer_rect);
    watch.drawWatch(game_window, 220, 45);
    table.drawTable(game_window, 35, 144);
}

int Game::startGame()
{
    while(game_window.isOpen())
    {
        sf::Event event{};
        while(game_window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    game_window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(is_started)
                        processingGameEvent(event);
                    break;
                case sf::Event::MouseButtonPressed:
                    processingMenuEvent(event);
                    break;
                default:
                    break;
            }
        }
        
        game_window.clear(sf::Color(43, 42, 51, 255));
        drawGame();
        game_window.display();
    }
    return 0;
}