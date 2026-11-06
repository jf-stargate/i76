# Validation results

Final fresh-project reproduction and a subsequent execution replay with additional
exact table-address assertions passed. Runtime buffer/sample/selection metadata is byte-identical across replays.
All published evidence derives from the final procedures, not failed attempts.

| Group | Passed | Evidence |
|---|---:|---|
| Authenticated original VQM/CBK decode comparisons | 20 | execution.json decoder_comparisons |
| Original synthetic edge/token/capacity/CBK-count cases | 14 | synthetic_original |
| Strict independent-decoder negative cases | 6 | strict_host_rejections |
| Authentic connected full callback cases | 24 | connected draws |
| Texture-format selection controls including direct MAP | 8 | selection.json |
| Original alternative M16 acquisition/marking | 2 | m16_observation |
| Synthetic reserved-index callbacks | 2 | reserved_indices.json |

296 original indexed framebuffer stores use authentic decoded materials; 10 more
belong only to synthetic reserved-index tests. All compared outputs, source texel
read addresses/bytes, shade/composition table addresses/bytes and byte stores
match independent calculations. Guard bytes and untouched framebuffer bytes pass.

Independent corpus: 5987 unique VQM names, 18 shapes, all strict decodes pass;
20 sampled original executions cover every shape. All inputs authenticated from
one base-game archive, not supplied historical exporter results. Full proprietary
buffers and full inventory remain private.

Static audit authenticated 5472 instructions across 26 requested functions, and 1951 unique executed instructions / 3792905 retirements. Ghidra annotation modification count stayed3→3. Original EXE/GZF and saved program hashes stayed unchanged. This is original-x86 emulation with explicit services, not native Windows execution.

| Texture | Source SHA-256 | Runtime header+pixels SHA-256 | Texels-only SHA-256 |
|---|---|---|---|
| xb11mdu1.vqm | 2effced14de7a2204c2881630d5f86691ccefadccbe11d5077d8bc447ee9bf6a | 1f1f9a9e2d080515114004a373ea97ce4a356860dbf6893d76ed06af54538f52 | 362f26209278587548091fe65ebf9cb51345aef5103ca62b2efc2549dcdcdaaa |
| al11mdu1.vqm | 1ae32fc7cf36fe041f58c5a1a3689f2a67605499f518df20f1c3fdb817715e67 | 821581b1b6aef9fabd045ec82076ed5c4dd34d1a9ca762d91c07a1cecacaebb1 | e850e73463803899368dad5a1668efe0b2869f4d8a258c18842e98639b74335f |
| 3abrtms1.vqm | d0ef3c30ea7ba603e63e3660baf8e36b451c054833a493516ca16460dfb1286d | 255c73795a27b8619c6ebc7acd017ce96906643e376a3c8d7688d81e06a3abb2 | 5aa62a70599c667485395bdf4b1f4b2036b95db41d6bcfcec15e4393288919d3 |

All CBK/TMT/M16/table and backing PIX/PAK/ZFS identities are in execution.json; MCALT101.MAP is in selection.json. See SERVICE_ACCOUNTING.md for substitutions and SOFTWARE_SAMPLING.md for numeric limits. Complete variable-q interpolation, real textured GEO submission, display RGB, M16 decode and full resource lifetimes remain unvalidated.
