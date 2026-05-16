/*
 * Program: i76.exe
 * Function: prepare_smacker_cutscene_display_surface
 * Entry: 0042e1d0
 * Signature: undefined4 __cdecl prepare_smacker_cutscene_display_surface(undefined4 param_1, undefined4 param_2)
 */


/* cgpt rename v8 display/d3d cluster: Prepares or restores the DirectDraw display/front-buffer
   surface state used by Smacker cutscene open/render/close paths. */

undefined4 __cdecl prepare_smacker_cutscene_display_surface(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piStack_dc;
  undefined4 local_d0 [16];
  undefined4 auStack_90 [4];
  undefined4 local_80;
  undefined4 local_6c [27];
  
  piVar1 = DAT_006080c4;
  puVar3 = local_6c;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = local_d0;
  for (iVar2 = 0x19; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_d0[0] = 100;
  local_80 = param_2;
  piStack_dc = DAT_006080c4;
  iVar2 = (**(code **)(*DAT_006080c4 + 0x60))();
  if (iVar2 != 0) {
    (**(code **)(*piVar1 + 0x6c))(piVar1);
  }
  if (DAT_005280cc == 0) {
    (**(code **)(*piVar1 + 0x14))(piVar1,0,0,0,0x1000400,&stack0xffffff2c);
    return 1;
  }
  (**(code **)(*piVar1 + 0x80))(piVar1,0);
  iVar2 = (**(code **)(*piVar1 + 0x14))(piVar1,0,0,0,0x1000400,&piStack_dc);
  if (iVar2 != 0) {
    return 0;
  }
  auStack_90[0] = 0x6c;
  iVar2 = (**(code **)(*piVar1 + 100))(piVar1,0,auStack_90,1,0);
  if (iVar2 != 0) {
    DAT_005280cc = 0;
    return 0;
  }
  return 1;
}


