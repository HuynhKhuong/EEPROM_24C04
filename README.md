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
+ The layout must be agreed and preconfigured between master and slave

e.g: 

**old format**
|Byte 0|Byte 1|Byte 2|Byte 3:5|Byte 6|Byte 7:262|Byte 263|
|---|---|---|---|---|---|---|
|W: Write/R:Read|Byte Write/Read,Block Write/Read|'A'|Address|'D'|Data|endofframe(*)|

**new format**
|Byte 0|Byte 1|Byte 2|Byte 3:5|Byte 6:261|Byte 262|
|---|---|---|---|---|---|---|
|Write/Read|Byte Write/Read,Block Write/Read|DLC (includes Address & Data bytes)|Address|Data|endofframe(*)|

From the proposed layout, 2 messages would be built between slave and master:
- Message for Block operation
- Message for Byte operation
- Signal monitoring would be added to enhance E2E protection beside DLC check

