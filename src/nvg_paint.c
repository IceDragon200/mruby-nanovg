#include <string.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/array.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include "nvg_paint.h"
#include "nvg_color.h"
#include "nvg_transform.h"

static struct RClass *mrb_nvg_paint_class;

#define ATTR_GET_HEAD(_name_) \
static mrb_value                                           \
paint_get_ ## _name_(mrb_state *mrb, mrb_value self)       \
{                                                          \
  NVGpaint *_obj_;                                         \
  _obj_ = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type)

#define ATTR_GET_f(_name_) \
ATTR_GET_HEAD(_name_);                        \
  return mrb_float_value(mrb, _obj_->_name_); \
}

#define ATTR_GET_i(_name_) \
ATTR_GET_HEAD(_name_);                    \
  return mrb_fixnum_value(_obj_->_name_); \
}

#define ATTR_GET_d_color(_name_) \
ATTR_GET_HEAD(_name_);                    \
  return mrb_nvg_color_value(mrb, _obj_->_name_); \
}

#define ATTR_SET_HEAD(_name_, _fmt_, _type_) \
static mrb_value                                            \
paint_set_ ## _name_(mrb_state *mrb, mrb_value self)        \
{                                                           \
  NVGpaint *_obj_;                                          \
  _type_ _val_;                                             \
  mrb_get_args(mrb, _fmt_, &_val_);                         \
  _obj_ = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type)

#define ATTR_SET_f(_name_) \
ATTR_SET_HEAD(_name_, "f", mrb_float); \
  _obj_->_name_ = (float)_val_;   \
  return mrb_nil_value();         \
}

#define ATTR_SET_i(_name_) \
ATTR_SET_HEAD(_name_, "i", mrb_int); \
  _obj_->_name_ = (int)_val_;   \
  return mrb_nil_value();       \
}

#define ATTR_SET_d_color(_name_) \
static mrb_value                                            \
paint_set_ ## _name_(mrb_state *mrb, mrb_value self)        \
{                                                           \
  NVGpaint *_obj_;                                          \
  NVGcolor *_val_;                                          \
  mrb_get_args(mrb, "d", &_val_, &mrb_nvg_color_type);      \
  _obj_ = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type); \
  _obj_->_name_ = *_val_;                                   \
  return mrb_nil_value();                                   \
}

void
mrb_nvg_paint_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

struct mrb_data_type mrb_nvg_paint_type = { "Nanovg::Paint", mrb_nvg_paint_free };

mrb_value
mrb_nvg_paint_value(mrb_state *mrb, NVGpaint paint)
{
  NVGpaint *npaint;
  mrb_value mrbpaint = mrb_obj_new(mrb, mrb_nvg_paint_class, 0, NULL);
  npaint = mrb_data_get_ptr(mrb, mrbpaint, &mrb_nvg_paint_type);
  *npaint = paint;
  return mrbpaint;
}

static mrb_value
paint_initialize(mrb_state *mrb, mrb_value self)
{
  NVGpaint *npaint = mrb_malloc(mrb, sizeof(NVGpaint));
  memset(npaint, sizeof(NVGpaint), 0);
  DATA_PTR(self) = npaint;
  DATA_TYPE(self) = &mrb_nvg_paint_type;
  return self;
}

static mrb_value
paint_get_xform(mrb_state *mrb, mrb_value self)
{
  NVGpaint *paint;
  paint = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type);
  return mrb_nvg_transform_value(mrb, paint->xform);
}

static mrb_value
paint_get_extent(mrb_state *mrb, mrb_value self)
{
  NVGpaint *paint;
  mrb_value vals[2];
  paint = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type);
  vals[0] = mrb_float_value(mrb, paint->extent[0]);
  vals[1] = mrb_float_value(mrb, paint->extent[1]);
  return mrb_ary_new_from_values(mrb, 2, vals);
}

ATTR_GET_f(radius);
ATTR_GET_f(feather);
ATTR_GET_d_color(innerColor);
ATTR_GET_d_color(outerColor);
ATTR_GET_i(image);

static mrb_value
paint_set_xform(mrb_state *mrb, mrb_value self)
{
  NVGpaint *paint;
  NVGtransform *t;
  mrb_get_args(mrb, "d", &t, &mrb_nvg_transform_type);
  paint = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type);
  memcpy(paint->xform, t->ary, sizeof(float) * 6);
  return mrb_nil_value();
}

static mrb_value
paint_set_extent(mrb_state *mrb, mrb_value self)
{
  NVGpaint *paint;
  mrb_value ary;
  mrb_get_args(mrb, "A", &ary);
  paint = mrb_data_get_ptr(mrb, self, &mrb_nvg_paint_type);
  paint->extent[0] = mrb_to_flo(mrb, mrb_ary_ref(mrb, ary, 0));
  paint->extent[1] = mrb_to_flo(mrb, mrb_ary_ref(mrb, ary, 1));
  return mrb_nil_value();
}

ATTR_SET_i(radius);
ATTR_SET_i(feather);
ATTR_SET_d_color(innerColor);
ATTR_SET_d_color(outerColor);
ATTR_SET_i(image);

void
mrb_nvg_paint_init(mrb_state *mrb, struct RClass *nvg_module)
{
  mrb_nvg_paint_class = mrb_define_class_under(mrb, nvg_module, "Paint", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_nvg_paint_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_nvg_paint_class, "initialize",   paint_initialize,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "xform",        paint_get_xform,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "extent",       paint_get_extent,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "radius",       paint_get_radius,     MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "feather",      paint_get_feather,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "inner_color",  paint_get_innerColor, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "outer_color",  paint_get_outerColor, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "image",        paint_get_image,      MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_nvg_paint_class, "xform=",       paint_set_xform,      MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "extent=",      paint_set_extent,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "radius=",      paint_set_radius,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "feather=",     paint_set_feather,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "inner_color=", paint_set_innerColor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "outer_color=", paint_set_outerColor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb_nvg_paint_class, "image=",       paint_set_image,      MRB_ARGS_REQ(1));
}
