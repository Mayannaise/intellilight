# Intellilight
Adaptive smart bulb controller using ESP32 and ambient light sensor

This project was designed for the _Element14_
[**Summer of Sensors Design Challenge**](https://community.element14.com/challenges-projects/design-challenges/summer-of-sensors-design-challenge/w/documents/27682)
under the challenge title:

**Exploration Station** - _Best Use of the SensorXplorer Sensors Wins_

## Abstract
Over the past 10 years, as the technology has become more available and ever
more affordable, home automation has become increasingly popular. It started
out as a dream for the average home owner or something from a scify movie and
was only realised in the luxurious estates of the wealthy home owner. Now, home
automation is so affordable that it has been estimated that 70% of households
in the US own at least one smart device.

From 2014 onwards, homes across the world were being equipped with
`Amazon Echo`s, `Google Nest`s and `Samsung SmartThings` to name but a few of
the smart hubs which have riddled the technologies stores around the world. To
many, the Internet Of Things (IoT) was just a passing craze; it was a fad that
would never materialise. However, today everyone has to admit that the IoT is no
longer a handful of products build by a club of inventors in their bedrooms and
garages. The IoT is here to stay. Sales of smart home products are perpetually
increasing and dare I say, it has dominated our homes.

Admittedly, not everyone's homes are so automated that their weelie bins put
themselves out every week and the carpets are cleaned over night by some magical
elves, but many home owners today will have purchased (or perhaps been gifted by
their techy relative) the cheapest smart device just to see what all the craze
was about - the smartbulb.

Today perhaps people are saving money more than they used to; they are spending
less on frivolities like smart devices, or perhaps they cannot afford the
fully-automated system involving the purchase of a hub, or maybe the thought of
yet another magic white box with flashing lights in the corner of the room is a
bit too overwhelming for them. Whatever the reason, for many people, the smart
bulb is as far as their IoT itch has been scratched, and even then it is often
just popped in the standard lamp next to their reading chair and used as a
standard light bulb with whatever colour they happened to have selected last.

This project is designed to be a cheap addon to those homes who haven't taken
the leap of faith yet. Those people who have a smart bulb in their house but
never really use it. The bulb that is sat on full brightness with the worst
possible shade of blue and perhaps they have forgotten which of they million
apps is used to control it. This project is to give those people a little
helping hand as they step onto the IoT express.

## Project Brief
To design and build an intuitive, low-cost and aesthetically-pleasing device to
monitor the ambient light conditions around a standard lamp (reading light for
non-Brits) and control the brightness and hue of a smart bulb to provide the
best conditions to reduce power consumption and reduce eye strain and fatigue.

### Saving your eyes
In dimly lit conditions, the brightness of the bulb will be equalised
in order to reduce eye tension. Likewise in bright ambient light, the brightness
of the bulb will also be increased in order to fully illuminate the user's
book, magazine or tablet that they are reading. This will be acheived using
an ambient light sensor (ALS).

### Saving power
Additionally, a proximity/gesture sensor (non-contact) will be used to detect
when someone is sat next to the reading lamp. When a person sits down, the smart
bulb will turn on. When they get up from the chair, the smart bulb will turn off
again to save power.

## Aims and Objectives
The aim of this project is to be:
- **Low cost**: affordable by the audience identified above
- **Standalone**: does not require a smart hub or smart phone
- **Convenient**: easy to setup, operate and customise (if desired)
- **Eco**: contribute to household power saving

The objectives of this project are threefold:
- To **save power** by automatically turning on/off the light when required
- To **reduce eye tension** by choosing the most suitable brightness for the ambient conditions
- To **inspire** people to discover and realise low-cost, helpful IoT devices

## Credentials
My name is Owen. I have a 1st class degree in Electronics and Software Engineering.
I work on the development of safety-critical embedded systems in the aerospace
and defence industry. In my spare time I enjoy tinkering around with electronics
and software. One of my favourite projects is a Raspberry PI powered 3D printer which
I designed and built from scratch as documented [here](https://vimeo.com/101339613).

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

## Development Environment
I use Linux as my main operating system, so all examples, instructions,
screenshots etc. will be based on `Ubuntu 20.04` (unless I upgrade to
`Ubuntu 22.04` in the meantime).

### Configuration and Change Management (CCM)
The project will be configured
[here](https://github.com/Mayannaise/intellilight).

This will include all aspects of the project such as the research results,
requirements, design, tests, documentation, source code, schematics and models.

Any third party and open source code will be identifed clearly and the licences
included.

### IDE
Most SW developers will be familiar with editors such as `Eclipse`, `VSCode` and
`Notepad++`. Since I use Linux and I'm a strong advocate for free OSS, I
personally use `VSCodium`.

There is a `VSCodium` extension available to help develop and debug applications
for the `ESP32` range of MCUs. This can be installed by searching for
`Espressif IDF` in the "Extensions" sidebar from within `VSCodium`.

A spellchecker plugin should also be used.

## Project Schedule
* Week 1 - Research
  * Component research
  * Integration research
  * Create in depth project schedule
* Week 2 - Design
  * System Design (block diagram, Visio)
  * High-Level SW Design (block diagram, Visio)
  * High-Level HW Design (block diagram, Visio)
  * Low-Level SW Design (class/sequence diagrams, Enterprise Architect)
  * Low-Level HW Design (schematic diagram, EaglePCB)
* Week 3 - Sourcing
  * Create full BOM
  * Order components
  * Install SW tools, debuggers etc
* Week 4 - Build Prototype (Pt 1)
* Week 5 - Build Prototype (Pt 2)
* Week 6 - Testing
* Week 7 - Printed Circuit Board (PCB)
  * Design PCB (EaglePCB)
  * Manufacture/Order
* Week 8 - 3D Printed Case
  * Design 3D model (SolidWorks)
  * 3D print it
* Week 9 - Assembly and Test
  * Unit level tests
  * System level tests
* Week 10 - Final Tweaks
  * HW
  * SW
  * Interface
