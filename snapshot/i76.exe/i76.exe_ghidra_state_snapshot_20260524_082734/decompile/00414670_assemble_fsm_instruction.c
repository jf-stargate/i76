/*
 * Program: i76.exe
 * Function: assemble_fsm_instruction
 * Entry: 00414670
 * Signature: undefined4 __cdecl assemble_fsm_instruction(int param_1, undefined4 param_2, int param_3, undefined4 param_4, int param_5, undefined4 param_6, int param_7, undefined4 param_8, int param_9, int * param_10)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Unknown fsm assembler instuction */

undefined4 __cdecl
assemble_fsm_instruction
          (int param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
          undefined4 param_6,int param_7,undefined4 param_8,int param_9,int *param_10)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int local_54;
  undefined4 local_4f;
  
  puVar4 = &local_4f;
  for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = 0;
  *(undefined1 *)((int)puVar4 + 2) = 0;
  local_54 = 0;
  do {
    if (800 < local_54) {
      DAT_005244dc = 1;
    }
    puVar4 = *(undefined4 **)(param_1 + 0x10a8);
    switch(*puVar4) {
    case 1:
      **(undefined4 **)(param_1 + 0x10b0) = puVar4[1];
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
      break;
    case 2:
      **(int **)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10ac) + puVar4[1] * 4;
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
      break;
    case 3:
      **(undefined4 **)(param_1 + 0x10b0) =
           *(undefined4 *)(*(int *)(param_1 + 0x10ac) + puVar4[1] * 4);
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
      break;
    case 4:
      **(int **)(param_1 + 0x10b4) = *(int *)(param_1 + 0x10ac) + puVar4[1] * 4;
      *(int *)(param_1 + 0x10b4) = *(int *)(param_1 + 0x10b4) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
      break;
    case 5:
      **(undefined4 **)(param_1 + 0x10b4) =
           *(undefined4 *)(*(int *)(param_1 + 0x10ac) + puVar4[1] * 4);
      *(int *)(param_1 + 0x10b4) = *(int *)(param_1 + 0x10b4) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a8) + 8;
      break;
    case 6:
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + puVar4[1] * 4;
      *(undefined4 **)(param_1 + 0x10a8) = puVar4 + 2;
      break;
    case 7:
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + puVar4[1] * -4;
      *(undefined4 **)(param_1 + 0x10a8) = puVar4 + 2;
      break;
    case 8:
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a4) + puVar4[1] * 8;
      break;
    case 9:
      if (*(int *)(param_1 + 0x10a0) != 0) goto LAB_00414866;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a4) + puVar4[1] * 8;
      break;
    case 10:
      *(int *)(param_1 + 0x10a8) =
           *(int *)(param_1 + 0x10a4) + *(int *)(*(int *)(param_1 + 0x10a8) + 4) * 8;
      return 0;
    case 0xb:
      iVar2 = puVar4[1];
      **(undefined4 **)(param_1 + 0x10b0) = *(undefined4 *)(param_1 + 0x10ac);
      piVar3 = (int *)(*(int *)(param_1 + 0x10b0) + 4);
      *(int **)(param_1 + 0x10b0) = piVar3;
      *(int **)(param_1 + 0x10ac) = piVar3;
      *piVar3 = *(int *)(param_1 + 0x10a8) + 8;
      *(int *)(param_1 + 0x10b0) = *(int *)(param_1 + 0x10b0) + 4;
      *(int *)(param_1 + 0x10a8) = *(int *)(param_1 + 0x10a4) + iVar2 * 8;
      break;
    case 0xc:
      puVar1 = *(undefined4 **)(param_1 + 0x10ac);
      iVar2 = puVar4[1];
      *(undefined4 *)(param_1 + 0x10a8) = *puVar1;
      iVar2 = (int)puVar1 - (iVar2 * 4 + 4);
      *(int *)(param_1 + 0x10b0) = iVar2;
      *(undefined4 *)(param_1 + 0x10ac) = puVar1[-1];
      if (iVar2 == param_1) {
        return 1;
      }
      break;
    case 0xd:
      execute_fsm_bytecode_instruction
                (param_1,puVar4[1],param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10)
      ;
      break;
    case 0xe:
      *(uint *)(param_1 + 0x10a0) = (uint)(*(int *)(param_1 + 0x10a0) == 0);
LAB_00414866:
      *(undefined4 **)(param_1 + 0x10a8) = puVar4 + 2;
      break;
    default:
      report_error();
    }
    local_54 = local_54 + 1;
    if (999 < local_54) {
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
  } while( true );
}


