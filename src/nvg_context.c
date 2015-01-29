#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/array.h>

#include "nvg_private.h"
#include "nvg_context.h"
#include "nvg_color.h"
#include "nvg_paint.h"
#include "nvg_transform.h"


/* Used for generating functions which only take a context */
#define DEFINE_FUNC_N0_HEAD(_mrb_name_, _func_name_) \
static mrb_value                           \
_mrb_name_(mrb_state *mrb, mrb_value self) \
{                                          \
  NVGcontext *context;                     \
  context = get_context(mrb, self)

#define DEFINE_FUNC_N0(_mrb_name_, _func_name_) \
DEFINE_FUNC_N0_HEAD(_mrb_name_, _func_name_); \
  _func_name_(context);                    \
  return self;                             \
}

#define DEFINE_FUNC_N0_i(_mrb_name_, _func_name_) \
DEFINE_FUNC_N0_HEAD(_mrb_name_, _func_name_); \
  return mrb_fixnum_value(_func_name_(context)); \
}

#define DEFINE_FUNC_N0_f(_mrb_name_, _func_name_) \
DEFINE_FUNC_N0_HEAD(_mrb_name_, _func_name_); \
  return mrb_float_value(mrb, _func_name_(context)); \
}

/* Used for generating functions that take a context and 1 parameter */
#define DEFINE_FUNC_N1_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_) \
static mrb_value                           \
_mrb_name_(mrb_state *mrb, mrb_value self) \
{                                          \
  NVGcontext *context;                     \
  _p0_type_ _p0_;                          \
  mrb_get_args(mrb, _fmt_, &_p0_);         \
  context = get_context(mrb, self)

#define DEFINE_FUNC_N1(_mrb_name_, _func_name_, _fmt_, _p0_type_) \
DEFINE_FUNC_N1_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_); \
  _func_name_(context, _p0_); \
  return self;                \
}

#define DEFINE_FUNC_N1_i(_mrb_name_, _func_name_, _fmt_, _p0_type_) \
DEFINE_FUNC_N1_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_); \
  return mrb_fixnum_value(_func_name_(context, _p0_));     \
}

#define DEFINE_FUNC_N1_f(_mrb_name_, _func_name_, _fmt_, _p0_type_) \
DEFINE_FUNC_N1_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_); \
  return mrb_float_value(mrb, _func_name_(context, _p0_));     \
}

#define DEFINE_FUNC_N2_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_) \
static mrb_value                           \
_mrb_name_(mrb_state *mrb, mrb_value self) \
{                                          \
  NVGcontext *context;                     \
  _p0_type_ _p0_;                          \
  _p1_type_ _p1_;                          \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_);  \
  context = get_context(mrb, self)

#define DEFINE_FUNC_N2(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_) \
DEFINE_FUNC_N2_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_); \
  _func_name_(context, _p0_, _p1_); \
  return self;                      \
}

#define DEFINE_FUNC_N2_i(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_) \
DEFINE_FUNC_N2_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_); \
  return mrb_fixnum_value(_func_name_(context, _p0_, _p1_)); \
}

#define DEFINE_FUNC_N3_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
static mrb_value                                 \
_mrb_name_(mrb_state *mrb, mrb_value self)       \
{                                                \
  NVGcontext *context;                           \
  _p0_type_ _p0_;                                \
  _p1_type_ _p1_;                                \
  _p2_type_ _p2_;                                \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_); \
  context = get_context(mrb, self)

#define DEFINE_FUNC_N3(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
DEFINE_FUNC_N3_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_); \
  _func_name_(context, _p0_, _p1_, _p2_);        \
  return self;                                   \
}

#define DEFINE_FUNC_N3_f(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
DEFINE_FUNC_N3_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_); \
  return mrb_float_value(mrb, _func_name_(context, _p0_, _p1_, _p2_));        \
}

#define DEFINE_FUNC_N4_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
static mrb_value                                        \
_mrb_name_(mrb_state *mrb, mrb_value self)              \
{                                                       \
  NVGcontext *context;                                  \
  _p0_type_ _p0_;                                       \
  _p1_type_ _p1_;                                       \
  _p2_type_ _p2_;                                       \
  _p3_type_ _p3_;                                       \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_); \
  context = get_context(mrb, self)

#define DEFINE_FUNC_N4(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
DEFINE_FUNC_N4_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_); \
  _func_name_(context, _p0_, _p1_, _p2_, _p3_);         \
  return self;                                          \
}

#define DEFINE_FUNC_N4_i(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
DEFINE_FUNC_N4_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_); \
  return mrb_fixnum_value(_func_name_(context, _p0_, _p1_, _p2_, _p3_)); \
}

#define DEFINE_FUNC_N4_f(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
DEFINE_FUNC_N4_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_); \
  return mrb_float_value(mrb, _func_name_(context, _p0_, _p1_, _p2_, _p3_)); \
}

#define DEFINE_FUNC_N5_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
static mrb_value                                               \
_mrb_name_(mrb_state *mrb, mrb_value self)                     \
{                                                              \
  NVGcontext *context;                                         \
  _p0_type_ _p0_;                                              \
  _p1_type_ _p1_;                                              \
  _p2_type_ _p2_;                                              \
  _p3_type_ _p3_;                                              \
  _p4_type_ _p4_;                                              \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_); \
  context = get_context(mrb, self)


#define DEFINE_FUNC_N5(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
DEFINE_FUNC_N5_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_); \
  _func_name_(context, _p0_, _p1_, _p2_, _p3_, _p4_); \
  return self;                                        \
}

#define DEFINE_FUNC_N5_f(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
DEFINE_FUNC_N5_HEAD(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_); \
  return mrb_float_value(mrb, _func_name_(context, _p0_, _p1_, _p2_, _p3_, _p4_));          \
}

#define DEFINE_FUNC_N6(_mrb_name_, _func_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
static mrb_value                                                      \
_mrb_name_(mrb_state *mrb, mrb_value self)                            \
{                                                                     \
  NVGcontext *context;                                                \
  _p0_type_ _p0_;                                                     \
  _p1_type_ _p1_;                                                     \
  _p2_type_ _p2_;                                                     \
  _p3_type_ _p3_;                                                     \
  _p4_type_ _p4_;                                                     \
  _p5_type_ _p5_;                                                     \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_, &_p5_); \
  context = get_context(mrb, self);                                   \
  _func_name_(context, _p0_, _p1_, _p2_, _p3_, _p4_, _p5_);           \
  return self;                                                        \
}

/* Used for generating context functions which take 1 data parameter */
#define DEFINE_FUNC_ND(_mrb_name_, _func_name_, _p0_mrb_, _p0_type_, _p0_mrb_datatype_, _p0_nvg_) \
static mrb_value                                        \
_mrb_name_(mrb_state *mrb, mrb_value self)              \
{                                                       \
  NVGcontext *context;                                  \
  _p0_type_ _p0_mrb_;                                   \
  mrb_get_args(mrb, "d", &_p0_mrb_, _p0_mrb_datatype_); \
  context = get_context(mrb, self);                     \
  _func_name_(context, _p0_nvg_);                       \
  return self;                                          \
}

/* If a helper wasn't found here, you most likely have to write the function yourself */

/* END OF CONTEXT MACROS */

/* patched function */
static inline float
nvgText_mrb(NVGcontext *context, float x, float y, const char *string)
{
  return nvgText(context, x, y, string, NULL);
}

static inline void
nvgTextBox_mrb(NVGcontext *context, float x, float y, float breakRowWidth, const char *string)
{
  nvgTextBox(context, x, y, breakRowWidth, string, NULL);
}

static struct RClass *nvg_context_class;

void
mrb_nvg_context_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    nvgDeleteGL2((NVGcontext*)ptr);
  }
}

const struct mrb_data_type mrb_nvg_context_type = { "NVGcontext", mrb_nvg_context_free };

static inline NVGcontext*
get_context(mrb_state *mrb, mrb_value self)
{
  return (NVGcontext*)mrb_data_get_ptr(mrb, self, &mrb_nvg_context_type);
}

static mrb_value
context_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int flags;
  NVGcontext *context;
  mrb_get_args(mrb, "i", &flags);
  context = nvgCreateGL2(flags);
  if (!context) {
    mrb_raise(mrb, E_NVG_ERROR, "Could not create Context.");
  }
  DATA_PTR(self) = context;
  DATA_TYPE(self) = &mrb_nvg_context_type;
  return self;
}

DEFINE_FUNC_N3(context_begin_frame, nvgBeginFrame, "iif", mrb_int, mrb_int, mrb_float);
DEFINE_FUNC_N0(context_cancel_frame, nvgCancelFrame);
DEFINE_FUNC_N0(context_end_frame, nvgEndFrame);
DEFINE_FUNC_N0(context_save, nvgSave);
DEFINE_FUNC_N0(context_restore, nvgRestore);
DEFINE_FUNC_N0(context_reset, nvgReset);

DEFINE_FUNC_ND(context_stroke_color, nvgStrokeColor, stroke_color, NVGcolor*, &mrb_nvg_color_type, *stroke_color);
DEFINE_FUNC_ND(context_stroke_paint, nvgStrokePaint, stroke_paint, NVGpaint*, &mrb_nvg_paint_type, *stroke_paint);
DEFINE_FUNC_ND(context_fill_color, nvgFillColor, fill_color, NVGcolor*, &mrb_nvg_color_type, *fill_color);
DEFINE_FUNC_ND(context_fill_paint, nvgFillPaint, fill_paint, NVGpaint*, &mrb_nvg_paint_type, *fill_paint);
DEFINE_FUNC_N1(context_miter_limit, nvgMiterLimit, "f", mrb_float);
DEFINE_FUNC_N1(context_stroke_width, nvgStrokeWidth, "f", mrb_float);
DEFINE_FUNC_N1(context_line_cap, nvgLineCap, "i", mrb_int);
DEFINE_FUNC_N1(context_line_join, nvgLineJoin, "i", mrb_int);
DEFINE_FUNC_N1(context_global_alpha, nvgGlobalAlpha, "f", mrb_float);

DEFINE_FUNC_N0(context_reset_transform, nvgResetTransform);
DEFINE_FUNC_N6(context_transform, nvgTransform, "ffffff", mrb_float, mrb_float, mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N2(context_translate, nvgTranslate, "ff", mrb_float, mrb_float);
DEFINE_FUNC_N1(context_rotate, nvgRotate, "f", mrb_float);
DEFINE_FUNC_N1(context_skew_x, nvgSkewX, "f", mrb_float);
DEFINE_FUNC_N1(context_skew_y, nvgSkewY, "f", mrb_float);
DEFINE_FUNC_N2(context_scale, nvgScale, "ff", mrb_float, mrb_float);

static mrb_value
context_current_transform(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  NVGtransform *t;
  mrb_get_args(mrb, "d", &t, &mrb_nvg_transform_type);
  context = get_context(mrb, self);
  nvgCurrentTransform(context, &t->ary[0]);
  return self;
}

static mrb_value
context_create_image(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  char *filename;
  mrb_int flags;
  int image;
  mrb_get_args(mrb, "zi", &filename, &flags);
  context = get_context(mrb, self);
  image = nvgCreateImage(context, filename, flags);
  return mrb_fixnum_value(image);
}

static mrb_value
context_create_image_mem(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int flags;
  char *data;
  mrb_int ndata;
  int image;
  mrb_get_args(mrb, "izi", &flags, &data, &ndata);
  context = get_context(mrb, self);
  image = nvgCreateImageMem(context, flags, (unsigned char*)data, ndata);
  return mrb_fixnum_value(image);
}

static mrb_value
context_create_image_rgba(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int w;
  mrb_int h;
  mrb_int flags;
  char *data;
  int image;
  mrb_get_args(mrb, "iiiz", &w, &h, &flags, &data);
  context = get_context(mrb, self);
  image = nvgCreateImageRGBA(context, w, h, flags, (unsigned char*)data);
  return mrb_fixnum_value(image);
}

static mrb_value
context_update_image(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int image;
  char *data;
  mrb_get_args(mrb, "iz", &image, &data);
  context = get_context(mrb, self);
  nvgUpdateImage(context, image, (unsigned char*)data);
  return mrb_fixnum_value(image);
}

static mrb_value
context_image_size(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_int image;
  mrb_value vals[2];
  int w;
  int h;
  mrb_get_args(mrb, "i", &image);
  context = get_context(mrb, self);
  nvgImageSize(context, image, &w, &h);
  vals[0] = mrb_fixnum_value(w);
  vals[1] = mrb_fixnum_value(h);
  return mrb_ary_new_from_values(mrb, 2, vals);
}

DEFINE_FUNC_N1(context_delete_image, nvgDeleteImage, "i", mrb_int);

DEFINE_FUNC_N4(context_scissor, nvgScissor, "ffff", mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N4(context_intersect_scissor, nvgIntersectScissor, "ffff", mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N0(context_reset_scissor, nvgResetScissor);

static mrb_value
context_linear_gradient(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float sx;
  mrb_float sy;
  mrb_float ex;
  mrb_float ey;
  NVGcolor *icol;
  NVGcolor *ocol;
  mrb_get_args(mrb, "ffffdd", &sx, &sy, &ex, &ey,
                              &icol, &mrb_nvg_color_type,
                              &ocol, &mrb_nvg_color_type);
  context = get_context(mrb, self);
  return mrb_nvg_paint_value(mrb, nvgLinearGradient(context, sx, sy, ex, ey, *icol, *ocol));
}

static mrb_value
context_box_gradient(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float x;
  mrb_float y;
  mrb_float w;
  mrb_float h;
  mrb_float r;
  mrb_float f;
  NVGcolor *icol;
  NVGcolor *ocol;
  mrb_get_args(mrb, "ffffffdd", &x, &y, &w, &h, &r, &f,
                                &icol, &mrb_nvg_color_type,
                                &ocol, &mrb_nvg_color_type);
  context = get_context(mrb, self);
  return mrb_nvg_paint_value(mrb, nvgBoxGradient(context, x, y, w, h, r, f, *icol, *ocol));
}

static mrb_value
context_radial_gradient(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float cx;
  mrb_float cy;
  mrb_float inr;
  mrb_float outr;
  NVGcolor *icol;
  NVGcolor *ocol;
  mrb_get_args(mrb, "ffffdd", &cx, &cy, &inr, &outr,
                              &icol, &mrb_nvg_color_type,
                              &ocol, &mrb_nvg_color_type);
  context = get_context(mrb, self);
  return mrb_nvg_paint_value(mrb, nvgRadialGradient(context, cx, cy, inr, outr, *icol, *ocol));
}

static mrb_value
context_image_pattern(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float ox;
  mrb_float oy;
  mrb_float ex;
  mrb_float ey;
  mrb_float angle;
  mrb_int image;
  mrb_float alpha;
  mrb_get_args(mrb, "fffffif", &ox, &oy, &ex, &ey, &angle, &image, &alpha);

  context = get_context(mrb, self);
  return mrb_nvg_paint_value(mrb, nvgImagePattern(context, ox, oy, ex, ey, angle, image, alpha));
}

DEFINE_FUNC_N0(context_begin_path, nvgBeginPath);
DEFINE_FUNC_N2(context_move_to, nvgMoveTo, "ff", mrb_float, mrb_float);
DEFINE_FUNC_N2(context_line_to, nvgLineTo, "ff", mrb_float, mrb_float);
DEFINE_FUNC_N6(context_bezier_to, nvgBezierTo, "ffffff", mrb_float, mrb_float, mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N4(context_quad_to, nvgQuadTo, "ffff", mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N5(context_arc_to, nvgArcTo, "fffff", mrb_float, mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N0(context_close_path, nvgClosePath);
DEFINE_FUNC_N1(context_path_winding, nvgPathWinding, "i", mrb_int);
DEFINE_FUNC_N6(context_arc, nvgArc, "fffffi", mrb_float, mrb_float, mrb_float, mrb_float, mrb_float, mrb_int);
DEFINE_FUNC_N4(context_rect, nvgRect, "ffff", mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N5(context_rounded_rect, nvgRoundedRect, "fffff", mrb_float, mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N4(context_ellipse, nvgEllipse, "ffff", mrb_float, mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N3(context_circle, nvgCircle, "fff", mrb_float, mrb_float, mrb_float);
DEFINE_FUNC_N0(context_fill, nvgFill);
DEFINE_FUNC_N0(context_stroke, nvgStroke);

DEFINE_FUNC_N2_i(context_create_font, nvgCreateFont, "zz", char*, char*);

static mrb_value
context_create_font_mem(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  char *name;
  char *data;
  mrb_int ndata;
  mrb_int free_data;
  mrb_get_args(mrb, "zzii", &name, &data, &ndata, &free_data);
  context = get_context(mrb, self);
  return mrb_fixnum_value(nvgCreateFontMem(context, name, (unsigned char*)data, ndata, free_data));
}

DEFINE_FUNC_N1_i(context_find_font, nvgFindFont, "z", char*);
DEFINE_FUNC_N1(context_font_size, nvgFontSize, "f", mrb_float);
DEFINE_FUNC_N1(context_font_blur, nvgFontBlur, "f", mrb_float);
DEFINE_FUNC_N1(context_text_letter_spacing, nvgTextLetterSpacing, "f", mrb_float);
DEFINE_FUNC_N1(context_text_line_height, nvgTextLineHeight, "f", mrb_float);
DEFINE_FUNC_N1(context_text_align, nvgTextAlign, "i", mrb_int);
DEFINE_FUNC_N1(context_font_face_id, nvgFontFaceId, "i", mrb_int);
DEFINE_FUNC_N1(context_font_face, nvgFontFace, "z", char*);

DEFINE_FUNC_N3_f(context_text, nvgText_mrb, "ffz", mrb_float, mrb_float, char*);
DEFINE_FUNC_N4(context_text_box, nvgTextBox_mrb, "fffz", mrb_float, mrb_float, mrb_float, char*);

static mrb_value
context_text_bounds(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float x;
  mrb_float y;
  char *str;
  NVGtransform *t;
  mrb_get_args(mrb, "ffzd", &x, &y, &str, &t, &mrb_nvg_transform_type);
  context = get_context(mrb, self);
  return mrb_float_value(mrb, nvgTextBounds(context, x, y, str, NULL, &t->ary[0]));
}

static mrb_value
context_text_box_bounds(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float x;
  mrb_float y;
  mrb_float brw;
  char *str;
  NVGtransform *t;
  mrb_get_args(mrb, "fffzd", &x, &y, &brw, &str, &t, &mrb_nvg_transform_type);
  context = get_context(mrb, self);
  nvgTextBoxBounds(context, x, y, brw, str, NULL, &t->ary[0]);
  return self;
}

/*static mrb_value
context_text_glyph_positions(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  mrb_float x;
  mrb_float y;
  char *str;
  char *end;
  mrb_int positions;
  mrb_int max_positions;
  mrb_get_args(mrb, "ffzzd", &x, &y, &brw, &str, &end, &t, &mrb_nvg_transform_type);
  context = get_context(mrb, self);
  nvgTextGlyphPositions(context, x, y, string, end, positions, max_positions);
  return self;
}*/

static mrb_value
context_text_metrics(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  float ascender;
  float descender;
  float lineh;
  mrb_value vals[3];
  context = get_context(mrb, self);
  nvgTextMetrics(context, &ascender, &descender, &lineh);
  vals[0] = mrb_float_value(mrb, ascender);
  vals[1] = mrb_float_value(mrb, descender);
  vals[2] = mrb_float_value(mrb, lineh);
  return mrb_ary_new_from_values(mrb, 3, vals);
}

/*static mrb_value
context_text_break_lines(mrb_state *mrb, mrb_value self)
{
  NVGcontext *context;
  char *str;
  char *end;
  mrb_int brw;
  NVGtextRow *rows;
  int max_rows;
  context = get_context(mrb, self);
  return mrb_fixnum_value(nvgTextBreakLines(context, str, end, brw, rows, max_rows));
}*/

void
mrb_nvg_context_init(mrb_state *mrb, struct RClass *nvg_module)
{
  nvg_context_class = mrb_define_class_under(mrb, nvg_module, "Context", mrb->object_class);
  MRB_SET_INSTANCE_TT(nvg_context_class, MRB_TT_DATA);

  mrb_define_method(mrb, nvg_context_class, "initialize",          context_initialize,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "begin_frame",         context_begin_frame,         MRB_ARGS_REQ(3));
  mrb_define_method(mrb, nvg_context_class, "cancel_frame",        context_cancel_frame,        MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "end_frame",           context_end_frame,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "save",                context_save,                MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "restore",             context_restore,             MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "reset",               context_reset,               MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "stroke_color",        context_stroke_color,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "stroke_paint",        context_stroke_paint,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "fill_color",          context_fill_color,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "fill_paint",          context_fill_paint,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "miter_limit",         context_miter_limit,         MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "stroke_width",        context_stroke_width,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "line_cap",            context_line_cap,            MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "line_join",           context_line_join,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "global_alpha",        context_global_alpha,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "reset_transform",     context_reset_transform,     MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "transform",           context_transform,           MRB_ARGS_REQ(6));
  mrb_define_method(mrb, nvg_context_class, "translate",           context_translate,           MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "rotate",              context_rotate,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "skew_x",              context_skew_x,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "skew_y",              context_skew_y,              MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "scale",               context_scale,               MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "current_transform",   context_current_transform,   MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "create_image",        context_create_image,        MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "create_image_mem",    context_create_image_mem,    MRB_ARGS_REQ(3));
  mrb_define_method(mrb, nvg_context_class, "create_image_rgba",   context_create_image_rgba,   MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "update_image",        context_update_image,        MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "image_size",          context_image_size,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "delete_image",        context_delete_image,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "scissor",             context_scissor,             MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "intersect_scissor",   context_intersect_scissor,   MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "reset_scissor",       context_reset_scissor,       MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "linear_gradient",     context_linear_gradient,     MRB_ARGS_REQ(6));
  mrb_define_method(mrb, nvg_context_class, "box_gradient",        context_box_gradient,        MRB_ARGS_REQ(8));
  mrb_define_method(mrb, nvg_context_class, "radial_gradient",     context_radial_gradient,     MRB_ARGS_REQ(6));
  mrb_define_method(mrb, nvg_context_class, "image_pattern",       context_image_pattern,       MRB_ARGS_REQ(7));
  mrb_define_method(mrb, nvg_context_class, "begin_path",          context_begin_path,          MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "move_to",             context_move_to,             MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "line_to",             context_line_to,             MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "bezier_to",           context_bezier_to,           MRB_ARGS_REQ(6));
  mrb_define_method(mrb, nvg_context_class, "quad_to",             context_quad_to,             MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "arc_to",              context_arc_to,              MRB_ARGS_REQ(5));
  mrb_define_method(mrb, nvg_context_class, "close_path",          context_close_path,          MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "path_winding",        context_path_winding,        MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "arc",                 context_arc,                 MRB_ARGS_REQ(6));
  mrb_define_method(mrb, nvg_context_class, "rect",                context_rect,                MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "rounded_rect",        context_rounded_rect,        MRB_ARGS_REQ(5));
  mrb_define_method(mrb, nvg_context_class, "ellipse",             context_ellipse,             MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "circle",              context_circle,              MRB_ARGS_REQ(3));
  mrb_define_method(mrb, nvg_context_class, "fill",                context_fill,                MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "stroke",              context_stroke,              MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "create_font",         context_create_font,         MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_context_class, "create_font_mem",     context_create_font_mem,     MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "find_font",           context_find_font,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_size",           context_font_size,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_blur",           context_font_blur,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text_letter_spacing", context_text_letter_spacing, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text_line_height",    context_text_line_height,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text_align",          context_text_align,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_face_id",        context_font_face_id,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_face",           context_font_face,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text",                context_text,                MRB_ARGS_REQ(3));
  mrb_define_method(mrb, nvg_context_class, "text_box",            context_text_box,            MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "text_bounds",         context_text_bounds,         MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "text_box_bounds",     context_text_box_bounds,     MRB_ARGS_REQ(5));

  /*mrb_define_method(mrb, nvg_context_class, "text_glyph_positions",context_text_glyph_positions,MRB_ARGS_REQ(6));*/
  mrb_define_method(mrb, nvg_context_class, "text_metrics",        context_text_metrics,        MRB_ARGS_NONE());
  /*mrb_define_method(mrb, nvg_context_class, "text_break_lines",    context_text_break_lines,    MRB_ARGS_REQ(5));*/
}
