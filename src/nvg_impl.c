/* This will is simply here to get nanovg to build correctly into the gem...
 * Because the headers are a bag of spaghetti and static function defs...
 * And other nutty, scary things... */
#include "nvg_impl.h"
#if MRUBY_NANOVG_GL2
#  define NANOVG_GL2_IMPLEMENTATION // Use GL2 implementation.
#elif MRUBY_NANOVG_GL3
#  define NANOVG_GL3_IMPLEMENTATION // Use GL3 implementation.
#elif MRUBY_NANOVG_GLES2
#  define NANOVG_GLES2_IMPLEMENTATION // Use GLES2 implementation.
#elif MRUBY_NANOVG_GLES3
#  define NANOVG_GLES3_IMPLEMENTATION // Use GLES3 implementation.
#else
#  error mruby-nanovg: You forgot to set a MRUBY_NANOVG_GL define!
#endif
#include <nanovg_gl.h>
