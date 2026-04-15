using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Robot_UI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            MVpb.Show();
            MFRpb.Show();
        }

        private void progressBar1_Click(object sender, EventArgs e)
        {


        }

        private void button3_Click(object sender, EventArgs e)
        {
            MVpb.Hide();
            MFRpb.Hide();
        }

        private void POTbt_Click(object sender, EventArgs e)
        {
            MVpb.Hide();
            MFRpb.Hide();
        }
    }
}
