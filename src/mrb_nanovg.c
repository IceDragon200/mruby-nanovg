#include <mruby.h>
#include <mruby/class.h>
#include <mruby/error.h>

#include <GL/glew.h>

#include "nvg.h"
#include "nvg_color.h"
#include "nvg_paint.h"
#include "nvg_transform.h"
#include "nvg_context.h"

static mrb_value
init(mrb_state *mrb, mrb_value klass)
{
  if (glewInit() != GLEW_OK) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "GLEW has failed to initialize.");
  }
  return mrb_nil_value();
}

static mrb_value
deg_to_rad(mrb_state *mrb, mrb_value klass)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_float_value(mrb, nvgDegToRad(f));
}

static mrb_value
rad_to_deg(mrb_state *mrb, mrb_value klass)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_float_value(mrb, nvgRadToDeg(f));
}

void
mrb_mruby_nanovg_gem_init(mrb_state* mrb)
{
  struct RClass *nvg_module = mrb_define_module(mrb, "Nanovg");
  mrb_nvg_color_init(mrb, nvg_module);
  mrb_nvg_paint_init(mrb, nvg_module);
  mrb_nvg_transform_init(mrb, nvg_module);
  mrb_nvg_context_init(mrb, nvg_module);

  mrb_define_class_method(mrb, nvg_module, "init",       init,       MRB_ARGS_NONE());
  mrb_define_class_method(mrb, nvg_module, "deg_to_rad", deg_to_rad, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, nvg_module, "rad_to_deg", rad_to_deg, MRB_ARGS_REQ(1));
}

void
mrb_mruby_nanovg_gem_final(mrb_state* mrb)
{
}
