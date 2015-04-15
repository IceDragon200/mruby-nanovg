# A 2D Vector drawing framework similar to HTML5 Canvas.
module Nanovg
  # @!group enum NVGwinding
  #   see {Nanovg::Context#path_winding}
  # Clockwise Winding
  CW = 1
  # Anti-Clockwise Winding
  CCW = 2
  # @!endgroup

  # @!group enum NVGsolidity
  #   see {Nanovg::Context#path_winding}
  # Solid paths
  SOLID = 1
  # Holed paths
  HOLE = 2
  # @!endgroup

  # @!group enum NVGlineCap
  #   see {Nanovg::Context#line_cap}
  # Butted line cap
  BUTT = 0
  # Rounded line cap
  ROUND = 1
  # Squared line cap
  SQUARE = 2
  # Beveled line cap
  BEVEL = 3
  # Mitered line cap
  MITER = 4
  # @!endgroup

  # @!group enum NVGalign
  #   see {Nanovg::Context#text_align}
  # @!group horizontal
  # Align to the left
  ALIGN_LEFT = 1 << 0
  # Align to the center
  ALIGN_CENTER = 1 << 1
  # Align to the right
  ALIGN_RIGHT = 1 << 2
  # @!endgroup
  # @!group vertical align
  # Align to the top
  ALIGN_TOP = 1 << 3
  # Align to the middle
  ALIGN_MIDDLE = 1 << 4
  # Align to the bottom
  ALIGN_BOTTOM = 1 << 5
  # Align to the baseline
  ALIGN_BASELINE = 1 << 6
  # @!endgroup
  # @!endgroup

  # @!group enum NVGimageFlags
  #   see {Nanovg::Context#create_image}
  # Should mipmaps be generated for the image?
  IMAGE_GENERATE_MIPMAPS = 1 << 0
  # Repeat the image horizontally?
  IMAGE_REPEATX = 1 << 1
  # Repeat the image vertically?
  IMAGE_REPEATY = 1 << 2
  # Flip the image upside down?
  IMAGE_FLIPY = 1 << 3
  # Premultiply the alpha?
  IMAGE_PREMULTIPLIED = 1 << 4
  # @!endgroup

  # @!group enum NVGcreateFlags
  #   see {Nanovg::Context#initialize}
  # Enables antialiasing in the context
  ANTIALIAS = 1 << 0
  # Use stencil strokes?
  STENCIL_STROKES = 1 << 1
  # Enable Debugging for the context
  DEBUG = 1 << 2
  # @!endgroup

  # Converts a degree to a radian.
  #
  # @param [Numeric] num
  # @return [Numeric]
  def self.deg_to_rad(num)
  end

  # Converts a radian to a degree.
  #
  # @param [Numeric] num
  # @return [Numeric]
  def self.rad_to_deg(num)
  end
end
