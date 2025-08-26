using ChatRoom.Resources;

namespace ChatRoom.Forms
{
	public partial class ClientWindow : Form
	{
		private AboutWindow aboutWindow;
		private PropsWindow propsWindow;

		private Socket messageSocket;
		private Thread receiveThread;

		public ClientWindow()
		{
			InitializeComponent();

			aboutWindow = new AboutWindow();
			propsWindow = new PropsWindow();

			messageSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			receiveThread = new Thread(MessageReceiveLoop);
		}

		private void OnAboutMenuItemClick(object sender, EventArgs args)
		{
			aboutWindow.ShowDialog();
		}

		private void OnPropsMenuItemClick(object sender, EventArgs args)
		{
			propsWindow.ShowDialog();
		}

		private void MessageReceiveLoop()
		{
			byte[] receiveBuffer = new byte[2048];

			try
			{
				while (true)
				{
					int receiveLength = messageSocket.Receive(receiveBuffer);

					if (receiveLength <= 0)
					{
						AddMessage(StringResources.ReceiveEndMessage);
						return;
					}
					AddMessage(Encoding.UTF8.GetString(receiveBuffer, 0, receiveLength));
				}
			}
			catch
			{
				AddMessage(StringResources.DisconnectReceiveMessage);
			}
		}

		private void OnExitMenuItemClick(object sender, EventArgs args)
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

				messageSocket.Connect(propsWindow.GetAddress(), propsWindow.GetPort());
				receiveThread.Start();

				AddMessage(StringResources.ConnectSuccessMessage);

				sendButton.Enabled = true;
				disconnectMenuItem.Enabled = true;
			}
			catch
			{
				AddMessage(StringResources.ConnectFailureMessage);

				sendButton.Enabled = false;
				connectMenuItem.Enabled = true;
			}
		}

		private async void OnConnectMenuItemClick(object sender, EventArgs args)
		{
			await Task.Run(ConnectServerTask);
		}

		private void DisconnectServer()
		{
			if (messageSocket.Connected)
			{
				messageSocket.Shutdown(SocketShutdown.Both);
				messageSocket.Close();
				receiveThread.Join();
			}
		}

		private void DisconnectServerTask()
		{
			disconnectMenuItem.Enabled = false;

			DisconnectServer();
			AddMessage(StringResources.DisconnectServerMessage);

			sendButton.Enabled = false;
			connectMenuItem.Enabled = true;
		}

		private async void OnDisconnectMenuItemClick(object sender, EventArgs args)
		{
			await Task.Run(DisconnectServerTask);
		}

		private void ResetClientSocket()
		{
			DisconnectServer();
			messageSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
		}

		private void SendMessageTask()
		{
			sendButton.Enabled = false;

			try
			{
				if (nameInputBox.Text.Length > 0 && sendInputBox.Text.Length > 0)
				{
					messageSocket.Send(Encoding.UTF8.GetBytes($"{nameInputBox.Text}: {sendInputBox.Text}"));
					sendInputBox.Clear();
				}
			}
			catch
			{
				AddMessage(StringResources.SendFailureMessage);
			}
			sendButton.Enabled = true;
		}

		private async void OnSendMessage(object sender, EventArgs args)
		{
			await Task.Run(SendMessageTask);
		}
	}
}
