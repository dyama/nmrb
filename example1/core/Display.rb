class Display
  
  WIDTH = 96
  HEIGHT = 48
  
  attr_accessor :buf, :c, :wait

  def initialize
    self.clear
    @c = 0
    @wait = 10
    self.clear
    self.init_font
  end

  def init
  end

  def update
    false
  end

  def keydown(key)

  end

  def clear
    self.fill 0
  end

  def [](x, y)
    @buf[y * Display::WIDTH + x]
  end

  def []=(x, y, z)
    return if x >= Display::WIDTH
    return if y >= Display::HEIGHT
    return if x < 0
    return if y < 0
    @buf[y * Display::WIDTH + x] = z
  end

  def fill(color = 4)
    @buf = (Display::WIDTH * Display::HEIGHT).times.map{color}
  end

  def line(color, x1, y1, x2, y2)
    x =0, y = 0
    dx = (x2 - x1).abs
    dy = (y2 - y1).abs
    if dx > dy
      if x1 > x2
        x = x1
        x1 = x2
        x2 = x
        y = y1
        y1 = y2
        y2 = y
      end 
      x = x1 >= 0 ? x1 : 0
      while (x <= x2 && x < Display::WIDTH)
        self[x, (y2 - y1) * (x - x1) / dx + y1] = color
        x += 1
      end
    else
      if y1 > y2
        x = x1
        x1 = x2
        x2 = x
        y = y1
        y1 = y2
        y2 = y
      end
      y = y1 >= 0 ? y1 : 0
      while (y <= y2 && y < Display::HEIGHT)
        self[(x2 - x1) * (y - y1) / dy + x1, y] = color
        y += 1
      end
    end
  end

  def rect(color, x, y, w, h)
    self.line color, x, y, x + w, y
    self.line color, x, y, x, y + h
    self.line color, x + w, y, x + w, y + h
    self.line color, x, y + h, x + w, y + h
  end

  def init_font
    @fonts = [
      1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,
      0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,
      1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,
      1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,
      1,0,1,1,0,1,1,1,1,0,0,1,0,0,1,
      1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,
      1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,
      1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,
      1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,
      1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,
      0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    ].each_slice(3 * 5).to_a
  end

  def put_value(n, x, y, forecolor = 4, backcolor = 0)
    if n.is_a?(Fixnum) || n.is_a?(Float)
      n.to_s.split('').each_with_index do |e, i|
        e = 10 if e == '-'
        e = 11 if e == '.'
        self.put_number e.to_i, x + (4 * i), y, forecolor, backcolor
      end
    end
  end

  def put_number(n, x, y, forecolor = 4, backcolor = 0)
    begin
      m = @fonts[n].map{|c| c == 1 ? forecolor : backcolor }
      self.put_image m, x, y, 3
    rescue => ex
      p ex
      self.put_image (3 * 5).times.map{forecolor}, x, y, 3
    end
  end

  def put_image(a, x, y, w)
    a.each_with_index do |e, i|
      self[x + (i % w), y + (i / w).to_i] = e
    end
  end

end
