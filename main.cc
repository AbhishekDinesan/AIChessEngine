#include <string>
#include <iostream>
// ADD INCLUDE STATEMENTS
using namespace std;

int main() {
    string cmd;
    while (true) {
        cin >> cmd;
        
        if (cmd == "game") {
            string playerType;
            int cpuDifficulty = 0;
            bool isWhiteInit = false;
            bool isBlackInit = false;

            while (!isWhiteInit || !isBlackInit) {
                cin >> playerType;
                if (playerType == "computer") {
                    cin.ignore(); // removes the "]" from the input 
                    cin >> cpuDifficulty;


                    if (cpuDifficulty > 4 || cpuDifficulty < 0) {
                        if (!isWhiteInit) cerr << "Invalid White Player Computer Difficulty";
                        else cerr << "Invalid Black Player Computer Difficulty";
                        break;
                    } 


                    if (!isWhiteInit) {
                        //
                        // IMPLEMENT WHITE PLAYER INITIALIZATION AS A COMPUTER
                        // WITH cpuDifficulty DIFFICULTY
                        //
                        isWhiteInit = true;
                    } else {
                        //
                        // IMPLEMENT BLACK PLAYER INITIALIZATION AS A COMPUTER
                        // WITH cpuDifficulty DIFFICULTY
                        //
                        isBlackInit = true;
                    }
                    cin.ignore(); // removes the "]" from the input
                } else if (playerType == "human") {
                    if (!isWhiteInit) {
                        //
                        // IMPLEMENT WHITE PLAYER INITIALIZATION AS A HUMAN
                        //
                        isWhiteInit = true;
                    } else {
                        //
                        // IMPLEMENT BLACK PLAYER INITIALIZATION AS A HUMAN
                        //
                        isBlackInit = true;
                    }
                } else {
                    // SHOULD THIS BE CERR??
                    if (!isWhiteInit) cerr << "Invalid White Player Type" << endl;
                    else cerr << "Invalid Black Player Type" << endl;
                }
            }
        } else if (cmd == "resign") {
            // 
            // IMPLEMENT RESIGNATION
            //
        } else if (cmd == "move") {
            char startFile = 'a';
            int startRank = 1;
            char endFile = 'h';
            int endRank = 8;
            bool validSquares = true;

            if (startFile < 'a' || startFile > 'h') {
                cerr << "Invalid Starting File" << endl;
                validSquares = false;
            }

            if (startRank < 1 || startRank > 8) {
                cerr << "Invalid Starting Rank" << endl;
                validSquares = false;
            }

            if (endFile < 'a' || startFile > 'h') {
                cerr << "Invalid Ending File" << endl;
                validSquares = false;
            }

            if (endRank < 1 || startRank > 8) {
                cerr << "Invalid Ending Rank" << endl;
                validSquares = false;
            }

            if (validSquares) {
                //
                // IMPLEMENT THE MOVE
                //
            }
        } else if (cmd == "setup") {
            //
            // IMPLEMENT LOGIC CHECKING IF A GAME IS CURRENTLY RUNNING
            // 
            

        }
    }
}