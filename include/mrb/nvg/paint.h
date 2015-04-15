#ifndef MRB_NVG_PAINT_H
#define MRB_NVG_PAINT_H

#include <mruby.h>
#include <mruby/data.h>
#include "mrb/nvg/nvg.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern const struct mrb_data_type mrb_nvg_paint_type;
void mrb_nvg_paint_init(mrb_state *mrb, struct RClass *nvg_module);

#ifdef __cplusplus
}
#endif
#endif
