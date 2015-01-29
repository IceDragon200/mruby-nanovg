def save_screenshot(width, height, flag, filename)
  #
end

GRAPH_RENDER_FPS = 0
GRAPH_RENDER_MS = 1
GRAPH_RENDER_PERCENT = 2

class PerfGraph
  GRAPH_HISTORY_COUNT = 100

  attr_accessor :head
  attr_accessor :style
  attr_accessor :name
  attr_accessor :values

  def initialize(style, name)
    @head = 0
    @style = style
    @name = name
    @values = Array.new(GRAPH_HISTORY_COUNT, 0.0)
  end

  def update(delta)
    @head = (@head + 1) % GRAPH_HISTORY_COUNT
    @values[@head] = delta
  end

  def render(vg, x, y)
    avg = average

    w = 200
    h = 35

    vg.path do |v|
      v.rect(x, y, w, h)
      v.fill_color(NVG.rgba(0, 0, 0, 128))
      v.fill
    end

    vg.path do |vgg|
      vgg.move_to(x, y + h)
      case @style
      when GRAPH_RENDER_FPS
        GRAPH_HISTORY_COUNT.times do |i|
          v = 1.0 / (0.00001 + @values[(@head + i) % GRAPH_HISTORY_COUNT])
          v = 80.0 if v > 80.0
          vx = x + (i.to_f / (GRAPH_HISTORY_COUNT - 1)) * w
          vy = y + h - ((v / 80.0) * h)
          vgg.line_to(vx, vy)
        end
      when GRAPH_RENDER_PERCENT
        GRAPH_HISTORY_COUNT.times do |i|
          v = @values[(@head + i) % GRAPH_HISTORY_COUNT] * 1.0
          v = 100.0 if v > 100.0
          vx = x + (i.to_f / (GRAPH_HISTORY_COUNT - 1)) * w
          vy = y + h - ((v / 100.0) * h)
          vgg.line_to(vx, vy)
        end
      when GRAPH_RENDER_MS
        GRAPH_HISTORY_COUNT.times do |i|
          v = @values[(@head + i) % GRAPH_HISTORY_COUNT] * 1000.0
          v = 20.0 if v > 20.0
          vx = x + (i.to_f / (GRAPH_HISTORY_COUNT - 1)) * w
          vy = y + h - ((v / 20.0) * h)
          vgg.line_to(vx, vy)
        end
      end
      vgg.line_to(x + w, y + h)
      vgg.fill_color NVG.rgba(255, 192, 0, 128)
      vgg.fill
    end

    vg.font_face('sans')

    unless @name.empty?
      vg.font_size 18.0
      vg.text_align NVG::ALIGN_LEFT | NVG::ALIGN_TOP
      vg.fill_color NVG.rgba(240, 240, 240, 255)
      vg.text(x + 3, y + 1, @name)
    end

    case @style
    when GRAPH_RENDER_FPS
      vg.font_size(18.0)
      vg.text_align(NVG::ALIGN_RIGHT | NVG::ALIGN_TOP)
      vg.fill_color(NVG.rgba(240, 240, 240, 255))
      str = sprintf('%.2f FPS', 1.0 / avg)
      vg.text(x + w - 3, y + 1, str)

      vg.font_size(15.0)
      vg.text_align(NVG::ALIGN_RIGHT | NVG::ALIGN_BOTTOM)
      vg.fill_color(NVG.rgba(240, 240, 240, 160))
      str = sprintf('%.2f ms', avg * 1000.0)
      vg.text(x + w - 3, y + h - 1, str)
    when GRAPH_RENDER_PERCENT
      vg.font_size(18.0)
      vg.text_align(NVG::ALIGN_RIGHT | NVG::ALIGN_TOP)
      vg.fill_color(NVG.rgba(240, 240, 240, 255))
      str = sprintf('%.1f %%', avg * 1.0)
      vg.text(x + w - 3, y + 1, str)
    else
      vg.font_size(18.0)
      vg.text_align(NVG::ALIGN_RIGHT | NVG::ALIGN_TOP)
      vg.fill_color(NVG.rgba(240, 240, 240, 255))
      str = sprintf('%.2f ms', avg * 1000.0)
      vg.text(x + w - 3, y + 1, str)
    end
  end

  def average
    @values.reduce(:+).to_f / GRAPH_HISTORY_COUNT.to_f
  end
end

class GPUtimer
  GPU_QUERY_COUNT = 5

  attr_accessor :supported
  attr_accessor :cur
  attr_accessor :ret
  attr_accessor :queries

  def initialize
    @supported = false
    @cur = 0
    @ret = 0
    @queries = Array.new(GPU_QUERY_COUNT, 0)
  end

  def start
  end

  def stop
  end
end

class GL2Demo
  attr_reader :state

  def initialize
    @state = {
      blowup: false,
      screenshot: false,
      premult: false
    }
  end

  def errorcb(error, desc)
    print "GLFW error #{error}: #{desc}"
  end

  def key(window, key, scancode, action, mods)
    if action == GLFW::PRESS
      case key
      when GLFW::KEY_ESCAPE
        window.should_close = true
      when GLFW::KEY_SPACE
        @state[:blowup] = !@state[:blowup]
      when GLFW::KEY_S
        @state[:screenshot] = true
      when GLFW::KEY_P
        @state[:premult] = !@state[:premult]
      end
    end
  end

  def draw_eyes(vg, x, y, w, h, mx, my, t)
    ex = w * 0.23
    ey = h * 0.5
    lx = x + ex
    ly = y + ey
    rx = x + w - ex
    ry = y + ey
    br = (ex < ey ? ex : ey) * 0.5
    blink = 1 - (Math.sin(t * 0.5) ** 200) * 0.8

    bg = vg.linear_gradient(x, y + h * 0.5, x + w * 0.1, y + h,
                            NVG.rgba(0, 0, 0, 32), NVG.rgba(0, 0, 0, 16));
    vg.path do |v|
      v.ellipse(lx + 3.0, ly + 16.0, ex, ey)
      v.ellipse(rx + 3.0, ry + 16.0, ex, ey)
      v.fill_paint(bg)
      v.fill
    end
    bg = vg.linear_gradient(x, y + h * 0.25, x + w * 0.1, y + h,
                            NVG.rgba(220, 220, 220, 255), NVG.rgba(128, 128, 128, 255));
    vg.path do |v|
      v.ellipse(lx, ly, ex, ey)
      v.ellipse(rx, ry, ex, ey)
      v.fill_paint(bg)
      v.fill
    end

    dx = (mx - rx) / (ex * 10)
    dy = (my - ry) / (ey * 10)
    d = Math.sqrt(dx * dx + dy * dy)

    if (d > 1.0)
      dx /= d
      dy /= d
    end
    dx *= ex * 0.4
    dy *= ey * 0.5

    vg.path do |v|
      v.ellipse(lx + dx, ly + dy + ey * 0.25 * (1 - blink), br, br * blink)
      v.fill_color(NVG.rgba(32, 32, 32, 255))
      v.fill
    end

    dx = (mx - rx) / (ex * 10)
    dy = (my - ry) / (ey * 10)
    d = Math.sqrt(dx * dx + dy * dy)

    if (d > 1.0)
      dx /= d
      dy /= d
    end
    dx *= ex * 0.4
    dy *= ey * 0.5

    vg.path do |v|
      v.ellipse(rx + dx, ry + dy + ey * 0.25 * (1 - blink), br, br * blink)
      v.fill_color(NVG.rgba(32, 32, 32, 255))
      v.fill
    end

    gloss = vg.radial_gradient(lx - ex * 0.25, ly - ey * 0.5, ex * 0.1, ex * 0.75, NVG.rgba(255, 255, 255, 128), NVG.rgba(255, 255, 255, 0))
    vg.path do |v|
      v.ellipse(lx, ly, ex, ey)
      v.fill_paint(gloss)
      v.fill
    end

    gloss = vg.radial_gradient(rx - ex * 0.25, ry - ey * 0.5, ex * 0.1, ex * 0.75, NVG.rgba(255, 255, 255, 128), NVG.rgba(255, 255, 255, 0))
    vg.path do |v|
      v.ellipse(rx, ry, ex, ey)
      v.fill_paint(gloss)
      v.fill
    end
  end

  def draw_paragraph(vg, x, y, w, h, mx, my)
    # TODO
  end

  def draw_graph(vg, x, y, w, h, t)
    samples = []
    sx = []
    sy = []
    dx = w / 5.0
    samples[0] = (1 + Math.sin(t * 1.2345 + Math.cos(t * 0.33457) * 0.44)) * 0.5
    samples[1] = (1 + Math.sin(t * 0.68363 + Math.cos(t * 1.3) * 1.55)) * 0.5
    samples[2] = (1 + Math.sin(t * 1.1642 + Math.cos(t * 0.3345) * 1.24)) * 0.5
    samples[3] = (1 + Math.sin(t * 0.56345 + Math.cos(t * 1.63) * 0.14)) * 0.5
    samples[4] = (1 + Math.sin(t * 1.6245 + Math.cos(t * 0.254) * 0.3)) * 0.5
    samples[5] = (1 + Math.sin(t * 0.345 + Math.cos(t * 0.03) * 0.6)) * 0.5

    6.times do |i|
      sx[i] = x + i * dx
      sy[i] = y + h * samples[i] * 0.8
    end

    # Graph Background
    bg = vg.linear_gradient(x, y, x, y + h, NVG.rgba(0, 160, 192, 0), NVG.rgba(0, 160, 192, 64))
    vg.path do |nvg|
      nvg.move_to(sx[0], sy[0])
      1.upto(5) do |i|
        nvg.bezier_to(sx[i - 1] * dx * 0.5, sy[i - 1], sx[i] - dx * 0.5, sy[i], sx[i], sy[i])
      end
      nvg.line_to(x + w, y + h)
      nvg.line_to(x, y + h)
      nvg.fill_paint(bg)
      nvg.fill
    end

    # Graph Line
    vg.path do |nvg|
      nvg.move_to(sx[0], sy[0])
      1.upto(5) do |i|
        nvg.bezier_to(sx[i - 1] + dx * 0.5, sy[i - 1] + 2, sx[i] - dx * 0.5, sy[i] + 2, sx[i], sy[i] + 2)
      end
      nvg.stroke_color(NVG.rgba(0, 0, 0, 32))
      nvg.stroke_width(3.0)
      nvg.stroke
    end

    vg.path do |nvg|
      nvg.move_to(sx[0], sy[0])
      1.upto(5) do |i|
        nvg.bezier_to(sx[i - 1] + dx * 0.5, sy[i - 1], sx[i ]- dx * 0.5, sy[i], sx[i], sy[i])
      end
      nvg.stroke_color(NVG.rgba(0, 160, 192, 255))
      nvg.stroke_width(3.0)
      nvg.stroke
    end

    # Graph sample pos
    6.times do |i|
      bg = vg.radial_gradient(sx[i], sy[i] + 2, 3.0, 8.0, NVG.rgba(0, 0, 0, 32), NVG.rgba(0, 0, 0, 0))
      vg.path do |nvg|
        nvg.rect(sx[i] - 10, sy[i] - 10 + 2, 20, 20)
        nvg.fill_paint(bg)
        nvg.fill
      end
    end

    vg.path do |nvg|
      6.times do |i|
        nvg.circle(sx[i], sy[i], 4.0)
      end
      nvg.fill_color(NVG.rgba(0, 160, 192, 255))
      nvg.fill
    end
    vg.path do |nvg|
      6.times do |i|
        nvg.circle(sx[i], sy[i], 2.0)
      end
      nvg.fill_color(NVG.rgba(220, 220, 220, 255))
      nvg.fill
    end

    vg.stroke_width(1.0)
  end

  def draw_colorwheel(vg, x, y, w, h, t)
    # TODO
  end

  def draw_lines(vg, x, y, w, h, t)
    pad = 5.0
    s = w / 9.0 - pad * 2
    pts = []
    joins = [NVG::MITER, NVG::ROUND, NVG::BEVEL]
    caps = [NVG::BUTT, NVG::ROUND, NVG::SQUARE]

    vg.spork do
      pts[0] = -s * 0.25 + Math.cos(t * 0.3) * s * 0.5
      pts[1] = Math.sin(t * 0.3) * s * 0.5
      pts[2] = -s * 0.25
      pts[3] = 0
      pts[4] = s * 0.25
      pts[5] = 0
      pts[6] = s * 0.25 + Math.cos(-t * 0.3) * s * 0.5
      pts[7] = Math.sin(-t * 0.3) * s * 0.5

      3.times do |i|
        3.times do |j|
          fx = x + s * 0.5 + (i * 3 + j) / 9.0 * w + pad
          fy = y - s * 0.5 + pad

          vg.line_cap(caps[i])
          vg.line_join(joins[i])

          vg.stroke_width(s * 0.3)
          vg.stroke_color(NVG.rgba(0, 0, 0, 160))
          vg.path do
            vg.move_to(fx + pts[0], fy + pts[1])
            vg.move_to(fx + pts[2], fy + pts[3])
            vg.move_to(fx + pts[4], fy + pts[5])
            vg.move_to(fx + pts[6], fy + pts[7])
            vg.stroke
          end

          vg.line_cap(NVG::BUTT)
          vg.line_cap(NVG::BEVEL)

          vg.stroke_width(1.0)
          vg.stroke_color(NVG.rgba(0, 192, 255, 255))
          vg.path do
            vg.move_to(fx + pts[0], fy + pts[1])
            vg.move_to(fx + pts[2], fy + pts[3])
            vg.move_to(fx + pts[4], fy + pts[5])
            vg.move_to(fx + pts[6], fy + pts[7])
            vg.stroke
          end
        end
      end
    end
  end

  def draw_widths(vg, x, y, width)
    # equivalent of save + restore
    vg.spork do |nvg|
      nvg.stroke_color(NVG.rgba(0, 0, 0, 255))

      20.times do |i|
        w = (i + 0.5) * 0.1
        nvg.stroke_width(w)
        nvg.path do
          nvg.move_to(x, y)
          nvg.line_to(x + width, y + width * 0.3)
          nvg.stroke
        end
        y += 10
      end
    end
  end

  def draw_caps(vg, x, y, width)
    caps = [NVG::BUTT, NVG::ROUND, NVG::SQUARE]
    line_width = 8.0

    vg.spork do |nvg|
      nvg.path do
        nvg.rect(x - line_width / 2, y, width + line_width, 40)
        nvg.fill_color(NVG.rgba(255, 255, 255, 32))
        nvg.fill
      end

      nvg.path do
        nvg.rect(x, y, width, 40)
        nvg.fill_color(NVG.rgba(255, 255, 255, 32))
        nvg.fill
      end

      nvg.stroke_width(line_width)
      3.times do |i|
        nvg.line_cap(caps[i])
        nvg.stroke_color(NVG.rgba(0, 0, 0, 255))
        nvg.path do
          nvg.move_to(x, y + i * 10 + 5)
          nvg.line_to(x + width, y + i * 10 + 5)
          nvg.stroke
        end
      end
    end
  end

  def draw_scissor(vg, x, y, t)
    vg.spork do
      vg.translate(x, y)
      vg.rotate(NVG.deg_to_rad(5))
      vg.path do
        vg.rect(-20, -20, 60, 40)
        vg.fill_color(NVG.rgba(255, 0, 0, 255))
        vg.fill
      end
      vg.scissor(-20, -20, 60, 40)

      vg.translate(40, 0)
      vg.rotate(t)

      vg.spork do
        vg.reset_scissor
        vg.path do
          vg.rect(-20, -10, 60, 30)
          vg.fill_color(NVG.rgba(255, 128, 0, 64))
          vg.fill
        end
      end

      vg.intersect_scissor(-20, -10, 60, 30)
      vg.path do
        vg.rect(-20, -10, 60, 30)
        vg.fill_color(NVG.rgba(255, 128, 0, 255))
        vg.fill
      end
    end
  end

  def draw_window(vg, title, x, y, w, h)
    corner_radius = 3.0

    vg.spork do
      vg.path do
        vg.rounded_rect(x, y, w, h, corner_radius)
        vg.fill_color(NVG.rgba(28, 30, 34, 192))
        vg.fill
      end

      shadow_paint = vg.box_gradient(x, y + 2, w, h, corner_radius * 2, 10, NVG.rgba(0, 0, 0, 128), NVG.rgba(0, 0, 0, 0))
      vg.path do
        vg.rect(x - 10, y - 10, w + 20, h + 30)
        vg.rounded_rect(x, y, w, h, corner_radius)
        vg.path_winding(NVG::HOLE)
        vg.fill_paint(shadow_paint)
        vg.fill
      end

      header_paint = vg.linear_gradient(x, y, x, y + 15, NVG.rgba(255, 255, 255, 8), NVG.rgba(0, 0, 0, 16))
      vg.path do
        vg.rounded_rect(x + 1, y + 1, w - 2, 30, corner_radius - 1)
        vg.fill_paint(header_paint)
        vg.fill
      end

      vg.path do
        vg.move_to(x + 0.5, y + 0.5 + 30)
        vg.line_to(x + 0.5 + w - 1, y + 0.5 + 30)
        vg.stroke_color(NVG.rgba(0, 0, 0, 32))
        vg.stroke
      end

      vg.font_size(18.0)
      vg.font_face('sans-bold')
      vg.text_align(NVG::ALIGN_CENTER | NVG::ALIGN_MIDDLE)

      vg.font_blur(2)
      vg.fill_color(NVG.rgba(0, 0, 0, 128))
      vg.text(x + w / 2, y + 16 + 1, title)

      vg.font_blur(0)
      vg.fill_color(NVG.rgba(220, 220, 200, 160))
      vg.text(x + w / 2, y + 16, title)
    end
  end

  def draw_search_box(vg, text, x, y, w, h)
    icon = []
    corner_radius = h / 2 - 1

    bg = vg.box_gradient(x, y + 1.5, w, h, h / 2, 5, NVG.rgba(0, 0, 0, 16), NVG.rgba(0, 0, 0, 92))
    vg.path do
      vg.rounded_rect(x, y, w, h, corner_radius)
      vg.fill_paint(bg)
      vg.fill
    end

    vg.font_size(h * 1.3)
    vg.font_face('icons')
    vg.fill_color(NVG.rgba(255, 255, 255, 64))
    vg.text_align(NVG::ALIGN_CENTER | NVG::ALIGN_MIDDLE)
    vg.text(x + h * 0.55, y + h * 0.55, '🔍')
  end

  def render(vg, mx, my, width, height, t, blowup, data = nil)
    draw_eyes(vg, width - 250, 50, 150, 100, mx, my, t)
    draw_paragraph(vg, width - 450, 50, 150, 100, mx, my)
    draw_graph(vg, 0, height / 2, width, height / 2, t)
    draw_colorwheel(vg, width - 300, height - 300, 250.0, 250.0, t)

    # Line joints
    draw_lines(vg, 120, height - 50, 600, 50, t)

    # Line caps
    draw_widths(vg, 10, 50, 30)

    # line caps
    draw_caps(vg, 10, 300, 30)

    draw_scissor(vg, 50, height - 80, t)

    vg.spork do
      if blowup
        vg.rotate(Math.sin(t * 0.3) * 5.0 / 180.0 * Math::PI)
        vg.scale(2.0, 2.0)
      end

      draw_window(vg, 'Widgets `n Stuff', 50, 50, 300, 400)
      x = 60
      y = 95
      draw_search_box(vg, 'Search', x, y, 280, 25)
    end
  end

  def load_demo_data(vg)
    data = {}
    data[:images] = []
    12.times do |i|
      filename = "images/image#{i + 1}.jpg"
      data[:images][i] = vg.create_image(filename, 0)
      fail "Could not load #{filename}" if data[:images][i] == 0
    end
    data[:font_icons] = vg.create_font('icons', 'entypo.ttf')
    data[:font_normal] = vg.create_font('sans', 'Roboto-Regular.ttf')
    data[:font_bold] = vg.create_font('sans-bold', 'Roboto-Bold.ttf')
    data
  end

  def run
    GLFW.init
    #GLFW.set_error_callback do |*args, &block|
    #  self.errorcb(*args, &block)
    #end

    window = GLFW::Window.new(1000, 600, 'mruby NanoVG', nil, nil)

    window.set_key_callback do |*args, &block|
      self.key(*args, &block)
    end

    window.make_current

    GLEW.init

    vg = NVG::Context.new(NVG::ANTIALIAS | NVG::STENCIL_STROKES | NVG::DEBUG)
    data = load_demo_data(vg)

    fps = PerfGraph.new(GRAPH_RENDER_FPS, "Frame Time")

    GLFW.swap_interval = 0
    GLFW.time = 0

    prevt = GLFW.time

    until window.should_close?
      t = GLFW.time
      dt = t - prevt
      prevt = t
      fps.update(dt)

      mx, my = *window.cursor_pos
      win_width, win_height = *window.window_size
      fb_width, fb_height = *window.framebuffer_size

      px_ratio = fb_width.to_f / win_width

      GL2.glViewport(0, 0, fb_width, fb_height)

      if @state[:premult]
        GL2.glClearColor(0, 0, 0, 0)
      else
        GL2.glClearColor(0.3, 0.3, 0.32, 1.0)
      end

      GL2.glClear(GL2::GL_COLOR_BUFFER_BIT |
                  GL2::GL_DEPTH_BUFFER_BIT |
                  GL2::GL_STENCIL_BUFFER_BIT)

      vg.draw(win_width, win_height, px_ratio) do
        render vg, mx, my, win_width, win_height, t, @state[:blowup], data
        fps.render vg, 5, 5
      end

      if @state[:screenshot]
        @state[:screenshot] = false
        save_screenshot(fb_width, fb_height, premult, "dump.png")
      end

      window.swap_buffers
      GLFW.poll_events
    end
  end
end

def main
  demo = GL2Demo.new

  demo.run
end

main
