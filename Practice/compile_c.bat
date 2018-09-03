@echo off

set name=%1

cc65 -Oi %name%.c --add-source
ca65 %name%_reset.s
ca65 %name%.s

ld65 -C compile_extras\nes.cfg -o %name%.nes %name%_reset.o %name%.o compile_extras\nes.lib

del *.o

pause

%name%.nes
