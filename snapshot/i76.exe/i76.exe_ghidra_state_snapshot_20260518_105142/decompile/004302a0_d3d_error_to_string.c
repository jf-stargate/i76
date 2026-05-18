/*
 * Program: i76.exe
 * Function: d3d_error_to_string
 * Entry: 004302a0
 * Signature: undefined4 __stdcall d3d_error_to_string(void)
 */


/* i76 first-pass rename
   old_name: FUN_004302a0
   suggested_name: d3d_error_to_string
   basis: Renderer/D3D error string lookup; includes D3DRMERR and execute-buffer diagnostics. */

undefined4 d3d_error_to_string(void)

{
  undefined4 uVar1;
  int iVar2;
  int *unaff_EDI;
  undefined4 *puVar3;
  char *pcVar4;
  undefined4 local_48;
  undefined4 *local_44;
  undefined4 local_40 [16];
  
  local_48 = 0;
  if (DAT_005fde4c == 0) {
    return 1;
  }
  local_40[1] = 0;
  local_44 = (undefined4 *)0x14;
  local_40[3] = 0;
  local_40[0] = 1;
  local_40[2] = 0x9c;
  DAT_005fdc0c = (**(code **)(*DAT_005fde48 + 0x18))(DAT_005fde48,&local_44,&local_48,0);
  if (DAT_005fdc0c == 0) {
    DAT_005fdc0c = (**(code **)(*unaff_EDI + 0x10))(unaff_EDI,&stack0xffffffac);
    if (DAT_005fdc0c == 0) {
      DAT_005fdc0c = 0;
      puVar3 = local_44;
      for (iVar2 = 0x27; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      *(undefined1 *)local_44 = 8;
      *(undefined1 *)((int)local_44 + 1) = 8;
      *(undefined2 *)((int)local_44 + 2) = 0xf;
      local_44[1] = 9;
      local_44[2] = DAT_005fcea8;
      local_44[3] = 4;
      local_44[4] = DAT_005fcea4;
      local_44[5] = 7;
      if ((DAT_005fcea0 == 0) || (DAT_005fe5b8 == 0)) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
      local_44[6] = uVar1;
      local_44[7] = 0xe;
      local_44[8] = DAT_005fcea0;
      local_44[9] = 0x17;
      local_44[10] = 4;
      local_44[0xb] = 0x11;
      local_44[0xc] = DAT_005fceac;
      local_44[0xd] = 0x12;
      local_44[0xe] = DAT_005fceac;
      local_44[0xf] = 3;
      local_44[0x10] = DAT_005fceb0;
      local_44[0x11] = 0x15;
      local_44[0x12] = DAT_005fceb4;
      local_44[0x13] = 8;
      local_44[0x14] = DAT_005fceb8;
      local_44[0x15] = 0x1a;
      local_44[0x16] = DAT_005fcebc;
      local_44[0x17] = 0x1d;
      local_44[0x18] = DAT_005fcec0;
      local_44[0x19] = 2;
      local_44[0x1a] = DAT_005fcec4;
      local_44[0x1b] = 0x1c;
      local_44[0x1c] = DAT_005fcec8;
      local_44[0x1d] = 0x22;
      local_44[0x1e] = DAT_005fcecc;
      *(undefined1 *)(local_44 + 0x1f) = 7;
      *(undefined1 *)((int)local_44 + 0x7d) = 8;
      *(undefined2 *)((int)local_44 + 0x7e) = 3;
      local_44[0x20] = 4;
      local_44[0x21] = -(uint)(DAT_005fcec8 != 0) & DAT_005fced0;
      local_44[0x22] = 5;
      local_44[0x23] = DAT_005fced4;
      local_44[0x24] = 6;
      local_44[0x25] = DAT_005fced8;
      *(undefined1 *)(local_44 + 0x26) = 0xb;
      *(undefined1 *)((int)local_44 + 0x99) = 0;
      *(undefined2 *)((int)local_44 + 0x9a) = 0;
      DAT_005fdc0c = (**(code **)(*unaff_EDI + 0x14))(unaff_EDI);
      if (DAT_005fdc0c == 0) {
        puVar3 = local_40;
        for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = 0;
          puVar3 = puVar3 + 1;
        }
        local_40[0] = 0x30;
        local_40[3] = 0;
        local_40[4] = 0x9c;
        (**(code **)(*unaff_EDI + 0x18))(unaff_EDI,local_40);
        DAT_005fdc0c = (**(code **)(*DAT_005fde48 + 0x4c))(DAT_005fde48);
        if (DAT_005fdc0c == 0) {
          DAT_005fdc0c = (**(code **)(*DAT_005fde48 + 0x20))(DAT_005fde48,unaff_EDI,DAT_005fde4c,2);
          if (DAT_005fdc0c == 0) {
            DAT_005fdc0c = (**(code **)(*DAT_005fde48 + 0x50))(DAT_005fde48);
            if (DAT_005fdc0c == 0) {
              (**(code **)(*unaff_EDI + 8))(unaff_EDI);
              return 1;
            }
            directdraw_error_to_string(DAT_005fdc0c);
            pcVar4 = s_EndScene_failed_in_SetRenderStat_004ee100;
          }
          else {
            directdraw_error_to_string(DAT_005fdc0c);
            pcVar4 = s_Execute_failed_in_SetRenderState_004ee128;
          }
        }
        else {
          directdraw_error_to_string(DAT_005fdc0c);
          pcVar4 = s_BeginScene_failed_in_SetRenderSt_004ee150;
        }
      }
      else {
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar4 = s_Unlock_failed_on_execute_buffer_i_004ee178;
      }
    }
    else {
      directdraw_error_to_string(DAT_005fdc0c);
      pcVar4 = s_Lock_failed_on_execute_buffer_in_004ee1b0;
    }
  }
  else {
    directdraw_error_to_string(DAT_005fdc0c);
    pcVar4 = s_CreateExecuteBuffer_failed_in_Se_004ee1e4;
  }
  set_directdraw_error_message(pcVar4);
  if (unaff_EDI != (int *)0x0) {
    (**(code **)(*unaff_EDI + 8))(unaff_EDI);
  }
  return 0;
}


