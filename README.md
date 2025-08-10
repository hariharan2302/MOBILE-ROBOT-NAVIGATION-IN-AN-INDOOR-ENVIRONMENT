# MOBILE ROBOT NAVIGATION IN AN INDOOR ENVIRONMENT

A cost-effective autonomous mobile robot system featuring 16 ultrasonic sensors and IMU for 360-degree obstacle detection, precise localization, and real-time navigation in indoor environments.

![Project Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![License](https://img.shields.io/badge/License-Apache%202.0-blue)
![Arduino](https://img.shields.io/badge/Arduino-Mega%202560-00979D)
![Python](https://img.shields.io/badge/Python-3.x-3776AB)

## 🎯 Project Overview

This project implements an advanced mobile robot navigation system that combines multiple sensor technologies for autonomous indoor navigation. The system features a unique 16-sensor ultrasonic array providing complete 360-degree coverage, integrated with gyroscopic sensors for enhanced localization and mapping capabilities.

### Key Features

- **360° Obstacle Detection**: 16 ultrasonic sensors arranged in a ring configuration
- **Real-time Visualization**: Live mapping using Python Turtle graphics
- **Wireless Communication**: ESP8266 WiFi module for sensor data transmission
- **Dual Control System**: Autonomous navigation + Bluetooth remote control
- **Sensor Fusion**: IMU integration with Kalman filtering
- **Omnidirectional Movement**: Mecanum wheel drive system
- **Scalable Architecture**: Modular design supporting 1, 8, 12, or 16 sensors

## 🏗️ System Architecture

```
┌─────────────────┐    WiFi     ┌─────────────────┐
│   Arduino Mega  │◄───────────►│  Python Visual │
│   + 16 Sensors  │             │   + Mapping     │
│   + IMU + WiFi  │             └─────────────────┘
└─────────────────┘
         ▲
    Bluetooth
         ▼
┌─────────────────┐
│  Mobile Phone   │
│  RC Controller  │
└─────────────────┘
```

## 📋 Table of Contents

- [Hardware Components](#-hardware-components)
- [Software Requirements](#-software-requirements)
- [Installation Guide](#-installation-guide)
- [Project Phases](#-project-phases)
- [Usage Instructions](#-usage-instructions)
- [Technical Details](#-technical-details)
- [Project Structure](#-project-structure)
- [Results & Performance](#-results--performance)
- [Contributing](#-contributing)
- [License](#-license)
- [Contact](#-contact)

## 🔧 Hardware Components

### Main Components
- **Arduino Mega 2560** - Main microcontroller
- **16x HC-SR04 Ultrasonic Sensors** - Distance measurement
- **MPU6050** - 6-axis IMU (Gyroscope + Accelerometer)
- **ESP8266 WiFi Module** - Wireless communication
- **HC-05 Bluetooth Module** - Remote control interface
- **4x DC Motors with Mecanum Wheels** - Omnidirectional movement
- **Motor Driver Shield** - Motor control
- **Power Supply**: 5V (Arduino) + 12V (Motors)

### Sensor Configuration
```
Sensor Array Layout (Top View):
      S1   S2   S3   S4
   S16               S5
S15                     S6
   S14               S7
      S13 S12 S11 S10
         [Robot Center]
```

## 💻 Software Requirements

### Development Environment
- **Arduino IDE** (version 1.8+)
- **Python 3.x** with required libraries
- **PyCharm** (recommended IDE)

### Python Dependencies
```bash
pip install pyserial
pip install turtle
pip install socket
pip install math
```

### Arduino Libraries
- Adafruit_MPU6050
- Adafruit_Sensor
- WiFiEsp
- WiFiEspUdp
- NewPing
- AFMotor
- Wire
- I2Cdev

## 🚀 Installation Guide

### Step 1: Hardware Setup
1. Install **CH34X USB Driver** (provided in `CH34x_Install_Windows_v3_4/`)
2. Connect Arduino Mega to PC via USB Type-B cable
3. Assemble the 16-sensor ring according to the design specifications

### Step 2: Software Installation
1. **Upload Arduino Code**:
   ```bash
   # Open Arduino IDE
   # Load: final_wireless_code_16_sensor_copy/final_wireless_code_16_sensor_copy.ino
   # Select Board: Arduino Mega 2560
   # Upload to device
   ```

2. **Configure WiFi Settings**:
   ```cpp
   char ssid[] = "YourWiFiName";
   char password[] = "YourPassword";
   IPAddress serverIP(192, 168, 1, 100); // Update IP
   ```

3. **Install Python Environment**:
   ```bash
   git clone https://github.com/hariharan2302/MOBILE-ROBOT-NAVIGATION-IN-AN-INDOOR-ENVIRONMENT.git
   cd MOBILE-ROBOT-NAVIGATION-IN-AN-INDOOR-ENVIRONMENT
   pip install -r requirements.txt
   ```

### Step 3: Mobile App Setup
1. Download **"Bluetooth RC Controller"** from app store
2. Pair with HC-05 Bluetooth module
3. Configure control mapping (F/B/L/R/G/I/H/J/Q)

## 📊 Project Phases

### Phase I: Gyroscope-Based Navigation
- **Objective**: Implement basic localization using IMU sensors
- **Features**: 
  - MPU6050 integration
  - Basic tilt measurement
  - Simple visualization with OpenCV
- **Code**: `Gyroscope measurement (PHASE I)/`

### Phase II: Advanced Multi-Sensor Integration
- **Objective**: Complete 360° obstacle detection and mapping
- **Features**:
  - 16 ultrasonic sensor array
  - Sensor fusion with Kalman filtering
  - Real-time wireless visualization
  - Autonomous navigation algorithms
- **Code**: `final_wireless_code_16_sensor_copy/` + `visualisatio of 16 sensor (Wireless code)/`

## 📖 Usage Instructions

### Quick Start
1. **Power Setup**:
   ```
   ✅ Connect 5V battery to Arduino Mega
   ✅ Connect 12V battery to motor shield
   ✅ Ensure all connections are secure
   ```

2. **Wireless Connection**:
   ```
   ✅ Arduino connects to WiFi network
   ✅ Python script listens on UDP port 139
   ✅ Bluetooth pairs with mobile device
   ```

3. **Launch System**:
   ```bash
   # Terminal 1: Start Python visualization
   cd "visualisatio of 16 sensor (Wireless code)"
   python main.py
   
   # Mobile App: Connect and control robot
   # Real-time mapping displays obstacle positions
   ```

### Control Commands
| Command | Action | Description |
|---------|--------|-------------|
| `F` | Forward | Move forward |
| `B` | Backward | Move backward |
| `L` | Left | Move left |
| `R` | Right | Move right |
| `G` | Forward-Left | Diagonal movement |
| `I` | Forward-Right | Diagonal movement |
| `H` | Backward-Left | Diagonal movement |
| `J` | Backward-Right | Diagonal movement |
| `Q` | Rotate | Rotate in place |

## 🔬 Technical Details

### Sensor Specifications
- **Range**: 2cm - 400cm per sensor
- **Accuracy**: ±3mm
- **Update Rate**: 50Hz
- **Coverage**: 22.5° per sensor (16 sensors = 360°)

### Communication Protocol
```
WiFi Network: Custom SSID
Protocol: UDP
Port: 139
Data Format: "S1,S2,S3,...,S16,GX,GY,GZ"
Transmission Rate: 10Hz
```

### Coordinate System
- **Scale**: 1 unit = 84 cm
- **Origin**: Robot center position
- **Mapping**: Real-time obstacle plotting
- **Grid**: Background reference system

### Performance Metrics
- **Detection Range**: 5 meters maximum
- **Angular Resolution**: 22.5 degrees
- **Response Time**: <100ms
- **Battery Life**: 2-3 hours continuous operation
- **Accuracy**: ±5cm positioning

## 📁 Project Structure

```
MOBILE-ROBOT-NAVIGATION-IN-AN-INDOOR-ENVIRONMENT/
├── 📁 CH34x_Install_Windows_v3_4/          # USB driver
├── 📁 Gyroscope measurement (PHASE I)/      # Phase 1 implementation
│   └── 📁 datavisualization/
│       └── main.py                          # Basic IMU visualization
├── 📁 final_wireless_code_16_sensor_copy/   # Arduino main code
│   └── final_wireless_code_16_sensor_copy.ino
├── 📁 visualisatio of 16 sensor (Wireless code)/ # Python visualization
│   ├── main.py                              # Real-time mapping
│   └── Another important code.py            # Alternative implementation
├── 📄 8th sem_project report.pdf           # Detailed project report
├── 📄 Readme for instructions.txt          # Setup instructions
├── 📄 LICENSE                               # Apache 2.0 License
└── 📄 README.md                             # This file
```

## 📈 Results & Performance

### Achievements
- ✅ **360° Coverage**: Complete environmental awareness
- ✅ **Real-time Performance**: <100ms response time
- ✅ **Accurate Mapping**: ±5cm precision
- ✅ **Wireless Operation**: Stable UDP communication
- ✅ **Autonomous Navigation**: Successful obstacle avoidance
- ✅ **Dual Control**: Manual override capability

### Applications
- **Indoor Mapping**: Automated floor plan generation
- **Security Patrol**: Autonomous surveillance systems
- **Research Platform**: SLAM algorithm development
- **Educational Tool**: Robotics and sensor fusion learning
- **Warehouse Automation**: Inventory and navigation systems

## 🎥 Demo & Documentation

### Visual Output
The system provides real-time visualization showing:
- Live obstacle positions in 360°
- Robot position and orientation
- Grid-based coordinate system
- Distance measurements for each sensor
- Movement trajectory tracking

### Performance Videos
- Real-time obstacle detection demonstration
- Autonomous navigation in complex environments
- Wireless communication stability tests
- Mobile app control interface

## 🤝 Contributing

We welcome contributions! Please follow these steps:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Development Guidelines
- Follow Arduino coding standards
- Comment code thoroughly
- Test all hardware integrations
- Update documentation for new features
- Ensure backward compatibility

## 📝 License

This project is licensed under the **Apache License 2.0** - see the [LICENSE](LICENSE) file for details.

## 📞 Contact

### Project Team

**Ganesh Baskaran** - Design Engineer
- 📧 Email: ganeshkarur1704@gmail.com
- 📱 Phone: +91 9790648017

**Hariharan Venkatraman** - Project Lead Developer
- 📧 Email: hariharanvenkatraman23@gmail.com
- 📱 Phone: +1 (716)986-1837
- 🐙 GitHub: [@hariharan2302](https://github.com/hariharan2302)

**Esha Gopalakrishnan** - Hardware Integration
- 📧 Email: esha1252002@gmail.com
- 📱 Phone: +91 7867007677

### Project Links
- 🔗 **Repository**: [Mobile Robot Navigation](https://github.com/hariharan2302/MOBILE-ROBOT-NAVIGATION-IN-AN-INDOOR-ENVIRONMENT)
- 📄 **Documentation**: [Project Report](8th%20sem_project%20report.pdf)
- 🎯 **Issues**: [Report Bugs](https://github.com/hariharan2302/MOBILE-ROBOT-NAVIGATION-IN-AN-INDOOR-ENVIRONMENT/issues)

---

### 🌟 Acknowledgments

- Thanks to the Arduino and Python communities for excellent libraries
- Special recognition to our academic advisors for guidance
- Appreciation to all contributors and testers

**⭐ If you found this project helpful, please give it a star!**

---
*Last Updated: January 2025*
