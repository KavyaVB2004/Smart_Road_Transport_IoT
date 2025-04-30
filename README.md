# **IoT Based Smart Road Transport**

An intelligent traffic management and street lighting system using IR sensors, Arduino, and IoT components to optimize vehicle flow, enable emergency control, and enhance pedestrian safety.

# **Description**

This Smart IoT-Based Road Transport System addresses inefficiencies in conventional traffic management by integrating automation, manual override, and real-time vehicle detection.

### Key features include:

- IR sensors dynamically adjust traffic signal durations based on vehicle density, reducing unnecessary wait times and improving flow.  
- An OLED pedestrian display shows WALK/STOP animations based on traffic light status, enhancing pedestrian safety.  
- A manual override system using a touch sensor and joystick enables authorized personnel to control signal directions in emergencies (e.g., ambulance passage).  
- A secondary Arduino (slave) displays countdown timers on an 8x8 red dot matrix, giving drivers visual preparation time.  
- An automatic street lighting system uses LDRs to activate lights in low-light conditions — all without using extra Arduino pins.  
- A welcome LCD display at the road entrance shows greetings, alerts, or dynamic info like weather data.  
- This system aims to improve safety, traffic efficiency, and user awareness in modern urban transport infrastructure.  

# **Hardware Components**

- 2x Arduino Uno boards (Master + Slave)  
- 5x IR Sensors (Vehicle detection)  
- 1x OLED Display (Pedestrian view)  
- 1x 8x8 Red Dot Matrix (Countdown)  
- 1x Touch Sensor (Mode toggle)  
- 1x Joystick (Manual lane control)  
- 2x LDRs (Street light control)  
- 2x LEDs per lane (Red + Green)  
- 1x LCD Display (Welcome/Alerts)

# **Getting Started**  

## Dependencies  

Ensure you have the following hardware and software prerequisites:  

### Hardware:  

- Common Ground for Master and Slave Arduino: It is important that both the Master and Slave Arduino share a common ground to ensure proper communication. Connect the GND pin of the Master Arduino to the GND pin of the Slave Arduino to establish a shared ground.
- Windows 10 / Linux / macOS 
- 2x Arduino Uno boards  
- USB cables for Arduino programming  
- IR sensors, OLED, LED, Joystick, Touch Sensor, Red Dot Matrix, LDRs, LCD Display  

### Software:  

- Arduino IDE  
- Adafruit SSD1306 and GFX libraries (for OLED)  
- Wire library (pre-installed in Arduino IDE)
- Wokwi animator ( for OLED nimation frame bits)

# **Installing**
1. Clone the repository
   Open terminal and run the following command to clone the repository:
   
   git clone https://github.com/KavyaVB2004/Smart_Road_Transport_IoT.git
2. Open Arduino IDE
   Launch the Arduino IDE on your system.

3. Open the code files
   Navigate to the code folder in the cloned repository.
   Open the appropriate .ino files for Master and Slave.

4. Install Required Libraries
   In Arduino IDE:  
   Go to Sketch > Include Library > Manage Libraries...  
   Search for and install the following libraries:
   - Adafruit SSD1306
   - Adafruit GFX

5. Connect the Arduino
   Plug in both the Master and Slave Arduino boards via USB cables.

6. Select the Correct Board and Port
   Ensure the correct board and port are selected under the Tools menu.

7. Upload the Code

   - Upload master.ino to the Master Arduino.  
   - Upload slave.ino to the Slave Arduino.
  
# **Usage**

Once the code is uploaded and the components are wired:

1. **Automatic Traffic Management**  
   - IR sensors detect vehicles in each lane.
   - Traffic light durations adjust dynamically based on sensor input.

2. **Pedestrian Display**  
   - The OLED shows **WALK** or **STOP** animations depending on traffic signals.
   - Enhances pedestrian safety and awareness.

3. **Manual Mode (Override)**  
   - Touch sensor toggles between **Automatic** and **Manual** mode.
   - In manual mode, use the joystick to control which lane has the green light.
   - Useful during emergencies (e.g., ambulance passage).

4. **Countdown Display**  
   - The slave Arduino displays the countdown on an 8x8 red dot matrix.
   - Helps drivers prepare for signal changes.

5. **Street Lighting System**  
   - LDRs automatically turn street lights ON/OFF based on ambient light.
   - Implemented without using additional Arduino pins.

6. **LCD Welcome Display**  
   - Displays custom welcome messages, safety alerts, or real-time info.

# **Troubleshooting**

### Problem: Countdown timer not displaying
- **Check:** Master-Slave serial connection.
- **Fix:** Ensure both Arduinos share a common ground and correct baud rate is used.

### Problem: OLED not showing animations
- **Check:** Wiring and library installation.
- **Fix:** Confirm Adafruit SSD1306 and GFX libraries are installed.

### Problem: Manual override not working
- **Check:** Joystick and touch sensor connections.
- **Fix:** Verify proper analog/digital pin configuration in code.

# **Future Enhancements**

- Integrate camera or ultrasonic sensors for more precise vehicle detection.
- Add GSM/Wi-Fi module for remote monitoring and mobile app integration.
- Use solar power and battery backup for off-grid operation.
- Expand to include pedestrian button control.

# License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
