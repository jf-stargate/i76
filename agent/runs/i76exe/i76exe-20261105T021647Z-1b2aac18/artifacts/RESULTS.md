# Complete output hashes and differential results

Generated from `evidence/results.json`; every LUM hash covers65,536 bytes, every gamma hash covers2,560 bytes. Individual256-byte gamma-row hashes are in the JSON. The original code uses the named substituted CRT services; these are not certified retail DLL outputs.

| Context / CW / power service | Complete LUM SHA-256 | Complete gamma SHA-256 |
|---|---|---|
| gray-037f-0 | `88541b4207dd51b8609c6e76c6055c36cf46ad2200488c49ed6c0e948ac64034` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| permuted-037f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| ties-037f-0 | `759deed8df55e3f047fc2b356506a4c85087b03ecaf90af667db9937aca0cc04` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| m05-037f-0 | `186a530206432bdd83a9479c6fb5e8af33a15365346e199454697044735cbede` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| m15-037f-0 | `4b13ed10b6820de8366c47165b3b9d5ec0b713ca942651723800901b310f2f75` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| t01-037f-0 | `e50b6fb7de146253bc34a244eae99cb68320be0e257769455d6c94bc2ef54689` | `98ec5d21af3d8b58fc1243b989897ebe30859d4276e029aeac865b99e78ed1c6` |
| permuted-007f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `bd88aa450596213497c866d22d5dd944a658299cbece15787402fd64650c6fa7` |
| permuted-047f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-087f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `bd88aa450596213497c866d22d5dd944a658299cbece15787402fd64650c6fa7` |
| permuted-0c7f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-027f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `4c97c9b3000f79d3c8e7825d5b5aed54b7179657463854d2bdc27e975ca9d908` |
| permuted-067f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-0a7f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `bd88aa450596213497c866d22d5dd944a658299cbece15787402fd64650c6fa7` |
| permuted-0e7f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-077f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-0b7f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `95adfd183bfe9d18504964c0f6a4c4462ef66b6265f2c3b802735c37ad5e693e` |
| permuted-0f7f-0 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |
| permuted-007f-1 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `bd88aa450596213497c866d22d5dd944a658299cbece15787402fd64650c6fa7` |
| permuted-027f-1 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `4c97c9b3000f79d3c8e7825d5b5aed54b7179657463854d2bdc27e975ca9d908` |
| permuted-037f-1 | `a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a` | `b85763042997637fe960ceab33332d7d6e3c2ad5c57eb13babecc7f39f24dcde` |

Power suffix0=glibc double pow,1=glibc extended powl. CW values are in case names as four hex digits. All20 cases have zero native-versus-rational LUM mismatches, zero native-versus-independent-C mismatches, and zero original-conversion-sequence mismatches. Each power trace contains all2,560 pairs of input operands and returned values; surrounding rational arithmetic verifies every operand and stored byte.

| Counterfactual on permuted palette | Different LUM bytes |
|---|---|
| no-cache | 553 |
| last-tie | 149 |
| row-major | 1214 |
| early-spill | 0 |

| Retail LUM resource | Different bytes from conditional generation |
|---|---|
| m05.lum | 65286 |
| m15.lum | 59832 |
| t01.lum | 46539 |

Resource differences use unmodified ACT bytes installed in a supplied context. They do not establish resource authoring methods or output under a particular corrected backend. Runtime tables and resource payloads remain private.

The published Ghidra comparisons include full original generator return and65,536 stores for permuted/tie/retail m05, plus a PC24 arithmetic control. PC64 power-operand and byte comparisons pass. Under PC24, native-service replay has2,556 mismatched original input pairs, despite equal final bytes; that replay must not be called architectural parity. The separate fixed-PC64 replay control returns identical gamma hashes for emulated CW037F and007F, exposing that Ghidra ignores these precision bits. Native CW007F with its own service differs in167 gamma bytes.
