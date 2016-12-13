using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using nmrb;

namespace example1
{
  public partial class Form1 : Form
  {
    protected State mrb;
    Bitmap bmp;

    public Form1()
    {
      InitializeComponent();
      runButton.Click += runButton_Click;
      lcd.BackColor = Color.FromArgb(0x9c,0xc0,0x96);
      reloadButton.Click += (s, e) => reload();
      reload();
      this.KeyDown += Form1_KeyDown;
      rubyCode.Select(0, 0);
    }

    private void reload()
    {
      if (runButton.Checked) {
        stop();
      }
      if (System.IO.File.Exists("./default.rb")) {
        rubyCode.Text = System.IO.File.ReadAllText("./default.rb");
      }
    }

    private void Form1_KeyDown(object sender, KeyEventArgs e)
    {
      if (runButton.Checked) {
        var k = e.KeyValue;
        mrb.Do($"$d.keydown({k})");
      }
    }

    private void stop()
    {
      if (t != null)
        t.Stop();
      runButton.Checked = false;
      rubyCode.Enabled = true;
    }

    Timer t = new Timer();

    private void runButton_Click(object sender, EventArgs e)
    {
      runButton.Checked = !runButton.Checked;
      if (runButton.Checked) {
        rubyCode.Enabled = false;
        mrb = new State();
        def_class();
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          stop();
          return;
        }
        mrb.Do(rubyCode.Text);
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          stop();
          return;
        }
        mrb.Do("$d = Display.new");
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          stop();
          return;
        }
        mrb.Do("$d.init");
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          stop();
          return;
        }
        t.Tick += (ss, ee) => {
          var n = update();
          if (n != 0) {
            stop();
          }
        };
        t.Interval = 10;
        var wait = mrb["$d.wait"];
        if (wait != null && wait.IsFixnum() && (wait as FixnumValue).ToInteger() > 0) {
          t.Interval = (wait as FixnumValue).ToInteger();
        }
        t.Start();
      }
      else {
        stop();
      }
    }

    public void def_class()
    {
      mrb.DoFile("./Display.rb");
    }

    private int update()
    {
      mrb.Do(rubyCode.Text);
      if (mrb.HasError) {
        toolStripStatusLabel1.Text = mrb.LastErrorMessage;
        return 1;
      }
      else {
        toolStripStatusLabel1.Text = "";
      }
      if (bmp == null) {
        bmp = new Bitmap(lcd.Width, lcd.Height);
      }
      var g = Graphics.FromImage(bmp);
      g.FillRectangle(new SolidBrush(lcd.BackColor), 0, 0, bmp.Width, bmp.Height);

      var r = mrb.Do("$d.update");
      if (mrb.HasError) {
        toolStripStatusLabel1.Text = mrb.LastErrorMessage;
        return 1;
      }

      try {
        var ww = (mrb["Display::WIDTH"] as FixnumValue).ToInteger();
        var hh = (mrb["Display::HEIGHT"] as FixnumValue).ToInteger();
        var sz = 6;

        var a1 = mrb.Do("$d.buf");
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          return 1;
        }
        var a2 = (a1 as ArrayValue);
        var a3 = a2.ToArray(mrb);
        var ary = a3.Select(n => (n as FixnumValue).ToInt32()).ToArray();
        for (var i = 0; i < ary.Length; i++) {
          var x = i % ww;
          var y = (int)(i / ww);
          Brush b = new SolidBrush(Color.FromArgb(0x86, 0xa6, 0x82));
          if (ary[i] == 1) {
            b = new SolidBrush(Color.FromArgb(0x64, 0x8c, 0x60));
          }
          else if (ary[i] == 2) {
            b = new SolidBrush(Color.FromArgb(0x42, 0x69, 0x40));
          }
          else if (ary[i] == 3) {
            b = new SolidBrush(Color.FromArgb(0x21, 0x46, 0x20));
          }
          else if (ary[i] == 4) {
            b = new SolidBrush(Color.FromArgb(0x00, 0x18, 0x00));
          }
          g.FillRectangle(b, x * sz, y * sz, sz - 1, sz - 1);
        }
        mrb.Do("$d.c += 1");
      }
      catch (Exception ex) {
        toolStripStatusLabel1.Text = ex.Message;
        return 2;
      }
      lcd.Image = bmp;
      if ((r as FalseValue) != null) {
        return -1;
      }
      return 0;
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      var d = new OpenFileDialog();
      d.Filter = "Ruby script file(*.rb)|*.rb|All files(*.*)|*.*";
      if (d.ShowDialog() == DialogResult.OK) {
        rubyCode.Text = System.IO.File.ReadAllText(d.FileName);
      }
    }
  }
}
