using FanControl.Plugins;

namespace FanControl.SerialComSensor
{
    public class SerialCOMSensor : IPluginSensor
    {
        private COMReader reader;

        public SerialCOMSensor(COMReader reader)
        {
            Value = States.INITIAL;
            this.reader = reader;
        }

        public string Id => Name;

        public string Name => "SerialCOMSensor";

        public float? Value { get; private set; }

        public void Update()
        {
            float result;
            if (float.TryParse(reader.Data, out result))
            {
                Value = result;
            }
            else {
                Value = States.COULDNT_PARSE;
            }
        }
    }
}
