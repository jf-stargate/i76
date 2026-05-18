/*
 * Program: i76.exe
 * Function: projection_or_clip_context_helper_0047a1b0
 * Entry: 0047a1b0
 * Signature: undefined8 __cdecl projection_or_clip_context_helper_0047a1b0(int * param_1, int param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: projection or clip context helper
   based on adjacent named subsystem context. */

undefined8 __cdecl projection_or_clip_context_helper_0047a1b0(int *param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  
  uVar4 = 0;
  uVar2 = 0;
  iVar5 = (param_1[1] & 0xffffU) * *param_1;
  puVar6 = (uint *)param_1[5];
  if (iVar5 != 0) {
    if (iVar5 < 4) goto LAB_0047a209;
    do {
      iVar5 = iVar5 + -4;
      uVar3 = CONCAT11(*(undefined1 *)(param_2 + (uint)*(byte *)((int)puVar6 + 1)),
                       *(undefined1 *)(param_2 + (uint)(byte)*puVar6));
      uVar2 = (uint)*(byte *)((int)puVar6 + 2);
      uVar4 = (uint)*(byte *)((int)puVar6 + 3);
      puVar7 = puVar6 + 1;
      *puVar6 = (uint)uVar3 |
                CONCAT22(uVar3,CONCAT11(*(undefined1 *)(param_2 + uVar4),
                                        *(undefined1 *)(param_2 + uVar2))) << 0x10;
      puVar6 = puVar7;
    } while (3 < iVar5);
    for (; puVar6 = puVar7, iVar5 != 0; iVar5 = iVar5 + -1) {
LAB_0047a209:
      puVar7 = (uint *)((int)puVar6 + 1);
      bVar1 = *(byte *)(param_2 + (uint)(byte)*puVar6);
      uVar2 = (uint)bVar1;
      *(byte *)puVar6 = bVar1;
    }
  }
  return CONCAT44(uVar4,uVar2);
}


