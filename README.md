# MINIGIN: DIG DUG
Reproduction of Dig Dug game using C++ and SDL for the programming 4 course 2018-2019

# ENGINE
The Minigin engine is build up using the following patterns

  -GameObject/Component

  -Observers/Subject

  -Concurrent Hierarchical State Machine

  -Commands

using the GameObject/Components all the elements of the game are build up, too create new type of game elements custom components can be created and attach to the objects similarly to how you can attach a script component to a object in Unity. The component are observers and subjects, allowing them to interface with othe component and game objects. Using Singletons the engine handels the data inside the scenes during the game and the between the switching of the scenes. There is some refractoring and decoupling that needs to done, mostly building the engine into a static libary.

# GAME
Gamemodes::

  -Single Player Mode

  -Coop Player Mode

  -VS Mode



Enemies::

  -Pooka

  -Fygar

  -Rock

Levels::
First two levels of Dig dug.

# CONTROLS
Supports Keyboard controls but only 1 controller

# Commad :: Keyboard :: Controller

UP::         up, w	          ::	directional pad up

DOWN::       down, s	        ::	directional pad down

LEFT::       left, a       	::	directional pad left 

RIGHT::      right, d	      ::	directional pad right

ATTACK::     Lshift,Rshift	  ::	A


# Menu

Exit::      esc

UP::        up

DOWN::      down

SELECT::    space