# Chess Engine using Aritificial Intelligence

Playable Chess Engine using Minimax Search-Tree Algorithm &amp; Alpha-Beta Pruning

## How does this work?

There are four main components to this project
1. Building Chess
2. Evaluation
3. Minimax Search Tree
4. Optimization Strategies

## Building Chess

In a group, I was asked to build a functioning chess game for one of our CS courses. This would feature a "set-up" mode where you could add/drop pieces, player vs player chess games, and a very simple player vs computer game (no real intelligene, mostly generated random moves). Our group used object oriented software principles to develop the basic functionality of the chess board.

Since this project needed to be finished on a deadline, it was poorly constructed. A few months past the due date, I took apart the code, refactored it, and decided to focus solely on human vs computer games, and wanted to construct the hardest computer level I could.

## Evaluation

An important problem you face when developing an engine is evaluation of a given position. Essentially, what defines a favourable position on the chess board?
To compute this, I used these evaluation matrixes from this community,
https://www.chessprogramming.org/Simplified_Evaluation_Function

## What is Minimax?

![image](https://github.com/AbhishekDinesan/MinimaxChess/assets/69426715/0e773c63-f880-400a-a7f8-b597c21eb96c)

At its core, Minimax is a recursive algorithim that is designed to find optimal moves in a two player game. We are able to generate game trees and evaluate nodes using the eval() function described above, and maximize/minimize moves accordinly.

However, optimization strategies are necessary as it can only evaluate to a depth of n=4 in a reasonable time.

## Optimization Strategies

### What is Alpha-Beta Pruning?

Alpha-Beta Pruning is a method of pruning un-needed branches from the game's search tree. 
The idea is that the highest value, alpha, and a lowest value, beta. The condition alpha >= beta must hold.
By keeping track of both alpha/beta, we are able to eliminate potential branch searches before they even occur!

## Instructions on how to play

Deployment is work in progress..



