module Nanovg
  class Color
    def self.mono(value)
      rgb(value, value, value)
    end

    def self.monof(value)
      rgbf(value, value, value)
    end
  end
end
