/*
 * Program: i76.exe
 * Function: test_road_loop_distance_window_clear
 * Entry: 0040d480
 * Signature: bool __cdecl test_road_loop_distance_window_clear(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Tests whether a road-loop traversal window remains
   clear within a supplied accumulated distance budget. */

bool __cdecl
test_road_loop_distance_window_clear
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
          int param_8)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == param_7) {
    return false;
  }
  if (param_1 == 1) {
    iVar2 = *(int *)(param_3 + 0x14) - param_4;
    iVar1 = *(int *)(param_3 + 0xc);
    while (iVar1 == 0) {
      param_3 = *(int *)(param_3 + 4);
      iVar2 = iVar2 + *(int *)(param_3 + 0x14);
      if (param_2 < iVar2) {
        return false;
      }
      iVar1 = *(int *)(param_3 + 0xc);
    }
    while( true ) {
      if (param_6 == param_7) {
        return iVar2 + param_8 < param_2;
      }
      iVar2 = iVar2 + *(int *)(param_6 + 0x14);
      if (param_2 < iVar2) break;
      param_6 = *(int *)(param_6 + 4);
    }
  }
  else {
    iVar1 = *(int *)(param_3 + 8);
    if (iVar1 != 0) {
      iVar2 = *(int *)(iVar1 + 0xc);
      while (iVar2 == 0) {
        param_4 = param_4 + *(int *)(iVar1 + 0x14);
        if (param_2 < param_4) {
          return false;
        }
        iVar1 = *(int *)(iVar1 + 8);
        if (iVar1 == 0) break;
        iVar2 = *(int *)(iVar1 + 0xc);
      }
    }
    while( true ) {
      if (param_5 == param_7) {
        return param_4 + (*(int *)(param_5 + 0x14) - param_8) < param_2;
      }
      param_4 = param_4 + *(int *)(param_5 + 0x14);
      if (param_2 < param_4) break;
      param_5 = *(int *)(param_5 + 8);
    }
  }
  return false;
}


