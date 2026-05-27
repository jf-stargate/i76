# Interstate '76 Object Resource Resolution Reference

This page documents the current binary-backed policy for resolving mission
object records to visual resources.

## Correct ODEF / LDEF Policy

```text
+---------------------------+-----------------------------+--------------------------------------+
| Record/source             | Classes / condition          | Resource behavior                    |
+---------------------------+-----------------------------+--------------------------------------+
| ODEF/OBJ                  | class 0x01 + "spawn"         | special spawn marker table           |
| ODEF/OBJ                  | class 0x01 + "regen"         | special regen marker table           |
| ODEF/OBJ                  | class 0x01                   | label.vcf                            |
| ODEF/OBJ                  | class 0x08 / 0x09            | label.vcf                            |
| ODEF/OBJ                  | 0x02/0x03/0x04               | label.sdf                            |
| ODEF/OBJ                  | 0x07/0x0a/0x0b/0x0c          | label.sdf                            |
| ODEF/OBJ                  | 0x50/0x52/0x53               | label.sdf                            |
| ODEF/OBJ                  | 0x05/0x06/0x0d..0x4f/0x51    | fallback/null-ish diagnostic         |
| ODEF/OBJ                  | class 0 / blank              | invalid/special diagnostic rows      |
| LDEF/OBJ                  | all normal records           | label.sdf                            |
| SDF child SOBJ/SGEO       | child part name              | partName.geo                         |
+---------------------------+-----------------------------+--------------------------------------+
```

Do not use either simplified rule:

```text
all ODEF -> .vcf
all ODEF -> .sdf
```

Both are wrong.

## Binary Evidence

```text
+----------+-------------------------------------------------------------+
| Address  | Evidence                                                     |
+----------+-------------------------------------------------------------+
| 004b7ac0 | Main ODEF/OBJ handler                                        |
| 004b7b96 | VCF case body; formats ".vcf" and loads vehicle config       |
| 004b7be9 | SDF case body; formats ".sdf" and parses descriptor table    |
| 00450f90 | spawn/regen table writer                                     |
| 004b8f70 | LDEF/OBJ static scene-object handler; formats ".sdf"         |
| 004b8470 | SOBJ child loader; formats ".geo"                            |
| 00500b18 | SDF child descriptor table                                   |
+----------+-------------------------------------------------------------+
```

## Practical Static Resolution Chain

```text
MSN BWD2
  -> ODEF/LDEF OBJ records
  -> class policy
  -> root .sdf
  -> parse SDF SGEO declared parts
  -> partName.geo
  -> embedded PIX/PAK/ZFS lookup
  -> GEO parse
  -> OBJ static scene assembly
```

## Current Validation State

```text
+------------------------------+-----------------------------------------------------------+
| Stage                        | Status                                                    |
+------------------------------+-----------------------------------------------------------+
| Mission BWD2 parsing         | Working                                                   |
| Root SDF/VCF resolution      | Working; unresolved policy resources currently zero       |
| SGEO declared part parsing   | Working                                                   |
| Embedded GEO lookup          | Working                                                   |
| Static mesh OBJ output       | Working                                                   |
| Static materials             | Working with VQM-first + family overrides                 |
| RSEG roads                   | Not part of ODEF/SDF; separate unresolved road pipeline    |
+------------------------------+-----------------------------------------------------------+
```
