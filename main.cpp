#include <iostream>

#include "funciones.h"

int main() {
    int opc;
    do {
        opc = menu();
        options(opc);
    } while (opc != 0);

    return 0;
}
