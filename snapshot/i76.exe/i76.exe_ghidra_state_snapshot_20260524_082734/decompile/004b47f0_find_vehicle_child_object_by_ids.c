/*
 * Program: i76.exe
 * Function: find_vehicle_child_object_by_ids
 * Entry: 004b47f0
 * Signature: int * __cdecl find_vehicle_child_object_by_ids(int * param_1, int param_2, int param_3)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Finds an existing vehicle
   child object by ID/name pair during VGEO hierarchy instantiation. */

int * __cdecl find_vehicle_child_object_by_ids(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  
  if (param_1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    while( true ) {
      if ((*param_1 == param_2) && (param_1[1] == param_3)) {
        return param_1;
      }
      piVar1 = find_vehicle_child_object_by_ids((int *)param_1[0x19],param_2,param_3);
      if (piVar1 != (int *)0x0) break;
      param_1 = (int *)param_1[0x18];
      if (param_1 == (int *)0x0) {
        return (int *)0x0;
      }
    }
  }
  return piVar1;
}


