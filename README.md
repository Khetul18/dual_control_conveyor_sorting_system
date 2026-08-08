# Dual-Control Conveyor Belt Sorting System

An automated conveyor belt sorting system developed for sorting objects
based on **material and colour** using a dual-Arduino control architecture.

The system uses two **Arduino Mega 2560** microcontrollers, a **TCS3200
colour sensor**, a modified **metal detector module**, a **NEMA 17 stepper
motor**, an **A4988 stepper driver**, and **MG90 servo motors**.

This project was developed as part of the research paper:

> **Design and Development of a Dual Control Conveyor Belt System for Object Sorting**

---

## Overview

Material sorting is an important task in industrial automation. This
project presents a low-cost automated conveyor belt system capable of
detecting and sorting objects based on their **material and colour**.

The system first detects whether an object is metallic using a modified
metal detector. Colour detection is then performed using a TCS3200 colour
sensor. Based on the sensor readings, servo-driven mechanisms divert the
object to the appropriate position.

---

## Key Features

- Dual Arduino Mega 2560 control architecture
- Automated conveyor belt movement
- Metal and non-metal detection
- Colour-based object classification
- TCS3200 colour sensing
- Modified metal detector based on electromagnetic induction
- Servo-based object sorting
- NEMA 17 stepper motor driven conveyor
- A4988 stepper motor driver
- Threshold-based classification
- Real-time information through Arduino IDE Serial Monitor

---

## System Architecture

The system is divided into two control units.

### Arduino Mega 1

Responsible for:

- TCS3200 colour sensor
- Colour detection
- Colour classification
- Servo-based sorting

### Arduino Mega 2

Responsible for:

- Metal detection
- Material classification
- Conveyor control
- A4988 stepper motor driver
- NEMA 17 stepper motor

---

## Working Principle

The sorting process follows the sequence:

```text
Object Placement
       ↓
Conveyor Movement
       ↓
Metal Detection
       ↓
Material Classification
       ↓
Colour Detection
       ↓
Colour Classification
       ↓
Servo Actuation
       ↓
Object Sorting
       ↓
System Reset
       ↓
Next Object
