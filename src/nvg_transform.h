#ifndef MRB_NVG_TRANSFORM_H
#define MRB_NVG_TRANSFORM_H

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include "nvg.h"

struct NVGtransform_ {
  union {
    float ary[6];
    struct {
      float a, b, c, d, e, f;
    };
  };
};

typedef struct NVGtransform_ NVGtransform;

extern const struct mrb_data_type mrb_nvg_transform_type;
mrb_value mrb_nvg_transform_value(mrb_state *mrb, float *xform);
void mrb_nvg_transform_init(mrb_state *mrb, struct RClass *nvg_module);

#endif
