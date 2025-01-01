Connect 4 AI with Alpha-Beta Pruning

Overview

This project is an implementation of the classic Connect 4 game, enhanced with an AI opponent powered by the minimax algorithm and alpha-beta pruning. The AI intelligently evaluates moves to provide a challenging opponent at multiple difficulty levels. The project is implemented entirely in C++ and runs in a text-based environment.

Features

AI Opponent: The AI uses the minimax algorithm with alpha-beta pruning to evaluate optimal moves.

Dynamic Difficulty: Choose from four difficulty levels:

Easy: Depth 2

Medium: Depth 4

Hard: Depth 6

Impossible: Depth 8

Win Detection: Supports horizontal, vertical, and diagonal win conditions.

Text-Based Interface: Simple and intuitive gameplay in the console.

How It Works

Algorithms Used

Minimax Algorithm: Evaluates all possible moves up to a given depth and selects the best move for the AI.

Alpha-Beta Pruning: Optimizes the minimax algorithm by reducing the number of nodes evaluated, improving computational efficiency.

Heuristic Evaluation: Scores board states based on patterns, central column control, and potential winning opportunities.

Key Gameplay Logic

The player and AI take turns dropping pieces into a 7x6 grid.

The AI evaluates the game state using a scoring system and selects moves accordingly.

The game ends when a player achieves a 4-in-a-row or the board is completely filled.

Getting Started

Prerequisites

A C++ compiler (e.g., GCC, Clang, or MSVC)

A terminal or IDE to compile and run the program

Installation

Clone this repository to your local machine:

git clone <repository-url>

Navigate to the project directory:

cd connect4-ai

Compile the program:

g++ connect.cpp -o connect4

Run the program:

./connect4

How to Play

Select the difficulty level (1: Easy, 2: Medium, 3: Hard, 4: Impossible).

The game alternates turns between the player and the AI.

To make a move, enter the column number (0-6) where you want to drop your piece.

The game announces the winner or declares a draw when no moves are left.

Code Structure

main(): Handles the game loop and user input.

checkWin(): Detects winning conditions.

minimax(): Implements the minimax algorithm with alpha-beta pruning.

evaluateBoard(): Heuristically evaluates the board state.

printBoard(): Displays the game board.
