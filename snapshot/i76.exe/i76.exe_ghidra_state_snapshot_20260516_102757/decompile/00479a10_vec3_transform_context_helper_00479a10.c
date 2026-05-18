/*
 * Program: i76.exe
 * Function: vec3_transform_context_helper_00479a10
 * Entry: 00479a10
 * Signature: undefined __stdcall vec3_transform_context_helper_00479a10(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: vec3 transform context helper based on
   adjacent named subsystem context. */

void vec3_transform_context_helper_00479a10(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 local_300;
  undefined1 local_2ff [767];
  
  _DAT_0059bb8c = 1;
  puVar1 = local_2ff;
  iVar2 = 0x100;
  do {
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 3;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  (*DAT_005dd2c8)(&DAT_005dcec0,&local_300);
  return;
}


