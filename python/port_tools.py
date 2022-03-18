import serial
from serial.tools import list_ports


class tools:
    
    def find_ftdi_ports(self) -> list:
        self.ftdi_ports = []
        self.ports = list_ports.comports()
        for port in self.ports:
            if port.vid == 1027:
                # add only FTDI devices    
                self.ftdi_ports.append(port.device)
        # if no one FTDI device was found                                                      
        if not self.ftdi_ports:
            print("Couldn't find any FTDI port") 
            return None  
        return self.ftdi_ports
    
    def open_ftdi_ports(self) -> list:
        # generate the empty list of opened serial ports
        serial_list = []
        # get a list of avaible ports connected to FTDIs
        ftdi_ports = tools().find_ftdi_ports()
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
