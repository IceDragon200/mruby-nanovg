#ifndef MRB_NVG_TRANSFORM_H
#define MRB_NVG_TRANSFORM_H

#include <mruby.h>
#include <mruby/data.h>
#include "mrb/nvg/nvg.h"

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

#endif
