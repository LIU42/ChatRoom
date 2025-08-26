using ChatRoom.Forms;

namespace ChatRoom
{
	internal static class Program
    {
        [STAThread]
        public static void Main()
        {
            ApplicationConfiguration.Initialize();
            Application.Run(new ClientWindow());
        }
    }
}
