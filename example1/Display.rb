class Display
  
  WIDTH = 96
  HEIGHT = 48
  
  attr_accessor :buf, :c, :wait

  def initialize
    self.clear
    @c = 0
    @wait = 10
  end

  def init

  end

  def update

  end

  def keydown(key)

  end

  def clear
    @buf = (Display::WIDTH * Display::HEIGHT).times.map{0}
  end

  def [](x, y)
    @buf[y * Display::WIDTH + x]
  end

  def []=(x, y, z)
    @buf[y * Display::WIDTH + x] = z
  end

end
