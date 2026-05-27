/*
 * Program: i76.exe
 * Function: spawn_vehicle_damage_chunk_pair
 * Entry: 0046b710
 * Signature: undefined __cdecl spawn_vehicle_damage_chunk_pair(float * param_1, float * param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Helper under vehicle destruction
   path referencing CHUNK1/CHUNK2/K1/K2. */

void __cdecl spawn_vehicle_damage_chunk_pair(float *param_1,float *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  iVar3 = 8;
  do {
    uVar1 = rand();
    uVar2 = (int)uVar1 >> 0x1f;
    if (((uVar1 ^ uVar2) - uVar2 & 1 ^ uVar2) == uVar2) {
      fVar6 = param_1[2];
      fVar5 = param_1[1];
      fVar4 = *param_1;
      uVar1 = DAT_004f7d24;
      uVar2 = DAT_004f7d28;
    }
    else {
      fVar6 = param_1[2];
      fVar5 = param_1[1];
      fVar4 = *param_1;
      uVar1 = DAT_004f7d2c;
      uVar2 = DAT_004f7d30;
    }
    destroy_chunk_manager_objects(uVar1,uVar2,fVar4,fVar5,fVar6,param_2,15.0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


