# EEPROM_24C04

## Record of changes

1. Reformat message layout between STM32 (slave) and PC (master)
Reformat points: 
+ Address field is considered as a signal in PDU layout (would contain: start bit, bit length, and byte order rule)
+ Data  field  is considered as a signal in PDU layout (woud contain: start bit, byte order rule)
+ Create a Value Table for Byte 0 (Mode: Write/Read)
+ Create a Value Table for Byte 1 (Mode: Byte/Block)
+ Remove Byte 2 (Indicator for Address field): as signal attributes cover this indicator field
+ Remove Byte 6 (Indicator for Data field): as signal attributes cover this indicator field
+ Add DLC Field (Data length code) 

The layout must be agreed and preconfigured between master and slave

