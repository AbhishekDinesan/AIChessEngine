#include <string>
#include <iostream>
#include <sstream>
#include "Gameplay/Game.h"
#include <memory>
#include "Gameplay/AbstractPlayer.h"
#include "Gameplay/Board.h"
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
        cin >> cmd;
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
                cin >> parameter;
                istringstream processParameter{parameter};
                getline(processParameter, playerType, '[');

                if (playerType == "computer")
                {
                    getline(processParameter, strCpuDifficulty, ']');
                    if (!isValidCpuInput(strCpuDifficulty))
                    {
                        cerr << "Invalid Input: \"" << strCpuDifficulty;
                        cerr << "\" is not a valid computer difficulty" << endl;

                        delete whitePlayer;
                        delete blackPlayer;

                        cin.ignore(int(2147483647), '\n');
                        break;
                    }
                    else
                    {
                        istringstream strToInt{strCpuDifficulty};
                        strToInt >> cpuDifficulty;
                    }

                    if (!isWhiteInit)
                    {
                        if (cpuDifficulty == 1)
                        {
                            // whitePlayer = new ComputerOne(true, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 2)
                        {
                            // whitePlayer = new ComputerTwo(true, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 3)
                        {
                            // whitePlayer = new ComputerThree(true, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 4)
                        {
                            // whitePlayer = new ComputerFour(true, false, false, nullptr);
                        }
                        isWhiteInit = true;
                    }
                    else
                    {
                        if (cpuDifficulty == 1)
                        {
                            // blackPlayer = new ComputerOne(false, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 2)
                        {
                            // blackPlayer = new ComputerTwo(false, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 3)
                        {
                            // blackPlayer = new ComputerThree(false, false, false, nullptr);
                        }
                        else if (cpuDifficulty == 4)
                        {
                            // blackPlayer = new ComputerFour(false, false, false, nullptr);
                        }
                        isBlackInit = true;
                    }
                }
                else if (playerType == "human" && !isWhiteInit)
                {
                    whitePlayer = new Player(true, true, false, nullptr);
                    isWhiteInit = true;
                }
                else if (playerType == "human" && !isBlackInit)
                {
                    blackPlayer = new Player(false, true, false, nullptr);
                    isBlackInit = true;
                }
                else
                {
                    cerr << "Invalid Input: \"" << playerType;
                    cerr << "\" is not a valid player type" << endl;

                    delete whitePlayer;
                    delete blackPlayer;

                    cin.ignore(int(2147483647), '\n');
                    break;
                }

                if (isWhiteInit && isBlackInit)
                {
                    g = new Game(whitePlayer, blackPlayer, whiteStarts, validCustomBoard, customBoard);
                }
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
        else if (cmd == "setup")
        {
            if (!g)
            {
                cerr << "Invalid Input: Setup mode cannot be accessed while a game is in progress" << endl;
                cin.ignore(int(2147483647), '\n');
                continue;
            }

            else if (!validCustomBoard)
            {
                // delete customBoard;
                customBoard = new Board(true, false);
            }

            while (true)
            {
                string subCmd = "";
                string colour;
                char processChar = '\0';
                char piece = '\0';
                int file = -1;
                int rank = -1;

                cin >> subCmd;
                if (subCmd == "done")
                {
                    if (customBoard->isValid())
                    {
                        validCustomBoard = true;
                    }
                    else
                    {
                        customBoard = new Board(false, false);
                        validCustomBoard = false;
                    }

                    break;
                }
                else if (subCmd == "+")
                {
                    cin >> processChar;
                    if (!isValidPieceInput(processChar))
                    {
                        cerr << "Invalid Input: \"" << processChar;
                        cerr << "\" is not a valid piece identifier" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }
                    else
                        piece = processChar;

                    cin >> processChar;
                    if (!isValidFileInput(processChar))
                    {
                        cerr << "Invalid Input: \"" << processChar;
                        cerr << "\" is not a valid file" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }
                    else
                        file = processChar - 'a';

                    cin >> processChar;
                    if (!isValidRankInput(processChar))
                    {
                        cerr << "Invalid Input: \"" << processChar;
                        cerr << "\" is not a valid rank" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }
                    else
                        rank = abs((processChar - '1') - 7);

                    // PIECES BEING ADDED TO THE BOARD
                    customBoard->addPiece(file, rank, piece);
                    cout << *customBoard;
                }
                else if (subCmd == "-")
                {
                    cin >> processChar;
                    if (!isValidFileInput(processChar))
                    {
                        cerr << "Invalid Input: \"" << processChar;
                        cerr << "\" is not a valid file" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }
                    else
                        file = processChar - 'a';

                    cin >> processChar;
                    if (!isValidRankInput(processChar))
                    {
                        cerr << "Invalid Input: \"" << processChar;
                        cerr << "\" is not a valid rank" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }
                    else
                        rank = abs((processChar - '1') - 7);

                    customBoard->removePiece(file, rank);
                    cout << *customBoard;
                }
                else if (subCmd == "=")
                {
                    cin >> colour;
                    if (colour != "white" && colour != "black")
                    {
                        cerr << "Invalid Input: \"" << colour;
                        cerr << "\" is not a valid colour" << endl;
                        cin.ignore(int(2147483647), '\n');
                        continue;
                    }

                    if (colour == "white")
                    {
                        whiteStarts = true;
                    }
                    else if (colour == "black")
                    {
                        whiteStarts = false;
                    }
                    cout << colour << " player starts" << endl;
                }
                else
                {
                    cerr << "Invalid Input: \"" << subCmd;
                    cerr << "\" is not a valid command within the setup scope" << endl;
                    cin.ignore(int(2147483647), '\n');
                    continue;
                }
            }

            //
            // CHECK FOR VALID BOARD
            //

            //
            // **MAYBE** ADD FIELDS FOR EN PASSANT AND CASTLING RIGHTS
            //
        }
        else if (cmd == "quit")
        {
            // if (g) delete g;
            // if (customBoard) delete customBoard;
            // if (whitePlayer) delete whitePlayer;
            // if (blackPlayer) delete blackPlayer;
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