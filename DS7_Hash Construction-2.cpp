// 1. Linear Probing  
// 2. Double Hash 
// 3. Quadratic Probing
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
using namespace std;


struct Allstat{
    char sID[10] ;  //學號 
    char sName[10] ;  //姓名 
	unsigned char score[6];
    float average ;  //平均分數 
};

class Info{

	public :
	  Allstat stat;
	  int hvalue;
	  string getsName(){
      	return stat.sName;
	  }
	  string getsID(){
      	return stat.sID;
	  }
	  float getaverage(){
      	return stat.average;
	  }

	  void InputFile( string & name , string & fileNum );
};

class Hash{
	public :
	long long ChangeAscii( string str );
	int FindPrimeNum( int num );
	Allstat stat;
  	Info binary;//用來存放讀取到的暫存資料 
  	vector<Info> list;
  	void InputFile( string & name );
  	  
};
class Linear:public Hash {
	public :
		void Mission1();
};
class Double:public Hash{
	public :
		void Mission2();
};
class Quadratic:public Hash{
	public :
		void Mission3();
};
   
int main(int argc, char** argv) {
    int command = -1;
    Linear lin;
    Double dou;
    Quadratic qua;
    while ( command != 0 ) {
	  cout << endl << "***** Hash Construction *****";
      cout << endl << "* 0. QUIT                   *";
      cout << endl << "* 1. Linear Probing         *";
      cout << endl << "* 2. Double Hash            *";
      cout << endl << "* 3. Quadratic Probing      *";
      cout << endl << "******************************";
      cout << endl << "Input a choice(0, 1, 2, 3): ";
      
      cin >> command;
      if ( command == 0 ) return 1;
      else if ( command == 1 ) lin.Mission1();
      else if ( command == 2 ) dou.Mission2();
      else if ( command == 3 ) qua.Mission3();
    } // while
	return 0;
}


void Mission0( string name ){
	Allstat stat;
	string data;
	int stNo = 0;
	fstream file;// INPUTFILE的宣告 
	fstream outFile;// OUTPUTFILE的宣告 
	file.open( ( "input" + name + ".txt" ).c_str(), fstream::in | fstream::binary);//開啟檔案 
	if ( !file.is_open() ) {// 如果沒開成 
      file.close();
      cout << "No such file! Please try again."<< endl;
      return;
	} // if
    outFile.open( ( "input" + name + ".bin" ).c_str(), fstream::out | fstream::binary);//寫入檔案 
    char tempdat[255];
	
	while ( file.getline(tempdat, 255 ,'\n' )) // 每次讀一行
	{ 
	    string temp;
	    int cNo = 0, pre = 0, pos = 0;
	    
	    temp.assign(tempdat);
	    stNo++;
	    pos = temp.find_first_of('\t', pre);
	    while ( pos != string::npos ) {
	    	switch( ++cNo ) {
	    		case 1:strcpy( stat.sID, temp.substr(pre, pos - pre).c_str() );
	    		  break;
	    		case 2:strcpy( stat.sName, temp.substr(pre, pos - pre).c_str() );
	    		  break;
	    		default: stat.score[cNo - 3] = atoi(temp.substr(pre, pos - pre).c_str() );
	    		  break;
	    		
			}
			pre = ++pos;
			pos = temp.find_first_of('\t', pre);
		}
		pos = temp.find_last_of('\t');
		stat.average = atof(temp.substr(pos+1).c_str() );
		outFile.write((char *)& stat, sizeof(stat)) ;
	}
    file.close();
}




void Linear::Mission1(){
	string name;
	bool finish = false;
	int hashsize = 0; //雜湊表大小 
	int hashkey = 0; //函數 
    InputFile( name );
    if ( list.size() == 0 ) return; 
    int move = 0;
    int unmove = 0;
    float unsuccessful = 0;
    float successful = 0;
    
	//此時檔案已開成 
	hashsize = FindPrimeNum( list.size() * 1.2 ); //大於資料1.2倍的最小質數
    Info bucket[hashsize] = {'\0'};
	for ( int x = 0; x < hashsize; x++) //初始化 
	{
		bucket[x].hvalue = 0;						 
		strcpy( bucket[x].stat.sID, "" ) ;
		strcpy( bucket[x].stat.sName, "" ) ;
		bucket[x].stat.average = 0.0;		
	}
	for ( int i = 0; i < list.size(); i++) // vector掃到第i筆資料 
	{
		finish = false;
        hashkey =  ChangeAscii( list[i].getsID() ) % hashsize;//計算第i筆資料的餘數 
		for( int j = hashkey; !finish; j++) // 如果bucket那一個位置被占走往下一格查看是否是空的 
		{
			move++;
			if( strcmp(bucket[j].stat.sID, "") == 0  ) // bucket是空的 
			{ 
				bucket[j].hvalue = hashkey;						 
				strcpy( bucket[j].stat.sID, list[i].getsID().c_str() ) ;
				strcpy( bucket[j].stat.sName, list[i].getsName().c_str() ) ;
				bucket[j].stat.average = list[i].getaverage();
				finish = true;
			}			
			if ( j == ( hashsize - 1 ) ) j = -1;	 // 已到底部 
		}
	}
	
	///////////////////////不存在值比較次數////////////////////////////
	for( int i = 0; i < hashsize ; i++)
	{
		finish = false;
		for( int j = i; !finish; j++)
		{
			unmove++;
			if ( strcmp(bucket[j].stat.sID, "" ) == 0 ) finish = true;
			else if ( j == ( hashsize - 1 ) ) j = -1;
		}
	}
	///////////////////////不存在值比較次數////////////////////////////	
	
	unsuccessful = (float)unmove / (float)hashsize;
	successful = (float)move / (float)list.size();
	cout << "--- Hash Table X --- (linear probing)" <<endl;
	cout << "unsuccessful search:  " << unsuccessful-1 << "  comparisons on average" << endl;
	cout << "successful search  " << successful << "  comparisons on average" << endl;
	
	
	
	
	
	ofstream fout( ( "Linear" + name + ".txt" ).c_str() );
	fout << "--- Hash Table X --- (linear probing)" <<endl;
	for( int i = 0; i < hashsize; i++ ){
		if ( strcmp(bucket[i].stat.sID, "") != 0 ) fout << "[" << i << "]"<< bucket[i].hvalue << "	" << bucket[i].stat.sID << "	" << bucket[i].stat.sName << "	" << bucket[i].stat.average << endl ;
		else fout << "[" << i << "]" << endl ;
	}
	cout << "Linear" << name << ".txt 建檔完成 " << endl; 
    list.clear();
}

void Double::Mission2(){
	string name;
	bool finish = false;
	int hashsize = 0; //雜湊表大小 
	int hashkey = 0; //函數 
    InputFile( name );
    if ( list.size() == 0 ) return; 
    int highstep = FindPrimeNum( list.size() / 3 );
    int stepsize = 0;
    int move = 0;
    int unmove = 0;
    float unsuccessful = 0;
    float successful = 0;
	//此時檔案已開成 
	hashsize = FindPrimeNum( list.size() * 1.2 ); //大於資料1.2倍的最小質數
    Info bucket[hashsize] = {'\0'};
	for ( int x = 0; x < hashsize; x++) //初始化 
	{
		bucket[x].hvalue = 0;						 
		strcpy( bucket[x].stat.sID, "" ) ;
		strcpy( bucket[x].stat.sName, "" ) ;
		bucket[x].stat.average = 0.0;		
	}
	for ( int i = 0; i < list.size(); i++) // vector掃到第i筆資料 
	{
		finish = false;
        hashkey =   ChangeAscii( list[i].getsID()) % hashsize;//計算第i筆資料的餘數 
        stepsize = highstep - ( ChangeAscii( list[i].getsID() ) % highstep );// stepkey函數////////////////////////////// 
		for( int j = hashkey; !finish; j = j + stepsize) // 如果bucket那一個位置被占走往下一格查看是否是空的 
		{
			move++;
			if ( j > ( hashsize - 1 ) ) j = j % hashsize;	 // 已到底部 
			if( strcmp(bucket[j].stat.sID, "") == 0  ) // bucket是空的 
			{ 
				bucket[j].hvalue = hashkey;						 
				strcpy( bucket[j].stat.sID, list[i].getsID().c_str() ) ;
				strcpy( bucket[j].stat.sName, list[i].getsName().c_str() ) ;
				bucket[j].stat.average = list[i].getaverage();
				finish = true;
			}			
		}
	}
	
	///////////////////////不存在值比較次數////////////////////////////
	for( int i = 0; i < hashsize ; i++)
	{
		finish = false;
		for( int j = i; !finish; j++)
		{
			unmove++;
			if ( strcmp(bucket[j].stat.sID, "" ) == 0 ) finish = true;
			else if ( j == ( hashsize - 1 ) ) j = -1;
		}
	}
	///////////////////////不存在值比較次數////////////////////////////	
	
	unsuccessful = (float)unmove / (float)hashsize;
	successful = (float)move / (float)list.size();
	cout << "--- Hash Table X --- (double hashing)" <<endl;
	cout << "unsuccessful search:  " << unsuccessful-1 << "  comparisons on average" << endl;
	cout << "successful search  " << successful << "  comparisons on average" << endl;
	
	
	
	
	
	
	ofstream fout( ( "Double" + name + ".txt" ).c_str() );
	fout << "--- Hash Table X --- (double hashing)" <<endl;
	for( int i = 0; i < hashsize; i++ ){
		if ( strcmp(bucket[i].stat.sID, "") != 0 ) fout << "[" << i << "]"<< bucket[i].hvalue << "	" << bucket[i].stat.sID << "	" << bucket[i].stat.sName << "	" << bucket[i].stat.average << endl ;
		else fout << "[" << i << "]" << endl ;
	}
	cout << "Double" << name << ".txt 建檔完成 " << endl; 
    list.clear();
}

void Quadratic::Mission3(){
	string name;
	bool finish = false;
	int hashsize = 0; //雜湊表大小 
	int hashkey = 0; //函數 
    InputFile( name );
    if ( list.size() == 0 ) return; 
    int move = 0;
    int unmove = 0;
    float unsuccessful = 0;
    float successful = 0;
    int num = 1;
    
	//此時檔案已開成 
	hashsize = FindPrimeNum( list.size() * 1.2 ); //大於資料1.2倍的最小質數
    Info bucket[hashsize] = {'\0'};
	for ( int x = 0; x < hashsize; x++) //初始化 
	{
		bucket[x].hvalue = 0;						 
		strcpy( bucket[x].stat.sID, "" ) ;
		strcpy( bucket[x].stat.sName, "" ) ;
		bucket[x].stat.average = 0.0;		
	}
	for ( int i = 0; i < list.size(); i++) // vector掃到第i筆資料 
	{
		finish = false;
        hashkey =  ChangeAscii( list[i].getsID() ) % hashsize;//計算第i筆資料的餘數 
        num = 1;
        // 第一次進入沒有衝突 
        move++;
        if( strcmp(bucket[hashkey].stat.sID, "") == 0  ) // bucket是空的  
		{ 
			bucket[hashkey].hvalue = hashkey;						 
			strcpy( bucket[hashkey].stat.sID, list[i].getsID().c_str() ) ;
			strcpy( bucket[hashkey].stat.sName, list[i].getsName().c_str() ) ;
			bucket[hashkey].stat.average = list[i].getaverage();
			finish = true;
		}
		// 第一次進入有衝突 
		
		else
		{
			for( int j = hashkey + (num*num); !finish; j = hashkey + (num*num) ) // 如果bucket那一個位置被占走往下一格查看是否是空的 
			{
				move++;
				if ( j > (hashsize-1) ) j = j % hashsize;
				
				if( strcmp(bucket[j].stat.sID, "") == 0  ) // bucket是空的 
				{ 
					bucket[j].hvalue = hashkey;						 
					strcpy( bucket[j].stat.sID, list[i].getsID().c_str() ) ;
					strcpy( bucket[j].stat.sName, list[i].getsName().c_str() ) ;
					bucket[j].stat.average = list[i].getaverage();
					finish = true;
				}
				num++;
			}		
		}
	}
	
	///////////////////////不存在值比較次數////////////////////////////
	for( int i = 0; i < hashsize ; i++)
	{
		finish = false;
		num = 1;
		unmove++;
		if( strcmp(bucket[i].stat.sID, "") == 0  ) finish = true;
		for( int j = i + (num*num); !finish; j = i + (num*num))
		{
			if ( j > (hashsize-1) ) j = j % hashsize;
			unmove++;
			if ( strcmp(bucket[j].stat.sID, "" ) == 0 ) finish = true;
			num++;
		}
	}
	///////////////////////不存在值比較次數////////////////////////////	
	
	unsuccessful = (float)unmove / (float)hashsize;
	successful = (float)move / (float)list.size();
	cout << "--- Hash Table X --- (Quadratic probing)" <<endl;
	cout << "unsuccessful search:  " << unsuccessful-1 << "  comparisons on average" << endl;
	cout << "successful search  " << successful << "  comparisons on average" << endl;
	
	
	
	
	
	ofstream fout( ( "Quadratic" + name + ".txt" ).c_str() );
	fout << "--- Hash Table X --- (Quadratic probing)" <<endl;
	for( int i = 0; i < hashsize; i++ ){
		if ( strcmp(bucket[i].stat.sID, "") != 0 ) fout << "[" << i << "]"<< bucket[i].hvalue << "	" << bucket[i].stat.sID << "	" << bucket[i].stat.sName << "	" << bucket[i].stat.average << endl ;
		else fout << "[" << i << "]" << endl ;
	}
	cout << "Quadratic" << name << ".txt 建檔完成 " << endl; 
    list.clear();
}

long long Hash::ChangeAscii( string str ){
	long long total = 1;
	for(int i = 0; i < 10; i++)
	{
		if( str[i] == '0' ) total = total * 48 ;
		else if ( str[i] == '1' ) total = total * 49 ;
		else if ( str[i] == '2' ) total = total * 50 ;
		else if ( str[i] == '3' ) total = total * 51 ;
		else if ( str[i] == '4' ) total = total * 52 ;
		else if ( str[i] == '5' ) total = total * 53 ;
		else if ( str[i] == '6' ) total = total * 54 ;
		else if ( str[i] == '7' ) total = total * 55 ;
		else if ( str[i] == '8' ) total = total * 56 ;
		else if ( str[i] == '9' ) total = total * 57 ;


	}
	//cout << total << endl;
	return total;
		
}

int Hash::FindPrimeNum( int num ){
	num++; //大於原本的數字 
	bool isprime = false;
	if ( num == 1 && num == 2 ) isprime = true;
	else
	{
		while ( !isprime )
		{
			isprime = true;
			for ( int i = 2; i < num; i++)
			{
				if( num%i == 0 ) isprime = false;
			}
			if ( !isprime ) num++;
		}
	}
	return num;
	 
} 

void Hash::InputFile( string & name ) {
	fstream file;// INPUTFILE的宣告 
	int stNo = 0;
	cout << "Input a file number,[0] quit: ";
	cin >> name;//檔案名稱 
	if ( !name.compare( "0" ) ) return; 
	file.open( ( "input" + name + ".bin" ).c_str(), fstream::in | fstream::binary);//開啟檔案 
    if ( !file.is_open() ) {// 如果沒開成 
      file.close();
      Mission0( name.c_str() );
      file.open( ( "input" + name + ".bin" ).c_str(), fstream::in | fstream::binary);//開啟檔案 
      if ( !file.is_open() ) return; // no such file
	} // if
	//此時檔案已開成 
	
	if ( file.is_open() ) {
		file.seekg( 0, file.end );
		stNo = file.tellg() / sizeof(binary.stat);
		file.seekg( 0, file.beg );
		for (int i = 0; i < stNo; i++ ) {
			file.read((char *)& binary.stat, sizeof(binary.stat)) ;
			list.push_back( binary );
			//cout << "[" << i << "]" << binary.stat.sID << "	" << binary.stat.sName << "	" << binary.stat.average << endl ;
		}
	}
	file.close();
}
