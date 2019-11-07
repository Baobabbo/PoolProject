# PoolProject

Real Time Project by Stefano Rossi and Riccardo Piccolo

Simulated Pool game where each ball is a preiodic task and where the user can decide direction and intensity of its throw using the mouse.

# Allegro Library

We have used Allegro (version 4) Library that is an open suource graphic library for games.
To install Allegro under Debian distributions execute this command from the terminal :
```
$sudo apt‐get install liballegro4.4 liballegro4.4‐dev 
```
<br/>For other Unix-like systems refer to:<br/>
- https://wiki.allegro.cc/index.php?title=Allegro_4#Download

# Other Library

- Pthread: https://www.gnu.org/software/hurd/libpthread.html
- Ptask: https://github.com/glipari/ptask

# How to Use

To compile and execute the program:
```
make
./main
```

To recompile the program:
```
make clean
make
```

# Description

- classic pool game, where the player has to pocket the balls
- 16 periodic tasks corresponding to each ball in the game
- if the ball with the number 8 is pocketed, the game finishes

# Graphical Layout

Main game screenshot:

![Pool Table Image](https://raw.githubusercontent.com/Baobabbo/PoolProject/master/img/readme/PoolScreen.PNG)


# User Interface/User Interaction

Mouse Input:
  - Mouse Movement: choose direction of the throw.
  - Left Click: freeze direction and go to power selection mode, if clicked a second time the throw is performed.
  - Right Click: if in power selection mode, go back to direction choice.
  
R: Restart game, available only after the ball number 8 has been pocketed.  
ESC: Quit application.

# Task Description

- BALLS:
  - Each periodic task updates his position before the screen gets refreshed.
  
- USER:
  - Aperiodic task that is executed only if all the balls on the pool table are stopped.
  - The task daws the stick and a trajectory according to the current mouse position.
  - It handles the power selection of the throw.
  
- GRAPHICS:
  - Periodic task that refreshes the screen. It re-draws the background and all the balls with their updated position.
  - This task also handles the collision of the balls, the table borders and the holes.
  
# Task Layout
  
# Collision Implementation


