/*
 * Program: i76.exe
 * Function: hash_texture_set_name_mod_0x7ed
 * Entry: 0044adf0
 * Signature: uint __cdecl hash_texture_set_name_mod_0x7ed(byte * param_1)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Case-insensitive texture-set
   name hash helper using multiplier 0x6cd/addend 0xaab modulo 0x7ed. */

uint __cdecl hash_texture_set_name_mod_0x7ed(byte *param_1)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = 0;
  bVar2 = *param_1;
  while (bVar2 != 0) {
    uVar3 = uVar3 * 2 ^ bVar2 & 0xdf;
    pbVar1 = param_1 + 1;
    param_1 = param_1 + 1;
    bVar2 = *pbVar1;
  }
  return (uVar3 * 0x6cd + 0xaab) % 0x7ed;
}


