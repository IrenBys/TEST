########################################################################
## This script is used to send and receice data between two COM ports ##
########################################################################
import sys
from port_tools import tools
import logging


def main():
    serial_list = tools().open_ftdi_ports()   
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
            logging.warning("Couldn't find data for reading")
            return 1                

    else:
        logging.warning("Couldn't write/receive a message")
        return 1  


if __name__ == '__main__':
    sys.exit(main())
