#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include "split.h"

using namespace std;

string* getSymbolPtr(string& s, set<string>& symbols) {
    string* ptr;
    set<string>::iterator q = symbols.find(s);
    if (q == symbols.end()) {
        // pair<set<string>::iterator, bool> result = 
        return (string*) &*symbols.insert(s).first;
    } else return (string*) &*q;
}

int main(int argc, char** argv) {

    if (argc > 1) {
        if ((string) argv[1] == "-h" || (string) argv[1] == "--help") {
            cerr << "usage: <[2-column table] " << argv[0] << " >[contingency matrix]" << endl
                 << "Writes a contingency table for the 2 variables described in the input." << endl
                 << "Input must be 2-column and tab-delimited.  Any header should be removed." << endl
                 << "In the output, the first variable is Y, the second is X." << endl;
            return 0;
        }
    }

    set<string> symbols;
    map<string*, map<string*, int> > contingency;

    long int lineno;
    string line;
    while (getline(cin, line)) {
        ++lineno;
        vector<string> fields = split(line, '\t');
        if (fields.size() != 2) {
            cerr << "cannot make contingency table for more than 2 variables" << endl
                 << "line " << lineno << ":" << line << endl
                 << "does not have 2 tab-delimited fields" << endl;
            return 1;
        }
        string* a = getSymbolPtr(fields.front(), symbols);
        string* b = getSymbolPtr(fields.back(), symbols);
        ++contingency[a][b];
    }

    for (set<string>::iterator a = symbols.begin(); a != symbols.end(); ++a) {
        cerr << "\t" << *a;
    }
    cerr << endl;
    for (set<string>::iterator a = symbols.begin(); a != symbols.end(); ++a) {
        cerr << *a;
        for (set<string>::iterator b = symbols.begin(); ; ++b) {
            if (b == symbols.end()) { cout << "\n"; break; }
            cout << "\t" << contingency[(string*)&*a][(string*)&*b];
        }
    }

    return 0;
}
