# Wemos-RC-Track-Tank
This project is a tracked robot vehicle controlled using an **Wemos D1 mini** microcontroller.   The electronic system, control logic, web interface, and wiring layout are custom-designed, while the mechanical chassis is based on a 3D model from Thingiverse.

---
## 📦 Project Overview
This robot uses **differential steering** (independent left/right motor control) and can be controlled through a smartphone-friendly web interface.  
The project combines:
- Dual motor control (DRV8833)
- Web-based control interface
- Proportional steering mode
- Active buzzer with custom melody
- LED with button 
- 3D-printable chassis and mechanical parts

---
## 🧩 3D Model Reference
The mechanical parts (chassis, tracks, gears, etc.) are based on:

**Tracked Vehicle Platform v1 (TVP-1)**  
Link: https://www.thingiverse.com/thing:6633454

Modifications I made include:
- Custom mounts for the Wemos D1 mini board
- Space for motor driver and wiring
- Cable routing adjustments
- Additional support structures

3D files are located in the **/models** folder.

---
## ⚙️ Key Features
- Wemos D1 mini/ESP8266 microcontroller  
- Mobile-friendly **web controller** (HTML/CSS/JS)  
- Proportional motor control  
- Active buzzer with custom melody
- LED with button
- Compatible with LittleFS for serving web files  
- DRV8833 dual motor driver  
- Fully 3D-printable body  

---
## 🛠️ Electronic Components
- ESP8266 (NodeMCU / Wemos D1 Mini / ESP-12)  
- DRV8833 motor driver  
- DC gear motors  
- Li-ion   
- Active buzzer
- LED
- Switch    

---
(Full wiring details provided in `/docs`.)

---
## 🧱 3D Printing
- Material: PLA / ABS  
- Infill: 20–30%  
- Layer height: 0.2 mm  
- All STL files are in the `/models` directory  

---
## 🚀 How to Use
1. Upload the code from the **/code** folder  
2. (Optional) Upload web control files to LittleFS  
3. Power on the ESP8266  
4. Connect your phone to the ESP8266 network / WiFi  
5. Open the IP address in your browser  
6. Control the tank 🚗💨  

---
## 📜 License
- Original 3D model follows the license provided by the Thingiverse creator  
- Custom electronics and software in this repository are free for **non-commercial and educational use**  

---

## 🙏 Credits
Original mechanical design by the creator of **TVP-1** on Thingiverse.  
Electronics, firmware, and integration by **Moch Rizky F.**.
