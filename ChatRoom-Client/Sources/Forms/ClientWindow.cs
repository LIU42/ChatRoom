using ChatRoom.Configs;

namespace ChatRoom.Forms
{
	public partial class ClientWindow : Form
	{
		private AboutWindow aboutWindow;
		private ConfigWindow configWindow;

		private Socket clientSocket;
		private Thread clientThread;

		public ClientWindow()
		{
			InitializeComponent();

			aboutWindow = new AboutWindow();
			configWindow = new ConfigWindow();

			clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			clientThread = new Thread(RecevieMessageLoop);
		}

		private void OnAboutItemClick(object sender, EventArgs args)
		{
			aboutWindow.ShowDialog();
		}

		private void OnConfigItemClick(object sender, EventArgs args)
		{
			configWindow.ShowDialog();
		}

		private void RecevieMessageLoop()
		{
			byte[] receiveBuffer = new byte[2048];

			try
			{
				while (true)
				{
					int receiveLength = clientSocket.Receive(receiveBuffer);

					if (receiveLength <= 0)
					{
						AddMessage(Resources.ReceiveEndMessage);
						return;
					}
					AddMessage(Encoding.UTF8.GetString(receiveBuffer, 0, receiveLength));
				}
			}
			catch (Exception)
			{
				AddMessage(Resources.DisconnectReceiveMessage);
			}
		}

		private void OnExitItemClick(object sender, EventArgs args)
		{
			Close();
		}

		private void OnClosing(object sender, FormClosingEventArgs args)
		{
			DisconnectServer();
		}

		private void AddMessage(string message)
		{
			lock (receiveTextBox)
			{
				receiveTextBox.AppendText($"{message}\r\n");
				receiveTextBox.ScrollToCaret();
			}
		}

		private void ConnectServerTask()
		{
			connectMenuItem.Enabled = false;

			try
			{
				ResetClientSocket();

				clientSocket.Connect(configWindow.GetAddress(), configWindow.GetPort());
				clientThread.Start();

				AddMessage(Resources.ConnectSuccessMessage);

				sendButton.Enabled = true;
				disconnectMenuItem.Enabled = true;
			}
			catch (Exception)
			{
				AddMessage(Resources.ConnectFailureMessage);

				sendButton.Enabled = false;
				connectMenuItem.Enabled = true;
			}
		}

		private async void OnConnectItemClick(object sender, EventArgs args)
		{
			await Task.Run(ConnectServerTask);
		}

		private void DisconnectServer()
		{
			if (clientSocket.Connected)
			{
				clientSocket.Shutdown(SocketShutdown.Both);
				clientSocket.Close();
				clientThread.Join();
			}
		}

		private void DisconnectServerTask()
		{
			disconnectMenuItem.Enabled = false;

			DisconnectServer();
			AddMessage(Resources.DisconnectServerMessage);

			sendButton.Enabled = false;
			connectMenuItem.Enabled = true;
		}

		private async void OnDisconnectItemClick(object sender, EventArgs args)
		{
			await Task.Run(DisconnectServerTask);
		}

		private void ResetClientSocket()
		{
			DisconnectServer();
			clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
		}

		private void SendMessageTask()
		{
			sendButton.Enabled = false;

			try
			{
				if (nameInputBox.Text.Length > 0 && sendInputBox.Text.Length > 0)
				{
					clientSocket.Send(Encoding.UTF8.GetBytes($"{nameInputBox.Text}: {sendInputBox.Text}"));
					sendInputBox.Clear();
				}
			}
			catch (Exception)
			{
				AddMessage(Resources.SendFailureMessage);
			}
			sendButton.Enabled = true;
		}

		private async void OnSendMessage(object sender, EventArgs args)
		{
			await Task.Run(SendMessageTask);
		}
	}
}
