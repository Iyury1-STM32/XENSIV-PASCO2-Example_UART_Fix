# Indoor CO2 Sensing

![blockdiagram](https://user-images.githubusercontent.com/76540445/192641730-168c4bf1-e662-4bef-a312-0dc307cb4783.png)

# Summary

This application is used for detection of indoor air CO2 content. The CO2 measurements can be used as inputs for demand controlled ventilation (DCV), activation of air purifiers, or an alarm system if CO2 levels reach unsafe levels. Measurement points can also be uploaded to a cloud server for data analytics.

The XENSIV PASCO2 sensor by Infineon is used to detect the CO2 concentration, whose measurements are transfered by UART to an STM32 B-U585I-IOT02A development board. The folder "CO2_ex" contains STM32CubeIDE project files for the B-U585I development board. The application uses ITTIA DB IoT store CO2 measurements locally with timestamps. Code has been included from an example project obtained from an ITTIA DB IoT Workshop hosted on June 15, 2022.

The XENSIV PASCO2 sensor was accessed using a software library availalbe on the Infineon Github repository:
[https://github.com/Infineon/sensor-xensiv-pasco2](https://github.com/Infineon/sensor-xensiv-pasco2)

The PASCO2 can be interfaced using I2C or UART. UART will be used for this example. The src file 'main.c' has been modified to initalize the USART2 peripheral and define a UART handle type 'huart2'. USART1 cannot be used because it is connected to the micro-usb port of the B-U585I.

The PASCO2 software library is available on the Infineon Github repository:
[https://github.com/Infineon/sensor-xensiv-pasco2](https://github.com/Infineon/sensor-xensiv-pasco2)

The src files 'xensiv_pasco2.c' and 'xensiv_pasco2_platform.c' has been added to CO2_ex/Core/Src, and the header files 'xensiv_pasco2.h', 'xensiv_pasco2_regs.h' and 'xensiv_pasco2_platform.h' have been added to ITTIA_DB_Fx_NoR/Core/Inc.

Definitions for the methods declared in 'xensiv_pasco2_platform.h' have been implemented with definitions specific to the STM32U5 platform, and are defined in 'xensiv_pasco2_platform.c'.

The datasheet for the PASCO2 is available from [https://www.infineon.com/cms/en/product/sensor/co2-sensors/pasco2v01/](https://www.infineon.com/cms/en/product/sensor/co2-sensors/pasco2v01/)

The application code is contained in "pasco2_example.c" under CO2_ex/Core/Src.

# Hardware Setup

Parts list: STM32 B-U585I-IOT02A x1     <br />
Infineon Xensiv PASCO2 CO2 sensor x1    <br />
HYFAI Universal AC/DC Power Adapter x1  <br />
47uF electrolytic capacitor x1          <br />
10uF ceramic capacitor x2               <br />
100nF ceramic capacitor x2              <br />

The sensor requires a 3.3V supply for its microcontroller, and a 12V supply for the IR light source driver. Both voltage sources share a common ground.
 ![internal_diagram](https://user-images.githubusercontent.com/76540445/189276004-33408bd3-8a63-42dd-a08c-f0691aa2c0a3.PNG)
 
Wiring instructions are also included in the datasheet:
![image](https://user-images.githubusercontent.com/76540445/189276868-cf4ef7b2-ba99-4a4c-9e0b-459334d7ff51.png)

The HYFAI Universal AC/DC Power Adapter is used to supply 12V to the sensor.

![HardwareSetup](https://user-images.githubusercontent.com/76540445/192639246-1f9dbbc1-75c1-4d8b-8097-dcc0d2173a4e.jpg)

# Software Setup

The application code is contained in "pasco2_example.c".

The main function creates two Azure RTOS ThreadX threads of equal priority to run "measurementTask" and "publisherTask". No time slices are provisioned to these threads, so cooperative scheduling is required. The thread running "publisherTask" starts automatically, initializes ITTIA DB IoT and the PASCO2 sensor, and then starts the thread running "measurementTask".

The "measurementTask" thread reads from the PASCO2 sensor in 10s intervals. The infrared emitter of the PASCO2 sensor requires at least 10s between reads in order to cool down. A timer "pco2_timer" is created to count down for 10s, and then signal a semaphore "pco2_timer_sem". The "measurementTask" will block on this semaphore, and then begin the measurement sequence once the semaphore is available after the 10s timer has expired. A watchdog timer "meas_watchdog" is used to detect when the measurement task has timed out on a read. The timer is activated when the measurement sequence begins and deactivated when the measurement sequence has completed. If the measurement task is preempted by FileX or a DMA interrupt during the measurement sequence, the measurement watchdog may time out as well. To ensure this does not occur, the timer is set sufficiently long such that the DMA interrupt handler has time to complete. After the measurment is taken, it is timestamped and stored into a time series on ITTIA DB IoT. When the measurement sequence has completed, "measurementTask" signals a "meas_rdy" semaphore, and calls "tx_thread_relinquish" to yield the CPU to the publisher task.

The "publisherTask" thread waits on the "meas_rdy" semaphore without blocking, so it is free to do other work until a measurement is available to publish. Once the "meas_rdy" semaphore is available, the "publisherTask" can read the value/timestamp pair from the CO2 time series stored on ITTIA DB IoT, and then publish the pair to an MQTT topic to be received from an MQTT broker. For the time being, the value/timestamp pair is output to the console, which can be read by opening a serial monitor using TeraTerm with the baud rate set to 115200.

By defining "APPDEBUG" at the beginning of "pasco2_example.c", additional print statements are output to the console which demonstrates context switching between threads. 

![teraterm_debug](https://user-images.githubusercontent.com/76540445/192642541-a5197149-833d-42db-94a4-93e124e82857.PNG)

Without APPDEBUG<br />
![teraterm_nodebug](https://user-images.githubusercontent.com/76540445/192642572-5468ed5d-9880-4c3f-add3-f5ee4e53d8a8.PNG)

