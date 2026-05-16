/*
 * Program: i76.exe
 * Function: format_8char_resource_basename_with_suffix
 * Entry: 004ad640
 * Signature: char * __cdecl format_8char_resource_basename_with_suffix(undefined4 param_1, undefined4 param_2, char * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Formats an 8-character
   resource basename with a suffix such as .geo/.vqm/.cbk/.map. */

char * __cdecl
format_8char_resource_basename_with_suffix(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  _g_vehicle_resource_name_scratch = 0;
  _DAT_005dabb4 = 0;
  _DAT_005dabb8 = 0;
  _DAT_005dabbc = 0;
  strncpy(&g_vehicle_resource_name_scratch,(char *)&param_1,8);
  iVar2 = _stricmp(&g_vehicle_resource_name_scratch,s_null_004c3280);
  if (iVar2 == 0) {
    return (char *)0x0;
  }
  uVar3 = 0;
  do {
    uVar4 = uVar3;
    (&g_vehicle_resource_name_scratch)[uVar4] = (&g_vehicle_resource_name_scratch)[uVar4] & 0x7f;
    uVar3 = uVar4 + 1;
  } while (uVar4 + 1 < 8);
  (&DAT_005dabb1)[uVar4] = 0;
  if (g_vehicle_resource_name_scratch == '\0') {
    return (char *)0x0;
  }
  if (param_3 != (char *)0x0) {
    uVar3 = 0xffffffff;
    do {
      pcVar5 = param_3;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar5 = param_3 + 1;
      cVar1 = *param_3;
      param_3 = pcVar5;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    iVar2 = -1;
    pcVar7 = &g_vehicle_resource_name_scratch;
    do {
      pcVar6 = pcVar7;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar6 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar6;
    } while (cVar1 != '\0');
    pcVar5 = pcVar5 + -uVar3;
    pcVar7 = pcVar6 + -1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  return &g_vehicle_resource_name_scratch;
}


