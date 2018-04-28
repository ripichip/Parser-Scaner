/*
 * GROUP NUMBER: 11
 * Type: Implementation file/.cpp
 */

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Alexander Shershnov Group Number: 11 
//=====================================================


bool vowel(char vowel)//check if our character is a a vowel of et a e i o u I E
{
  return((vowel=='a')||(vowel=='e')||(vowel=='i')||(vowel=='o')||(vowel=='u')||(vowel=='I')||(vowel=='E'));
}
bool setbr(char con)//checks if our character is a consonant that's part of set b g h k m n p r
{
  return ((con=='b')||(con=='g')||(con=='h')||(con=='k')||(con=='m')||(con=='n')||(con=='p')||(con=='r'));
}
bool setdz(char con)//Checks if our character is a constonant that's part of set d j w y z
{
  return((con=='d')||(con=='j')||(con=='w')||(con=='y')||(con=='z'));
}


// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Alexander Shershhnov
// ** RE: (vowel | vowel n | br vowel | br vowel n | br y vowel | br y vowel n | dz vowel | dz vowel n | s vowel | s vowel n| sh vowel | sh vowel n | ch vowel | ch vowel n | ts vowel | ts vowel n)^+
bool mytoken(string s)
{
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0') 
    {
      if(state == 0 && vowel(s[charpos]))
	state = 2;
      else if(state == 0 && setbr(s[charpos]))
	state = 1;
      else if(state == 0 && setdz(s[charpos]))
	state = 3;
      else if(state == 0 && (s[charpos]=='s'))
	state = 4;
      else if(state == 0 && (s[charpos]=='c'))
	state = 5;
      else if(state == 0 && (s[charpos]=='t'))
	state = 6;
      else if(state == 1 && vowel(s[charpos]))
	state = 2;
      else if(state == 1 && (s[charpos]=='y'))
	state = 3;
      else if(state == 2 && (s[charpos]=='n'))
	state = 0;
      else if(state == 2 && (s[charpos]=='c'))
	state = 5;
      else if(state == 2 && (s[charpos]=='t'))
	state = 6;
      else if(state == 2 && (s[charpos]=='s'))
	state = 4;
      else if(state == 2 && setbr(s[charpos]))
	state = 1;
      else if(state == 2 && setdz(s[charpos]))
	state = 3;
      else if(state == 2 && vowel(s[charpos]))
	state == 2;
      else if(state == 3 && vowel(s[charpos]))
	state = 2;
      else if(state == 4 && vowel(s[charpos]))
	state = 2;
      else if(state == 4 && (s[charpos]=='h'))
	state = 3;
      else if(state == 5 && (s[charpos]=='h'))
	state = 3;
      else if(state == 6 && (s[charpos]=='s'))
	state = 3;
      else if(state == 6 && vowel(s[charpos]))
	state = 2;
      else
	return false;
      charpos++;
    }//end of while

  // where did I end up????
  if ((state == 2)||(state == 0)) 
    return true;  // end in a final state
  else
    return false;
}

// ** Add the PERIOD DFA here
// ** Done by: Alexander Shershnov
bool period(string period)
{
  return (period == ".");
}


// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, SUBJECT, PRONOUN, CONNECTOR, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, DESTINATION,EOFM};

// ** string tokenName[30] = { }; for the display names of tokens
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "SUBJECT", "PRONOUN", "CONNECTOR", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "DESTINATION", "EOFM"};
// ** Need the reservedwords table to be set up here. English will be
// ** used in Part C but it should be stored now.
// ** Do not require any file input for this.
// ** a.out should work without any additional files.

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// ** Done by: Alexander Shershnov
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file via fin
  if(!(fin>>w))
    return 0;
  
  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */
  if(w == "masu")
    a = VERB;
  else if(w=="masen")
    a = VERBNEG;
  else if(w=="mashita")
    a = VERBPAST;
  else if(w=="masendeshita")
    a = VERBPASTNEG;
  else if(w=="desu")
    a = IS;
  else if(w=="deshita")
    a = WAS;
  else if(w=="o")
    a = OBJECT;
  else if(w=="wa")
    a = SUBJECT;
  else if(w=="ni")
    a = DESTINATION;
  else if((w=="watashi")||(w=="anata")||(w=="kare")||(w=="kanojo")||(w=="sore"))
    a = PRONOUN;
  else if((w=="mata")||(w=="soshite")||(w=="shikashi")||(w=="dakara"))
    a = CONNECTOR;
  else if(w=="eofm")
    a = EOFM;
  else if(mytoken(w))
    {
      a = WORD1;
      if((w[w.length()-1] == 'I')||(w[w.length()-1] == 'E'))
	a = WORD2;
    }
  else if(period(w))
    a = PERIOD;
  else
    {
      a = ERROR;
      cout << "\nLEXICAL ERROR " << w << " IS NOT A VALID TOKEN" << endl;
    }
  return 1;

}//the end



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;


  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

   while (true)
    {
      scanner(thetype, theword);  // call the scanner

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << "\n" << endl;   
       if(thetype == EOFM)
	 break;

    }

  fin.close();

}// end



