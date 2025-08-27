# MiniOS
Simple OS I'm making. Inspired and got the boot files from @mell-o-tron's OS-Reference and a bit of IO from his MellOs project.
Probably gonna change the name until it feels nice
## To run
do `sh run.sh` in linux to compile for changes.
If you don't have a cross compiler and don't want to make changes run `qemu-system-x86_64 -drive format=raw,file="bins/OS.bin",index=0,if=floppy, -m 128M`.
If it pops an error you need to download qemu with `sudo apt install qemu-system-x86_64`

# In progress:
Add/Make a filesystem<br/>
Make a window handler<br/>
API for application development<br/>

# Surely in the future:
Terminal<br/>
Calculator

# Possibly in the future:
Networking<br/>
Multithreading<br/>
3D renderer<br/>
Web browser<br/>
Full 1080p resolution instead of mode 13h with VESA VBE
