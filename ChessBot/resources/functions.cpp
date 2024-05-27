#include <Windows.h>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <sstream>
#include <stdint.h>
#include <list>
#include <iostream>


#define PI 3.14159265f
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
#define CHECK_ANY_BIT_EQUALITY(var,var1) !(((var)&(var1))==0)

System::String^ (*toSystemString)(const std::string&) = msclr::interop::marshal_as<System::String^>;

template <typename I> std::string intToHexString(I w, size_t hex_len = sizeof(I) << 1) {
    static const char* digits = "0123456789abcdef";
    std::string rc(hex_len, '0');
    for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
        rc[i] = digits[(w >> j) & 0x0f];
    return rc;
}

template<typename Float> Float stringToFloat(const std::string& s){
    Float output = 0.0f;
    int temp = 0; int8_t pos = -1;
    for (uint8_t i = 0; i < s.length(); i++)
        if ((s[i]) == '.') pos = i;
    if (pos < 0) return(stringToInt<int>(s));

    for (uint8_t i = s.length(); i > pos; i--) {
        switch (s[i]) {
            case '1': output += 1; break;
            case '2': output += 2; break;
            case '3': output += 3; break;
            case '4': output += 4; break;
            case '5': output += 5; break;
            case '6': output += 6; break;
            case '7': output += 7; break;
            case '8': output += 8; break;
            case '9': output += 9; break;
        }
        output /= 10;
    }

    for (uint8_t i = 0; i < pos; i++) {
        temp *= 10;
        switch (s[i]) {
        case '0': continue;
        case '1': temp += 1; break;
        case '2': temp += 2; break;
        case '3': temp += 3; break;
        case '4': temp += 4; break;
        case '5': temp += 5; break;
        case '6': temp += 6; break;
        case '7': temp += 7; break;
        case '8': temp += 8; break;
        case '9': temp += 9; break;
        }
    }
    return temp + output;
}

template<typename Type> void bitSet(Type &number, uint8_t bit) {
    number |= ((Type)1 << bit);
}

//ЅуваЇ потр≥бно uint8_t, а буваЇ uint64_t вертати
template<typename Type> inline Type powOfTwo(uint8_t power) {
    if (power == 0) return 1;
    return (Type(1) << power);
}

uint8_t strLen(System::String^ input) {
    return input->Length;
}

uint8_t strLen(std::string input) {
    return input.length();
}

template<typename Integer> std::string intToString(Integer number, bool reverse = 0) {
    if (number) {
        std::string temp;
        while (number) {
            temp += ((char)((number % 10) + 48));
            number /= 10; }
        if (reverse) return temp;
        else {
            std::string output;
            for (uint8_t i = temp.length(); i > 0; i--) output += temp[i];
            return output;
        }
    }
    else return "0";
}

template<typename Type, typename Type2> Type charToInt(const Type2 &s) {
    switch (s) {
        case '0': return (Type)0; break;
        case '1': return (Type)1; break;
        case '2': return (Type)2; break;
        case '3': return (Type)3; break;
        case '4': return (Type)4; break;
        case '5': return (Type)5; break;
        case '6': return (Type)6; break;
        case '7': return (Type)7; break;
        case '8': return (Type)8; break;
        case '9': return (Type)9; break;
    }
    return (Type)-1;
}

template<typename Type> Type stringToInt(const char& s) {
    switch (s) {
        case '0': return (Type)0;
        case '1': return (Type)1;
        case '2': return (Type)2;
        case '3': return (Type)3;
        case '4': return (Type)4;
        case '5': return (Type)5;
        case '6': return (Type)6;
        case '7': return (Type)7;
        case '8': return (Type)8;
        case '9': return (Type)9;
    }
}

template<typename Type> Type stringToInt(const std::string &s) {
    Type output;
    switch (s[0]) {
        case '0': return 0;
        case '1': output = 1; break;
        case '2': output = 2; break;
        case '3': output = 3; break;
        case '4': output = 4; break;
        case '5': output = 5; break;
        case '6': output = 6; break;
        case '7': output = 7; break;
        case '8': output = 8; break;
        case '9': output = 9; break;
    }
    for (uint8_t i = 1; i < s.length(); i++) {
        output *= 10;
        switch (s[i]) {
            case '1': output += 1; break;
            case '2': output += 2; break;
            case '3': output += 3; break;
            case '4': output += 4; break;
            case '5': output += 5; break;
            case '6': output += 6; break;
            case '7': output += 7; break;
            case '8': output += 8; break;
            case '9': output += 9; break;
        }
    }
    return output;
}

template<typename Type, typename Type2> Type angleBetweenVectors(Type2 x1, Type2 y1, Type2 x2, Type2 y2) {
    return (Type)acos((x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2)));
}

template<typename Type, typename Type2> Type angleBetweenVectors(Type2 x1, Type2 y1, Type2 z1, Type2 x2, Type2 y2, Type2 z2) {
    return (Type)acos((x1 * x2 + y1 * y2 + z1 * z2) / (sqrt(x1 * x1 + y1 * y1 + z1 * z1) * sqrt(x2 * x2 + y2 * y2 + z2 * z2)));
}

template<typename Type> Type mapValues(Type x, Type in_min, Type in_max, Type out_min, Type out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<class Integer> static Integer powOfTen(uint8_t input) {
    static const int pow10[10] = {
        1, 10, 100, 1000, 10000,
        100000, 1000000, 10000000, 100000000, 1000000000
    }; return Integer(pow10[input]);
}

template <class Char> uint8_t pieceToInt(Char input) {
    switch (input) {
        case 'P':return 1;
        case 'p':return 2;
        case 'N':return 3;
        case 'n':return 4;
        case 'B':return 5;
        case 'b':return 6;
        case 'R':return 7;
        case 'r':return 8;
        case 'Q':return 9;
        case 'q':return 10;
        case 'K':return 11;
        case 'k':return 12;
    }
}

void splitFaceIndex(const std::string &faceIndex, std::vector<std::string> &parts) {
    std::stringstream ss(faceIndex);
    std::string part;
    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }
}

std::vector<std::string> Extract(const std::string& Text) {
    std::vector<std::string> Words;
    std::stringstream ss(Text);
    std::string Buf;

    while (ss >> Buf)
        Words.push_back(Buf);

    return Words;
}

void split(const std::string& in,
    std::vector<std::string>& out,
    std::string token)
{
    out.clear();

    std::string temp;

    for (int i = 0; i < int(in.size()); i++)
    {
        std::string test = in.substr(i, token.size());

        if (test == token)
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else
            {
                out.push_back("");
            }
        }
        else if (i + token.size() >= in.size())
        {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        }
        else
        {
            temp += in[i];
        }
    }
}

// Get tail of string after first token and possibly following spaces
inline std::string tail(const std::string& input){
    size_t token_start = input.find_first_not_of(" \t");
    size_t space_start = input.find_first_of(" \t", token_start);
    size_t tail_start = input.find_first_not_of(" \t", space_start);
    size_t tail_end = input.find_last_not_of(" \t");
    if (tail_start != std::string::npos && tail_end != std::string::npos)
        return input.substr(tail_start, tail_end - tail_start + 1);
    else if (tail_start != std::string::npos)
        return input.substr(tail_start);
    return "";
}

inline std::string firstToken(const std::string &input) {
    if (!input.empty()) {
        size_t token_start = input.find_first_not_of(" \t");
        size_t token_end = input.find_first_of(" \t", token_start);
        if (token_start != std::string::npos && token_end != std::string::npos)
            return input.substr(token_start, token_end - token_start);
        else if (token_start != std::string::npos)
            return input.substr(token_start);
    }
    return "";
}

System::String^ reverse(System::String^ &str) {
    uint8_t len = str->Length;
    for (uint8_t i = len - 1; i > 0; i--) str += str[i];
    str = str->Remove(0, len);
    return str;
}

std::string reverse(const std::string& str) {
    std::string output;
    for (int i = str.length(); i >= 0; i--) output += str[i];
    return output;
}

uint8_t whichPowOf256(uint64_t num) {
    uint8_t output = 0;
    while (num > 0) {
        num >>= 8;
        output++;
    } return output;
}

inline uint64_t toSquareLong(const uint8_t &square) {
    return (uint64_t) 1 << square;
}

std::string toSquare(const uint8_t& input) {
    std::string output;
    switch (input & 7) {
        case 0: output += 'a';
        case 1: output += 'b';
        case 2: output += 'c';
        case 3: output += 'd';
        case 4: output += 'e';
        case 5: output += 'f';
        case 6: output += 'g';
        case 7: output += 'h';
    }
    switch (input >> 3) {
        case 0: output += '1';
        case 1: output += '2';
        case 2: output += '3';
        case 3: output += '4';
        case 4: output += '5';
        case 5: output += '6';
        case 6: output += '7';
        case 7: output += '8';
    } return output;
}

std::string longToSquare(const uint64_t &squareLong) {
    std::string square;
    if (squareLong > 0) {
        switch (squareLong & 7) {
        case 0: square += 'a'; break;
        case 7: square += 'b'; break;
        case 6: square += 'c'; break;
        case 5: square += 'd'; break;
        case 4: square += 'e'; break;
        case 3: square += 'f'; break;
        case 2: square += 'g'; break;
        case 1: square += 'h'; break;
        } square += intToString<uint8_t>(whichPowOf256(squareLong));
    }
    else square += "-";
    return square;

}

System::String^ stdToSystemString(std::string input) {
    System::String^ output;
    for (uint8_t i = 0; i < input.length(); i++) output += input[i];
    return output;
}

