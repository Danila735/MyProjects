using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Курсовая_работа_Исполнитель_
{
    public partial class Form1 : Form
    {
        private int step;
        private List<string> code;
        private int x;
        private int y;
        private List<int> xy;
        private bool isModePaint;

        public Form1()
        {
            InitializeComponent();
            step = 0;
            x = pictureBox1.Width / 2;
            y = pictureBox1.Height / 2;
            isModePaint = false;
            xy = new List<int>();
            code = new List<string>();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            code.Clear();
            code.AddRange(richTextBox1.Lines);

            if (code.Count != 0 && isCodeWrittenTrue())
            {
                x = pictureBox1.Width / 2;
                y = pictureBox1.Height / 2;
                step = 0;
                xy.Clear();
                pictureBox1.Refresh();
                timer1.Start();
            }
            else
            {
                pictureBox1.BackColor = Color.Red;
            }
        }

        private bool isCodeWrittenTrue()
        {
            bool isTrue = true;
            for (int i = 0; i < code.Count; i++)
            {
                if (code[i].IndexOf("вперед") == -1 && code[i].IndexOf("назад") == -1 && code[i].IndexOf("налево") == -1 
                    && code[i].IndexOf("направо") == -1 && code[i] != "начать рисование"
                    && code[i] != "закончить рисование" && code[i].IndexOf("повторить") == -1 && code[i] != "конец")
                {
                    richTextBox1.SelectionStart = richTextBox1.Find(code[i]);
                    richTextBox1.SelectionLength = code[i].Length;
                    richTextBox1.SelectionColor = Color.Red;
                    isTrue = false;
                }
                else
                {
                    richTextBox1.SelectionStart = richTextBox1.Find(code[i]);
                    richTextBox1.SelectionLength = code[i].Length;
                    richTextBox1.SelectionColor = Color.Black;
                }
            }

            return isTrue;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (step < code.Count)
            {
                pictureBox1.Refresh();
            }
            else
            {
                timer1.Stop();
            }
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            pictureBox1.BackColor = Color.White;
            drawGrid(e);

            Rectangle rectPatch = new Rectangle(x, y, 10, 10);
            e.Graphics.FillRectangle(new SolidBrush(Color.Red), rectPatch);

            if (code != null && isCodeWrittenTrue() && step < code.Count)
            {
                if (code[step].IndexOf("вперед") != -1)
                {
                    int i = code[step].IndexOf(' ');
                    if (i != -1)
                    {
                        int n = Convert.ToInt32(code[step].Substring(i + 1));
                        code.RemoveRange(step, 1);
                        for (int j = 0; j < n; j++)
                        {
                            code.Insert(step, "вперед");
                        }
                        
                    }

                    drawMoveLine(e);
                    drawMovePoint(e, 0, -10);
                    if (isModePaint)
                    {
                        xy.AddRange(new int[] { x, y });
                    }
                    step++;
                }
                else if (code[step].IndexOf("назад") != -1)
                {
                    int i = code[step].IndexOf(' ');
                    if (i != -1)
                    {
                        int n = Convert.ToInt32(code[step].Substring(i + 1));
                        code.RemoveRange(step, 1);
                        for (int j = 0; j < n; j++)
                        {
                            code.Insert(step, "назад");
                        }

                    }
                    drawMoveLine(e);
                    drawMovePoint(e, 0, 10);
                    if (isModePaint)
                    {
                        xy.AddRange(new int[] { x, y });
                    }
                    step++;
                }
                else if (code[step].IndexOf("налево") != -1)
                {
                    int i = code[step].IndexOf(' ');
                    int n = Convert.ToInt32(code[step].Substring(i + 1));

                    drawMoveLine(e);
                    if (n == 45)
                    {
                        drawMovePoint(e, -10, -10);
                    }
                    else if (n == 90)
                    {
                        drawMovePoint(e, -10, 0);
                    }
                    else if (n == 135)
                    {
                        drawMovePoint(e, -10, 10);
                    }

                    if (isModePaint)
                    {
                        xy.AddRange(new int[] { x, y });
                    }
                    step++;
                }
                else if (code[step].IndexOf("направо") != -1)
                {
                    int i = code[step].IndexOf(' ');
                    int n = Convert.ToInt32(code[step].Substring(i + 1));

                    drawMoveLine(e);
                    if (n == 45)
                    {
                        drawMovePoint(e, 10, -10);
                    }
                    else if (n == 90)
                    {
                        drawMovePoint(e, 10, 0);
                    }
                    else if (n == 135)
                    {
                        drawMovePoint(e, 10, 10);
                    }

                    
                    if (isModePaint)
                    {
                        xy.AddRange(new int[] { x, y });
                    }
                    step++;
                }
                else if (code[step] == "начать рисование")
                {
                    xy.AddRange(new int[] { x, y });
                    isModePaint = true;
                    step++;
                }
                else if (code[step] == "закончить рисование")
                {
                    isModePaint = false;
                    drawMoveLine(e);
                    drawMovePoint(e, 0, 0);
                    step++;
                }
                else if (code[step].IndexOf("повторить") != -1)
                {
                    int i = code[step].IndexOf(' ');
                    int n = Convert.ToInt32(code[step].Substring(i + 1));

                    int stepTemp = step + 1;
                    List<string> codeTemp = new List<string>();
                    while (code[stepTemp] != "конец")
                    {
                        codeTemp.Add(code[stepTemp]);
                        stepTemp++;
                    }
                    code.RemoveRange(step, stepTemp - step + 1);
                    for (int j = 0; j < n; j++)
                    {
                        code.InsertRange(step, codeTemp);
                    }
                }
            }
        }

        private void drawMoveLine(PaintEventArgs e)
        {
            for (int i = 0; i < xy.Count; i+=2)
            {
                Rectangle rectPatch = new Rectangle(xy[i], xy[i + 1], 10, 10);
                e.Graphics.FillRectangle(new SolidBrush(Color.Gray), rectPatch);
            }
            drawGrid(e);
        }

        private void drawMovePoint(PaintEventArgs e, int dX, int dY)
        {
            Rectangle rectPatch = new Rectangle(x, y, 10, 10);
            e.Graphics.FillRectangle(new SolidBrush(Color.White), rectPatch);
            y += dY;
            x += dX;
            drawGrid(e);
            rectPatch = new Rectangle(x, y, 10, 10);
            e.Graphics.FillRectangle(new SolidBrush(Color.Red), rectPatch);
        }

        private void drawGrid(PaintEventArgs e)
        {
            for (int i = 0; i <= pictureBox1.Height; i += 10)
            {
                GraphicsPath myGraphicsPath = new GraphicsPath();
                myGraphicsPath.AddLine(0, i, pictureBox1.Width, i);
                e.Graphics.DrawPath(new Pen(Color.LightGray), myGraphicsPath);
            }

            for (int i = 0; i <= pictureBox1.Width; i += 10)
            {
                GraphicsPath myGraphicsPath = new GraphicsPath();
                myGraphicsPath.AddLine(i, 0, i, pictureBox1.Height);
                e.Graphics.DrawPath(new Pen(Color.LightGray), myGraphicsPath);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            pictureBox1.BackColor = Color.White;
            x = pictureBox1.Width / 2;
            y = pictureBox1.Height / 2;
            richTextBox1.Clear();
            step = 0;
        }
    }
}