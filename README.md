# IoT_FlowSensor
This project involved creating an Internet of Things (IoT) leak detector for water piping systems. In order to test the effectiveness of such a system, two water flow sensors were connected at different points of the pipeline, each connected to a NodeMCU ESP8266 board. The IoT-based microcontroller boards send the flowrate data over the internet (through the MQTT protocol) another NodeMCU board which acts as the primary controller for the water flow. Once the primary controller detects a high difference in flow rate between the sensors at the pipeline, there is a obvious leak. The primary controller is interfaced with a solenoid valve through a 12 V relay. If a leak is detected, the main controller will send a signal to the relay to close the solenoid valve and prevent further water loss. 

Project Components:

Electronic Components - NodeMCU ESP8266, 5V flow rate sensor, 12V Solenoid Valve, 12V Relay.

Software/Programming Languages - Arduino IDE, MQTT

Instructions for the repository:
The Arduino IDE codes for Flow Sensor 1 and Flow Sensor 2 are named NEW_MQTT_subscribe.ino and NEW_MQTT_subscribe2.ino respectively. As for the code of the main controller, it is named NEW_PANEL3.ino. 

