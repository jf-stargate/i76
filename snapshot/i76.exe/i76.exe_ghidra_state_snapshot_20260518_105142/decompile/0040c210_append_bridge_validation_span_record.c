/*
 * Program: i76.exe
 * Function: append_bridge_validation_span_record
 * Entry: 0040c210
 * Signature: undefined * __cdecl append_bridge_validation_span_record(double param_1, double param_2, undefined4 param_3, float param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v7 fsm predicate/bridge cluster: Appends a bridge/path validation span record from
   rounded endpoint coordinates, object pointer, and height/range values. */

undefined * __cdecl
append_bridge_validation_span_record
          (double param_1,double param_2,undefined4 param_3,float param_4,float param_5)

{
  double _X;
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  floor(param_1 - _DAT_004bc658);
  uVar2 = ftol();
  _X = param_2 - _DAT_004bc658;
  iVar3 = DAT_0051f690 * 0x28;
  *(undefined4 *)(&DAT_0051f6a0 + DAT_0051f690 * 0x28) = uVar2;
  floor(_X);
  uVar2 = ftol();
  *(undefined4 *)(&DAT_0051f6a4 + iVar3) = uVar2;
  *(undefined4 *)(&DAT_0051f6b0 + iVar3) = param_3;
  *(double *)(&DAT_0051f698 + iVar3) =
       (double)*(int *)(&DAT_0051f6a4 + iVar3) -
       (double)*(int *)(&DAT_0051f6a0 + iVar3) * _DAT_004bc660;
  floor((double)(param_4 - _DAT_004bc668));
  uVar2 = ftol();
  iVar3 = DAT_0051f690;
  fVar1 = param_5 - _DAT_004bc668;
  iVar4 = DAT_0051f690 * 0x28;
  *(undefined4 *)(&DAT_0051f6a8 + DAT_0051f690 * 0x28) = uVar2;
  floor((double)fVar1);
  uVar2 = ftol();
  *(undefined4 *)(&DAT_0051f6ac + iVar4) = uVar2;
  (&DAT_0051f6b4)[iVar3 * 10] = 0;
  (&DAT_0051f6b8)[iVar3 * 10] = 0;
  DAT_0051f690 = DAT_0051f690 + 1;
  return &DAT_0051f670 + DAT_0051f690 * 0x28;
}


