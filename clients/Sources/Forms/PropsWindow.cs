namespace ChatRoom.Forms
{
	public partial class PropsWindow : Form
	{
		public PropsWindow()
		{
			InitializeComponent();
		}

		private void OnButtonClick(object sender, EventArgs args)
		{
			Close();
		}

		public IPAddress GetAddress()
		{
			long ipAddress = 0;

			ipAddress += (long)ipAddressInputBox1.Value << 0;
			ipAddress += (long)ipAddressInputBox2.Value << 8;
			ipAddress += (long)ipAddressInputBox3.Value << 16;
			ipAddress += (long)ipAddressInputBox4.Value << 24;

			return new IPAddress(ipAddress);
		}

		public int GetPort()
		{
			return (int)portInputBox.Value;
		}
	}
}
 