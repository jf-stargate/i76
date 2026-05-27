/*
 * Program: i76.exe
 * Function: build_vehicle_descriptor_from_vcf_path
 * Entry: 004b72b0
 * Signature: undefined __cdecl build_vehicle_descriptor_from_vcf_path(char * param_1, undefined4 * param_2, undefined4 param_3)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Splits an input vehicle path,
   normalizes/appends the .vcf basename, and finalizes a shell vehicle descriptor. */

void __cdecl
build_vehicle_descriptor_from_vcf_path(char *param_1,undefined4 *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char local_160 [40];
  char local_138 [45];
  undefined4 local_10b;
  undefined4 local_107;
  undefined4 local_103;
  undefined4 local_ff;
  undefined4 local_7c;
  char local_78 [40];
  char local_50 [40];
  char local_28 [40];
  
  pcVar5 = local_138;
  for (iVar2 = 0x30; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  _splitpath(param_1,local_50,local_78,local_160,local_28);
  uVar3 = 0xffffffff;
  pcVar5 = &s_dot_vcf;
  do {
    pcVar7 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar2 = -1;
  pcVar5 = local_160;
  do {
    pcVar6 = pcVar5;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  pcVar5 = pcVar7 + -uVar3;
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
  uVar3 = 0xffffffff;
  pcVar5 = local_160;
  do {
    pcVar7 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar7 + -uVar3;
  pcVar7 = local_138;
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
  local_10b = 0;
  local_107 = 0;
  local_103 = 0;
  local_ff = 0;
  local_7c = param_3;
  copy_vehicle_descriptor_and_read_scene_chunks(local_138,param_2,param_1);
  return;
}


