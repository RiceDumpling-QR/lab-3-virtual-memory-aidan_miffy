#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    std::cerr << "\n== Segfault Test ==\n";

    unsigned long bad1 = 0x0;
    unsigned long bad2 = 0xABCDEF;

    vm->pageLoadSingle(bad1, 0);
    vm->pageStoreSingle(bad2, 0);

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
