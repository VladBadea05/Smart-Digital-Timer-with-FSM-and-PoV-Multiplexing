# Smart-Digital-Timer-with-FSM-and-PoV-Multiplexing
📌 Project Overview
This repository contains the source code for an embedded digital countdown timer built on the Arduino platform. The project was designed with scalability and performance in mind, demonstrating core embedded software engineering principles. Instead of using basic sequential logic, the system is driven by a robust Finite State Machine (FSM) and utilizes custom-built multiplexing to control a 4-digit 7-segment display without external libraries.

⚙️ Core Technical Features
Finite State Machine (FSM) Architecture: The system logic is cleanly divided into three isolated states (STATE_SET_TIME, STATE_COUNTDOWN, and STATE_ALARM) using enum and switch-case structures. This ensures deterministic behavior, avoids logic conflicts, and makes the code highly scalable for future features.

Custom Persistence of Vision (PoV) Multiplexing: Implemented a continuous display refresh algorithm from scratch. By rapidly switching active digits with a 4ms micro-delay, the code tricks the human eye into seeing all four digits simultaneously, successfully bypassing the hardware limitations of a shared-segment display.

Non-Blocking Hardware Control: The entire execution flow avoids the use of blocking delay() functions (except for the micro-delay required by the PoV). State transitions and countdown decrements are strictly handled using millis(), allowing the microcontroller to process inputs and refresh the display continuously without freezing.

Analog Data Scaling & Math Logic: The user interface relies on a single potentiometer mapped to a 3600-second scale (0 to 60 minutes). The raw seconds are dynamically converted into hexadecimal digit formats using modulo (%) and division (/) operators for real-time display.

🛠️ Hardware Requirements
Arduino Uno / Nano

1x 4-Digit 7-Segment Display (Common Cathode)

1x Potentiometer (for time adjustment)

1x Piezo Buzzer (for the alarm system)

Jumper wires & Breadboard

🚀 How It Works
Set Mode: The system reads the potentiometer values and dynamically updates the display. If the value remains unchanged for 3 seconds, the FSM automatically locks the time and transitions to the countdown sequence.

Countdown Mode: The timer strictly decrements every 1000ms while maintaining the display refresh rate.

Alarm Mode: Once the time reaches 00:00, the system triggers an audible piezoelectric alarm before automatically resetting to the Set Mode for a new cycle.
