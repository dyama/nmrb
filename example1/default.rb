class Display

  def init
    @wait = 100              # Speed
    @x = Display::WIDTH / 2  # Initial location
    @y = Display::HEIGHT / 2
    @mw = 8                  # Mushroom size
    @mh = 7
    @mr = '00000000003344000343343034434334344343340022220000111100'.split('').map(&:to_i)
    @me = '00334400034334300343343034434334344343340022220000111100'.split('').map(&:to_i)
  end

  def update
    self.clear
    self.put_mushroom(@x, @y)
  end

  def keydown(key)
    @x += 1 if key == 68 # D
    @x -= 1 if key == 65 # A
    @y += 1 if key == 83 # S
    @y -= 1 if key == 87 # W
    @x = 0 if @x < 0
    @x = Display::WIDTH - @mw if @x + @mw >= Display::WIDTH
    @y = 0 if @y < 0
    @y = Display::HEIGHT - @mh if @y + @mh >= Display::HEIGHT
  end

  def put_mushroom(x, y)
    aa = @c % 10 < 5 ? @mr : @me
    aa.each_with_index do |e, i|
      self[x + i % @mw, y + (i / @mw).to_i] = e
    end
  end

end
