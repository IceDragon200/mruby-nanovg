def save_screenshot(width, height, flag, filename)
  #
end

GRAPH_RENDER_FPS = 0
GRAPH_RENDER_MS = 1
GRAPH_RENDER_PERCENT = 2

ICON_SEARCH = "\u{1F50D}"
ICON_CIRCLED_CROSS = "\u{2716}"
ICON_CHEVRON_RIGHT = "\u{E75E}"
ICON_CHECK = "\u{2713}"
ICON_LOGIN = "\u{E740}"
ICON_TRASH = "\u{E729}"

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

  def is_black?(col)
    return col.r == 0.0 && col.g == 0.0 && col.b == 0.0 && col.a == 0.0
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
                            NVG.rgba(0, 0, 0, 32), NVG.rgba(0, 0, 0, 16))
    vg.path do |v|
      v.ellipse(lx + 3.0, ly + 16.0, ex, ey)
      v.ellipse(rx + 3.0, ry + 16.0, ex, ey)
      v.fill_paint(bg)
      v.fill
    end
    bg = vg.linear_gradient(x, y + h * 0.25, x + w * 0.1, y + h,
                            NVG.rgba(220, 220, 220, 255), NVG.rgba(128, 128, 128, 255))
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

  def draw_paragraph(vg, x, y, width, _height, mx, my)
    text = "This is longer chunk of text.\n  \n  Would have used lorem ipsum but she    was busy jumping over the lazy dog with the fox and all the men who came to the aid of the party."
    lnum = 0
    gutter = 0
    bounds = NVG::Transform.new
    gx = x
    gy = y
    vg.spork do
      vg.font_size 18.0
      vg.font_face "sans"
      vg.text_align NVG::ALIGN_LEFT | NVG::ALIGN_TOP
      _, _, lineh = vg.text_metrics

      vg.text_break_lines text, width do |row_string, row_width, min_x, max_x|
        hit = mx > x && mx < (x + width) && my >= y && my < (y + lineh)
        vg.path do
          vg.fill_color NVG.rgba(255, 255, 255, hit ? 64 : 16)
          vg.rect x, y, row_width, lineh
          vg.fill
        end
        vg.fill_color NVG.rgba(255, 255, 255, 255)
        vg.text x, y, row_string
        if hit
          caretx = (mx < (x + row_width / 2)) ? x : x + row_width
          px = x
          glyphs = vg.text_glyph_positions x, y, row_string
          glyphs.each_with_index do |gylph, j|
            x0 = gylph[0]
            x1 = j + 1 < row_string.size ? glyphs[j + 1][0] : x + row_width
            gx = x0 * 0.3 + x1 * 0.7
            if mx >= px && mx < gx
              caretx = glyphs[j][0]
            end
            px = gx
          end
          vg.path do
            vg.fill_color NVG.rgba(255, 192, 0, 255)
            vg.rect caretx, y, 1, lineh
            vg.fill
          end

          gutter = lnum + 1
          gx = x - 10
          gy = y + (lineh / 2)
        end
        lnum = lnum + 1
        y += lineh
      end

      if gutter > 0
        txt = gutter.to_s
        vg.font_size 13.0
        vg.text_align NVG::ALIGN_RIGHT | NVG::ALIGN_MIDDLE
        vg.text_bounds gx, gy, txt, bounds
        vg.path do
          vg.fill_color NVG.rgba(255, 192, 0, 255)
          vg.rounded_rect bounds[0].to_i - 4, bounds[1].to_i - 2, (bounds[2] - bounds[0]).to_i + 8, (bounds[3] - bounds[1]).to_i + 4, ((bounds[3] - bounds[1]).to_i + 4) / 2 - 1
          vg.fill
        end
        vg.fill_color NVG.rgba(32, 32, 32, 255)
        vg.text gx, gy, txt
      end

      y += 20.0

      vg.font_size 13.0
      vg.text_align NVG::ALIGN_LEFT | NVG::ALIGN_TOP
      vg.text_line_height 1.2

      tooltip_text = "Hover your mouse over the text to see calculated caret position."
      vg.text_box_bounds x, y, 150, tooltip_text, bounds

      gx = ((mx - (bounds[0] + bounds[2]) * 0.5) / (bounds[0] - bounds[2])).abs
      gy = ((my - (bounds[1] + bounds[3]) * 0.5) / (bounds[1] - bounds[3])).abs
      a = [[[gx, gy].max - 0.5, 1].min, 0].max
      vg.global_alpha a
      vg.path do
        vg.fill_color NVG.rgba(220, 220, 220, 255)
        vg.rounded_rect bounds[0] - 2, bounds[1] - 2, (bounds[2] - bounds[0]).to_i + 4, (bounds[3] - bounds[1]).to_i + 4, 3
        px = ((bounds[2] + bounds[0]) / 2).to_i
        vg.move_to px, bounds[1] - 10
        vg.line_to px + 7, bounds[1] + 1
        vg.line_to px - 7, bounds[1] + 1
        vg.fill
      end
      vg.fill_color NVG.rgba(0, 0, 0, 220)
      vg.text_box x, y, 150, tooltip_text
    end
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
        nvg.bezier_to(sx[i - 1] + dx * 0.5, sy[i - 1], sx[i] - dx * 0.5, sy[i], sx[i], sy[i])
      end
      nvg.line_to(x + w, y + h)
      nvg.line_to(x, y + h)
      nvg.fill_paint(bg)
      nvg.fill
    end

    # Graph Line
    vg.path do |nvg|
      nvg.move_to(sx[0], sy[0] + 2)
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
        nvg.bezier_to(sx[i - 1] + dx * 0.5, sy[i - 1], sx[i] - dx * 0.5, sy[i], sx[i], sy[i])
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
    hue = Math.sin(t * 0.12)

    vg.spork do
      cx = x + w*0.5
      cy = y + h*0.5
      r1 = (w < h ? w : h) * 0.5 - 5.0
      r0 = r1 - 20.0
      # half a pixel arc length in radians (2pi cancels out).
      aeps = 0.5 / r1

      6.times do |i|
        a0 = i / 6.0 * Math::PI * 2.0 - aeps
        a1 = (i+1.0) / 6.0 * Math::PI * 2.0 + aeps
        vg.begin_path
        vg.arc(cx, cy, r0, a0, a1, NVG::CW)
        vg.arc(cx, cy, r1, a1, a0, NVG::CCW)
        vg.close_path
        ax = cx + Math.cos(a0) * (r0 + r1) * 0.5
        ay = cy + Math.sin(a0) * (r0 + r1) * 0.5
        bx = cx + Math.cos(a1) * (r0 + r1) * 0.5
        by = cy + Math.sin(a1) * (r0 + r1) * 0.5
        paint = vg.linear_gradient(ax,ay, bx,by, NVG.hsla(a0/(Math::PI*2),1.0,0.55,255), NVG.hsla(a1/(Math::PI*2),1.0,0.55,255))
        vg.fill_paint(paint)
        vg.fill
      end

      vg.path do
        vg.circle(cx,cy, r0 - 0.5)
        vg.circle(cx,cy, r1 + 0.5)
        vg.stroke_color(NVG.rgba(0,0,0,64))
        vg.stroke_width(1.0)
        vg.stroke
      end

      # Selector
      vg.spork do
        vg.translate(cx, cy)
        vg.rotate(hue * Math::PI * 2)

        # Marker on
        vg.stroke_width(2.0)
        vg.path do
          vg.rect(r0-1,-3,r1-r0+2,6)
          vg.stroke_color(NVG.rgba(255,255,255,192))
          vg.stroke
        end

        paint = vg.box_gradient(r0-3,-5,r1-r0+6,10, 2,4, NVG.rgba(0,0,0,128), NVG.rgba(0,0,0,0))
        vg.path do
          vg.rect(r0-2-10,-4-10,r1-r0+4+20,8+20)
          vg.rect(r0-2,-4,r1-r0+4,8)
          vg.path_winding(NVG::Solidity::HOLE)
          vg.fill_paint(paint)
          vg.fill
        end

        # Center triangle
        r = r0 - 6
        ax = Math.cos(120.0/180.0*Math::PI) * r
        ay = Math.sin(120.0/180.0*Math::PI) * r
        bx = Math.cos(-120.0/180.0*Math::PI) * r
        by = Math.sin(-120.0/180.0*Math::PI) * r
        vg.begin_path
        vg.move_to(r, 0)
        vg.line_to(ax, ay)
        vg.line_to(bx, by)
        vg.close_path
        paint = vg.linear_gradient(r,0, ax,ay, NVG.hsla(hue,1.0,0.5,255), NVG.rgba(255,255,255,255))
        vg.fill_paint(paint)
        vg.fill
        paint = vg.linear_gradient((r+ax)*0.5,(0+ay)*0.5, bx,by, NVG.rgba(0,0,0,0), NVG.rgba(0,0,0,255))
        vg.fill_paint(paint)
        vg.fill
        vg.stroke_color(NVG.rgba(0,0,0,64))
        vg.stroke

        # Select circle on triangle
        ax = Math.cos(120.0 / 180.0 * Math::PI) * r * 0.3
        ay = Math.sin(120.0 / 180.0 * Math::PI) * r * 0.4
        vg.stroke_width(2.0)
        vg.path do
          vg.circle(ax, ay, 5)
          vg.stroke_color(NVG.rgba(255,255,255,192))
          vg.stroke
        end

        paint = vg.radial_gradient(ax,ay, 7,9, NVG.rgba(0,0,0,64), NVG.rgba(0,0,0,0))
        vg.path do
          vg.rect(ax-20,ay-20,40,40)
          vg.circle(ax,ay,7)
          vg.path_winding(NVG::HOLE)
          vg.fill_paint(paint)
          vg.fill
        end
      end
    end
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
          vg.line_join(joins[j])

          vg.stroke_width(s * 0.3)
          vg.stroke_color(NVG.rgba(0, 0, 0, 160))
          vg.path do
            vg.move_to(fx + pts[0], fy + pts[1])
            vg.line_to(fx + pts[2], fy + pts[3])
            vg.line_to(fx + pts[4], fy + pts[5])
            vg.line_to(fx + pts[6], fy + pts[7])
            vg.stroke
          end

          vg.line_cap(NVG::BUTT)
          vg.line_join(NVG::BEVEL)

          vg.stroke_width(1.0)
          vg.stroke_color(NVG.rgba(0, 192, 255, 255))
          vg.path do
            vg.move_to(fx + pts[0], fy + pts[1])
            vg.line_to(fx + pts[2], fy + pts[3])
            vg.line_to(fx + pts[4], fy + pts[5])
            vg.line_to(fx + pts[6], fy + pts[7])
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
    vg.text(x + h * 0.55, y + h * 0.55, ICON_SEARCH)

    vg.font_size(20)
    vg.font_face('sans')
    vg.fill_color(NVG.rgba(255, 255, 255, 32))
    vg.text_align(NVG::ALIGN_LEFT | NVG::ALIGN_MIDDLE)
    vg.text(x + h * 1.05, y + h * 0.5, text)

    vg.font_size(h * 1.3)
    vg.font_face('icons')
    vg.fill_color(NVG.rgba(255, 255, 255, 32))
    vg.text_align(NVG::ALIGN_CENTER | NVG::ALIGN_MIDDLE)
    vg.text(x + h * 0.55, y + h * 0.55, ICON_CIRCLED_CROSS)
  end

  def draw_drop_down(vg, text, x, y, w, h)
    bg = vg.linear_gradient(x, y, x, y + h, NVG.rgba(255, 255, 255, 16), NVG.rgba(0, 0, 0, 16))
    corner_radius = 4.0
    vg.path do
      vg.rounded_rect(x + 1, y + 1, w - 2, h - 2, corner_radius - 1)
      vg.fill_paint(bg)
      vg.fill
    end

    vg.path do
      vg.rounded_rect(x + 0.5,y+0.5, w-1,h-1, corner_radius - 0.5)
      vg.stroke_color(NVG.rgba(0,0,0,48))
      vg.stroke
    end

    vg.font_size(20.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,160))
    vg.text_align(NVG::ALIGN_LEFT | NVG::ALIGN_MIDDLE)
    vg.text(x + h * 0.3, y + h * 0.5, text)

    vg.font_size(h * 1.3)
    vg.font_face("icons")
    vg.fill_color(NVG.rgba(255,255,255,64))
    vg.text_align(NVG::ALIGN_CENTER|NVG::ALIGN_MIDDLE)
    vg.text(x + w - h * 0.5, y + h * 0.5, ICON_CHEVRON_RIGHT)
  end

  def draw_label(vg, text, x, y, _w, h)
    vg.font_size(18.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,128))

    vg.text_align(NVG::ALIGN_LEFT|NVG::ALIGN_MIDDLE)
    vg.text(x, y + h * 0.5, text)
  end

  def draw_edit_box_base(vg, x, y, w, h)
    # Edit
    bg = vg.box_gradient(x + 1, y + 1 + 1.5, w - 2, h - 2, 3, 4, NVG.rgba(255,255,255,32), NVG.rgba(32,32,32,32))
    vg.path do
      vg.rounded_rect(x + 1, y + 1, w - 2, h - 2, 4 - 1)
      vg.fill_paint(bg)
      vg.fill
    end

    vg.path do
      vg.rounded_rect(x + 0.5, y + 0.5, w - 1, h - 1, 4 - 0.5)
      vg.stroke_color(NVG.rgba(0,0,0,48))
      vg.stroke
    end
  end

  def draw_edit_box(vg, text, x, y, w, h)
    draw_edit_box_base(vg, x, y, w, h)

    vg.font_size(20.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,64))
    vg.text_align(NVG::ALIGN_LEFT|NVG::ALIGN_MIDDLE)
    vg.text(x+h*0.3,y+h*0.5,text)
  end

  def draw_edit_box_num(vg, text, units, x, y, w, h)
    draw_edit_box_base(vg, x, y, w, h)

    uw = vg.text_bounds(0, 0, units)

    vg.font_size(18.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,64))
    vg.text_align(NVG::ALIGN_RIGHT|NVG::ALIGN_MIDDLE)
    vg.text(x+w-h*0.3,y+h*0.5,units)

    vg.font_size(20.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,128))
    vg.text_align(NVG::ALIGN_RIGHT|NVG::ALIGN_MIDDLE)
    vg.text(x+w-uw-h*0.5,y+h*0.5,text)
  end

  def draw_check_box(vg, text, x, y, w, h)
    vg.font_size(18.0)
    vg.font_face("sans")
    vg.fill_color(NVG.rgba(255,255,255,160))

    vg.text_align(NVG::ALIGN_LEFT|NVG::ALIGN_MIDDLE)
    vg.text(x+28,y+h*0.5,text)

    bg = vg.box_gradient(x + 1, y + (h * 0.5).to_i - 9 + 1, 18, 18, 3, 3, NVG.rgba(0,0,0,32), NVG.rgba(0,0,0,92))
    vg.path do
      vg.rounded_rect(x + 1, y + (h * 0.5).to_i - 9, 18, 18, 3)
      vg.fill_paint(bg)
      vg.fill
    end

    vg.font_size(40)
    vg.font_face("icons")
    vg.fill_color(NVG.rgba(255,255,255,128))
    vg.text_align(NVG::ALIGN_CENTER|NVG::ALIGN_MIDDLE)
    vg.text(x+9+2, y+h*0.5, ICON_CHECK)
  end

  def draw_button(vg, preicon, text, x, y, w, h, col)
    corner_radius = 4.0
    tw = 0
    iw = 0

    bg = vg.linear_gradient(x, y, x, y + h, NVG.rgba(255,255,255,is_black?(col)?16:32), NVG.rgba(0,0,0,is_black?(col)?16:32))
    vg.path do
      vg.rounded_rect(x + 1, y + 1, w - 2, h - 2, corner_radius - 1)
      if !is_black?(col)
        vg.fill_color(col)
        vg.fill
      end
      vg.fill_paint(bg)
      vg.fill
    end

    vg.path do
      vg.rounded_rect(x + 0.5, y + 0.5, w - 1, h - 1, corner_radius - 0.5)
      vg.stroke_color(NVG.rgba(0,0,0,48))
      vg.stroke
    end

    vg.font_size(20.0)
    vg.font_face("sans-bold")
    tw = vg.text_bounds(0,0, text)
    if preicon != 0
      vg.font_size(h*1.3)
      vg.font_face("icons")
      iw = vg.text_bounds(0,0, preicon)
      iw += h * 0.15
    end

    if preicon != 0
      vg.font_size(h * 1.3)
      vg.font_face("icons")
      vg.fill_color(NVG.rgba(255,255,255,96))
      vg.text_align(NVG::Align::ALIGN_LEFT|NVG::Align::ALIGN_MIDDLE)
      vg.text(x + w * 0.5 - tw * 0.5 - iw * 0.75, y + h * 0.5, preicon)
    end

    vg.font_size(20.0)
    vg.font_face("sans-bold")
    vg.text_align(NVG::Align::ALIGN_LEFT|NVG::Align::ALIGN_MIDDLE)
    vg.fill_color(NVG.rgba(0,0,0,160))
    vg.text(x+w*0.5-tw*0.5+iw*0.25,y+h*0.5-1,text)
    vg.fill_color(NVG.rgba(255,255,255,160))
    vg.text(x+w*0.5-tw*0.5+iw*0.25,y+h*0.5,text)
  end

  def draw_slider(vg, pos, x, y, w, h)
    cy = y + (h * 0.5).to_i
    kr = (h * 0.25).to_i

    vg.spork do

      # Slot
      bg = vg.box_gradient(x,cy-2+1, w,4, 2,2, NVG.rgba(0,0,0,32), NVG.rgba(0,0,0,128))
      vg.path do
        vg.rounded_rect(x, cy - 2, w, 4, 2)
        vg.fill_paint(bg)
        vg.fill
      end

      # Knob Shadow
      bg = vg.radial_gradient(x+(pos*w).to_i,cy+1, kr-3,kr+3, NVG.rgba(0,0,0,64), NVG.rgba(0,0,0,0))
      vg.path do
        vg.rect(x + (pos * w).to_i - kr - 5, cy - kr - 5, kr * 2 + 5 + 5, kr * 2 + 5 + 5 + 3)
        vg.circle(x + (pos * w).to_i, cy, kr)
        vg.path_winding(NVG::Solidity::HOLE)
        vg.fill_paint(bg)
        vg.fill
      end

      # Knob
      knob = vg.linear_gradient(x,cy-kr,x,cy+kr, NVG.rgba(255,255,255,16), NVG.rgba(0,0,0,16))
      vg.path do
        vg.circle(x + (pos * w).to_i,cy, kr-1)
        vg.fill_color(NVG.rgba(40,43,48,255))
        vg.fill
        vg.fill_paint(knob)
        vg.fill
      end

      vg.path do
        vg.circle(x + (pos * w).to_i, cy, kr - 0.5)
        vg.stroke_color(NVG.rgba(0, 0, 0, 92))
        vg.stroke
      end
    end
  end

  def draw_spinner(vg, cx, cy, r, t)
    a0 = t * 6.0
    a1 = Math::PI + t * 6
    r0 = r
    r1 = r * 0.75
    vg.spork do
      vg.begin_path
        vg.arc(cx, cy, r0, a0, a1, NVG::CW)
        vg.arc(cx, cy, r1, a1, a0, NVG::CCW)
      vg.close_path
      ax = cx + Math.cos(a0) * (r0 + r1) * 0.5
      ay = cy + Math.sin(a0) * (r0 + r1) * 0.5
      bx = cx + Math.cos(a1) * (r0 + r1) * 0.5
      by = cy + Math.sin(a1) * (r0 + r1) * 0.5
      paint = vg.linear_gradient ax, ay, bx, by, NVG.rgba(0,0,0,0), NVG.rgba(0,0,0,128)
      vg.fill_paint paint
      vg.fill
    end
  end

  def draw_thumbnails(vg, x, y, w, h, images, t)
    ix,iy,iw,ih = nil, nil, nil, nil
    nimages = images.size
    corner_radius = 3.0
    thumb = 60.0
    arry = 30.5
    stackh = (nimages / 2) * (thumb + 10) + 10
    u = (1 + Math.cos(t * 0.5)) * 0.5
    u2 = (1 - Math.cos(t * 0.2)) * 0.5
    vg.spork do
      shadow_paint = vg.box_gradient(x, y + 4, w, h, corner_radius * 2, 20, NVG.rgba(0, 0, 0, 128), NVG.rgba(0, 0, 0, 0))
      vg.path do
        vg.rect x - 10, y - 10, w + 20, h + 30
        vg.rounded_rect x, y, w, h, corner_radius
        vg.path_winding NVG::HOLE
        vg.fill_paint shadow_paint
        vg.fill
      end

      vg.path do
        vg.rounded_rect x, y, w, h, corner_radius
        vg.move_to x - 10, y + arry
        vg.line_to x + 1, y + arry - 11
        vg.line_to x + 1, y + arry + 11
        vg.fill_color NVG.rgba(200, 200, 200, 255)
        vg.fill
      end

      vg.spork do
        vg.scissor x, y, w, h
        vg.translate 0, -(stackh - h) * u
        dv = 1.0 / (nimages - 1).to_f
        nimages.times do |i|
          tx = x + 10
          ty = y + 10
          tx += (i % 2).to_i * (thumb + 10)
          ty += (i / 2).to_i * (thumb + 10)
          imgw, imgh = vg.image_size images[0]
          if (imgw < imgh)
            iw = thumb
            ih = iw * imgh / imgw.to_f
            ix = 0
            iy = -(ih - thumb) * 0.5
          else
            ih = thumb
            iw = ih * imgw / imgh.to_f
            ix = -(iw - thumb) * 0.5
            iy = 0
          end
          v = i * dv
          a = [[(u2 - v) / dv, 0].max, 1].min
          if a < 1.0
            draw_spinner(vg, tx + thumb / 2, ty + thumb / 2, thumb * 0.25, t)
          end

          img_paint = vg.image_pattern(tx + ix, ty + iy, iw, ih, 0.0 / 180.0 * Math::PI, images[i], a)
          vg.path do
            vg.rounded_rect tx, ty, thumb, thumb, 5
            vg.fill_paint img_paint
            vg.fill
          end
          shadow_paint = vg.box_gradient tx - 1, ty, thumb + 2, thumb + 2, 5, 3, NVG.rgba(0, 0, 0, 128), NVG.rgba(0, 0, 0, 0)
          vg.path do
            vg.rect tx - 5, ty - 5, thumb + 10, thumb + 10
            vg.rounded_rect tx, ty, thumb, thumb, 6
            vg.path_winding NVG::HOLE
            vg.fill_paint shadow_paint
            vg.fill
          end
          vg.path do
            vg.rounded_rect tx + 0.5, ty + 0.5, thumb - 1, thumb - 1, 4 - 0.5
            vg.stroke_width 1.0
            vg.stroke_color NVG.rgba(255, 255, 255, 192)
            vg.stroke
          end
        end
      end

      fade_paint = vg.linear_gradient x, y, x, y + 6, NVG.rgba(200, 200, 200, 255), NVG.rgba(200, 200, 200, 0)
      vg.path do
        vg.path do
          vg.rect x + 4, y, w - 8, 6
          vg.fill_paint fade_paint
          vg.fill
        end
      end

      fade_paint = vg.linear_gradient x, y + h, x, y + h - 6, NVG.rgba(200, 200, 200, 255), NVG.rgba(200, 200, 200, 0)
      vg.path do
        vg.path do
          vg.rect x + 4, y + h - 6, w - 8, 6
          vg.fill_paint fade_paint
          vg.fill
        end
      end

      shadow_paint = vg.box_gradient(x + w - 12 + 1, y + 4 + 1, 8, h - 8, 3, 4, NVG.rgba(0, 0, 0, 32), NVG.rgba(0, 0, 0, 92))
      vg.path do
        vg.rounded_rect x + w - 12, y + 4, 8, h - 8, 3
        vg.fill_paint shadow_paint
        vg.fill
      end

      scrollh = (h / stackh) * (h - 8)
      shadow_paint = vg.box_gradient(x + w - 12 - 1, y + 4 + (h - 8 - scrollh) * u - 1, 8, scrollh, 3, 4, NVG.rgba(220, 220, 220, 255), NVG.rgba(128, 128, 128, 255))
      vg.path do
        vg.rounded_rect x + w - 12 + 1, y + 4 + 1 + (h - 8 - scrollh) * u, 8 - 2, scrollh - 2, 2
        vg.fill_paint shadow_paint
        vg.fill
      end
    end
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

      # Widgets
      draw_window(vg, 'Widgets `n Stuff', 50, 50, 300, 400)
      x = 60
      y = 95
      draw_search_box(vg, 'Search', x, y, 280, 25)
      y += 40
      draw_drop_down(vg, 'Effects', x, y, 280, 28)
      popy = y + 14
      y += 45

      # Form
      draw_label(vg, "Login", x, y, 280, 20)
      y += 25
      draw_edit_box(vg, "Email",  x, y, 280, 28)
      y += 35
      draw_edit_box(vg, "Password", x, y, 280, 28)
      y += 38
      draw_check_box(vg, "Remember me", x, y, 140, 28)
      draw_button(vg, ICON_LOGIN, "Sign in", x + 138, y, 140, 28, NVG.rgba(0, 96, 128, 255))
      y += 45

      # Slider
      draw_label(vg, "Diameter", x, y, 280,20)
      y += 25
      draw_edit_box_num(vg, "123.00", "px", x + 180,y, 100,28)
      draw_slider(vg, 0.4, x, y, 170, 28)
      y += 55

      draw_button(vg, ICON_TRASH, "Delete", x, y, 160, 28, NVG.rgba(128, 16, 8, 255))
      draw_button(vg, 0, "Cancel", x + 170, y, 110, 28, NVG.rgba(0, 0, 0, 0))

      # Thumbnails box
      draw_thumbnails(vg, 365, popy - 30, 160, 300, data[:images], t)
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

    window = GLFW::Window.new(1000, 600, 'mruby NanoVG')

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
