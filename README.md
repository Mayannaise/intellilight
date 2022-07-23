# Intellilight
Adaptive smart bulb controller using ESP32 and ambient light sensor.

This project was designed for the _Element14_
[**Summer of Sensors Design Challenge**](https://community.element14.com/challenges-projects/design-challenges/summer-of-sensors-design-challenge/w/documents/27682)
under the challenge title:

**Exploration Station** - _Best Use of the SensorXplorer Sensors Wins_

## Acronyms and Abbreviations
Acronym | Meaning
---|---
ALS | Ambient Light Sensor
BOM | Bill of Materials
HW  | Hardware
I2C | Inter-Integrated Circuit (protocol)
IDE | Integrated Development Environment
MCU | Micro-controller
OSS | Open Source Software
SW  | Software

## BOM
ID | Item | Manufacturer | Qty | Cost | Description
---|---|---|---|---|---
1 | ESP32 PICO-KIT       | Espressif | 1 | £10.08 | Micro-controller to read the sensors (via I2C) and control the light bulb (via WiFi)
2 | VCNL4035X01-GES-SB   | Vishay    | 1 | £24.02 | Proximity and ambient light sensor module
3 | Tapo L530 Smart Bulb | TP-Link   | 1 | £8.98  | WiFi smart light bulb, no hub required

## Development Environment

I use Linux as my main operating system, so all examples, instructions, screenshots etc.
will be based on `Ubuntu 20.04`.

### IDE
Most SW developers will be familiar with editors such as `Eclipse`, `VSCode` and `Notepad++`.
Since I use Linux and I'm a strong advocate for free OSS, I personally use `VSCodium`.
There is a `VSCodium` extension available to help develop and debug applications for the
`ESP32` range of MCUs. This can be installed by searching for `Espressif IDF` in the "Extensions"
sidebar from within `VSCodium`.
