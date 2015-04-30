module Nanovg
  # A drawing context
  class Context
    # @param [Integer] flags
    #   see {Nanovg::CreateFlags}
    def initialize(flags)
    end

    # @!group Frame
    # Starts drawing, call {#end_frame} when you have finished drawing to
    # commit the changes.
    #
    # @param [Integer] width
    # @param [Integer] height
    # @param [Float] pixel_ratio
    # @return [self]
    def begin_frame(width, height, pixel_ratio)
    end

    # Cancels drawing current frame, and drops all drawing.
    #
    # @return [self]
    def cancel_frame
    end

    # Stops drawing and commits all the drawing changes.
    #
    # @return [self]
    def end_frame
    end
    # @!endgroup Frame

    # @!group State
    # Saves the current Context stack, to be later {#restore}d
    #
    # @return [self]
    def save
    end

    # Restores the Context stack from a {#save}
    #
    # @return [self]
    def restore
    end

    # Restores the Context to its pristine state
    #
    # @return [self]
    def reset
    end
    # @!endgroup State

    # @!group Drawing Settings
    # Sets the Context stroke color
    #
    # @param [Color] color
    # @return [self]
    def stroke_color(color)
    end

    # Sets the Context stroke paint
    #
    # @param [Paint] paint
    # @return [self]
    def stroke_paint(paint)
    end

    # Sets the Context fill color
    #
    # @param [Color] color
    # @return [self]
    def fill_color(color)
    end

    # Sets the Context fill paint
    #
    # @param [Paint] paint
    # @return [self]
    def fill_paint(paint)
    end

    # Sets the Context miter limit
    #
    # @param [Float] limit
    # @return [self]
    def miter_limit(limit)
    end

    # Sets the Context stroke width
    #
    # @param [Float] width
    # @return [self]
    def stroke_width(width)
    end

    # @param [Integer] cap
    #   see {Nanovg::LineCap}
    # @return [self]
    def line_cap(cap)
    end

    # @param [Integer] jn
    #   see {Nanovg::LineCap}
    # @return [self]
    def line_join(jn)
    end

    # @param [Float] alpha
    # @return [self]
    def global_alpha(alpha)
    end
    # @!endgroup Drawing Settings

    # @!group Transform

    # @return [self]
    def reset_transform
    end

    # @param [Float] a
    # @param [Float] b
    # @param [Float] c
    # @param [Float] d
    # @param [Float] e
    # @param [Float] f
    # @return [self]
    def transform(a, b, c, d, e, f)
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def translate(x, y)
    end

    # @param [Float] angle
    def rotate(angle)
    end

    # @param [Float] n
    def skew_x(n)
    end

    # @param [Float] n
    def skew_y(n)
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def scale(x, y)
    end

    # @param [Transform] transf
    # @return [self]
    def current_transform(transf)
    end
    # @!endgroup Transform

    # @!group Image
    # @note mruby strings do not allow NULLS, this breaks creating images
    #       using Strings, instead use mruby-nanovg-idnarray-image, which
    #       adds a method for using NArray for the image data.

    # @param [String] filename
    # @param [Integer] flags
    #   see {Nanovg::ImageFlags}
    # @return [Integer] the image handle
    def create_image(filename, flags)
    end

    # @param [Integer] flags
    #   see {Nanovg::ImageFlags}
    # @param [String] data
    # @param [Integer] datasize
    # @return [Integer] the image handle
    def create_image_mem(flags, data, datasize)
    end

    # @param [Integer] w
    # @param [Integer] h
    # @param [Integer] flags
    #   see {Nanovg::ImageFlags}
    # @param [String] data
    # @return [self]
    def create_image_rgba(w, h, flags, data)
    end

    # @param [Integer] image  the image handle
    # @param [String] data
    # @return [self]
    def update_image(image, data)
    end

    # @param [Integer] image  the image handle
    # @return [Array<Integer>] w, h
    def image_size(image)
    end

    # @param [Integer] image  the image handle
    # @return [self]
    def delete_image(image)
    end
    # @!endgroup Image

    # @!group Scissor
    # @param [Float] x
    # @param [Float] y
    # @param [Float] w
    # @param [Float] h
    # @return [self]
    def scissor(x, y, w, h)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] w
    # @param [Float] h
    # @return [self]
    def intersect_scissor(x, y, w, h)
    end

    # @return [self]
    def reset_scissor
    end
    # @!endgroup Scissor

    # @!group Paints

    # @param [Float] sx
    # @param [Float] sy
    # @param [Float] ex
    # @param [Float] ey
    # @param [Color] icol
    # @param [Color] ocol
    # @return [Paint]
    def linear_gradient(sx, sy, ex, ey, icol, ocol)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] w
    # @param [Float] h
    # @param [Float] r
    # @param [Float] f
    # @param [Color] icol
    # @param [Color] ocol
    # @return [Paint]
    def box_gradient(x, y, w, h, r, f, icol, ocol)
    end

    # @param [Float] cx
    # @param [Float] cy
    # @param [Float] inr
    # @param [Float] outr
    # @param [Color] icol
    # @param [Color] ocol
    # @return [Paint]
    def radial_gradient(cx, cy, inr, outr, icol, ocol)
    end

    # @param [Float] ox
    # @param [Float] oy
    # @param [Float] ex
    # @param [Float] ey
    # @param [Float] angle
    # @param [Integer] image
    # @param [Float] alpha
    # @return [Paint]
    def image_pattern(ox, oy, ex, ey, angle, image, alpha)
    end
    # @!endgroup Paints

    # @!group Paths

    # @return [self]
    def begin_path
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def move_to(x, y)
    end

    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def line_to(x, y)
    end

    # @param [Float] c1x
    # @param [Float] c1y
    # @param [Float] c2x
    # @param [Float] c2y
    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def bezier_to(c1x, c1y, c2x, c2y, x, y)
    end

    # @param [Float] cx
    # @param [Float] cy
    # @param [Float] x
    # @param [Float] y
    # @return [self]
    def quad_to(cx, cy, x, y)
    end

    # @param [Float] x1
    # @param [Float] y1
    # @param [Float] x2
    # @param [Float] y2
    # @param [Float] radius
    # @return [self]
    def arc_to(x1, y1, x2, y2, radius)
    end

    # @return [self]
    def close_path
    end

    # @param [Integer] winding
    #   see {Nanovg::Winding}
    # @return [self]
    def path_winding(winding)
    end

    # @param [Float] cx
    # @param [Float] cy
    # @param [Float] r
    # @param [Float] a0
    # @param [Float] a1
    # @param [Integer] dir
    # @return [self]
    def arc(cx, cy, r, a0, a1, dir)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] w
    # @param [Float] h
    # @return [self]
    def rect(x, y, w, h)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] w
    # @param [Float] h
    # @param [Float] r
    # @return [self]
    def rounded_rect(x, y, w, h, r)
    end

    # @param [Float] cx
    # @param [Float] cy
    # @param [Float] rx
    # @param [Float] ry
    # @return [self]
    def ellipse(cx, cy, rx, ry)
    end

    # @param [Float] cx
    # @param [Float] cy
    # @param [Float] r
    # @return [self]
    def circle(cx, cy, r)
    end
    # @!endgroup Paths

    # @return [self]
    def fill
    end

    # @return [self]
    def stroke
    end

    # @!group Text

    # @param [String] name
    # @param [String] filename
    # @return [Integer] the font handle
    def create_font(name, filename)
    end

    # @param [String] name
    # @param [String] data
    # @param [Integer] ndata
    # @param [Integer] free_data
    # @return [Integer] the font handle
    def create_font_mem(name, data, ndata, free_data)
    end

    # @param [String] name
    # @return [Integer] the font handle
    def find_font(name)
    end

    # @param [Float] size
    # @return [self]
    def font_size(size)
    end

    # @param [Float] blur
    # @return [self]
    def font_blur(blur)
    end

    # @param [Float] spacing
    # @return [self]
    def text_letter_spacing(spacing)
    end

    # @param [Float] line_height
    # @return [self]
    def text_line_height(line_height)
    end

    # @param [Integer] align
    # @return [self]
    def text_align(align)
    end

    # @param [Integer] id
    # @return [self]
    def font_face_id(id)
    end

    # @param [String] face
    # @return [self]
    def font_face(face)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [String] str
    def text(x, y, str)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] break_row_width
    # @param [String] str
    def text_box(x, y, break_row_width, str)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [String] str
    # @param [Transform] bounds
    def text_bounds(x, y, str, bounds = nil)
    end

    # @param [Float] x
    # @param [Float] y
    # @param [Float] break_row_width
    # @param [String] str
    # @param [Transform] bounds
    def text_box_bounds(x, y, break_row_width, str, bounds = nil)
    end

    # @return [Array<Float>]
    def text_metrics
    end
    # @!endgroup Text
  end
end

__END__
  mrb_define_method(mrb, nvg_context_class, "text_line_height",    context_text_line_height,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text_align",          context_text_align,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_face_id",        context_font_face_id,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "font_face",           context_font_face,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, nvg_context_class, "text",                context_text,                MRB_ARGS_REQ(3));
  mrb_define_method(mrb, nvg_context_class, "text_box",            context_text_box,            MRB_ARGS_REQ(4));
  mrb_define_method(mrb, nvg_context_class, "text_bounds",         context_text_bounds,         MRB_ARGS_ARG(3, 1));
  mrb_define_method(mrb, nvg_context_class, "text_box_bounds",     context_text_box_bounds,     MRB_ARGS_ARG(4, 1));

  /*mrb_define_method(mrb, nvg_context_class, "text_glyph_positions",context_text_glyph_positions,MRB_ARGS_REQ(6));*/
  mrb_define_method(mrb, nvg_context_class, "text_metrics",        context_text_metrics,        MRB_ARGS_NONE());
  mrb_define_method(mrb, nvg_context_class, "text_break_lines",    context_text_break_lines,    MRB_ARGS_REQ(5));
