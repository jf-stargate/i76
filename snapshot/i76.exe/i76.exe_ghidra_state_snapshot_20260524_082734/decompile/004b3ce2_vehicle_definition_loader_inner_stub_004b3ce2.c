/*
 * Program: i76.exe
 * Function: vehicle_definition_loader_inner_stub_004b3ce2
 * Entry: 004b3ce2
 * Signature: undefined4 __fastcall vehicle_definition_loader_inner_stub_004b3ce2(int param_1, int param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle definition loader inner stub
   based on adjacent named subsystem context. */

undefined4 __fastcall vehicle_definition_loader_inner_stub_004b3ce2(int param_1,int param_2)

{
  int *in_EAX;
  
  (&DAT_005db190)[param_1 * 0x3f] = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(&DAT_005db194 + *in_EAX * 0xfc) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(&DAT_005db1d4 + *in_EAX * 0xfc) = *(undefined4 *)(param_2 + 0x20);
  *in_EAX = *in_EAX + 1;
  return 1;
}


