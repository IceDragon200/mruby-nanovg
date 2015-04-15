module Nanovg
  # Floating point Color
  class Color
    # @!attribute r
    #   @return [Float]
    attr_accessor :r
    # @!attribute g
    #   @return [Float]
    attr_accessor :g
    # @!attribute b
    #   @return [Float]
    attr_accessor :b
    # @!attribute a
    #   @return [Float]
    attr_accessor :a

    # @param [Float] r  red channel value
    # @param [Float] g  green channel value
    # @param [Float] b  blue channel value
    # @param [Float] a  alpha channel value
    def initialize(r = 0.0, g = 0.0, b = 0.0, a = 0.0)
    end

    # @param [Color] other
    # @return [self]
    def initialize_copy(other)
    end

    # Returns an Array with the values of each color channel
    #
    # @return [Array<Float>]
    def to_a
    end

    # Creates a new Color from the given RGB bytes
    # Each channel is expected to be a uint8 (1 byte, ranging from 0..255)
    #
    # @param [Integer] r
    # @param [Integer] g
    # @param [Integer] b
    # @return [Color]
    #
    # @example
    #   Nanovg::Color.rgba(178, 128, 96)
    def self.rgb(r, g, b)
    end

    # Creates a new Color from the given RGB floats
    #
    # @param [Float] r
    # @param [Float] g
    # @param [Float] b
    # @return [Color]
    #
    # @example
    #   Nanovg::Color.rgb(1.0, 0.7, 0.4)
    def self.rgbf(r, g, b)
    end

    # Creates a new Color from the given RGBA bytes
    # Each channel is expected to be a uint8 (1 byte, ranging from 0..255)
    #
    # @param [Integer] r
    # @param [Integer] g
    # @param [Integer] b
    # @param [Integer] a
    # @return [Color]
    #
    # @example
    #   Nanovg::Color.rgba(178, 128, 96, 198)
    def self.rgba(r, g, b, a)
    end

    # Creates a new Color from the given RGBA floats
    #
    # @param [Float] r
    # @param [Float] g
    # @param [Float] b
    # @param [Float] a
    # @return [Color]
    #
    # @example
    #   Nanovg::Color.rgb(1.0, 0.7, 0.4, 0.98)
    def self.rgbaf(r, g, b, a)
    end

    # Creates a new Color from the given Hue Saturation and Luminosity
    #
    # @param [Float] h
    # @param [Float] s
    # @param [Float] l
    # @return [Color]
    def self.hsl(h, s, l)
    end

    # Creates a new Color from the given Hue Saturation, Luminosity and Alpha
    #
    # @param [Float] h
    # @param [Float] s
    # @param [Float] l
    # @param [Float] a
    # @return [Color]
    def self.hsla(h, s, l, a)
    end

    # @param [Color] c1
    # @param [Color] c2
    # @param [Float] d
    # @return [Color]
    def self.lerp_rgba(c1, c2, d)
    end

    # @param [Color] c
    # @param [Integer] a
    # @return [Color]
    def self.trans(c, a)
    end

    # @param [Color] c
    # @param [Float] a
    # @return [Color]
    def self.transf(c, a)
    end
  end
end
