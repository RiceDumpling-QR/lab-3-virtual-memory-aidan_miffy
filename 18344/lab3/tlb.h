#pragma once

/* Your TLB should be modeled after the
 * Intel Skylake DATA TLB L1 with the following
 * parameters
*/
#define TLB_OFFSET_LEN      12
#define TLB_INDEX_LEN       6
/* Number of TLB sets must be 2^TLB_INDEX_LEN. Derive it to avoid
  mismatches when changing the index length. */
#define TLB_SET             (1UL << TLB_INDEX_LEN)
/* Use unsigned shift to avoid UB when shifting ints */
#define TLB_INDEX_MASK      ((1UL << TLB_INDEX_LEN) - 1)

class TLB
{
private:
  struct TLB_Entry{
    bool valid;
    unsigned long tag;
    unsigned long ppn;
    TLB_Entry(){
      valid = false;
      tag = 0;
      ppn = 0;
    }
  };

  TLB_Entry sets[TLB_SET];

public:
  TLB();
  bool lookup(unsigned long addr, unsigned long & PPN);
  void update(unsigned long addr, unsigned long new_PPN);

};
