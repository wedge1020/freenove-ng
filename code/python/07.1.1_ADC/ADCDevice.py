#!/usr/bin/env python3
#############################################################################################
# Filename    : ADCDevice.py
# Description : Freenove ADC Module library.
# Author      : www.freenove.com
# modification: 2023/05/11
#############################################################################################

#############################################################################################
##
## import the smbus library
##
import smbus

#############################################################################################
##
## for storing ADCDevice values
##
class ADCDevice(object):

    #########################################################################################
    ##
    ## initializes the attributes of the class
    ##
    def __init__(self):
        self.cmd = 0
        self.address = 0
        self.bus=smbus.SMBus(1)
        # print("ADCDevice init")
        
    #########################################################################################
    ##
    ## detects the device in the provided address
    ##
    def detectI2C(self,addr):
        
        #####################################################################################
        ##
        ## detects the device and displays a conformation message
        ##
        try:
            self.bus.write_byte(addr,0)
            print("Found device in address 0x%x"%(addr))
            return True
            
        #####################################################################################
        ##
        ## displays this message if no device is found
        ##
        except:
            print("Not found device in address 0x%x"%(addr))
            return False
           
    def close(self):
        
        #####################################################################################
        ##
        ## close the connection to the bus pin
        ## 
        self.bus.close()

#############################################################################################
##
## for storing the values for the ADS7830 ADC Module
##        
class PCF8591(ADCDevice):

    #########################################################################################
    ##
    ## initializes the attributes of the class
    ##
    def __init__(self):
        super(PCF8591, self).__init__()
        self.cmd = 0x40     # The default command for PCF8591 is 0x40.
        self.address = 0x48 # 0x48 is the default i2c address for PCF8591 Module.
     
    #########################################################################################
    ##
    ## returns the ADC value from the specified address, command, and pins
    ##   
    def analogRead(self, chn): # PCF8591 has 4 ADC input pins, chn:0,1,2,3
        value = self.bus.read_byte_data(self.address, self.cmd+chn)
        value = self.bus.read_byte_data(self.address, self.cmd+chn)
        return value
    
#############################################################################################
##
## for storing the values for the ADS7830 ADC Module
##
class ADS7830(ADCDevice):

    #########################################################################################
    ##
    ## initializes the attributes of the class
    ##
    def __init__(self):
        super(ADS7830, self).__init__()
        self.cmd = 0x84
        self.address = 0x4b # 0x4b is the default i2c address for ADS7830 Module.   
    
    #########################################################################################
    ##
    ## returns the ADC value from the specified address, command, and pins
    ##    
    def analogRead(self, chn): # ADS7830 has 8 ADC input pins, chn:0,1,2,3,4,5,6,7
        value = self.bus.read_byte_data(self.address, self.cmd|(((chn<<2 | chn>>1)&0x07)<<4))
        return value
