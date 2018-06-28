# Disassembly review
The purpose of this section is to build simple c and c++ application which can then be opened up
in IDA Pro for review.  It will demonstrate what various things look like under the hood from
C to disassembly.


# Notes

A useful way of determining the architecture of a binary.
readelf -h <program-name>


When looking at variables in a function, variables with a positive offset is a parameter to the function, where a variable with a negative offset is usually a local variable. This is of course not always the case but you can take it as a general rule of thumb.
