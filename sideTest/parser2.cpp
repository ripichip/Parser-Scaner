#include<iostream>
#include<fstream>
#include<string>
using namespace std;

enum token_type {ERROR, WORD1, WORD2, PERIOD, VERB, SUBJECT, PRONOUN, CONNECTOR, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, DESTINATION,EOFM};

token_type saved_token;// global buffer for the scanner token                                                                                
bool token_available;// global flag indicating whether we have saved a token to eat up or not   
ifstream fin; 

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
bool period(string period)
{
  return (period == ".");
}

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

/*Scanner sets new word that's read and also sets the token type*/
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


//Done by: Alex Shershnov
bool noun(token_type& thetype, string& word)
{
  cout << "Processing <noun>" << endl;
  if(match(PRONOUN)){
    cout << "Matched PRONOUN" << endl;
    return true;
  }else if(match(WORD1)){
    cout << "Matched WORD1" << endl;
    return true;
  }else{
    syntaxerror2(word, "noun");
    return false;
  }
}

//Done by: Joshua Cantero
bool subject(token_type& thetype, string& word){
  if(match(SUBJECT)){
     cout << "Matched SUBJECT" << endl;
    return true;
  }else{
    syntaxerror2(word, "SUBJECT");
    return false;
  }
}
/*
  1. <s> ::= [CONNECTOR] <noun> SUBJECT <verbOrNoun1>  
  2. <verbOrNoun1> ::= <verb> <tense> PERIOD | <noun> <beDestOrObj>
  3. <beDestOrObj>::= <be> PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <verbOrNoun2>
  4. <verbOrNoun2> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
*/

//Done by: Alex Shershnov
bool be(token_type& thetype, string& word)
{
  cout << "Processing <be>" << endl;
  if(match(IS)){
    cout << "Matched IS" << endl;
    return true;
  }
  else if(match(WAS)){
    cout << "Matched WAS" << endl;
    return true;
  }
  else{
    syntaxerror2(word, "be");
    return false;
  }
  return false;
}

//Done by: Alex Shershnv
bool verb(token_type& thetype, string& word)
{
  cout << "Processing <verb>" << endl;
  if(match(WORD2)){
    cout << "Matched WORD2" << endl;
    return true;
  }
  else{
    syntaxerror2(word, "verb");
    return false;
  }
}
//Done by: Alex Shershnv
bool tense(token_type& thetype, string& word)//(tokentype thetype, string word)
{
  cout << "Processing <tense>" << endl;
  
  if(match(VERBPAST)){
    cout << "Matched VERBPAST" << endl;
    return true;
  }
  else if(match(VERB)){
    cout << "Matched VERB" << endl;
    return true;
  }
  else if(match(VERBNEG)){
    cout << "Matched VERBNEG" << endl;
    return true;
  }
  else if(match(VERBPASTNEG)){
    cout << "Matched VERBPASTNEG" << endl;
    return true;
  }
  else{
    syntaxerror2(word, "tense");
    return false;
  }
  // return true;   
}

//Done by: Joshua Cantero
bool PERIODFUNC(token_type& thetype, string& word){
  if(match(PERIOD)){
    cout<<"Matched PERIOD"<<endl;
    return true;
  }else{
    syntaxerror2(word, "PERIOD");
    return false;
  }
}
//Done by: Joshua Cantero
bool DESTINATIONFUNC(token_type& thetype, string& word){
  if(match(DESTINATION)){
    cout<<"Matched DESTINATION"<<endl;
    return true;
  }else{
    syntaxerror2(word, "DESTINATION");
    return false;
  }
}

//Done by: Joshua Cantero
bool OBJECTFUNC(token_type& thetype, string& word){
  if(match(OBJECT)){
    cout<<"Matched OBJECT"<<endl;
    return true;
  }else{
    syntaxerror2(word, "OBJECT");
    return false;
  }
}

// 4. <verbOrNoun2> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
//Done by: Joshua Cantero
bool verbOrNoun2(token_type& thetype, string& word){
  if(verb(thetype,word)){
    if(tense(thetype,word)){
      if(PERIODFUNC(thetype,word)){
        return true;
      }
    }
  }else if(noun(thetype,word)){
    if(DESTINATIONFUNC(thetype,word)){
      if(verb(thetype,word)){
        if(tense(thetype,word)){
          if(PERIODFUNC(thetype,word)){
            return true;
          }
        }
      }
    }
  }else{
    //Error
    return false;
  }
  return false;
}

// 3. <beDestOrObj>::= <be> PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <verbOrNoun2>
//Done by: Joshua Cantero
bool beDestOrObj(token_type& thetype, string& word){
  if(be(thetype,word)){
    if(PERIODFUNC(thetype,word)){
      return true;
    }
  }else if(DESTINATIONFUNC(thetype,word)){
    if(verb(thetype,word)){
      if(tense(thetype,word)){
        if(PERIODFUNC(thetype,word)){
          return true;
        }
      }
    }
  }else if(OBJECTFUNC(thetype,word)){
    if(verbOrNoun2(thetype,word)){
      return true;
    }
  }else{
    //Error
  }
  return false;
}

//Done by: Joshua Cantero
bool verbOrNoun1(token_type& thetype, string& word){
  cout<<"Processing <verbOrNoun1>" << endl;
  if(verb(thetype,word)){
    if(tense(thetype,word)){
      if(PERIODFUNC(thetype,word)){
        return true;
      }
    }
  }else if(noun(thetype,word)){
    if(beDestOrObj(thetype,word)){
      return true;
    }

  }
return false;
}

//Done by: Joshua Cantero
bool s(token_type& thetype, string& word){
  //Call noun
  cout<<"\nProcessing <s>" << endl;
  /*Scanner sets new word that's read and also sets the token type*/
  if(noun(thetype,word)){
     if(subject(thetype,word)){
       if(verbOrNoun1(thetype,word)){
          return true;
        }
     }
  }else{
    cout<<"Test error"<<endl;
    return false;
  }
  return false;
}

//Done by: Joshua Cantero
void story(){
  cout<<"Processing <story>\n"<<endl;
  token_type a;
  string w;

  while(s(a,w)){
  }
}

int main()
{
  // string inputFile;
  // cout<<"Enter input file: ";
  // cin>>inputFile;
  // fin.open(inputFile.c_str());
  fin.open("testinput.txt");
  story();
  cout<<"Fin"<<endl;
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}