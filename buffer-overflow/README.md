# Instructions for buffer-overflow example.

# Original article.
https://samsclass.info/127/proj/lbuf1.htm

# Notes

$esp (the top of the stack)
$ebp (the bottom of the stack)


# GDB commands
info registers
x/40x $esp


# Testing Exploit 4 in gdb
gdb bo1
break 8
run $(cat e4)
info registers
x/40x $esp
