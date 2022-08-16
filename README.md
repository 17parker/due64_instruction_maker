A helper program, designed to make controller data for an N64 controller

This makes controller instructions for the "due64" project (https://github.com/17parker/due64). It takes what buttons are pressed, and the analog stick's angle and magnitude, and prints out a 4-byte hex number to copy/paste. 

For example, if you pressed the buttons "A", "B", and "Z", held the analog stick at 45 degrees at "half strength", and you wanted to repeat that for 3 frames, it would print out:

**{ 0x84840007, 3 }**
