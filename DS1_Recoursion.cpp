#include <stdio.h> 
#include <stdlib.h>
#include <iostream> 
#include <time.h>

int gN = 0;
int gcheck = 0 ;
int gPlus = 0;
void sort();
void perm1(int*, int);
void perm2(int*, int);
void perm3(int*, int);
void rotate(int*, int, int);
void plus(int* num, int i);
void mission1();
void mission2();
void mission3();
void mission4();
bool CheckRe(int* num );

struct All {                             
  int *gnum = new int[gN] ;
  All *next;
} ;

All *gall = new All;
All *gfirst = new All;
All *glast = new All;
bool gstart = false;

int main(void){
	int N = 0 ; 
	int fun = -1;
	while ( fun != 0) {
      printf( "** permutation Generator **\n" );
      printf( "* 0. Quit                 *\n" );
      printf( "* 1. N numbers from 1..N  *\n" );
      printf( "* 2. M numbers from input *\n" );
      printf( "* 3. M numbers from 1..9  *\n" );
      printf( "* 4. M numbers from 1..N  *\n" );
      printf( "**YEEEEEEEEEEEEEEEEEEEEEE**\n" );
      printf( "Input a choise<0, 1, 2, 3, 4>:" );
      std::cin >> fun ;
      if ( fun == 0 || fun == 1 || fun == 2 || fun == 3 || fun == 4) {
        if ( fun == 1) mission1();
	    if ( fun == 2) mission2(); 
        if ( fun == 3) mission3();
        if ( fun == 4) mission4();
        if ( fun == 0) return 0;
	  }
	  else printf( "command does not exist\n" );
	  gcheck = 0;
    } // while
    return 0;
}

void mission1() { 
    int N = 0 ; 
    printf( "Input a number: " );
    std::cin >> gN ;
    /*
    while ( gN > 9 || gN < 1 ) {
	  printf( "### It is NOT in [1,9] ###\n" );
	  printf( "\nInput a number: " );	  
      std::cin >> gN ;
    } // while     
    */
    int *num = new int[gN] ;
    for ( int i = 0; i < gN; i++) 
      num[i] = i + 1 ;
    if ( gN < 13 && gN > 0 ) {
	  perm1(num, 0);
	  std::cout << "Mission 1: " << gcheck << " permutations\n";
      std::cout << "L = " << gN ;
    } // if
} 

void mission2() { 
    int N = 0 ; 
    int input = 0;
    printf( "Input a number: " );
    std::cin >> gN ;
    while ( gN > 9 || gN < 1 ) {
	  printf( "### It is NOT in [1,9] ###\n" );
	  printf( "\nInput a number: " );	  
      std::cin >> gN ;
    } // while
	     
    int *num = new int[gN] ;
    for ( int i = 0; i < gN; i++) {
	  printf( "\nInput a number: " );	 
      std::cin >> input ;
      while ( input < 0 ) {
	    printf( "\nInput a number: " );	  
        std::cin >> input ;
      } // while
      num[i] = input ;
    } // for 
      
    if ( gN < 10 && gN > 0 ) {
	  perm2(num, 0);
      std::cout << "mission2: " << gcheck << " permutations" ;
    } // if
    
    std::cout << "\nT = " << (double)clock() / CLOCKS_PER_SEC << " ms"; 
} 

void mission3() { 
    int n = 0;
    int junk = 0;
    bool repeat = false;
    int N = 0 ; 
    int input = 0;
    printf( "Input a number: " );
    std::cin >> gN ;
    while ( gN > 9 || gN < 1 ) {
	  printf( "### It is NOT in [1,9] ###\n" );
	  printf( "\nInput a number: " );	  
      std::cin >> gN ;
    } // while
    
    int *num = new int[gN] ;
    for ( int i = 0; i < gN; i++) {
      num[i] = i + 1 ;
    } // for
    
    while( num[0]!=9 ) {	  
      if ( !CheckRe(num) ) {
        perm3(num, 0);
      } // if
      plus( num, gN-1);
    } // while
    
    int dash = 1;  
    
    gall = gfirst;
    sort();
    for( int p = 0 ; gall != NULL ; gall = gall->next){
    	std::cout << "[" << dash << "] " ; 
        for(int i = 0; i < gN-1; i++) { /////////////////////////////
          printf("%d,", gall->gnum[i]);
		  n = i + 1; 
        } // for
        printf("%d", gall->gnum[n]); 
        printf("\n");////////////////////////////////////////////////
        dash = dash + 1;
        p++;
    }// for
    
    
    
    
    std::cout << "\nT = " << (double)clock() / CLOCKS_PER_SEC << " ms"; 
} 

void mission4() { 
    int n = 0;
    int junk = 0;
    bool repeat = false;
    int N = 0 ; 
    int input = 0;
    printf( "Input a number: " );
    std::cin >> gN ;
    while ( gN > 9 || gN < 1 ) {
	  printf( "### It is NOT in [1,9] ###\n" );
	  printf( "\nInput a number: " );	  
      std::cin >> gN ;
    } // while
    
    int *num = new int[gN] ;
    for ( int i = 0; i < gN; i++) {
      num[i] = i + 1 ;
    } // for
    
    printf( "\nInput N to 1~N: " );
    std::cin >> gPlus;
    while( num[0]!=gPlus ) {	  
      if ( !CheckRe(num) ) {
        perm3(num, 0);
      } // if
      plus( num, gN-1);
    } // while
    
    int dash = 1;  
    
    gall = gfirst;
    sort();
    for( int p = 0 ; gall != NULL ; gall = gall->next){
    	std::cout << "[" << dash << "] " ; 
        for(int i = 0; i < gN-1; i++) { /////////////////////////////
          printf("%d,", gall->gnum[i]);
		  n = i + 1; 
        } // for
        printf("%d", gall->gnum[n]); 
        printf("\n");////////////////////////////////////////////////
        dash = dash + 1;
        p++;
    }// for
    
    
    
    
    std::cout << "\nT = " << (double)clock() / CLOCKS_PER_SEC << " ms"; 
} 

void sort(){
  All *memory = new All;
  All *memory2 = new All;
  for( All *temp = gfirst ; temp->next != NULL ; temp = temp->next){
  	for( All *temp2 = temp; temp2->next != NULL ; temp2 = temp2->next ){
  		if( temp2->gnum[0] *gPlus*100 + temp2->gnum[1] *gPlus* 10 + temp2->gnum[2] * gPlus > temp2->next->gnum[0] *gPlus*100 + temp2->next->gnum[1] *gPlus *10 + temp2->next->gnum[2]*gPlus ) {
  			for( int m = 0; m < gN ; m++ ) 
  			  memory->gnum[m] = temp2->gnum[m];
  			for( int m = 0; m < gN ; m++ ) 
  			  temp2->gnum[m] = temp2->next->gnum[m];
  			for( int m = 0; m < gN ; m++ ) 
  			  temp2->next->gnum[m] = memory->gnum[m];
	    }
  		
	}
  }
}
void plus(int* num, int i) {
  if ( num[i] < gPlus ) {
  	num[i] = num[i] + 1;
  } 
  else if( i != 0 ) {
    plus( num , i - 1 );
    num[i] = 1;
  } 
}

void perm1(int* num, int i) {  // RECURSION  任務一的排列 
    int n = 0;
    if(i < gN) { 
        int j = 0;
        for(j = i; j < gN; j++) {
          int to[gN];
          for( int m = 0; m < gN; m++) { // 將NUM複製到TO  
            to[m] = num[m];
          } // for 
          rotate(to, i, j);
          perm1(to, i + 1); 
        } // for 
    } // if
	else {    
	  gcheck++;
	  std::cout << "[" << gcheck << "] " ; 
      for(int i = 0; i < gN-1; i++) {
        printf("%d,", num[i]); 
        n = i + 1;
      } // for
      printf("%d", num[n]); 
      printf("\n");   
    } // else
}
  
void perm2(int* num, int i) {  // RECURSION 
    int n = 0;
    if(i < gN) { 
        int j = 0;
        for(j = i; j < gN; j++) {
          int to[gN];
          for( int m = 0; m < gN; m++) { // 將NUM複製到TO  
            to[m] = num[m];
          } // for 
          rotate(to, i, j);
          perm2(to, i + 1); 
        } // for 
    } // if
	else {    
	  gcheck++;
	  std::cout << "[" << gcheck << "] " ; 
      for(int i = 0; i < gN-1; i++) {
        printf("%d,", num[i]); 
        n = i + 1;
      } // for
      printf("%d", num[n]); 
      printf("\n");   
    } // else
}  

void perm3(int* num, int i) {  // RECURSION  任務3的排列 
    int junk = 0;
    All *temp = new All;
    temp->next = NULL;
    int n = 0;
    if(i < gN) { 
        int j = 0;
        for(j = i; j < gN; j++) {
          int to[gN];
          for( int m = 0; m < gN; m++) { // 將NUM複製到TO  
            to[m] = num[m];
          } // for 
          rotate(to, i, j);
          perm3(to, i + 1); 
        } // for 
    } // if
    else {    
	  gcheck++;
	  for( int m = 0; m < gN; m++)
	    temp->gnum[m] = num[m];
	  gall->next = temp;
	  gall = gall->next;
	  gall->next = NULL;
	  glast = gall;
	  if( !gstart ) {
	    gfirst = gall;
	    gstart = true;
      }
      
    } // else
}  

bool CheckRe(int* num ) {
	int same = 0, junk = 0;
	int n = 0;
    for( int k = 0; k < gN ; k++ ) { //查找數列重複數字 
      for( int h = 0; h < gN ; h++ ) {
      	if( num[k] == num[h] && k != h ) return true;
      } // for
	} // for
	gall = gfirst;
	for( int i = 0; gall != NULL && gstart; gall = gall->next ) { // 找重復排列 
	  for ( int j = 0; j < gN; j++) {
		if ( num[j] == gall->gnum[j] ) same++;
      }
      if ( same == gN ) {
        gall = glast;
	    return true;
      } // if
      
      same = 0;
	}
  gall = glast;
  return false;
}

void rotate(int* num, int i, int j) {
    int tmp = num[j]; 
    int k;
    for(k = j; k > i; k--) {
        num[k] = num[k - 1]; 
    }
    num[i] = tmp;
}
