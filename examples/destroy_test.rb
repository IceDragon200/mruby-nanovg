# Run this file if you want to test context destruction
GLFW.init

window = GLFW::Window.new(640, 480, 'Context Destroy')
window.make_current
GLEW.init

# create and destroy the context immediately
context = Nanovg::Context.new
context.destroy
context = nil

# start the GC, which should collect the context
GC.start

# now just watch this black screen safely I suppose...
until window.should_close?
  GL2.glClear GL2::GL_COLOR_BUFFER_BIT
  window.swap_buffers
  GLFW.poll_events
end
