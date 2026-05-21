/*
 * Program: i76shell.dll
 * Function: write_vehicle_part_pointer_list_records
 * Entry: 10035f70
 * Signature: undefined __cdecl write_vehicle_part_pointer_list_records(int param_1, FILE * param_2)
 */


void __cdecl write_vehicle_part_pointer_list_records(int param_1,FILE *param_2)

{
  int *_Str;
  undefined4 *_Str_00;
  int iVar1;
  
  _Str = (int *)(param_1 + 4);
  fwrite(_Str,4,1,param_2);
  iVar1 = 0;
  if (0 < *_Str) {
    do {
      _Str_00 = *(undefined4 **)(*(int *)(param_1 + 8) + iVar1 * 4);
      fwrite(_Str_00,0x20,1,param_2);
      fwrite((void *)*_Str_00,0x54,1,param_2);
      iVar1 = iVar1 + 1;
    } while (iVar1 < *_Str);
  }
  return;
}


