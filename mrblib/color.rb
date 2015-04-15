module Nanovg
  class Color
    # Set all channels in the Color at once
    #
    # @param [Float] r
    # @param [Float] g
    # @param [Float] b
    # @param [Float] a
    # @return [self]
    #
    # @example
    #   color.set(1, 1, 0, 0.5)
    def set(r, g, b, a)
      self.r, self.g, self.b, self.a = r, g, b, a
      self
    end

    def self.mono(value)
      rgb(value, value, value)
    end

    def self.monof(value)
      rgbf(value, value, value)
    end
  end
end
