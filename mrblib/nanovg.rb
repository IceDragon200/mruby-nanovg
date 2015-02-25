module Nanovg
  def self.hsl(*args)
    Nanovg::Color.hsl(*args)
  end

  def self.rgb(*args)
    Nanovg::Color.rgb(*args)
  end

  def self.rgbf(*args)
    Nanovg::Color.rgbf(*args)
  end

  def self.rgba(*args)
    Nanovg::Color.rgba(*args)
  end

  def self.rgbaf(*args)
    Nanovg::Color.rgbaf(*args)
  end

  def self.mono(value)
    Nanovg::Color.mono(value)
  end

  def self.monof(value)
    Nanovg::Color.monof(value)
  end
end

# alias
NVG = Nanovg
