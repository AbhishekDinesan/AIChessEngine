#include <string>
#include <iostream>
#include <sstream>
#include "Game.h"
#include <memory>
#include "AbstractComputer.h"
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
    unique_ptr<Game> g;
    Board *customBoard;
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
                        //
                        //  DELETE EXISTING PLAYERS
                        //
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
                            // ComputerOne();
                        }
                        else if (cpuDifficulty == 2)
                        {
                        }
                        else if (cpuDifficulty == 3)
                        {
                        }
                        else if (cpuDifficulty == 4)
                        {
                        }
                        //
                        // INITIALIZE WHITE PLAYER AS COMPUTER
                        //
                        cout << "WHITE = COMPUTER" << cpuDifficulty << endl;
                        isWhiteInit = true;
                    }
                    else
                    {
                        //
                        // INITIALIZE BLACK PLAYER AS COMPUTER
                        //
                        cout << "BLACK = COMPUTER" << cpuDifficulty << endl;
                        isBlackInit = true;
                    }
                }
                else if (playerType == "human" && !isWhiteInit)
                {
                    //
                    // INITIALIZE WHITE PLAYER AS HUMAN
                    //
                    cout << "WHITE = HUMAN" << endl;
                    isWhiteInit = true;
                }
                else if (playerType == "human" && !isBlackInit)
                {
                    //
                    // INITIALIZE BLACK PLAYER AS HUMAN
                    //
                    cout << "BLACK = HUMAN" << endl;
                    isBlackInit = true;
                }
                else
                {
                    cerr << "Invalid Input: \"" << playerType;
                    cerr << "\" is not a valid player type" << endl;
                    //
                    //  DELETE EXISTING PLAYERS
                    //
                    cin.ignore(int(2147483647), '\n');
                    break;
                }

                if (isWhiteInit && isBlackInit)
                {
                    g = make_unique<Game>(whiteStarts, validCustomBoard, customBoard);
                }
            }
        }
        else if (cmd == "resign")
        {
            //
            // RESIGN
            //
            cout << "Resigned" << endl;
        }
        else if (cmd == "move")
        {
            if (!g)
            {
                cerr << "Invalid Input: Moves cannot be made until a game has been started" << endl;
                cin.ignore(int(2147483647), '\n');
                continue;
                ;
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
                    cout << "SR: " << startRank << endl;
                }
                else
                {
                    endRank = abs((processChar - '1') - 7);
                    cout << (processChar - '1') << endl;
                    cout << "ER: " << endRank << endl;
                }
            }
            if (reset)
                continue;

            cout << "(1)" << endl;
            g->movePiece(startFile, startRank, endFile, endRank);
            g->printBoard();

            cout << "From: (" << startFile << "," << startRank << ")" << endl;
            cout << "To: (" << endFile << "," << endRank << ")" << endl;
        }
        else if (cmd == "setup")
        {
            if (g != nullptr)
            {
                cerr << "Invalid Input: Setup mode cannot be accessed while a game is in progress" << endl;
                cin.ignore(int(2147483647), '\n');
                continue;
            }
            else if (!validCustomBoard)
            {
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
                    validCustomBoard = true;

                    /* THIS IS WHAT IT WILL BE LATER, BUT LEAVE IT COMMENTED FOR TESTING
                    if (customBoard->isValid()) {
                        validCustomBoard = true;
                    } else {
                        customBoard = new Board(false);
                        validCustomBoard = false;
                    }
                    */

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

                    // cout << piece << " added at (" << file << "," << rank << ")" << endl;
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
                    cout << "piece removed from (" << file << "," << rank << ")" << endl;
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
                    cout << colour << " player's turn" << endl;
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
        else if (cmd == "undo")
        {
            //
            // UNDO PREVIOUS MOVE
            //
            cout << "Move Undid" << endl;
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