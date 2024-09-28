# Gomoku
Gomoku is a game resembling tic-tac-toe but on a larger, 15x15 board. The player's task is to place **exatcly** 5 of their stones in a straight line - vertically, horizontally or diagonally. The player who's first to do so wins. If none of the players manages to win there's a draw!

# Game

## Before you play
The interface of the program is in Polish. After launching the program make sure to **maximize the console window** and **press ENTER**, otherwise the graphical contents **won't display correctly**.

## App's interface
After launching the app you'll be taken to a main menu screen. Here you can choose 3 options:
* wyjdz (exit)
* zasady (rules)
* graj (play)
You can make your choice by typing it in the console, all in lowercase.

### Rules
In the **Rules** section you can read the rules of the game. The content of this tab is identical to the first header of this README file. To go back to main menu type in `wroc`.

### Playing the game
To start a new game type in `graj`. The game will start with your move. To make your move type in the ID of the slot you want to put your stone into. Correct input consists of an uppercase letter (A-O) immediately followed by a number(1-15). Here are some examples of specifying a move correctly:
```
A1
N13
J8
```
Here's a couple of **incorrect** ways to make a move:
```
a 1
13N
j8
```
After the game ends, there's a message on the screen:
* wygrana (you won)
* przegrana (you lose)
* remis (a draw)
After pressing any key on the keyboard, you'll be taken back to the main menu.

## Exiting the program
To exit the program, when in main menu type in `wyjdz`. The program will display a goodbye message. After pressing any key the program will officialy end, closing the console window.
