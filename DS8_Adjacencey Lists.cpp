//系級: 資訊二甲 10627134 許寓翔 資訊二甲 10627149 許?僑 
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
#include <queue>
using namespace std;


struct Allstat{
    char putID[10] ;  //發訊者ID 
    char getID[10] ;  //收訊者ID 
    float weight ;  //量化權重 
};

struct PutList{
	Allstat stat;
	vector<Allstat> getlist;
    int Influence; //影響力 
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
	//此時檔案已開成 
	PutList temp;
	for ( int i = 0; i < list.size(); i++) // vector掃到第i筆資料 
	{
		if ( putlist.size() == 0 ) {//沒有主陣列時 
		    putlist.push_back(temp);
		    putlist[0].stat = list[i]; 
		    putlist[0].getlist.push_back(list[i]);//新增收訊者資料 
		    putlist.push_back(temp);//主陣列新增收訊者資料 
		    putlist[1].stat = list[i]; 
		    strcpy( putlist[1].stat.putID, list[i].getID );//主陣列新增資料 
		} // if 
		else {
			int j = 0;
		    while ( j < putlist.size() ) 
		    {
				if ( strcmp( putlist[j].stat.putID, list[i].putID ) == 0  ) {//找到相同發訊人 
					putlist[j].getlist.push_back(list[i]);//主陣列新增資料 
					int num = 0;//處理收訊人丟去主陣列問題 
			        while( num < putlist.size() ) {
					    if ( strcmp( putlist[num].stat.putID, list[i].getID ) == 0  ) {//找到相同發訊人 
						    break;
					    } // if
					    else if ( num == putlist.size() - 1 ) {
						    putlist.push_back(temp);//主陣列新增資料 
				            putlist[putlist.size() - 1].stat = list[i];
						    strcpy( putlist[putlist.size() - 1].stat.putID, list[i].getID );//主陣列新增資料 
						    break; 
					    }
					    num++;
				    }// while 處理收訊人丟去主陣列問題 
				    break;
				} // if
				else if ( j == putlist.size() - 1 ) {//沒有相同發訊人
				    putlist.push_back(temp);//主陣列新增資料 
				    putlist[putlist.size() - 1].stat = list[i]; 
		            putlist[putlist.size() - 1].getlist.push_back(list[i]);//新增收訊者資料 
		            int num = 0;//處理收訊人丟去主陣列問題 
			        while( num < putlist.size() ) {
					    if ( strcmp( putlist[num].stat.putID, list[i].getID ) == 0  ) {//找到相同發訊人 
						    break;
					    } // if
					    else if ( num == putlist.size() - 1 ) {
						    putlist.push_back(temp);//主陣列新增資料 
				            putlist[putlist.size() - 1].stat = list[i];
						    strcpy( putlist[putlist.size() - 1].stat.putID, list[i].getID );//主陣列新增資料 
						    break; 
					    }
					    num++;
				    }// while 處理收訊人丟去主陣列問題 
				    break;
				} // else if
				
	
				j++;
		    }
	    } // else處理主陣列插入 
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
	cout << "Pairs" << name << ".adj 建檔完成 " << endl; 
}


void AdjacencyList::Mission2(){
	if ( putlist.size() == 0 ) {
		cout << "請先使用任務1" << endl;
		return;
		 
	}
	for ( int i = 0; i < putlist.size(); i++ )  //初始化 
		putlist[i].Influence = 0;
	



	int num = 0;
	Allstat Cur; //當前資料 
	bool exist = false ; //檢查是否存在佇列中 
	for ( int i = 0 ; i < putlist.size() ; i++ )  // 所有主陣列資料是否全部跑完 
	{
			//cout << "2";
		//   將收訊者放入佇列等待處理 
		for ( int j = 0 ; j < putlist[i].getlist.size() ; j++ ) // 將第 i 筆資料的收訊者放入佇列 
		{
			//	cout << "3";
			waittinglist.push(putlist[i].getlist[j]) ; // 放入佇列
			allwaitlist.push_back(putlist[i].getlist[j]); // 將該發訊者所有已放入佇列的收訊者紀錄在vector 避免重複放入佇列 
		}
			//cout << "4";
		//  處理佇列的所有資料 
		while ( !waittinglist.empty() ) // 佇列空 才能跳出 
		{ 
		//	cout << "5";
			Cur = waittinglist.front(); // Cur為佇列最上面資料
			for ( num = 0 ; num < putlist.size(); num++ ) //尋找Cur在主陣列的哪筆資料 
			{
				//	cout << "6";
				if ( strcmp ( putlist[num].stat.putID, Cur.getID ) == 0 ) //從主陣列中找尋收訊人的資料 
					break; //主陣列第 num 筆為收訊人資料  
			}
			
			// 檢查第 num 筆資料的收訊者並把他放入佇列中 
			for ( int j = 0 ; j < putlist[num].getlist.size() ; j++ ) // 將第 i 筆資料的收訊者放入佇列 
			{
			//	cout << "7";
				exist = false;
				for ( int a = 0; a < allwaitlist.size(); a++ ) //檢查收訊者是否存入佇列過 
				{
					//	cout << "8";
					if ( strcmp( allwaitlist[a].getID, putlist[num].getlist[j].getID ) == 0 ) //找到相同資料 
						exist = true;
				}
				
				if ( !exist && strcmp( putlist[i].stat.putID, putlist[num].getlist[j].getID ) != 0 )
					waittinglist.push(putlist[num].getlist[j]) ; // 放入佇列 
					allwaitlist.push_back(putlist[num].getlist[j]); // 將該發訊者所有已放入佇列的收訊者紀錄在vector 避免重複放入佇列 
			}
				//cout << "9";
			putlist[i].Influence++ ; // 第 i 筆的影響力 
			waittinglist.pop(); // 移除佇列最上面資料 
		
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
	fstream file;// INPUTFILE的宣告 
	int stNo = 0;
	cout << "Input a file number,[0] quit: ";
	cin >> name;//檔案名稱 
	if ( !name.compare( "0" ) ) return; 
	file.open( ( "pairs" + name + ".bin" ).c_str(), fstream::in | fstream::binary);//開啟檔案 
    if ( !file.is_open() ) return; // no such file
	//此時檔案已開成 
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

