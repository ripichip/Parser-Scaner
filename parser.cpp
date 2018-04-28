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

/*
  1. <s> ::= [CONNECTOR] <noun> SUBJECT <verbOrNoun1>  
  2. <verbOrNoun1> ::= <verb> <tense> PERIOD | <noun> <beDestOrObj>
  3. <beDestOrObj>::= <be> PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <verbOrNoun2>
  4. <verbOrNoun2> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
*/
enum token_type {ERROR, WORD1, WORD2, PERIOD, VERB, SUBJECT, PRONOUN, CONNECTOR, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, DESTINATION,EOFM};
token_type saved_token;// global buffer for the scanner token                                                                                
bool token_available;// global flag indicating whether we have saved a token to eat up or not   
ifstream fin; 

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
  state = 2;
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
  cout << "Processing <verb>" << endl;
  if(match(thetype, WORD2))
    cout << "Matched WORD2" << endl;
  else
    syntaxerror2(word, "verb");
  return true;
}
//Done by: Alex Shershnv
bool tense()//(tokentype thetype, string word)
{
  cout << "Processing <tense>" << endl;
  
  if(match(thetype, VERBPAST))
    cout << "Matched VERBPAST" << endl;
  else if(match(thetype, VERB))
    cout << "Matched VERB" << endl;
  else if(match(thetype, VERBNEG))
    cout << "Matched VERBNEG" << endl;
  else if(match(thetype, VERBPASTNEG))
    cout << "Matched VERBPASTNEG" << endl;
  else
    syntaxerror2(word, "tense");
  return true;
    
}
//Done by: Alex Shershnov
bool be(toketype thetype, string word)
{
  cout << "Processing <be>" << endl;
  if(match(thetype, IS))
    cout << "Matched IS" << endl;
  else if(match(thetype, WAS))
    cout << "Matched WAS" << endl;
  else
    syntaxerror2(word, "be");
  return true;
}

bool Subject(toketype thetype, string word){
  if(match(thetype,word))
}

bool s(token_type& thetype, string& word){
  //Call noun
  cout<<"Processing <s>" << endl;
  /*Scanner sets word type and the word itself*/
  scanner(thetype,word);

  if(noun(thetype,word)){
    if(Subject(thetype,word)){
      // scanner(thetype,word);
      if(verbOrNoun1(thetype,word)){
        return true;
      }
    }
  }
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


int scanner(token_type& a, string& w)
{

  // ** Grab the next word from the file via fin
  if(!(fin>>w))
    return 0;
  cout<<"Scanner called using word: "<< w <<endl;
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


// next_token(void)                                                                                                                           
//    Looks ahead to see what token comes next from the scanner.                                                                              
//    HOW: checks first to see if the token_available flag is false.                                                                          
//    If so, saved_token gets scanner() result.                                                                                               
//           and the flag is set true.                                                                                                        
//    Thus a token is grabbed but is not eaten up.                                                                                            
//    Returns the saved_token                                                                                                                 
//    
//Done by: Joshua Cantero
token_type next_token(){
  string lexeme;
  if (!token_available) // if there is no saved token from previous lookahead                                                                 
    {
      // call scanner to grab a new token                                                                        
      if(scanner(saved_token, lexeme))
        token_available = true;// mark that fact that you have saved it                                                                         
    else
      cout<<"Error reading from file"<<endl;
    }
  return saved_token; // return the saved token                                                                                               
}

//match(expected)                                                                                                                             
//  Checks and eats up the expected token.                                                                                                    
//  HOW: checks to see if expected is different from next_token()                                                                             
//  and if so, generates a syntax error and handles the error                                                                                 
//  else token_available becomes false (eat up) and returns true.

//Done by: Joshua Cantero
bool match(token_type expected)
{
  if (next_token() != expected)  // mismatch has occurred with the next token                                                                 
    { // generate a syntax error message here                                                                                                 
      // do error handling here if any 
      //Error message called in calling function
      return false;                                                                                                     
    }
  else  // match has occurred                                                                                                                 
    { 
      token_available = false;  // eat up the token                                                                                         
        return true;              // say there was a match                                                                                      
    }
}

void story(){
  cout<<"Processing <story>"<<endl;
  token_type a;
  string w;

  while(s(a,w)){
  

  }
}


// The test driver to start the parser
// Done by:  **
int main()
{
  string inputFile;
  cout<<"Enter input file: ";
  cin>>inputFile;
  fin.open(inputFile.c_str());
  story();

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}// end
//** should require no other input files!


