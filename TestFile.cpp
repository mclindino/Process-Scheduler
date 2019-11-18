#include <stdlib.h>
#include <time.h>
#include <iostream>

main()
{
    clock_t init, fim, decorrido;
    while(decorrido != 10)
    {
        decorrido = clock() / CLOCKS_PER_SEC;
        std::cout << decorrido << std::endl;
    }
}