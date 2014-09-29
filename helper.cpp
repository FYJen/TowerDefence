#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
    cerr << str << endl;
    exit(0);
}