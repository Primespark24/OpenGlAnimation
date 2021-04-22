# Project 4 - Animation and Lighting
Whitworth University - CS-357 Computer Graphics  
Last edited: 4/22/2021 by Scott  

## Overview
Start pulling together our work in the fragment shader with more advanced vertex operations.

You are welcome (and encouraged) to use provided code, both from me and from sb7 source code. Always be clear about your citations.

As this is a 300 level course, I expect adherence to style and appropriate and complete commenting.

As always: you can do this assignment in whatever Graphics Language you like, but you need to approach the theme of the original assignment if not doing it in OpenGL.

## Grade

| Portion             | Points Possible |
|---------------------|-----------------|
| Model Creation      | 20              |
| Animation           | 20              |
| Lighting            | 20              |
| Extras              | 20              |
| Proof               | 20              |

Please only upload original code and documentation! I don't want to see whole libraries uploaded or zip files unrelated to what you did. You should use a good `.gitignore` file, if you don't know what that is, let me know and I can show you.

## Part 1: Model Creation
You are going to need to generate a model for the animation part. These models need to have texture components with them as well. Make sure you document this process (see Proof).

Don't go overboard (unless you want to). 

## Part 2: Animation
Animate your models, I would suggest using hierarchical modeling, but you are free to do whatever you like.

Your models needs to be at least three 'deep' on the hierarchy (so three levels of interaction) and have at least some interactions that are not 'just' one-to-one. In my example from class this would be like the pinchers (there are two that are mapped to one upper arm).

You do need to be more original than just copy/pasting my code. You need to have your own structure and relationships.

## Part 3: Dynamic Lighting 
You need to implement both texturing as well as some kind of fragment-based lighting. This could be Blinn-Phong, this could be environment mapping, this could be something else.

This lighting should be reactive in some way. Either the lighting source should be able to move, or the mapping needs to be able to change. 

## Part 4: Extras

Be creative! Add features!

This could be having two hierarchies interact with each other, this could be complex animation, this could be input mapping (look up "reverse kinematics" if you want to know how to go from mouse position to arm angles), interactions with the user, lighting paired with the animation (think Pixar lamp, it is a moving light source).

Like before: you are welcome to come talk to me to brainstorm.

## Part 5: Proof
Show and tell! Show off what you did!

Include:
* Screenshots of your models in whatever tool you used to make them
  * You should also probably at least upload the .obj or other files for your objects.
* Sketch/diagram of your animation layout (this can be digital or physical, I care more about layout than detail)
* Video or .gif recording of an interaction with your program. Show off the features!
