#ifndef I76_OBJECT_DISPATCH_V101_H
#define I76_OBJECT_DISPATCH_V101_H
/* Research-derived layout sketch for human C reconstruction. NOT a source header from Activision.
 * Values are retail i76.exe 32-bit address slots, not host-native pointers.
 * Only evidence-backed offsets are typed; unknown fields remain opaque. */
#include <stddef.h>
#include <stdint.h>
typedef uint32_t I76Addr32;
#pragma pack(push,1)
typedef struct I76_WorldNode_0xB0 {
    uint8_t unknown_00_07[0x08];
    uint16_t logical_removal_state;         /* +08 */
    uint8_t unknown_0A_0B[2];
    uint32_t reference_count;               /* +0C */
    uint32_t status_flags;                  /* +10 */
    uint8_t unknown_14_17[4];
    float orientation_basis_3x3[9];         /* +18 */
    uint8_t unknown_3C_3F[4];
    double position_x;                      /* +40 */
    double position_y;                      /* +48 */
    double position_z;                      /* +50 */
    uint8_t unknown_58_5F[8];
    I76Addr32 sibling_or_preceding_link;    /* +60 */
    I76Addr32 last_child;                   /* +64; newest child */
    I76Addr32 context_link_mutable;         /* +68; NOT invariant parent */
    uint32_t class_id;                     /* +6C */
    I76Addr32 class_runtime;                /* +70; class-specific opaque runtime */
    uint8_t unknown_74_AF[0xB0-0x74];
} I76_WorldNode_0xB0;

typedef struct I76_ClassLinkNode_0x0C {
    I76Addr32 previous;                    /* +00 */
    I76Addr32 next;                        /* +04 */
    I76Addr32 payload;                     /* +08; enrolled => world handle, pending => enrolled-node */
} I76_ClassLinkNode_0x0C;

typedef struct I76_ActiveWorldEntry_0x78 {
    I76Addr32 world_object;                /* +00 */
    uint8_t unknown_04_13[0x10];
    uint32_t active_state;                 /* +14 */
    uint32_t registration_tag;             /* +18 */
    uint8_t unknown_1C_2F[0x14];
    uint32_t has_supplied_bounds_payload;  /* +30 */
    uint8_t unknown_34_77[0x78-0x34];
} I76_ActiveWorldEntry_0x78;
#pragma pack(pop)
_Static_assert(sizeof(I76_WorldNode_0xB0)==0xB0,"world node size");
_Static_assert(offsetof(I76_WorldNode_0xB0,orientation_basis_3x3)==0x18,"basis");
_Static_assert(offsetof(I76_WorldNode_0xB0,position_x)==0x40,"world pos");
_Static_assert(offsetof(I76_WorldNode_0xB0,last_child)==0x64,"latest child");
_Static_assert(offsetof(I76_WorldNode_0xB0,context_link_mutable)==0x68,"mutable context link");
_Static_assert(offsetof(I76_WorldNode_0xB0,class_id)==0x6C,"class id");
_Static_assert(offsetof(I76_WorldNode_0xB0,class_runtime)==0x70,"class runtime");
_Static_assert(sizeof(I76_ClassLinkNode_0x0C)==12,"class link size");
_Static_assert(offsetof(I76_ClassLinkNode_0x0C,payload)==8,"class link payload");
_Static_assert(sizeof(I76_ActiveWorldEntry_0x78)==0x78,"registry entry stride");
_Static_assert(offsetof(I76_ActiveWorldEntry_0x78,registration_tag)==0x18,"entry tag");
#endif