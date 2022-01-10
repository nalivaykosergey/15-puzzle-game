#ifndef TABLE_H
#define TABLE_H

#include <SFML/Graphics.hpp>
#include <random>
#include <string>
#include <iostream>


class Table 
{
    private:
        struct Field
        {
            int value{};
            sf::Sprite sprite;
        };
        Field table[4][4];
        struct
        {
            int row;
            int column;
        } empty{};
        sf::Texture texture;
        int field_w{};
        int field_h{};
        int field_gap{};
        bool moveEmpty(int row, int column);
    public:
        Table() = default;
        Table(const std::string& fileName, int field_w, int field_h, int gap);
        void rollback();
        void drawTable(sf::RenderWindow & window, int x_offset, int y_offset);

        bool moveRight();
        bool moveLeft();
        bool moveUp();
        bool moveDown();
        void shuffleFields(int n = 30);
        bool isCorrectOrder();

};

#endif