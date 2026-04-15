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
            numericUpDown1 = new NumericUpDown();
            POTbt = new Button();
            CTRbt = new Button();
            linkLabel1 = new LinkLabel();
            MVpb = new VerticalProgressBar();
            MFRpb = new ProgressBar();
            ((System.ComponentModel.ISupportInitialize)numericUpDown1).BeginInit();
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
            MIbt.Click += button1_Click;
            // 
            // numericUpDown1
            // 
            numericUpDown1.Location = new Point(311, 198);
            numericUpDown1.Name = "numericUpDown1";
            numericUpDown1.Size = new Size(125, 27);
            numericUpDown1.TabIndex = 2;
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
            CTRbt.Click += button3_Click;
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
            MFRpb.Click += progressBar1_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(967, 450);
            Controls.Add(MVpb);
            Controls.Add(linkLabel1);
            Controls.Add(CTRbt);
            Controls.Add(POTbt);
            Controls.Add(numericUpDown1);
            Controls.Add(MFRpb);
            Controls.Add(MIbt);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)numericUpDown1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button MIbt;
        private NumericUpDown numericUpDown1;
        private Button POTbt;
        private Button CTRbt;
        private LinkLabel linkLabel1;
        private VerticalProgressBar MVpb;
        public ProgressBar MFRpb;
    }
}
