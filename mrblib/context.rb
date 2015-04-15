module Nanovg
  class Context
    # Error raised when aborting a draw
    # @see Nanovg::Context#draw
    # @see Nanovg::Context#abort_frame
    class AbortFrame < IndexError
    end

    # Initializes the context given a flag
    alias :initialize_w_flags :initialize
    private :initialize_w_flags

    # @overload initialize
    # @overload initialize(flags)
    #   @param [Integer] flags
    #   {NVGcreateFlags}
    def initialize(*args)
      if args.empty?
        initialize_w_flags(0)
      else
        initialize_w_flags(*args)
      end
    end

    # Copies the current Context transform to the target transform
    alias :copy_current_transform_to :current_transform

    # @overload current_transform
    #   Copies the current Context transform to a new Transform
    # @overload current_transform(t)
    #   Copies the current Context transform to t and returns it
    #   @param [Transform] t
    # @return [Transform]
    def current_transform(t = nil)
      t ||= Nanovg::Transform.new
      copy_current_transform_to(t)
      t
    end

    # Creates and returns a ImageHandle.
    # If you pass in a ImageHandle it will return the same handle, handy
    # if your not sure if your variable is an id or a handle.
    #
    # @param [Integer, ImageHandle] image
    # @return [ImageHandle]
    def image_handle(image)
      if Nanovg::ImageHandle === image
        image
      else
        Nanovg::ImageHandle.new(self, image)
      end
    end

    # Creates and returns a FontHandle.
    # If you pass in a FontHandle it will return the same handle, handy
    # if your not sure if your variable is an id or a handle.
    #
    # @param [Integer] font
    # @return [Nanovg::FontHandle]
    def font_handle(font)
      if Nanovg::FontHandle === font
        font
      else
        Nanovg::FontHandle.new(self, font)
      end
    end

    # Cancels drawing the current frame and raises an AbortFrame.
    # The AbortFrame is caught if the abort_frame is called in a {#draw} block.
    #
    # @raise AbortFrame
    def abort_frame
      cancel_frame
      raise AbortFrame
    end

    # Wraps execution between #begin_frame and #end_frame
    #
    # @param (see #begin_frame)
    # @return [void]
    def draw(*args)
      begin_frame(*args)
      yield self
      end_frame
    rescue AbortFrame
      nil
    end

    # Convience method for {#begin_path}
    #
    # @return [void]
    def path
      begin_path
      yield self
    end

    # Convience method for wrapping drawing between a {#save} and {#restore}
    # call.
    #
    # @return [void]
    def spork
      save
      yield self
      restore
    end
  end
end
