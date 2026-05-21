/*
 * Program: i76shell.dll
 * Function: open_mpack_database
 * Entry: 10007fd0
 * Signature: char * __thiscall open_mpack_database(void * this, char * param_1)
 */


/* i76shell first-pass rename
   old_name: FUN_10007fd0
   suggested_name: open_mpack_database
   basis: References diagnostic string: Could not open mpack DB: %s. */

char * __thiscall open_mpack_database(void *this,char *param_1)

{
  int *_DstBuf;
  char cVar1;
  FILE *pFVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  void *local_4;
  
  uVar7 = 0xffffffff;
  do {
    pcVar9 = param_1;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar9 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar9;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar9 = pcVar9 + -uVar7;
  pcVar11 = this;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar11 = pcVar11 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar11 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar11 = pcVar11 + 1;
  }
  local_4 = this;
  pFVar2 = fopen(this,s_rb_10043b20);
  *(FILE **)((int)this + 0x80) = pFVar2;
  if (pFVar2 != (FILE *)0x0) {
    setvbuf(*(FILE **)((int)this + 0x80),(char *)0x0,0,0x4000);
    _DstBuf = (int *)((int)this + 0x84);
    fread(_DstBuf,4,1,*(FILE **)((int)this + 0x80));
    piVar6 = (int *)((int)this + 0x88);
    create_pointer_collection(piVar6,*_DstBuf,0,4,0);
    param_1 = (char *)0x0;
    if (0 < *_DstBuf) {
      do {
        fread(&local_4,4,1,*(FILE **)((int)this + 0x80));
        puVar3 = operator_new(8);
        if (puVar3 == (undefined4 *)0x0) {
          puVar3 = (undefined4 *)0x0;
        }
        else {
          puVar3[1] = 0;
          *puVar3 = local_4;
        }
        expand_pointer_collection((int *)*piVar6,puVar3);
        param_1 = param_1 + 1;
      } while ((int)param_1 < *_DstBuf);
    }
    fseek(*(FILE **)((int)this + 0x80),0,2);
    piVar4 = (int *)ftell(*(FILE **)((int)this + 0x80));
    piVar5 = (int *)FUN_10003610(*piVar6,0);
    iVar10 = 1;
    piVar6 = piVar4;
    if (1 < *_DstBuf) {
      do {
        piVar6 = (int *)FUN_10003610(*(int *)((int)this + 0x88),iVar10);
        piVar5[1] = *piVar6 - *piVar5;
        if (iVar10 < *_DstBuf + -1) {
          piVar5 = piVar6;
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < *_DstBuf);
    }
    piVar6[1] = (int)piVar4 - *piVar6;
    return this;
  }
  fprintf((FILE *)(_iob_exref + 0x40),s_Could_not_open_mpack_DB___s_10043b24,this);
  fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
  exit(1);
}


