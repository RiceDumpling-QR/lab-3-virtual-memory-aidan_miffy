#include <iostream>
#include <cstdlib>
#include "../vm.h"
#include "../tlb.h"

int main() {
    vm = new VM();
    srand(123);

    unsigned long base = 0x20000;
    size_t numPages = 32;

    vm->vmMap(base, 4096 * numPages);

    std::cerr << "\n== TLB Conflict-Sensitive Random Test ==\n";

    // ******** WARMUP (allocate pages + fill TLB initially) ********
    for (size_t i = 0; i < numPages; i++) {
        unsigned long addr = base + i * 4096;
        vm->Load(addr);
    }

    // ***** Choose TWO pages that FORCE a TLB index conflict *****
    // Compute aliasing distance = 1 << (offsetBits + indexBits)
    unsigned long aliasOffset = 1UL << (VM_PPOBITS + TLB_INDEX_LEN);

    unsigned long addrA = base + 0;              // Page 0
    unsigned long addrB = base + aliasOffset;    // Aliases in TLB index!

    // ******** CONFLICT HEAVY RANDOM ACCESS ********
    for (int i = 0; i < 5000; i++) {
        // Flip between the conflicting pages
        unsigned long addr = (rand() % 2 == 0) ? addrA : addrB;
        vm->Store(addr);
    }

    std::cerr << "Accesses:    " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits:     " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults:  " << vm->getNumPgFault() << "\n";
}
