/*
 * Interstate '76 research C layout sketch (v100), NOT recovered source.
 * Original retail i76.exe: SHA-256 bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3
 * Evidence: accepted jf-stargate/i76 research/promotions #58, #62, #66-#70, #73-#81, #83-#84.
 * C99 fixed-width layout reference ONLY; addresses are stored as 32-bit integers so
 * the layout can be checked on 64-bit workstations. NOT an implementation ABI header.
 * Unknown members and original source identifiers are NOT inferred.
 */
#ifndef I76_READABILITY_V100_H
#define I76_READABILITY_V100_H
#include <stdint.h>
#include <stddef.h>

typedef uint32_t I76Addr32;  /* original x86 pointer storage: resolve against retail image */

typedef struct I76_CameraView_0x1D8 {
    float viewport_center_x;          /* 0x000 */
    float viewport_center_y;          /* 0x004 */
    float projection_scale_x;         /* 0x008 */
    float projection_scale_y;         /* 0x00c */
    uint8_t unknown_0x010[0x0c];
    float viewport_min_x;             /* 0x01c */
    float viewport_min_y;             /* 0x020 */
    float viewport_max_x;             /* 0x024 */
    float viewport_max_y;             /* 0x028 */
    float fov_tangent;                /* 0x02c */
    float aspect;                     /* 0x030 */
    float zoom;                       /* 0x034 */
    uint8_t unknown_0x038[0x04];
    I76Addr32 viewport_context_ptr;  /* 0x03c */
    float inverse_orientation_3x3[9];/* 0x040; basis order remains reference-defined */
    uint8_t unknown_0x064[0x04];
    double inverse_translation_x;     /* 0x068 */
    double inverse_translation_y;     /* 0x070 */
    double inverse_translation_z;     /* 0x078 */
    double world_aabb_center_x;       /* 0x080 */
    double world_aabb_center_y;       /* 0x088 */
    double world_aabb_center_z;       /* 0x090 */
    double world_bounding_radius;     /* 0x098 */
    uint8_t frustum_plane_raw[0x60]; /* 0x0a0; deliberately not fully typed */
    uint8_t local_corner_prefix[0x08]; /* 0x100 */
    float near_clip_z;                /* 0x108; 0.1 in tested M06 fixture */
    uint8_t local_corner_unknown0[0x2c];
    float far_clip_z;                 /* 0x138; 150 in tested M06 fixture */
    uint8_t local_corner_unknown1[0x24];
    double source_camera_x;           /* 0x160 */
    double source_camera_y;           /* 0x168 */
    double source_camera_z;           /* 0x170 */
    double world_frustum_corners_4x3[12]; /* 0x178 */
} I76_CameraView_0x1D8;

typedef struct I76_SoftwareSurface_0x34 {
    uint32_t byte_pitch;              /* +0x00; 640 in tested fixture */
    uint32_t flags;                   /* +0x04; bit meanings unresolved */
    uint32_t caller_mode;             /* +0x08 */
    uint32_t pixel_count_div_4;       /* +0x0c */
    uint32_t pixel_count_mod_32;      /* +0x10 */
    I76Addr32 aligned_pixel_base;    /* +0x14 */
    I76Addr32 backing_allocation;    /* +0x18 */
    uint32_t x_offset_bytes;          /* +0x1c */
    uint32_t y_row_offset;            /* +0x20 */
    uint32_t max_x_inclusive;         /* +0x24 */
    uint32_t max_y_inclusive;         /* +0x28 */
    uint32_t owns_backing;            /* +0x2c; observed 1, not full teardown proof */
    uint32_t unknown_0x30;
} I76_SoftwareSurface_0x34;

typedef struct I76_SoftwareDrawCommand_0x60 {
    uint32_t call_color_control;      /* +0x00 */
    I76Addr32 next_command;          /* +0x04 */
    I76Addr32 span_callback;          /* +0x08 -> 0047CB00 in executed case */
    uint8_t unknown_0x0c[0x0c];
    float shade_plane_constant;       /* +0x18 */
    uint32_t control_word;            /* +0x1c */
    I76Addr32 left_edge_head;        /* +0x20 */
    I76Addr32 right_edge_head;       /* +0x24 */
    int32_t pending_packed_span;      /* +0x28; -1 at initialization */
    uint32_t unknown_0x2c;
    uint32_t extent_or_span_slot;     /* +0x30; phase-dependent integer OR address */
    uint32_t sequence_serial;         /* +0x34 */
    uint8_t unknown_0x38[0x20];
    float shade_gradient_x;           /* +0x58 */
    float shade_gradient_y;           /* +0x5c */
} I76_SoftwareDrawCommand_0x60;

typedef struct I76_RenderWorkKind6_0x44 {
    uint8_t unknown_0x00[0x0c];
    uint32_t record_kind;             /* +0x0c; observed 6 */
    uint32_t unknown_0x10;
    I76Addr32 next_record;           /* +0x14 */
    uint32_t unknown_0x18;
    I76Addr32 world_object_owner;    /* +0x1c */
    float camera_classified_x;        /* +0x20 */
    float camera_classified_y;        /* +0x24 */
    float camera_classified_z;        /* +0x28 */
    float bounding_radius;            /* +0x2c */
    uint32_t mode_selector;           /* +0x30; not bucket index */
    uint32_t flags;                   /* +0x34 */
    uint32_t pass_selector;           /* +0x38 */
    uint32_t cache_state;             /* +0x3c */
    I76Addr32 active_world_entry;    /* +0x40; kind-6 ONLY */
} I76_RenderWorkKind6_0x44;

typedef struct I76_TerrainAdaptiveLeaf_0x1C {
    uint8_t unknown_0x00[8];
    I76Addr32 next_leaf;              /* +0x08 */
    I76Addr32 edge_reverse_last;     /* +0x0c */
    I76Addr32 edge_forward_second;   /* +0x10 */
    I76Addr32 edge_forward_first;    /* +0x14 */
    I76Addr32 edge_reverse_third;    /* +0x18 */
} I76_TerrainAdaptiveLeaf_0x1C;

typedef struct I76_Class1Descriptor_0x34 {
    uint8_t unknown_0x00[8];
    I76Addr32 initialize_callback;    /* +0x08 -> 00463120 */
    I76Addr32 pre_update_callback;    /* +0x0c -> 00463800 */
    I76Addr32 post_update_callback;   /* +0x10 -> 00463950 (NOT +0x30's interior 004639A0) */
    uint8_t unknown_0x14[0x20];       /* other previously analyzed pointers intentionally unresolved */
} I76_Class1Descriptor_0x34;

/* Layout assertions are portable; they do NOT validate host callable ABI or original behavior. */
_Static_assert(sizeof(I76_CameraView_0x1D8) == 0x1d8, "camera size");
_Static_assert(offsetof(I76_CameraView_0x1D8, near_clip_z) == 0x108, "camera near offset");
_Static_assert(offsetof(I76_CameraView_0x1D8, far_clip_z) == 0x138, "camera far offset");
_Static_assert(offsetof(I76_CameraView_0x1D8, source_camera_x) == 0x160, "camera position offset");
_Static_assert(sizeof(I76_SoftwareSurface_0x34) == 0x34, "surface size");
_Static_assert(offsetof(I76_SoftwareSurface_0x34, aligned_pixel_base) == 0x14, "surface pixel base");
_Static_assert(sizeof(I76_SoftwareDrawCommand_0x60) == 0x60, "draw command size");
_Static_assert(offsetof(I76_SoftwareDrawCommand_0x60, shade_gradient_x) == 0x58, "draw gradient offset");
_Static_assert(sizeof(I76_RenderWorkKind6_0x44) == 0x44, "work kind-6 size");
_Static_assert(sizeof(I76_TerrainAdaptiveLeaf_0x1C) == 0x1c, "terrain leaf size");
_Static_assert(sizeof(I76_Class1Descriptor_0x34) == 0x34, "class descriptor size");

#endif /* I76_READABILITY_V100_H */
