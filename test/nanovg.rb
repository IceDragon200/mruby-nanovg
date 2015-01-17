assert('Nanovg type') do
  assert_kind_of(Module, Nanovg)
end

assert('Nanovg.rad_to_deg') do
  f = Nanovg.rad_to_deg(3.14)
  assert_kind_of(Float, f)
end

assert('Nanovg.deg_to_rad') do
  f = Nanovg.rad_to_deg(180)
  assert_kind_of(Float, f)
end
