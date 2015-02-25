#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include "nvg_color.h"
#include "mrb_helper_macros.h"

static struct RClass *nvg_color_class;

void
mrb_nvg_color_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

const struct mrb_data_type mrb_nvg_color_type = { "NVGcolor", mrb_nvg_color_free };

static inline NVGcolor*
get_color(mrb_state *mrb, mrb_value self)
{
  return (NVGcolor*)mrb_data_get_ptr(mrb, self, &mrb_nvg_color_type);
}

mrb_value
mrb_nvg_color_value(mrb_state *mrb, NVGcolor color)
{
  mrb_value result = mrb_obj_new(mrb, nvg_color_class, 0, NULL);
  NVGcolor *ncolor = DATA_PTR(result);
  *ncolor = color;
  return result;
}

static mrb_value
color_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float r = 0.0;
  mrb_float g = 0.0;
  mrb_float b = 0.0;
  mrb_float a = 0.0;
  NVGcolor *color;
  mrb_get_args(mrb, "|ffff", &r, &g, &b, &a);
  color = mrb_malloc(mrb, sizeof(NVGcolor));
  color->r = (float)r;
  color->g = (float)g;
  color->b = (float)b;
  color->a = (float)a;
  DATA_PTR(self) = color;
  DATA_TYPE(self) = &mrb_nvg_color_type;
  return self;
}

static mrb_value
color_initialize_copy(mrb_state *mrb, mrb_value self)
{
  NVGcolor *src;
  NVGcolor *color;
  mrb_get_args(mrb, "d", &src, &mrb_nvg_color_type);
  color = mrb_malloc(mrb, sizeof(NVGcolor));
  *color = *src;
  if (DATA_PTR(self)) {
    mrb_nvg_color_free(mrb, DATA_PTR(self));
  }
  DATA_PTR(self) = color;
  DATA_TYPE(self) = &mrb_nvg_color_type;
  return self;
}

#define ATTR_GET(_name_)                                                      \
static mrb_value                                                              \
color_get_ ## _name_(mrb_state *mrb, mrb_value self)                          \
{                                                                             \
  NVGcolor *color = get_color(mrb, self);                                     \
  return mrb_float_value(mrb, (mrb_float)color->_name_);                      \
}

#define ATTR_SET(_name_)                                                      \
static mrb_value                                                              \
color_set_ ## _name_(mrb_state *mrb, mrb_value self)                          \
{                                                                             \
  NVGcolor *color;                                                            \
  mrb_float n;                                                                \
  mrb_get_args(mrb, "f", &n);                                                 \
  color = get_color(mrb, self);                                               \
  color->_name_ = (float)n;                                                   \
  return mrb_nil_value();                                                     \
}

ATTR_GET(r);
ATTR_GET(g);
ATTR_GET(b);
ATTR_GET(a);

ATTR_SET(r);
ATTR_SET(g);
ATTR_SET(b);
ATTR_SET(a);

static mrb_value
color_to_a(mrb_state *mrb, mrb_value self)
{
  NVGcolor *color = get_color(mrb, self);
  mrb_value argv[4];
  argv[0] = mrb_float_value(mrb, (mrb_float)color->r);
  argv[1] = mrb_float_value(mrb, (mrb_float)color->g);
  argv[2] = mrb_float_value(mrb, (mrb_float)color->b);
  argv[3] = mrb_float_value(mrb, (mrb_float)color->a);
  return mrb_ary_new_from_values(mrb, 4, argv);
}

static mrb_value
color_s_new_rgb(mrb_state *mrb, mrb_value klass)
{
  mrb_int r;
  mrb_int g;
  mrb_int b;
  mrb_get_args(mrb, "iii", &r, &g, &b);
  return mrb_nvg_color_value(mrb, nvgRGB(r, g, b));
}

static mrb_value
color_s_new_rgbf(mrb_state *mrb, mrb_value klass)
{
  mrb_float r;
  mrb_float g;
  mrb_float b;
  mrb_get_args(mrb, "fff", &r, &g, &b);
  return mrb_nvg_color_value(mrb, nvgRGBf(r, g, b));
}

static mrb_value
color_s_new_rgba(mrb_state *mrb, mrb_value klass)
{
  mrb_int r;
  mrb_int g;
  mrb_int b;
  mrb_int a;
  mrb_get_args(mrb, "iiii", &r, &g, &b, &a);
  return mrb_nvg_color_value(mrb, nvgRGBA(r, g, b, a));
}

static mrb_value
color_s_new_rgbaf(mrb_state *mrb, mrb_value klass)
{
  mrb_float r;
  mrb_float g;
  mrb_float b;
  mrb_float a;
  mrb_get_args(mrb, "ffff", &r, &g, &b, &a);
  return mrb_nvg_color_value(mrb, nvgRGBAf(r, g, b, a));
}

static mrb_value
color_s_new_hsl(mrb_state *mrb, mrb_value klass)
{
  mrb_float h;
  mrb_float s;
  mrb_float l;
  mrb_get_args(mrb, "fff", &h, &s, &l);
  return mrb_nvg_color_value(mrb, nvgHSL(h, s, l));
}

static mrb_value
color_s_new_hsla(mrb_state *mrb, mrb_value klass)
{
  mrb_float h;
  mrb_float s;
  mrb_float l;
  mrb_float a;
  mrb_get_args(mrb, "ffff", &h, &s, &l, &a);
  return mrb_nvg_color_value(mrb, nvgHSLA(h, s, l, a));
}

static mrb_value
color_s_lerp_rgba(mrb_state *mrb, mrb_value klass)
{
  NVGcolor *c0;
  NVGcolor *c1;
  mrb_float u;
  mrb_get_args(mrb, "ddf", &c0, &mrb_nvg_color_type,
                           &c1, &mrb_nvg_color_type,
                           &u);
  return mrb_nvg_color_value(mrb, nvgLerpRGBA(*c0, *c1, u));
}

static mrb_value
color_s_trans(mrb_state *mrb, mrb_value klass)
{
  NVGcolor *c0;
  mrb_int a;
  mrb_get_args(mrb, "di", &c0, &mrb_nvg_color_type,
                          &a);
  return mrb_nvg_color_value(mrb, nvgTransRGBA(*c0, a));
}

static mrb_value
color_s_transf(mrb_state *mrb, mrb_value klass)
{
  NVGcolor *c0;
  mrb_float a;
  mrb_get_args(mrb, "df", &c0, &mrb_nvg_color_type,
                          &a);
  return mrb_nvg_color_value(mrb, nvgTransRGBAf(*c0, a));
}

void
mrb_nvg_color_init(mrb_state *mrb, struct RClass *nvg_module)
{
  nvg_color_class = mrb_define_class_under(mrb, nvg_module, "Color", mrb->object_class);
  MRB_SET_INSTANCE_TT(nvg_color_class, MRB_TT_DATA);

  mrb_define_method(mrb, nvg_color_class, "initialize", color_initialize, MRB_ARGS_ANY());
  mrb_define_method(mrb, nvg_color_class, "initialize_copy", color_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_color_class, "r",    color_get_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_color_class, "g",    color_get_g, MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_color_class, "b",    color_get_b, MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_color_class, "a",    color_get_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_color_class, "r=",   color_set_r, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_color_class, "g=",   color_set_g, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_color_class, "b=",   color_set_b, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_color_class, "a=",   color_set_a, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_color_class, "to_a", color_to_a,  MRB_ARGS_NONE());

  mrb_define_class_method(mrb, nvg_color_class, "rgb",       color_s_new_rgb,   MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, nvg_color_class, "rgbf",      color_s_new_rgbf,  MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, nvg_color_class, "rgba",      color_s_new_rgba,  MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, nvg_color_class, "rgbaf",     color_s_new_rgbaf, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, nvg_color_class, "hsl",       color_s_new_hsl,   MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, nvg_color_class, "hsla",      color_s_new_hsla,  MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, nvg_color_class, "lerp_rgba", color_s_lerp_rgba, MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, nvg_color_class, "trans",     color_s_trans,     MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, nvg_color_class, "transf",    color_s_transf,    MRB_ARGS_REQ(2));
}
