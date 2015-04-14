#ifndef MRB_NVG_COLOR_H
#define MRB_NVG_COLOR_H

#include <mruby.h>
#include <mruby/data.h>
#include "mrb/nvg/nvg.h"

extern const struct mrb_data_type mrb_nvg_color_type;
mrb_value mrb_nvg_color_value(mrb_state *mrb, NVGcolor color);

#endif
