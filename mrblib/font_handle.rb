module Nanovg
  # A FontHandle is a helper class for managing font objects instead of passing
  # around its ID.
  class FontHandle
    # @!attribute [r] context
    #   @return [Context]
    attr_reader :context
    # @!attribute [r] font
    #   @return [Integer]
    attr_reader :font

    # @param [Context] context
    # @param [Integer] font
    def initialize(context, font)
      @context = context
      @font = font
    end

    # Returns the font handle
    alias :to_int :font
    # Returns the font handle
    alias :to_i :font
  end
end
