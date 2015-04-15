/* This header is used in place of the nanovg.h and nanovg_gl.h */
#ifndef MRB_NVG_H
#define MRB_NVG_H

#include <GL/glew.h>
#include <nanovg.h>
#include <nanovg_gl.h>

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * We included just the barebones nanovg_gl header, so we'll need a extern to the
 * context constructor and destructor.
 * Reason for not calling it with a IMPLEMENTATION flag is to avoid redefintions.
 */
NVGcontext* nvgCreateGL2(int flags);
void nvgDeleteGL2(NVGcontext* ctx);

#ifdef __cplusplus
}
#endif
#endif
