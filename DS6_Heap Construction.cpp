//系級: 資訊二甲 10627134 許寓翔 資訊二甲 10627149 許?橋 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
using namespace std;

int gnum = 1;
int gright = false;
class Info{
	private :
       string rawR; // raw data of one record
       int ID; //唯一序號 
       int SID; // 學校代碼 
       string cName; // college name
       int DID; // 科系代碼
       string dName; // 科系名稱 
       string school; // 日間進修 
       int level; // 等級別 
       int sNo;// 學生數 
       int tNo; // 教師數 
       int gNo; // 上學年度畢業生數
       string cityName; // 縣市名稱 
       string Dif; // 體系別 
	public :
	  Info *Left;
	  Info *Right;
	  Info *Parent;
	  void newsch( string sch ) {
  		rawR = sch;
	  }
	  string getDat(){
	  	return rawR;
	  }
	  int getID(){
      	return ID;
	  }
	  int getSID(){
      	return SID;
	  }
      string getcName(){
	  	return cName;
      }
      int getDID(){
	  	return DID;
      }
      string getdName(){
      	return dName;
	  }
	  string getschool(){
      	return school;
	  }
	  int getlevel(){
      	return level;
	  }
	  int getsNo(){
      	return sNo;
	  }
	  int gettNo(){
      	return tNo;
	  }
	  int getgNo(){
      	return gNo;
	  }
	  string getcityName(){
      	return cityName;
	  }
	  string getDif(){
	    return Dif;
      }
      int setsNo( int num ){
      	sNo = num;
	  }
	  void DealDat( string data );
};


class Tree{
    private:
  	  Info binary;
  	  
    public:
	  vector<Info> list;
	  vector<Info> deap;
	  vector<Info> maxlist;
	  vector<Info> ldeap;
	  vector<Info> rdeap;
	  void mission1();
      void mission2();
      void BuildMaxHeap();
      void CheckMaxHeap();
      void CheckMinHeap();
      bool Checkminmax( int curnum);
      void BuildDeap();
      void Sortlist( int &temp );
      void InputFile( string & name, string & fileNum );
};

void saveFile( string &name , char c); // save all records into a file
void DealN( string &name ); // 處理檔名
   
int main(int argc, char** argv) {
	Tree Sch;
	gnum = 1;
    int command = -1;
    while ( command != 0 ) {
	  cout << endl << "***** Heap Construction *****";
      cout << endl << "* 0. QUIT                   *";
      cout << endl << "* 1. Build a max heap       *";
      cout << endl << "* 2. Build a Deap           *";
      cout << endl << "*************************************";
      cout << endl << "Input a choice(0, 1, 2): ";
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) Sch.mission1();
      else if ( command == 2 ) Sch.mission2();
      gnum = 1;
      
    } // while
	return 0;
}


void Tree::mission1() { 
	string name, fileNum;
	ifstream fin;
	int height = 1,max = 1;
	cout << "Input a file number,[0] quit: ";
	cin >> name;
	list.push_back(binary); // add data to last one;
	InputFile( name, fileNum );
	BuildMaxHeap();
	int left = 0;
	for ( int i = 1; i < list.size(); i = i * 2 ) left = i;
	cout << "root: [" << list[1].getID()  << "] " <<  list[1].getsNo() << endl;
	cout << "bottom: [" << list[list.size() - 1].getID()  << "] " <<  list[list.size() - 1].getsNo() << endl;
	cout << "leftmost bottom: [" << list[left].getID()  << "] " <<  list[left].getsNo() << endl;
}


void Tree::mission2() { 
	string name, fileNum;
	ifstream fin;
	int height = 1,max = 1, temp = 0;
	cout << "Input a file number,[0] quit: ";
	cin >> name;
	list.push_back(binary); // add data to last one;
	InputFile( name, fileNum );
	for ( int i = 0; i < list.size(); i++ ) deap.push_back(list[i]);
	Sortlist( temp );
	int left = 0;
	if (gright)
	{
		cout << "bottom: [" << rdeap[rdeap.size() - 1].getID()  << "] " <<  rdeap[rdeap.size() - 1].getsNo() << endl;	
	}	
	else
	{
		cout << "bottom: [" << ldeap[ldeap.size() - 1].getID()  << "] " <<  ldeap[ldeap.size() - 1].getsNo() << endl;
	}
	for ( int i = 1; i < ldeap.size(); i = i * 2 ) left = i;
	cout << "leftmost bottom: [" << ldeap[left].getID()  << "] " <<  ldeap[left].getsNo() << endl;
	
}


void Tree::BuildMaxHeap(){
	int root = 1, left = 2*root, right = 2*root + 1;
	for ( root = 1; root < list.size(); ) 
	{
		if ( left < list.size() ) //在左節點新增 
		{
			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( list[i].getsNo() > list[i / 2].getsNo() ) swap(list[i], list[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < list.size() ) //在右節點新增 
		{
		    for ( int i = right; i != 1; i = i / 2 ) 
			{
				if ( list[i].getsNo() > list[i / 2].getsNo() ) swap(list[i], list[i / 2]);
				else break;
			}
	    }
		else break;
		root++;
		left = 2*root; 
		right = 2*root + 1;
	}
}

void Tree::CheckMinHeap(){
	int root = 1, left = 2*root, right = 2*root + 1;
	for ( root = 1; root < ldeap.size(); ) 
	{
		if ( left < ldeap.size() ) //在左節點新增 
		{

			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( ldeap[i].getsNo() < ldeap[i / 2].getsNo() ) swap(ldeap[i], ldeap[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < ldeap.size() ) //在右節點新增 
		{
		    for ( int i = right; i != 1; i = i / 2 ) 
			{
				if ( ldeap[i].getsNo() < ldeap[i / 2].getsNo() ) swap(ldeap[i], ldeap[i / 2]);
				else break;
			}
	    }
		else break;
		root++;
		left = 2*root; 
		right = 2*root + 1;
	}
}

void Tree::CheckMaxHeap(){
	int root = 1, left = 2*root, right = 2*root + 1;
	for ( root = 1; root < rdeap.size(); ) 
	{
		if ( left < rdeap.size() ) //在左節點新增
		{
			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( rdeap[i].getsNo() > rdeap[i / 2].getsNo() ) swap(rdeap[i], rdeap[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < rdeap.size() ) //在右節點新增
		{
		    for ( int i = right; i != 1; i = i / 2 ) 
			{
				if ( rdeap[i].getsNo() > rdeap[i / 2].getsNo() ) swap(rdeap[i], rdeap[i / 2]);
				else break;
			}
	    }
		else break;
		root++;
		left = 2*root; 
		right = 2*root + 1;
	}
}


void Tree::Sortlist( int &temp ){ //vector分別放入左子樹vector和右子樹vector 
	int root = 1, total = 0;
	ldeap.push_back(list[0]);//將第0項空出來 不放東西 
	rdeap.push_back(list[0]);//將第0項空出來 不放東西 
	for( total = 0; total < list.size() - 1; root = root * 2 ) //vector是否全部讀出 
	{
		for( int i = root; i > 0 && total < list.size() - 1; i-- ) //放置左子樹vector 
		{
			total++;
			gright = false;
			ldeap.push_back(list[total]); // 插入一個node
			//cout << list[total].getsNo() << "\n";
			if ( ldeap[ldeap.size() - 1].getsNo() > rdeap[ ( ldeap.size() - 1 ) / 2].getsNo() && ldeap.size() != 2 )// 確認對應點的父節點否符合DEAP 規則 
			{
				swap( ldeap[ldeap.size() - 1], rdeap[ ( ldeap.size() - 1 ) / 2] );//兩個對應點交換 
				temp = ldeap[ldeap.size() - 1].getsNo();
			}
			CheckMinHeap(); // 最小堆疊
			CheckMaxHeap(); // 最大堆積
		}
		for( int i = root; i > 0 && total < list.size() - 1; i-- ) //放置右子樹vector 
		{
			total++;
			gright = true;
			rdeap.push_back(list[total]); // 插入一個node
			//cout << list[total].getsNo() << "\n";
			if ( rdeap[rdeap.size() - 1].getsNo() < ldeap[rdeap.size() - 1].getsNo() )// 確認對應點是否符合DEAP 規則 
			{
				swap( rdeap[rdeap.size() - 1], ldeap[rdeap.size() - 1] );//兩個對應點交換 
				temp = rdeap[rdeap.size() - 1].getsNo();
			}
			CheckMinHeap(); // 最小堆疊
			CheckMaxHeap(); // 最大堆積
		}
	}
	
}

void Tree::InputFile( string & name , string & fileNum ) {
	ifstream fin;
	fileNum = name;
	list.clear();
	ldeap.clear();
	rdeap.clear();
    DealN( name );// 處理INPUT
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 501,502.....[0] quit: " << endl;
		cin >> name;
		DealN( name );// 處理INPUT
		fin.open( name.c_str() );
	}
	string tempdat;
	list.push_back(binary);
	getline(fin,tempdat);// 去掉標題
	getline(fin,tempdat);
	getline(fin,tempdat);
	while ( getline(fin,tempdat) ) { // 每次讀一行
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}

}

void DealN( string & name ){
	string temp;
    if ( name.at(0) >= '0' && name.at(0) <= '9' && name.at(1) >= '0' && name.at(1) <= '9' ) {
	  temp = "input" + name + ".txt";
	  name = temp;
    }

}
void Info::DealDat( string data ) {
	  	int tabcount = 0 ;
        int tabstart = -1 ;
        int tabend = 0 ;
        string infostring = "";
      	rawR = data;
      	ID = gnum;
      	gnum++;
	  	string temp;
	  	for ( int i = 0; tabcount < 10 ; i++ ) {
	  	  if ( data[i] == '\t' ) { // 從rawR讀取資訊(sNO.gNO.cname.gname) 
            tabcount++;
			tabend = i;
			if ( tabcount == 1 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              SID = atoi( infostring.c_str() );
              infostring = "" ;
            } // if
	        else if ( tabcount == 2 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              cName = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 3 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              DID = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 4 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              dName = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 7 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              sNo = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 8 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              tNo = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 9 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              gNo = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            tabstart = tabend;
          } // if
      	}
	  } // DealDat
