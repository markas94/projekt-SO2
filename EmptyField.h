#include <ncurses.h>

struct EmptyField : Pionek_Design
{
    void rysuj() const override
    {
        printw("O");
        refresh();
    }
};


