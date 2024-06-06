**Explanation**

Wi-Fi Setup: The ESP32 connects to the specified Wi-Fi network.
mDNS Setup: Sets up mDNS so the ESP32 can be accessed using a hostname.
HTML Pages: Serves login and combined pages.
Firmware Update: Handles firmware updates through a form upload.
Restart Endpoint: Handles the /restart endpoint which restarts the ESP32 when accessed.
Combined Page: Contains both the firmware update form and the restart button.
Step-by-Step Usage
Replace ssid and password with your actual Wi-Fi credentials.
Upload the code to your ESP32.
Open the Serial Monitor to check the ESP32's IP address once it’s connected to Wi-Fi.
Open a web browser and navigate to the IP address of the ESP32.
Log in using the username and password (Lion and Lion).
Navigate to the /serverIndex page to access both the firmware update form and the restart button.
Use the form to update the firmware.
Click the Restart button to restart the ESP32.
