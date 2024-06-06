**How does OTA Web Updater Work?**
The first sketch should be uploaded via serial port. This sketch should contain the code to create the OTA Web Updater, so that you are able to upload code later using your browser.
The OTA Web Updater sketch creates a web server you can access to upload a new sketch via web browser.
Then, you need to implement OTA routines in every sketch you upload, so that you’re able to do the next updates/uploads over-the-air.
If you upload a code without a OTA routine you’ll no longer be able to access the web server and upload a new sketch over-the-air.


**Prerequisites**
Before proceeding with this tutorial you should have the ESP32 add-on installed in your Arduino IDE. Follow one of the next tutorials to install the ESP32 on the Arduino IDE, if you haven’t already.


**ESP32 OTA Web Updater**
When you install the ESP32 add-on for the Arduino IDE, it will automatically install the ArduinoOTA library. Go to File > Examples >ArduinoOTA> OTAWebUpdater.

**You should change the following lines on the code to include your own network credentials:**

const char* ssid = "";
const char* password = "";
The OTAWebUpdater example for the ESP32 creates an asynchronous web server where you can upload new code to your board without the need for a serial connection.

Upload the previous code to your ESP32 board. Don’t forget to enter your network credentials and select the right board and serial port.



After uploading the code, open the Serial Monitor at a baud rate of 115200, press the ESP32 enable button, and you should get the ESP32 IP address:

Now, you can upload code to your ESP32 over-the-air using a browser on your local network.

To test the OTA Web Updater you can disconnect the ESP32 from your computer and power it using a power bank, for example (this is optional, we’re suggesting this to mimic a situation in which the ESP32 is not connected to your computer).

**Update New Code using OTA Web Updater**
Open a browser in your network and enter the ESP32 IP address. You should get the following:
lionahmmed.local

**Username: Lion
Password: Lion**
You can change the username and password on the code.

Note: After you enter the username and password, you are redirected to the /serverIndex URL. You don’t need to enter the username and password to access the /serverIndex URL. So, if someone knows the URL to upload new code, the username and password don’t protect the web page from being accessible from others.

A new tab should open on the /serverIndex URL. This page allows you to upload a new code to your ESP32. You should upload .bin files (we’ll see how to do that in a moment).

As you can see, we’ve added the “blink without delay” code to the OTAWebUpdater code, so that we’re able to make updates later on.

After copying the code to your Arduino IDE, you should generate a .bin file.

Generate a .bin file in Arduino IDE
Save your sketch as LED_Web_Updater.

**To generate a .bin file from your sketch, go to Sketch > Export compiled Binary**
A new file on the folder sketch should be created. Go to Sketch > Show Sketch Folder. You should have two files in your Sketch folder: the .ino and the .bin file. You should upload the .bin file using the OTA Web Updater.

Upload a new sketch over-the-air to the ESP32
In your browser, on the ESP32 OTA Web Updater page, click the Choose File button. Select the .bin file generated previously, and then click Update.

After a few seconds, the code should be successfully uploaded.
