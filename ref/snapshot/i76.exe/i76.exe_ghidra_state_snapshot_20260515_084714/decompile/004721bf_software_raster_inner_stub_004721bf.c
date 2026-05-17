/*
 * Program: i76.exe
 * Function: software_raster_inner_stub_004721bf
 * Entry: 004721bf
 * Signature: undefined4 __stdcall software_raster_inner_stub_004721bf(void)
 */


/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */
/* cgpt readability rename set C v15: Readability pass set C: software raster inner stub based on
   adjacent named subsystem context. */

undefined4 software_raster_inner_stub_004721bf(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  undefined2 in_FPUControlWord;
  
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + -4) = 0x4721c7;
  zone_satellite_map_context_helper_00493c40();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(undefined2 *)(unaff_EBP + -0x340) = in_FPUControlWord;
  uVar1 = *(undefined4 *)(unaff_EBP + -0x340);
  *(uint *)(unaff_EBP + -0x340) =
       *(uint *)(unaff_EBP + -0x31c) & 0xc00 | *(uint *)(unaff_EBP + -0x340) & 0xfffff3ff;
  ExceptionList = *(void **)(unaff_EBP + -0x10);
  return uVar1;
}


