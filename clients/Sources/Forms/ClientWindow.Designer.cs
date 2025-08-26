namespace ChatRoom.Forms
{
	partial class ClientWindow
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ClientWindow));
			menuStrip = new MenuStrip();
			startMenuItem = new ToolStripMenuItem();
			serverPropsMenuItem = new ToolStripMenuItem();
			connectMenuItem = new ToolStripMenuItem();
			disconnectMenuItem = new ToolStripMenuItem();
			helpMenuItem = new ToolStripMenuItem();
			aboutMenuItem = new ToolStripMenuItem();
			exitMenuItem = new ToolStripMenuItem();
			mainLayout = new TableLayoutPanel();
			receiveGroupBox = new GroupBox();
			receiveTextBox = new TextBox();
			sendGroupBox = new GroupBox();
			sendInputBox = new TextBox();
			sendButton = new Button();
			nameInputBox = new TextBox();
			usernameLabel = new Label();
			menuStrip.SuspendLayout();
			mainLayout.SuspendLayout();
			receiveGroupBox.SuspendLayout();
			sendGroupBox.SuspendLayout();
			SuspendLayout();
			// 
			// menuStrip
			// 
			menuStrip.BackColor = SystemColors.ControlLightLight;
			menuStrip.ImageScalingSize = new Size(20, 20);
			menuStrip.Items.AddRange(new ToolStripItem[] { startMenuItem, helpMenuItem });
			menuStrip.Location = new Point(0, 0);
			menuStrip.Name = "menuStrip";
			menuStrip.Size = new Size(800, 28);
			menuStrip.TabIndex = 0;
			// 
			// startMenuItem
			// 
			startMenuItem.DropDownItems.AddRange(new ToolStripItem[] { serverPropsMenuItem, connectMenuItem, disconnectMenuItem });
			startMenuItem.Name = "startMenuItem";
			startMenuItem.Size = new Size(72, 24);
			startMenuItem.Text = "开始(S)";
			// 
			// serverPropsMenuItem
			// 
			serverPropsMenuItem.Name = "serverPropsMenuItem";
			serverPropsMenuItem.Size = new Size(224, 26);
			serverPropsMenuItem.Text = "服务器配置(O)";
			serverPropsMenuItem.Click += OnPropsMenuItemClick;
			// 
			// connectMenuItem
			// 
			connectMenuItem.Name = "connectMenuItem";
			connectMenuItem.Size = new Size(224, 26);
			connectMenuItem.Text = "连接服务器(C)";
			connectMenuItem.Click += OnConnectMenuItemClick;
			// 
			// disconnectMenuItem
			// 
			disconnectMenuItem.Enabled = false;
			disconnectMenuItem.Name = "disconnectMenuItem";
			disconnectMenuItem.Size = new Size(224, 26);
			disconnectMenuItem.Text = "断开服务器(D)";
			disconnectMenuItem.Click += OnDisconnectMenuItemClick;
			// 
			// helpMenuItem
			// 
			helpMenuItem.DropDownItems.AddRange(new ToolStripItem[] { aboutMenuItem, exitMenuItem });
			helpMenuItem.Name = "helpMenuItem";
			helpMenuItem.Size = new Size(75, 24);
			helpMenuItem.Text = "帮助(H)";
			// 
			// aboutMenuItem
			// 
			aboutMenuItem.Name = "aboutMenuItem";
			aboutMenuItem.Size = new Size(143, 26);
			aboutMenuItem.Text = "关于(A)";
			aboutMenuItem.Click += OnAboutMenuItemClick;
			// 
			// exitMenuItem
			// 
			exitMenuItem.Name = "exitMenuItem";
			exitMenuItem.Size = new Size(143, 26);
			exitMenuItem.Text = "退出(X)";
			exitMenuItem.Click += OnExitMenuItemClick;
			// 
			// mainLayout
			// 
			mainLayout.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			mainLayout.AutoSize = true;
			mainLayout.ColumnCount = 1;
			mainLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			mainLayout.Controls.Add(receiveGroupBox, 0, 0);
			mainLayout.Controls.Add(sendGroupBox, 0, 1);
			mainLayout.Location = new Point(0, 29);
			mainLayout.Name = "mainLayout";
			mainLayout.Padding = new Padding(6);
			mainLayout.RowCount = 2;
			mainLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
			mainLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
			mainLayout.Size = new Size(800, 511);
			mainLayout.TabIndex = 1;
			// 
			// receiveGroupBox
			// 
			receiveGroupBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			receiveGroupBox.Controls.Add(receiveTextBox);
			receiveGroupBox.Location = new Point(9, 9);
			receiveGroupBox.Name = "receiveGroupBox";
			receiveGroupBox.Size = new Size(782, 243);
			receiveGroupBox.TabIndex = 0;
			receiveGroupBox.TabStop = false;
			receiveGroupBox.Text = "消息接收";
			// 
			// receiveTextBox
			// 
			receiveTextBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			receiveTextBox.BackColor = SystemColors.ControlLightLight;
			receiveTextBox.HideSelection = false;
			receiveTextBox.Location = new Point(6, 25);
			receiveTextBox.Multiline = true;
			receiveTextBox.Name = "receiveTextBox";
			receiveTextBox.ReadOnly = true;
			receiveTextBox.ScrollBars = ScrollBars.Vertical;
			receiveTextBox.Size = new Size(770, 211);
			receiveTextBox.TabIndex = 0;
			receiveTextBox.TabStop = false;
			// 
			// sendGroupBox
			// 
			sendGroupBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			sendGroupBox.Controls.Add(sendInputBox);
			sendGroupBox.Controls.Add(sendButton);
			sendGroupBox.Controls.Add(nameInputBox);
			sendGroupBox.Controls.Add(usernameLabel);
			sendGroupBox.Location = new Point(9, 258);
			sendGroupBox.Name = "sendGroupBox";
			sendGroupBox.Size = new Size(782, 244);
			sendGroupBox.TabIndex = 1;
			sendGroupBox.TabStop = false;
			sendGroupBox.Text = "消息发送";
			// 
			// sendInputBox
			// 
			sendInputBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			sendInputBox.Location = new Point(6, 75);
			sendInputBox.Multiline = true;
			sendInputBox.Name = "sendInputBox";
			sendInputBox.ScrollBars = ScrollBars.Vertical;
			sendInputBox.Size = new Size(770, 162);
			sendInputBox.TabIndex = 3;
			sendInputBox.TabStop = false;
			// 
			// sendButton
			// 
			sendButton.Anchor = AnchorStyles.Top | AnchorStyles.Right;
			sendButton.Enabled = false;
			sendButton.Location = new Point(663, 31);
			sendButton.Name = "sendButton";
			sendButton.Size = new Size(94, 28);
			sendButton.TabIndex = 2;
			sendButton.TabStop = false;
			sendButton.Text = "发送";
			sendButton.UseVisualStyleBackColor = true;
			sendButton.Click += OnSendMessage;
			// 
			// nameInputBox
			// 
			nameInputBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			nameInputBox.Location = new Point(82, 32);
			nameInputBox.MaxLength = 16;
			nameInputBox.Name = "nameInputBox";
			nameInputBox.PlaceholderText = "请输入您的昵称";
			nameInputBox.Size = new Size(563, 27);
			nameInputBox.TabIndex = 1;
			nameInputBox.TabStop = false;
			nameInputBox.Text = "访客";
			// 
			// usernameLabel
			// 
			usernameLabel.AutoSize = true;
			usernameLabel.Location = new Point(24, 35);
			usernameLabel.Name = "usernameLabel";
			usernameLabel.Size = new Size(39, 19);
			usernameLabel.TabIndex = 0;
			usernameLabel.Text = "昵称";
			// 
			// ClientWindow
			// 
			AutoScaleDimensions = new SizeF(9F, 19F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(800, 542);
			Controls.Add(mainLayout);
			Controls.Add(menuStrip);
			Icon = (Icon)resources.GetObject("$this.Icon");
			MainMenuStrip = menuStrip;
			MinimumSize = new Size(818, 589);
			Name = "ClientWindow";
			StartPosition = FormStartPosition.CenterScreen;
			Text = "聊天室";
			FormClosing += OnClosing;
			menuStrip.ResumeLayout(false);
			menuStrip.PerformLayout();
			mainLayout.ResumeLayout(false);
			receiveGroupBox.ResumeLayout(false);
			receiveGroupBox.PerformLayout();
			sendGroupBox.ResumeLayout(false);
			sendGroupBox.PerformLayout();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private MenuStrip menuStrip;
		private ToolStripMenuItem startMenuItem;
		private ToolStripMenuItem serverPropsMenuItem;
		private ToolStripMenuItem connectMenuItem;
		private ToolStripMenuItem disconnectMenuItem;
		private ToolStripMenuItem helpMenuItem;
		private ToolStripMenuItem exitMenuItem;
		private TableLayoutPanel mainLayout;
		private GroupBox receiveGroupBox;
		private GroupBox sendGroupBox;
		private TextBox receiveTextBox;
		private Label usernameLabel;
		private TextBox nameInputBox;
		private Button sendButton;
		private TextBox sendInputBox;
		private ToolStripMenuItem aboutMenuItem;
	}
}
