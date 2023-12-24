#include "AVL.h"

/*
 test_read() is a function that reads words, one at a time, from cin,
 into the AVL tree and print the stats.
*/
void test_read()
{
    Wordlist lst;
    string w;
    while (cin >> w)
    {
        lst.add_word(w);
    }

    lst.print_words();
    cout << endl;
    lst.print_stats();
}

int main() 
{
    test_read();
}
