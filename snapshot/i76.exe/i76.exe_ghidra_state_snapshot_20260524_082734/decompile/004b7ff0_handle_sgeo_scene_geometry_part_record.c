/*
 * Program: i76.exe
 * Function: handle_sgeo_scene_geometry_part_record
 * Entry: 004b7ff0
 * Signature: bool __cdecl handle_sgeo_scene_geometry_part_record(int param_1, undefined4 * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle geometry part set context
   helper based on adjacent named subsystem context.
   [cgpt-i76-v36 medium] SGEO handler in scene-object descriptor pipeline.
   
   I76 rename v43: handle_sgeo_scene_geometry_record
   SGEO handler in SDF child descriptor table. */

bool __cdecl handle_sgeo_scene_geometry_part_record(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int local_18 [6];
  
  piVar3 = (int *)&stack0xffffffe4;
  iVar4 = 6;
  piVar5 = local_18;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = param_1 + 0xc;
  do {
    piVar3 = piVar3 + 1;
    *piVar3 = iVar2;
    iVar2 = iVar2 + iVar1 * 0x78;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar2 = instantiate_vdf_vehicle_geometry_part_sets
                    (local_18,(int *)*param_2,3,2,iVar1,(undefined *)0x0);
  return iVar2 != 0;
}


