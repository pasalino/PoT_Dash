# Dash Counter

## Abstract
This project is a subset of main project [Meeting Counter](https://github.com/pasalino/MeetingCounter) for [IoT meetup Milano](https://www.meetup.com/it-IT/IoT-Meetup-Milano/) community.  
With Arduino and Node.js recreate a copy of Amazon Dash: one button for call a service.
We share this project in [#2 meetup](http://bit.ly/2urjH8i) of this community 

## Mission
This project is created for [IoT meetup Milano](https://www.meetup.com/it-IT/IoT-Meetup-Milano/)

[Arduino spiegato agli idraulici](https://www.meetup.com/it-IT/IoT-Meetup-Milano/events/240049140/https://www.meetup.com/it-IT/IoT-Meetup-Milano/events/240049140/)

It's a basic example to use arduino with node.js REST

## Electrical Scheme
In docs there is an Electrical scheme for build a device
Use Fritzing for open and look how connect all components
List of scheme:
* Scheme for use Arduino Uno

### Components
* Arduino uno
* ESP8266 - Wifi
* 1 Red led diode
* 1 Blue led diode
* 1 switch
* 1 10k Ohm Resistor
* 1 220 Ohm Resistor
* 1 100 Ohm Resistor


## Architecture
* Arduino connect on Web with ESP8266. 
* The server expose a REST API


## Usage

Click button for start service increment counter on server

### Installation

#### Node.js

In server folder run command

```npm install```

#### ESP8266
**Important!!!**  

Change ESP8266 bound rate from 115200 to 9600 for use this module.

**Steps:**
* Connect arduino without program on memory
* Open serial monitor
* Write ```AT``` command and wait responde OK
* Write ```AT+CIOBAUD=9600``` and change boundrate

**Check:**
* Reboot arduino
* Open serial monitor and change bound rate in dropdownlist from 115200 to 9600
* Try to write AT and wait OK

## Dependences

### Arduino
* [WifiEsp](https://github.com/bportaluri/WiFiEsp)
* SoftwareSerial

#### Node.js
* [Bluebird](http://bluebirdjs.com/docs/getting-started.html) 

## API AND WEB

* Use ```http://server:port``` for list of meetings
* Use PATCH METHOD and ```user:pwd@server:port/api/v1/counter/[MeetingName]``` for add visitors on specific meeting
* Use DELETE METHOD and ```user:pwd@server:port/api/v1/counter/[MeetingName]``` for add clear users in meetings

## Difference From Orginal Project
This project is a subset of main project [Meeting Counter](https://github.com/pasalino/MeetingCounter).  
The main project has more features than this basic project:
* Websocket for update real-time counter
* Single page for each meeting
* Basic Auth for API
* Sass preprocessor for styles
* Structured Directory
* Catching Error
* 404 page
* 500 page
* More update