#ifndef MRB_NVG_PAINT_PRIV_H
#define MRB_NVG_PAINT_PRIV_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "mrb/nvg/paint.h"

mrb_value mrb_nvg_paint_value(mrb_state *mrb, NVGpaint paint);

#endif
