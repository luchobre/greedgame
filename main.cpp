#include <iostream>

#include "funciones.h"

int main() {
    int opc;
    do {
        opc = menu();
        options(opc);
    } while (opc != 5);

    return 0;
}
