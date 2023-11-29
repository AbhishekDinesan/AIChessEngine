#include "TextDisplay.h"
#include "Square.h"

TextDisplay::TextDisplay() : theDisplay(8, std::vector<char>(8, '_')) {}

void TextDisplay::notify(Square &s)
{
    
}

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            out << td.theDisplay[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}
