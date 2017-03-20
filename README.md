# 3D_Terrain_Generation
**Three-dimensional terrain generation using the diamond-square algorithm for heightmap generation and 
OpenGL with GLEW for rendering.**   
Created in June of 2016.

The initial purpose of this project was to create a set of classes for generating heightmaps. The Map class
provides the ability to generate terrain using an iterative implementation of the diamond-square algorithm.

The functions that handle the actual generation allow you to define the terrain's roughness/courseness and its level of detail 
(or polygon count).  Besides the basic functions that handle things such as capping the heightmap and cleaning it up, I've included
a function for smoothing the terrain using a mean/box filter.  

Initially I had the heightmaps rendering in 2D where the height values mapped to color values in an image,
but later I decided to make the Mesh class for rendering the heightmap in 3D. I've implemented
basic lighting and shaders, along with the ability to rotate and translate the terrain.  I've also decided to create my own math 
classes for dealing with matrixes and vectors.

Below are some screen shots obtained by tweaking the values in main.cpp, and using the uncommented lines in the shader files.

**Default values as seen in main:**
![alt tag](http://i.imgur.com/26EB0Kh.jpg)
![alt tag](http://i.imgur.com/bxUosov.jpg)

**Increasing passes of smooth filter and its size:**
![alt tag](http://i.imgur.com/ruzV7iD.jpg)
![alt tag](http://i.imgur.com/zBWACu1.jpg)
![alt tag](http://i.imgur.com/hyRevyJ.jpg)

**Changing the roughness:**
![alt tag](http://i.imgur.com/GeAj6PZ.jpg)

Changing the level of detail (mapsize value in main):
![alt tag](http://i.imgur.com/UW1peQ3.jpg)
![alt tag](http://i.imgur.com/ydKujWf.jpg)

**Messing around with commented lines in the fragshader:**
![alt tag](http://i.imgur.com/1uN46Rg.jpg)
![alt tag](http://i.imgur.com/7t1jZax.jpg)
![alt tag](http://i.imgur.com/ZAYN6tq.jpg)
![alt tag](http://i.imgur.com/HCRmDOh.jpg)
![alt tag](http://i.imgur.com/IBryzHQ.jpg)
![alt tag](http://i.imgur.com/5FQPebt.jpg)

The imgur album can be viewed here: http://imgur.com/a/VaVkM
