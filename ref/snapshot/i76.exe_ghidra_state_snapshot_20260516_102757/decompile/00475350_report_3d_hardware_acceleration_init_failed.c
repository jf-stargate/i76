/*
 * Program: i76.exe
 * Function: report_3d_hardware_acceleration_init_failed
 * Entry: 00475350
 * Signature: undefined4 __stdcall report_3d_hardware_acceleration_init_failed(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence failed to initialize 3D hardware
   acceleration */

undefined4 report_3d_hardware_acceleration_init_failed(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  uVar1 = *(uint *)(param_1 + 0xc);
  if (((uVar1 < 0x401) && (uVar2 = *(uint *)(param_1 + 8), uVar2 < 0x301)) &&
     (*(int *)(param_1 + 0x54) == 8)) {
    iVar4 = 0;
    puVar3 = &DAT_004f9e1c;
    while (((((*(uint *)(param_1 + 0x4c) & 0x20) == 0 ||
             ((*(uint *)(param_1 + 0x68) & 0x200000) != 0)) ||
            ((uVar1 != puVar3[-2] || ((uVar1 != *puVar3 || (uVar2 != puVar3[-1])))))) ||
           (uVar2 != puVar3[1]))) {
      puVar3 = puVar3 + 7;
      iVar4 = iVar4 + 1;
      if (0x4f9f33 < (int)puVar3) {
        return 1;
      }
    }
    (&DAT_004f9e08)[iVar4 * 7] = 1;
  }
  return 1;
}


