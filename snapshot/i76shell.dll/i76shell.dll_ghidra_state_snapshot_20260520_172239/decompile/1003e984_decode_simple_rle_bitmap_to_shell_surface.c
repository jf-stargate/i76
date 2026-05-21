/*
 * Program: i76shell.dll
 * Function: decode_simple_rle_bitmap_to_shell_surface
 * Entry: 1003e984
 * Signature: undefined4 __cdecl decode_simple_rle_bitmap_to_shell_surface(int * param_1, int param_2)
 */


undefined4 __cdecl decode_simple_rle_bitmap_to_shell_surface(int *param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  
  sVar3 = *(short *)(param_2 + 10);
  sVar4 = *(short *)(param_2 + 6);
  iVar9 = 0;
  uVar5 = *(ushort *)(param_2 + 0x42);
  puVar10 = (undefined1 *)(param_2 + 0x80);
  do {
    puVar11 = &DAT_1004db25;
    do {
      puVar1 = puVar10 + 1;
      uVar6 = CONCAT11(*puVar10,*puVar10) & 0xc0ff;
      uVar7 = uVar6 ^ 0xc000;
      if ((char)(uVar7 >> 8) == '\0') {
        puVar10 = puVar10 + 2;
        uVar2 = *puVar1;
        puVar12 = puVar11;
        for (uVar8 = uVar7 & 0x3f; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar12 = uVar2;
          puVar12 = puVar12 + 1;
        }
      }
      else {
        puVar12 = puVar11 + 1;
        *puVar11 = (char)uVar6;
        puVar10 = puVar1;
      }
      puVar11 = puVar12;
    } while ((int)puVar12 < (int)((undefined1 *)(uint)uVar5 + 0x1004db25));
    write_decoded_image_scanline_to_shell_surface
              (param_1,iVar9,(undefined4 *)&DAT_1004db25,(undefined1 *)(uint)uVar5);
    iVar9 = iVar9 + 1;
  } while (iVar9 <= (int)(uint)(ushort)(sVar3 - sVar4));
  return 0;
}


