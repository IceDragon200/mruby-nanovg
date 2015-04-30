#include <mruby.h>
#include <mruby/class.h>
#include <mruby/error.h>

#include <GL/glew.h>

#include "mrb/nvg/nvg.h"
#include "nvg_color.h"
#include "nvg_paint.h"
#include "nvg_transform.h"
#include "nvg_context.h"

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
  struct RClass *nvg_mod = mrb_define_module(mrb, "Nanovg");
  struct RClass *nvg_err_class = mrb_define_class(mrb, "NVGError", mrb_class_get(mrb, "StandardError"));
  struct RClass *nvg_winding_mod = mrb_define_module_under(mrb, nvg_mod, "Winding");
  struct RClass *nvg_solidity_mod = mrb_define_module_under(mrb, nvg_mod, "Solidity");
  struct RClass *nvg_line_cap_mod = mrb_define_module_under(mrb, nvg_mod, "LineCap");
  struct RClass *nvg_align_mod = mrb_define_module_under(mrb, nvg_mod, "Align");
  struct RClass *nvg_image_flags_mod = mrb_define_module_under(mrb, nvg_mod, "ImageFlags");
  struct RClass *nvg_create_flags_mod = mrb_define_module_under(mrb, nvg_mod, "CreateFlags");

  mrb_nvg_color_init(mrb, nvg_mod);
  mrb_nvg_paint_init(mrb, nvg_mod);
  mrb_nvg_transform_init(mrb, nvg_mod);
  mrb_nvg_context_init(mrb, nvg_mod);

  mrb_define_class_method(mrb, nvg_mod, "deg_to_rad", deg_to_rad, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, nvg_mod, "rad_to_deg", rad_to_deg, MRB_ARGS_REQ(1));

  /* enum NVGwinding */
  mrb_define_const(mrb, nvg_winding_mod, "CW",                     mrb_fixnum_value(NVG_CW));
  mrb_define_const(mrb, nvg_winding_mod, "CCW",                    mrb_fixnum_value(NVG_CCW));
  /* enum NVGsolidity */
  mrb_define_const(mrb, nvg_solidity_mod, "SOLID",                  mrb_fixnum_value(NVG_SOLID));
  mrb_define_const(mrb, nvg_solidity_mod, "HOLE",                   mrb_fixnum_value(NVG_HOLE));
  /* enum NVGlineCap */
  mrb_define_const(mrb, nvg_line_cap_mod, "BUTT",                   mrb_fixnum_value(NVG_BUTT));
  mrb_define_const(mrb, nvg_line_cap_mod, "ROUND",                  mrb_fixnum_value(NVG_ROUND));
  mrb_define_const(mrb, nvg_line_cap_mod, "SQUARE",                 mrb_fixnum_value(NVG_SQUARE));
  mrb_define_const(mrb, nvg_line_cap_mod, "BEVEL",                  mrb_fixnum_value(NVG_BEVEL));
  mrb_define_const(mrb, nvg_line_cap_mod, "MITER",                  mrb_fixnum_value(NVG_MITER));
  /* enum NVGalign */
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_LEFT",             mrb_fixnum_value(NVG_ALIGN_LEFT));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_CENTER",           mrb_fixnum_value(NVG_ALIGN_CENTER));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_RIGHT",            mrb_fixnum_value(NVG_ALIGN_RIGHT));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_TOP",              mrb_fixnum_value(NVG_ALIGN_TOP));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_MIDDLE",           mrb_fixnum_value(NVG_ALIGN_MIDDLE));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_BOTTOM",           mrb_fixnum_value(NVG_ALIGN_BOTTOM));
  mrb_define_const(mrb, nvg_align_mod, "ALIGN_BASELINE",         mrb_fixnum_value(NVG_ALIGN_BASELINE));
  /* enum NVGimageFlags */
  mrb_define_const(mrb, nvg_image_flags_mod, "IMAGE_GENERATE_MIPMAPS", mrb_fixnum_value(NVG_IMAGE_GENERATE_MIPMAPS));
  mrb_define_const(mrb, nvg_image_flags_mod, "IMAGE_REPEATX",          mrb_fixnum_value(NVG_IMAGE_REPEATX));
  mrb_define_const(mrb, nvg_image_flags_mod, "IMAGE_REPEATY",          mrb_fixnum_value(NVG_IMAGE_REPEATY));
  mrb_define_const(mrb, nvg_image_flags_mod, "IMAGE_FLIPY",            mrb_fixnum_value(NVG_IMAGE_FLIPY));
  mrb_define_const(mrb, nvg_image_flags_mod, "IMAGE_PREMULTIPLIED",    mrb_fixnum_value(NVG_IMAGE_PREMULTIPLIED));
  /* enum NVGcreateFlags */
  mrb_define_const(mrb, nvg_create_flags_mod, "ANTIALIAS",              mrb_fixnum_value(NVG_ANTIALIAS));
  mrb_define_const(mrb, nvg_create_flags_mod, "STENCIL_STROKES",        mrb_fixnum_value(NVG_STENCIL_STROKES));
  mrb_define_const(mrb, nvg_create_flags_mod, "DEBUG",                  mrb_fixnum_value(NVG_DEBUG));
}

void
mrb_mruby_nanovg_gem_final(mrb_state* mrb)
{

}
