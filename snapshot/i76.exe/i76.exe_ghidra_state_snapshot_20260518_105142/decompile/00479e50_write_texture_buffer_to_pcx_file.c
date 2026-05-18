/*
 * Program: i76.exe
 * Function: write_texture_buffer_to_pcx_file
 * Entry: 00479e50
 * Signature: undefined4 __cdecl write_texture_buffer_to_pcx_file(char * param_1, int * param_2, void * param_3)
 */


/* cgpt rename v4: Wraps a texture buffer as a bitmap surface context, writes it as an 8bpp PCX
   file, then releases the temporary context. */

undefined4 __cdecl write_texture_buffer_to_pcx_file(char *param_1,int *param_2,void *param_3)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int local_68 [13];
  int local_34 [13];
  
  piVar1 = (int *)construct_bitmap_surface_context
                            (local_34,*param_2,(param_2[1] << 3) >> 3,(int)(param_2 + 2),0);
  piVar4 = local_68;
  for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = *piVar1;
    piVar1 = piVar1 + 1;
    piVar4 = piVar4 + 1;
  }
  uVar2 = write_8bpp_pcx_file_with_palette(param_1,local_68,param_3);
  release_bitmap_surface_context(local_68);
  return uVar2;
}


