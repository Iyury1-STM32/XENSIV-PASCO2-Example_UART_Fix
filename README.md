# Indoor CO2 Sensing

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

Parts list: STM32 B-U585I-IOT02A x1
Infineon Xensiv PASCO2 CO2 sensor x1
HYFAI Universal AC/DC Power Adapter x1
47uF electrolytic capacitor x1
10uF ceramic capacitor x2
100nF ceramic capacitor x2

The sensor requires a 3.3V supply for its microcontroller, and a 12V supply for the IR light source driver. Both voltage sources share a common ground.
 ![internal_diagram](https://user-images.githubusercontent.com/76540445/189276004-33408bd3-8a63-42dd-a08c-f0691aa2c0a3.PNG)
 
Wiring instructions are also included in the datasheet:
![image](https://user-images.githubusercontent.com/76540445/189276868-cf4ef7b2-ba99-4a4c-9e0b-459334d7ff51.png)

The HYFAI Universal AC/DC Power Adapter is used to supply 12V to the sensor.
