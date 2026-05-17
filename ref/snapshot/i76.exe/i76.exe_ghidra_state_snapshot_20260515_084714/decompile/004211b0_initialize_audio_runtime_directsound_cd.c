/*
 * Program: i76.exe
 * Function: initialize_audio_runtime_directsound_cd
 * Entry: 004211b0
 * Signature: undefined4 __cdecl initialize_audio_runtime_directsound_cd(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Initializes DirectSound runtime state, audio attenuation tables, default volumes,
   CD audio state, and the audio object heap. */

undefined4 __cdecl initialize_audio_runtime_directsound_cd(int param_1)

{
  int *piVar1;
  float10 fVar2;
  int *piVar3;
  int *piVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int *piVar8;
  uint uVar9;
  uint uVar10;
  undefined4 *puVar11;
  uint uVar12;
  float10 fVar13;
  
  puVar11 = &DAT_005fce00;
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  DAT_00524564 = (undefined4 *)0x0;
  if (DAT_004ed7e0 != 0) {
    iVar7 = init_directsound(param_1,&DAT_005fce00,(undefined4 *)&DAT_004ed7e4);
    if (iVar7 != 0) {
      DAT_00524564 = &DAT_005fce00;
      puVar11 = &DAT_005fcdc0;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      puVar11 = &DAT_005fce40;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = 0;
        puVar11 = puVar11 + 1;
      }
      if (DAT_005fce08 != 0) {
        _DAT_005fcdf4 = 0x3f800000;
        DAT_005fcdc0 = 0x40;
        DAT_005fce40 = 0x40;
        _DAT_005fcdf8 = 0x3f800000;
        _DAT_005fce5c = 0x168;
        _DAT_005fce60 = 0x168;
        _DAT_005fcdfc = 0x3f4ccccd;
        _DAT_005fce64 = 0;
        _DAT_005fce68 = 0;
        _DAT_005fce6c = 0x3f800000;
        _DAT_005fce70 = 0;
        if (DAT_0052467c == 0) {
          _DAT_005fce74 = 0x41c80000;
          _DAT_005fce78 = 0x43c80000;
        }
        else {
          _DAT_005fce74 = 0x3f800000;
          _DAT_005fce78 = 0x4e6e6b28;
        }
        _DAT_005fce7c = 0;
      }
      uVar9 = DAT_00654b90 >> 0x18;
      if (uVar9 == 1) {
        uVar9 = 0;
      }
      iVar7 = 0;
      piVar3 = (int *)0x0;
      piVar4 = DAT_005fce1c;
      while (piVar4 != (int *)0x0) {
        piVar1 = (int *)*piVar4;
        piVar8 = piVar3;
        if (((int)uVar9 <= iVar7) && (piVar8 = piVar4, (*(byte *)(piVar4 + 5) & 4) == 0)) {
          set_audio_object_playback_flags_and_queue(piVar4,0x20);
          piVar8 = piVar3;
        }
        iVar7 = iVar7 + 1;
        piVar3 = piVar8;
        piVar4 = piVar1;
      }
      DAT_00524564[4] = uVar9;
      if (piVar3 != (int *)0x0) {
        release_audio_world_object_attachment_records(0);
      }
      fVar13 = (float10)_DAT_004bccc8;
      param_1 = 1;
      _DAT_005fcc20 = 0xc61c4000;
      fVar2 = (float10)_DAT_004bccd0;
      pfVar5 = (float *)&DAT_005fcc24;
      do {
        pfVar6 = pfVar5 + 1;
        *pfVar5 = (float)((float10)0.6931471805599453 * (float10)param_1 * (float10)_DAT_004bccd8 *
                          (fVar2 / ((float10)0.6931471805599453 * fVar13)) * (float10)_DAT_004bccdc)
        ;
        pfVar5 = pfVar6;
        param_1 = param_1 + 1;
      } while ((int)pfVar6 < 0x5fcdb4);
      uVar10 = DAT_00654b90 >> 8 & 0xff;
      uVar9 = DAT_00654b90 & 0xff;
      uVar12 = DAT_00654b90 >> 0x10 & 0xff;
      if (uVar9 == 1) {
        uVar9 = 0;
      }
      if (uVar10 == 1) {
        uVar10 = 0;
      }
      if (uVar12 == 1) {
        uVar12 = 0;
      }
      if (uVar9 != 0xfffffffe) {
        set_aux_cd_audio_volume_scaled(uVar9);
      }
      if (DAT_00524564 != (undefined4 *)0x0) {
        if (uVar10 != 0xfffffffe) {
          DAT_00524564[5] = uVar10;
        }
        if (uVar12 != 0xfffffffe) {
          DAT_00524564[6] = uVar12;
        }
      }
      initialize_cd_audio_playback_state();
      DAT_005fcc00 = HeapCreate(0,0,0);
      DAT_005fcbf4 = 0;
      return 1;
    }
    return 0;
  }
  return 0;
}


