#include "Pionek_Design.h"
#include <vector>

class Macierz
{
public:
    Macierz(int rozimar_x, int rozimar_y);

    void wrzucPionek(int pozycja_x, int pozycja_y);
    void movePionki();
    void rysuj();

private:
    void clearMacierz();

    std::vector<std::vector<Pionek_Design *>> maacierz;

    int max;
    int max_limit;
    int counter;
};
