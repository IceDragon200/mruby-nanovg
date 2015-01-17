module Nanovg
  class FontHandle
    attr_reader :context
    attr_reader :font

    def initialize(context, font)
      @context = context
      @font = font
    end

    def to_int
      @font
    end

    def to_i
      @font
    end
  end
end
