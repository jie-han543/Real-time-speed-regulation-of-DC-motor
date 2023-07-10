# Real-time-speed-regulation-of-DC-motor

### Introduction
The motor system can generate different disturbances through a knob. To make the system quickly recover to the target speed after the disturbance, the parameters are determined by Matlab, and PID control module is realized based on MSP430. In addition, different target speeds can be set by the button.

TimerA0 is used to generate the interrupts, and the incremental encoder is used to calculate the DC motor speed, which is displayed through the 7-segment digital tube. TimerA1 is used to generate PWM signal as motor input.


### Mapping table
![image](https://github.com/jie-han543/Real-time-speed-regulation-of-DC-motor/assets/57163528/ad9a4375-9a9f-4604-bc83-d060072375b7)

![image](https://github.com/jie-han543/Real-time-speed-regulation-of-DC-motor/assets/57163528/2eb9cc6c-2e7b-47d5-b95a-73c6172ee441)


### The strategy of measuring the speed
According to the principle of the incremental encoder, it outputs 3 pulse for every revolution. We can use the MSP430's internal timer and set it to trigger an interrupt every 0.1 seconds, capturing the total number of input pulses at P2.6/P2.7 in this period, thus converting the speed of the motor.

In addition, pulses on P2.6 and P2.7 can be measured simultaneously, and the phase difference between them determines the direction of rotation of the motor.

### Function

*port_init*

Initialize the pins. Including.
-	Set P2.1 ~ P2.2 as output.
-	Set P2.6 as GPIO input. P2.6 is the phase A of the incremental encoder. Use pull-down resistor and enable the interrupt.
-	Set P1.3 as GPIO input. P1.3 is a button. Use pull-down resistor and enable the interrupt.

*timer_init*

Initialize the timer. Use TimerA_0 to create interrupts and count the pulse number num every 0.1 seconds. 
-	SMCLK = 1MHz, DIV = 2.
-	Up mode. 
-	Set the timer interrupt per 0.1 seconds.

*pwm_init*

Initialize the PWM. 
-	Set P2.1 as Timer1_A3.TA1.
-	Set P2.2 as primary peripheral module function. Use TimerA_1 to create PWM as the input of DC motor.
-	SMCLK = 1MHz, DIV = 1.
-	Up mode. 
-	Output mode 7.
-	The duty ratio = 35%.

*PID_controller*

When the disturbance occurs, it will work to return to the desired speed. Adjust the output PWM according to the speed feedback from the encoder.
The parameters of PID controller:
-	Kp = 0.00002
-	Ki = 0.000008
-	Kd = 0.000001

*affiche_Vitesse(speed)*

Display the speed Vitesse.

*TIMER1_A0_ISR*

Calculation speed when interrupt happens. speed = (num/3)*10*60. Call the PID control and display the speed. Clear interrupt flag.

*TIMER1_A1_ISR*	

Clear interrupt flag.

*PORT2_ISR*	

The interruption occurs at each pulse edge of the sensor on the motor. Add num for each interrupt to measure the speed. Clear interrupt flag.

*PORT1_ISR*	

An interrupt occurs when the button is pressed. Change the button value between [0,2]. Clear interrupt flag.

*main*	

Change the target speed according to the value of button. Three different target speeds are set: 3000, 4800, 6000.

![image](https://github.com/jie-han543/Real-time-speed-regulation-of-DC-motor/assets/57163528/a3731599-a701-4b57-8c33-e533c0f90ef2)




