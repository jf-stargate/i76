/*
 * Program: i76.exe
 * Function: world_instance_id_table_context_helper_004ad260
 * Entry: 004ad260
 * Signature: undefined __stdcall world_instance_id_table_context_helper_004ad260(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: world instance id table context helper
   based on adjacent named subsystem context. */

void world_instance_id_table_context_helper_004ad260(void)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  time_t tVar6;
  
  srand(0);
  pfVar3 = (float *)&DAT_005da7c0;
  do {
    *pfVar3 = 0.0;
    iVar5 = 10;
    do {
      iVar2 = rand();
      iVar5 = iVar5 + -1;
      fVar1 = *pfVar3 - (float)iVar2 * _DAT_004bec68;
      *pfVar3 = fVar1;
    } while (iVar5 != 0);
    pfVar4 = pfVar3 + 1;
    *pfVar3 = fVar1 * _DAT_004bec6c - _DAT_004bec70;
    pfVar3 = pfVar4;
  } while ((int)pfVar4 < 0x5dabac);
  DAT_005da7b8 = 0;
  tVar6 = time((time_t *)0x0);
  srand((uint)tVar6);
  return;
}


