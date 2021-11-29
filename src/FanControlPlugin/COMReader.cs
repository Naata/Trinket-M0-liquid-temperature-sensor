using System.IO.Ports;

namespace FanControl.SerialComSensor
{
    public class COMReader : System.IDisposable
    {
        private SerialPort port;

        public string Data { set; get; }

        public COMReader(string com) {
            port = new SerialPort(com, 9600, Parity.None, 8, StopBits.One);
            port.DtrEnable = true;
            port.DataReceived += new SerialDataReceivedEventHandler(dataReceived);
            port.Open();
            Data = States.PORT_OPENED.ToString();
        }

        public void Dispose()
        {
            port.Close();
        }

        public void dataReceived(object sender, SerialDataReceivedEventArgs e) {
            Data = port.ReadLine().Trim().Split('.')[0]; // leave fraction part .XXX
        }
    }
}
