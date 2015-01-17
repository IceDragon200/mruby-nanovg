module Nanovg
  class Context
    class AbortFrame < IndexError
    end

    alias :initialize_w_flags :initialize
    def initialize(*args)
      if args.empty?
        initialize_w_flags(0)
      else
        initialize_w_flags(*args)
      end
    end

    alias :copy_current_transform_to :current_transform
    def current_transform(*args)
      if args.empty?
        t = Nanovg::Transform.new
        copy_current_transform_to(t)
        t
      else
        copy_current_transform_to(*args)
      end
    end

    # An ImageHandle is a helper class for managing images from a context
    # its a simple ruby implementation so it should be garbage collected safely.
    # Don't try throwing random numbers in it to get a image though,
    # this don't absolutely 0 checks to ensure validity of the provided
    # image id.
    # If you pass in a ImageHandle it will return the same handle, handy
    # if your not sure if your variable is an id or a handle.
    #
    # @param [Integer] image
    # @return [Nanovg::ImageHandle]
    def image_handle(image)
      if Nanovg::ImageHandle === image
        return image
      else
        Nanovg::ImageHandle.new(self, image)
      end
    end

    # Same drill as the ImageHandle, just for fonts instead.
    #
    # @param [Integer] font
    # @return [Nanovg::FontHandle]
    def font_handle(font)
      if Nanovg::FontHandle === font
        return font
      else
        Nanovg::FontHandle.new(self, font)
      end
    end

    def abort_frame
      cancel_frame
      raise AbortFrame
    end

    def draw(*args)
      begin_frame(*args)
      yield self
      end_frame
    rescue AbortFrame
      nil
    end
  end
end
