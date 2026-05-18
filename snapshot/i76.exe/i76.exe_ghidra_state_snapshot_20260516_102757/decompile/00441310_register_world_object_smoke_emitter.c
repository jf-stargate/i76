/*
 * Program: i76.exe
 * Function: register_world_object_smoke_emitter
 * Entry: 00441310
 * Signature: undefined __cdecl register_world_object_smoke_emitter(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Allocates/registers a
   world-object-attached smoke/effect emitter and increments the attached object tree refcount. */

void __cdecl
register_world_object_smoke_emitter
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (((DAT_0052ba34 != 0) && (param_1 != 0)) &&
     (increment_refcount_recursive_for_object_tree(param_1,&DAT_004f1b84), puVar3 = DAT_0052b958,
     DAT_0052b958 != (undefined4 *)0x0)) {
    puVar1 = DAT_0052b958 + 4;
    puVar2 = DAT_0052b958 + 3;
    DAT_0052b958 = (undefined4 *)DAT_0052b958[7];
    *puVar2 = param_2;
    *puVar1 = param_3;
    puVar3[2] = param_1;
    puVar3[5] = param_4;
    puVar3[6] = param_5;
    puVar3[1] = 2;
    *puVar3 = 0;
    puVar3[8] = 0;
    puVar3[7] = DAT_0052ba24;
    if (DAT_0052ba24 == (undefined4 *)0x0) {
      DAT_0052b950 = puVar3;
      DAT_0052ba24 = puVar3;
      return;
    }
    DAT_0052ba24[8] = puVar3;
    DAT_0052ba24 = puVar3;
  }
  return;
}


