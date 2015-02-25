/*
 * mruby helper macros
 * rev. 4
 *   Added helper functions extmrb_data_cleanup, extmrb_malloc_set and extmrb_malloc_setzero
 * rev. 3
 *   Fixed ATTR macros using get for SET and set for GET
 * rev. 2
 * rev. 1
 */
#ifndef EXTMRB_HELPER_MACROS
#define EXTMRB_HELPER_MACROS

#include <mruby.h>
#include <memory.h>

inline static void
extmrb_data_cleanup(mrb_state *mrb, mrb_value self, void (*dfree)(mrb_state *mrb, void*)) {
  void *ptr = DATA_PTR(self);
  if (ptr) {
    dfree(mrb, ptr);
    DATA_PTR(self) = NULL;
    DATA_TYPE(self) = NULL;
  }
}

inline static void*
extmrb_malloc_set(mrb_state *mrb, int v, size_t size) {
  void *ptr = mrb_malloc(mrb, size);
  memset(ptr, v, size);
  return ptr;
}

inline static void*
extmrb_malloc_setzero(mrb_state *mrb, size_t size) {
  return extmrb_malloc_set(mrb, 0, size);
}

#define DEF_MRB_FUNC_HEAD(_mrb_name_) static mrb_value _mrb_name_(mrb_state *mrb, mrb_value self)

// _d_ Datatype
// _get_d_ function which returns the _d_, should take an mrb_state (mrb) and mrb_value (self)
#define d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _d_ _data_ = (_d_)_get_d_(mrb, self);

/*
 * ATTR functions
 */
/* GET */
#define base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _type_ *_d_ = (_type_*)mrb_data_get_ptr(mrb, self, _mrb_type_)

#define base_DEF_ATTR_GET_i(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_fixnum_value(_d_->_name_); \
}

#define base_DEF_ATTR_GET_f(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_float_value(mrb, _d_->_name_); \
}

#define base_DEF_ATTR_GET_s(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_str_new_cstr(mrb, _d_->_name_); \
}

/* SET */
#define base_DEF_ATTR_SET_HEAD(_mrb_name_, _mrb_type_, _type_, _name_, _fmt_, _p0_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _type_ *_d_ = (_type_*)mrb_data_get_ptr(mrb, self, _mrb_type_); \
  _p0_type_ _p0_; \
  mrb_get_args(mrb, _fmt_, &_p0_)

#define base_DEF_ATTR_SET_GENERIC(_mrb_name_, _mrb_type_, _type_, _name_, _fmt_, _p0_type_) \
base_DEF_ATTR_SET_HEAD(_mrb_name_, _mrb_type_, _type_, _name_, _fmt_, _p0_type_); \
  _d_->_name_ = _p0_; \
  return self; \
}

#define base_DEF_ATTR_SET_i(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_GENERIC(_mrb_name_, _mrb_type_, _type_, _name_, "i", mrb_int)

#define base_DEF_ATTR_SET_f(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_GENERIC(_mrb_name_, _mrb_type_, _type_, _name_, "f", mrb_float)

#define base_DEF_ATTR_SET_data(_mrb_name_, _mrb_type_, _type_, _name_, _p0_type_, _datatype_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _type_ *_d_ = (_type_*)mrb_data_get_ptr(mrb, self, _mrb_type_); \
  _p0_type_ *_p0_; \
  mrb_get_args(mrb, "d", &_p0_, _datatype_); \
  _d_->_name_ = *_p0_; \
  return self; \
}

#define base_DEF_ATTR_ACCESSOR_i(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_i(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_i(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

#define base_DEF_ATTR_ACCESSOR_f(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_f(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_f(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

#define base_DEF_ATTR_ACCESSOR_s(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_s(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_s(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)


/* Special types */
/* mruby-nanovg */
#define base_DEF_ATTR_GET_NVGcolor(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_nvg_color_value(mrb, _d_->_name_); \
}

#define base_DEF_ATTR_SET_NVGcolor(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_data(_mrb_name_, _mrb_type_, _type_, _name_, NVGcolor, &mrb_nvg_color_type)

#define base_DEF_ATTR_ACCESSOR_NVGcolor(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_NVGcolor(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_NVGcolor(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

/* mruby-blendish */
#define base_DEF_ATTR_GET_BNDwidgetTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_bnd_widget_theme_value(mrb, _d_->_name_); \
}

#define base_DEF_ATTR_GET_BNDnodeTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_bnd_node_theme_value(mrb, _d_->_name_); \
}

#define base_DEF_ATTR_GET_BNDtheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_HEAD(_mrb_name_, _mrb_type_, _type_); \
  return mrb_bnd_theme_value(mrb, _d_->_name_); \
}

#define base_DEF_ATTR_SET_BNDwidgetTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_data(_mrb_name_, _mrb_type_, _type_, _name_, BNDwidgetTheme, &mrb_bnd_widget_theme_type)

#define base_DEF_ATTR_SET_BNDnodeTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_data(_mrb_name_, _mrb_type_, _type_, _name_, BNDnodeTheme, &mrb_bnd_node_theme_type)

#define base_DEF_ATTR_SET_BNDtheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_SET_data(_mrb_name_, _mrb_type_, _type_, _name_, BNDtheme, &mrb_bnd_theme_type)

#define base_DEF_ATTR_ACCESSOR_BNDwidgetTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_BNDwidgetTheme(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_BNDwidgetTheme(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

#define base_DEF_ATTR_ACCESSOR_BNDnodeTheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_BNDnodeTheme(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_BNDnodeTheme(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

#define base_DEF_ATTR_ACCESSOR_BNDtheme(_mrb_name_, _mrb_type_, _type_, _name_) \
base_DEF_ATTR_GET_BNDtheme(_mrb_name_ ## _get, _mrb_type_, _type_, _name_); \
base_DEF_ATTR_SET_BNDtheme(_mrb_name_ ## _set, _mrb_type_, _type_, _name_)

/* -------------------------------------------------------------------------- */
/* DEF calling functions */
/* _mrb_name_
 *   Name of the function
 * _target_name_
 *   Name of function to call internally
 *
 * Macros prefixed with ng, mean "NO GET", meaning the function does not require
 * a data object ptr
 *
 * Nn
 * Where n == numeric value
 * when n == 0
 *   The function will take 0 parameters
 * when n == 1
 *   The function will take 1 parameter
 * when n == x
 *   The function will take x parameters
 *
 * Macros appended with a lowercase letter denote the return type
 * f - float
 * i - integer
 * s - string
 * In the case of arrays the function is called Na, most times array functions
 * should be written by hand instead of using a helper macro.
 */

/*
 * def (no data) functions
 */
#define nd_DEF_FUNC_N0_HEAD(_mrb_name_) DEF_MRB_FUNC_HEAD(_mrb_name_)

#define nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  mrb_get_args(mrb, _fmt_, &_p0_);

#define nd_DEF_FUNC_N2_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_);


#define nd_DEF_FUNC_N3_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_);


#define nd_DEF_FUNC_N4_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_);

#define nd_DEF_FUNC_N5_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  _p4_type_ _p4_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_);

#define nd_DEF_FUNC_N6_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
DEF_MRB_FUNC_HEAD(_mrb_name_) { \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  _p4_type_ _p4_; \
  _p5_type_ _p5_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_, &_p5_);

#define nd_DEF_FUNC_N0(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  _target_name_(); \
  return self; \
}

#define nd_DEF_FUNC_N1(_mrb_name_, _target_name_, _fmt_, _p0_type_) \
nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
  _target_name_(_p0_); \
  return self; \
}

#define nd_DEF_FUNC_N2(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
nd_DEF_FUNC_N2_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  _target_name_(_p0_, _p1_); \
  return self; \
}

#define nd_DEF_FUNC_N3(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
nd_DEF_FUNC_N3_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  _target_name_(_p0_, _p1_, _p2_); \
  return self; \
}

#define nd_DEF_FUNC_N4(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
nd_DEF_FUNC_N4_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  _target_name_(_p0_, _p1_, _p2_, _p3_); \
  return self; \
}

#define nd_DEF_FUNC_N5(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
nd_DEF_FUNC_N5_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_); \
  return self; \
}

#define nd_DEF_FUNC_N6(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
nd_DEF_FUNC_N6_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_, _p5_); \
  return self; \
}

/*
 * fixnum returns
 */
#define nd_DEF_FUNC_N0_i(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  return mrb_fixnum_value(_target_name_()); \
}

#define nd_DEF_FUNC_N1_i(_mrb_name_, _target_name_, _fmt_, _p0_type_) \
nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
  return mrb_fixnum_value(_target_name_(_p0_)); \
}

#define nd_DEF_FUNC_N2_i(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
nd_DEF_FUNC_N2_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_fixnum_value(_target_name_(_p0_, _p1_)); \
}

#define nd_DEF_FUNC_N3_i(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
nd_DEF_FUNC_N3_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_fixnum_value(_target_name_(_p0_, _p1_, _p2_)); \
}

#define nd_DEF_FUNC_N4_i(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
nd_DEF_FUNC_N4_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_fixnum_value(_target_name_(_p0_, _p1_, _p2_, _p3_)); \
}

#define nd_DEF_FUNC_N5_i(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
nd_DEF_FUNC_N5_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_fixnum_value(_target_name_(_p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define nd_DEF_FUNC_N6_i(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
nd_DEF_FUNC_N6_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_fixnum_value(_target_name_(_p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}

/*
 * float returns
 */
#define nd_DEF_FUNC_N0_f(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  return mrb_float_value(mrb, _target_name_()); \
}

#define nd_DEF_FUNC_N1_f(_mrb_name_, _target_name_, _fmt_, _p0_type_) \
nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_)); \
}

#define nd_DEF_FUNC_N2_f(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
nd_DEF_FUNC_N2_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_, _p1_)); \
}

#define nd_DEF_FUNC_N3_f(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
nd_DEF_FUNC_N3_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_, _p1_, _p2_)); \
}

#define nd_DEF_FUNC_N4_f(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
nd_DEF_FUNC_N4_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_)); \
}

#define nd_DEF_FUNC_N5_f(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
nd_DEF_FUNC_N5_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define nd_DEF_FUNC_N6_f(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
nd_DEF_FUNC_N6_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_float_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}


/*
 * cptr returns
 */
#define nd_DEF_FUNC_N0_cptr(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  return mrb_cptr_value(mrb, _target_name_()); \
}

#define nd_DEF_FUNC_N1_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_) \
nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_)); \
}

#define nd_DEF_FUNC_N2_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
nd_DEF_FUNC_N2_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_, _p1_)); \
}

#define nd_DEF_FUNC_N3_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
nd_DEF_FUNC_N3_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_, _p1_, _p2_)); \
}

#define nd_DEF_FUNC_N4_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
nd_DEF_FUNC_N4_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_)); \
}

#define nd_DEF_FUNC_N5_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
nd_DEF_FUNC_N5_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define nd_DEF_FUNC_N6_cptr(_mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
nd_DEF_FUNC_N6_HEAD(_mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_cptr_value(mrb, _target_name_(_p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}

/* OUI specific functions */
/*
 * vec returns
 */
#define nd_DEF_FUNC_N0_vec2(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  return mrb_oui_vec2_value(mrb, _target_name_()); \
}

/*
 * rect returns
 */
#define nd_DEF_FUNC_N0_rect(_mrb_name_, _target_name_) \
nd_DEF_FUNC_N0_HEAD(_mrb_name_) \
  return mrb_oui_rect_value(mrb, _target_name_()); \
}

#define nd_DEF_FUNC_N1_rect(_mrb_name_, _target_name_, _fmt_, _p0_type_) \
nd_DEF_FUNC_N1_HEAD(_mrb_name_, _fmt_, _p0_type_) \
  return mrb_oui_rect_value(mrb, _target_name_(_p0_)); \
}


/* -------------------------------------------------------------------------- */
/*
 * def (data) functions
 */
#define d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_)

#define d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  mrb_get_args(mrb, _fmt_, &_p0_);

#define d_DEF_FUNC_N2_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_);


#define d_DEF_FUNC_N3_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_);


#define d_DEF_FUNC_N4_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_);

#define d_DEF_FUNC_N5_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  _p4_type_ _p4_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_);

#define d_DEF_FUNC_N6_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
d_DEF_FUNC_HEAD(_d_, _get_d_, _mrb_name_) \
  _p0_type_ _p0_; \
  _p1_type_ _p1_; \
  _p2_type_ _p2_; \
  _p3_type_ _p3_; \
  _p4_type_ _p4_; \
  _p5_type_ _p5_; \
  mrb_get_args(mrb, _fmt_, &_p0_, &_p1_, &_p2_, &_p3_, &_p4_, &_p5_);

#define d_DEF_FUNC_N0(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  _target_name_(_data_); \
  return self; \
}

#define d_DEF_FUNC_N1(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
  _target_name_(_data_, _p0_); \
  return self; \
}

#define d_DEF_FUNC_N2(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
d_DEF_FUNC_N2_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  _target_name_(_data_, _p0_, _p1_); \
  return self; \
}

#define d_DEF_FUNC_N3(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
d_DEF_FUNC_N3_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  _target_name_(_data_, _p0_, _p1_, _p2_); \
  return self; \
}

#define d_DEF_FUNC_N4(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
d_DEF_FUNC_N4_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  _target_name_(_data_, _p0_, _p1_, _p2_, _p3_); \
  return self; \
}

#define d_DEF_FUNC_N5(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
d_DEF_FUNC_N5_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_); \
  return self; \
}

#define d_DEF_FUNC_N6(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
d_DEF_FUNC_N6_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_, _p5_); \
  return self; \
}

/*
 * fixnum returns
 */
#define d_DEF_FUNC_N0_i(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  return mrb_fixnum_value(_target_name_(_data_)); \
}

#define d_DEF_FUNC_N1_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_)); \
}

#define d_DEF_FUNC_N2_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
d_DEF_FUNC_N2_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_, _p1_)); \
}

#define d_DEF_FUNC_N3_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
d_DEF_FUNC_N3_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_, _p1_, _p2_)); \
}

#define d_DEF_FUNC_N4_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
d_DEF_FUNC_N4_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_, _p1_, _p2_, _p3_)); \
}

#define d_DEF_FUNC_N5_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
d_DEF_FUNC_N5_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define d_DEF_FUNC_N6_i(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
d_DEF_FUNC_N6_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_fixnum_value(_target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}

/*
 * float returns
 */
#define d_DEF_FUNC_N0_f(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  return mrb_float_value(mrb, _target_name_(_data_)); \
}

#define d_DEF_FUNC_N1_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_)); \
}

#define d_DEF_FUNC_N2_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
d_DEF_FUNC_N2_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_, _p1_)); \
}

#define d_DEF_FUNC_N3_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
d_DEF_FUNC_N3_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_)); \
}

#define d_DEF_FUNC_N4_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
d_DEF_FUNC_N4_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_)); \
}

#define d_DEF_FUNC_N5_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
d_DEF_FUNC_N5_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define d_DEF_FUNC_N6_f(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
d_DEF_FUNC_N6_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_float_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}


/*
 * cptr returns
 */
#define d_DEF_FUNC_N0_cptr(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  return mrb_cptr_value(mrb, _target_name_(_data_)); \
}

#define d_DEF_FUNC_N1_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_)); \
}

#define d_DEF_FUNC_N2_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_) \
d_DEF_FUNC_N2_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_, _p1_)); \
}

#define d_DEF_FUNC_N3_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
d_DEF_FUNC_N3_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_)); \
}

#define d_DEF_FUNC_N4_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
d_DEF_FUNC_N4_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_)); \
}

#define d_DEF_FUNC_N5_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
d_DEF_FUNC_N5_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_)); \
}

#define d_DEF_FUNC_N6_cptr(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
d_DEF_FUNC_N6_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_, _p1_type_, _p2_type_, _p3_type_, _p4_type_, _p5_type_) \
  return mrb_cptr_value(mrb, _target_name_(_data_, _p0_, _p1_, _p2_, _p3_, _p4_, _p5_)); \
}

/* OUI specific functions */
/*
 * vec returns
 */
#define d_DEF_FUNC_N0_vec2(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  return mrb_oui_vec2_value(mrb, _target_name_(_data_)); \
}

/*
 * rect returns
 */
#define d_DEF_FUNC_N0_rect(_d_, _get_d_, _mrb_name_, _target_name_) \
d_DEF_FUNC_N0_HEAD(_d_, _get_d_, _mrb_name_) \
  return mrb_oui_rect_value(mrb, _target_name_(_data_)); \
}

#define d_DEF_FUNC_N1_rect(_d_, _get_d_, _mrb_name_, _target_name_, _fmt_, _p0_type_) \
d_DEF_FUNC_N1_HEAD(_d_, _get_d_, _mrb_name_, _fmt_, _p0_type_) \
  return mrb_oui_rect_value(mrb, _target_name_(_data_, _p0_)); \
}


#endif
