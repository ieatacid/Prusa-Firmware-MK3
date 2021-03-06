# Differences from default Prusa MK3 firmware
   * Adds `M951` m code which lets one set the machine Live Z via serial terminal or slicer gcode. 
      * `M951` with no parameters will display the current Live Z offset in the serial terminal
      * `M951 Z-0.550` will change your Live Z to -0.550
      * `M951 Z-0.05 R` will move your Live Z -0.05mm *relative* to your current Live Z (Z-0.550 will become Z-0.600). `M951 Z0.05 R` will *add* 0.05mm to your Live Z (Z-0.550 will become Z-0.500)
      
      With Slic3rPE you can do something like this to have different Live Z values for different filament types:
      
          {if filament_notes[0] =~ /.*PETG.*/}
          M951 Z-0.690 ; Z offset for PETG
          {elsif filament_notes[0] =~ /.*PLA.*/}
          M951 Z-0.740 ; Z offset for PLA
          {endif}
          
      Will Pargeter on Facebook had a good idea for using relative mode:  Set your Live Z in start gcode then revert in the end gcode, like this:
      
          /* Start gcode */
          {if filament_notes[0] =~ /.*PETG.*/}
          M951 Z-0.050 R ; Z offset for PETG
          {endif}
          
          /* End gcode */
          {if filament_notes[0] =~ /.*PETG.*/}
          M951 Z0.050 R ; Z offset for PETG
          {endif}



# 1. Development environment preparation

   1. install `"Arduino Software IDE"` for your preferred operating system  
`https://www.arduino.cc -> Software->Downloads`  
it is strongly recommended to use older version `"1.6.9"`, by which we can assure correct compilation results  
_note: in versions `1.7.x` and `1.8.x` there are known some C/C++ compilator disasters, which disallow correct source code compilation (you can obtain `"... internal compiler error: in extract_insn, at ..."` error message, for example); we are not able to affect this situation afraid_  
_note: in the case of persistent compilation problems, check the version of the currently used C/C++ compiler (GCC) - should be `4.8.1`; version can be verified by entering the command  
`avr-gcc --version`  
if you are not sure where the file is placed (depends on how `"Arduino Software IDE"` was installed), you can use the search feature within the file system_  
_note: name collision for `"LiquidCrystal"` library known from previous versions is now obsolete (so there is no need to delete or rename original file/-s)_

   2. add (`UltiMachine`) `RAMBo` board into the list of Arduino target boards  
`File->Preferences->Settings`  
into text field `"Additional Boards Manager URLs"`  
type location  
`"https://raw.githubusercontent.com/ultimachine/ArduinoAddons/master/package_ultimachine_index.json"`  
or you can 'manually' modify the item  
`"boardsmanager.additional.urls=....."`  
at the file `"preferences.txt"` (this parameter allows you to write a comma-separated list of addresses)  
_note: you can find location of this file on your disk by following way:  
`File->Preferences->Settings`  (`"More preferences can be edited in file ..."`)_  
than do it  
`Tools->Board->BoardsManager`  
from viewed list select an item `"RAMBo"` (will probably be labeled as `"RepRap Arduino-compatible Mother Board (RAMBo) by UltiMachine"`  
_note: select this item for any variant of board used in printers `'Prusa i3 MKx'`, that is for `RAMBo-mini x.y` and `EINSy x.y` to_  
'clicking' the item will display the installation button; select choice `"1.0.1"` from the list(last known version as of the date of issue of this document)  
_(after installation, the item is labeled as `"INSTALLED"` and can then be used for target board selection)_  

   3. modify platform.txt to enable float printf support:
   `"compiler.c.elf.flags=-w -Os -Wl,-u,vfprintf -lprintf_flt -lm -Wl,--gc-sections"`

# 2. Source code compilation

place the source codes corresponding to your printer model obtained from the repository into the selected directory on your disk  
`https://github.com/prusa3d/Prusa-Firmware/`  
in the subdirectory `"Firmware/variants/"` select the configuration file (`.h`) corresponding to your printer model, make copy named `"Configuration_prusa.h"` (or make simple renaming) and copy them into `"Firmware/"` directory  

run `"Arduino IDE"`; select the file `"Firmware.ino"` from the subdirectory `"Firmware/"` at the location, where you placed the source codes  
`File->Open`  
make the desired code customizations; **all changes are on your own risk!**  

select the target board `"RAMBo"`  
`Tools->Board->RAMBo`  
_note: it is not possible to use any of the variants `"Arduino Mega …"`, even though it is the same MCU_  

run the compilation  
`Sketch->Verify/Compile`  

upload the result code into the connected printer  
`Sketch->Upload`  

or you can also save the output code to the file (in so called `HEX`-format) `"Firmware.ino.rambo.hex"`:  
`Sketch->ExportCompiledBinary`  
and then upload it to the printer using the program `"FirmwareUpdater"`  
_note: this file is created in the directory `"Firmware/"`_  

# 3. Automated tests
## Prerequisites
c++11 compiler e.g. g++ 6.3.1

cmake

build system - ninja or gnu make

## Building
Create folder where you want to build tests.

Example:

`cd ..`

`mkdir Prusa-Firmware-test`

Generate build scripts in target folder.

Example:

`cd Prusa-Firmware-test`

`cmake -G "Eclipse CDT4 - Ninja" ../Prusa-Firmware`

or for DEBUG build:

`cmake -G "Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug ../Prusa-Firmware`

Build it.

Example:

`ninja`

## Runing
`./tests`
