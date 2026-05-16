/*
 * Program: i76.exe
 * Function: set_directsound_primary_buffer_rate
 * Entry: 00426050
 * Signature: undefined4 __cdecl set_directsound_primary_buffer_rate(int param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Cannot set DSound primary buffer rate */

undefined4 __cdecl set_directsound_primary_buffer_rate(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 local_10;
  int local_c;
  int local_8;
  undefined4 local_4;
  
  if ((param_1 != 0) && (piVar1 = *(int **)(param_1 + 4), piVar1 != (int *)0x0)) {
    local_8 = param_2 * 2;
    local_10 = 0x20001;
    local_c = param_2;
    local_4 = 0x80002;
    iVar2 = (**(code **)(*piVar1 + 0x38))(piVar1,&local_10);
    if (iVar2 != 0) {
      report_chunk_parse_error();
      return 0;
    }
  }
  return 1;
}


