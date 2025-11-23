#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    std::cerr << "\n== Segfault Test ==\n";

    // Access illegal low addresses
    vm->pageLoadSingle(0x0, 0);
    vm->pageLoadSingle(0x10, 0);
    vm->pageStoreSingle(0x500, 0);

    // Access unallocated high virtual region
    vm->pageStoreSingle(0xABCDEF, 0);

    std::cerr << "\nAccesses:    " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits:     " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults:  " << vm->getNumPgFault() << "\n";
}
