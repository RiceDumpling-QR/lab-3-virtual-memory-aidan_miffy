#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();

    unsigned long base = 0x30000;
    vm->vmMap(base, 4096 * 8);

    std::cerr << "\n== High Locality (TLB-Sensitive) Test ==\n";

    unsigned long aliasOffset = 1UL << (VM_PPOBITS + TLB_INDEX_LEN);
    unsigned long conflictPage = base + aliasOffset;

    for (int i = 0; i < 4; i++)
        vm->pageLoadSingle(base + i * 4096, 0);

    for (int i = 0; i < 500; i++) {
        if (i % 20 == 0)
            vm->pageLoadSingle(conflictPage, 0);
        else
            vm->pageLoadSingle(base + ((i % 4) * 4096), 0);
    }

    std::cerr << "Accesses:    " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits:     " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults:  " << vm->getNumPgFault() << "\n";
}
