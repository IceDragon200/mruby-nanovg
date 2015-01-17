GLFW.default_window_hints
window = GLFW::Window.new(640, 480, 'My Window')
window.make_current

Nanovg.init

assert('Nanovg::Context type') do
  assert_kind_of(Class, Nanovg::Context)
end

assert('Nanovg::Context#draw') do
  c = Nanovg::Context.new
  c.draw(640, 480, 1.0) do
    # do some drawing I guess.
  end
end
