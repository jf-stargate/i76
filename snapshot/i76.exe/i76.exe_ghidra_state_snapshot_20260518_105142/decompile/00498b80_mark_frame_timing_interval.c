/*
 * Program: i76.exe
 * Function: mark_frame_timing_interval
 * Entry: 00498b80
 * Signature: undefined __cdecl mark_frame_timing_interval(char * param_1)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Records a named frame timing interval
   for profiling/log output. */

void __cdecl mark_frame_timing_interval(char *param_1)

{
  char cVar1;
  DWORD DVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (DAT_005a7c90 != 0) {
    DVar2 = timeGetTime();
    if (DAT_005a6c38 + DAT_005a7c5c == 0) {
      uVar3 = 0xffffffff;
      do {
        pcVar6 = param_1;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar6 = param_1 + 1;
        cVar1 = *param_1;
        param_1 = pcVar6;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar6 = pcVar6 + -uVar3;
      pcVar7 = &DAT_005a6178 + DAT_005a6c3c * 0x50;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      }
    }
    iVar5 = DVar2 - DAT_005a7c88;
    DAT_005a7c88 = DVar2;
    (&DAT_005a6c40)[DAT_005a6c3c] = iVar5;
    DAT_005a6c3c = DAT_005a6c3c + 1;
  }
  return;
}


