#include <iostream>
#include "../vm.h"

int main() {
    vm = new VM();
    unsigned long base = 0x10000;

    vm->vmMap(base, 4096 * 64); // Map 64 pages

    std::cerr << "\n== TLB Set-Collision Stress Test ==\n";

    const unsigned long p0 = 0;      // page 0
    const unsigned long p1 = 32;     // page 32 -> collides with p0 when sets=32
    const int warmups = 2;
    const int repeats = 2000;

    // Warm up so pages are mapped/loaded once
    for (int i = 0; i < warmups; ++i) {
        vm->Load(base + p0 * 4096);
        vm->Load(base + p1 * 4096);
    }

    // Alternating accesses that will thrash if TLB has only 32 sets
    for (int i = 0; i < repeats; ++i) {
        vm->Load(base + p0 * 4096);
        vm->Load(base + p1 * 4096);
    }

    std::cerr << "Accesses: " << vm->getNumAcc() << "\n";
    std::cerr << "TLBHits: " << vm->getNumTlbHit() << "\n";
    std::cerr << "PageFaults: " << vm->getNumPgFault() << "\n";
}
