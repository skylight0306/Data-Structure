#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int gnum = 1;
class mission{
	public:
		void mission1( int &stop );
		void mission2( int &stop );
		void mission3( int &stop );
		void mission4( int &stop );
};
class Info{
	typedef struct cT{
       string rawR; // raw data of one record
       string cname; // college name
       string dname; // department name
       int sNO; // number of students
       int gNO; // number of graduates
       int tNO;// teachers
       int cnameID ;
       int dnameID ;
    } collegeType;

    cT lib;
	public :
	  void newsch( string sch ) {
  		lib.rawR = sch;
	  }
	  void print() {
		cout << lib.rawR << "\n" <<endl;
	  }
	  string getDat(){
	  	return lib.rawR;
	  }
	  string getcname(){
	  	return lib.cname;
      }
      string getdname(){
	  	return lib.dname;
      }
	  int getsNO(){
	  	return lib.sNO;
	  }
	  int getgNO(){
	  	return lib.gNO;
	  }
	  int gettNO(){
	  	return lib.tNO;
	  }
	  int getcnameID(){
	  	return lib.cnameID;
	  }
	  int getdnameID(){
	  	return lib.dnameID;
	  }
	  
	  void DealDat( string data ) {
	  	int tabcount = 0 ;
        int tabstart = -1 ;
        int tabend = 0 ;
        string infostring = "";
      	lib.rawR = data;
      	lib.ID = gnum;
      	gnum++;
	  	string temp;
	  	for ( int i = 0; tabcount < 10 ; i++ ) {
	  	  if ( data[i] == '\t' ) { // 從rawR讀取資訊(sNO.gNO.cname.gname) 
            tabcount++;
			tabend = i;
			if ( tabcount == 1 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              lib.cnameID = atoi( infostring.c_str() );
              infostring = "" ;
            } // if
	        else if ( tabcount == 2 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              lib.cname = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 3 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              lib.dnameID = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 4 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              lib.dname = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 7 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              lib.sNO = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 8 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              lib.tNO = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 9 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              lib.gNO = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            tabstart = tabend;
          } // if
      	}
	  } // DealDat
};


void saveFile( string &name ); // save all records into a file
void DealN( string &name ); // 處理檔名
void DealN2( string &name );
void Judgedat(int lows, int lowg, int lowt, string &tempdat);//第二題判斷學生數和畢業數 
void mission1( int &stop );
void mission2( int &stop );
void mission3( int &stop );
void mission4( int &stop );
    Info binary;
	vector<Info> list(0);
    vector<Info> list1(0);
    vector<Info> list2(0);
    
int main(int argc, char** argv) {
    int command = -1;
    int stop = -1;
    while ( command != 0 ) {
	  cout << endl << "* File Object Manipulator *";
      cout << endl << "* 0. QUIT *";
      cout << endl << "* 1. COPY (Read & Save a file)*";
      cout << endl << "* 2. FILTER (Reduce a file)   *";
      cout << endl << "* 3. MERGE (Join two files)   *";
      cout << endl << "* 4. MERGE (Join three files) *";
      cout << endl << "*****************************";
      cout << endl << "Input a choice(0, 1, 2, 3, 4): ";
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) mission1( stop );
      else if ( command == 2 ) mission2( stop );
      else if ( command == 3 ) mission3( stop );
      else if ( command == 4 ) mission4( stop );
      
      if ( stop == 0 ) return 0;
      list.clear();
      list1.clear();
      list2.clear();
    } // while
	return 0;
}

//freopen( name.c_str(), "r" , stdin );

void mission1( int &stop ) {
	string name;
	ifstream fin;
	cout << "input 201,202.....[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) {
	  stop = 0;
	  return;
    }
    DealN( name );// 處理INPUT
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) {
	      stop = 0;
	      return;
        }
		DealN( name );// 處理INPUT
		fin.open( name.c_str() );
	}
	string tempdat;
	for ( int n = 0; n < 3 ; n++ ) {// 去掉標題
		getline(fin,tempdat);
	}
	int i = 0;
	while ( getline(fin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}
    
	saveFile( name ); // copy Data

	cout << "Total number of records = " << list.size() << endl;
}

void mission2( int &stop ) {
	string name;
	ifstream fin;
	int lows = 0, lowg = 0, lowt;// 最低學生數和最低畢業生數 
	cout << "input 201,202.....[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) {
	  stop = 0;
	  return;
    }
    DealN2( name );// 處理INPUT
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) {
	      stop = 0;
	      return;
        }
		DealN2( name );// 處理INPUT
		fin.open( name.c_str() );
	}
	cout << "input a lower bound on the number of students :" ;
	cin >> lows;
	cout << "input a lower bound on the number of graduates :";
	cin >> lowg;
	cout << "input a lower bound on the number of teachers :";
	cin >> lowt;
	string tempdat;
	//cout << name << endl;
	int i = 0;
	while ( getline(fin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}
	Judgedat(lows, lowg, lowt, tempdat );//分析檔案中學生數和畢業生數 
    
	saveFile( name ); // copy Data

	cout << "Total number of records = " << list.size() << endl;
}

void mission3( int &stop ) {
	string name;
	string filename;
	string fileN, fileN2;
	ifstream fin, gin;
	int lows = 0, lowg = 0;
	cout << "input 201,202.....[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) {
	  stop = 0;
	  return;
    }
    DealN2( name );// 處理INPUT
    for (int i = 0; i < 3 ; i++ ) fileN = fileN + name[i + 4];
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) {
	      stop = 0;
	      return;
        }
		DealN2( name );// 處理INPUT
		for (int i = 0; i < 3 ; i++ ) fileN = fileN + name[i + 4];
		fin.open( name.c_str() );
	}
	string tempdat;
	while ( getline(fin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}
	
////////////////////////////////////////////////////////////////////	

	cout << "input 201,202.....[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) {
	  stop = 0;
	  return;
    }
	DealN2( name );
	for (int i = 0; i < 3 ; i++ ) fileN2 = fileN2 + name[i + 4];
	gin.open( name.c_str() );
	while ( !gin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) {
	      stop = 0;
	      return;
        }
		DealN2( name );// 處理INPUT
		for (int i = 0; i < 3 ; i++ ) fileN = fileN + name[i + 4];
		gin.open( name.c_str() );
	}
	//cout << name << endl;
	
	while ( getline(gin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list1.push_back(binary); // add data to last one;
	}
	
	for ( int i = 0 ; i < list1.size() ; i++ ) {
      for ( int j = 0 ; j < list.size() ; j++ ) {
        if ( strcmp(list1[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) {
          list.insert( list.begin()+j, list1[i]) ;
          break ;
        } // if
        if ( j == list.size() - 1 ) {
          list.insert( list.begin()+j + 1, list1[i]) ;
          break ;
        } // if
      } // for
    } // for


    for ( int i = 0 ; i < list.size() ; i++ ){
      for ( int j = 0 ; strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) != 0 ; j++ ){
        if ( strcmp(list[i].getdname().c_str(), list[j].getdname().c_str()) < 0 && strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) swap (list[i], list[j]);
      } // for
    } // for
	
	filename = "ouput" + fileN + "_" + fileN2 + ".txt" ;
    ofstream fout( filename.c_str()) ;
    for ( int i = 0; i < list.size() ; i++ ) fout << list[i].getDat() << endl;
    
    
	cout << "Total number of records = " << list.size() << endl;
}

void mission4( int &stop ){
	string name;
	string filename;
	string fileN, fileN2, fileN3;
	ifstream fin, gin, hin;
	int lows = 0, lowg = 0;
	
///////////////////////////////////////////////////////////////////
//the first file
	cout << "input 201,202.....[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) {
	  stop = 0;
	  return;
    }
    DealN2( name );// 處理INPUT
    for (int i = 0; i < 3 ; i++ ) fileN = fileN + name[i + 4];
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) {
	      stop = 0;
	      return;
        }
		DealN2( name );// 處理INPUT
		for (int i = 0; i < 3 ; i++ ) fileN = fileN + name[i + 4];
		fin.open( name.c_str() );
	}
	string tempdat;
	while ( getline(fin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}
	fin.close();
	
////////////////////////////////////////////////////////////////////	
// the second file
	cout << "input 201,202.....to second file[0] quit: " << endl;
	cin >> name;
	if (name == "0" ) return;
	DealN2( name );
	for (int i = 0; i < 3 ; i++ ) fileN2 = fileN2 + name[i + 4];
	gin.open( name.c_str() );
	while ( !gin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....to second file[0] quit: " << endl;
		cin >> name;
		if (name == "0" ) return ;
		DealN2( name );// 處理INPUT
		for (int i = 0; i < 3 ; i++ ) fileN2 = fileN2 + name[i + 4];
		gin.open( name.c_str() );
	}
	//cout << name << endl;
	
	while ( getline(gin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list1.push_back(binary); // add data to last one;
	}
	
	for ( int i = 0 ; i < list1.size() ; i++ ) {
      for ( int j = 0 ; j < list.size() ; j++ ) {
        if ( strcmp(list1[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) {
          list.insert( list.begin()+j, list1[i]) ;
          break ;
        } // if
        if ( j == list.size() - 1 ) {
          list.insert( list.begin()+j + 1, list1[i]) ;
          break ;
        } // if
      } // for
    } // for


    for ( int i = 0 ; i < list.size() ; i++ ){
      for ( int j = 0 ; strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) != 0 ; j++ ){
        if ( strcmp(list[i].getdname().c_str(), list[j].getdname().c_str()) < 0 && strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) swap (list[i], list[j]);
      } // for
    } // for
    gin.close();
    
    
////////////////////////////////////////////////////////////////
// the third file
    cout << "input 201,202.....to third file, [0] quit: " << endl;
	cin >> name;
	DealN2( name );
	for (int i = 0; i < 3 ; i++ ) fileN3 = fileN3 + name[i + 4];
	hin.open( name.c_str() );
	while ( !hin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 201,202.....[0] quit: " << endl;
		cin >> name;
		DealN2( name );// 處理INPUT
		for (int i = 0; i < 3 ; i++ ) fileN3 = fileN3 + name[i + 4];
		hin.open( name.c_str() );
	}
	while ( getline(hin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list2.push_back(binary); // add data to last one;
	}
	for ( int i = 0 ; i < list2.size() ; i++ ) {
      for ( int j = 0 ; j < list.size() ; j++ ) {
        if ( strcmp(list2[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) {
          list.insert( list.begin()+j, list2[i]) ;
          break ;
        } // if
        if ( j == list.size() - 1 ) {
          list.insert( list.begin()+j + 1, list2[i]) ;
          break ;
        } // if
      } // for
    } // for

    for ( int i = 0 ; i < list.size() ; i++ ){
      for ( int j = 0 ; strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) != 0 ; j++ ){
        if ( strcmp(list[i].getdname().c_str(), list[j].getdname().c_str()) < 0 && strcmp(list[i].getcname().c_str(), list[j].getcname().c_str()) == 0 ) swap (list[i], list[j]);
      } // for
    } // for
	hin.close();
	
	
///////////////////////////////////////////////
	
	filename = "ouput" + fileN + "" + fileN2 + "" + fileN3 +".txt" ;
    ofstream fout( filename.c_str()) ;
    for ( int i = 0; i < list.size() ; i++ ) fout << list[i].getDat() << endl;
    
    
	cout << "Total number of records = " << list.size() << endl;
}

void Judgedat( int lows,int lowg,int lowt,string & tempdat ){
	for ( int i = 0 ; i < list.size() ; i++ ){
      if ( list[i].getsNO() < lows || list[i].getgNO() < lowg || list[i].gettNO() < lowt ){
        list.erase( list.begin()+ i ) ;
        i-- ;
      } // if
    } // for
}
void saveFile( string & name ) { // save all records into a file
  string num;
  string co;
  if ( name[0] == 'i') {
  	for (int i = 0; i < 3 ; i++ ) num = num + name.at(i + 5);
  	co = "copy" + num + ".txt";
  }
  else co = name;
  ofstream fout( co.c_str() );
  for ( int i = 0; i < list.size() ; i++ ) fout << list[i].getDat() << endl;
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
	  temp = "copy" + name + ".txt";
	  name = temp;
    }
}
