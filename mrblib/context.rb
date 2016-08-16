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
    #   {CreateFlags}
    def initialize(*args)
      if args.empty?
        initialize_w_flags(NO_FLAG)
      else
        initialize_w_flags(*args)
      end
    end

    # @!group Transform

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
    # @!endgroup Transform

    # @!group Handle
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
    # @!endgroup Handle

    # @!group Frame
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
    # @yieldparam [self] ctx
    # @return [void]
    def draw(*args)
      begin_frame(*args)
      yield self
      end_frame
    rescue AbortFrame
      nil
    end
    # @!endgroup Frame

    # @!group Paths
    # Convience method for {#begin_path}
    #
    # @yieldparam [self] ctx
    # @return [void]
    def path
      begin_path
      yield self
    end
    # @!endgroup Paths

    # @!group State
    # Convience method for wrapping drawing between a {#save} and {#restore}
    # call.
    #
    # @yieldparam [self] ctx
    # @return [void]
    def spork
      save
      yield self
      restore
    end
    # @!endgroup State

    alias :text_glyph_positions_yielded :text_glyph_positions

    # @!group Text
    # Returns a list of gylph positions
    #
    # @param [Float] x
    # @param [Float] y
    # @param [String] text
    # @return [Array<Array[Float, Float, Float]>] (x, min_x, max_x)
    def text_glyph_positions(x, y, text)
      result = []
      text_glyph_positions_yielded x, y, text do |_, x, min_x, max_x|
        result << [x, min_x, max_x]
      end
      result
    end
    # @!endgroup text

    alias :fill_color= :fill_color
    alias :fill_paint= :fill_paint
    alias :font_blur= :font_blur
    alias :font_size= :font_size
    alias :global_alpha= :global_alpha
    alias :line_cap= :line_cap
    alias :line_join= :line_join
    alias :miter_limit= :miter_limit
    alias :path_winding= :path_winding
    alias :stroke_color= :stroke_color
    alias :stroke_paint= :stroke_paint
    alias :stroke_width= :stroke_width
    alias :text_letter_spacing= :text_letter_spacing
    alias :text_line_height= :text_line_height
    alias :text_align= :text_align
    alias :font_face_id= :font_face_id
    alias :font_face= :font_face
  end
end
