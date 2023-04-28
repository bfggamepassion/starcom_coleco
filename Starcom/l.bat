path c:\sdcc\bin
@echo off
sdcc -mz80 --code-loc 0x8048 --data-loc 0x7000 --no-std-crt0 ../crtcv.rel ../comp.lib ../cvlib.lib ../getput.lib charset.rel levels.rel main.rel music.rel splash0_dan0.rel splash1_dan0.rel splash2_dan0.rel tiles.rel title_dan0.rel
objcopy --input-target=ihex --output-target=binary crtcv.ihx result.rom
del *.ihx
del *.rel
del crtcv.lnk
pause
