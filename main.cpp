#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <thread>
#include <mutex>

#include "Macierz.hpp"
#include <ncurses.h>

Macierz * macierz_main;
std::queue<int> queue_X;
std::queue<int> queue_Y;
std::mutex mx;

void producent(const int size_x, const int size_y)
{
    while(true)
    {
        std::lock_guard<std::mutex> lock(mx);
        auto selected_x =  std::rand() % size_x;
        auto selected_y = std::rand() % size_y ;

        queue_X.push( selected_x );
        queue_Y.push( selected_y );
    }
}

void przetwarzacz()
{
    while(true)
    {
        std::this_thread::sleep_for( std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx);

        if ((!queue_X.empty()) && (!queue_Y.empty()))
        {
            macierz_main->wrzucPionek(queue_X.front(), queue_Y.front());
            queue_X.pop();
            queue_Y.pop();
        }
        macierz_main->movePionki();
    }
}

void odswiez()
{
    initscr();
    start_color();

    while(true)
    {
        std::this_thread::sleep_for( std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx);
        macierz_main->rysuj();
    }

    endwin();
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Dane wejsciowe niepoprawne" << std::endl;
        return 0;
    }

    const int size_x  = std::stoi(argv[1]);
    const int size_y  = std::stoi(argv[2]);
	macierz_main = new Macierz(size_x, size_y);

    srand( time(NULL));

    std::vector<std::thread> threads;

    threads.push_back(std::thread(producent, size_x, size_y) );
    threads.push_back(std::thread(przetwarzacz) );
    threads.push_back(std::thread(odswiez) );

    for(auto & thread : threads )
    {
        thread.join();
    }

    return 0;
}
