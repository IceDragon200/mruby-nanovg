#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include "nvg_paint.h"

static struct RClass *mrb_nvg_paint_class;

void
mrb_nvg_paint_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

struct mrb_data_type mrb_nvg_paint_type = { "Nanovg::Paint", mrb_nvg_paint_free };

void
mrb_nvg_paint_init(mrb_state *mrb, struct RClass *nvg_module)
{
  mrb_nvg_paint_class = mrb_define_class_under(mrb, nvg_module, "Paint", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_nvg_paint_class, MRB_TT_DATA);
}
