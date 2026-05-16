/*
 * Program: i76.exe
 * Function: init_directsound
 * Entry: 00425c10
 * Signature: undefined4 __cdecl init_directsound(undefined4 param_1, int * param_2, undefined4 * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_00425c10
   suggested_name: init_directsound
   basis: Initializes COM/DirectSound; calls CoInitialize and DirectSoundCreate. */

undefined4 __cdecl init_directsound(undefined4 param_1,int *param_2,undefined4 *param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puStack_9c;
  int *piStack_98;
  undefined4 local_74;
  undefined4 local_70 [16];
  int iStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_8;
  
  if (param_2 == (int *)0x0) {
    return 0;
  }
  piVar3 = param_2;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  if (*param_2 == 0) {
    piStack_98 = (int *)0x425c48;
    CoInitialize((LPVOID)0x0);
    piStack_98 = param_2;
    puStack_9c = (undefined4 *)0x0;
    DAT_0052467c = 0;
    iVar2 = DirectSoundCreate();
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code **)(*(int *)*param_2 + 0x18))((int *)*param_2,uStack_8,3);
    if (iVar2 != 0) {
      if ((int *)*param_2 == (int *)0x0) {
        return 0;
      }
      piStack_98 = (int *)0x425c82;
      (**(code **)(*(int *)*param_2 + 8))();
      *param_2 = 0;
      piStack_98 = (int *)0x425c8e;
      CoUninitialize();
      return 0;
    }
  }
  piVar3 = param_2 + 1;
  *param_3 = 1;
  local_70[1] = 0;
  local_70[2] = 0;
  puStack_9c = &local_74;
  local_70[3] = 0;
  local_74 = 0x14;
  local_70[0] = 0x11;
  piStack_98 = piVar3;
  iVar2 = (**(code **)(*(int *)*param_2 + 0xc))((int *)*param_2);
  if (iVar2 == 0) {
    puVar4 = local_70;
    for (iVar2 = 0x18; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_70[0] = 0x60;
    (**(code **)(*(int *)*param_2 + 0x10))((int *)*param_2,local_70);
    DAT_005fcbfc = iStack_30;
    if (iStack_30 == 0) {
      DAT_005fcbfc = 1000000;
    }
    _DAT_005fcbf8 = uStack_2c;
    piVar1 = (int *)*piVar3;
    if (piVar1 != (int *)0x0) {
      piStack_98 = (int *)0x2b11;
      puStack_9c = (undefined4 *)0x20001;
      iVar2 = (**(code **)(*piVar1 + 0x38))(piVar1,&puStack_9c);
      if (iVar2 != 0) {
        report_chunk_parse_error();
        (**(code **)(*(int *)*piVar3 + 8))((int *)*piVar3);
        *piVar3 = 0;
        return 1;
      }
    }
    iVar2 = (*(code *)**(undefined4 **)*piVar3)((undefined4 *)*piVar3,&DAT_004bcf38,param_2 + 2);
    if (iVar2 == 0) {
      return 1;
    }
    (**(code **)(*(int *)*piVar3 + 8))((int *)*piVar3);
    *piVar3 = 0;
  }
  report_chunk_parse_error();
  return 1;
}


