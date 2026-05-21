/*
 * Program: i76.exe
 * Function: world_object_texture_binding_apply_helper_0046e2e0
 * Entry: 0046e2e0
 * Signature: undefined __cdecl world_object_texture_binding_apply_helper_0046e2e0(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object texture binding apply
   helper based on adjacent named subsystem context. */

void __cdecl world_object_texture_binding_apply_helper_0046e2e0(int param_1,int param_2)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  
  if (param_2 == 1) {
    uVar3 = *(uint *)(*(int *)(param_1 + 0x70) + 0x400);
  }
  else {
    uVar3 = *(uint *)(*(int *)(param_1 + 0x70) + 0x404);
  }
  if ((((uVar3 != 0) && ((*(int **)(uVar3 + 0x70))[1] != 0)) &&
      (piVar1 = (int *)**(int **)(uVar3 + 0x70), piVar1 != (int *)0x0)) && (*piVar1 == 0)) {
    piVar1[2] = 5;
    pbVar2 = (byte *)find_object_texture_slot_name(uVar3,0);
    piVar1[4] = 0;
    piVar1[3] = 0;
    set_texture_binding_frame_and_reload(uVar3,pbVar2,1,0,0);
  }
  return;
}


