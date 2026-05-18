/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f140
 * Entry: 0040100f
 * Signature: undefined8 __cdecl thunk_FUN_0040f140(float param_1)
 */


undefined8 __cdecl thunk_FUN_0040f140(float param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar2 = (float10)fsin((float10)param_1);
  return CONCAT44((float)fVar1,(float)fVar2);
}


