using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Trade
{
    public partial class FormMain : Form
    {
        private double price = 0;
        private double amount = 0;
        private double total = 0;

        private bool priceChanged = false;
        private bool amountChanged = false;
        private bool totalChanged = false;

        private Color defaultForeColor;
        private Color defaultBackColor;

        public FormMain()
        {
            InitializeComponent();
            defaultForeColor = this.ForeColor;
            defaultBackColor = this.BackColor;
        }

        private void textBoxPrice_TextChanged(object sender, EventArgs e)
        {
            priceChanged = true;
        }

        private void textBoxPrice_Leave(object sender, EventArgs e)
        {
            if (priceChanged)
            {
                string input = textBoxPrice.Text;
                if (!double.TryParse(input, out price))
                {
                    MessageBox.Show("输入的单价不合法");
                    price = double.NaN;
                    return;
                }
                textBoxPrice.Text = price.ToString("N2");
                price = double.Parse(textBoxPrice.Text);
                if (!amount.Equals(double.NaN))
                {
                    total = amount * price;
                    textBoxTotal.Text = total.ToString("N2");
                }
                priceChanged = false;
            }
        }

        private void textBoxAmount_TextChanged(object sender, EventArgs e)
        {
            amountChanged = true;
        }

        private void textBoxAmount_Leave(object sender, EventArgs e)
        {
            if (amountChanged)
            {
                string input = textBoxAmount.Text;
                if (!double.TryParse(input, out amount))
                {
                    MessageBox.Show("输入的单价不合法");
                    amount = double.NaN;
                    return;
                }
                if (!price.Equals(double.NaN))
                {
                    total = amount * price;
                    textBoxTotal.Text = total.ToString("N2");
                }
                amountChanged = false;
            }
        }

        private void textBoxTotal_TextChanged(object sender, EventArgs e)
        {
            totalChanged = true;
        }

        private void textBoxTotal_Leave(object sender, EventArgs e)
        {
            if (totalChanged)
            {
                string input = textBoxTotal.Text;
                if (!double.TryParse(input, out total))
                {
                    MessageBox.Show("输入的单价不合法");
                    total = double.NaN;
                    return;
                }
                textBoxTotal.Text = total.ToString("N2");
                total = double.Parse(textBoxTotal.Text);
                if (amount != 0)
                {
                    price = total / amount;
                    textBoxPrice.Text = price.ToString("N2");
                }
                amountChanged = false;
            }
        }

        private void showColorSetError()
        {
            MessageBox.Show("前景色与背景色不能相同");
        }

        private void stateChange(string key, ToolStripMenuItem item)
        {
            ToolStripMenuItem[] items = null;

            if (key.Equals("fore"))
            {
                items = new ToolStripMenuItem[] {
                    foreRedToolStripMenuItem, foreGreenToolStripMenuItem,
                    foreBlueToolStripMenuItem, foreDefaultToolStripMenuItem  
                };
            }
            else if (key.Equals("back"))
            {
                items = new ToolStripMenuItem[] {
                    backRedToolStripMenuItem, backGreenToolStripMenuItem,
                    backBlueToolStripMenuItem, backDefaultToolStripMenuItem  
                };
            }
            else
            {
                return;
            }

            for (int i = 0; i < items.Length; i++)
            {
                if (item == items[i])
                {
                    item.Checked = true;
                }
                else
                {
                    items[i].Checked = false;
                }
            }
        }

        private void setColor(string key, Color color, object sender)
        {
            if (key.Equals("fore"))
            {
                if (this.BackColor == color)
                {
                    showColorSetError();
                }
                else
                {
                    stateChange(key, (ToolStripMenuItem)sender);
                    this.ForeColor = color;
                }
            }
            else if (key.Equals("back"))
            {
                if (this.ForeColor == color)
                {
                    showColorSetError();
                }
                else
                {
                    stateChange(key, (ToolStripMenuItem)sender);
                    this.BackColor = color;
                }
            }
        }

        private void foreRedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("fore", Color.Red, sender);
        }

        private void foreGreenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("fore", Color.Green, sender);
        }

        private void foreBlueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("fore", Color.Blue, sender);
        }

        private void foreDefaultToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("fore", defaultForeColor, sender);
        }

        private void backRedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("back", Color.Red, sender);
        }

        private void backGreenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("back", Color.Green, sender);
        }

        private void backBlueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("back", Color.Blue, sender);
        }

        private void backDefaultToolStripMenuItem_Click(object sender, EventArgs e)
        {
            setColor("back", defaultBackColor, sender);
        }
    }
}
