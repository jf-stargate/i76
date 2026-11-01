/* Research layout notation, not a resource-manager implementation.
 * VA fields represent original 32-bit pointers, not host-dereferenceable pointers.
 * Names are proposed descriptive aliases, not recovered source symbols. */
#ifndef PILOT_C_RESOURCE_DESIGN_H
#define PILOT_C_RESOURCE_DESIGN_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
typedef uint32_t va32;
typedef struct {
    char name[16];                 /* +00; only 15 bytes copied on cache insertion */
    int32_t allocation_payload_size; /* +10; size queried before loading */
    uint16_t references;           /* +14 */
    uint16_t unknown_16;           /* +16; not initialized by inspected insertion */
    va32 hash_next;                /* +18 */
    va32 purge_toward_newer;        /* +1c */
    va32 purge_toward_older;        /* +20 */
    uint8_t payload[];             /* +24; returned address */
} LoadedFile32;
typedef struct {
    char member_key[16];           /* +00; lowercased, zero-initialized by PIX parser */
    uint32_t package_index;        /* +10 */
    int32_t offset;                /* +14; added to cached PAK byte pointer */
    int32_t length;                /* +18; size helper, not checked by acquire */
} PixMember32;
typedef struct {
    char package_name[16];         /* +00; filename of sibling .pak, not member */
    va32 loaded_package_bytes;     /* +10; points to LoadedFile32.payload */
    uint32_t member_references;    /* +14; shared across members in this PAK */
} PakRetention32;
typedef struct {
    char key[16];                  /* +00 */
    uint32_t source_membership[8]; /* +10..2f; up to 256 source rows */
} RegisteredKey32;
typedef struct {
    char path[256];                /* +00 */
    int32_t path_mode;             /* +100; zero uses root/CD-relative formatting */
    int32_t root_index;            /* +104; also compared with current-media selector */
    va32 cached_zfs_handle;        /* +108 */
} MountedSource32;
#define OFFSET(T,F,N) _Static_assert(offsetof(T,F)==(N), #T "." #F)
OFFSET(LoadedFile32,allocation_payload_size,0x10);
OFFSET(LoadedFile32,references,0x14); OFFSET(LoadedFile32,unknown_16,0x16);
OFFSET(LoadedFile32,hash_next,0x18); OFFSET(LoadedFile32,purge_toward_newer,0x1c);
OFFSET(LoadedFile32,purge_toward_older,0x20); OFFSET(LoadedFile32,payload,0x24);
OFFSET(PixMember32,package_index,0x10); OFFSET(PixMember32,offset,0x14); OFFSET(PixMember32,length,0x18);
OFFSET(PakRetention32,loaded_package_bytes,0x10); OFFSET(PakRetention32,member_references,0x14);
OFFSET(RegisteredKey32,source_membership,0x10);
OFFSET(MountedSource32,path_mode,0x100); OFFSET(MountedSource32,root_index,0x104); OFFSET(MountedSource32,cached_zfs_handle,0x108);
_Static_assert(sizeof(LoadedFile32)==0x24,"loaded header");
_Static_assert(sizeof(PixMember32)==0x1c,"PIX row");
_Static_assert(sizeof(PakRetention32)==0x18,"PAK retention");
_Static_assert(sizeof(RegisteredKey32)==0x30,"registered key");
_Static_assert(sizeof(MountedSource32)==0x10c,"mounted source");
#undef OFFSET
/* Semantic ABI proposals for the original 32-bit cdecl functions.
 * These declarations intentionally have no maintained implementations. */
uint8_t *res_acquire(const char *logical_name);                 /* 0046ffc0 */
uint8_t *res_acquire_loaded_file(const char *logical_name);     /* 00470070 */
bool res_is_indexed_or_registered(const char *logical_name);   /* 00470340 */
uint8_t *res_acquire_pix_member(const char *key16);             /* 00470b20 */
MountedSource32 *res_select_source(const char *key16);         /* 004b2e00 */
uint8_t *res_read_registered(const char *key16, uint32_t *out_size,
                           uint8_t *destination, int32_t capacity); /* 004b3030 */
#endif
