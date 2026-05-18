/*
 * Program: i76.exe
 * Function: graphics_buffer_memory_error_context_helper_00474b90
 * Entry: 00474b90
 * Signature: undefined __cdecl graphics_buffer_memory_error_context_helper_00474b90(undefined4 * param_1, int * param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: graphics buffer memory error context
   helper based on adjacent named subsystem context. */

void __cdecl graphics_buffer_memory_error_context_helper_00474b90(undefined4 *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 uVar5;
  
  uVar5 = (undefined1)*param_1;
  draw_clipped_line_to_bitmap_surface
            (param_2,param_1[0x10],param_1[0x11],param_1[0x12],param_1[0x13],uVar5,0);
  iVar1 = param_1[0x12];
  iVar2 = param_1[0x13];
  iVar3 = param_1[0x10];
  iVar4 = param_1[0x11];
  if (iVar2 - iVar4 < iVar1 - iVar3) {
    draw_clipped_line_to_bitmap_surface(param_2,iVar3,iVar4 + 1,iVar1,iVar2 + 1,uVar5,0);
    return;
  }
  draw_clipped_line_to_bitmap_surface(param_2,iVar3 + 1,iVar4,iVar1 + 1,iVar2,uVar5,0);
  return;
}


