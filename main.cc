#include <string>
#include <iostream>
#include <sstream>
// ADD INCLUDE STATEMENTS
using namespace std;
const int MAX_DIFFICULTY = 5;

int main()
{
    string cmd;
    while (true)
    {
        cin >> cmd;

        // GAME
        if (cmd == "game")
        {
            cout << "testing" << endl;
            string input = "";
            string playerType = "";
            string strCpuDifficulty;
            int cpuDifficulty = 0;
            bool isWhiteInit = false;
            bool isBlackInit = false;

            while (!isWhiteInit || !isBlackInit)
            {

                getline(cin, playerType, '[');

                if (playerType == "computer")
                {

                    getline(cin, strCpuDifficulty, ']');
                    // CONVERT STRING TO INT AND STORE IT

                    if (cpuDifficulty > MAX_DIFFICULTY || cpuDifficulty < 0)
                    {
                        if (!isWhiteInit)
                            cerr << "Invalid White Player Computer Difficulty" << endl;
                        else
                            cerr << "Invalid Black Player Computer Difficulty" << endl;
                        break;
                    }

                    if (!isWhiteInit)
                    {
                        //
                        // IMPLEMENT WHITE PLAYER INITIALIZATION AS A COMPUTER
                        // WITH cpuDifficulty DIFFICULTY
                        //
                        isWhiteInit = true;
                    }
                    else
                    {
                        //
                        // IMPLEMENT BLACK PLAYER INITIALIZATION AS A COMPUTER
                        // WITH cpuDifficulty DIFFICULTY
                        //
                        isBlackInit = true;
                    }
                    cin.ignore(); // removes the "]" from the input
                }
                else if (playerType == "human")
                {
                    if (!isWhiteInit)
                    {
                        //
                        // IMPLEMENT WHITE PLAYER INITIALIZATION AS A HUMAN
                        //
                        isWhiteInit = true;
                    }
                    else
                    {
                        //
                        // IMPLEMENT BLACK PLAYER INITIALIZATION AS A HUMAN
                        //
                        isBlackInit = true;
                    }
                }
                else
                {
                    if (!isWhiteInit)
                        cerr << "Invalid White Player Type" << endl;
                    else
                        cerr << "Invalid Black Player Type" << endl;
                }
            }
        }

        // RESIGN
        else if (cmd == "resign")
        {
            //
            // IMPLEMENT RESIGNATION
            //
        }

        // MOVE
        else if (cmd == "move")
        {
            char startFile = 'a';
            int startRank = 1;
            char endFile = 'h';
            int endRank = 8;
            bool validSquares = true;

            if (startFile < 'a' || startFile > 'h')
            {
                cerr << "Invalid Starting File" << endl;
                validSquares = false;
            }

            if (startRank < 1 || startRank > 8)
            {
                cerr << "Invalid Starting Rank" << endl;
                validSquares = false;
            }

            if (endFile < 'a' || startFile > 'h')
            {
                cerr << "Invalid Ending File" << endl;
                validSquares = false;
            }

            if (endRank < 1 || startRank > 8)
            {
                cerr << "Invalid Ending Rank" << endl;
                validSquares = false;
            }

            if (validSquares)
            {
                //
                // IMPLEMENT THE MOVE
                //
            }
        }

        // SETUP
        else if (cmd == "setup")
        {
            //
            // IMPLEMENT LOGIC CHECKING IF A GAME IS CURRENTLY RUNNING
            //
            while (true)
            {
                string oper;
                string colour;
                char piece = 'K';
                char file = 'a';
                int rank = 1;

                cin >> oper;
                if (oper == "done")
                {
                    break;
                }
                else if (oper == "+")
                {
                    cin >> piece;
                    if (piece != 'K' && piece != 'k' &&
                        piece != 'Q' && piece != 'q' &&
                        piece != 'B' && piece != 'b' &&
                        piece != 'N' && piece != 'n' &&
                        piece != 'R' && piece != 'r' &&
                        piece != 'P' && piece != 'p')
                    {
                        cerr << "Invalid Piece" << endl;
                        cin.clear();
                        continue;
                    }

                    cin >> file;
                    if (file < 'a' || file > 'h')
                    {
                        cerr << "Invalid File" << endl;
                        cin.clear();
                        continue;
                    }

                    cin >> rank;
                    if (rank < 1 || rank > 8)
                    {
                        cerr << "Invalid Rank" << endl;
                        cin.clear();
                        continue;
                    }

                    //
                    // IMPLEMENT THE ADDITION OF A PIECE TO THE BOARD
                    //
                }
                else if (oper == "-")
                {

                    cin >> file;
                    if (file < 'a' || file > 'h')
                    {
                        cerr << "Invalid File" << endl;
                        cin.clear();
                        continue;
                    }

                    cin >> rank;
                    if (rank < 1 || rank > 8)
                    {
                        cerr << "Invalid Rank" << endl;
                        cin.clear();
                        continue;
                    }

                    //
                    // IMPLEMENT THE REMOVAL OF A PIECE FROM THE BOARD
                    //
                }
                else if (oper == "=")
                {
                    cin >> colour;
                    if (colour != "white" && colour != "black")
                    {
                        cerr << "Invalid Piece" << endl;
                        cin.clear();
                        continue;
                    }

                    //
                    // SET THE INDICATED PLAYERS TURN
                    //
                }
            }
            //
            // CHECK FOR A VALID BOARD
            //

            //
            // **MAYBE** ADD THINGS TO INDICATE THE ALLOWANCE OF CASTLING AND EN PASSANT
            //
        }
    }
}