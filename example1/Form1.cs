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
      exitToolStripMenuItem.Click += (sender, e) => Close();
      toolStripButton1.Click += ToolStripButton1_Click;
    }

    Timer t = new Timer();

    private void ToolStripButton1_Click(object sender, EventArgs e)
    {
      toolStripButton1.Checked = !toolStripButton1.Checked;
      if (toolStripButton1.Checked) {
        textBox1.Enabled = false;
        mrb = new State();
        def_class();
        mrb.Do(textBox1.Text);
        mrb.Do("$d = Display.new");
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          toolStripButton1.Checked = false;
          textBox1.Enabled = true;
          return;
        }
        mrb.Do("$d.init");
        if (mrb.HasError) {
          toolStripStatusLabel1.Text = mrb.LastErrorMessage;
          toolStripButton1.Checked = false;
          textBox1.Enabled = true;
          return;
        }
        t.Tick += (ss, ee) => {
          if (update() > 0) {
            textBox1.Enabled = true;
            toolStripButton1.Checked = false;
            t.Stop();
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
        textBox1.Enabled = true;
        t.Stop();
      }
    }

    public void def_class()
    {
      mrb.Do(@"
        class Display
          WIDTH = 64
          HEIGHT = 32
          attr_accessor :disp, :c, :wait
          def initialize
            @disp = Array.new(Display::WIDTH * Display::HEIGHT, 0)
            @c = 0
            @wait = 10
          end
          def init

          end
          def update

          end
        end
       ");
    }

    private int update()
    {
      mrb.Do(textBox1.Text);
      if (mrb.HasError) {
        toolStripStatusLabel1.Text = mrb.LastErrorMessage;
        return 1;
      }
      else {
        toolStripStatusLabel1.Text = "";
      }
      if (bmp == null) {
        bmp = new Bitmap(pictureBox1.Width, pictureBox1.Height);
      }
      var g = Graphics.FromImage(bmp);
      g.FillRectangle(Brushes.Black, 0, 0, bmp.Width, bmp.Height);

      mrb.Do("$d.update");
      if (mrb.HasError) {
        toolStripStatusLabel1.Text = mrb.LastErrorMessage;
        return 1;
      }

      try {
        var ww = (mrb["Display::WIDTH"] as FixnumValue).ToInteger();
        var hh = (mrb["Display::HEIGHT"] as FixnumValue).ToInteger();
        var sz = 8;

        var a1 = mrb.Do("$d.disp");
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
          Brush b = ary[i] == 0 ? Brushes.DarkGreen : Brushes.GreenYellow;
          g.FillRectangle(b, x * sz + 1, y * sz + 1, sz - 2, sz - 2);
        }
        mrb.Do("$d.c += 1");
      }
      catch (Exception ex) {
        toolStripStatusLabel1.Text = ex.Message;
        return 2;
      }
      pictureBox1.Image = bmp;
      return 0;
    }
  }
}
