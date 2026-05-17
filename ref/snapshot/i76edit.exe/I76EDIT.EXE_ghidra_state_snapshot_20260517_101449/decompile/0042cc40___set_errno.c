/*
 * Program: I76EDIT.EXE
 * Function: __set_errno
 * Entry: 0042cc40
 * Signature: errno_t __cdecl __set_errno(int _Value)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_errno
   
   Library: Visual Studio 1998 Release */

errno_t __cdecl __set_errno(int _Value)

{
  if (_Value == 1) {
    _DAT_00437ae4 = 0x21;
    return _Value;
  }
  if (1 < _Value) {
    if (3 < _Value) {
      return _Value;
    }
    _DAT_00437ae4 = 0x22;
  }
  return _Value;
}


