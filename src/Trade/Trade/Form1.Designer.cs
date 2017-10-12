namespace Trade
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.labelPrice = new System.Windows.Forms.Label();
            this.labelAmount = new System.Windows.Forms.Label();
            this.labelTotal = new System.Windows.Forms.Label();
            this.textBoxPrice = new System.Windows.Forms.TextBox();
            this.textBoxAmount = new System.Windows.Forms.TextBox();
            this.textBoxTotal = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.主菜单ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.backColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.backRedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.backGreenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.backBlueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.backDefaultToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.foreRedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.foreGreenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.foreBlueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.foreDefaultToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.foreColorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelPrice
            // 
            this.labelPrice.AutoSize = true;
            this.labelPrice.Location = new System.Drawing.Point(49, 66);
            this.labelPrice.Margin = new System.Windows.Forms.Padding(9, 0, 9, 0);
            this.labelPrice.Name = "labelPrice";
            this.labelPrice.Size = new System.Drawing.Size(81, 33);
            this.labelPrice.TabIndex = 0;
            this.labelPrice.Text = "单价";
            // 
            // labelAmount
            // 
            this.labelAmount.AutoSize = true;
            this.labelAmount.Location = new System.Drawing.Point(49, 144);
            this.labelAmount.Margin = new System.Windows.Forms.Padding(9, 0, 9, 0);
            this.labelAmount.Name = "labelAmount";
            this.labelAmount.Size = new System.Drawing.Size(81, 33);
            this.labelAmount.TabIndex = 1;
            this.labelAmount.Text = "数量";
            // 
            // labelTotal
            // 
            this.labelTotal.AutoSize = true;
            this.labelTotal.Location = new System.Drawing.Point(49, 227);
            this.labelTotal.Margin = new System.Windows.Forms.Padding(9, 0, 9, 0);
            this.labelTotal.Name = "labelTotal";
            this.labelTotal.Size = new System.Drawing.Size(81, 33);
            this.labelTotal.TabIndex = 2;
            this.labelTotal.Text = "总价";
            // 
            // textBoxPrice
            // 
            this.textBoxPrice.Location = new System.Drawing.Point(170, 63);
            this.textBoxPrice.Name = "textBoxPrice";
            this.textBoxPrice.Size = new System.Drawing.Size(217, 44);
            this.textBoxPrice.TabIndex = 3;
            this.textBoxPrice.Text = "0";
            this.textBoxPrice.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxPrice.TextChanged += new System.EventHandler(this.textBoxPrice_TextChanged);
            this.textBoxPrice.Leave += new System.EventHandler(this.textBoxPrice_Leave);
            // 
            // textBoxAmount
            // 
            this.textBoxAmount.Location = new System.Drawing.Point(170, 141);
            this.textBoxAmount.Name = "textBoxAmount";
            this.textBoxAmount.Size = new System.Drawing.Size(217, 44);
            this.textBoxAmount.TabIndex = 4;
            this.textBoxAmount.Text = "0";
            this.textBoxAmount.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxAmount.TextChanged += new System.EventHandler(this.textBoxAmount_TextChanged);
            this.textBoxAmount.Leave += new System.EventHandler(this.textBoxAmount_Leave);
            // 
            // textBoxTotal
            // 
            this.textBoxTotal.Location = new System.Drawing.Point(170, 224);
            this.textBoxTotal.Name = "textBoxTotal";
            this.textBoxTotal.Size = new System.Drawing.Size(217, 44);
            this.textBoxTotal.TabIndex = 5;
            this.textBoxTotal.Text = "0";
            this.textBoxTotal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.textBoxTotal.TextChanged += new System.EventHandler(this.textBoxTotal_TextChanged);
            this.textBoxTotal.Leave += new System.EventHandler(this.textBoxTotal_Leave);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.主菜单ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(432, 25);
            this.menuStrip1.TabIndex = 14;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 主菜单ToolStripMenuItem
            // 
            this.主菜单ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.foreColorToolStripMenuItem,
            this.backColorToolStripMenuItem});
            this.主菜单ToolStripMenuItem.Name = "主菜单ToolStripMenuItem";
            this.主菜单ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.主菜单ToolStripMenuItem.Text = "设置";
            // 
            // backColorToolStripMenuItem
            // 
            this.backColorToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.backRedToolStripMenuItem,
            this.backGreenToolStripMenuItem,
            this.backBlueToolStripMenuItem,
            this.toolStripMenuItem3,
            this.backDefaultToolStripMenuItem});
            this.backColorToolStripMenuItem.Name = "backColorToolStripMenuItem";
            this.backColorToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.backColorToolStripMenuItem.Text = "背景色";
            // 
            // backRedToolStripMenuItem
            // 
            this.backRedToolStripMenuItem.Name = "backRedToolStripMenuItem";
            this.backRedToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.backRedToolStripMenuItem.Text = "红色";
            this.backRedToolStripMenuItem.Click += new System.EventHandler(this.backRedToolStripMenuItem_Click);
            // 
            // backGreenToolStripMenuItem
            // 
            this.backGreenToolStripMenuItem.Name = "backGreenToolStripMenuItem";
            this.backGreenToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.backGreenToolStripMenuItem.Text = "绿色";
            this.backGreenToolStripMenuItem.Click += new System.EventHandler(this.backGreenToolStripMenuItem_Click);
            // 
            // backBlueToolStripMenuItem
            // 
            this.backBlueToolStripMenuItem.Name = "backBlueToolStripMenuItem";
            this.backBlueToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.backBlueToolStripMenuItem.Text = "蓝色";
            this.backBlueToolStripMenuItem.Click += new System.EventHandler(this.backBlueToolStripMenuItem_Click);
            // 
            // backDefaultToolStripMenuItem
            // 
            this.backDefaultToolStripMenuItem.Checked = true;
            this.backDefaultToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.backDefaultToolStripMenuItem.Name = "backDefaultToolStripMenuItem";
            this.backDefaultToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.backDefaultToolStripMenuItem.Text = "默认";
            this.backDefaultToolStripMenuItem.Click += new System.EventHandler(this.backDefaultToolStripMenuItem_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(149, 6);
            // 
            // foreRedToolStripMenuItem
            // 
            this.foreRedToolStripMenuItem.Name = "foreRedToolStripMenuItem";
            this.foreRedToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.foreRedToolStripMenuItem.Text = "红色";
            this.foreRedToolStripMenuItem.Click += new System.EventHandler(this.foreRedToolStripMenuItem_Click);
            // 
            // foreGreenToolStripMenuItem
            // 
            this.foreGreenToolStripMenuItem.Name = "foreGreenToolStripMenuItem";
            this.foreGreenToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.foreGreenToolStripMenuItem.Text = "绿色";
            this.foreGreenToolStripMenuItem.Click += new System.EventHandler(this.foreGreenToolStripMenuItem_Click);
            // 
            // foreBlueToolStripMenuItem
            // 
            this.foreBlueToolStripMenuItem.Name = "foreBlueToolStripMenuItem";
            this.foreBlueToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.foreBlueToolStripMenuItem.Text = "蓝色";
            this.foreBlueToolStripMenuItem.Click += new System.EventHandler(this.foreBlueToolStripMenuItem_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(149, 6);
            // 
            // foreDefaultToolStripMenuItem
            // 
            this.foreDefaultToolStripMenuItem.Checked = true;
            this.foreDefaultToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.foreDefaultToolStripMenuItem.Name = "foreDefaultToolStripMenuItem";
            this.foreDefaultToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.foreDefaultToolStripMenuItem.Text = "默认";
            this.foreDefaultToolStripMenuItem.Click += new System.EventHandler(this.foreDefaultToolStripMenuItem_Click);
            // 
            // foreColorToolStripMenuItem
            // 
            this.foreColorToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.foreRedToolStripMenuItem,
            this.foreGreenToolStripMenuItem,
            this.foreBlueToolStripMenuItem,
            this.toolStripMenuItem2,
            this.foreDefaultToolStripMenuItem});
            this.foreColorToolStripMenuItem.Name = "foreColorToolStripMenuItem";
            this.foreColorToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.foreColorToolStripMenuItem.Text = "前景色";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(17F, 33F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(432, 340);
            this.Controls.Add(this.textBoxTotal);
            this.Controls.Add(this.textBoxAmount);
            this.Controls.Add(this.textBoxPrice);
            this.Controls.Add(this.labelTotal);
            this.Controls.Add(this.labelAmount);
            this.Controls.Add(this.labelPrice);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("楷体", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(9, 9, 9, 9);
            this.Name = "FormMain";
            this.Text = "交易计算器";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelPrice;
        private System.Windows.Forms.Label labelAmount;
        private System.Windows.Forms.Label labelTotal;
        private System.Windows.Forms.TextBox textBoxPrice;
        private System.Windows.Forms.TextBox textBoxAmount;
        private System.Windows.Forms.TextBox textBoxTotal;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 主菜单ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem backColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem backRedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem backGreenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem backBlueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem backDefaultToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem foreColorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem foreRedToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem foreGreenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem foreBlueToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem foreDefaultToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
    }
}

