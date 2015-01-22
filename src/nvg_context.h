#ifndef MRB_NVG_CONTEXT_H
#define MRB_NVG_CONTEXT_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "nvg.h"

extern const struct mrb_data_type mrb_nvg_context_type;
void mrb_nvg_context_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
