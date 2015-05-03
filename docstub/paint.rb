module Nanovg
  # A pattern or painting object
  class Paint
    # @!attribute xform
    #   @return [Transform]
    attr_accessor :xform

    # @!attribute extent
    #   @return [Array<Float>] 2 floats defining the extent
    attr_accessor :extent

    # @!attribute radius
    #   @return [Float]
    attr_accessor :radius

    # @!attribute feather
    #   @return [Float]
    attr_accessor :feather

    # @!attribute inner_color
    #   @return [Color]
    attr_accessor :inner_color

    # @!attribute outer_color
    #   @return [Color]
    attr_accessor :outer_color

    # @!attribute image
    #   @return [Integer]
    attr_accessor :image

    # Initializes the underlying Paint structure
    #
    # @return [self]
    def initialize
    end
  end
end
