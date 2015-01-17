#ifndef MRB_NVG_COLOR_H
#define MRB_NVG_COLOR_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "nvg.h"

struct mrb_data_type mrb_nvg_color_type;
void mrb_nvg_color_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
