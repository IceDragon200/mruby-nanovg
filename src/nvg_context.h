#ifndef MRB_NVG_CONTEXT_PRIV_H
#define MRB_NVG_CONTEXT_PRIV_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "mrb/nvg/context.h"

void mrb_nvg_context_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
