/*
 * Program: i76.exe
 * Function: fsm_astar_illegal_state_error
 * Entry: 0040cc90
 * Signature: undefined4 __cdecl fsm_astar_illegal_state_error(undefined4 * param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: FSM - astar in illigal state */

undefined4 __cdecl fsm_astar_illegal_state_error(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  switch(*param_1) {
  case 0:
    if ((-1 < param_2) && (param_2 < 3)) {
      return 1;
    }
    break;
  case 1:
    if (-1 < param_2) {
      if (param_2 < 2) {
        return 1;
      }
      if (param_2 == 6) {
        return 1;
      }
    }
    break;
  case 2:
    if (1 < param_2) {
      if (param_2 < 4) {
        return 1;
      }
      if (param_2 == 7) {
        return 1;
      }
    }
    break;
  case 3:
    if ((2 < param_2) && (param_2 < 6)) {
      return 1;
    }
    break;
  case 4:
    if (2 < param_2) {
      if (param_2 < 5) {
        return 1;
      }
      if (param_2 == 6) {
        return 1;
      }
    }
    break;
  case 5:
    if (param_2 == 3) {
      return 1;
    }
    if (param_2 == 5) {
      return 1;
    }
    if (param_2 == 7) {
      return 1;
    }
    return 0;
  case 6:
    iVar1 = param_2 + -1;
    goto LAB_0040ccb4;
  case 7:
    iVar1 = param_2 + -2;
LAB_0040ccb4:
    if ((iVar1 == 0) || (iVar1 == 3)) {
      return 1;
    }
    if (iVar1 == 5) {
      return 1;
    }
    break;
  default:
    report_error();
  }
  return 0;
}


