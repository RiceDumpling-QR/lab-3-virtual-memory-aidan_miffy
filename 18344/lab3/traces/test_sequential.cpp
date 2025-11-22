#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    unsigned long base = 0x10000;
    vm->vmMap(base, 4096 * 8); // 8 pages

    std::cerr << "\n== Sequential Access Test ==\n";

    for (unsigned long i = 0; i < 8 * 4096; i += 16) {
        vm->pageLoadSingle(base + i, 0);
    }

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
