module Nanovg
  include Winding
  include Solidity
  include LineCap
  include Align
  include ImageFlags
  include CreateFlags

  # General purpose flag for saying "there are no flags" instead of using a magic number.
  NO_FLAG = 0

  # @!group Color
  # (see Color.hsl)
  def self.hsl(h, s, l)
    Nanovg::Color.hsl(h, s, l)
  end

  # (see Color.rgb)
  def self.rgb(r, g, b)
    Nanovg::Color.rgb(r, g, b)
  end

  # (see Color.rgbf)
  def self.rgbf(r, g, b)
    Nanovg::Color.rgbf(r, g, b)
  end

  # (see Color.rgba)
  def self.rgba(r, g, b, a)
    Nanovg::Color.rgba(r, g, b, a)
  end

  # (see Color.rgbaf)
  def self.rgbaf(r, g, b, a)
    Nanovg::Color.rgbaf(r, g, b, a)
  end

  # (see Color.mono)
  def self.mono(value)
    Nanovg::Color.mono(value)
  end

  # (see Color.monof)
  def self.monof(value)
    Nanovg::Color.monof(value)
  end
  # @!endgroup Color
end

# shorthand alias for {Nanovg}
NVG = Nanovg
