/*
 * Program: I76EDIT.EXE
 * Function: ___sbh_heap_check
 * Entry: 004257e0
 * Signature: uint __stdcall ___sbh_heap_check(void)
 */


/* Library Function - Single Match
    ___sbh_heap_check
   
   Library: Visual Studio 1998 Release */

uint ___sbh_heap_check(void)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  undefined **local_1c;
  undefined *local_18;
  int local_14;
  uint local_8;
  int local_4;
  
  local_4 = 0;
  local_1c = &PTR_LOOP_00437e58;
  do {
    if ((undefined **)PTR_LOOP_0043866c == local_1c) {
      local_4 = local_4 + 1;
    }
    puVar6 = (uint *)local_1c[0x204];
    if (puVar6 != (uint *)0x0) {
      local_18 = (undefined *)0x0;
      local_14 = 0;
      do {
        if (*(byte *)((int)local_1c + (int)(local_18 + 0x10)) == 0xff) {
          if ((local_14 == 0) && (local_1c[3] != local_18)) {
            return 0xffffffff;
          }
          local_14 = local_14 + 1;
        }
        else {
          if (puVar6 + 0x3e <= (uint *)*puVar6) {
            return 0xfffffffe;
          }
          if ((char)puVar6[0x3e] != -1) {
            return 0xfffffffd;
          }
          iVar5 = 0;
          iVar8 = 0;
          iVar7 = 0;
          local_8 = 0;
          do {
            if ((iVar5 - *puVar6) + (int)puVar6 == -8) {
              iVar8 = iVar8 + 1;
            }
            bVar2 = *(byte *)((int)puVar6 + iVar5 + 8);
            if (bVar2 == 0) {
              iVar7 = iVar7 + 1;
              iVar5 = iVar5 + 1;
              local_8 = local_8 + 1;
            }
            else {
              if ((int)(uint)*(byte *)((int)local_1c + (int)(local_18 + 0x410)) <= iVar7) {
                return 0xfffffffc;
              }
              if (iVar8 == 1) {
                if (iVar7 < (int)puVar6[1]) {
                  return 0xfffffffb;
                }
                iVar8 = 2;
              }
              iVar7 = 0;
              iVar1 = (uint)bVar2 + iVar5;
              iVar4 = iVar5;
              while (iVar5 = iVar4 + 1, iVar5 < iVar1) {
                iVar3 = iVar4 + 9;
                iVar4 = iVar5;
                if (*(char *)((int)puVar6 + iVar3) != '\0') {
                  return 0xfffffffa;
                }
              }
            }
          } while (iVar5 < 0xf0);
          if (*(byte *)((int)local_1c + (int)(local_18 + 0x10)) != local_8) {
            return 0xfffffff9;
          }
          if (iVar8 == 0) {
            return 0xfffffff8;
          }
        }
        puVar6 = puVar6 + 0x400;
        local_18 = local_18 + 1;
      } while ((int)local_18 < 0x400);
    }
    local_1c = (undefined **)*local_1c;
    if (local_1c == &PTR_LOOP_00437e58) {
      return -(uint)(local_4 == 0) & 0xfffffff7;
    }
  } while( true );
}


