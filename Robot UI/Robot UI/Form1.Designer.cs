namespace Robot_UI
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            MIbt = new Button();
            MFRnum = new NumericUpDown();
            POTbt = new Button();
            CTRbt = new Button();
            linkLabel1 = new LinkLabel();
            MVpb = new VerticalProgressBar();
            MFRpb = new ProgressBar();
            Forward = new Button();
            Left = new Button();
            Right = new Button();
            Back = new Button();
            Up = new Button();
            Down = new Button();
            ((System.ComponentModel.ISupportInitialize)MFRnum).BeginInit();
            SuspendLayout();
            // 
            // MIbt
            // 
            MIbt.Location = new Point(12, 12);
            MIbt.Name = "MIbt";
            MIbt.Size = new Size(94, 29);
            MIbt.TabIndex = 0;
            MIbt.Text = "Milk Intake";
            MIbt.UseVisualStyleBackColor = true;
            MIbt.Click += MIbt_Click;
            // 
            // MFRnum
            // 
            MFRnum.Location = new Point(311, 198);
            MFRnum.Name = "MFRnum";
            MFRnum.Size = new Size(125, 27);
            MFRnum.TabIndex = 2;
            MFRnum.ValueChanged += MFRnum_ValueChanged;
            // 
            // POTbt
            // 
            POTbt.Location = new Point(112, 12);
            POTbt.Name = "POTbt";
            POTbt.Size = new Size(94, 29);
            POTbt.TabIndex = 3;
            POTbt.Text = "Positioning";
            POTbt.UseVisualStyleBackColor = true;
            POTbt.Click += POTbt_Click;
            // 
            // CTRbt
            // 
            CTRbt.Location = new Point(212, 12);
            CTRbt.Name = "CTRbt";
            CTRbt.Size = new Size(94, 29);
            CTRbt.TabIndex = 4;
            CTRbt.Text = "Controls";
            CTRbt.UseVisualStyleBackColor = true;
            CTRbt.Click += CTRbt_Click;
            // 
            // linkLabel1
            // 
            linkLabel1.AutoSize = true;
            linkLabel1.Location = new Point(311, 322);
            linkLabel1.Name = "linkLabel1";
            linkLabel1.Size = new Size(0, 20);
            linkLabel1.TabIndex = 5;
            // 
            // MVpb
            // 
            MVpb.Location = new Point(12, 62);
            MVpb.Name = "MVpb";
            MVpb.Size = new Size(125, 234);
            MVpb.Style = ProgressBarStyle.Continuous;
            MVpb.TabIndex = 6;
            // 
            // MFRpb
            // 
            MFRpb.Location = new Point(173, 145);
            MFRpb.Name = "MFRpb";
            MFRpb.Size = new Size(361, 47);
            MFRpb.Style = ProgressBarStyle.Continuous;
            MFRpb.TabIndex = 1;
            // 
            // Forward
            // 
            Forward.Location = new Point(698, 122);
            Forward.Name = "Forward";
            Forward.Size = new Size(94, 29);
            Forward.TabIndex = 7;
            Forward.Text = "Forward";
            Forward.UseVisualStyleBackColor = true;
            Forward.Click += fwrd_click;
            // 
            // Left
            // 
            Left.Location = new Point(637, 165);
            Left.Name = "Left";
            Left.Size = new Size(94, 29);
            Left.TabIndex = 8;
            Left.Text = "Left";
            Left.UseVisualStyleBackColor = true;
            Left.Click += left_click;
            // 
            // Right
            // 
            Right.Location = new Point(758, 165);
            Right.Name = "Right";
            Right.Size = new Size(94, 29);
            Right.TabIndex = 9;
            Right.Text = "Right";
            Right.UseVisualStyleBackColor = true;
            Right.Click += right_click;
            // 
            // Back
            // 
            Back.Location = new Point(698, 210);
            Back.Name = "Back";
            Back.Size = new Size(94, 29);
            Back.TabIndex = 10;
            Back.Text = "Back";
            Back.UseVisualStyleBackColor = true;
            Back.Click += back_click;
            // 
            // Up
            // 
            Up.Location = new Point(852, 62);
            Up.Name = "Up";
            Up.Size = new Size(94, 29);
            Up.TabIndex = 11;
            Up.Text = "Up";
            Up.UseVisualStyleBackColor = true;
            Up.Click += up_click;
            // 
            // Down
            // 
            Down.Location = new Point(852, 97);
            Down.Name = "Down";
            Down.Size = new Size(94, 29);
            Down.TabIndex = 12;
            Down.Text = "Down";
            Down.UseVisualStyleBackColor = true;
            Down.Click += down_click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(967, 450);
            Controls.Add(Down);
            Controls.Add(Up);
            Controls.Add(Back);
            Controls.Add(Right);
            Controls.Add(Left);
            Controls.Add(Forward);
            Controls.Add(MVpb);
            Controls.Add(linkLabel1);
            Controls.Add(CTRbt);
            Controls.Add(POTbt);
            Controls.Add(MFRnum);
            Controls.Add(MFRpb);
            Controls.Add(MIbt);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)MFRnum).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button MIbt;
        private NumericUpDown MFRnum;
        private Button POTbt;
        private LinkLabel linkLabel1;
        private VerticalProgressBar MVpb;
        public ProgressBar MFRpb;
        private Button CTRbt;
        private Button Forward;
        private Button Left;
        private Button Right;
        private Button Back;
        private Button Up;
        private Button Down;
    }
}
