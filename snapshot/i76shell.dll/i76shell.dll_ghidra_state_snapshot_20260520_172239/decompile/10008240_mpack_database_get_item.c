/*
 * Program: i76shell.dll
 * Function: mpack_database_get_item
 * Entry: 10008240
 * Signature: undefined4 __thiscall mpack_database_get_item(void * this, int param_1, undefined4 * param_2, long * param_3)
 */


/* i76shell first-pass rename
   old_name: FUN_10008240
   suggested_name: mpack_database_get_item
   basis: TMPackDataBaseObj::GetDBItem candidate from mpack/database diagnostic strings. */

undefined4 __thiscall
mpack_database_get_item(void *this,int param_1,undefined4 *param_2,long *param_3)

{
  long *plVar1;
  LPVOID _DstBuf;
  
  if ((*(int *)(*(int *)((int)this + 0x88) + 4) < param_1) || (param_1 < 0)) {
    plVar1 = (long *)0x0;
  }
  else {
    plVar1 = (long *)FUN_10003610(*(int *)((int)this + 0x88),param_1 + -1);
  }
  if (plVar1 == (long *)0x0) {
    *param_2 = 0;
    *param_3 = 0;
    return 1;
  }
  _DstBuf = HeapAlloc(DAT_10051c50,1,plVar1[1]);
  if (_DstBuf == (LPVOID)0x0) {
    fprintf((FILE *)(_iob_exref + 0x40),s_Out_of_memory_in_TMPackDataBaseO_10043b44);
    fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  *param_2 = _DstBuf;
  *param_3 = plVar1[1];
  fseek(*(FILE **)((int)this + 0x80),*plVar1,0);
  fread(_DstBuf,1,plVar1[1],*(FILE **)((int)this + 0x80));
  return 0;
}


