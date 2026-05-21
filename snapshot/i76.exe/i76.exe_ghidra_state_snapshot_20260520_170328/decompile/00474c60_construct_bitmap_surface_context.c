/*
 * Program: i76.exe
 * Function: construct_bitmap_surface_context
 * Entry: 00474c60
 * Signature: undefined __cdecl construct_bitmap_surface_context(int * param_1, int param_2, uint param_3, int param_4, int param_5)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Constructs bitmap/surface
   context backing texture image resources. */

void __cdecl
construct_bitmap_surface_context(int *param_1,int param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int local_34 [4];
  uint local_24;
  uint local_20;
  LPVOID local_1c;
  int local_10;
  int local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  piVar3 = local_34;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  uVar2 = param_3 * param_2;
  if (param_5 == 1) {
    uVar2 = uVar2 * 2;
  }
  if (0 < (int)uVar2) {
    if (param_4 == 0) {
      local_1c = HeapAlloc(DAT_0058dac8,0,uVar2 + 0x20);
      if (local_1c == (LPVOID)0x0) goto LAB_00474d23;
      local_20 = (int)local_1c + 0x1fU & 0xffffffe0;
    }
    else {
      local_20 = param_4;
      local_1c = (LPVOID)0x0;
      local_4 = 1;
    }
    local_34[0] = param_2;
    local_24 = uVar2 & 0x1f;
    local_34[2] = param_5;
    local_8 = 1;
    local_34[3] = (int)uVar2 >> 2;
    local_34[1] = (local_34[1] ^ (local_34[1] ^ param_3) & 0x1fffffff) & 0x3fffffff | 0x20000000;
    local_10 = param_2 + -1;
    local_c = param_3 - 1;
  }
LAB_00474d23:
  piVar3 = local_34;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *piVar3;
    piVar3 = piVar3 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


