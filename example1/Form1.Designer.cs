namespace example1
{
  partial class Form1
  {
    /// <summary>
    /// 必要なデザイナー変数です。
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// 使用中のリソースをすべてクリーンアップします。
    /// </summary>
    /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows フォーム デザイナーで生成されたコード

    /// <summary>
    /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
    /// コード エディターで変更しないでください。
    /// </summary>
    private void InitializeComponent()
    {
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
      this.lcd = new System.Windows.Forms.PictureBox();
      this.splitContainer1 = new System.Windows.Forms.SplitContainer();
      this.rubyCode = new System.Windows.Forms.TextBox();
      this.statusStrip1 = new System.Windows.Forms.StatusStrip();
      this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
      this.toolStrip1 = new System.Windows.Forms.ToolStrip();
      this.openButton = new System.Windows.Forms.ToolStripButton();
      this.clearButton = new System.Windows.Forms.ToolStripButton();
      this.reloadButton = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.runButton = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      ((System.ComponentModel.ISupportInitialize)(this.lcd)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // lcd
      // 
      this.lcd.Dock = System.Windows.Forms.DockStyle.Fill;
      this.lcd.Location = new System.Drawing.Point(0, 0);
      this.lcd.Name = "lcd";
      this.lcd.Padding = new System.Windows.Forms.Padding(5);
      this.lcd.Size = new System.Drawing.Size(587, 300);
      this.lcd.TabIndex = 0;
      this.lcd.TabStop = false;
      // 
      // splitContainer1
      // 
      this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
      this.splitContainer1.Location = new System.Drawing.Point(0, 25);
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
      // 
      // splitContainer1.Panel1
      // 
      this.splitContainer1.Panel1.Controls.Add(this.lcd);
      // 
      // splitContainer1.Panel2
      // 
      this.splitContainer1.Panel2.Controls.Add(this.rubyCode);
      this.splitContainer1.Panel2.Controls.Add(this.statusStrip1);
      this.splitContainer1.Size = new System.Drawing.Size(587, 528);
      this.splitContainer1.SplitterDistance = 300;
      this.splitContainer1.TabIndex = 2;
      this.splitContainer1.TabStop = false;
      // 
      // rubyCode
      // 
      this.rubyCode.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
      this.rubyCode.Dock = System.Windows.Forms.DockStyle.Fill;
      this.rubyCode.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.rubyCode.ForeColor = System.Drawing.Color.Silver;
      this.rubyCode.Location = new System.Drawing.Point(0, 0);
      this.rubyCode.Multiline = true;
      this.rubyCode.Name = "rubyCode";
      this.rubyCode.ScrollBars = System.Windows.Forms.ScrollBars.Both;
      this.rubyCode.Size = new System.Drawing.Size(587, 202);
      this.rubyCode.TabIndex = 0;
      this.rubyCode.WordWrap = false;
      // 
      // statusStrip1
      // 
      this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
      this.statusStrip1.Location = new System.Drawing.Point(0, 202);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new System.Drawing.Size(587, 22);
      this.statusStrip1.SizingGrip = false;
      this.statusStrip1.TabIndex = 1;
      this.statusStrip1.Text = "statusStrip1";
      // 
      // toolStripStatusLabel1
      // 
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new System.Drawing.Size(0, 17);
      // 
      // toolStrip1
      // 
      this.toolStrip1.CanOverflow = false;
      this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openButton,
            this.clearButton,
            this.reloadButton,
            this.toolStripSeparator1,
            this.runButton,
            this.toolStripSeparator2});
      this.toolStrip1.Location = new System.Drawing.Point(0, 0);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new System.Drawing.Size(587, 25);
      this.toolStrip1.TabIndex = 3;
      this.toolStrip1.Text = "toolStrip1";
      // 
      // openButton
      // 
      this.openButton.Image = global::example1.Properties.Resources.open;
      this.openButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.openButton.Name = "openButton";
      this.openButton.Size = new System.Drawing.Size(51, 22);
      this.openButton.Text = "&Open";
      this.openButton.Click += new System.EventHandler(this.toolStripButton1_Click);
      // 
      // clearButton
      // 
      this.clearButton.Image = global::example1.Properties.Resources.clear;
      this.clearButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.clearButton.Name = "clearButton";
      this.clearButton.Size = new System.Drawing.Size(52, 22);
      this.clearButton.Text = "&Clear";
      this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
      // 
      // reloadButton
      // 
      this.reloadButton.Enabled = false;
      this.reloadButton.Image = global::example1.Properties.Resources.refresh;
      this.reloadButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.reloadButton.Name = "reloadButton";
      this.reloadButton.Size = new System.Drawing.Size(60, 22);
      this.reloadButton.Text = "&Reload";
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
      // 
      // runButton
      // 
      this.runButton.Image = global::example1.Properties.Resources.start;
      this.runButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.runButton.Name = "runButton";
      this.runButton.Size = new System.Drawing.Size(45, 22);
      this.runButton.Text = "&Run";
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(587, 553);
      this.Controls.Add(this.splitContainer1);
      this.Controls.Add(this.toolStrip1);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.KeyPreview = true;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "Form1";
      this.Text = "nmrb example";
      ((System.ComponentModel.ISupportInitialize)(this.lcd)).EndInit();
      this.splitContainer1.Panel1.ResumeLayout(false);
      this.splitContainer1.Panel2.ResumeLayout(false);
      this.splitContainer1.Panel2.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
      this.splitContainer1.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.PictureBox lcd;
    private System.Windows.Forms.SplitContainer splitContainer1;
    private System.Windows.Forms.TextBox rubyCode;
    private System.Windows.Forms.ToolStrip toolStrip1;
    private System.Windows.Forms.ToolStripButton runButton;
    private System.Windows.Forms.StatusStrip statusStrip1;
    private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    private System.Windows.Forms.ToolStripButton reloadButton;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
    private System.Windows.Forms.ToolStripButton openButton;
    private System.Windows.Forms.ToolStripButton clearButton;
  }
}

