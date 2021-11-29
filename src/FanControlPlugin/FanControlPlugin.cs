using FanControl.Plugins;
using System;

namespace FanControl.SerialComSensor
{
    public class FanControlPlugin : IPlugin
    {
        public string Name => "FanControlPlugin.SerialCOMSensor";

        private COMReader reader;

        public void Close()
        {
            reader.Dispose();
            reader = null;
        }

        [System.Obsolete]
        public void Initialize()
        {
            string com = Environment.GetEnvironmentVariable("SENSOR_COM_PORT");
            if (com == null)
            {
                throw new Exception("SENSOR_COM_PORT variable is not set!");
            }
            reader = new COMReader(com);
        }

        public void Load(IPluginSensorsContainer _container)
        {
            _container.TempSensors.Add(new SerialCOMSensor(reader));
        }
    }
}
