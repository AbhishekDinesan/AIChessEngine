# Chess Engine

This Chess Engine is a playable command-line application built using C++. It uses the Minimax Search Tree Algorithm with Alpha-Beta Pruning to simulate intelligent gameplay, offering various difficulty levels for player vs. computer matches.

## Features

- Set-up mode: Allows users to place pieces in arbitrary positions, simulating real-game scenarios.

- Player vs. Player: Two human players can play against each other.

- Player vs. Computer: Play against the engine, with adjustable difficulty levels.

## How does this work?

There are four main components to this project
1. Standard Chess
2. Evaluation
3. Minimax Search Tree
4. Further Optimization Strategies

## Standard Chess

This project follows Object Oriented Programming principles to develop a CLI Chess Engine with C++.
So yes, literally everything has a class (Board, Game, Pieces, etc.).

Within my group, I focused on the player vs computer interactions, particularly developing varying difficulties of computer intelligence and simulating "intelligence".

## Evaluation

An important problem you face when developing an engine is evaluation of a given position. Essentially, what defines a favourable position on the chess board?
To compute this, I used these evaluation matrices from this community forum,
https://www.chessprogramming.org/Simplified_Evaluation_Function.

These matrices were used in a formula that computed the relative strength of the board for a given player, at a given time. It should be noted that this approach fails to recognize nuance in developed positions, but does work okay generally.

## What is Minimax?

At its core, Minimax is a recursive algorithim that is designed to find optimal moves in a two player game. We are able to generate game trees and evaluate nodes using the eval() function described above, and maximize/minimize moves accordingly.

How Minimax Works:
- Generate Game Tree: Simulates all possible moves up to a certain depth.
- Evaluate Leaf Nodes: Uses the evaluation function to assign scores.
- Maximize/Minimize: Alternates between maximizing the player’s advantage and minimizing the opponent’s advantage.

However, optimization strategies are necessary as it can only evaluate to a depth of n=4 in a reasonable time.

## Optimization Strategies

Alpha-Beta Pruning is a search algorithm enhancement that eliminates unnecessary nodes in the game tree, significantly reducing computation time.
- Alpha: The best score achievable by the maximizing player.
- Beta: The best score achievable by the minimizing player.
- By maintaining these value, we skip branches that cannot improve the result for either player.

## Gameplay

The graphics for this project were devleoped with XWindows Graphics on a university Linux system. Due to incompatibility issues, they were removed from this repo. Thus, this app is a CLI Application.

Note that the app is compiled with G++, v17.





