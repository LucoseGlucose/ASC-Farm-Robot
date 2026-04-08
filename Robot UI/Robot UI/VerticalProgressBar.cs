using System;
using System.Collections.Generic;
using System.Text;

namespace Robot_UI
{
    public class VerticalProgressBar : ProgressBar
    {
        public VerticalProgressBar()
        {
            this.SetStyle(ControlStyles.UserPaint, true);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Rectangle rect = this.ClientRectangle;
            Graphics g = e.Graphics;

            // Draw background
            g.FillRectangle(Brushes.LightGray, rect);

            // Calculate fill from bottom up
            int fillHeight = (int)(rect.Height * ((double)Value / Maximum));
            Rectangle fillRect = new Rectangle(
                rect.X,
                rect.Height - fillHeight,
                rect.Width,
                fillHeight
            );

            g.FillRectangle(Brushes.Green, fillRect);

            // Optional: draw border
            g.DrawRectangle(Pens.Gray, 0, 0, rect.Width - 1, rect.Height - 1);
        }
    }
}