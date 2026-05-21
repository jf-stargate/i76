/*
 * Program: i76shell.dll
 * Function: write_i76car_vehicle_definition_file
 * Entry: 10008cf0
 * Signature: undefined4 __cdecl write_i76car_vehicle_definition_file(void * param_1, size_t param_2)
 */


undefined4 __cdecl write_i76car_vehicle_definition_file(void *param_1,size_t param_2)

{
  FILE *_File;
  
  _File = fopen(s_i76car_def_10043fdc,s_wb_10043fd8);
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fwrite(&param_2,4,1,_File);
  fwrite(param_1,0x1c,param_2,_File);
  fclose(_File);
  return 1;
}


