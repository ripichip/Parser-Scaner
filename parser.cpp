#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function



//Done by: Alex Shershnov
void syntaxerror1(string s, string s1)
{
  cout << "Syntax error: expected " << s << " but found " << s1 << endl;
  return;
}
//Done by: Alex Shershnov
void syntaxerror2(string s, string s1)
{
  cout << "Syntax error: unexpected " << s << " found in " << s1 << endl;
  return;
}
//Done by: Alex Shershnov
bool noun(tokentype thetype, string word)
{
  cout << "Processing <noun>" << endl;
  if(match(thetype,PRONOUN))
    cout << "Matched PRONOUN" << endl;
  else if(match(thetype, WORD1))
    cout << "Matched WORD1" << endl;
  else
    syntaxerror2(word, "noun");
}
bool verb(tokentype thetype, string word)
{
}

bool tense()//(tokentype thetype, string word)
{
}
bool be(toketype thetype, string word)
{

}
bool s()
{
}
bool verbOrNoun1()
{
}
bool verbOrNoun2()
{
}
bool beDestOrObj()
{
} 
// The test driver to start the parser
// Done by:  **
int main()
{

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}// end
//** should require no other input files!


