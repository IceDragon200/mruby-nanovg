#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include "nvg_transform.h"

static struct RClass *nvg_transform_class;

void
mrb_nvg_transform_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

const struct mrb_data_type mrb_nvg_transform_type = { "NVGtransform", mrb_nvg_transform_free };

mrb_value
mrb_nvg_transform_value(mrb_state *mrb, float *xform)
{
  NVGtransform *t;
  mrb_value transform = mrb_obj_new(mrb, nvg_transform_class, 0, NULL);
  t = mrb_data_get_ptr(mrb, transform, &mrb_nvg_transform_type);
  memcpy(&t->ary[0], xform, sizeof(float) * 6);
  return transform;
}

static mrb_value
transform_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float a = 0.0;
  mrb_float b = 0.0;
  mrb_float c = 0.0;
  mrb_float d = 0.0;
  mrb_float e = 0.0;
  mrb_float f = 0.0;
  NVGtransform *t;
  t = mrb_malloc(mrb, sizeof(NVGtransform));
  mrb_get_args(mrb, "|ffffff", &a, &b, &c, &d, &e, &f);
  t->a = a;
  t->b = b;
  t->c = c;
  t->d = d;
  t->e = e;
  t->f = f;
  DATA_PTR(self) = t;
  DATA_TYPE(self) = &mrb_nvg_transform_type;
  return self;
}

static mrb_value
transform_initialize_copy(mrb_state *mrb, mrb_value self)
{
  return self;
}

#define ATTR_GET(_name_)                                                      \
static mrb_value                                                              \
transform_get_ ## _name_(mrb_state *mrb, mrb_value self)                      \
{                                                                             \
  NVGtransform *transform;                                                    \
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);           \
  return mrb_float_value(mrb, transform->_name_);                             \
}

#define ATTR_SET(_name_)                                                      \
static mrb_value                                                              \
transform_set_ ## _name_(mrb_state *mrb, mrb_value self)                      \
{                                                                             \
  NVGtransform *transform;                                                    \
  mrb_float n;                                                                \
  mrb_get_args(mrb, "f", &n);                                                 \
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);           \
  transform->_name_ = (float)n;                                               \
  return mrb_nil_value();                                                     \
}

ATTR_GET(a);
ATTR_GET(b);
ATTR_GET(c);
ATTR_GET(d);
ATTR_GET(e);
ATTR_GET(f);

ATTR_SET(a);
ATTR_SET(b);
ATTR_SET(c);
ATTR_SET(d);
ATTR_SET(e);
ATTR_SET(f);

static mrb_value
transform_translate(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  mrb_float y;
  NVGtransform *transform;
  mrb_get_args(mrb, "ff", &x, &y);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformTranslate(&transform->ary[0], x, y);
  return self;
}

static mrb_value
transform_scale(mrb_state *mrb, mrb_value self)
{
  mrb_float sx;
  mrb_float sy;
  NVGtransform *transform;
  mrb_get_args(mrb, "ff", &sx, &sy);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformScale(&transform->ary[0], sx, sy);
  return self;
}

static mrb_value
transform_rotate(mrb_state *mrb, mrb_value self)
{
  mrb_float a;
  NVGtransform *transform;
  mrb_get_args(mrb, "f", &a);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformRotate(&transform->ary[0], a);
  return self;
}

static mrb_value
transform_skew_x(mrb_state *mrb, mrb_value self)
{
  mrb_float a;
  NVGtransform *transform;
  mrb_get_args(mrb, "f", &a);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformSkewX(&transform->ary[0], a);
  return self;
}

static mrb_value
transform_skew_y(mrb_state *mrb, mrb_value self)
{
  mrb_float a;
  NVGtransform *transform;
  mrb_get_args(mrb, "f", &a);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformSkewY(&transform->ary[0], a);
  return self;
}

static mrb_value
transform_multiply(mrb_state *mrb, mrb_value self)
{
  NVGtransform *a;
  NVGtransform *transform;
  mrb_get_args(mrb, "d", &a, &mrb_nvg_transform_type);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformMultiply(&transform->ary[0], &a->ary[0]);
  return self;
}

static mrb_value
transform_pre_multiply(mrb_state *mrb, mrb_value self)
{
  NVGtransform *a;
  NVGtransform *transform;
  mrb_get_args(mrb, "d", &a, &mrb_nvg_transform_type);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  nvgTransformPremultiply(&transform->ary[0], &a->ary[0]);
  return self;
}

static mrb_value
transform_inverse(mrb_state *mrb, mrb_value self)
{
  mrb_bool res;
  NVGtransform *a;
  NVGtransform *transform;
  mrb_get_args(mrb, "d", &a, &mrb_nvg_transform_type);
  transform = mrb_data_get_ptr(mrb, self, &mrb_nvg_transform_type);
  res = nvgTransformInverse(&transform->ary[0], &a->ary[0]) == 1;
  return mrb_bool_value(res);
}

void
mrb_nvg_transform_init(mrb_state *mrb, struct RClass *nvg_module)
{
  nvg_transform_class = mrb_define_class_under(mrb, nvg_module, "Transform", mrb->object_class);
  MRB_SET_INSTANCE_TT(nvg_transform_class, MRB_TT_DATA);

  mrb_define_method(mrb, nvg_transform_class, "initialize",      transform_initialize,      MRB_ARGS_ANY());
  mrb_define_method(mrb, nvg_transform_class, "initialize_copy", transform_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "a",               transform_get_a,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "b",               transform_get_b,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "c",               transform_get_c,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "d",               transform_get_d,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "e",               transform_get_e,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "f",               transform_get_f,           MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_transform_class, "a=",              transform_set_a,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "b=",              transform_set_b,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "c=",              transform_set_c,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "d=",              transform_set_d,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "e=",              transform_set_e,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "f=",              transform_set_f,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "translate!",      transform_translate,       MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_transform_class, "scale!",          transform_scale,           MRB_ARGS_REQ(2));
  mrb_define_method(mrb, nvg_transform_class, "rotate!",         transform_rotate,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "skew_x!",         transform_skew_x,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "skew_y!",         transform_skew_y,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "multiply!",       transform_multiply,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "pre_multiply!",   transform_pre_multiply,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_transform_class, "inverse!",        transform_inverse,         MRB_ARGS_REQ(1));
}
