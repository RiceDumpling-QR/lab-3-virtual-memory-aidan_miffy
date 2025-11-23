#include <iostream>
#include "../vm.h"
#include "../tlb.h"

int main() {
    vm = new VM();

    unsigned long base = 0x10000;
vm->vmMap(base, 4096 * 32); // 32 pages

std::cerr << "\n== TLB Conflict Test ==\n";

for (int t = 0; t < 1000; t++) {
    vm->pageLoadSingle(base + 0x0000, 0); // VPN 0
    vm->pageLoadSingle(base + (1UL << (12 + TLB_INDEX_LEN)), 0); // VPN that aliases in TLB
}

std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";

}
