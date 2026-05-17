/*
 * Program: I76EDIT.EXE
 * Function: getSystemCP
 * Entry: 00427f30
 * Signature: int __cdecl getSystemCP(int param_1)
 */


/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 1998 Release */

int __cdecl getSystemCP(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    DAT_00438b8c = 1;
                    /* WARNING: Could not recover jumptable at 0x00427f4d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    DAT_00438b8c = 1;
                    /* WARNING: Could not recover jumptable at 0x00427f62. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = DAT_00438fa0;
  }
  DAT_00438b8c = (uint)bVar2;
  return param_1;
}


