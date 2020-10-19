//�t��: ��T�G�� 10627134 �\�J�� ��T�G�� 10627149 �\?�� 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
#include <queue>
#include <time.h>
#include <iomanip>
using namespace std;

    struct ablist {
      int Oid; //OID
      int Delay;
      int Abort;
	};
    struct ablist2 {
      int Oid; //OID
      int Cid;
      int Delay;
      int Abort;
	};
    ablist temp ;
    ablist2 temp2;
    struct cT {
       string rawR; // raw data of one record
       int Oid; // OID
       int Arr; // Arrival
       int Dur; // Duration
       int Time; // TimeOut
    } ;
    cT lib;
    cT ord;
    struct Chef {
     int Cid ;
     cT Current ;
     queue<cT> waittinglist ; 
     bool standby = true ; // chef�O�_���m 
     int currenttime;
   }; 
   	cT ordqueue ;

class mission{
	public:
		void mission1( int &stop );
		void mission2( int &index );
		void mission3( int &index );
};

void DealDat( string data ) {
	  	int tabcount = 0 ;
        int tabstart = -1 ;
        int tabend = 0 ;
        int k = 0;
        string infostring = "";
      	lib.rawR = data;
	  	string temp;
	  	for ( tabcount = 1; tabcount < 5 ; tabcount++ ) {
			if ( tabcount == 1 ) {
              for ( k = 0; data[k] != '\t' ; k++ ) infostring = infostring + data[k] ;
              lib.Oid = atoi( infostring.c_str() );
              infostring = "" ;
            } // if
	        else if ( tabcount == 2 ) {
              for ( k = k + 1 ; data[k] != '\t' ; k++ ) infostring = infostring + data[k] ;
              lib.Arr = atoi( infostring.c_str() );
              infostring = "" ;
            } // else if
            else if ( tabcount == 3 ) {
              for ( k = k + 1 ;data[k] != '\t' ; k++ ) infostring = infostring + data[k] ;
              lib.Dur = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 4 ) {
              for ( k = k + 1 ; k <= data.size() ; k++ ) 
			    infostring = infostring + data[k] ;
              lib.Time = atoi( infostring.c_str() );
              infostring = "" ;
            } // else if

      	}
	  } // DealDat

void sort(int);
void saveFile( string &name ); // save all records into a file
void saveFile2( string &name ); // save all records into a file
void saveFile3( string &name ); // save all records into a file
void DealN( string &name ); // �B�z�ɦW
void DealN2( string &name );
void Judgedat(int lows, int lowg, int lowt, string &tempdat);//�ĤG�D�P�_�ǥͼƩM���~�� 
void mission1( int &stop );
void mission2( int & index );
void mission3( int & index );
void mission4( int & index );
	vector<cT> list(0);
    vector<cT> list1(0);
    vector<ablist> abortlist(0);
    vector<ablist> timeoutlist(0);    
    vector<ablist> complete(0) ;
    vector<ablist2> abortlist2(0);
    vector<ablist2> timeoutlist2(0);    
    vector<ablist2> complete2(0) ;
void AllClear(){
 list.clear();
 list1.clear();
 abortlist.clear();
 timeoutlist.clear();    
 complete.clear() ;
 abortlist2.clear();
    timeoutlist2.clear();    
    complete2.clear() ;
}    
int main(int argc, char** argv) {
    int command = -1;
    int stop = -1;
    while ( command != 0 ) {
	  cout << endl << "**** Simulate FIFO Queues by SQF *****";
      cout << endl << "* 0. Quit                            *";
      cout << endl << "* 1. Sort a file                     *";
      cout << endl << "* 2. Simulate one FIFO queue         *";
      cout << endl << "* 3. Simulate two queues by SQF      *";
      cout << endl << "* 4. Simulate multiple queues by SQF *";
      cout << endl << "**************************************";
      cout << endl << "Input a command(0, 1, 2, 3, 4): ";
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) mission1( command );
      else if ( command == 2 ) mission2( command );
      else if ( command == 3 ) mission3( command );
      else if ( command == 4 ) mission4( command );

      AllClear();
	} // while
	return 0;
}

void Shellsort( int len) {
	
  int i = 1 ; 
  sort( len) ;

	
} // shellsort()

void mission1( int &stop ) {
	double start1,end1;
	double start2,end2;
	double start3,end3;
	string name;
	ifstream fin;
    int len = 0 ;
	int i = 1;
	int j = 1 ;
	int index = 0;
	cout << "Input a file number (e.g., 401, 402, 403, ...):" ;
	cin >> name;
    DealN( name );// �B�zINPUT
	fin.open( name.c_str() );
    if ( !fin ) {
      return ;
	}
	start1 = clock();
	string tempdat;
    getline(fin,tempdat); // �h�����D
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
	  DealDat( tempdat ) ;// input data to class
      list.push_back(lib); // add data to last one;
	}
    cout << "  	 OID	Arrival	Duration	TimeOut" << endl ;
	while ( i < list.size() + 1 ) { // �L�X���Ƨǫe��input.txt 
		cout << "(" << i << ")" << "	" << list[i-1].Oid << "	" << list[i-1].Arr << "	" << list[i-1].Dur << "	" << list[i-1].Time << endl ;
	    i++ ;
	}
    end1 = clock();
    len = list.size() ;
    start2 = clock();
    sort( len) ;
    end2 = clock() ;
    start3 = clock();   
    saveFile( name ); // sort Data
    end3 = clock() ;
    cout << "Reading data: " <<  1000 * (end1 - start1) / CLOCKS_PER_SEC << "ms" << endl << endl;
    cout << "Sorting data: " <<  1000 * (end2 - start2) / CLOCKS_PER_SEC << "ms"  << endl << endl;
    cout << "Writing data: " <<  1000 * (end3 - start3) / CLOCKS_PER_SEC << "ms"  << endl << endl;

    

    cout << "  	 OID	Arrival	Duration	TimeOut" << endl ;
    while ( j < list.size() + 1 ) { // �L�X�Ƨǫ᪺input.txt 
	  cout << "(" << j << ")" << "	" << list[j-1].Oid << "	" << list[j-1].Arr << "	" << list[j-1].Dur << "	" << list[j-1].Time << endl ;
      j++ ;
    }	 
}

void mission2( int &index ) {
	int m = 0;
	int n = 0;
	bool first = true ;
	bool inwhile = false ;
	int b = 0;
	int last = 0;
	int a = 0 ;
	Chef cheforder[index - 1];
	index = index - 2 ; 	
	string name;
	ifstream fin;
    int len = 0 ;
	int i = 1;
	cout << "Input a file number (e.g., 401, 402, 403, ...):" ;
	cin >> name;
    DealN2( name );// �B�zINPUT
	fin.open( name.c_str() );    
    if ( !fin ) {
      return ;
	}    
	string tempdat;
    getline(fin,tempdat); // �h�����D
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
	  DealDat( tempdat ) ;// input data to class
      list1.push_back(lib); // add data to last one;
	}    
//---------------------------------------------------------------------------------------------------
    int currenttime = 0 ;  // ��s��U�ɨ� 
      // �@��chef�����p 
      while ( a < list1.size() ) { //  �B�z�@���@���q�� 
          if ( cheforder[index].standby ) { // �p�v�Y���m �N�q���ƶǹL�h
          	cheforder[index].Current = list1[a] ; 
            currenttime = cheforder[index].Current.Arr ;
            for ( a = 1 ; a < 4 ; a++ )
		      cheforder[index].waittinglist.push(list1[a]) ; //�x�s��C 
          	cheforder[index].standby = false ;
          	a--;
		  }
		  else {     //�p�v�D���m���A   
			    if ( list1[a].Arr < currenttime && !first) { // �s���q���F�Y�p�v�|��������e�q��
			      abortlist.push_back(temp) ;     //���������q�� ��Jvector�s���������q���T
			      abortlist[m].Oid = list1[a].Oid ;
			      abortlist[m].Delay = 0 ;
			      abortlist[m].Abort = list1[a].Arr ; 
			      m++;
			    }
		  	    else {   // �s���q���F�p�v�w������e�q��
		  	      if ( currenttime >= cheforder[index].Current.Time ) {
			        abortlist.push_back(temp) ;     //���������q�� ��Jvector�s���������q���T
			        abortlist[m].Oid = cheforder[index].Current.Oid ;
			        abortlist[m].Delay = currenttime - cheforder[index].Current.Arr ;
			        abortlist[m].Abort = currenttime ; 
			        m++;		  	      	
				  }
		  	      else if ( currenttime + cheforder[index].Current.Dur > cheforder[index].Current.Time ) { //������e�q���o�{�W�L�ɶ��F  �s�J�W��vector 
			        currenttime = currenttime + cheforder[index].Current.Dur ;
		  	        timeoutlist.push_back(temp) ;
		  	        timeoutlist[n].Oid =  cheforder[index].Current.Oid ;
			        timeoutlist[n].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
			        timeoutlist[n].Abort = currenttime; 
				 	first = false ;              // �����ɨ� 
                    n++;
			      }
			      else {   // �Ǯɧ����q�� �s�J����vector 
                    currenttime = currenttime + cheforder[index].Current.Dur ;
			    	complete.push_back(temp) ;
			    	complete[b].Oid = cheforder[index].Current.Oid ;
			    	complete[b].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
			    	complete[b].Abort = currenttime ;
			    	first = false ;
			    	b++ ;
			       }
			        cheforder[index].Current = cheforder[index].waittinglist.front(); // �N��C�Ĥ@���q���ܦ��p�v��e���u�@	  
			        cheforder[index].waittinglist.pop();	// ������C�Ĥ@���q�� 
			        while ( cheforder[index].waittinglist.size() < 3 && a < list1.size() ) {
			          inwhile = true;
			          if ( currenttime > list1[a].Arr ) {
					    abortlist.push_back(temp) ;     //���������q�� ��Jvector�s���������q���T
			            abortlist[m].Oid = list1[a].Oid ;
			            abortlist[m].Delay = 0 ;
			            abortlist[m].Abort = list1[a].Arr ; 
			            m++;
				      }
					  else  cheforder[index].waittinglist.push(list1[a]) ; //�x�s��C 
					  a++;
				    } // while 
				    if ( inwhile ) {
				      a--;
				      inwhile = false;
			     	} // if
	     	    
		  	 } 
		  }   
		  a++; 
       } // while  
        // �B�z���Ҧ��q�� �B�z�Ѿl�d�b��C���� 
	   if ( currenttime >= cheforder[index].Current.Time ) {
	      abortlist.push_back(temp) ;     //���������q�� ��Jvector�s���������q���T
	      abortlist[m].Oid = cheforder[index].Current.Oid ;
	      abortlist[m].Delay = currenttime - cheforder[index].Current.Arr ;
	      abortlist[m].Abort = currenttime ; 
	      m++;		  	      	
	    }
        else if ( currenttime + cheforder[index].Current.Dur > cheforder[index].Current.Time ) { // �p�v�B�z����e�q�� �o�{�W�� 
           currenttime = currenttime + cheforder[index].Current.Dur ;
	 	   timeoutlist.push_back(temp) ;
       	   timeoutlist[n].Oid =  cheforder[index].Current.Oid ;
	  	   timeoutlist[n].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
		   timeoutlist[n].Abort = currenttime;               // �����ɨ� 
           n++;
	     }
	     else {   // �Ǯɧ����q�� �s�J����vector 
		   complete.push_back(temp) ;
		   currenttime = currenttime + cheforder[index].Current.Dur ;
	 	   complete[b].Oid = cheforder[index].Current.Oid ;
		   complete[b].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
		   complete[b].Abort = currenttime ;
		   b++ ;
	     }
        while ( cheforder[index].waittinglist.size() > 0  ) {  
           cheforder[index].Current = cheforder[index].waittinglist.front(); // �N��C�Ĥ@���q���ܦ��p�v��e���u�@	  
	       cheforder[index].waittinglist.pop();	// ������C�Ĥ@���q��    
          if ( currenttime >= cheforder[index].Current.Time ) {
	        abortlist.push_back(temp) ;     //���������q�� ��Jvector�s���������q���T
	        abortlist[m].Oid = cheforder[index].Current.Oid ;
	        abortlist[m].Delay = currenttime - cheforder[index].Current.Arr ;
	        abortlist[m].Abort = currenttime ; 
	        m++;		  	      	
	      }
	      else if ( currenttime + cheforder[index].Current.Dur > cheforder[index].Current.Time ) { // �p�v�B�z����e�q�� �o�{�W�� 
	        currenttime = currenttime + cheforder[index].Current.Dur ;
	 	    timeoutlist.push_back(temp) ;
       	    timeoutlist[n].Oid =  cheforder[index].Current.Oid ;
	  	    timeoutlist[n].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
		    timeoutlist[n].Abort = currenttime;               // �����ɨ� 
            n++;
	      }
	      else {   // �Ǯɧ����q�� �s�J����vector 
		    complete.push_back(temp) ;
	   	    currenttime = currenttime + cheforder[index].Current.Dur ;
	 	    complete[b].Oid = cheforder[index].Current.Oid ;
		    complete[b].Delay = currenttime - cheforder[index].Current.Arr - cheforder[index].Current.Dur ;
		    complete[b].Abort = currenttime ;
		    b++ ;
	      }

        } //while
	   

  saveFile2( name ) ;
} // mission2()
//---------------------------------------------2�Ӽp�v----------------------------------------------------------------------------                 

void mission3( int &index ) {
	int m = 0;
	int o = 0;
	int l = 0;
	index--;
	Chef cheforder[index];	
	string name;
	int smallest = 3;
	int indexOfChef = -1;
	ifstream fin;
  	bool placed = false ;
  	bool have = false ;
	cout << "Input a file number (e.g., 401, 402, 403, ...):" ;
	cin >> name;
    DealN2( name );// �B�zINPUT
	fin.open( name.c_str() );    
    if ( !fin ) {
      return ;
	}    
	string tempdat;
    getline(fin,tempdat); // �h�����D
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
	  DealDat( tempdat ) ;// input data to class
      list1.push_back(lib); // add data to last one;
	}    
	int currenttime = 0 ;
	//----------------------------------------�}�l�B�z�q�� ------------------------------------------------------- 
	for ( int i = 0 ; i < list1.size() ; i ++ ) {
		placed = false ;
		if ( currenttime == 0 ) { //�]�w��l�� 0 
			for ( int r = 0 ; r < index ; r ++ ) {
				cheforder[r].currenttime = 0 ;
			}
		}
		for ( int a = 0 ; a < index ; a ++ ) {  //��s��e�ɨ� 
			if ( cheforder[a].currenttime < list1[i].Arr && cheforder[a].Current.Oid == 0 ) {
				cheforder[a].currenttime = list1[i].Arr ;
			}
		}
		currenttime = list1[i].Arr ; //�]�w��e�ɨ� 
		
		for ( int n = 0 ; n < index ; n++ ){
			if( cheforder[n].Current.Oid != 0 ) {
				have = true ;	
				if ( ((currenttime >= cheforder[n].Current.Time) || ( currenttime >= cheforder[n].Current.Dur + cheforder[n].currenttime )) ) {				
					while(((currenttime >= cheforder[n].Current.Time) || ( currenttime >= cheforder[n].Current.Dur + cheforder[n].currenttime )) && have ) {
						if ( cheforder[n].currenttime >= cheforder[n].Current.Time ) {  //��e�q��W�L�ɶ�  ���� 
							abortlist2.push_back(temp2) ;
							abortlist2[m].Oid = cheforder[n].Current.Oid ;
							abortlist2[m].Cid = n + 1 ;
							abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
							abortlist2[m].Abort = cheforder[n].currenttime ;
							m++;
						}						
						// ��e�q��|���W�L�ɶ� 
						else if ( cheforder[n].currenttime + cheforder[n].Current.Dur > cheforder[n].Current.Time ) {  // �B�z����o�{�W�� 
							timeoutlist2.push_back(temp2) ;
							timeoutlist2[o].Oid = cheforder[n].Current.Oid ;
							timeoutlist2[o].Cid = n + 1 ;
							timeoutlist2[o].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
							timeoutlist2[o].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
							o++;							
							cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ� 
						}
						else {    // �Ǯɧ����q�� 
							cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ� 
		                    complete2.push_back(temp2) ;
	 	     				complete2[l].Oid = cheforder[n].Current.Oid ;
	 	     				complete2[l].Cid = n + 1 ;
		    				complete2[l].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
		    				complete2[l].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
						}

						
						
						cheforder[n].Current.Oid = 0 ;
						
						if ( ! cheforder[n].waittinglist.empty() ) { //�Y��C�٦��q�� �N��C�̤W����J��e�q�� 
							
							cheforder[n].Current = cheforder[n].waittinglist.front() ;
							cheforder[n].waittinglist.pop() ; //�R����C�Ĥ@�� 
							have = true ;
							
						}
						else have = false ;
					}
				}
			}
		}


		// search for free chef
		for ( int j = 0 ; j < index && ! placed ; j ++ ) { // ��Ŷ����p�v �����s�q�� 
			if( cheforder[j].Current.Oid == 0 ) {
				cheforder[j].Current = list1[i] ;
				cheforder[j].currenttime = list1[i].Arr ;
				placed = true ;
			}
		}

		// search for the smallest queue
		for ( int k = 0 ; k < index && ! placed ; k ++ ) { // ���C�̤p���p�v 
			if(cheforder[k].waittinglist.size() < smallest) {
				indexOfChef = k ;
				smallest = cheforder[k].waittinglist.size() ;
			}
		}


		if(!placed ) {
			
			if ( smallest == 3 ) {  //��C�Һ�   �����q�� 
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = list1[i].Oid ;
				abortlist2[m].Cid = 0 ;
				abortlist2[m].Delay = 0 ;
				abortlist2[m].Abort = list1[i].Arr ;
				m++;
				
			}
			else { //��C�S��  �N�s���@���q���J��C 
				cheforder[indexOfChef].waittinglist.push(list1[i]) ;
			}			
			
		}

		
		indexOfChef = -1 ;
		smallest = 3 ;
		
	}
	//�q�浲�� �B�z��e�M��C�����q�� 
	
	for (int n = 0 ; n < index ; n++) {
		
		have = false ; 
		if ( cheforder[n].Current.Oid != 0 ) have = true ;		
		while ( have ) {							
			if ( cheforder[n].currenttime > cheforder[n].Current.Time ) { 
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = cheforder[n].Current.Oid ;
				abortlist2[m].Cid = n+1 ;
				abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				abortlist2[m].Abort = cheforder[n].currenttime ;
				m++;				
			}
			else if ( cheforder[n].currenttime == cheforder[n].Current.Time ) {
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = cheforder[n].Current.Oid ;
				abortlist2[m].Cid = n+1 ;
				abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				abortlist2[m].Abort = cheforder[n].currenttime ;
				m++;
			}
			else if ( cheforder[n].currenttime + cheforder[n].Current.Dur > cheforder[n].Current.Time ) { 
                timeoutlist2.push_back(temp2) ;
				timeoutlist2[o].Oid = cheforder[n].Current.Oid ;
				timeoutlist2[o].Cid = n+1 ;
				timeoutlist2[o].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				timeoutlist2[o].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
				o++;				
				cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ�		
			}
			else {
				cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ�
		        complete2.push_back(temp2) ;
	 	     	complete2[l].Oid = cheforder[n].Current.Oid ;
	 	     	complete2[l].Cid = n + 1 ;
		    	complete2[l].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
		    	complete2[l].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;				
		    	l++;
			}
			cheforder[n].Current.Oid = 0 ;
			if ( ! cheforder[n].waittinglist.empty() ) {
				
				cheforder[n].Current = cheforder[n].waittinglist.front() ;
				cheforder[n].waittinglist.pop() ;
				have = true ;		
			}
			else have = false ;		
		}		
			
	}
		
    saveFile3( name ) ;
} // mission3()


void mission4( int &index ) {
	int m = 0;
	int o = 0;
	int l = 0;
	index = index - 2;
	string name;
	int smallest = 3;
	int indexOfChef = -1;
	ifstream fin;
  	bool placed = false ;
  	bool have = false ;
	cout << "Input a file number (e.g., 401, 402, 403, ...):" ;
	cin >> name;
	cout << "Input the number of queues: " ;
    cin >> index;
    Chef cheforder[index];
    DealN2( name );// �B�zINPUT
	fin.open( name.c_str() );    
    if ( !fin ) {
      return ;
	}    
	string tempdat;
    getline(fin,tempdat); // �h�����D
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
	  DealDat( tempdat ) ;// input data to class
      list1.push_back(lib); // add data to last one;
	}    
	int currenttime = 0 ;
	//----------------------------------------�}�l�B�z�q�� ------------------------------------------------------- 
	for ( int i = 0 ; i < list1.size() ; i ++ ) {
		placed = false ;
		if ( currenttime == 0 ) { //�]�w��l�� 0 
			for ( int r = 0 ; r < index ; r ++ ) {
				cheforder[r].currenttime = 0 ;
			}
		}
		for ( int a = 0 ; a < index ; a ++ ) {  //��s��e�ɨ� 
			if ( cheforder[a].currenttime < list1[i].Arr && cheforder[a].Current.Oid == 0 ) {
				cheforder[a].currenttime = list1[i].Arr ;
			}
		}
		currenttime = list1[i].Arr ; //�]�w��e�ɨ� 
		
		for ( int n = 0 ; n < index ; n++ ){
			if( cheforder[n].Current.Oid != 0 ) {
				have = true ;	
				if ( ((currenttime >= cheforder[n].Current.Time) || ( currenttime >= cheforder[n].Current.Dur + cheforder[n].currenttime )) ) {				
					while(((currenttime >= cheforder[n].Current.Time) || ( currenttime >= cheforder[n].Current.Dur + cheforder[n].currenttime )) && have ) {
						if ( cheforder[n].currenttime >= cheforder[n].Current.Time ) {  //��e�q��W�L�ɶ�  ���� 
							abortlist2.push_back(temp2) ;
							abortlist2[m].Oid = cheforder[n].Current.Oid ;
							abortlist2[m].Cid = n + 1 ;
							abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
							abortlist2[m].Abort = cheforder[n].currenttime ;
							m++;
						}						
						// ��e�q��|���W�L�ɶ� 
						else if ( cheforder[n].currenttime + cheforder[n].Current.Dur > cheforder[n].Current.Time ) {  // �B�z����o�{�W�� 
							timeoutlist2.push_back(temp2) ;
							timeoutlist2[o].Oid = cheforder[n].Current.Oid ;
							timeoutlist2[o].Cid = n + 1 ;
							timeoutlist2[o].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
							timeoutlist2[o].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
							o++;							
							cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ� 
						}
						else {    // �Ǯɧ����q�� 
							cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ� 
		                    complete2.push_back(temp2) ;
	 	     				complete2[l].Oid = cheforder[n].Current.Oid ;
	 	     				complete2[l].Cid = n + 1 ;
		    				complete2[l].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
		    				complete2[l].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
						}

						
						
						cheforder[n].Current.Oid = 0 ;
						
						if ( ! cheforder[n].waittinglist.empty() ) { //�Y��C�٦��q�� �N��C�̤W����J��e�q�� 
							
							cheforder[n].Current = cheforder[n].waittinglist.front() ;
							cheforder[n].waittinglist.pop() ; //�R����C�Ĥ@�� 
							have = true ;
							
						}
						else have = false ;
					}
				}
			}
		}


		// search for free chef
		for ( int j = 0 ; j < index && ! placed ; j ++ ) { // ��Ŷ����p�v �����s�q�� 
			if( cheforder[j].Current.Oid == 0 ) {
				cheforder[j].Current = list1[i] ;
				cheforder[j].currenttime = list1[i].Arr ;
				placed = true ;
			}
		}

		// search for the smallest queue
		for ( int k = 0 ; k < index && ! placed ; k ++ ) { // ���C�̤p���p�v 
			if(cheforder[k].waittinglist.size() < smallest) {
				indexOfChef = k ;
				smallest = cheforder[k].waittinglist.size() ;
			}
		}


		if(!placed ) {
			
			if ( smallest == 3 ) {  //��C�Һ�   �����q�� 
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = list1[i].Oid ;
				abortlist2[m].Cid = 0 ;
				abortlist2[m].Delay = 0 ;
				abortlist2[m].Abort = list1[i].Arr ;
				m++;
				
			}
			else { //��C�S��  �N�s���@���q���J��C 
				cheforder[indexOfChef].waittinglist.push(list1[i]) ;
			}			
			
		}

		
		indexOfChef = -1 ;
		smallest = 3 ;
		
	}
	//�q�浲�� �B�z��e�M��C�����q�� 
	
	for (int n = 0 ; n < index ; n++) {
		
		have = false ; 
		if ( cheforder[n].Current.Oid != 0 ) have = true ;		
		while ( have ) {							
			if ( cheforder[n].currenttime > cheforder[n].Current.Time ) { 
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = cheforder[n].Current.Oid ;
				abortlist2[m].Cid = n+1 ;
				abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				abortlist2[m].Abort = cheforder[n].currenttime ;
				m++;				
			}
			else if ( cheforder[n].currenttime == cheforder[n].Current.Time ) {
				abortlist2.push_back(temp2) ;
				abortlist2[m].Oid = cheforder[n].Current.Oid ;
				abortlist2[m].Cid = n+1 ;
				abortlist2[m].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				abortlist2[m].Abort = cheforder[n].currenttime ;
				m++;
			}
			else if ( cheforder[n].currenttime + cheforder[n].Current.Dur > cheforder[n].Current.Time ) { 
                timeoutlist2.push_back(temp2) ;
				timeoutlist2[o].Oid = cheforder[n].Current.Oid ;
				timeoutlist2[o].Cid = n+1 ;
				timeoutlist2[o].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
				timeoutlist2[o].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;
				o++;				
				cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ�		
			}
			else {
				cheforder[n].currenttime = cheforder[n].currenttime + cheforder[n].Current.Dur ; // ��s�ɨ�
		        complete2.push_back(temp2) ;
	 	     	complete2[l].Oid = cheforder[n].Current.Oid ;
	 	     	complete2[l].Cid = n + 1 ;
		    	complete2[l].Delay = cheforder[n].currenttime - cheforder[n].Current.Arr ;
		    	complete2[l].Abort = cheforder[n].currenttime + cheforder[n].Current.Dur ;				
		    	l++;
			}
			cheforder[n].Current.Oid = 0 ;
			if ( ! cheforder[n].waittinglist.empty() ) {
				
				cheforder[n].Current = cheforder[n].waittinglist.front() ;
				cheforder[n].waittinglist.pop() ;
				have = true ;		
			}
			else have = false ;		
		}		
			
	}
		
    saveFile3( name ) ;
} // mission4()

void saveFile( string & name ) { // save all records into a file
  string num;
  string co;
  if ( name[0] == 'i') {
  	for (int i = 0; i < 3 ; i++ ) num = num + name.at(i + 5);
  	co = "sort" + num + ".txt";
  }
  else co = name;
  ofstream fout( co.c_str() );
  fout << "OID	Arrival	Duration	TimeOut" << endl; 
  for ( int i = 0; i < list.size() ; i++ ) fout << list[i].Oid << "	" << list[i].Arr << "	" << list[i].Dur << "	" << list[i].Time << endl ;
}

void saveFile2( string & name ) { // save all records into a file
  string num;
  string co;
  float a , t , l ;
  int lose = 0 ;
  int delay = 0;
  if ( name[0] == 's') {
  	for (int i = 0; i < 3 ; i++ ) num = num + name.at(i + 4);
  	co = "one" + num + ".txt";
  }
  else co = name;
  ofstream fout( co.c_str() );
  fout << "	[Done List]" << endl ; 
  fout << "	OID	Delay	Departure" << endl ;
  for ( int i = 0; i < complete.size() ; i++ ) fout << "[" << i+1 << "]	" << complete[i].Oid << "	" << complete[i].Delay << "	" << complete[i].Abort << endl; //�x�s��C 
  /*fout << "[Total Delay]" << endl ;
  for ( int i = 0; i < timeoutlist.size() ; i++ ) delay = delay + timeoutlist[i].Delay ;
  for ( int i = 0; i < abortlist.size() ; i++ )  delay = delay + abortlist[i].Delay ;
  fout << delay << " min." << endl ;
  fout << "[Failure Percentage]" << endl ;
  a = abortlist.size();
  t = timeoutlist.size();
  l = list1.size() ;
  fout << setprecision(4) << 100 * ( a + t ) / l << " %" << endl ;*/
}

void saveFile3( string & name ) { // save all records into a file
  string num;
  string co;
  float a , t , l ;
  float num123 = 0.0;
  int lose = 0 ;
  int delay = 0;
  if ( name[0] == 's') {
  	for (int i = 0; i < 3 ; i++ ) num = num + name.at(i + 4);
  	co = "more" + num + ".txt";
  }
  else co = name;
  ofstream fout( co.c_str() );
  fout << "	[Abort List]" << endl ;
  fout << "	OID	CID	Delay	Abort" << endl; 
  for ( int i = 3; i < abortlist2.size() ; i++ ) fout << "[" << i-2 << "]	" << abortlist2[i].Oid << "	" << abortlist2[i].Cid << "	" << abortlist2[i].Delay << "	" << abortlist2[i].Abort << endl; //�x�s��C 
  fout << "	[Timeout List]" << endl ; 
  fout << "	OID	CID	Delay	Departure" << endl ;
  for ( int i = 0; i < timeoutlist2.size() ; i++ ) fout << "[" << i+1 << "]	" << timeoutlist2[i].Oid << "	" << timeoutlist2[i].Cid << "	" << timeoutlist2[i].Delay << "	" << timeoutlist2[i].Abort << endl; //�x�s��C 
  fout << "[Total Delay]" << endl ;
  for ( int i = 0; i < timeoutlist2.size() ; i++ ) delay = delay + timeoutlist2[i].Delay ;
  for ( int i = 3; i < abortlist2.size() ; i++ )  delay = delay + abortlist2[i].Delay ;
  fout << delay << " min." << endl ;
  fout << "[Failure Percentage]" << endl ;
  a = abortlist2.size() - 3 ;
  if ( a <= num123 ){
  	cout << "in" ;
    a = 0;
  } 
  t = timeoutlist2.size();
  cout << a << endl ;
  cout << timeoutlist2.size() << endl ;
  cout << list1.size() << endl ; 
  l = list1.size() ;
  fout << setprecision(4) << 100 * ( a + t ) / l << " %" << endl ;
}

void DealN( string & name ){
	string temp;
    if ( name.at(0) >= '0' && name.at(0) <= '9' && name.at(1) >= '0' && name.at(1) <= '9' ) {
	  temp = "input" + name + ".txt";
	  name = temp;
    }

}

void DealN2( string &name ){
	string temp;
    if ( name.at(0) >= '0' && name.at(0) <= '9' && name.at(1) >= '0' && name.at(1) <= '9' ) {
	  temp = "sort" + name + ".txt";
	  name = temp;
    }
}
// --------------------------------------------------------------------------------------------------------------
void sort( int len ) {
    int gap;
    int i, j;
    for(gap = len / 2; gap > 0; gap = gap / 2) {
        int begin;
        for(begin = 0; begin < gap; begin++) { 
          for(i = begin + gap; i < len; i = i + gap ) { 
            for(j = i - gap; j >= begin ; j = j - gap) { 
              if ( list[j].Arr > list[j + gap].Arr ) 
                swap(list[j], list[j + gap]); 
              if( list[j].Arr == list[j + gap].Arr )
                if ( list[j].Oid > list[j + gap].Oid ) 
	              swap(list[j], list[j + gap]); 	   
            }
          } 
        }
    }
}


