#include <iostream>
#include <cstdlib>
#include "../vm.h"

int main() {
    vm = new VM();
    srand(123);

    unsigned long base = 0x20000;
    vm->vmMap(base, 4096 * 32);

    std::cerr << "\n== Random Access Test ==\n";

    for (int i = 0; i < 300; i++) {
        unsigned long offset = (rand() % (4096 * 32)) & ~0xF;
        vm->pageStoreSingle(base + offset, 0);
    }

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
