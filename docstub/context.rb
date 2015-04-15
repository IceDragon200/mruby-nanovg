module Nanovg
  # A drawing context
  class Context
    # Starts drawing, call {#end_frame} when you have finished drawing to
    # commit the changes.
    #
    # @param [Integer] width
    # @param [Integer] height
    # @param [Float] pixel_ratio
    # @return [void]
    def begin_frame(width, height, pixel_ratio)
    end

    # Cancels drawing current frame, and drops all drawing.
    # @return [void]
    def cancel_frame
    end

    # Stops drawing and commits all the drawing changes.
    # @return [void]
    def end_frame
    end

    # Saves the current Context stack, to be later {#restore}d
    #
    # @return [void]
    def save
    end

    # Restores the Context stack from a {#save}
    #
    # @return [void]
    def restore
    end

    # Restores the Context to its pristine state
    #
    # @return [void]
    def reset
    end

    # Sets the Context stroke color
    #
    # @param [Color] color
    # @return [void]
    def stroke_color(color)
    end

    # Sets the Context stroke paint
    #
    # @param [Paint] paint
    # @return [void]
    def stroke_paint(paint)
    end

    # Sets the Context fill color
    #
    # @param [Color] color
    # @return [void]
    def fill_color(color)
    end

    # Sets the Context fill paint
    #
    # @param [Paint] paint
    # @return [void]
    def fill_paint(paint)
    end

    # Sets the Context miter limit
    #
    # @param [Float] limit
    # @return [void]
    def miter_limit(limit)
    end

    # Sets the Context stroke width
    #
    # @param [Float] width
    # @return [void]
    def stroke_width(width)
    end

    #
    #
    # @param [String] filename
    # @param [Integer] flags
    #   see {enum NVGimageFlags}
    # @return [Integer] the image handle
    def create_image(filename, flags)
    end

    # @param [Integer] flags
    # @param [String] data
    # @param [Integer] datasize
    # @return [Integer] the image handle
    #
    # @note mruby strings do not allow NULLS, this breaks creating images
    #       using them, instead use mruby-nanovg-idnarray-image, which
    #       adds a method for using NArray for the image data.
    def create_image_mem(flags, data, datasize)
    end

    def update_image
    end

    # @return [void]
    def begin_path
    end

    # @return [void]
    def close_path
    end
  end
end
