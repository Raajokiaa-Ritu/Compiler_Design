✅ C++ Code for Lexical Analyzer
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

const int MAX_ID_LENGTH = 31;

unordered_set<string> keywords = {
    "int", "float", "char", "if", "else", "while", "return", "for", "void", "main"
};

// Check if character is valid in identifier
bool isIdentifierStart(char ch) {
    return isalpha(ch) || ch == '_';
}

bool isIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

void lexicalAnalyzer(ifstream &file) {
    char ch;
    string buffer;

    while (file.get(ch)) {
        // Ignore whitespace
        if (isspace(ch)) continue;

        // Skip single-line comments //
        if (ch == '/') {
            char next = file.peek();
            if (next == '/') {
                while (file.get(ch) && ch != '\n');
                continue;
            } else if (next == '*') {
                file.get(); // consume '*'
                while (file.get(ch)) {
                    if (ch == '*' && file.peek() == '/') {
                        file.get(); // consume '/'
                        break;
                    }
                }
                continue;
            }
        }

        // Identifiers / Keywords
        if (isIdentifierStart(ch)) {
            buffer = ch;
            while (file.peek() != EOF && isIdentifierChar(file.peek())) {
                char next = file.get();
                if (buffer.length() < MAX_ID_LENGTH)
                    buffer += next;
            }

            if (keywords.count(buffer)) {
                cout << "[KEYWORD: " << buffer << "]\n";
            } else {
                cout << "[IDENTIFIER: " << buffer << "]\n";
            }
        }

        // Numbers
        else if (isdigit(ch)) {
            buffer = ch;
            while (isdigit(file.peek())) {
                buffer += file.get();
            }
            cout << "[NUMBER: " << buffer << "]\n";
        }

        // Symbols / Operators
        else if (string("+-*/=;,(){}<>").find(ch) != string::npos) {
            cout << "[SYMBOL: " << ch << "]\n";
        }

        // Unknown character
        else {
            cout << "[UNKNOWN: " << ch << "]\n";
        }
    }
}

int main() {
    ifstream file("input.cpp");

    if (!file.is_open()) {
        cerr << "Could not open the file.\n";
        return 1;
    }

    cout << "Lexical Analysis Output:\n\n";
    lexicalAnalyzer(file);
    file.close();

    return 0;
}
