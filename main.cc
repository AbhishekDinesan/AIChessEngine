#include <string>
#include <iostream>
#include <sstream>
#include "Gameplay/Game.h"
#include <memory>
#include "Gameplay/AbstractPlayer.h"
#include "Gameplay/Board.h"
#include "Gameplay/Computer.h"
// ADD INCLUDE STATEMENTS
using namespace std;

bool isValidCpuInput(string s)
{
    return (s >= "1" && s <= "4");
}

bool isValidFileInput(char c)
{
    return (c >= 'a' && c <= 'h');
}

bool isValidRankInput(char c)
{
    return (c >= '1' && c <= '8');
}

bool isValidPieceInput(char c)
{
    return (c == 'K' || c == 'k' || c == 'Q' || c == 'q' ||
            c == 'B' || c == 'b' || c == 'N' || c == 'n' ||
            c == 'R' || c == 'r' || c == 'P' || c == 'p');
}

int main()
{
    int whiteScore = 0;
    int blackScore = 0;
    Game *g;
    Board *customBoard;
    AbstractPlayer *whitePlayer;
    AbstractPlayer *blackPlayer;
    bool validCustomBoard = false;
    bool whiteStarts = true;
    string cmd;

    while (true)
    {
        std::cin >> cmd;
        if (cmd == "game")
        {
            string parameter = "";
            string playerType = "";
            string strCpuDifficulty = "";
            int cpuDifficulty = 0;
            bool isWhiteInit = false;
            bool isBlackInit = false;

            while (!isWhiteInit || !isBlackInit)
            {
                blackPlayer = new ComputerThree(false, false, false, nullptr);
                isBlackInit = true;
                whitePlayer = new Player(true, true, false, nullptr);
                isWhiteInit = true;
            }
            if (isWhiteInit && isBlackInit)
            {
                g = new Game(whitePlayer, blackPlayer, whiteStarts, validCustomBoard, customBoard);
            }
        }
        else if (cmd == "resign")
        {
            if (g->getCurrTurn() == true)
            {
                ++blackScore;
            }
            else
            {
                ++whiteScore;
            }
            string colour = (g->getCurrTurn()) ? "Black" : "White";
            cout << " resigned" << endl
                 << endl;
            cout << "Final Score:" << endl;
            cout << "White: " << whiteScore << endl;
            cout << "Black: " << blackScore << endl;
            delete g;
        }
        else if ((cmd == "move") && (g->getCurrPlayer()->getIsHuman() == true))
        {
            if (!g)
            {
                cerr << "Invalid Input: Moves cannot be made until a game has been started" << endl;
                cin.ignore(int(2147483647), '\n');
                continue;
            }

            char processChar = '0';
            int startFile = -1;
            int startRank = -1;
            int endFile = -1;
            int endRank = -1;
            bool reset = false;

            while (startFile == -1 || startRank == -1 || endFile == -1 || endRank == -1)
            {
                cin >> processChar;
                if (!isValidFileInput(processChar))
                {
                    cerr << "Invalid Input: \"" << processChar;
                    cerr << "\" is not a valid file" << endl;
                    cin.ignore(int(2147483647), '\n');
                    reset = true;
                    break;
                }
                else if (startFile == -1)
                    startFile = processChar - 'a';
                else
                    endFile = processChar - 'a';

                cin >> processChar;
                if (!isValidRankInput(processChar))
                {
                    cerr << "Invalid Input: \"" << processChar;
                    cerr << "\" is not a valid rank" << endl;
                    cin.ignore(int(2147483647), '\n');
                    reset = true;
                    break;
                }
                else if (startRank == -1)
                {
                    startRank = abs((processChar - '1') - 7);
                }
                else
                {
                    endRank = abs((processChar - '1') - 7);
                }
            }
            if (reset)
                continue;

            g->movePiece(startFile, startRank, endFile, endRank);
            g->printBoard();
            if (g->getGameOver() == true)
            {
                if (g->getCurrTurn() == true)
                {
                    ++blackScore;
                }
                else
                {
                    ++whiteScore;
                }
                cout << "Final Score:" << endl;
                cout << "White: " << whiteScore << endl;
                cout << "Black: " << blackScore << endl;
                validCustomBoard = false;
                delete g;
                // delete customBoard;
            }
        }
        else if ((cmd == "move") && (g->getCurrPlayer()->getIsHuman() == false))
        {
            g->getCurrPlayer()->makeMove(0, 0, 0, 0);
            g->printBoard();
            if (g->getGameOver() == true)
            {
                if (g->getCurrTurn() == true)
                {
                    ++blackScore;
                }
                else
                {
                    ++whiteScore;
                }
                cout << "Final Score:" << endl;
                cout << "White: " << whiteScore << endl;
                cout << "Black: " << blackScore << endl;
                validCustomBoard = false;
                delete g;
            }
        }
        else if (cmd == "quit")
        {
            break;
        }
        else
        {
            cerr << "Invalid Input: \"" << cmd;
            cerr << "\" is not a valid command" << endl;
            cin.ignore(int(2147483647), '\n');
            continue;
        }
    }
}