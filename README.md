# Make Zurich 2020 Badge
## HTS221 temperature & humidity sensor demo

### Features
- Periodically read the HTS221 sensor
- Print measurements to the Serial Monitor
- Change the MZ2020 badge LED colour depending on measured temperature

### Requirements 
Depends on the following Arduino libraries to be installed 
(Tools -> Manage Libraries)
- Adafruit_Neopixel
- Arduino_HTS221

### Limitations
- Display range is limited from -23°C to 42°C due to geek worker union demands
