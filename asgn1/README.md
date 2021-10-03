#James Gu
#jjgu
#Fall 2021
#Assignment 1: Pass the Pigs

##DESCRIPTION OF PROGRAM:
This program is a simulation of the game David Moffat's dice game, Pass the Pigs. This game is played between 2 and 10 players and the players take turns rolling a pig.The pig can land on 5 different sides: Side, Razorback, Trotter, Snouter, and Jowler. If the player rolls side they pass their turn to the next player. All the other sides give a range of points. Razorback and Trotter yield 10 points, Snouter yields 15 points, and Jowler yields 5 points. Side, and Jowler each have a 2/7 chance of happening and Razorback, Trotter, and Snouter each have a 1/7 chance of happening. First player to 100 points or more wins the game.

###BUILD OF THE PROGRAM:
This program needs the following: pig.c, names.h, Makefile, README.md, and DESIGN.pdf. 

pig.c:
This contains the implementation of the simulaiton for Pass the Pigs.

names.h:
This contains the array of player names to be used in this simulation.

Makefile:
The file that directs program compilation, building the program pig from pig.c.

README.md:
Describes program, how to use program and how to build program.

DESIGN.pdf:
Describes the design and design process of the program with enough detail that another programmer can recreate the implementation.


####HOW TO RUN THE PROGRAM:
pig.c is a simulation of the Pass the Pigs game so users will have to input the number of players they want in the game (an integer between 2 and 10 inclusive). After that the user must select the random seed they would like the game to be played under (a positive integer). If the user submits inputs that aren't allowed there will be automati values assigned. Number of players will default to 2 and the seed will default to 2021. After that the program will simulate a game of Pass the Pigs.
