# CAN-BASED-SMART-SHIP-MONITORING-AND-COLLISION-WARNING-SYSTEM

##  Project Overview

The system consists of three ECUs:

### ECU-1 – Marine Radar Navigation ECU

- Detects nearby objects using an HC-SR04 ultrasonic sensor.
- Uses an SG90 servo motor to scan the environment from 0° to 180°.
- Calculates object distance and collision risk.
- Sends distance information to ECU-3 through CAN.

### ECU-2 – Ship Safety Monitoring ECU

- Monitors engine-room safety conditions.
- Measures engine temperature using an LM35.
- Detects gas/fuel leakage.
- Detects fire using a flame sensor.
- Sends sensor information to ECU-3 through CAN.

### ECU-3 – Captain Control & Alert ECU

- Acts as the central CAN receiver.
- Receives data from ECU-1 and ECU-2.
- Displays real-time information on a 20×4 LCD.
- Provides visual alerts using LEDs when dangerous conditions are detected.

## Problem Statement

In modern ships, continuous monitoring of navigation and engine-room safety conditions is essential to prevent accidents and protect both the ship and its crew members. Traditional monitoring systems may rely on separate subsystems, making it difficult to obtain critical information at a single location and respond quickly to dangerous situations.

A ship may encounter several real-time hazards such as **nearby obstacles, collision risks, engine overheating, gas or fuel leakage, and fire**. If these conditions are not detected and communicated immediately, they can lead to serious damage, operational failure, or safety risks.

Therefore, there is a need for a **distributed, real-time monitoring and alert system** that can collect data from multiple sensors, process the information locally, and reliably communicate critical events between different control units.

This project addresses the problem by implementing a **CAN-based Smart Ship Monitoring and Collision Warning System** using three LPC2129-based ECUs. The system distributes monitoring tasks across independent ECUs and uses the CAN bus to transfer critical information to a centralized captain-control ECU.

The system is designed to:

- Detect nearby objects and identify potential collision risks.
- Monitor engine temperature in real time.
- Detect gas or fuel leakage.
- Detect fire conditions inside the engine room.
- Transmit sensor information between multiple ECUs using CAN communication.
- Display real-time ship safety information.
- Generate immediate visual alerts when dangerous conditions are detected.

# 🔹 ECU-1: Marine Radar Navigation ECU

## Hardware

- LPC2129 Development Board
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor

## Working

- The SG90 servo motor scans the environment from 0° to 180°.
- At each angle, the HC-SR04 ultrasonic sensor measures the distance of nearby objects.
- The LPC2129 processes the measured distance.
- Distance information is transmitted to the Captain Control & Alert ECU through CAN.

## CAN Message

| CAN ID | Data |
|---|---|
| 0x102 | Object Distance |

# 🔹 ECU-2: Ship Safety Monitoring ECU

## Hardware

- LPC2129 Development Board
- LM35 Temperature Sensor
- MQ-2 Gas Sensor
- Flame Sensor

## Functions

This ECU monitors critical conditions inside the ship's engine room:

- Engine temperature monitoring
- Gas/fuel leakage detection
- Fire detection

The sensor data collected by ECU-2 is processed and transmitted to the Captain Control & Alert ECU through the CAN bus for centralized monitoring and real-time alert generation.

## CAN Messages

| CAN ID | Data |
|---|---|
| 0x104 | Engine Temperature |
| 0x105 | Gas Status |
| 0x106 | Fire Status |

# 🔹 ECU-3: Captain Control & Alert ECU

## Hardware

- LPC2129 Development Board
- 20×4 LCD
- LEDs

## Function

This ECU acts as the central CAN receiver and provides real-time information and alerts to the captain.

It receives sensor information from both ECU-1 and ECU-2 through the CAN bus.

## LCD Monitoring

The 20×4 LCD displays:

- Engine temperature
- Gas leakage status
- Fire detection status
- Object distance
- Collision status

## Collision Warning System

When ECU-3 receives distance information with CAN ID 0x102, the distance is evaluated and the corresponding status is displayed on the LCD.

| Distance | Status | LED Indication |
|---|---|---|
| 0–15 cm | 🔴 DANGER | Red LED + Warning LED |
| 15–25 cm | 🟡 WARNING | Yellow LED |
| >25 cm | 🟢 SAFE | Green LED |

## Example LCD Display

```text
DISTANCE: 12cm
STATUS: DANGER
TEMP: 35.52
GAS:N FIRE:N
```
## Engine Temperature Monitoring

When ECU-3 receives the engine-temperature message:

**CAN ID: 0x104**

The temperature value is displayed on the LCD in degrees Celsius.

## Gas Leakage Detection

When ECU-3 receives the gas-status message:

**CAN ID: 0x105**

If no gas leakage is detected:

```text
GAS:N
```

If gas leakage is detected:

```text
GAS:Y
```

The warning LED is activated when gas leakage is detected.

## Fire Detection

When ECU-3 receives the fire-status message:

**CAN ID: 0x106**

If no fire is detected:

```text
FIRE:N
```

If fire is detected:

```text
FIRE:Y
```

The warning LED is activated when a fire condition is detected.

## Software Used

- Keil µVision
- Flash Magic
- Embedded C

# CAN Communication

The project uses CAN communication to exchange data between the three ECUs.

## CAN Message Mapping

| CAN ID | Source ECU | Destination | Data |
|---|---|---|---|
| 0x102 | ECU-1 | ECU-3 | Object Distance |
| 0x104 | ECU-2 | ECU-3 | Engine Temperature |
| 0x105 | ECU-2 | ECU-3 | Gas Status |
| 0x106 | ECU-2 | ECU-3 | Fire Status |


## Key Features

- Three-node distributed ECU architecture
- CAN-based communication between independent ECUs
- Servo-based ultrasonic scanning from 0° to 180°
- Real-time object-distance monitoring
- Collision-risk classification
- Engine temperature monitoring
- Gas/fuel leakage detection
- Fire detection
- Centralized monitoring
- Visual warning system
- Dedicated CAN identifiers for different sensor data

## Learning Outcomes

This project provided hands-on experience with:

- Designing a distributed embedded system
- Implementing CAN-based ECU communication
- Interfacing multiple sensors with a microcontroller
- Processing real-time sensor data
- Implementing collision-warning logic
- Designing a centralized monitoring and alert system
- Integrating multiple hardware modules into a single safety-oriented application
