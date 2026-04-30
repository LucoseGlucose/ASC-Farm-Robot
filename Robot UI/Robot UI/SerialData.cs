using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Text;

namespace Robot_UI
{
    public static class SerialData
    {
        public static SerialPort? port;

        public static void Begin()
        {
            port = new SerialPort("COM3", 19200);
            port.Encoding = Encoding.UTF8;
            port.Open();
        }
    }
}
