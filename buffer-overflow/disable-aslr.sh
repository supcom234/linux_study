#!/bin/bash
: '
This scripts disables ASLR protection.  For more details on what this is,
run "man proc" and serach for randomize_va_space Before running this, run make 
and run ./esp.  Then run this script and rerun ./esp to see the 
difference.
'
echo 0 > /proc/sys/kernel/randomize_va_space
