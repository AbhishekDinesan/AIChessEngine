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
                        //SHOULD THIS BE CERR??
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
            //
            // IMPLEMENT MOVES
            //
        }
    }
}