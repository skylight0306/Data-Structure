//�t��: ��T�G�� 10627134 �\�J�� ��T�G�� 10627149 �\?�� 
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
       int ID; //�ߤ@�Ǹ� 
       int SID; // �ǮեN�X 
       string cName; // college name
       int DID; // ��t�N�X
       string dName; // ��t�W�� 
       string school; // �鶡�i�� 
       int level; // ���ŧO 
       int sNo;// �ǥͼ� 
       int tNo; // �Юv�� 
       int gNo; // �W�Ǧ~�ײ��~�ͼ�
       string cityName; // �����W�� 
       string Dif; // ��t�O 
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
void DealN( string &name ); // �B�z�ɦW
   
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
		if ( left < list.size() ) //�b���`�I�s�W 
		{
			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( list[i].getsNo() > list[i / 2].getsNo() ) swap(list[i], list[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < list.size() ) //�b�k�`�I�s�W 
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
		if ( left < ldeap.size() ) //�b���`�I�s�W 
		{

			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( ldeap[i].getsNo() < ldeap[i / 2].getsNo() ) swap(ldeap[i], ldeap[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < ldeap.size() ) //�b�k�`�I�s�W 
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
		if ( left < rdeap.size() ) //�b���`�I�s�W
		{
			for ( int i = left; i != 1; i = i / 2 ) 
			{
				if ( rdeap[i].getsNo() > rdeap[i / 2].getsNo() ) swap(rdeap[i], rdeap[i / 2]);
				else break;
			}
	    }
		else break;
		if ( right < rdeap.size() ) //�b�k�`�I�s�W
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


void Tree::Sortlist( int &temp ){ //vector���O��J���l��vector�M�k�l��vector 
	int root = 1, total = 0;
	ldeap.push_back(list[0]);//�N��0���ťX�� ����F�� 
	rdeap.push_back(list[0]);//�N��0���ťX�� ����F�� 
	for( total = 0; total < list.size() - 1; root = root * 2 ) //vector�O�_����Ū�X 
	{
		for( int i = root; i > 0 && total < list.size() - 1; i-- ) //��m���l��vector 
		{
			total++;
			gright = false;
			ldeap.push_back(list[total]); // ���J�@��node
			//cout << list[total].getsNo() << "\n";
			if ( ldeap[ldeap.size() - 1].getsNo() > rdeap[ ( ldeap.size() - 1 ) / 2].getsNo() && ldeap.size() != 2 )// �T�{�����I�����`�I�_�ŦXDEAP �W�h 
			{
				swap( ldeap[ldeap.size() - 1], rdeap[ ( ldeap.size() - 1 ) / 2] );//��ӹ����I�洫 
				temp = ldeap[ldeap.size() - 1].getsNo();
			}
			CheckMinHeap(); // �̤p���|
			CheckMaxHeap(); // �̤j��n
		}
		for( int i = root; i > 0 && total < list.size() - 1; i-- ) //��m�k�l��vector 
		{
			total++;
			gright = true;
			rdeap.push_back(list[total]); // ���J�@��node
			//cout << list[total].getsNo() << "\n";
			if ( rdeap[rdeap.size() - 1].getsNo() < ldeap[rdeap.size() - 1].getsNo() )// �T�{�����I�O�_�ŦXDEAP �W�h 
			{
				swap( rdeap[rdeap.size() - 1], ldeap[rdeap.size() - 1] );//��ӹ����I�洫 
				temp = rdeap[rdeap.size() - 1].getsNo();
			}
			CheckMinHeap(); // �̤p���|
			CheckMaxHeap(); // �̤j��n
		}
	}
	
}

void Tree::InputFile( string & name , string & fileNum ) {
	ifstream fin;
	fileNum = name;
	list.clear();
	ldeap.clear();
	rdeap.clear();
    DealN( name );// �B�zINPUT
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "input 501,502.....[0] quit: " << endl;
		cin >> name;
		DealN( name );// �B�zINPUT
		fin.open( name.c_str() );
	}
	string tempdat;
	list.push_back(binary);
	getline(fin,tempdat);// �h�����D
	getline(fin,tempdat);
	getline(fin,tempdat);
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
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
	  	  if ( data[i] == '\t' ) { // �qrawRŪ����T(sNO.gNO.cname.gname) 
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
