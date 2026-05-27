/*
 * Program: i76.exe
 * Function: multiplayer_host_migration_context_helper_00454840
 * Entry: 00454840
 * Signature: undefined __cdecl multiplayer_host_migration_context_helper_00454840(short param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer host migration context
   helper based on prior focused closure context. */

void __cdecl multiplayer_host_migration_context_helper_00454840(short param_1)

{
  short *psVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if ((iVar2 != -1) &&
     (fVar3 = get_network_or_session_runtime_seconds(),
     (float10)(float)(&DAT_0054109c)[iVar2 * 0x12] < fVar3)) {
    (&DAT_0054109c)[iVar2 * 0x12] = (float)fVar3;
    return;
  }
  return;
}


