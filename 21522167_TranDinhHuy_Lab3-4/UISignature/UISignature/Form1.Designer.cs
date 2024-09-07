namespace UISignature
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PDFTextBox = new System.Windows.Forms.TextBox();
            this.SignTextBox = new System.Windows.Forms.TextBox();
            this.privateKeyTextBox = new System.Windows.Forms.TextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.keybutton = new System.Windows.Forms.Button();
            this.pdfbutton = new System.Windows.Forms.Button();
            this.signbutton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.openFileDialog2 = new System.Windows.Forms.OpenFileDialog();
            this.saveSignDialog = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // PDFTextBox
            // 
            this.PDFTextBox.Location = new System.Drawing.Point(229, 62);
            this.PDFTextBox.Name = "PDFTextBox";
            this.PDFTextBox.Size = new System.Drawing.Size(100, 20);
            this.PDFTextBox.TabIndex = 0;
            // 
            // SignTextBox
            // 
            this.SignTextBox.Location = new System.Drawing.Point(437, 63);
            this.SignTextBox.Name = "SignTextBox";
            this.SignTextBox.Size = new System.Drawing.Size(100, 20);
            this.SignTextBox.TabIndex = 1;
            // 
            // privateKeyTextBox
            // 
            this.privateKeyTextBox.Location = new System.Drawing.Point(24, 62);
            this.privateKeyTextBox.Name = "privateKeyTextBox";
            this.privateKeyTextBox.Size = new System.Drawing.Size(100, 20);
            this.privateKeyTextBox.TabIndex = 2;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // keybutton
            // 
            this.keybutton.Location = new System.Drawing.Point(130, 61);
            this.keybutton.Name = "keybutton";
            this.keybutton.Size = new System.Drawing.Size(75, 23);
            this.keybutton.TabIndex = 3;
            this.keybutton.Text = "Browse";
            this.keybutton.UseVisualStyleBackColor = true;
            this.keybutton.Click += new System.EventHandler(this.keybutton_Click);
            // 
            // pdfbutton
            // 
            this.pdfbutton.Location = new System.Drawing.Point(335, 61);
            this.pdfbutton.Name = "pdfbutton";
            this.pdfbutton.Size = new System.Drawing.Size(75, 23);
            this.pdfbutton.TabIndex = 4;
            this.pdfbutton.Text = "Browse";
            this.pdfbutton.UseVisualStyleBackColor = true;
            this.pdfbutton.Click += new System.EventHandler(this.pdfbutton_Click);
            // 
            // signbutton
            // 
            this.signbutton.Location = new System.Drawing.Point(543, 60);
            this.signbutton.Name = "signbutton";
            this.signbutton.Size = new System.Drawing.Size(75, 23);
            this.signbutton.TabIndex = 5;
            this.signbutton.Text = "Browse";
            this.signbutton.UseVisualStyleBackColor = true;
            this.signbutton.Click += new System.EventHandler(this.signbutton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 102);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Private Key file";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(256, 102);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "PDF file";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(469, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(28, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Sign";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(645, 60);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 9;
            this.button4.Text = "SignPDF";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // openFileDialog2
            // 
            this.openFileDialog2.FileName = "openFileDialog2";
            this.openFileDialog2.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog2_FileOk);
            // 
            // saveSignDialog
            // 
            this.saveSignDialog.FileName = "saveSignDialog";
            this.saveSignDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.saveSignDialog_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.signbutton);
            this.Controls.Add(this.pdfbutton);
            this.Controls.Add(this.keybutton);
            this.Controls.Add(this.privateKeyTextBox);
            this.Controls.Add(this.SignTextBox);
            this.Controls.Add(this.PDFTextBox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox PDFTextBox;
        private System.Windows.Forms.TextBox SignTextBox;
        private System.Windows.Forms.TextBox privateKeyTextBox;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button keybutton;
        private System.Windows.Forms.Button pdfbutton;
        private System.Windows.Forms.Button signbutton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.OpenFileDialog openFileDialog2;
        private System.Windows.Forms.OpenFileDialog saveSignDialog;
    }
}

