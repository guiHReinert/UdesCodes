 #!/bin/bash

odir=out

gcc robot_glut.c -lglut -lGL -lGLU -o $odir/robot_glut
./$odir/robot_glut

gcc snowman_glfw.c -lglfw -lGL -lGLU -lm -o $odir/snowman_glfw
./$odir/snowman_glfw

gcc snowman_glut.c -lglut -lGL -lGLU -lm -o $odir/snowman_glut
./$odir/snowman_glut

gcc snowman_sample.c -lglut -lGL -lGLU -lm -o $odir/snowman_sample
./$odir/snowman_sample

gcc snowman_sdl.c -lGL -lGLU -lSDL -lm -o $odir/snowman_sdl
./$odir/snowman_sdl


