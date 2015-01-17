assert('Nanovg::Transform type') do
  assert_kind_of(Class, Nanovg::Transform)
end

assert('Nanovg::Transform') do
  t = Nanovg::Transform.new
  assert_kind_of(Nanovg::Transform, t)
end
