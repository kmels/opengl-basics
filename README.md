Description
-----------
An opengl + glut application that performs the following transformations to a polygon in 3D:
 + scaling
 + rotate
 + translation

Dependencies
------------
 + Glut
 + OpenGL
 + libsdl1.2-dev 

How to compile and run
----------------------
	make
	./opengl-basics

How to use
----------------------
 + Move camera
   + With the keypad:
     + '8' - moves camera up
     + '2' - moves camera down
     + '5' - zooms camera
     + '0' - unzoom camera
     + '4' - moves camera to left
     + '6' - moves camera to right
 + Translating
   + P sets translating unit to positive (0.5 units)
   + P sets translating unit to negative (-0.5 units)
   + CTRL + Y, translates in Y
   + CTRL + X, translates in X
   + CTRL + Z, translates in Z
 + Rotating
   + P sets rotating unit to positive (0.02 units)
   + P sets rotating unit to negative (-0.02 units)
   + ALT + Y, rotates in Y axis
   + ALT + X, rotates in X axis
   + ALT + Z, rotates in Z axis
 + Scaling
   + P sets scaling unit to positive (0.02 units)
   + P sets scaling unit to negative (-0.02 units)
   + SHIFT + Y, scales in Y axis
   + SHIFT + X, scales in X axis
   + SHIFT + Z, scales in Z axis
 + Increasing and decreasing transformation unit size
   + '+' increases transformation unit by 100% of the base unit (0.5 in case of translating, 0.02 in rotating and scaling)
   + '-' decreases transformation unit by 100% of the base unit (0.5 in case of translating, 0.02 in rotating and scaling)

