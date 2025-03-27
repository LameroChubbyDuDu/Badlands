# Badland RS485 Communication
### MASTER
- The master sends out two messages to the buffer in each loop: the slave number and the led_case.
- The master rod only activates only when all the slave rods are being touched.
### SLAVE
There are **three cases** for the slave rod, which are:
- LED_off
- LED_on(independent)
- LED_on(all light up)

### EEPROM
The slave number will be stored in the ProMini board so that we don't need to keep modifying the slave number when programming the slave board.
