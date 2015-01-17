#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include "nvg_context.h"
#include "nvg_paint.h"
#include "nvg_color.h"


/* Used for generating functions which only take a context */
#define CONTEXT_FUNC_N0(mrb_name, nvg_name)                                   \
static mrb_value                                                              \
mrb_name(mrb_state *mrb, mrb_value self)                                      \
{                                                                             \
  NVGcontext *context;                                                        \
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);               \
  nvg_name(context);                                                          \
  return self;                                                                \
}

/* Used for generating functions that take a context and 1 parameter */
#define CONTEXT_FUNC_N1(mrb_name, nvg_name, p0, p0_type, p0_mrb_char)         \
static mrb_value                                                              \
mrb_name(mrb_state *mrb, mrb_value self)                                      \
{                                                                             \
  NVGcontext *context;                                                        \
  p0_type p0;                                                                 \
  mrb_get_args(mrb, p0_mrb_char, &p0);                                        \
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);               \
  nvg_name(context, p0);                                                      \
  return self;                                                                \
}

#define CONTEXT_FUNC_N_D(mrb_name, nvg_name, p0_mrb, p0_type, p0_nvg, p0_mrb_char, datatype) \
static mrb_value                                                                             \
mrb_name(mrb_state *mrb, mrb_value self)                                                     \
{                                                                                            \
  NVGcontext *context;                                                                       \
  p0_type p0_mrb;                                                                            \
  mrb_get_args(mrb, p0_mrb_char, &p0_mrb, datatype);                                         \
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);                              \
  nvg_name(context, p0_nvg);                                                                 \
  return self;                                                                               \
}

static struct RClass *mrb_nvg_context_class;

void
mrb_nvg_context_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    nvgDeleteGL2((NVGcontext*)ptr);
  }
}

struct mrb_data_type mrb_nvg_context_type = { "Nanovg::Context", mrb_nvg_context_free };

static mrb_value
context_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int flags;
  NVGcontext *context;
  mrb_get_args(mrb, "i", &flags);
  context = nvgCreateGL2(flags);
  DATA_PTR(self) = context;
  DATA_TYPE(self) = &mrb_nvg_context_type;
  return self;
}

static mrb_value
context_begin_frame(mrb_state *mrb, mrb_value self)
{
  mrb_int width;
  mrb_int height;
  mrb_float dpr;
  NVGcontext *context;
  mrb_get_args(mrb, "iif", &width, &height, &dpr);
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
  nvgBeginFrame(context, width, height, dpr);
  return self;
}

CONTEXT_FUNC_N0(context_cancel_frame, nvgCancelFrame);
CONTEXT_FUNC_N0(context_end_frame, nvgEndFrame);
CONTEXT_FUNC_N0(context_save, nvgSave);
CONTEXT_FUNC_N0(context_restore, nvgRestore);
CONTEXT_FUNC_N0(context_reset, nvgReset);

CONTEXT_FUNC_N_D(context_stroke_color, nvgStrokeColor, stroke_color, NVGcolor*, *stroke_color, "d", &mrb_nvg_color_type);
CONTEXT_FUNC_N_D(context_stroke_paint, nvgStrokePaint, stroke_paint, NVGpaint*, *stroke_paint, "d", &mrb_nvg_paint_type);
CONTEXT_FUNC_N_D(context_fill_color, nvgFillColor, fill_color, NVGcolor*, *fill_color, "d", &mrb_nvg_color_type);
CONTEXT_FUNC_N_D(context_fill_paint, nvgFillPaint, fill_paint, NVGpaint*, *fill_paint, "d", &mrb_nvg_paint_type);

CONTEXT_FUNC_N1(context_miter_limit, nvgMiterLimit, fill_paint, mrb_float, "f");
CONTEXT_FUNC_N1(context_stroke_width, nvgStrokeWidth, stroke_width, mrb_float, "f");
CONTEXT_FUNC_N1(context_line_cap, nvgLineCap, line_cap, mrb_int, "i");
CONTEXT_FUNC_N1(context_line_join, nvgLineJoin, line_join, mrb_int, "i");
CONTEXT_FUNC_N1(context_global_alpha, nvgGlobalAlpha, global_alpha, mrb_float, "f");

CONTEXT_FUNC_N0(context_reset_transform, nvgResetTransform);

static mrb_value
context_transform(mrb_state *mrb, mrb_value self)
{
  mrb_float a;
  mrb_float b;
  mrb_float c;
  mrb_float d;
  mrb_float e;
  mrb_float f;
  NVGcontext *context;
  mrb_get_args(mrb, "ffffff", &a, &b, &c, &d, &e, &f);
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
  nvgTransform(context, a, b, c, d, e, f);
  return self;
}

static mrb_value
context_translate(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  mrb_float y;
  NVGcontext *context;
  mrb_get_args(mrb, "ff", &x, &y);
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
  nvgTranslate(context, x, y);
  return self;
}

CONTEXT_FUNC_N1(context_rotate, nvgRotate, rotate, mrb_float, "f");
CONTEXT_FUNC_N1(context_skew_x, nvgSkewX, skew_x, mrb_float, "f");
CONTEXT_FUNC_N1(context_skew_y, nvgSkewY, skew_y, mrb_float, "f");

static mrb_value
context_scale(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  mrb_float y;
  NVGcontext *context;
  mrb_get_args(mrb, "ff", &x, &y);
  context = mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
  nvgScale(context, x, y);
  return self;
}

void
mrb_nvg_context_init(mrb_state *mrb, struct RClass *nvg_module)
{
  mrb_nvg_context_class = mrb_define_class_under(mrb, nvg_module, "Context", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_nvg_context_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_nvg_context_class, "initialize",      context_initialize,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "begin_frame",     context_begin_frame,     MRB_ARGS_REQ(3));
  mrb_define_method(mrb, mrb_nvg_context_class, "cancel_frame",    context_cancel_frame,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_context_class, "end_frame",       context_end_frame,       MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_context_class, "save",            context_save,            MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_context_class, "restore",         context_restore,         MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_context_class, "reset",           context_reset,           MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_nvg_context_class, "stroke_color",    context_stroke_color,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "stroke_paint",    context_stroke_paint,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "fill_color",      context_fill_color,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "fill_paint",      context_fill_paint,      MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_nvg_context_class, "miter_limit",     context_miter_limit,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "stroke_width",    context_stroke_width,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "line_cap",        context_line_cap,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "line_join",       context_line_join,       MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "global_alpha",    context_global_alpha,    MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb_nvg_context_class, "reset_transform", context_reset_transform, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_nvg_context_class, "transform",       context_transform,       MRB_ARGS_REQ(6));
  mrb_define_method(mrb, mrb_nvg_context_class, "translate",       context_translate,       MRB_ARGS_REQ(2));
  mrb_define_method(mrb, mrb_nvg_context_class, "rotate",          context_rotate,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "skew_x",          context_skew_x,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "skew_y",          context_skew_y,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_context_class, "scale",           context_scale,           MRB_ARGS_REQ(2));

  mrb_define_const(mrb, mrb_nvg_context_class, "ANTIALIAS",       mrb_fixnum_value(NVG_ANTIALIAS));
  mrb_define_const(mrb, mrb_nvg_context_class, "STENCIL_STROKES", mrb_fixnum_value(NVG_STENCIL_STROKES));
  mrb_define_const(mrb, mrb_nvg_context_class, "DEBUG",           mrb_fixnum_value(NVG_DEBUG));
}
