using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Robot_UI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            MVpb.Hide();
            MFRpb.Hide();
            MFRnum.Hide();
            Forward.Hide();
            Back.Hide();
            Up.Hide();
            Down.Hide();
            Right.Hide();
            Left.Hide();
            label1.Hide();
            label2.Hide();
            Run.Hide();
            Status_Chklst.Hide();
            panel1.Hide();
            label3.Hide();
        }


        private void POTbt_Click(object sender, EventArgs e)
        {
            MVpb.Hide();
            MFRpb.Hide();
            MFRnum.Hide();
            Forward.Hide();
            Back.Hide();
            Up.Hide();
            Down.Hide();
            Right.Hide();
            Left.Hide();
            label1.Hide();
            label2.Hide();
            Run.Hide();
            Status_Chklst.Hide();
            panel1.Show();
            label3.Show();
        }

        private void CTRbt_Click(object sender, EventArgs e)
        {
            MVpb.Hide();
            MFRpb.Hide();
            MFRnum.Hide();
            Up.Show();
            Down.Show();
            Forward.Show();
            Back.Show();
            Right.Show();
            Left.Show();
            label1.Hide();
            label2.Hide();
            Run.Hide();
            Status_Chklst.Hide();
            panel1.Hide();
            label3.Hide();
        }

        private void MIbt_Click(object sender, EventArgs e)
        {
            Up.Hide();
            Down.Hide();
            Forward.Hide();
            Back.Hide();
            Right.Hide();
            Left.Hide();
            MVpb.Show();
            MFRpb.Show();
            MFRnum.Show();
            label1.Show();
            label2.Show();
            Run.Show();
            Status_Chklst.Hide();
            panel1.Hide();
            label3.Hide();
        }

        private void MFRnum_ValueChanged(object sender, EventArgs e)
        {

        }

        private void fwrd_click(object sender, EventArgs e)
        {

        }

        private void left_click(object sender, EventArgs e)
        {

        }

        private void right_click(object sender, EventArgs e)
        {

        }

        private void back_click(object sender, EventArgs e)
        {

        }

        private void up_click(object sender, EventArgs e)
        {

        }

        private void down_click(object sender, EventArgs e)
        {

        }

        private void Status_Click(object sender, EventArgs e)
        {
            MVpb.Hide();
            MFRpb.Hide();
            MFRnum.Hide();
            Forward.Hide();
            Back.Hide();
            Up.Hide();
            Down.Hide();
            Right.Hide();
            Left.Hide();
            label1.Hide();
            label2.Hide();
            Run.Hide();
            Status_Chklst.Show();
            panel1.Hide();
            label3.Hide();
        }

        private void panel1_BackgroundImageLayoutChanged(object sender, EventArgs e)
        {
            
        }
    }
}
