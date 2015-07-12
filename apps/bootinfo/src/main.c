/*
 * Copyright 2015, Wink Saville
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 */

#include <sel4/sel4.h>
#include <sel4/printf.h>
#include <sel4/bootinfo.h>

void println_SlotRegionEOL(seL4_SlotRegion *sr, seL4_Bool eol) {
  seL4_Printf("{start:%d end:%d}", sr->start, sr->end);
  if (eol) seL4_Printf("\n");
}

void println_SlotRegion(seL4_SlotRegion *sr) {
  println_SlotRegionEOL(sr, seL4_True);
}

void println_DeviceRegion(seL4_DeviceRegion *dr) {
  seL4_Printf("{basePaddr:0x%x frameSizeBits:0x%x frames:",
     dr->basePaddr, dr->frameSizeBits);
  println_SlotRegionEOL(&dr->frames, seL4_False);
  seL4_Printf("}\n");
}

/**
 * No parameters are passed to main, the return
 * value is ignored and the program hangs.
 */
int main(void) {
  seL4_BootInfo *bi = seL4_GetBootInfo();
  seL4_Printf("bi=%p\n", bi);
  seL4_Printf("bi->nodeId=%d\n", bi->nodeID);
  seL4_Printf("bi->numNodes=%d\n", bi->numNodes);
  seL4_Printf("bi->numIOPTLevels=%d\n", bi->numIOPTLevels);
  seL4_Printf("bi->ipcBuffer=%p\n", bi->ipcBuffer);
  seL4_Printf("bi->empty=%p ", &bi->empty);
  println_SlotRegion(&bi->empty);
  seL4_Printf("bi->sharedFrames=%p ", &bi->sharedFrames);
  println_SlotRegion(&bi->sharedFrames);
  seL4_Printf("bi->userImageFrames=%p ", &bi->userImageFrames);
  println_SlotRegion(&bi->userImageFrames);
  seL4_Printf("bi->userImagePDs=%p ", &bi->userImagePDs);
  println_SlotRegion(&bi->userImagePDs);
  seL4_Printf("bi->userImagePTs=%p ", &bi->userImagePTs);
  println_SlotRegion(&bi->userImagePTs);
  seL4_Printf("bi->untyped=%p ", &bi->untyped);
  println_SlotRegion(&bi->untyped);
  seL4_Printf("bi->untypedPaddrList=%p\n", bi->untypedPaddrList);
  for(int i=0; i < CONFIG_MAX_NUM_BOOTINFO_UNTYPED_CAPS; i++) {
    seL4_Printf("bi->untypedPaddrList[%d] 0x%x\n", i, bi->untypedPaddrList[i]);
  }
  seL4_Printf("bi->untypedSizeBitsList=%p\n", bi->untypedSizeBitsList);
  for(int i=0; i < CONFIG_MAX_NUM_BOOTINFO_UNTYPED_CAPS; i++) {
    seL4_Printf("bi->untypedSizeBitsList[%d] 0x%x\n", i, bi->untypedSizeBitsList[i]);
  }
  seL4_Printf("bi->initThreadCNodeSizeBits=%d\n", bi->initThreadCNodeSizeBits);
  seL4_Printf("bi->numDeviceRegions=%d\n", bi->numDeviceRegions);
  for(int i=0; i < CONFIG_MAX_NUM_BOOTINFO_DEVICE_REGIONS; i++) {
    seL4_Printf("bi->deviceRegions[%d] ", i); println_DeviceRegion(&bi->deviceRegions[i]);
  }
  seL4_Printf("bi->initThreadDomain=%d\n", bi->initThreadDomain);

  seL4_Printf("Bootinfo app done.\n");

  return 0;
}
