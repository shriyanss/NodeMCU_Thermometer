# NodeMCU_Thermometer
This a basic code example to display the live temperature on an OLED connected to the Node MCU and also make it available through a simple endpoint

## Connecting the wires
### OLED display
- GND to GND
- VCC to 3V3
- SCL to D1
- SDA to D2
### DHT 11 Sensor
- Out to D3
- + to 3V3
- - to GND

# Web Endpoints
Web Endpoint is accessible through [http://192.168.4.1/](http://192.168.4.1/)
## /
Simply display the temperature and humidity
## /temperature
Show the temperature (raw)
## /humidity
Show the humidity (raw)

# Using it with other projects
You can either use a dedicated NodeMCU for this and to make it available to other devices, you can use the endpoints at `/humidity` and at `/temperature` to get humidity and temperature respectively or you can simply embed the lines from the code you need in your project.

# Troubleshooting
The main error is getting `nan` in temperature as well as humidity. To troubleshoot this,
- Check if all wiring is done properly
- Restart it (NodeMCU)
