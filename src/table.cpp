#include "table.h"


Table::Table(const std::string& fileName, int field_w, int field_h, int field_gap) 
        : field_w(field_w), field_h(field_h), field_gap(field_gap)
{
    texture.loadFromFile(fileName);
    rollback();
}

void Table::rollback()
{
    for(int i = 0, k = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++, k++)
        {
            table[i][j].value = k;
            table[i][j].sprite.setTexture(texture);
            table[i][j].sprite.setTextureRect(sf::IntRect((field_w + field_gap)*j,
                (field_h + field_gap) * i, field_w, field_h));
        }
    }
    empty = {3,3};
}


void Table::drawTable(sf::RenderWindow & window, int x_offset, int y_offset)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            table[i][j].sprite.setPosition(
                    static_cast<float>((field_w + field_gap) * j + x_offset),
                    static_cast<float>((field_h + field_gap) * i + y_offset));
            window.draw(table[i][j].sprite);
        }
}

bool Table::moveEmpty(int row, int column)
{
    row = empty.row + row;
    column = empty.column + column;

    if(row < 4 && column < 4 && row >= 0 && column >= 0)
    {
        int val_tab = table[row][column].value, val_em = table[empty.row][empty.column].value;
        table[row][column].value = table[empty.row][empty.column].value;
        table[empty.row][empty.column].value = val_tab;


        table[row][column].sprite.setTextureRect(sf::IntRect((field_w + field_gap)*(val_em % 4),
                (field_h + field_gap) * (val_em / 4), field_w, field_h));
        table[empty.row][empty.column].sprite.setTextureRect(sf::IntRect((field_w + field_gap)*(val_tab % 4),
                (field_h + field_gap) * (val_tab / 4), field_w, field_h));
        empty = {row, column};
        return true;
    }

    return false;
}

bool Table::moveLeft()
{
    return moveEmpty(0, 1);
}
bool Table::moveRight()
{
    return moveEmpty(0, -1);
}
bool Table::moveUp()
{
    return moveEmpty(1, 0);
}
bool Table::moveDown()
{
    return moveEmpty(-1, 0);
}

void Table::shuffleFields(int n)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    while(n >= 0)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);
        bool flag = false;
        switch(static_cast<int>(dist6(rng)))
        {
            case 0:
                flag = moveLeft();
                break;
            case 1:
                flag = moveRight();
                break;
            case 2:
                flag = moveUp();
                break;
            case 3:
                flag = moveDown();
                break;
            default:
                break;
        };
        if(flag)
            n--;
    }
}

bool Table::isCorrectOrder()
{
    for(int i = 0, k = 0; i < 4; i++)
    {
        for(int j = 1; j < 4; j++, k++)
        {
            if(table[i][j].value < table[i][j - 1].value)
            {
                return false;
            }
        }
    }
    return true;

}