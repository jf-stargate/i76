/*
 * Program: i76.exe
 * Function: fill_resource_lookup_key_stride100
 * Entry: 004b7570
 * Signature: undefined __cdecl fill_resource_lookup_key_stride100(int param_1, int * param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium] Helper used by geometry callbacks
   to convert chunk name fields into lookup-key records.
   [cgpt i76.exe vehicle object rename v7; confidence=medium] Fills an array of lookup-key dwords by
   repeatedly adding class/stride*100 to the initial key; used by geometry/chunk lookup setup. */

void __cdecl fill_resource_lookup_key_stride100(int param_1,int *param_2,int param_3,int param_4)

{
  if (param_3 != 0) {
    do {
      *param_2 = param_1;
      param_1 = param_1 + param_4 * 100;
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}


