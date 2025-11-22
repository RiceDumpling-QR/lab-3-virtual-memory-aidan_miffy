#pragma once

/* Your TLB should be modeled after the
 * Intel Skylake DATA TLB L1 with the following
 * parameters
*/
#define TLB_SET             64
#define TLB_OFFSET_LEN      12
#define TLB_INDEX_LEN       6
#define TLB_INDEX_MASK      0xF

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
