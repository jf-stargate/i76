/*
 * Program: i76.exe
 * Function: load_serialized_fsm_record_array_with_bitfields
 * Entry: 004105a0
 * Signature: undefined __cdecl load_serialized_fsm_record_array_with_bitfields(int * param_1, int * param_2, HANDLE param_3)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Loads a serialized FSM/AI record array with
   0x60-byte records and packed flag/bitfield payloads. */

void __cdecl
load_serialized_fsm_record_array_with_bitfields(int *param_1,int *param_2,HANDLE param_3)

{
  uint *puVar1;
  undefined4 uVar2;
  LPVOID pvVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  
  DAT_005244d4 = DAT_005244d4 + 1;
  iVar5 = *(int *)(DAT_005244d0 + -4 + DAT_005244d4 * 4);
  *param_2 = iVar5;
  pvVar3 = HeapAlloc(param_3,0,(iVar5 + 200) * 0x60);
  iVar5 = 0;
  *param_1 = (int)pvVar3;
  if (0 < *param_2) {
    iVar6 = 0;
    do {
      puVar4 = (undefined1 *)(*param_1 + iVar6);
      DAT_005244d4 = DAT_005244d4 + 1;
      iVar7 = 9;
      uVar2 = *(undefined4 *)(DAT_005244d0 + -4 + DAT_005244d4 * 4);
      *puVar4 = (char)uVar2;
      puVar4[3] = (char)((uint)uVar2 >> 0x18);
      puVar4[2] = (char)((uint)uVar2 >> 0x10);
      puVar4[1] = (char)((uint)uVar2 >> 8);
      puVar4 = puVar4 + 6;
      do {
        DAT_005244d4 = DAT_005244d4 + 1;
        uVar2 = *(undefined4 *)(DAT_005244d0 + -4 + DAT_005244d4 * 4);
        puVar4[1] = (char)((uint)uVar2 >> 0x18);
        *puVar4 = (char)((uint)uVar2 >> 0x10);
        puVar4[-1] = (char)((uint)uVar2 >> 8);
        puVar4[-2] = (char)uVar2;
        iVar7 = iVar7 + -1;
        puVar4 = puVar4 + 4;
      } while (iVar7 != 0);
      iVar7 = *param_1;
      *(undefined4 *)(iVar7 + 0x50 + iVar6) = 0;
      *(undefined4 *)(iVar7 + 0x54 + iVar6) = 0;
      DAT_005244d4 = DAT_005244d4 + 1;
      iVar7 = *param_1;
      *(undefined4 *)(iVar7 + 0x50 + iVar6) = *(undefined4 *)(DAT_005244d0 + -4 + DAT_005244d4 * 4);
      *(undefined4 *)(iVar7 + 0x54 + iVar6) = 0;
      DAT_005244d4 = DAT_005244d4 + 1;
      puVar1 = (uint *)(*param_1 + 0x50 + iVar6);
      lVar8 = __allshl(0x20,(int)(int3)((uint)*(undefined4 *)(DAT_005244d0 + -4 + DAT_005244d4 * 4)
                                       >> 8) >> 0x17);
      iVar6 = iVar6 + 0x60;
      *puVar1 = *puVar1 | (uint)lVar8;
      iVar5 = iVar5 + 1;
      puVar1[1] = puVar1[1] | (uint)((ulonglong)lVar8 >> 0x20);
    } while (iVar5 < *param_2);
  }
  return;
}


