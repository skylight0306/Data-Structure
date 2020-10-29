#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <cstdlib> 
#include <time.h>
using namespace std;


struct Allstat{
    char putID[10] ;  //發訊者ID 
    char getID[10] ;  //收訊者ID 
    float weight ;  //量化權重 
};

struct SaveList{
	float weight ; // weight
	int offset ; // Displacement
};

class ExternalSort{
	private :
		fstream file;// INPUTFILE的宣告 
		int filecount;
		string name;
	public :
	    Allstat stat;
  	    vector<Allstat> list;
  	    vector<SaveList> slist; 
  	    void SelectSort();//處理內部排序的200筆資料 
  	    void BubbleSort();
  	    void InputFile();
  	    void Mission1();
  	    void Mission2();
  	    void InsertionSort();
  	    void ExternalMerge();
  	    void test();
};

   
int main(int argc, char** argv) {
    int command = -1;
    ExternalSort Ext;
    while ( command != 0 ) {
	  cout << endl << "******* ExternalSort *******";
      cout << endl << "* 0. QUIT                  *";
      cout << endl << "* 1. ExternalSort          *";
      cout << endl << "* 2. Primary index         *";
      cout << endl << "****************************";
      cout << endl << "Input a choice(0, 1, 2): ";
      
      cin >> command;
      if ( command == 0 ) return 0;
      else if ( command == 1 ) Ext.Mission1();
      else if ( command == 2 ) Ext.Mission2(); 
    } // while
	return 0;
}

void ExternalSort::Mission1() {
//	test();
	
	double insclockstart,insclockend;
	double extclockstart,extclockend;
	insclockstart = clock();
	InsertionSort();//處理內部排序
	insclockend = clock();
	extclockstart = clock();
	ExternalMerge();//合併外部排序 
	extclockend = clock();
	cout << "the Execution time ..." << endl;
	cout << "Internal Sort = " << insclockend - insclockstart << " ms" << endl;
	cout << "External Sort = " << extclockend - extclockstart << " ms" << endl;
	cout << "Total Execution Time = " << insclockend - insclockstart + extclockend - extclockstart << " ms" << endl;
	
}   

void ExternalSort::InsertionSort(){
	fstream outFile;// OUTPUTFILE的宣告 
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
		int all = stNo / 200, index = -1;
		filecount = all;
		for ( int i = 0; i < stNo; ) {
		    for ( int j = 0; j < 200 && i < stNo; j++ ) {//一次只讀200筆資料 以應付記憶體不足的可能 
			    file.read((char *)& stat, sizeof(stat) );
			    list.push_back( stat );
			    i++;
		    }
		    index++;
		    BubbleSort();
		    // 下一行 寫成檔案 EX: sorted501_94_0  
		    char alls[3],indexs[3];
			sprintf(alls, "%d", all);
			sprintf(indexs, "%d", index);
		    outFile.open( ( "sorted" + name + "_" + alls + "_" + indexs + ".bin" ).c_str(), fstream::out | fstream::binary);//寫入檔案 
		    for ( int num = 0; num < list.size(); num++ ) {
		    	outFile.write((char *)& list[num], sizeof(list[num])) ;
			}
		    list.clear();
		    outFile.close();
		}
		
	}
	file.close();
}

void ExternalSort::test() {
	file.open( "sorted501_47_16.bin", fstream::in | fstream::binary);//開啟檔案 
	for ( int i = 0; i < 200; i++ ) {
		file.read((char *)& stat, sizeof(stat) );
		cout << stat.weight << endl;
	}
	file.seekg( 0, file.end );
	int stNo = file.tellg() / sizeof(stat);
	file.seekg( 0, file.beg );
	cout << stNo << endl;
}		
void ExternalSort::ExternalMerge(){
	int mergetimes = 0;
	fstream File1, File2;
	fstream outFile1;
	Allstat stat2;
	system("pause");
	stat2.weight = -1;
	for ( int files = filecount; files >= 1; files = files / 2) {
		for ( int i = 0; i <= files; i = i + 2 ) {
		    char alls[3],indexs[3], indexs2[3];
	    	char outalls[3], outindexs[3];
	    	sprintf(alls, "%d", files);
	    	sprintf(indexs, "%d", i);
	    	sprintf(indexs2, "%d", i + 1);
	    
	    	File1.open( ( "sorted" + name + "_" + alls + "_" + indexs + ".bin" ).c_str(), fstream::in | fstream::binary);//寫入檔案   	
	    	File2.open( ( "sorted" + name + "_" + alls + "_" + indexs2 + ".bin" ).c_str(), fstream::in | fstream::binary);//寫入檔案 
	    	sprintf(outalls, "%d",  files / 2 );
	    	sprintf(outindexs, "%d", i / 2);
	    	outFile1.open( ( "sorted" + name + "_" + outalls + "_" + outindexs + ".bin" ).c_str(), fstream::out | fstream::binary );
	    	File1.read((char *)& stat, sizeof(stat) );
	    	File2.read((char *)& stat2, sizeof(stat2) );
	    	while ( !File1.eof() ) {
	    		if ( stat.weight >= stat2.weight ){
			    	outFile1.write((char *)& stat, sizeof(stat)) ;
			    	File1.read((char *)& stat, sizeof(stat) );
			    }
			    else if ( stat2.weight > stat.weight ){
			    	outFile1.write((char *)& stat2, sizeof(stat2)) ;
			    	File2.read((char *)& stat2, sizeof(stat2) );
			    }
			    
	    		if ( File1.eof() ) {
	    			while ( !File2.eof() ) {
						outFile1.write((char *)& stat2, sizeof(stat2)) ;
	    				File2.read((char *)& stat2, sizeof(stat2) );
					} // while
					//break;
				}
			    else if ( File2.eof() ) {
			    	while ( !File1.eof() ) {
						outFile1.write((char *)& stat, sizeof(stat)) ;
	    				File1.read((char *)& stat, sizeof(stat) );
					} // while
					//break;
		    	}
		    }
	        mergetimes++;
	        File1.close();
	        File2.close();
	        remove(( "sorted" + name + "_" + alls + "_" + indexs + ".bin" ).c_str());
	        remove(( "sorted" + name + "_" + alls + "_" + indexs2 + ".bin" ).c_str());
	        outFile1.close();
        }
        cout << "now there are " << ( files + 2 )/ 2 << " runs" << endl;
        system("pause");
        
    }
    rename ( ( "sorted" + name + "_0_0.bin" ).c_str(), ( "sorted" + name + ".bin" ).c_str() );
}

void ExternalSort::Mission2(){	
	fstream outFile;// OUTPUTFILE的宣告 
	int stNo = 0;
	cout << "Input a file number,[0] quit: ";
	cin >> name;//檔案名稱 
	if ( !name.compare( "0" ) ) return; 
	file.open( ( "sorted" + name + ".bin" ).c_str(), fstream::in | fstream::binary);//開啟檔案 
    if ( !file.is_open() ) return; // no such file
	//此時檔案已開成 
	
	float cur = 0.0; // current weight
	int offset = 0; //Displacement
	bool first = true ;
	SaveList temp ; //temp savelist for pushback
	
	if ( file.is_open() ) {
		file.seekg( 0, file.end );
		stNo = file.tellg() / sizeof(stat);
		file.seekg( 0, file.beg );
		int all = stNo / 200, index = -1;
		filecount = all;
		for ( int i = 0; i < stNo; ) {
		    for ( int j = 0; j < 200 && i < stNo; j++ )  // read 200 informations a time
			{ 
			    file.read((char *)& stat, sizeof(stat) );
			    list.push_back( stat );
			    i++;
		    }
		    
			if ( first ) // first time in this "for" loop
			{
				cur = list[0].weight ; //set current weight value
				slist.push_back( temp );
				slist[0].weight = cur ;
				slist[0].offset = offset;
				offset++;
				first = false ; // first time turn false
				for ( int num = 1; num < list.size(); num++)
				{
					if ( cur == list[num].weight )			
						offset++ ; // record offset
					else 
					{
						cur = list[num].weight ; //change current weight
						slist.push_back( temp );
						slist[slist.size() - 1].weight = cur ;
						slist[slist.size() - 1].offset = offset;
						offset++; 
					}
				
				} 
			}	
			
			else // more than one time
			{
				for ( int num = 0; num < list.size(); num++)
				{
					if ( cur == list[num].weight )			
						offset++ ; // record offset
					else 
					{
						cur = list[num].weight ; //change current weight
						slist.push_back( temp );
						slist[slist.size() - 1].weight = cur ;
						slist[slist.size() - 1].offset = offset;
						offset++; 
					}
				
				} 
			} 
			
			list.clear();
		}
		file.close();
	}
	
	
	
	
	
	

	
	
	
	
	
	
	for ( int i = 0; i < slist.size() ; i++ ) cout << "[" << i + 1 << "]" << " (" << slist[i].weight << ", " << slist[i].offset << ")" << endl ;
	return ;
} 


void ExternalSort::InputFile() {
	int stNo = 0;
	string name;
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
			file.read((char *)& stat, sizeof(stat));
			list.push_back( stat );
		}
	}
	file.close();
} 

void ExternalSort::BubbleSort(){
	for ( int i = 0; i < list.size(); i++ ) { // 尚未排序成功的資料列 
		for ( int current = 0; current + 1 < list.size() - i ; current++ ) { // 正在對比大小 
			if( list[current].weight < list[current + 1].weight ) swap(list[current], list[current + 1]);
		}
    }
}
