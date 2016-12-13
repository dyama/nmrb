class Display

  def update
    self.clear
    line 1, 0, (Display::HEIGHT / 2).to_i, Display::WIDTH - 1, (Display::HEIGHT / 2).to_i
    xang = 0.0
    y = 0.0
    px = 0, py = 0
    yy = 0
    i = @c % Display::WIDTH
    x = 0
    while x < Display::WIDTH + i
      xang = x * Math::PI / (Display::WIDTH / 4);
      y = Math.sin(xang);
      y *= (Display::HEIGHT / 3); 
      if x > 0
        line 2, px - i, py + (Display::HEIGHT / 2).to_i, x - i, (y + Display::HEIGHT / 2).floor.to_i
      end
      if x - i == 10
        yy = (y + Display::HEIGHT / 2).to_i
      end
      px = x
      py = y.to_i
      x += 1
    end
    rect 4, 10, yy, 3, 3
    self.put_value(@c, 1, 1)
  end

end
