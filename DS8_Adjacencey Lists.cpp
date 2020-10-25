//�t��: ��T�G�� 10627134 �\�J�� ��T�G�� 10627149 �\?�� 
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
#include <queue>
using namespace std;


struct Allstat{
    char putID[10] ;  //�o�T��ID 
    char getID[10] ;  //���T��ID 
    float weight ;  //�q���v�� 
};

struct PutList{
	Allstat stat;
	vector<Allstat> getlist;
    int Influence; //�v�T�O 
};


class AdjacencyList{
	public :
	Allstat stat;
  	vector<Allstat> list;
  	vector<PutList> putlist;
  	queue<Allstat> waittinglist ; 
  	vector<Allstat> allwaitlist ;
  	void InputFile( string & name );
  	void Mission1();
  	void Mission2();
};

   
int main(int argc, char** argv) {
    int command = -1;
    AdjacencyList adj;
    while ( command != 0 ) {
	  cout << endl << "***** Adjacencey Lists *****";
      cout << endl << "* 0. QUIT                  *";
      cout << endl << "* 1. Adjacencey Lists      *";
      cout << endl << "* 2. Influence             *";
      cout << endl << "****************************";
      cout << endl << "Input a choice(0, 1, 2): ";
      
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) adj.Mission1();
      else if ( command == 2 ) adj.Mission2(); 
    } // while
	return 0;
}

string name;
void AdjacencyList::Mission1(){
	
	bool finish = false;
	if ( putlist.size() != 0 ) putlist.clear();
	if ( list.size() != 0 ) list.clear();
    InputFile( name );
    if ( list.size() == 0 ) return; 
    int move = 0;
	//�����ɮפw�}�� 
	PutList temp;
	for ( int i = 0; i < list.size(); i++) // vector�����i����� 
	{
		if ( putlist.size() == 0 ) {//�S���D�}�C�� 
		    putlist.push_back(temp);
		    putlist[0].stat = list[i]; 
		    putlist[0].getlist.push_back(list[i]);//�s�W���T�̸�� 
		    putlist.push_back(temp);//�D�}�C�s�W���T�̸�� 
		    putlist[1].stat = list[i]; 
		    strcpy( putlist[1].stat.putID, list[i].getID );//�D�}�C�s�W��� 
		} // if 
		else {
			int j = 0;
		    while ( j < putlist.size() ) 
		    {
				if ( strcmp( putlist[j].stat.putID, list[i].putID ) == 0  ) {//���ۦP�o�T�H 
					putlist[j].getlist.push_back(list[i]);//�D�}�C�s�W��� 
					int num = 0;//�B�z���T�H��h�D�}�C���D 
			        while( num < putlist.size() ) {
					    if ( strcmp( putlist[num].stat.putID, list[i].getID ) == 0  ) {//���ۦP�o�T�H 
						    break;
					    } // if
					    else if ( num == putlist.size() - 1 ) {
						    putlist.push_back(temp);//�D�}�C�s�W��� 
				            putlist[putlist.size() - 1].stat = list[i];
						    strcpy( putlist[putlist.size() - 1].stat.putID, list[i].getID );//�D�}�C�s�W��� 
						    break; 
					    }
					    num++;
				    }// while �B�z���T�H��h�D�}�C���D 
				    break;
				} // if
				else if ( j == putlist.size() - 1 ) {//�S���ۦP�o�T�H
				    putlist.push_back(temp);//�D�}�C�s�W��� 
				    putlist[putlist.size() - 1].stat = list[i]; 
		            putlist[putlist.size() - 1].getlist.push_back(list[i]);//�s�W���T�̸�� 
		            int num = 0;//�B�z���T�H��h�D�}�C���D 
			        while( num < putlist.size() ) {
					    if ( strcmp( putlist[num].stat.putID, list[i].getID ) == 0  ) {//���ۦP�o�T�H 
						    break;
					    } // if
					    else if ( num == putlist.size() - 1 ) {
						    putlist.push_back(temp);//�D�}�C�s�W��� 
				            putlist[putlist.size() - 1].stat = list[i];
						    strcpy( putlist[putlist.size() - 1].stat.putID, list[i].getID );//�D�}�C�s�W��� 
						    break; 
					    }
					    num++;
				    }// while �B�z���T�H��h�D�}�C���D 
				    break;
				} // else if
				
	
				j++;
		    }
	    } // else�B�z�D�}�C���J 
	} // for
	
	for ( int i = 0; i < putlist.size(); i++ ) {
		for ( int j = putlist.size() - 1; j > 0 ; j-- ) {
			if ( putlist[j].stat.weight > putlist[j - 1].stat.weight ) swap( putlist[j], putlist[j - 1]) ;
		}
	}
	
	ofstream fout( ( "Pairs" + name + ".adj" ).c_str() );
	fout << "--- AdjacencyList --- " <<endl;
	for( int i = 0; i < putlist.size(); i++ ){
		fout << putlist[i].stat.putID << "	" << endl;
		for ( int j = 0; j < putlist[i].getlist.size(); j++ ) fout << "	" << putlist[i].getlist[j].getID << "	" << putlist[i].getlist[j].weight << endl ;
	}
	cout << "Pairs" << name << ".adj ���ɧ��� " << endl; 
}


void AdjacencyList::Mission2(){
	if ( putlist.size() == 0 ) {
		cout << "�Х��ϥΥ���1" << endl;
		return;
		 
	}
	for ( int i = 0; i < putlist.size(); i++ )  //��l�� 
		putlist[i].Influence = 0;
	



	int num = 0;
	Allstat Cur; //��e��� 
	bool exist = false ; //�ˬd�O�_�s�b��C�� 
	for ( int i = 0 ; i < putlist.size() ; i++ )  // �Ҧ��D�}�C��ƬO�_�����]�� 
	{
			//cout << "2";
		//   �N���T�̩�J��C���ݳB�z 
		for ( int j = 0 ; j < putlist[i].getlist.size() ; j++ ) // �N�� i ����ƪ����T�̩�J��C 
		{
			//	cout << "3";
			waittinglist.push(putlist[i].getlist[j]) ; // ��J��C
			allwaitlist.push_back(putlist[i].getlist[j]); // �N�ӵo�T�̩Ҧ��w��J��C�����T�̬����bvector �קK���Ʃ�J��C 
		}
			//cout << "4";
		//  �B�z��C���Ҧ���� 
		while ( !waittinglist.empty() ) // ��C�� �~����X 
		{ 
		//	cout << "5";
			Cur = waittinglist.front(); // Cur����C�̤W�����
			for ( num = 0 ; num < putlist.size(); num++ ) //�M��Cur�b�D�}�C��������� 
			{
				//	cout << "6";
				if ( strcmp ( putlist[num].stat.putID, Cur.getID ) == 0 ) //�q�D�}�C����M���T�H����� 
					break; //�D�}�C�� num �������T�H���  
			}
			
			// �ˬd�� num ����ƪ����T�̨ç�L��J��C�� 
			for ( int j = 0 ; j < putlist[num].getlist.size() ; j++ ) // �N�� i ����ƪ����T�̩�J��C 
			{
			//	cout << "7";
				exist = false;
				for ( int a = 0; a < allwaitlist.size(); a++ ) //�ˬd���T�̬O�_�s�J��C�L 
				{
					//	cout << "8";
					if ( strcmp( allwaitlist[a].getID, putlist[num].getlist[j].getID ) == 0 ) //���ۦP��� 
						exist = true;
				}
				
				if ( !exist && strcmp( putlist[i].stat.putID, putlist[num].getlist[j].getID ) != 0 )
					waittinglist.push(putlist[num].getlist[j]) ; // ��J��C 
					allwaitlist.push_back(putlist[num].getlist[j]); // �N�ӵo�T�̩Ҧ��w��J��C�����T�̬����bvector �קK���Ʃ�J��C 
			}
				//cout << "9";
			putlist[i].Influence++ ; // �� i �����v�T�O 
			waittinglist.pop(); // ������C�̤W����� 
		
		} 
		allwaitlist.clear();  
	}


	for ( int i = putlist.size() - 1; i > 0; i-- ) {
		for ( int j = i; j > 0 ; j-- ) {
			if ( putlist[j].Influence < putlist[j - 1].Influence ) swap( putlist[j], putlist[j - 1]) ;
		}
	}

	
	ofstream fout( ( "Pairs" + name + ".cnt" ).c_str() );
	fout << "--- Influence --- " <<endl;
	for( int i = 0; i < putlist.size(); i++ ){
		fout << putlist[i].stat.putID << " : influence = " <<  putlist[i].Influence << endl;
		for ( int j = 0; j < putlist[i].getlist.size(); j++ ) fout << "	" << putlist[i].getlist[j].getID << endl ;
	}
	
}
void AdjacencyList::InputFile( string & name ) {
	fstream file;// INPUTFILE���ŧi 
	int stNo = 0;
	cout << "Input a file number,[0] quit: ";
	cin >> name;//�ɮצW�� 
	if ( !name.compare( "0" ) ) return; 
	file.open( ( "pairs" + name + ".bin" ).c_str(), fstream::in | fstream::binary);//�}���ɮ� 
    if ( !file.is_open() ) return; // no such file
	//�����ɮפw�}�� 
	if ( file.is_open() ) {
		file.seekg( 0, file.end );
		stNo = file.tellg() / sizeof(stat);
		file.seekg( 0, file.beg );
		for (int i = 0; i < stNo; i++ ) {
			file.read((char *)& stat, sizeof(stat)) ;
			list.push_back( stat );
		}
	}
	file.close();
}

