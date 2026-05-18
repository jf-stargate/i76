/*
 * Program: I76EDIT.EXE
 * Function: __ld12tod
 * Entry: 0042a610
 * Signature: INTRNCVT_STATUS __cdecl __ld12tod(_LDBL12 * _Ifp, _CRT_DOUBLE * _D)
 */


/* Library Function - Single Match
    __ld12tod
   
   Library: Visual Studio 1998 Release */

INTRNCVT_STATUS __cdecl __ld12tod(_LDBL12 *_Ifp,_CRT_DOUBLE *_D)

{
  INTRNCVT_STATUS IVar1;
  
  IVar1 = __ld12cvt((ushort *)_Ifp,(uint *)_D,(int *)&DAT_00438f48);
  return IVar1;
}


