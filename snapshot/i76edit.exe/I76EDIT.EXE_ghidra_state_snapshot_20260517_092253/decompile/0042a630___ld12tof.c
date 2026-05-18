/*
 * Program: I76EDIT.EXE
 * Function: __ld12tof
 * Entry: 0042a630
 * Signature: INTRNCVT_STATUS __cdecl __ld12tof(_LDBL12 * _Ifp, _CRT_FLOAT * _F)
 */


/* Library Function - Multiple Matches With Different Base Names
    __ld12tod
    __ld12tof
   
   Library: Visual Studio 1998 Release */

INTRNCVT_STATUS __cdecl __ld12tof(_LDBL12 *_Ifp,_CRT_FLOAT *_F)

{
  INTRNCVT_STATUS IVar1;
  
  IVar1 = __ld12cvt((ushort *)_Ifp,(uint *)_F,(int *)&DAT_00438f60);
  return IVar1;
}


