CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -MMD -g -Werror=vla
EXEC = chess
OBJECTS = main.o BishopPiece.o Board.o ComputerFour.o ComputerOne.o ComputerThree.o ComputerTwo.o Game.o graphicsDisplay.o KingPiece.o KnightPiece.o Move.o NonePiece.o PawnPiece.o Player.o QueenPiece.o RookPiece.o square.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
        ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
        rm ${OBJECTS} ${EXEC} ${DEPENDS}