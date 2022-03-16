########################################################################
## This script is used to send and receice data between two COM ports ##
########################################################################
import sys
import serial
from serial.tools import list_ports

def find_ftdi_ports() -> list:
    ftdi_ports = []
    ports = list_ports.comports()
    for port in ports:
        serial_num = str(port.serial_number)            # it's necessary, cause the var port.serial_number is NoneType
        if port.vid == 1027 and serial_num[0] == "F":   # add only FTDI devices 
            ftdi_ports.append(port.device)
    # if no one FTDI device was found                                                      
    if not ftdi_ports:
        print("Couldn't find any FTDI port") 
        return None  
    print(ftdi_ports)      
    return ftdi_ports
    

def open_ftdi_ports() -> list:
    # generate the empty list of opened serial ports
    serial_list = []
    # get a list of avaible ports connected to FTDIs
    ftdi_ports = find_ftdi_ports()
    # open ports connected to FTDIs
    if ftdi_ports is not None: 
        try:
            for port_num in ftdi_ports:
                serial_port = serial.Serial(
                    port=port_num,
                    baudrate=115200,
                    bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    timeout=1
                )
                # add opened port to the list 
                serial_list.append(serial_port)
                print(f"The {serial_port.port} is opened!")
                return serial_list 

        except serial.SerialException as e:
            print(e)
            
    return None           


def main():
    serial_list = open_ftdi_ports()    
    if serial_list is not None:
        # the first port from the list is always selected for sending data
        print(f"The port to send data: {serial_list[0].port}")
        print("Enter data for sending:")    
        send_data = input()
        serial_list[0].write(str.encode(send_data))    
        # search the port with receiving data
        for i in range(len(serial_list)):
            receive_data = serial_list[i].readline()
            if receive_data:
                print(f"The port to receive data: {serial_list[i].port}")
                print("Receiving data:")
                print(receive_data.decode("utf-8"))
                return 0                 
        if not receive_data:
            print("Couldn't find data for reading")
            return 1                

    else:
        print("Couldn't write/receive a message")
        return 1  


if __name__ == '__main__':
    sys.exit(main())
