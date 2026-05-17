/*
 * Program: i76.exe
 * Function: multiplayer_join_prompt_context_helper_004558c0
 * Entry: 004558c0
 * Signature: uint __cdecl multiplayer_join_prompt_context_helper_004558c0(short param_1, int param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer join prompt context helper
   based on prior focused closure context. */

uint __cdecl multiplayer_join_prompt_context_helper_004558c0(short param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  bool bVar4;
  float10 fVar5;
  
  uVar1 = DAT_00541520;
  uVar2 = DAT_00541520;
  do {
    if (uVar2 == DAT_005419b4) {
      puVar3 = (undefined4 *)0x0;
      goto LAB_00455903;
    }
    uVar2 = uVar2 + 1 & 0x3f;
  } while ((*(short *)(&DAT_00541528 + uVar2 * 3) != param_1) ||
          ((&DAT_0054152c)[uVar2 * 3] != param_2));
  puVar3 = &DAT_00541528 + uVar2 * 3;
LAB_00455903:
  if (puVar3 != (undefined4 *)0x0) {
    return puVar3[2] & 7;
  }
  uVar2 = DAT_005419b4 + 1 & 0x3f;
  bVar4 = DAT_00541520 == uVar2;
  DAT_005419b4 = uVar2;
  *(short *)(&DAT_00541528 + uVar2 * 3) = param_1;
  (&DAT_0054152c)[uVar2 * 3] = param_2;
  *(undefined4 *)(&DAT_00541530 + uVar2 * 0xc) = 0;
  if (bVar4) {
    DAT_00541520 = uVar1 + 1 & 0x3f;
  }
  uVar2 = DAT_00541828 + 1 & 0x3f;
  if (uVar2 != DAT_005419b0) {
    DAT_00541828 = uVar2;
    *(short *)(&DAT_00541830 + uVar2 * 3) = param_1;
    (&DAT_00541834)[uVar2 * 3] = param_2;
    fVar5 = get_multiplayer_or_runtime_seconds();
    *(float *)(&DAT_00541838 + DAT_00541828 * 0xc) = (float)fVar5;
  }
  return 0;
}


