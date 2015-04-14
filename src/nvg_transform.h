#ifndef MRB_NVG_TRANSFORM_PRIV_H
#define MRB_NVG_TRANSFORM_PRIV_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "mrb/nvg/transform.h"

void mrb_nvg_transform_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
