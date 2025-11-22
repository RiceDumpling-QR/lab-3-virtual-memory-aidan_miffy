#include "tlb.h"

TLB::TLB()
{
}

static inline unsigned long tlbIndex(unsigned long addr) {
  return (addr >> TLB_OFFSET_LEN) & TLB_INDEX_MASK;
}

static inline unsigned long tlbTag(unsigned long addr) {
  return (addr >> (TLB_OFFSET_LEN + TLB_INDEX_LEN));
}


bool TLB::lookup(unsigned long addr, unsigned long &PPN){

  /*TODO: Implement a TLB lookup here, assign the PPN ref arg
          to the PPN cached in the TLB, and return true if
          your TLB lookup is a hit
  */
  unsigned long index = tlbIndex(addr);
  unsigned long tag = tlbTag(addr);
  if(sets[index].valid && sets[index].tag == tag){
    PPN = sets[index].ppn;
    return true;
  }
  return false;

}

void TLB::update(unsigned long addr, unsigned long new_PPN){
  
  /*TODO: Implement a TLB update here using the 
          virtual address and new PPN*/
  unsigned long index = tlbIndex(addr);
  unsigned long tag = tlbTag(addr);
  
  sets[index].valid = true;
  sets[index].tag = tag;
  sets[index].ppn = new_PPN;

  return;

}
