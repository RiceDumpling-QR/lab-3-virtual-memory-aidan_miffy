#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    unsigned long base = 0x40000;
    vm->vmMap(base, 4096 * 64);

    std::cerr << "\n== Page Fault Stress Test ==\n";

    for (int i = 0; i < 64; i++) {
        vm->pageStoreSingle(base + i * 4096, 0);
    }

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
