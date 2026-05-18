/*
 * Program: i76.exe
 * Function: load_predefined_localized_m16_texture_set
 * Entry: 00401510
 * Signature: undefined __stdcall load_predefined_localized_m16_texture_set(void)
 */


/* cgpt rename v3: Iterates a predefined table and loads localized M16 texture resources, then
   resets related render counters. */

void load_predefined_localized_m16_texture_set(void)

{
  int *piVar1;
  
  piVar1 = (int *)&DAT_00504850;
  do {
    load_localized_m16_texture_resource(piVar1,(char *)(piVar1 + -4));
    piVar1 = piVar1 + 6;
  } while ((int)piVar1 < 0x5049d0);
  DAT_00503034 = 0;
  DAT_00504838 = 0;
  return;
}


