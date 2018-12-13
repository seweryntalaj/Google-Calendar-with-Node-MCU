# Google-Calendar-with-Node-MCU
Simple IoT device that takes events from Google Calendar and displays them on LCD.

HARDWARE:
1. NodeMCU v2
2. 20x4 LCD (HD44780 compatible) with I2C adapter

SOFTWARE:
1. ArduinoIDE
2. Google Account

HOW TO RUN:
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
