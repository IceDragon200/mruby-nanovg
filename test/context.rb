#GLFW.init
#GLFW.default_window_hints
#window = GLFW::Window.new(640, 480, 'mruby-nanovg Test')
#window.make_current
#
#GLEW.init
#
#assert('Nanovg::Context type') do
#  assert_kind_of(Class, Nanovg::Context)
#end
#
#assert('Nanovg::Context#draw') do
#  c = Nanovg::Context.new
#  GL2.glClear(GL2::GL_COLOR_BUFFER_BIT)
#  c.draw(640, 480, 1.0) do |ctx|
#    # do some drawing I guess.
#    ctx.stroke_color(Nanovg::Color.rgbf(1.0, 1.0, 1.0))
#    ctx.stroke_width(2)
#
#    #ctx.translate(0, 0)
#    #ctx.translate(320, 0)
#    #ctx.translate(320, 240)
#    #ctx.translate(0, 240)
#    #ctx.translate(0, 0)
#  end
#  window.swap_buffers
#end
#
#60.times do
#  break if window.should_close?
#  #window.swap_buffers
#  GLFW.poll_events
#end
#
