#include <mruby.h>
#include <mruby/class.h>
#include <mruby/error.h>

#include <GL/glew.h>

#include "nvg.h"
#include "nvg_color.h"
#include "nvg_paint.h"
#include "nvg_transform.h"
#include "nvg_context.h"

static struct RClass *nvg_module;
static struct RClass *nvg_err_class;

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
  nvg_module = mrb_define_module(mrb, "Nanovg");
  nvg_err_class = mrb_define_class(mrb, "NVGError", mrb_class_get(mrb, "StandardError"));

  mrb_nvg_color_init(mrb, nvg_module);
  mrb_nvg_paint_init(mrb, nvg_module);
  mrb_nvg_transform_init(mrb, nvg_module);
  mrb_nvg_context_init(mrb, nvg_module);

  mrb_define_class_method(mrb, nvg_module, "deg_to_rad", deg_to_rad, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, nvg_module, "rad_to_deg", rad_to_deg, MRB_ARGS_REQ(1));

  /* enum NVGwinding */
  mrb_define_const(mrb, nvg_module, "CW",                     mrb_fixnum_value(NVG_CW));
  mrb_define_const(mrb, nvg_module, "CCW",                    mrb_fixnum_value(NVG_CCW));
  /* enum NVGsolidity */
  mrb_define_const(mrb, nvg_module, "SOLID",                  mrb_fixnum_value(NVG_SOLID));
  mrb_define_const(mrb, nvg_module, "HOLE",                   mrb_fixnum_value(NVG_HOLE));
  /* enum NVGlineCap */
  mrb_define_const(mrb, nvg_module, "BUTT",                   mrb_fixnum_value(NVG_BUTT));
  mrb_define_const(mrb, nvg_module, "ROUND",                  mrb_fixnum_value(NVG_ROUND));
  mrb_define_const(mrb, nvg_module, "SQUARE",                 mrb_fixnum_value(NVG_SQUARE));
  mrb_define_const(mrb, nvg_module, "BEVEL",                  mrb_fixnum_value(NVG_BEVEL));
  mrb_define_const(mrb, nvg_module, "MITER",                  mrb_fixnum_value(NVG_MITER));
  /* enum NVGalign */
  mrb_define_const(mrb, nvg_module, "ALIGN_LEFT",             mrb_fixnum_value(NVG_ALIGN_LEFT));
  mrb_define_const(mrb, nvg_module, "ALIGN_CENTER",           mrb_fixnum_value(NVG_ALIGN_CENTER));
  mrb_define_const(mrb, nvg_module, "ALIGN_RIGHT",            mrb_fixnum_value(NVG_ALIGN_RIGHT));
  mrb_define_const(mrb, nvg_module, "ALIGN_TOP",              mrb_fixnum_value(NVG_ALIGN_TOP));
  mrb_define_const(mrb, nvg_module, "ALIGN_MIDDLE",           mrb_fixnum_value(NVG_ALIGN_MIDDLE));
  mrb_define_const(mrb, nvg_module, "ALIGN_BOTTOM",           mrb_fixnum_value(NVG_ALIGN_BOTTOM));
  mrb_define_const(mrb, nvg_module, "ALIGN_BASELINE",         mrb_fixnum_value(NVG_ALIGN_BASELINE));
  /* enum NVGimageFlags */
  mrb_define_const(mrb, nvg_module, "IMAGE_GENERATE_MIPMAPS", mrb_fixnum_value(NVG_IMAGE_GENERATE_MIPMAPS));
  mrb_define_const(mrb, nvg_module, "IMAGE_REPEATX",          mrb_fixnum_value(NVG_IMAGE_REPEATX));
  mrb_define_const(mrb, nvg_module, "IMAGE_REPEATY",          mrb_fixnum_value(NVG_IMAGE_REPEATY));
  mrb_define_const(mrb, nvg_module, "IMAGE_FLIPY",            mrb_fixnum_value(NVG_IMAGE_FLIPY));
  mrb_define_const(mrb, nvg_module, "IMAGE_PREMULTIPLIED",    mrb_fixnum_value(NVG_IMAGE_PREMULTIPLIED));
  /* enum NVGcreateFlags */
  mrb_define_const(mrb, nvg_module, "ANTIALIAS",              mrb_fixnum_value(NVG_ANTIALIAS));
  mrb_define_const(mrb, nvg_module, "STENCIL_STROKES",        mrb_fixnum_value(NVG_STENCIL_STROKES));
  mrb_define_const(mrb, nvg_module, "DEBUG",                  mrb_fixnum_value(NVG_DEBUG));
}

void
mrb_mruby_nanovg_gem_final(mrb_state* mrb)
{

}
