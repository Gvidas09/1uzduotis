#include "Ivedimas.h"
#include "Tyrimai.h"

int main() {
    while (true) {
        int p = meniu();

        if (p == 1) {
            generuoti_visus_testinius_failus();
        }
        else if (p == 2) {
            apdoroti_viena_faila();
        }
        else if (p == 3) {
            vykdyti_visu_failu_tyrima();
        }
        else if (p == 4) {
            vykdyti_v11_tyrima();
        }
        else if (p == 5) {
            break;
        }
    }

    return 0;
}