namespace ChatRoom.Forms
{
	partial class PropsWindow
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
			addressLabel = new Label();
			portLabel = new Label();
			portInputBox = new NumericUpDown();
			ipAddressInputBox1 = new NumericUpDown();
			ipAddressInputBox2 = new NumericUpDown();
			ipAddressInputBox3 = new NumericUpDown();
			ipAddressInputBox4 = new NumericUpDown();
			pointLabel1 = new Label();
			pointLabel2 = new Label();
			pointLabel3 = new Label();
			okButton = new Button();
			((System.ComponentModel.ISupportInitialize)portInputBox).BeginInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox1).BeginInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox2).BeginInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox3).BeginInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox4).BeginInit();
			SuspendLayout();
			// 
			// addressLabel
			// 
			addressLabel.AutoSize = true;
			addressLabel.Location = new Point(29, 50);
			addressLabel.Margin = new Padding(3);
			addressLabel.Name = "addressLabel";
			addressLabel.Size = new Size(56, 20);
			addressLabel.TabIndex = 2;
			addressLabel.Text = "IP 地址";
			addressLabel.TextAlign = ContentAlignment.MiddleCenter;
			// 
			// portLabel
			// 
			portLabel.AutoSize = true;
			portLabel.Location = new Point(30, 100);
			portLabel.Margin = new Padding(3);
			portLabel.Name = "portLabel";
			portLabel.Size = new Size(54, 20);
			portLabel.TabIndex = 3;
			portLabel.Text = "端口号";
			portLabel.TextAlign = ContentAlignment.MiddleCenter;
			// 
			// portInputBox
			// 
			portInputBox.Location = new Point(97, 97);
			portInputBox.Maximum = new decimal(new int[] { 65535, 0, 0, 0 });
			portInputBox.Name = "portInputBox";
			portInputBox.Size = new Size(297, 27);
			portInputBox.TabIndex = 4;
			portInputBox.TabStop = false;
			portInputBox.TextAlign = HorizontalAlignment.Center;
			portInputBox.Value = new decimal(new int[] { 8000, 0, 0, 0 });
			// 
			// ipAddressInputBox1
			// 
			ipAddressInputBox1.Location = new Point(97, 47);
			ipAddressInputBox1.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
			ipAddressInputBox1.Name = "ipAddressInputBox1";
			ipAddressInputBox1.Size = new Size(60, 27);
			ipAddressInputBox1.TabIndex = 5;
			ipAddressInputBox1.TabStop = false;
			ipAddressInputBox1.TextAlign = HorizontalAlignment.Center;
			ipAddressInputBox1.Value = new decimal(new int[] { 127, 0, 0, 0 });
			// 
			// ipAddressInputBox2
			// 
			ipAddressInputBox2.Location = new Point(176, 47);
			ipAddressInputBox2.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
			ipAddressInputBox2.Name = "ipAddressInputBox2";
			ipAddressInputBox2.Size = new Size(60, 27);
			ipAddressInputBox2.TabIndex = 6;
			ipAddressInputBox2.TabStop = false;
			ipAddressInputBox2.TextAlign = HorizontalAlignment.Center;
			// 
			// ipAddressInputBox3
			// 
			ipAddressInputBox3.Location = new Point(255, 47);
			ipAddressInputBox3.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
			ipAddressInputBox3.Name = "ipAddressInputBox3";
			ipAddressInputBox3.Size = new Size(60, 27);
			ipAddressInputBox3.TabIndex = 7;
			ipAddressInputBox3.TabStop = false;
			ipAddressInputBox3.TextAlign = HorizontalAlignment.Center;
			// 
			// ipAddressInputBox4
			// 
			ipAddressInputBox4.Location = new Point(334, 47);
			ipAddressInputBox4.Maximum = new decimal(new int[] { 255, 0, 0, 0 });
			ipAddressInputBox4.Name = "ipAddressInputBox4";
			ipAddressInputBox4.Size = new Size(60, 27);
			ipAddressInputBox4.TabIndex = 8;
			ipAddressInputBox4.TabStop = false;
			ipAddressInputBox4.TextAlign = HorizontalAlignment.Center;
			ipAddressInputBox4.Value = new decimal(new int[] { 1, 0, 0, 0 });
			// 
			// pointLabel1
			// 
			pointLabel1.AutoSize = true;
			pointLabel1.Font = new Font("Microsoft YaHei UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 134);
			pointLabel1.Location = new Point(160, 55);
			pointLabel1.Margin = new Padding(0);
			pointLabel1.Name = "pointLabel1";
			pointLabel1.Size = new Size(13, 19);
			pointLabel1.TabIndex = 9;
			pointLabel1.Text = ".";
			// 
			// pointLabel2
			// 
			pointLabel2.AutoSize = true;
			pointLabel2.Font = new Font("Microsoft YaHei UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 134);
			pointLabel2.Location = new Point(239, 55);
			pointLabel2.Margin = new Padding(0);
			pointLabel2.Name = "pointLabel2";
			pointLabel2.Size = new Size(13, 19);
			pointLabel2.TabIndex = 10;
			pointLabel2.Text = ".";
			// 
			// pointLabel3
			// 
			pointLabel3.AutoSize = true;
			pointLabel3.Font = new Font("Microsoft YaHei UI", 9F, FontStyle.Bold, GraphicsUnit.Point, 134);
			pointLabel3.Location = new Point(318, 55);
			pointLabel3.Margin = new Padding(0);
			pointLabel3.Name = "pointLabel3";
			pointLabel3.Size = new Size(13, 19);
			pointLabel3.TabIndex = 11;
			pointLabel3.Text = ".";
			// 
			// okButton
			// 
			okButton.Location = new Point(300, 171);
			okButton.Name = "okButton";
			okButton.Size = new Size(94, 29);
			okButton.TabIndex = 12;
			okButton.TabStop = false;
			okButton.Text = "OK";
			okButton.UseVisualStyleBackColor = true;
			okButton.Click += OnButtonClick;
			// 
			// ConfigWindow
			// 
			AutoScaleDimensions = new SizeF(9F, 20F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(435, 230);
			Controls.Add(okButton);
			Controls.Add(pointLabel3);
			Controls.Add(pointLabel2);
			Controls.Add(pointLabel1);
			Controls.Add(ipAddressInputBox4);
			Controls.Add(ipAddressInputBox3);
			Controls.Add(ipAddressInputBox2);
			Controls.Add(ipAddressInputBox1);
			Controls.Add(portInputBox);
			Controls.Add(portLabel);
			Controls.Add(addressLabel);
			FormBorderStyle = FormBorderStyle.FixedDialog;
			MaximizeBox = false;
			MdiChildrenMinimizedAnchorBottom = false;
			MinimizeBox = false;
			Name = "ConfigWindow";
			ShowIcon = false;
			ShowInTaskbar = false;
			StartPosition = FormStartPosition.CenterScreen;
			Text = "聊天室服务器配置";
			((System.ComponentModel.ISupportInitialize)portInputBox).EndInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox1).EndInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox2).EndInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox3).EndInit();
			((System.ComponentModel.ISupportInitialize)ipAddressInputBox4).EndInit();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private Label addressLabel;
		private Label portLabel;
		private NumericUpDown portInputBox;
		private NumericUpDown ipAddressInputBox1;
		private NumericUpDown ipAddressInputBox2;
		private NumericUpDown ipAddressInputBox3;
		private NumericUpDown ipAddressInputBox4;
		private Label pointLabel1;
		private Label pointLabel2;
		private Label pointLabel3;
		private Button okButton;
	}
}