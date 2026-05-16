/*
 * Program: i76.exe
 * Function: load_gdf_resource_reference
 * Entry: 004b1610
 * Signature: undefined __stdcall load_gdf_resource_reference(void)
 */


/* cgpt whole-binary semantic rename v1: references .gdf */

void load_gdf_resource_reference(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int in_stack_00002404;
  undefined4 uVar5;
  
  zfsf_error_context_helper_004ba0a0();
  get_vehicle_runtime_context(in_stack_00002404);
  if (((byte)DAT_00654b98 & 2) == 0) {
    extract_trip_vehicle_vsf_state_from_world_object
              (in_stack_00002404,(undefined4 *)&stack0x00000000);
    iVar3 = 0;
    piVar4 = (int *)&stack0x00000040;
    do {
      if (((piVar4[6] != 0x6c6c756e) || (piVar4[7] != 0)) && (iVar2 = *piVar4, 0 < iVar2)) {
        switch(iVar3) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          pcVar1 = &DAT_004ffec8;
          break;
        default:
          pcVar1 = &DAT_00504c28;
          break;
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
          pcVar1 = s__gdf_004ffec0;
        }
        uVar5 = 0;
        pcVar1 = format_8char_resource_basename_with_suffix(piVar4[6],piVar4[7],pcVar1);
        iVar2 = append_salvage_resource_reference_for_mission(pcVar1,iVar2,uVar5);
        if (iVar2 == 0) {
          return;
        }
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 0x18;
    } while (iVar3 < 0x40);
  }
  return;
}


