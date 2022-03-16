import serial
from serial.tools import list_ports
import traceback

# ser = serial.Serial()
 
# ftdi_ports = []
# ports = list_ports.comports()
# for port in ports:
#     #if port.vid == 1027:
#         #ftdi_ports.append(port.device)
#     #print(port.vid)
#     #print(port.device)
#     #print(port.name)
#     #print(port.description)
#     #print(port.hwid)
#     #print(list(str(port.pid)))
#     print(list(str(port.serial_number)))
#     #print(port.product)
#     #print(port.interface)
# # print(f'Found {len(ftdi_ports)} FTDI ports')

# def __find_ftdi_ports():
#     ftdi_ports = []
#     ports = list_ports.comports()
#     for port in ports:
#         serial_num = str(port.serial_number)
#         if port.vid == 1027 and serial_num[0] == "F":   # add only FTDI devices 
#             ftdi_ports.append(port.device)                    
#     if ftdi_ports == []:
#         print("Couldn't find any FTDI port")            
#         return None
#     return ftdi_ports


try:
  ser_port = serial.Serial( # set parameters, in fact use your own :-)
    port="COM5",
    baudrate=9600,
    bytesize=serial.SEVENBITS,
    parity=serial.PARITY_EVEN,
    stopbits=serial.STOPBITS_ONE
  )
  ser_port.isOpen() # try to open port, if possible print message and proceed with 'while True:'
  print ("port is opened!")

except Exception:
    traceback.print_exc()

while True: 
    pass
    # do something...
            

    


