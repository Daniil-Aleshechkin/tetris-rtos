# Introduction

Tetris is a modern implemenation of the Tetris game which runs the game on embedded hardware along with all the modern features including: 
- a five piece queue
- a hold piece
- the SRS rotation system
- the DAS (Delayed auto shift) movement mechanics

This project extends this functionality providing more possible ways of interacting including an LED matrix display and a keyboard input

# Requirements
The project shall:
- Display the tetris board state in a LED matrix. It must:
    - Show what the hold piece is
    - Show where the current piece is
    - Show a shadow where the current piece will be placed
    - Show the next 5 pieces 
    - Show the full tetris board

The project should do one of the following:
- Display the board data from a bluetooth input
- Get the user input from a bluetooth
- Get the user input from a PS/2 Keybaord

