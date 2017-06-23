#include <ncurses.h>

struct Pionek : Pionek_Design
{
    void rysuj() const override
    {
        init_pair( 2, COLOR_BLUE, COLOR_WHITE );
        attron( COLOR_PAIR( 2 ) );
        attron( A_BOLD );

        printw("I");

        attroff( A_BOLD);
        attroff( COLOR_PAIR( 2 ) );
        refresh();
    }
};
