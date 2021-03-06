<h1 align="center">
  <img src="doc/AR.png" alt="AR"> 
  Instructions for fundamental testing on angel 
</h1>

<p align="center">
<b><a href="#overview">Overview</a></b>
|
<b><a href="#table-of-contents">Table of contents</a></b>
|
<b><a href="#preparing-for-testing">Preparing for testing</a></b>
|
<b><a href="#system-architecture">System architecture</a></b>
|
<b><a href="#module-test">Module test</a></b>
|
<b><a href="#function-test">Function test</a></b>
|
<b><a href="#team">Team</a></b>
|
<b><a href="#license">License</a></b>
</p>

## Overview

This is a guiding repository that gives you basic instructions to test and drive our robot system, **angel** for this case. 
Required firmwares and programs are all included in this repository. 
**Please go through this document very carefully.**
In addition, this repository is also designated to store angel's design files, including system block diagram, schematics of electronic components and CAD files, etc. 
They are placed in the **/hardware_design** folder. 
 
## Table of contents
* [**Preparing for testing**](#preparing-for-testing)
* [**System architecture**](#system-architecture)
* [**Module test**] (#module-test) 
  * [**Base driving test**](#base-driving-test)
  	* [**Step 1 Check hardware setups for base driving**](#step1-check-hardware-setups-for-base-driving)
  	* [**Step 2 Upload firmware to 3in1 board**](#step-2-upload-firmware-to-3in1-board)
  	* [**Step 3 Upload firmware to mega2560**](#step-3-upload-firmware-to-mega2560)
  	* [**Step 4 Drive angel base**](#step-4-drive-angel-base)
  * [**Laser scanning test**](#laser-scanning-test)
  	* [**Step 1 Check hardware setup for laser scanning**](#step-1-check-hardware-setup-for-laser-scanning)
  	* [**Step 2 Launch rplidar driver**](#step-2-launch-rplidar-driver)
  * [**Camera Joint control test. To be continue ...**](#camera-joint-control-test)
  	* [**Step 1 Check hardware setup to control camera's heading**](#step-1-check-hardware-setup-to-control-camera's-heading)
  	* [**Step 2 Uploading firmware to camera joint driver 3in1 board**](#step-2-upload-firmware-to-camera-joint-driver-3in1 board)
  	* [**Step 3 Control camera's heading**](#step-3-control-camera's-heading)
  * [**Security Sensing test. To be continue ...**](#security-sensing-test)
  	* [**Step 1 Check sensor setup**](#step-1-check-sensor-setup)
  	* [**Step 2 Read each sensor**](#step-2-read-each-sensor)
  * [**Camera image topic test**](#camera-image-topic-test)
  	* [**Step 1 Check camera setup**](#step-1-check-camera-setup)
  	* [**Step 2 Run camera on odroid**](#step-2-run-camera-on-odroid)	  
* [**Function test**](#function-test)
  * [**Tele-operation**](#tele-operation)
  	* [**Step 1 Check requirements of tele-operation**](#step-1-check-requirements-of-tele-operation)
  	* [**Step 2 Tele-operating Angel**](#step-2-tele-operating-angel)
  * [**Auto docking. To be determine ...**](#auto-docking)
  	* [**Step 1 Check docking module setup**](#step-1-check-docking-module-setup)
  	* [**Step 2 Launch auto docking sequence**](#step-2-launch-auto-docking-sequence)
* [**Appendix**](#appendix)

## Preparing for testing

1. Prepare a cell phone installed "teleop" app provided from Software team.
	https://github.com/wennycooper/teleop_apk/raw/master/android_tutorial_teleop-debug.apk

2. Prepare the SD/EMMC card provided from Software team and install on the odroid board.
3. Find a monitor and a HDMI cable and connect to odroid board.
4. Power on the odroid XU4 board and wait for ubuntu finishing starting.
5. Check odroid IP address. 
	
	Open a terminal and type the following command on odroid board.
	
	```
	ifconfig
	``` 
	In our example, the IP address is `192.168.25.110` 
6. Download this repository and compile it on odroid by going through the following steps.

	On a terminal, please type the following commands.
	
	```
	ssh odroid@[Odroid IP address]
	cd ~/catkin_ws/src
	git clone https://github.com/advancedroboticsaws/angel.git
	cd ~/catkin_ws
	catkin_make 
	```
7. **Very important!** Please go to the following page and make sure you have connected components to the specified port on the hub.
	
	https://github.com/Muchun-Yen/Assign-symbolic-links-for-auto-mounting-USB-devices-by-udev 


## System architecture

This section gives you an overview on angel's design.
s
**Note: All files related to angel's hardware design are placed in the folder `/hardware_design`.** 

* Overall block diagram

![System](doc/Angel%20system%20diagram.png)

* Specifications -- not available yet

* Detailed wiring schematics -- not available yet 

* Schematic of DC motor driver board `3in1 board`

![3in1 board-1](doc/3in1%20board-1st.jpg)

![3in1 board-2](doc/3in1%20board-2nd.jpg)
  
## Module test

Here, we separate Angel into several modules. 

<p align="center">
<b><a href="#base-driving-test">Base driving test</a></b>
|
<b><a href="#laser-scan-test">Laser scan test</a></b>
|
<b><a href="#camera-joint-test">Camera joint test</a></b>
|
<b><a href="#security-sensing-test">Security Sensing test</a></b>
|
<b><a href="#camera-image-topic-test">Camera image topic test</a></b>
</p>

### Base driving test

<a name="base-driving-test-step1"></a>

#### Step 1 `Check hardware setups for base driving`

Check all the hardware setup !!

Here we regard motor control module as a motor **JGB37 3530B** + driver **3in1 board**.
Also, both motor control module for each wheel must be connected to mega2560.

Mark the following checklist yourself when you have finished each setup.

- [ ] Check your motor model. Make sure you have installed the right one.
- [ ] Motor control modules are well prepared. Each motor connects to their driver correctly.
- [ ] Motor control module for **left wheel** connects to mega2560 correctly.  
- [ ] Motor control module for **right wheel** connects to mega2560 correctly. 

**Note: If you have any doubt or not sure the hardware wirings, please review system diagrams and double check before going to the next step.**

Having finished the first step, you are about to make wheels spin.
There are two control boards that should have firmwares uploaded, **mega2560 & 3in1 board**. 

<a name="base-driving-test-step2"></a>

#### Step 2 `Upload firmware to 3in1 board` 

Firmware for each wheel's driver is inside the folder.

```
/mcu_control/base_control/vnh5019_base/src
```

* Upload firmware to left/right wheel
	1. Open `vnh5019_base.ino` with Arduino IDE on your PC.
	2. **Important! Please go to line 8 and 9. Uncomment one of these two lines according to which wheel you are about to do the uploading.**
	3. Modify Arduino PWM Frequency in Arduino IDE. 
		
		Copy
		
		```
		/mcu_control/wiring.c
		```
		 to ~/arduino-1.6.5/hardware/arduino/avr/cores/arduino.
		 
		 Make sure the following code is on line 31 or 32 in wiring.c.   
		 
		 ```
		 #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(8 * 256))
		 ```
	4. Set your upload target to **promini**.
	5. Choose your **port** carefully.
	6. Go for it! Click upload!
		
		If you get any error when uploading,
		* Please look into the errors carefully.
		* Please check the port you choose.
			   
	7. Go through the steps above again **for the other wheel**.
	

<a name="base-driving-test-step3"></a>

#### Step 3 `Upload firmware to mega2560` 

Firmware for mega2560 is inside the following folder.

```
/mcu_control/base_control/mega_base_ultrasonic_angelbot/src
```

* Upload firmware to mega2560
	1. Open `mega_base_ultrasonic_angelbot.ino` with Arduino IDE on your PC.
	2. Libraries for this firmware is placed in	
	
		```
		/mcu_control/mega_base_ultrasonic_angelbot/lib
		``` 
	   Copy all the contents inside and paste them to `/%document%/arduino/libraries` folder on your PC.
	3. Make sure the following code is on line 31 or 32 in wiring.c.   
		 
		 ```
		 #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(8 * 256))
		 ```
		 If you don't understand this step, please refer to step 2 Upload firmware to 3in1 board above to find out. 
	4. Set your upload target to **mega2560**.
	5. Choose your **port** carefully.
	6. Go for it! Click upload!
		If you get any error when PC uploading,
		* Please look into the errors carefully.
		* Please check the port you choose.
		* Please make sure you have put all the libraries into the Arduino's library folder.
			If you get the message about library conflicts, please find out those files and delete the old one.   
	
<a name="base-driving-test-step4"></a>

#### Step 4 `Drive angel base`

**Hook up angel on any surface without wheels touching anything.**

1. Open a terminal on you PC and type

	```
	ssh odroid@[odroid IP]
	```
	to access to angel.
2. Launch base driver.
	Type the following command.
		
	``` 
	roslaunch angelbot angelbot_sanitytest.launch
	```
	check and make sure there is no error message pops up.
3. Open another terminal and access into odroid by entering ssh commands (step1) then type:
	
	```
	rostopic list
	```   
	
	Check and make sure the following two topics are on the list.
	
	```
	/cmd_wheel_angularVel
	/feedback_wheel_angularVel	
	```
4. Start driving wheels one by one.  
	* left wheel
		* forward direction
		
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 6.283 speed2: 0.0 driverstate: false" 
			```
			
			On another terminal
					
			```
			rostopic echo /feedback_wheel_angularVel  
			```
			
			Enter `ctrl + c` to exit.
			- [ ] Check if left wheel is rotating in the forward direction **same as the base's heading**.
			- [ ] Check if left wheel is rotating at a speed of 6.283/s, which also means 1 rev/s.
			- [ ] Check the topic /feedback_wheel_angularVel shows the same result. 
					If the speed feedback is not the same as the command, please check the wirings of encoder.
			
			Type the following to make it stop.
				
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: 0.0 driverstate: false" 
			```
			Enter `ctrl + c` to exit.
		* backward direction
					
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: -6.283 speed2: 0.0 driverstate: false" 
			```
			On another terminal
					
			```
			rostopic echo /feedback_wheel_angularVel  
			```
			
			Enter `ctrl + c` to exit.
			- [ ] Check if left wheel is rotating in the backward direction **opposite to the base's heading**.
			- [ ] Check if left wheel is rotating at a speed of 6.283/s, which also means 1 rev/s.
			- [ ] Check the topic /feedback_wheel_angularVel shows the same result.
					f the speed feedback is not the same as the command, please check the wirings of encoder.
			
			Type the following to make it stop.
				
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: 0.0 driverstate: false" 
			```
			Enter `ctrl + c` to exit.
	* right wheel
		* forward direction
		
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: 6.283 driverstate: false" 
			```
			On another terminal
					
			```
			rostopic echo /feedback_wheel_angularVel  
			```
			Enter `ctrl + c` to exit.
			- [ ] Check if left wheel is rotating in the forward direction **same as the base's heading**.
			- [ ] Check if left wheel is rotating at a speed of 6.283/s, which also means 1 rev/s.
			- [ ] Check the topic /feedback_wheel_angularVel shows the same result.
					f the speed feedback is not the same as the command, please check the wirings of encoder.
			
			Type the following to make it stop.
				
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: 0.0 driverstate: false" 
			```
			Enter `ctrl + c` to exit.
		* backward direction
		
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: -6.283 driverstate: false" 
			```
			On another terminal
					
			```
			rostopic echo /feedback_wheel_angularVel  
			```
			Enter `ctrl + c` to exit.
			- [ ] Check if left wheel is rotating in the backward direction **opposite to the base's heading**.
			- [ ] Check if left wheel is rotating at a speed of 6.283/s, which also means 1 rev/s.
			- [ ] Check the topic /feedback_wheel_angularVel shows the same result.
					If the speed feedback is not the same as the command, please check the wirings of encoder.
			
			Type the following to make it stop.
				
			```
			rostopic pub /cmd_wheel_angularVel angelbot/WheelCmd "speed1: 0.0 speed2: 0.0 driverstate: false"
			``` 
			Enter `ctrl + c` to exit.
	
5. If you have finished all the steps, type `ctrl + c` on all the terminal you have opened to exit.
	
<p align="right">
<b><img src="doc/AR.png" alt="AR">End of base driving test</b>
|
<a href="#">BACK TO TOP</a>
</p>

### Laser scanning test

<a name="laser-scan-test-step1"></a>

#### Step 1 `Check hardware setups for laser scanning`

The laser scanner we use is **rplidar**. 
To use it, the complete hardware setup should contain **rplidar + data transmission board**.

Before going through the steps below, please mark the following checklist yourself when you have finished each setup.

- [ ] Check your data transmission board. Make sure you installed the right one.

**Note: If you have any doubt or not sure the hardware wirings,
please review system diagrams or datasheet and double check before going to next step.**

<a name="laser-scan-test-step2"></a> 

#### Step 2 `Launch rplidar driver`

This is to help you find out whether the rplidar you installed is functional and your hardware setup is correct.
Still, to make sure it is completely functional, please refer to **teleoperation** below in the functional test section.

* Launch laser scanner
	1. Open a terminal on you PC and type
	
		```
		ssh odroid@[Odroid IP]
		```
		to access to angel.
	2. The next step should be starting communication between odroid and rplidar through ROS.
		Open another termimal and type:
		
		```
		roslaunch angelbot rplidar.lanuch 
		```
		
		You will see something like this:
		
		```
		started roslaunch server http://192.168.25.110:60968/

		SUMMARY
		========
		
		......
		......
		
		NODES
		  /
		    rplidarNode (rplidar_ros/rplidarNode)
		
		......
		......
		RPLidar health status : 0
		```
	3. Open another terminal and type:
		
		```
		rostopic list
		```   
		Check if the topic **/scan** shows up. 
	4. Type the following command to see if anything shows up.
		
		```
		rostopic echo /scan
		```   
		You will see something similar on your terminal:
		
		![laser scan sample](doc/laser_scan_sample.png)
		
		Type `ctrl + c` to exit when you have finished checking.
	5. If you have finished all the steps, type `ctrl + c` on all the terminal you have opened to exit.

<p align="right">
<b><img src="doc/AR.png" alt="AR">End of laser scan test</b>
|
<a href="#">BACK TO TOP</a>
</p>

### Camera Joint control test

<a name="camera-joint-control-step1"></a>

#### Step 1 `Check hardware setup to control camera's heading`

The recent version of Angel's camera joint consists of a motor control module same as the one used to control wheels.
(a motor **JGB37 3530B** + **3in1 board**).
This motor control module must also be connected to mega2560.

**Cautions!!**

**We do not have `limit switch` on the joint, which is supposed to prevent Angel's joint or housing damages from operators giving position commands that the joint cannot reach.   
So please check the following list carefully.**

Mark the following checklist yourself when you have finished each setup.

- [ ] Check your motor model. Make sure you have installed the right one.
- [ ] Motor control module is well prepared. The motor connects to driver correctly.
- [ ] Motor control module connects to mega2560 correctly.
- [ ] **Please make sure Angel's camera is headed in Z direction, that is, toward the sky.** 

**Note: If you have any doubt or not sure the hardware wirings, 
please review system diagrams and double check before going to next step.**

<a name="camera-joint-control-step2"></a>

#### Step 2 `Uploading firmware to camera joint driver 3in1 board`

Firmware for joint position control is placed in the following folder.

```
/mcu_control/camera_joint_control/src
```

* Upload firmware to camera joint driver
	1. Open `vnh5019_camera_joint.ino` with Arduino IDE on your PC. 
	2. Modify Arduino PWM Frequency in Arduino IDE. 
		Copy
		
		```
		/mcu_control/wiring.c
		```
		 to ~/arduino-1.6.5/hardware/arduino/avr/cores/arduino.
		 
		 Make sure the following code is on line 31 or 32 in wiring.c.   
		 
		 ```
		 #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(8 * 256))
		 ```
	3. Set your upload target to **promini**.
	4. Choose your **port** carefully.
	5. Go for it! Click upload!
		If you get any error when PC uploading,
		* Please look into the errors carefully.
		* Please check the port you choose.
		* Please make sure you have put all the libraries into the folder.
			If you get the message about library conflicts, please find out those files and delete the old one.
	
<a name="camera-joint-control-step3"></a>

#### Step 3 `Control camera's heading`

To be determine !

* Launch camera heading control
	1. Open a terminal up on you PC and type
	
		```
		ssh odroid@[Odroid IP]
		```
		to access to angel.
	2. Launch base driver. (Camera is connected to mega_base.)
		Type the following command.
			
		``` 
		roslaunch angelbot angelbot_sanitytest.launch
		```
		check if no error pops up.
	3. Open another terminal and access into odroid by entering ssh commands (step1) then type:
		
		```
		rostopic list
		```   
		
		Check if the following topic is on the list.
		
		```
		/camera_joint_position	
		```
	4. Type the following command to move the camera joint axis forward to 30 degree from the initial angle of 0 degree.
		
		```
		rostopic pub /camera_joint_position ... position: 30
		```
	5. 	Type the following command to move the camera joint axis backward to -30 degree from the previous angle of 30 degree.
		
		```
		rostopic pub /camera_joint_position ... position: -30
		```
	6. After you have finished controlling camera_joint, **please drive camera joint axis to the initial angle of 0 by giving 0 degree command.**
		The camera is supposed to look toward the sky when you turn off Angel's power.
		
		```
		rostopic pub /camera_joint_position ... position: 0
		```
	7. If you have finished all the steps, type `ctrl + c` on all the terminal you opened to exit.
			
### Security Sensing test

<a name="security-sensing-test-step1"></a>

#### Step 1 `Check sensor setup`

Mark the following checklist yourself when you have finished each setup.

- [ ] Check your sensor model. Make sure you have installed the right one.
- [ ] Make sure you have wired each sensor to the correct pin on mega2560.  

<a name="security-sensing-test-step2"></a>

#### Step 2 `Read each sensor`

To be continue ...

* Launch sensor reading
	1. Open a terminal up on you PC and type
	
		```
		ssh odroid@[Odroid IP]
		```
		to access to angel.
	2. Launch base driver. (Sensors are connected to mega_base.)
		Type the following command.
			
		``` 
		roslaunch angelbot angelbot_sanitytest.launch
		```
		check if no error pops up.
	3. Open another terminal and access into odroid by entering ssh commands (step1) then type:
		
		```
		rostopic list
		```   
		
		The following list should appear. 
		
		```
		/SensorActiveList
		/CurTemperature
		/CurHumidity
		/MotionDetection
		/FlameDetection
		/MQ2CO
		/DustDetection
		```
		
	5. Test these sensors by echoing each ros topics `one by one`. 
		
	* MQ2.
		
		Type the following command on a terminal.
		
		```
		rostopic echo /MQ2CO
		```
		
		You should see something like this.
		
		![MQ2CO](doc/mq2co.png)
		
		You can spray some gas material to see the value changing.
		
	* DHT22
		
		Type the following command on a terminal.
				
		```
		rostopic echo /CurTemperature
		```
			
		```		
		rostopic echo /CurHumidity
		```
		You should see something like this. (Unit: temperature: celsius; humidity: %)
		
		**Check whether the values are reasonable.**
		
		![DHT22-Temperature](doc/curtemperature.png)
		
		![DHT22-Humidity](doc/curhumidity.png)
		
		You can blow on the senser to see the value changing.
				
	* Flame sensor
		
		Type the following command on a terminal.
		
		```
		rostopic echo /FlameDetection
		```
		You should see something like this.
		
		![flame detection](doc/flamedetection.png)
		
		**Use a lighter to test it.**
		
	* PM2.5 -- not availble yet
		
	* PIR
		
		Type the following command on a terminal.
		
		```
		rostopic echo /MotionDedection
		```
		You should see something like this.
		
		![PIR](doc/motiondetection.png)
		
		**Simply wave your hand in front of the PIR sensor. The value on the screen would be `true` if something moves.**
	6. If you have finished all the steps, type `ctrl + c` on all the termianl you opened to exit.
		
### Camera image topic test

<a name="camera-image-topic-test-step1"></a>

#### Step 1 `Check camera setup`

Mark the following checklist yourself when you have finished each setup.

- [ ] Check your camera model. Make sure you have installed the right one.
- [ ] Camera shoud be connected to the hub.  

<a name="camera-image-topic-test-step2"></a>

#### Step 2 `Run camera on odroid`

* Launch image capturing
	1. Open a terminal up on you PC and type
	
		```
		ssh odroid@[Odroid IP]
		```
		to access to angel.
	2. The next step should be starting communication between odroid and the camera through ROS.
		Open a terminal and type the following command.
		
		``` 
		roslaunch angelbot usb_camera.launch
		```
	
		If everything goes right, you will see something like this
		
		```
		started roslaunch server http://192.168.25.110:37226/

		SUMMARY
		========
		
		PARAMETERS
		 ...
		 * /uvc_camera_node/device: /dev/video0
		 * /uvc_camera_node/exposure: 0
		 * /uvc_camera_node/frame_rate: 20
		 * /uvc_camera_node/gain: 100
		 * /uvc_camera_node/height: 240
		 * /uvc_camera_node/width: 320
		
		NODES
		  /
		    uvc_camera_node (uvc_camera/uvc_camera_node)
		...
		
		core service [/rosout] found
		process[uvc_camera_node-1]: started with pid [3439]
		...
		opening /dev/video0
		pixfmt 0 = 'MJPG' desc = 'MJPEG'
		  discrete: 640x480:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 1280x960:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 800x600:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 352x288:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 320x240:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 176x144:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 160x120:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 1280x720:   1/30 1/25 1/20 1/15 1/10 1/5 
		pixfmt 1 = 'YUYV' desc = 'YUV 4:2:2 (YUYV)'
		  discrete: 640x480:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 1280x960:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 800x600:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 352x288:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 320x240:   1/30 1/25 1/20 1/15 1/10 1/5 
		  discrete: 176x144:   1/15 1/10 1/5 
		  discrete: 160x120:   1/15 1/10 1/5 
		  discrete: 1280x720:   1/12 1/10 1/5 
		  int (Brightness, 0, id = 980900): -255 to 255 (1)
		  int (Contrast, 0, id = 980901): 0 to 30 (1)
		  int (Saturation, 0, id = 980902): 0 to 127 (1)
		  int (Hue, 0, id = 980903): -16000 to 16000 (1)
		  bool (White Balance Temperature, Auto, 0, id = 98090c): 0 to 1 (1)
		  int (Gamma, 0, id = 980910): 20 to 250 (10)
		  menu (Power Line Frequency, 0, id = 980918): 0 to 2 (1)
		    0: Disabled
		    1: 50 Hz
		    2: 60 Hz
		  int (White Balance Temperature, 16, id = 98091a): 2500 to 7000 (1)
		  int (Sharpness, 0, id = 98091b): 0 to 3 (1)
		  int (Backlight Compensation, 0, id = 98091c): 0 to 2 (1)
		  menu (Exposure, Auto, 0, id = 9a0901): 0 to 3 (1)
		  int (Exposure (Absolute), 16, id = 9a0902): 2 to 5000 (1)
		  bool (Exposure, Auto Priority, 0, id = 9a0903): 0 to 1 (1)
		```
	3. Open another terminal and type:
		
		```
		rostopic list
		```   
		Check if there is a topic name `/camera/image_raw`. 
	4. Type the following command to see if there is anything shows up.
		
		```
		rostopic echo /camera/image_raw
		```   
		You will see something similar on your terminal:
		
		![camera image sample](doc/camera_image_topic.png)
	5. If you have finished all the steps, type `ctrl + c` on all the terminal you opened to exit.

<p align="right">
<b><img src="doc/AR.png" alt="AR">End of Module test</b>
|
<a href="#">BACK TO TOP</a>
</p>

## Functional test 

After you go over all the module tests, Angel is now capable of perform some function.
This section is to give a basic instruction of test iconic functions.
If you haven't passed the module tests, **please go back and finish tests before continue.**

<p align="center">
<b><a href="#tele-operation-test">Tele-operation test</a></b>
|
<b><a href="#auto-docking-test">Auto docking test</a></b>
</p>

### Tele-operation

<a name="tele-operation-test-step1"></a>

#### Step 1 `Check requirements of tele-operation`

- [ ] Check if you pass all the module tests. 
- [ ] Make sure you have "teleop" app on you cell phone.  

<a name="tele-operation-test-step2"></a>

#### Step 2 `Tele-operating Angel`

1. Use ssh command to access to odroid

	```
	ssh odroid@[Odroid IP]
	```
2. Launching sequence to drive angel around and scanning.
	
	```
	roslaunch angelbot angelbot_functionaltest.launch
	```
3. Check topics

	``` 
	rostopic list
	```
	Make sure /andbot/cmd_vel is on the list.
4. Bring up your cell phone. Open teleop app and type `http://[Odroid IP]:11311` to access to angel.
6. Put angel in a open area with large spaces and begin the following test
	Tap on the screen and:
	* Forward direction: Drive angel to move forward 2 meters.
	* Backward dirction: Drive angel to move backward back to origin.
	* Rotation (left): Drive angel to rotate 3 rounds in the counter-clockwise direction.
	* Rotation (right): Drive angel to rotate 3 rounds in the clockwise direction. 
7. Check if there is a map shows up. This is to make sure the laser scanner works.
	If the expected map does not show up, laser scanner might be broken.
			
8. If you have finished all the steps, close you app on the phone and type `ctrl + c` on all the terminal you opened to exit.

### Auto docking

To be determine.

<a name="auto-docking-test-step1"></a>

#### Step 1 `Check docking module setup`

Mark the following checklist yourself when you have finished each setup.

- [ ] Make sure there are auto docking module on angel. 
- [ ] Docking station is well-built.  

<a name="auto-docking-test-step2"></a>

#### Step 2 `Launch auto docking sequence`

1. Please redo Function: Tele-operation step 1 ~ 2.
2. Use your cell phone to drive angel to about `2.5 meter` in front of the docking station and set its heading opposite to it.
3. Launching `charging mode` to enable auto docking function. 
	Open another terminal and ssh into angel and type the following command.
	
	``` 
	rosservice call /DockingEnable true
	```	
4. See if angel is approaching the ducking station and finally touches the charging station.
5. If you carry out step 4 successfully, please type the following command to end up charging mode.

	``` 
	rosservice call /DockingEnable false
	``` 
6. If you have finished all the steps, type `ctrl + c` on all the terminal you opened to exit. 

<p align="right">
<b><img src="doc/AR.png" alt="AR">End of Function test</b>
|
<a href="#">BACK TO TOP</a>
</p>

## Appendix


* udev rules on odroid. **[(reference)](https://github.com/Muchun-Yen/Assign-symbolic-links-for-auto-mounting-USB-devices-by-udev)**

```
KERNEL=="ttyUSB*", ATTRS{idProduct}=="6001", ATTRS{idVendor}=="0403", ATTRS{devpath}=="1.1", SYMLINK+="imu"
KERNEL=="ttyACM*", ATTRS{idProduct}=="0042", ATTRS{idVendor}=="2341", ATTRS{devpath}=="1.2.1.1", SYMLINK+="mega_base"
KERNEL=="ttyUSB*", ATTRS{idProduct}=="6001", ATTRS{idVendor}=="0403", ATTRS{devpath}=="1.2.1.2", SYMLINK+="rplidar"
```

## License
Copyright © 2016 Advanced Robotics Corporation

<p align="right">
<img src="doc/AR.png" alt="AR"><a href="#">BACK TO TOP</a>
</p>
