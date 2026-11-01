/* Source-oriented layout notation only; addresses are 32-bit guest values. */
#ifndef I76_CONSOLIDATED_LAYOUTS_H
#define I76_CONSOLIDATED_LAYOUTS_H
#include <stdint.h>
#include <stddef.h>
typedef struct { float x, y, z; } I76TerNormal;
typedef struct { uint16_t samples[128][128]; } I76TerPage;
typedef struct { uint32_t kind, payload; } I76VmToken;
typedef struct {
    uint32_t workspace_words[1024], host_words[40], condition;
    uint32_t token_base, entry_index_or_live_ip, frame;
    uint32_t operand_cursor, host_cursor, next;
} I76VmNode32;
_Static_assert(sizeof(I76TerNormal)==12,"normal");
_Static_assert(sizeof(I76TerPage)==0x8000,"page");
_Static_assert(sizeof(I76VmToken)==8,"token");
_Static_assert(sizeof(I76VmNode32)==0x10bc,"node");
#define CHECK(F,O) _Static_assert(offsetof(I76VmNode32,F)==O,#F)
CHECK(host_words,0x1000); CHECK(condition,0x10a0); CHECK(token_base,0x10a4);
CHECK(entry_index_or_live_ip,0x10a8); CHECK(frame,0x10ac);
CHECK(operand_cursor,0x10b0); CHECK(host_cursor,0x10b4); CHECK(next,0x10b8);
#undef CHECK
/* 004931C0: explicit out at +4, X double +8, Z double +16; EAX = out.
 * Source declaration is unknown; use four-byte x86 stack packing in Ghidra.
 * The five RES records remain separate proposals in Pilot C resource_design.h.
 * No common runtime object, host service bundle, or modern implementation is implied.
 */
#endif
