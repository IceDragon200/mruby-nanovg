assert('Nanovg::Color type') do
  assert_kind_of(Class, Nanovg::Color)
end

assert('Nanovg::Color#initialize') do
  c = Nanovg::Color.new
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color#initialize(r, g, b, a)') do
  c = Nanovg::Color.new(0.1, 0.2, 0.3, 0.4)
  assert_kind_of(Nanovg::Color, c)
  # floats are meh
  assert_float(0.1, c.r.round(1))
  assert_float(0.2, c.g.round(1))
  assert_float(0.3, c.b.round(1))
  assert_float(0.4, c.a.round(1))
end

assert('Nanovg::Color#initialize_copy') do
  c = Nanovg::Color.new
  c2 = c.dup
  assert_false(c.equal?(c2))
  assert_float(c.r, c2.r)
  assert_float(c.g, c2.g)
  assert_float(c.b, c2.b)
  assert_float(c.a, c2.a)
end

assert('Nanovg::Color#r') do
  c = Nanovg::Color.new
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
  c.r = 0.1
  assert_float(0.1, c.r.round(1))
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
end

assert('Nanovg::Color#g') do
  c = Nanovg::Color.new
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
  c.g = 0.1
  assert_float(0.0, c.r)
  assert_float(0.1, c.g.round(1))
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
end

assert('Nanovg::Color#b') do
  c = Nanovg::Color.new
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
  c.b = 0.1
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.1, c.b.round(1))
  assert_float(0.0, c.a)
end

assert('Nanovg::Color#a') do
  c = Nanovg::Color.new
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.0, c.a)
  c.a = 0.1
  assert_float(0.0, c.r)
  assert_float(0.0, c.g)
  assert_float(0.0, c.b)
  assert_float(0.1, c.a.round(1))
end

assert('Nanovg::Color.hsl') do
  c = Nanovg::Color.hsl(0, 1.0, 0.2)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.hsla') do
  c = Nanovg::Color.hsla(0, 1.0, 0.2, 0.5)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.lerp_rgba') do
  c0 = Nanovg::Color.new
  c1 = Nanovg::Color.new(0, 1.0, 0, 0.5)
  u = 0.5
  c = Nanovg::Color.lerp_rgba(c0, c1, u)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.rgb') do
  c = Nanovg::Color.rgb(255, 128, 98)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.rgbf') do
  c = Nanovg::Color.rgbf(0.1, 0.5, 0.3)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.rgba') do
  c = Nanovg::Color.rgba(255, 128, 98, 196)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.rgbaf') do
  c = Nanovg::Color.rgbaf(1.0, 0.5, 0.333, 0.75)
  assert_kind_of(Nanovg::Color, c)
end

assert('Nanovg::Color.trans') do
  c = Nanovg::Color.rgba(255, 128, 98, 196)
  assert_kind_of(Nanovg::Color, c)
  c2 = Nanovg::Color.trans(c, 128)
  assert_kind_of(Nanovg::Color, c2)
end

assert('Nanovg::Color.transf') do
  c = Nanovg::Color.rgbaf(1.0, 0.5, 0.333, 0.75)
  assert_kind_of(Nanovg::Color, c)
  c2 = Nanovg::Color.transf(c, 0.5)
  assert_kind_of(Nanovg::Color, c2)
end
