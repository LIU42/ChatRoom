namespace ChatRoom.Forms
{
	partial class AboutWindow
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
			titleLabel = new Label();
			contentLabel = new Label();
			SuspendLayout();
			// 
			// titleLabel
			// 
			titleLabel.AutoSize = true;
			titleLabel.Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 134);
			titleLabel.Location = new Point(31, 37);
			titleLabel.Name = "titleLabel";
			titleLabel.Size = new Size(184, 27);
			titleLabel.TabIndex = 0;
			titleLabel.Text = "聊天室 ChatRoom";
			// 
			// contentLabel
			// 
			contentLabel.AutoSize = true;
			contentLabel.Location = new Point(31, 96);
			contentLabel.Name = "contentLabel";
			contentLabel.Size = new Size(324, 20);
			contentLabel.TabIndex = 1;
			contentLabel.Text = "一个基于 TCP Socket 的简单局域网聊天室程序";
			// 
			// AboutWindow
			// 
			AutoScaleDimensions = new SizeF(9F, 20F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(400, 200);
			Controls.Add(contentLabel);
			Controls.Add(titleLabel);
			FormBorderStyle = FormBorderStyle.FixedDialog;
			MaximizeBox = false;
			MdiChildrenMinimizedAnchorBottom = false;
			MinimizeBox = false;
			Name = "AboutWindow";
			ShowIcon = false;
			ShowInTaskbar = false;
			StartPosition = FormStartPosition.CenterScreen;
			Text = "关于聊天室 (客户端)";
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private Label titleLabel;
		private Label contentLabel;
	}
}