using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UISignature
{
    public partial class Form1 : Form
    {

        // P/Invoke declaration for the SignPdf function from the sig.dll
        [DllImport("sigdll.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "signPdf")]
        private static extern bool SignPdf(string privateKeyPath, string pdfPath, string signaturePath);


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            string privateKeyPath = privateKeyTextBox.Text;
            string pdfPath = PDFTextBox.Text;
            string signaturePath = SignTextBox.Text;



            if (SignPdf(privateKeyPath, pdfPath, signaturePath))
            {
                MessageBox.Show("PDF signed successfully.");
            }
            else
            {
                MessageBox.Show("Failed to sign PDF.");
            }
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void openFileDialog2_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void saveSignDialog_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void keybutton_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog1 = new OpenFileDialog())
            {
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    // Example: Set the text of a text box to the selected file's path
                    privateKeyTextBox.Text = openFileDialog1.FileName;
                }
            }
        }

        private void pdfbutton_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog2 = new OpenFileDialog())
            {
                if (openFileDialog2.ShowDialog() == DialogResult.OK)
                {
                    // Example: Set the text of a text box to the selected file's path
                    PDFTextBox.Text = openFileDialog2.FileName;
                }
            }
        }

        private void signbutton_Click(object sender, EventArgs e)
        {
            // Configure the SaveFileDialog
            saveSignDialog.Filter = "Signature files (*.sig)|*.sig|All files (*.*)|*.*";
            saveSignDialog.Title = "Save Signature File";



            // Show the SaveFileDialog
            if (saveSignDialog.ShowDialog() == DialogResult.OK)
            {
                // Set the TextBox text to the selected file path
                SignTextBox.Text = saveSignDialog.FileName;
            }
        }


        
    }
}
