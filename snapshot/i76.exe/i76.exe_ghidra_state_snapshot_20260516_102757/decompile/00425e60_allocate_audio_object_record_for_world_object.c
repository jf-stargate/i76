/*
 * Program: i76.exe
 * Function: allocate_audio_object_record_for_world_object
 * Entry: 00425e60
 * Signature: char * __cdecl allocate_audio_object_record_for_world_object(char * param_1, int param_2, undefined4 * param_3, char * param_4)
 */


/* cgpt rename v3: Allocates or initializes an audio object record, copies sound name/params, and
   increments the attached world-object refcount. */

char * __cdecl
allocate_audio_object_record_for_world_object
          (char *param_1,int param_2,undefined4 *param_3,char *param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if ((param_4 == (char *)0x0) && (param_4 = HeapAlloc(DAT_005fcc00,0,0x7c), param_4 == (char *)0x0)
     ) {
    return (char *)0x0;
  }
  initialize_audio_params_full_defaults((undefined4 *)param_4);
  *(int *)(param_4 + 0x5c) = param_2;
  increment_refcount_recursive_for_object_tree(param_2,&PTR_DAT_004ed7ec);
  if (param_3 != (undefined4 *)0x0) {
    pcVar6 = param_4;
    for (iVar2 = 0xb; pcVar6 = pcVar6 + 4, iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pcVar6 = *param_3;
      param_3 = param_3 + 1;
    }
  }
  if (param_1 != (char *)0x0) {
    uVar3 = 0xffffffff;
    do {
      pcVar6 = param_1;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar5 = pcVar6 + -uVar3;
    pcVar6 = param_4;
    for (uVar4 = uVar3 >> 2; pcVar6 = pcVar6 + 4, uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar6 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  if ((*(uint *)(param_4 + 0x14) & 6) == 0) {
    *(uint *)(param_4 + 0x14) = *(uint *)(param_4 + 0x14) | 2;
  }
  return param_4;
}


