# Test Methods

## Introduction

The test methods outlined below are designed to rigorously validate the functionality and performance of the Tetris project. This project integrates modern Tetris game mechanics and display methods on embedded hardware, utilizing an LED matrix for visualization and offering various input methods including Bluetooth and a PS/2 keyboard. The tests are categorized into hardware performance, current draw measurements, and functionality.

## Hardware Performance Tests

### ADALM

- **Objective**: Ensure the LED matrix display refresh rate is below 50ms to maintain a smooth visual experience.
- **Method**: Use the ADALM (Analog Devices Active Learning Module) to measure the period of the display frequency. A complete refresh is indicated by 16 signals of the LAT (latch) pin. The refresh rate is calculated by measuring the time taken for these 16 signals to occur.
- **Pass Criteria**: The measured refresh rate must be less than 50ms.

### Multimeter Current Draw

- **Objective**: Measure the current draw of the LED matrix display to ensure it meets power consumption requirements.
- **Method**: Connect a multimeter in series with the power supply of the LED matrix display. Measure the current while the Tetris game is active and displaying various states (e.g., game in progress, displaying next pieces, etc.).
- **Pass Criteria**: The current draw should be within the specified limits for the hardware used, ensuring efficient power use and preventing overheating.

## Functionality Tests

### Terminal Application

- **Objective**: Verify that the Tetris board updates correctly after each type of input, ensuring that the game mechanics are implemented accurately.
- **Method**: Use a terminal application to simulate each of the following user inputs and observe the changes on the LED matrix display.
    - **D (Hard Drop)**: The current piece should immediately be placed at the location indicated by the ghost piece.
    - **W (270 Rotate)**: The current piece should rotate 270 degrees clockwise. Perform kick tests to ensure the piece moves correctly when rotation would otherwise cause overlap.
    - **Q (180 Rotate)**: The current piece should rotate 180 degrees. Test for correct piece movement considering kicks.
    - **R (Reset Board)**: The game board should reset, clearing all pieces.
    - **Tab (Hold Piece)**: The current piece should be held, swapping with the previously held piece if applicable.
    - **Arrow Right (Move Right)**: The current piece should move one tile to the right. Test for continuous movement when the key is held.
    - **Arrow Left (Move Left)**: The current piece should move one tile to the left. Test for continuous movement when the key is held.
    - **Arrow Up (Rotate 90)**: The current piece should rotate 90 degrees clockwise. Test for kicks to ensure correct movement.
    - **Arrow Down (Soft Drop)**: The current piece should move downwards towards the ghost piece's position without being placed.
    - **P (Exit to CLI)**: The board display should be replaced with the CLI interface.
- **Pass Criteria**: The LED matrix display must correctly reflect the game state after each input, with all functionalities working as described.
