#ifndef MRUBY_NVG_IMPL_H
#define MRUBY_NVG_IMPL_H

#include <GL/glew.h>
#include <nanovg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* If none of the defines are set, assume GLES2 */
#ifndef MRUBY_NANOVG_GL2
#  ifndef MRUBY_NANOVG_GL3
#    ifndef MRUBY_NANOVG_GLES2
#      ifndef MRUBY_NANOVG_GLES3
#        define MRUBY_NANOVG_GLES2 1
#      endif
#    endif
#  endif
#endif

/*
 * We included just the barebones nanovg_gl header, so we'll need a extern to the
 * context constructor and destructor.
 * Reason for not calling it with a IMPLEMENTATION flag is to avoid redefintions.
 */
#if MRUBY_NANOVG_GL2
NVGcontext* nvgCreateGL2(int flags);
void nvgDeleteGL2(NVGcontext* ctx);
#elif MRUBY_NANOVG_GL3
NVGcontext* nvgCreateGL3(int flags);
void nvgDeleteGL3(NVGcontext* ctx);
#elif MRUBY_NANOVG_GLES2
NVGcontext* nvgCreateGLES2(int flags);
void nvgDeleteGLES2(NVGcontext* ctx);
#elif MRUBY_NANOVG_GLES3
NVGcontext* nvgCreateGLES3(int flags);
void nvgDeleteGLES3(NVGcontext* ctx);
#endif

static inline void
mrb_nvgDeleteGL(NVGcontext *ptr)
{
#if MRUBY_NANOVG_GL2
  nvgDeleteGL2(ptr);
#elif MRUBY_NANOVG_GL3
  nvgDeleteGL3(ptr);
#elif MRUBY_NANOVG_GLES2
  nvgDeleteGLES2(ptr);
#elif MRUBY_NANOVG_GLES3
  nvgDeleteGLES3(ptr);
#endif
}

static inline NVGcontext*
mrb_nvgCreateGL(int flags)
{
#if MRUBY_NANOVG_GL2
  return nvgCreateGL2(flags);
#elif MRUBY_NANOVG_GL3
  return nvgCreateGL3(flags);
#elif MRUBY_NANOVG_GLES2
  return nvgCreateGLES2(flags);
#elif MRUBY_NANOVG_GLES3
  return nvgCreateGLES3(flags);
#endif
}

#ifdef __cplusplus
}
#endif

#endif
