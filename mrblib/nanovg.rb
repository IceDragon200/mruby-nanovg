module Nanovg
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
end

# alias
NVG = Nanovg
