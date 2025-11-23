#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    unsigned long base = 0x40000;

    std::cerr << "\n== Page-Fault Stress Test ==\n";

    // Map 4 pages at a time to force replacement after each cluster
    for (int pass = 0; pass < 10; pass++) {
        unsigned long region = base + pass * 4096 * 4;
        vm->vmMap(region, 4096 * 4);

        for (int i = 0; i < 4; i++)
            vm->pageStoreSingle(region + i * 4096, 0);
    }

    std::cerr << "Accesses:    " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits:     " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults:  " << vm->getNumPgFault() << "\n";
}
