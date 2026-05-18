/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_00457570
 * Entry: 00457570
 * Signature: int __cdecl entity_instance_table_context_helper_00457570(int * param_1, int param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457570. Remove
   duplicated network/entity wording. */

int __cdecl entity_instance_table_context_helper_00457570(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int local_400 [256];
  
  iVar4 = 0;
  iVar3 = *param_1;
  do {
    piVar5 = local_400 + iVar4;
    do {
      iVar2 = *(int *)(iVar3 + 0x6c);
      *piVar5 = iVar3;
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 1;
      if (iVar2 == param_2) {
        return iVar3;
      }
      iVar3 = *(int *)(iVar3 + 100);
    } while (iVar3 != 0);
    piVar5 = local_400 + iVar4;
    do {
      if (iVar4 == 0) {
        return 0;
      }
      piVar1 = piVar5 + -1;
      piVar5 = piVar5 + -1;
      iVar4 = iVar4 + -1;
      iVar3 = *(int *)(*piVar1 + 0x60);
    } while (iVar3 == 0);
  } while( true );
}


