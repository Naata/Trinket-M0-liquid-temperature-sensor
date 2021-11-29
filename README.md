# Trinket-M0-liquid-temperature-sensor
Simple program and PS script to allow monitoring of liquid temps in liquid cooling PCs

## Usage

1. Make sure that your liquid cooling loop has a temp probe installed. For my project I used this [Phobya G1/4" Inline Temperature Sensor](https://www.amazon.com/,Phobya-Inline-Temperature-Sensor-Nickel/dp/B00414VYEC), but any will be fine.

2. Buy yourself a [Trinket M0](https://www.adafruit.com/product/3500). This is a board I used, but feel free to use a different one and change the code as needed. **Trinket M0** is very cool as it can natively output serial data via USB, and it can be seen in Windows as COM device. It also has RGB diode which is useful to have some indication of liquid temperature without need to access data in OS.

3. Solder some goldpins to your **Trinket M0** - pin **A4** will be used as analog input, which is conveniant as **GND** is right next to it.

4. Flash [trinket_m0_temp_sensor.ino](src/trinket_m0_temp_sensor.ino) into your board.

5. Connect temp probe from your liquid cooling loop into your board. You remembered to add it to your loop, right? :)

6. Power your **Trinket M0** with usb from your PC. It should immediately display colors that indicate temperature:

| Avg. Color | Temp range C | Description  |
| ---------- | ------------ | ------------ |
| Blue       | 0 - 24       | Ambient      |
| Green      | 25 - 32      | Idle         | 
| Yellow     | 33 - 37      | Light load   |
| Orange     | 38 - 53      | Regular load |
| Red        | 54 - 59      | Overheat     |
| Hot Pink   | > 60         | Danger!      |

Keep in mind that colors will tend to shift from blue -> green -> yellow -> red smoothly, so it's best to expect soe color range as indication of actual temperature.

## Control PC fans using liquid temperature
1. I use tool called [Fan Control](https://github.com/Rem0o/FanControl.Releases). It's a great free tool that accepts file as mock "sensor". We can log our liquid temp into file and **Fan Control** will control our fans using this file. Download the tool and create new custom sensor.
2. Launch Windows Scheduler and create new Task:
- basic: administrator privileges + launch regardless of logged in user
- trigger: on user login
- actions: launch program - powershell, arguments: -command &{path-to\Trinket-M0-liquid-temperature-sensor\src\WatchLiquidTemp.ps1 -filePath 'path-to\FanControl\LiquidTemp.sensor' -com COM5} (change COM5 to whatever is seen by your system)
3. Save your task and restart system. After reboot your custom sensor should display values from liquid temp sensor.
  
## TODO
Create custom plugin for **Fan Control** to remove the need to use powershell
