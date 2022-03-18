# TEST

The project is created to receive and transmit messages between two USART blocks. 
This is implemented for the STM32F407VG Discovery Kit using the Keil µVision and the STL.

A Python script is developed to test the project performance:
 - looking for a com port to which ftdi is connected
 - opens this port
 - asks for a message to be sent
 - and then receives this message.

This script can be run by 'python -B port.py' command for Windows.
