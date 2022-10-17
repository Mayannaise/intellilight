# Intellilight
Adaptive smart bulb controller using ESP32 and ambient light sensor

This project was designed for the _Element14_
[**Summer of Sensors Design Challenge**](https://community.element14.com/challenges-projects/design-challenges/summer-of-sensors-design-challenge/w/documents/27682)
under the challenge title:

**Exploration Station** - _Best Use of the SensorXplorer Sensors Wins_

## Acronyms and Abbreviations
Acronym | Meaning
---|---
ALS  | Ambient Light Sensor
BOM  | Bill of Materials
CCM  | Configuration and Change Management
COB  | Close of Business
FOSS | Free Open Source Software
HLD  | High-Level Design
HW   | Hardware
I2C  | Inter-Integrated Circuit (protocol)
IoT  | Internet of Things
IDE  | Integrated Development Environment
LLD  | Low-Level Design
MCU  | Micro-controller
OSS  | Open Source Software
SDK  | Software Development Kit
SW   | Software

## BOM
This the initial BOM for the main components identified thus far. Following the
component research scheduled to be conducted in week 1, the BOM will be
populated more and then by COB week 2, the full BOM will be compiled following
the schematic capture activity.

ID | Item | Manufacturer | Qty | Cost | Description
---|---|---|---|---|---
1 | ESP32 PICO-KIT       | Espressif | 1 | £10.08 | Micro-controller to read the sensors (via I2C) and control the light bulb (via WiFi)
2 | VCNL4035X01-GES-SB   | Vishay    | 1 | £24.02 | Proximity and ambient light sensor module
3 | Tapo L530 Smart Bulb | TP-Link   | 1 | £8.98  | WiFi smart light bulb, no hub required
