
#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>
#include <stdbool.h>
#include <math.h>

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t    i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef float    f32;
typedef double   f64;

typedef struct vec2{
  f32 x;
  f32 y;
} vec2;

#define neg_vec2(v)      (vec2) {-v.x, -v.y}
#define add_vec2(v, u)   (vec2) { v.x + u.x, v.y + u.y }
#define scale_vec2(v, A) (vec2) { v.x * A, v.y * A }
#define dist_vec2(v, u)  (f32) sqrt( (v.x - u.x)*(v.x - u.x) + (v.y - u.y)*(v.y - u.y) )

typedef struct t_color{
  u32 r;
  u32 g;
  u32 b;
  u32 a;
} t_color;

#define rgb_color(r, g, b) (t_color) {r, g, b, 255};
#define rgba_color(r, g, b, a) (t_color) {r, g, b, a};

typedef struct t_node {
  vec2 pos;
  bool ready;
  f32 anim_counter;
  f32 duration;
  int  id;
} t_node;

typedef struct t_vertex {
  t_node node_1;
  t_node node_2;
  float  dist;
} t_vertex;

#endif
