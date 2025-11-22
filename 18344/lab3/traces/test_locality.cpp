#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    unsigned long base = 0x30000;
    vm->vmMap(base, 4096 * 4);

    std::cerr << "\n== High Locality Test ==\n";

    for (int i = 0; i < 500; i++) {
        vm->pageLoadSingle(base + ((i % 4) * 4096), 0);
    }

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
