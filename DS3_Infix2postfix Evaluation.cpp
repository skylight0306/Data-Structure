#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib> 
#include "memory.h"

using namespace std;
void InToPost(char*, char*);
int Priority(char);
int PostToInt(char*);
int Cal(char, int, int);
void Mission1(char* infix, char* postfix, bool & error );
void Mission2(char* infix, char* postfix);
void Mission3(char* postfix, int val);
void Clearwhitespace( char* Infix ) ;
int main() {
  char infix[1000] = {'\0'}; 
  char postfix[1000]= {'\0'}; 
  int command = 0 ;
  int val = 0;
  bool error = false ;
  char ch;
  cout << endl << "* Arithmetic Expression Evaluator *" ;
  cout << endl << "* 0. QUIT                         *" ;
  cout << endl << "* 1. Infix2postfix Evaluation     *" ;
  cout << endl << "***********************************" ;
  cout << endl << "Input a choice(0, 1): " ;
  cin >> command ;  // get a command
  cout << endl;
  while ( command != 0 ) {
  	val = 0; // 歸零 
    for ( int i = 0 ; i < 1001 ; i++ ) { // 初始化 
      infix[i] = '\0' ;
      postfix[i] = '\0' ;
    } // for
  	error = false ; // 初始化 
    if ( command == 1 ) { // mission
      cout << endl << "Input an infix expression:" ;
      cin.getline( infix, sizeof(infix), '\n' ) ;
      Clearwhitespace( infix ) ;
      Mission1(infix, postfix, error) ;
      if ( !error ) {
        Mission2(infix, postfix) ;
        Mission3(postfix, val) ;
      } // if  
	} // if
	else if ( command == 0 )
	  return 1 ;
	else {
      cout << "Command does not exist!" << endl ; 
	} // else
    cout << endl << "* Arithmetic Expression Evaluator *" ;
    cout << endl << "* 0. QUIT                         *" ;
    cout << endl << "* 1. Infix2postfix Evaluation     *" ;
    cout << endl << "***********************************" ;
    cout << endl << "Input a choice(0, 1): " ;
    cin >> command ;  // get a command
    cout << endl;
  } // while
} // main()

void Clearwhitespace( char* infix ) {
    char temp[1000] = {'\0'} ;
    cin.getline( temp, sizeof(temp), '\n' ) ;
    int m = 0;
    int n = 0;
	while( m < strlen(temp) ) {
      if ( temp[m] != ' ' ) {
        infix[n] = temp[m] ;
        n++;
      } // if
      m++;
	} // while
} // Clearwhitespace() 

void InToPost(char* Infix, char* Postfix) {
    char Stack[1000] = {'\0'};
    int i, j, Stack_Top;
    int temp=0;
    for(i = 0; Infix[i] != '\0'; i++) {
        if(Infix[i]=='(')
        	temp++;
        if(Infix[i]==')')
        	temp--;	 
	} // for
    for(i = 0, j = 0, Stack_Top = 0; Infix[i] != '\0'; i++) {
		if(i==0) {
			if(Infix[i]=='-') {
            		Postfix[j++] = '-';
            		i++;
            } // if
        	else if(Infix[i]=='+') {
            		Postfix[j++] = '+';
            		i++;
            } // else if
		} // if
		
		switch(Infix[i]) {
        	case '(':     
            	Stack[++Stack_Top] = Infix[i];
            	if(Infix[i+1]=='-') {
            		Postfix[j++] = '-';
            		i++;
            	} // if 
            	break; 
        	case '+': case '-': case '*': case '/': case '%': 
				while(Priority(Stack[Stack_Top]) >= Priority(Infix[i])) {
                	if(Postfix[j-1]!=' ') {
                		Postfix[j++] = ' ';
                	} // if
					Postfix[j++] = Stack[Stack_Top--];
            	} // while
            	Postfix[j++] = ' ';
            	Stack[++Stack_Top] = Infix[i]; 
            	if(Infix[i+1]=='-') {
            		Postfix[j++] = '-';
            		i++;
            	} // if
            	if(Infix[i+1]=='+')            
            	  i++;          	
            	break;
            	
        	case ')':
            	while(Stack[Stack_Top] != '(')	{ 
                	Postfix[j++] = ' ';
					Postfix[j++] = Stack[Stack_Top--];	
            	}  // while
            	Stack_Top--;
            	break;
            	
        	default:       		
            	Postfix[j++] = Infix[i];
    	}
    } // for
    
    while(Stack_Top > 0) {
		Postfix[j++] = ' '; 
        Postfix[j++] = Stack[Stack_Top--];
    } // while
} // InToPost()

int Priority(char op) {
    switch(op)
	{ 
        case '+': case '-':
			return 1;
        case '*': case '/': case '%':
			return 2;
        default:            
			return 0;
    } 
} //Priority()

int PostToInt(char* Postfix) {
    char temp[1000] = {'\0'};
    int stack[1000] = {'\0'}; 
    int top, i, j;
    for(top = 0, i = 0; Postfix[i] != '\0'; i++)
		switch(Postfix[i])
		{
        	case '+': case '-':
				if(Postfix[i+1]>47 && Postfix[i+1]<58) {
					for(j = 0; Postfix[i] != ' '; i++, j++)	{
            			temp[j] = Postfix[i];
					} // for
					stack[++top] = atoll(temp);
					memset(temp, '\0', sizeof(temp));
					break;
				} // if 
				stack[top - 1] = Cal(Postfix[i], stack[top - 1], stack[top]);
            	top--; 
            	break;
            	
            case '/': case '%':
				stack[top - 1] = Cal(Postfix[i], stack[top - 1], stack[top]);
            	top--; 
            	break;
            	
			case '*':
            	stack[top - 1] = Cal(Postfix[i], stack[top - 1], stack[top]); 
            	top--; 
            	break;
				 
        	case ' ':
				break;
				
        	default:
				for(j = 0; Postfix[i] != ' '; i++, j++)	{
            		temp[j] = Postfix[i];
				} // for
				stack[++top] = atoll(temp);
				memset(temp, '\0', sizeof(temp));
		}
		
    return stack[top];
} // PostToInt()

int Cal(char op, int N1, int N2) { //計算符號 
    switch(op)
	{
        case '+':
			return N1 + N2;
        case '-':
			return N1 - N2;
        case '*':
			return N1 * N2;
        case '/':
			return N1 / N2;
        case '%':
			return N1 % N2;
    }
    
    return 0;
} // cal()

void Mission1(char* infix, char* postfix, bool & error ) {
    int i = 0, j = 1;
    int m = 0, n = 0;
    error = false;
    bool error1 = false ;
    bool error3 = false ;
    if ( i == 0 )
      if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' ) error3 = true ;
    while( i <= 100 ) {
    	if ( infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')' && infix[i] != '\0' 
     	     && infix[i] != '1' && infix[i] != '2' && infix[i] != '3' && infix[i] != '4' && infix[i] != '5' && infix[i] != '6' && infix[i] != '7' &&
			 infix[i] != '8' && infix[i] != '9' && infix[i] != '0' ) {  // error1
      		cout << "Error 1: " << infix[i] << "is not a legitimate character." << endl ;
      		error1 = true ; 
     		break ;
        } // if
    	if ( infix[i] == '(' || infix[i] == ')') { // error2
	      if ( infix[i] == '(' ) m++ ;
		  if ( infix[i] == ')' ) n++ ;
		} // if
		if ( i < 100 ) {  // error3
		  if ( infix[i] == '/' ) {
		  	if( infix[j] == '1' || infix[j] == '2' || infix[j] == '3' || infix[j] == '4' || infix[j] == '5' || infix[j] == '6' || infix[j] == '7' 
		         || infix[j] == '8' || infix[j] == '9' || infix[j] == '0') {
		  	  cout << "### Error: Divided by ZERO! ###" << endl << "### It cannot be successfully evaluated! ###" << endl ;
		  	  error = true;
		  	  break;
            } // if
		  } // if
		  if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' ) {
			if ( infix[j] == '+' || infix[j] == '-' || infix[j] == '*' || infix[j] == '/' || infix[j] == ')' ) error3 = true;
    	  } // if
    	  if ( infix[i] == '1' || infix[i] == '2' || infix[i] == '3' || infix[i] == '4' || infix[i] == '5' || infix[i] == '6' || infix[i] == '7' 
		       || infix[i] == '8' || infix[i] == '9' || infix[i] == '0' ) {
		    	if ( infix[j] == '(' ) error3 = true;
          } // if
          if ( infix[i] == ')' ) {
            if ( infix[i] == '1' || infix[i] == '2' || infix[i] == '3' || infix[i] == '4' || infix[i] == '5' || infix[i] == '6' || infix[i] == '7' 
		         || infix[i] == '8' || infix[i] == '9' || infix[i] == '0' ) error3 = true ; 
		  } // if
	    } // if 
		i++;
		j = i + 1;
	} // while
	
	if ( error1 || m != n || error3 ) error = true ;
    if ( m != n ) cout << "Error 2: there is one extra open parenthesis." << endl ;
	else if ( error3 ) cout << "Error 3: there is one extra operand." << endl ; 
	if ( !error ) cout << "It is a legitimate infix expression." << endl ;
} // Mission1()

void Mission2(char* infix, char* postfix) {
	InToPost(infix, postfix);
    int i = 0;
    cout << "Postfix expression: " ; 
cout << postfix[0] ; 
    for(i = 1; postfix[i] != '\0'; i++) {
    cout << postfix[i] ; 
    } // for
    cout << endl ;
} // Mission2()

void Mission3(char* Postfix, int val ) {
    val=PostToInt(Postfix);
    cout << "Answer: " << val << endl ;
} // Mission3()


