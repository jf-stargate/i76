/*
 * Program: i76shell.dll
 * Function: build_vehicle_hardpoint_slot_labels
 * Entry: 10006280
 * Signature: undefined __stdcall build_vehicle_hardpoint_slot_labels(void)
 */


void build_vehicle_hardpoint_slot_labels(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 local_c0 [16];
  undefined4 local_80 [15];
  undefined4 auStack_44 [17];
  
  iVar5 = 0;
  DAT_10051f70 = 0;
  DAT_10051fac = 0;
  DAT_10051f6c = 0;
  DAT_10051e64 = 0;
  iVar1 = *(int *)(DAT_100c5ad8 + 0x38);
  if (0 < *(int *)(&DAT_10058a04 + iVar1 * 0x8c4)) {
    do {
      iVar1 = (iVar1 * 0xbb + iVar5) * 0xc;
      switch(*(undefined4 *)(&DAT_10058a10 + iVar1)) {
      case 1:
      case 3:
        wsprintfA(&DAT_10051e70 + DAT_10051fac * 0x10,s___d__s_10043a40,DAT_10051fac + 1,
                  PTR_DAT_10043384);
        local_c0[DAT_10051fac] =
             *(undefined4 *)(&DAT_10058a08 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0xbb) * 0xc);
        DAT_10051fac = DAT_10051fac + 1;
        break;
      case 2:
      case 5:
        if (*(int *)(&DAT_10058a0c + iVar1) == 1) {
          wsprintfA(&DAT_10051f78 + DAT_10051f70 * 0x10,s___d__s_10043a50,DAT_10051f70 + 1,
                    PTR_DAT_10043380);
          local_80[DAT_10051f70] =
               *(undefined4 *)(&DAT_10058a08 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0xbb) * 0xc)
          ;
          DAT_10051f70 = DAT_10051f70 + 1;
        }
        else if (*(int *)(&DAT_10058a0c + iVar1) == 2) {
          wsprintfA(&DAT_10051cb0 + DAT_10051f6c * 0x10,s___d__s_10043a58,DAT_10051f6c + 1,
                    PTR_DAT_10043388);
          DAT_10051f6c = DAT_10051f6c + 1;
          auStack_44[DAT_10051f6c] =
               *(undefined4 *)(&DAT_10058a08 + (iVar5 + *(int *)(DAT_100c5ad8 + 0x38) * 0xbb) * 0xc)
          ;
        }
        break;
      case 4:
        wsprintfA(&DAT_10051e20 + DAT_10051e64 * 0x10,s___d__s_10043a48,DAT_10051e64 + 1,
                  PTR_s_Dropper_1004338c);
        DAT_10051e64 = DAT_10051e64 + 1;
      }
      iVar5 = iVar5 + 1;
      iVar1 = *(int *)(DAT_100c5ad8 + 0x38);
    } while (iVar5 < *(int *)(&DAT_10058a04 + iVar1 * 0x8c4));
  }
  iVar4 = DAT_10051fac;
  iVar5 = DAT_10051f70;
  iVar1 = DAT_10051f6c;
  iVar2 = 0;
  if (0 < DAT_10051f70) {
    puVar6 = local_80;
    puVar7 = &DAT_10052018;
    for (iVar3 = DAT_10051f70; iVar2 = iVar5, iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  if (0 < iVar4) {
    puVar6 = &DAT_10052018 + iVar2;
    iVar2 = iVar2 + iVar4;
    puVar7 = local_c0;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  if (0 < iVar1) {
    puVar6 = auStack_44;
    puVar7 = &DAT_10052018 + iVar2;
    for (; puVar6 = puVar6 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar7 = *puVar6;
      puVar7 = puVar7 + 1;
    }
  }
  return;
}


