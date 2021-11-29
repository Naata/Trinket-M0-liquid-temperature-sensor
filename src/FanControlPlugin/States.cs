using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FanControl.SerialComSensor
{
    internal class States
    {
        public const float INITIAL = -10;
        public const float PORT_OPENED = 0;
        public const float COULDNT_PARSE = -1;
    }
}
