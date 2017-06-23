#include "Macierz.hpp"
#include "EmptyField.h"
#include "Pionek.h"

#include "iostream"
#include "ncurses.h"

Macierz::Macierz(int size_x, int size_y) : max(size_x*size_y), max_limit((0.5) * max), counter(0)
{
    for(auto i = 0 ; i < size_x; i ++)
    {
        maacierz.push_back({});
        for( auto j = 0; j < size_y; j++)
        {
            maacierz.at(i).push_back( new EmptyField());
        }
    }
}

void Macierz::wrzucPionek(int position_x, int position_Y)
{
    if(counter> max_limit)
    {
        counter= 0;
        clearMacierz();
    }
    auto pole =  maacierz.at(position_x).at(position_Y);
    delete pole;
    maacierz.at(position_x).at(position_Y) =  new Pionek();
    counter++;
}

void Macierz::clearMacierz()
{
    for( auto i = 0 ; i < maacierz.size(); i++)
    {
        for(auto j= 0; j < maacierz.at(maacierz.size() - 1).size(); j++)
        {
            auto pole = maacierz.at(i).at(j);
            delete pole;

            maacierz.at(i).at(j) = new EmptyField();
        }
    }
}

void Macierz::movePionki()
{
    Pionek_Design * removePionek = maacierz.at(maacierz.size() - 1).at(maacierz.at(0).size() - 1);
    delete removePionek;

    for(auto i = 0 ; i < maacierz.size(); i ++)
    {
        for(auto j = 0; j < maacierz.at(maacierz.size() - 1).size(); j++)
        {
            int pozycja_x = maacierz.size() - 1 - i;
            int pozycja_y = maacierz.at(pozycja_x).size() - 1 -j;

            if(!((pozycja_y == 0) && (pozycja_x == 0)))
            {

                if(pozycja_y == 0)
                {
                    maacierz.at(pozycja_x).at(pozycja_y) = maacierz.at(pozycja_x - 1).at(maacierz.at(pozycja_x).size() - 1);
                }
                else
                {
                    maacierz.at(pozycja_x).at(pozycja_y) = maacierz.at(pozycja_x).at(pozycja_y - 1);
               }
            }
            else
            {
                maacierz.at(0).at(0) = new EmptyField();
            }

        }
    }
}

void Macierz::rysuj()
{
    clear();

    for(const auto & wiersz : maacierz)
    {
        for(const auto & komorka : wiersz)
        {
            komorka->rysuj();
        }

        printw("\n");
    }
}

