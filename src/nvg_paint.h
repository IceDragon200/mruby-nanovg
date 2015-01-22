#ifndef MRB_NVG_PAINT_H
#define MRB_NVG_PAINT_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "nvg.h"

extern const struct mrb_data_type mrb_nvg_paint_type;
mrb_value mrb_nvg_paint_value(mrb_state *mrb, NVGpaint paint);
void mrb_nvg_paint_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
