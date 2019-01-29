# Google-Calendar-with-Node-MCU
Simple IoT device that takes events from Google Calendar and displays them on LCD.

**HARDWARE:**
1. NodeMCU v2
2. 20x4 LCD (HD44780 compatible) with I2C adapter
3. Li-Po charge control board dedicated for powerbanks
4. Tactile reset switch
5. On/Off switch of choice
6. Li-Po 18650 cell with holder
7. Perfboard, soldering iron, saw or Dremel, some M3 nuts and bolts.
8. Enclosure


**SOFTWARE:**
1. ArduinoIDE
2. Google Account

**HOW IT WORKS:**
1. Device connects with WiFi getting time from router and displays it on LCD, refreshing each 5 seconds.
2. Device connects with GoogleScript, which then gets events from your Google Calendar.
3. GoogleScript retrieves events scheduled for current day and sends it to NodeMCU, which displays it on LCD.

**TO IMPROVE:**
1. Titles of events cannot be longer than 20 chars long, otherwise it will be cut to 17 chars + ellipsis;
2. Displaying title of more than one event at a time;


No events scheduled:
![noevents](https://user-images.githubusercontent.com/34771956/51911687-c82ce300-23d2-11e9-97c0-541c6eea430f.png)
![noevents1](https://user-images.githubusercontent.com/34771956/51911692-ca8f3d00-23d2-11e9-9e01-2919f6c77d0f.jpg)

Event scheduled for later that day:
![eventlater](https://user-images.githubusercontent.com/34771956/51911704-d11db480-23d2-11e9-99b7-2e1bb31b9b4f.png)
![eventlater1](https://user-images.githubusercontent.com/34771956/51911710-d3800e80-23d2-11e9-8f71-f0fa38021d9a.jpg)

Event taking place at this moment:
![eventnow](https://user-images.githubusercontent.com/34771956/51911720-d5e26880-23d2-11e9-9035-84ca44ed30a4.png)
![eventnow1](https://user-images.githubusercontent.com/34771956/51911725-d844c280-23d2-11e9-944e-f378ddd34cf4.jpg)

Inside:
![inside](https://user-images.githubusercontent.com/34771956/51911729-da0e8600-23d2-11e9-93f4-7aa05c409855.png)

**HOW TO RUN:**
1. Go to script.google.com
2. Create new script file
3. Copy JavaScript code from gscript folder and paste it to script file.
4. Enter your email address.
5. Save, run function doGet();
6. Publish code, enable tinkering with calendar and grant access for everyone, even anonymous.
7. Copy your Google Script ID and paste it in Arduino file.
8. Enter your WiFi credentials.
9. Upload Arduino file to NodeMCU.
10. Enjoy.
