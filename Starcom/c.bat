path c:\sdcc\bin
@echo off
sdcc -mz80 -c --std-c99 --opt-code-speed charset.c
del charset.lst
del charset.sym
del charset.asm
sdcc -mz80 -c --std-c99 --opt-code-speed levels.c
del levels.lst
del levels.sym
del levels.asm
sdcc -mz80 -c --std-c99 --opt-code-speed main.c
del main.lst
del main.sym
del main.asm
sdasz80 -o music.rel music.s
sdasz80 -o splash0_dan0.rel splash0_dan0.s
sdasz80 -o splash1_dan0.rel splash1_dan0.s
sdasz80 -o splash2_dan0.rel splash2_dan0.s
sdcc -mz80 -c --std-c99 --opt-code-speed tiles.c
del tiles.lst
del tiles.sym
del tiles.asm
sdasz80 -o title_dan0.rel title_dan0.s
pause
