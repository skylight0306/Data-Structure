//�t��: ��T�G�� 10627134 �\�J�� ��T�G�� 10627149 �\?�� 

#include <iostream>   // cout, endl
#include <fstream>    // open, is_open, close
#include <vector>     // vector, push_back
#include <cstdlib>
#include <string>     // string
#include <stdio.h>   
#include <string.h> 
#include <stdlib.h>
 
using namespace std;





class Info
{
	private :
       string rawR ;
       int ID ;
       string Name ;
       string Type1 ;
       int Total ;
       int HP ;
       int Atk ;
       int Def ;
       int SpAtk ;
       int SpDef ;
       int Speed ;
       int Gen ;
       string Leg ;
       
	public :
		void newsch( string sch ) 
		{ rawR = sch ; }
		
		string getDat()
		{ return rawR ; }
		
		int getID() 
		{ return ID ; }
    	
		string getName()
		{ return Name ; }
		
    	string getType1()
		{ return Type1 ; }
    	
		int getTotal()
		{ return Total ; }
	  
		int getHP()
		{ return HP ; }
		
		int getAtk()
		{ return Atk ; }
		
		int getDef()
		{ return Def ; }
		
		void Printsix( int i ) 
		{
	  		cout << "[ " << i << "]	"<< getID() << "	" <<  getName() << "				" <<  getType1() << "		" 
			<<  getHP() << "	" <<  getAtk() << "	" <<  getDef() << endl ;
	  	}
	  	
	  	void Printseven ( int i ) 
		{
	  		cout << "[ " << i << "]	"<< getID() << "	" <<  getName() << "				" << getTotal() << "	" 
			<<  getHP() << "	" <<  getAtk() << "	" <<  getDef() << endl ;
	  	}
	  	
		void DealDat( string data ) ;
} ; 
struct BST{
	vector<Info> Cur;
	BST *Left;
	BST *Right;
	BST *Last;
};

class Pokemon{
    private:
  	  Info binary;
  	  
    public:
	  vector<Info> list;
	  void mission1( BST *&tree );
      void mission2( BST *&tree );
      void mission3( BST *&tree );
      int findheight( BST *&tree );
      void traverse( BST *&tree, int num ,int &visit);
      void CreateTree( BST *&tree );
      void InputFile( string & name, string & fileNum );
};

void saveFile( string &name , char c); // save all records into a file
void DealN( string &name ); // �B�z�ɦW
   
int main(int argc, char** argv) {
	Pokemon Pok;
	BST *tree = NULL; 
    int command = -1;
    while ( command != 0 ) {
	  cout << endl << "*** Binary Search Tree on Pokemon ***";
      cout << endl << "* 0. QUIT *";
      cout << endl << "* 1. Read one file to build BST     *";
      cout << endl << "* 2. Threshold search on one column *";
      cout << endl << "* 3. Delete the max on one column   *";
      cout << endl << "*************************************";
      cout << endl << "Input a choice(0, 1, 2, 3): ";
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) Pok.mission1( tree );
      else if ( command == 2 ) Pok.mission2( tree );
      else if ( command == 3 ) Pok.mission3( tree );
    } // while
	return 0;
}





void Pokemon::mission1( BST *&tree ) { // Select_sort & Bubble_sort
	
	string name, fileNum;
	ifstream fin;
	int height = 1,max = 1;
	cout << "Input a file number,[0] quit: ";
	cin >> name;
	InputFile( name, fileNum );
	CreateTree( tree );
}





int curnum = 1;
void Pokemon::mission2( BST *&tree ) { 
    int visit = 0,largest = 0;
    if ( tree == NULL ) {
    	cout << "ERROR :�Х��ϥΥ���1" << endl; 
    	return ;
	}
	BST *first = tree;
	BST *temp = tree;
	int height = 1,max = 1,num = 0;
	while( tree->Right != NULL ) tree = tree->Right;//��J����W�Llargest���� 
	largest = tree->Cur[0].getHP();//��J����W�Llargest���� 
	tree = first;//��J����W�Llargest���� 
	cout << "Input a positive num[1 ~ "  << largest << "] = " ; 
	cin >> num;
	if ( num > largest && num > 0) {
		cout << "�W�L�d��,�Э��s�������2" << endl; 
		return;
	}
	cout << "	#	Name				Total	Type1		HP	Attack	Defence" << endl;
	while ( tree != NULL ) {
		if ( num > tree->Cur[0].getHP() ) {
		  tree = tree->Right;
		  visit++;
		}
		else if ( num <= tree->Cur[0].getHP() ) {
			traverse ( tree,num,visit );
			break;
		}
    }
    curnum = 1;
	tree = first;
	cout << "Number of visited nodes = " << visit << endl;
}

void Pokemon::mission3( BST *&tree ){
	int height = 0;
	if ( tree == NULL ) {
    	cout << "ERROR :�Х��ϥΥ���1" << endl; 
    	return;
	}
	BST *first = tree;
	while( tree->Right != NULL ) tree = tree->Right;
	cout << "#	Name	Type1	Type2	Total	HP	Attack	Defense	Sp.Atk	Sp.Def	Speed	Generation	Legendary" << endl;
	if ( tree->Cur.size() > 1 ) {
	  cout << tree->Cur[0].getDat() << endl ;
	  tree->Cur.erase( tree->Cur.begin() );	
	}
	else if ( tree == first ) {//�̤j�Ȭ��𪺳��ݮ� 
		cout << tree->Cur[0].getDat() << endl ;
		first = first->Left;
		delete tree;
	}
	else if ( tree->Left == NULL ) {//����L�`�I 
		cout << tree->Cur[0].getDat() << endl ;
		tree->Last->Right = NULL;
		delete tree;
	}
	else if ( tree->Left != NULL ) {
		cout  << tree->Cur[0].getDat() << endl ;
		tree->Last->Right = tree->Left;
		tree->Left->Last = tree->Last;
		delete tree;
	}
	tree = first;
	height = findheight( tree ) ;
	cout << "HP tree height = " << height << endl;
}

int Pokemon::findheight( BST *&tree ) {
  if ( tree == NULL )
    return 0 ;
  else if ( findheight(tree->Left) > findheight(tree->Right)) return findheight(tree->Left) + 1;
  else return findheight(tree->Right) + 1;
}





void Pokemon::traverse ( BST *&tree, int num , int &visit){
	
	if ( tree != NULL ) {
		if ( num < tree->Cur[0].getHP()  ){
			traverse ( tree->Right ,num ,visit);
			for ( int i = 0; i < tree->Cur.size(); i++ ) {
		      tree->Cur[i].Printseven( curnum );
		      curnum++;
		    }
		    traverse ( tree->Left ,num ,visit);
		    visit++;
		}
		else if ( num == tree->Cur[0].getHP()  ){
			traverse ( tree->Right ,num ,visit);
			for ( int i = 0; i < tree->Cur.size(); i++ ) {
		      tree->Cur[i].Printseven( curnum );
		      curnum++;
		    }
		    visit++;
		}
	    else if ( num > tree->Cur[0].getHP() ) {
	    	traverse ( tree->Right ,num ,visit);
	    	visit++;
		}
	}
}





void Pokemon::CreateTree( BST *&tree ) {
	// ===== initialize =====
	int height = 1,max = 1 ;
	BST *temp = new BST ;             //�ΨӰO����e�W�@����� 
	tree = new BST ;                  // �s�ؤ@�ʾ� 
	tree->Cur.push_back(list[0]) ;    // ��J�Ĥ@�� 
	tree->Left = NULL ;               // �Ĥ@�����䬰null 
	tree->Right = NULL ;              // �Ĥ@���k�䬰null 
	BST *first = tree ;               // root = tree
	 
	cout << "	#	Name				Type1		HP	Attack	Defence" << endl;
	list[1].Printsix( 1 );//�L�e������� 
	
	
	// ===== build binary tree =====
	for ( int i = 1; i < list.size(); i++ ) {
	  	list[i].Printsix( i + 1 ) ;        // �L�e������� 
	  	while ( tree != NULL )                                                     // ��tree���V����m���O�Ū�
		{ 
	    	temp = tree ;                                                          // �N�Ӧ�m�O�����W�@�� 
			if ( list[i].getHP() > tree->Cur[0].getHP() ) tree = tree->Right ;     // ��Ӧ�m�j�A���k�� 
			else if ( list[i].getHP() < tree->Cur[0].getHP()) tree = tree->Left ;  // ��Ӧ�m�p�A������ 
			else if ( list[i].getHP() == tree->Cur[0].getHP() ) break ;            // �۵��A���X 
			height++;
    	}
      
      
      	// ===== data -> tree =====
     	if ( tree == NULL )  // �p�G�Ӧ�m�O�Ū� 
	  	{ 
      		tree = new BST ;
	  		tree->Cur.push_back(list[i]) ;
	  		tree->Left = NULL ;
	  		tree->Right = NULL ;
	  		tree->Last = temp ;
	  		if ( temp->Cur[0].getHP() < list[i].getHP() ) temp->Right = tree ;
	  		else temp->Left = tree ;
      	}
      	else                // �p�G�Ӧ�m���O�Ū� 
			tree->Cur.push_back(list[i]) ;
	  
	  
      	tree = first;
      	if ( max < height ) max = height;
      	height = 1;
	}
	cout << "HP tree height = " << max << endl;
}





void Pokemon::InputFile( string & name , string & fileNum ) {
	fstream fin;
	fileNum = name;
	list.clear();
    name = "input" + name + ".txt" ;
	fin.open( name.c_str() );
    while ( !fin ) {
    	cout << name << " does not exist! " << endl ;
    	cout << "input 201, 202, ..... (0:quit): " << endl ;
		cin >> name ;
		name = "input" + name + ".txt" ;
		fin.open( name.c_str() ) ;
	}
	string tempdat ;
	getline(fin,tempdat);// �h�����D
	while ( getline(fin,tempdat) ) { // �C��Ū�@��
	    binary.DealDat( tempdat ) ;// input data to class
    	list.push_back(binary); // add data to last one;
	}

}





void Info::DealDat( string data ) {
	  	int tabcount = 0 ;
        int tabstart = -1 ;
        int tabend = 0 ;
        string infostring = "";
      	rawR = data;
	  	string temp;
	  	for ( int i = 0; tabcount < 10 ; i++ ) {
	  	  if ( data[i] == '\t' ) { // �qrawRŪ����T(sNO.gNO.cname.gname) 
            tabcount++;
			tabend = i;
			if ( tabcount == 1 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              ID = atoi( infostring.c_str() );
              infostring = "" ;
            } // if
	        else if ( tabcount == 2 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              Name = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 3 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              Type1 = infostring ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 5 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              Total = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 6 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              HP = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 7 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' && data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              Atk = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 8 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              Def = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 9 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              SpAtk = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 10 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              SpDef = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 11 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              Speed = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 12 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) {
                if ( data[k] != '"' || data[k] != ',' )
                  infostring = infostring + data[k] ;
              } // for
              Gen = atoi( infostring.c_str() ) ;
              infostring = "" ;
            } // else if
            else if ( tabcount == 13 ) {
              for ( int k = tabstart + 1 ; k < tabend ; k++ ) infostring = infostring + data[k] ;
              Leg = infostring ;
              infostring = "" ;
            } // else if
            tabstart = tabend;
          } // if
      	}
	  } // DealDat
