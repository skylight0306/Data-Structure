#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <iomanip>
#pragma warning( disable : 4996 )

using namespace std;

char outputFileName[30];
int totalDelay;

class guest_list {

	struct guest {

		int OID = 0;
		int Arrival = 0;
		int Duration = 0;
		int TimeOut = 0;
		int Delay = 0;
		int Abort = 0;
		int Departure = 0;
		int CID = 0;


		struct guest* prev;
		struct guest* next;

	};

	struct guest* head = NULL;
	struct guest* tail = NULL;
public:
	void addAGuest(int OID, int Arrival, int Duration, int TimeOut)
	{

		struct guest* temp = new guest;
		temp->OID = OID;
		temp->Arrival = Arrival;
		temp->Duration = Duration;
		temp->TimeOut = TimeOut;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果隊伍原本是空的，就把head跟tail指向第一位客人
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在隊伍尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}

	void addACancel(int OID, int Delay, int Abort)
	{


		struct guest* temp = new guest;
		temp->OID = OID;
		temp->Arrival = 0;
		temp->Duration = 0;
		temp->TimeOut = 0;
		temp->Delay = Delay;
		temp->Abort = Abort;
		temp->Departure = 0;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果取消清單原本是空的，就把head跟tail指向第一張訂單
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在清單尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}

	void addACancel(int OID, int Delay, int Abort, int CID)
	{


		struct guest* temp = new guest;
		temp->OID = OID;
		temp->Arrival = 0;
		temp->Duration = 0;
		temp->TimeOut = 0;
		temp->Delay = Delay;
		temp->Abort = Abort;
		temp->Departure = 0;
		temp->CID = CID;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果取消清單原本是空的，就把head跟tail指向第一張訂單
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在清單尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}

	void addATimeOut(int OID, int Delay, int Departure)
	{


		struct guest* temp = new guest;
		temp->OID = OID;
		temp->Arrival = 0;
		temp->Duration = 0;
		temp->TimeOut = 0;
		temp->Delay = Delay;
		temp->Abort = 0;
		temp->Departure = Departure;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果取消清單原本是空的，就把head跟tail指向第一張訂單
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在清單尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}


	void addATimeOut(int OID, int Delay, int Departure, int CID)
	{


		struct guest* temp = new guest;
		temp->OID = OID;
		temp->Arrival = 0;
		temp->Duration = 0;
		temp->TimeOut = 0;
		temp->Delay = Delay;
		temp->Abort = 0;
		temp->Departure = Departure;
		temp->CID = CID;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果取消清單原本是空的，就把head跟tail指向第一張訂單
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在清單尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}


	struct guest* findAGuest(int counting)
	{
		struct guest* temp = head;
		for (int i_in = 0; i_in < counting; i_in++) {
			temp = temp->next;
		}
		return temp;

	};

	int peopleInLine()
	{
		int counter = 0;
		struct guest* temp = head;
		if (temp == NULL) return 0;
		counter++;
		while (temp->next != NULL) {
			temp = temp->next;
			counter++;
		} // while

		return counter;
	}

	void Shell_sort()
	{
		int amount = peopleInLine(); // 要排序的資料的筆數
		for (int D = amount / 2; D > 0; D /= 2) {
			for (int P = D; P < amount; P++) {
				struct guest* temp = new guest;
				temp->OID = findAGuest(P)->OID;
				temp->Arrival = findAGuest(P)->Arrival;
				temp->Duration = findAGuest(P)->Duration;
				temp->TimeOut = findAGuest(P)->TimeOut;
				// int Tmp = A[P];
				int i;
				for (i = P; i >= D && (findAGuest(i - D)->Arrival > temp->Arrival || (findAGuest(i - D)->Arrival == temp->Arrival && findAGuest(i - D)->OID > temp->OID)); i -= D) {
					// A[i] = A[i-D] ;
					findAGuest(i)->OID = findAGuest(i - D)->OID;
					findAGuest(i)->Arrival = findAGuest(i - D)->Arrival;
					findAGuest(i)->Duration = findAGuest(i - D)->Duration;
					findAGuest(i)->TimeOut = findAGuest(i - D)->TimeOut;
				} // for
				  // A[i] = Tmp;
				findAGuest(i)->OID = temp->OID;
				findAGuest(i)->Arrival = temp->Arrival;
				findAGuest(i)->Duration = temp->Duration;
				findAGuest(i)->TimeOut = temp->TimeOut;
			} // for
		} // for


	} // Shell_sort()

	void showAllGuest()
	{
		cout << "OID     Arrival  Duration  TimeOut\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			cout << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Arrival;
			temp_for_counting = temp->Arrival;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Duration;
			temp_for_counting = temp->Duration;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 9; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->TimeOut;
			temp_for_counting = temp->TimeOut;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 6; i++) {
				cout << " ";
			}
			cout << " ";
			cout << "\n";
			temp = temp->next;
		}
		cout << "\n";

	} // showAllGuest()

	void showCancelList()
	{
		cout << "[Abort List]\nOID     Delay   Abort\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			cout << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Abort;
			temp_for_counting = temp->Abort;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				cout << " ";
			}
			cout << " ";

			cout << "\n";
			temp = temp->next;
		}
		cout << "\n";

	} // showCancelList()

	void showTimeoutList()
	{
		cout << "[Timeout List]\nOID     Delay   Departure\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			cout << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Departure;
			temp_for_counting = temp->Departure;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				cout << " ";
			}
			cout << " ";

			cout << "\n";
			temp = temp->next;
		}
		cout << "\n";

	} // showCancelList()


	void showCancelListWithCID()
	{
		cout << "[Abort List]\nOID     CID  Delay   Abort\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			cout << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->CID;
			temp_for_counting = temp->CID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Abort;
			temp_for_counting = temp->Abort;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				cout << " ";
			}
			cout << " ";

			cout << "\n";
			temp = temp->next;
		}
		cout << "\n";

	} // showCancelList()

	void showTimeoutListWithCID()
	{
		cout << "[Timeout List]\nOID     CID  Delay   Departure\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			cout << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->CID;
			temp_for_counting = temp->CID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				cout << " ";
			}
			cout << " ";

			cout << temp->Departure;
			temp_for_counting = temp->Departure;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				cout << " ";
			}
			cout << " ";

			cout << "\n";
			temp = temp->next;
		}
		cout << "\n";

	} // showCancelList()


	void storeAllGuest(char outputFileName[])
	{
		ofstream outputFile;
		outputFile.open(outputFileName);

		outputFile << "OID     Arrival  Duration  TimeOut\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			outputFile << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Arrival;
			temp_for_counting = temp->Arrival;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Duration;
			temp_for_counting = temp->Duration;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 9; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->TimeOut;
			temp_for_counting = temp->TimeOut;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 6; i++) {
				outputFile << " ";
			}
			outputFile << " ";
			outputFile << "\n";
			temp = temp->next;
		}

	} // storeAllGuest()
	

	void storeCancelList()
	{
		ofstream outputFile;
		outputFile.open(outputFileName);
		outputFile << "[Abort List]\nOID     Delay   Abort\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			outputFile << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Abort;
			temp_for_counting = temp->Abort;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << "\n";
			temp = temp->next;
		}
		outputFile << "\n";

	} // showCancelList()

	void storeTimeoutList()
	{
		ofstream outputFile;
		outputFile.open(outputFileName, ios::app);
		outputFile << "[Timeout List]\nOID     Delay   Departure\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			outputFile << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Departure;
			temp_for_counting = temp->Departure;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << "\n";
			temp = temp->next;
		}
		outputFile << "\n";

	} // showCancelList()


	void storeCancelListWithCID()
	{
		ofstream outputFile;
		outputFile.open(outputFileName);
		outputFile << "[Abort List]\nOID     CID  Delay   Abort\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			outputFile << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->CID;
			temp_for_counting = temp->CID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Abort;
			temp_for_counting = temp->Abort;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << "\n";
			temp = temp->next;
		}
		outputFile << "\n";

	} // showCancelList()

	void storeTimeoutListWithCID()
	{
		ofstream outputFile;
		outputFile.open(outputFileName, ios::app);
		outputFile << "[Timeout List]\nOID     CID  Delay   Departure\n";
		struct guest* temp = head;
		int temp_for_counting, counter;
		while (temp != NULL) {

			outputFile << temp->OID;
			temp_for_counting = temp->OID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->CID;
			temp_for_counting = temp->CID;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 4; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Delay;
			temp_for_counting = temp->Delay;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 7; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << temp->Departure;
			temp_for_counting = temp->Departure;
			counter = 0;
			if (temp_for_counting == 0) counter++;
			while (temp_for_counting != 0) {
				temp_for_counting /= 10;
				counter++;
			}
			for (int i = counter; i < 8; i++) {
				outputFile << " ";
			}
			outputFile << " ";

			outputFile << "\n";
			temp = temp->next;
		}
		outputFile << "\n";

	} // showCancelList()



	void removeFirstOne() {
		if (head != NULL) {
			if (head == tail) {
				delete(head);
				head = NULL;
				tail = NULL;
			}
			else {
				struct guest* temp = head->next;
				delete(head);
				head = temp;
			}
		}
	}

	void cleanThisList() {
		struct guest* cur = head;
		struct guest* next = head;

		while (cur != NULL) {
			next = cur->next;
			delete(cur);
			cur = next;
		}
		head = NULL;
		tail = NULL;
	}

}; // class guest_list

guest_list line_1;
guest_list line_2;
guest_list line_3;
guest_list queue_1;
guest_list chef_1_doing;
guest_list abortList;
guest_list timeoutList;

class Cook_list {

	struct cook {
		
		int CID;
		int freeTime;
		int freeTime_pre;
		guest_list queue;
		guest_list nowDoing;

		struct cook* prev;
		struct cook* next;

	};

	struct cook* head = NULL;
	struct cook* tail = NULL;

public:
	void addACook()
	{

		struct cook* temp = new cook;
		temp->CID = cooksInKitchen() + 1;
		temp->freeTime = 0;
		temp->freeTime_pre = 0;

		temp->prev = NULL;
		temp->next = NULL;

		// 如果隊伍原本是空的，就把head跟tail指向第一位客人
		if (head == NULL) {
			head = temp;
			tail = temp;
			return;
		}
		// if 上面成功執行 than return
		// else 繼續做底下的事
		// 也就是加在隊伍尾巴
		tail->next = temp;
		temp->prev = tail;
		tail = temp;

	}

	void cleanAllCooks() {

		struct cook* cur = head;
		struct cook* next = head;

		while (cur != NULL) {
			next = cur->next;
			delete(cur);
			cur = next;
		}
		head = NULL;
		tail = NULL;
	}

	bool isFreeNow( int nowTime, int CID ) {
		int freeTime = findACook(CID)->freeTime;
		if (nowTime >= freeTime) return true;
		else return false;
	}

	struct cook* findACook(int CID)
	{
		struct cook* temp = head;
		for (int i_in = 0; i_in < CID -1; i_in++) {
			temp = temp->next;
		}
		return temp;

	};

	int cooksInKitchen() {

		int counter = 0;
		struct cook* temp = head;
		if (temp == NULL) return 0;
		counter++;
		while (temp->next != NULL) {
			temp = temp->next;
			counter++;
		} // while

		return counter;
	}
	
}; // class cook

Cook_list kitchen_1;


char trash;

void mission_1()
{
	int fileNum;
	char fileNumStr[20] = { 0 };
	char fileName[30] = { 0 };
	char outputFileName[30] = { 0 };
	ifstream file;
	ofstream outputFile;
	clock_t start, stop;
	cout << "Input a file number (e.g., 401, 402, 403, ...):";
	cin >> fileNum;
	sprintf(fileNumStr, "%d", fileNum);
	strcat(fileName, "input");
	strcat(fileName, fileNumStr);
	strcat(fileName, ".txt");

	strcat(outputFileName, "sort");
	strcat(outputFileName, fileNumStr);
	strcat(outputFileName, ".txt");

	cout << fileName << "\n";


	file.open(fileName);
	// 如果有找到檔案
	if (file.is_open()) {

		if (file.peek() == EOF) {
			cout << "\nEmpty file is not supported, please try anothoer one ! \n";
			return;
		}
		start = clock();
		// 把第一行吃掉
		char trash;
		do {
			file.get(trash);
		} while (trash != '\n' && file.peek() != EOF);

		int OID;
		int Arrival;
		int Duration;
		int TimeOut;

		// 在結束之前
		// 把該顧客的資料依序讀入
		// 並將該顧客加到隊伍內
		while (file.peek() != EOF) {

			file >> OID;
			file >> Arrival;
			file >> Duration;
			file >> TimeOut;

			line_1.addAGuest(OID, Arrival, Duration, TimeOut);

			while (file.peek() == ' ' || file.peek() == '\n' || file.peek() == '	') {
				file.get(trash);
			}


		} // while

		stop = clock();
		int Reading_time = double(stop - start) * 1000 / CLOCKS_PER_SEC;

		cout << "\nBefore : \n";
		line_1.showAllGuest();

		start = clock();
		line_1.Shell_sort();
		stop = clock();
		int Sorting_time = double(stop - start) * 1000 / CLOCKS_PER_SEC;


		start = clock();
		line_1.storeAllGuest(outputFileName);
		stop = clock();
		int Writing_time = double(stop - start) * 1000 / CLOCKS_PER_SEC;

		cout << "After : \n";
		line_1.showAllGuest();
		line_1.cleanThisList();


		cout << "Reading data : " << Reading_time << " ms\n";
		cout << "Sorting data : " << Sorting_time << " ms\n";
		cout << "Writing data : " << Writing_time << " ms\n";

	} // 如果有找到檔案
	  // 如果沒找到檔案
	else {
		cout << "沒找到檔案\n";
	}

}

void newOrder(int nowTime, int &freeTime, int &freeTime_pre, int &i, bool chefCalling)
{
	int Delay = 0;
	bool keepRunning = true;
	// 如果此時有訂單要進來
	while (i < line_2.peopleInLine() && nowTime == line_2.findAGuest(i)->Arrival && keepRunning) {
		// 訂單進入佇列前，若發現佇列空間不足，就予以取消
		if (queue_1.peopleInLine() == 3) {
			// 把此訂單放入取消清單
			Delay = nowTime - line_2.findAGuest(i)->Arrival;
			totalDelay += Delay;
			abortList.addACancel(line_2.findAGuest(i)->OID, Delay, nowTime);
			i++;
		}
		// 佇列還有空間，但廚師正在忙，或正在抽單，就先將訂單先放入佇列
		else if (freeTime > line_2.findAGuest(i)->Arrival || chefCalling) {
			queue_1.addAGuest(line_2.findAGuest(i)->OID, line_2.findAGuest(i)->Arrival, line_2.findAGuest(i)->Duration, line_2.findAGuest(i)->TimeOut);
			i++;
			if (chefCalling) keepRunning = false;
		} // else if
		// 通過以上條件，廚師也有空，就直接執行了
		else if (freeTime <= line_2.findAGuest(i)->Arrival) {
			chef_1_doing.addAGuest(line_2.findAGuest(i)->OID, line_2.findAGuest(i)->Arrival, line_2.findAGuest(i)->Duration, line_2.findAGuest(i)->TimeOut);
			freeTime_pre = freeTime;
			freeTime = line_2.findAGuest(i)->Arrival + line_2.findAGuest(i)->Duration;
			// 把佇列中第一張單移除掉 (此處用途為何?)
			queue_1.removeFirstOne();
			i++;
		} // else if

	} // (如果此時有訂單要進來)

}

void storeFinalResult() {

	// abortList.storeCancelList();
	// timeoutList.storeTimeoutList();

	ofstream outputFile;
	outputFile.open(outputFileName, ios::app);
	outputFile << "[Total Delay] : " << totalDelay << " min\n";

	if (line_2.peopleInLine() == 0) outputFile << "[Failure Percentage] : Not Defined ! \n\n";
	else {
		double failurePercent;
		failurePercent = (double)(abortList.peopleInLine() + timeoutList.peopleInLine()) * 100 / line_2.peopleInLine();
		outputFile << "[Failure Percentage] : " << fixed << setprecision(2) << failurePercent << " %\n\n";
		outputFile.unsetf(ios::fixed);
	}
}

void storeFinalResult_V2() {

	// abortList.storeCancelList();
	// timeoutList.storeTimeoutList();

	ofstream outputFile;
	outputFile.open(outputFileName, ios::app);
	outputFile << "[Total Delay] : " << totalDelay << " min\n";

	if (line_3.peopleInLine() == 0) outputFile << "[Failure Percentage] : Not Defined ! \n\n";
	else {
		double failurePercent;
		failurePercent = (double)(abortList.peopleInLine() + timeoutList.peopleInLine()) * 100 / line_3.peopleInLine();
		outputFile << "[Failure Percentage] : " << fixed << setprecision(2) << failurePercent << " %\n\n";
		outputFile.unsetf(ios::fixed);
	}
}

void chef_1()
{
	ofstream outputFile;
	int freeTime = 0;
	int freeTime_pre = 0;
	int nowTime = 0;
	int Delay = 0;
	totalDelay = 0;
	double failurePercent;

	for (int i = 0; i < line_2.peopleInLine() || freeTime >= nowTime; nowTime++) {


		// 廚師上一件事情做好了，把目前的餐點交出去後，開始執行佇列中的任務
		if (nowTime > 0 && nowTime == freeTime) {

			// 廚師處理完訂單之後才發現已經逾時
			if (chef_1_doing.findAGuest(0)->TimeOut < nowTime) {
				// 就立即寫入『逾時清單』Timeout List
				// 三個欄位包括「訂單編號」、「延誤時間」Delay（多少分鐘）為廚師從佇列取出訂單的閒置時刻減去「下單時刻」、
				// 「完成時刻」Departure（第幾分鐘）為「下單時刻」加上「延誤時間」和「製作耗時」（Departure = Arrival + Delay + Duration）
				Delay = freeTime_pre - chef_1_doing.findAGuest(0)->Arrival;
				totalDelay += Delay;
				timeoutList.addATimeOut(chef_1_doing.findAGuest(0)->OID, Delay, chef_1_doing.findAGuest(0)->Arrival + Delay + chef_1_doing.findAGuest(0)->Duration);

				// 把目前這張單移除掉
				chef_1_doing.removeFirstOne();
				// 載入新訂單
				// newOrder(nowTime, freeTime, i);

			} // (廚師處理完訂單之後才發現已經逾時)
			  // 若沒有逾時
			  // 順利出貨
			else {
				// 把目前這張單移除掉
				chef_1_doing.removeFirstOne();
			} // (若沒有逾時)



			  // 廚師看佇列中的第一張單時，若發現已經逾時，就予以取消
			while (queue_1.peopleInLine() != 0 && queue_1.findAGuest(0)->TimeOut <= nowTime) {
				// 把此訂單放入取消清單
				Delay = nowTime - queue_1.findAGuest(0)->Arrival;
				totalDelay += Delay;
				abortList.addACancel(queue_1.findAGuest(0)->OID, Delay, nowTime);
				// 把佇列中第一張單移除掉
				queue_1.removeFirstOne();
				// 載入新訂單
				newOrder(nowTime, freeTime, freeTime_pre, i, true);
			}

			// 若是有機會做好，就開始執行
			// 事情做好的時間會是:現在時間+佇列中排第一張單所需的執行時間
			if (queue_1.peopleInLine() != 0) {
				chef_1_doing.addAGuest(queue_1.findAGuest(0)->OID, queue_1.findAGuest(0)->Arrival, queue_1.findAGuest(0)->Duration, queue_1.findAGuest(0)->TimeOut);
				freeTime_pre = freeTime;
				freeTime = nowTime + queue_1.findAGuest(0)->Duration;
				// 把佇列中第一張單移除掉
				queue_1.removeFirstOne();
			}



		} // if

		  // 載入新訂單
		newOrder(nowTime, freeTime, freeTime_pre, i, false);



	}

	outputFile.open(outputFileName);
	abortList.storeCancelList();
	timeoutList.storeTimeoutList();
	storeFinalResult();

	abortList.showCancelList();
	timeoutList.showTimeoutList();
	cout << "[Total Delay] : " << totalDelay << " min\n";

	if (line_2.peopleInLine() == 0 ) cout << "[Failure Percentage] : Not Defined ! \n\n";
	else {
		failurePercent = (double)(abortList.peopleInLine() + timeoutList.peopleInLine()) * 100 / line_2.peopleInLine();
		cout << "[Failure Percentage] : " << fixed << setprecision(2) << failurePercent << " %\n\n";
		cout.unsetf(ios::fixed);
	}


}

void mission_2()
{

	int fileNum;
	char fileNumStr[20] = { 0 };
	char fileName[30] = { 0 };
	ifstream file;
	ofstream outputFile;
	for (int i = 0; i < 30; i++) {
		outputFileName[i] = 0;
	}
	cout << "Input a file number (e.g., 401, 402, 403, ...):";
	cin >> fileNum;
	sprintf(fileNumStr, "%d", fileNum);
	strcat(fileName, "sort");
	strcat(fileName, fileNumStr);
	strcat(fileName, ".txt");

	strcat(outputFileName, "one");
	strcat(outputFileName, fileNumStr);
	strcat(outputFileName, ".txt");

	cout << fileName << "\n\n";


	file.open(fileName);
	// 如果有找到檔案
	if (file.is_open()) {

		if (file.peek() == EOF) {
			cout << "\nEmpty file is not supported, please try anothoer one ! \n";
			return;
		}

		// 把第一行吃掉
		char trash;
		do {
			file.get(trash);
		} while (trash != '\n' && file.peek() != EOF);

		int OID;
		int Arrival;
		int Duration;
		int TimeOut;

		// 在結束之前
		// 把該顧客的資料依序讀入
		// 並將該顧客加到隊伍內
		while (file.peek() != EOF) {

			file >> OID;
			file >> Arrival;
			file >> Duration;
			file >> TimeOut;

			line_2.addAGuest(OID, Arrival, Duration, TimeOut);

			while (file.peek() == ' ' || file.peek() == '\n' || file.peek() == '	') {
				file.get(trash);
			}

		} // while

		chef_1();

		// line_2.storeAllGuest( outputFileName );
		// line_2.showAllGuest();
		

		line_2.cleanThisList();

		queue_1.cleanThisList();
		abortList.cleanThisList();
		timeoutList.cleanThisList();


	} // 如果有找到檔案
	  // 如果沒找到檔案

	else {
		cout << "\nFile Not Found ! \n";
	} // else

}

int numOfFreeCook(int nowTime) {

	int counter = 0;
	for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
		if (kitchen_1.isFreeNow(nowTime, i + 1)) counter++;
	}

	return counter;
}

bool allQueueFull() {

	for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
		// 只要有一個沒有滿，那就回傳false
		if (kitchen_1.findACook(i+1)->queue.peopleInLine() < 3) return false;
	}
	return true;
}

bool onlyOneShortest(int &minLength) {

	int counter = 0;
	// 先找出最小的長度
	for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
		if (kitchen_1.findACook(i+1)->queue.peopleInLine() < minLength) minLength = kitchen_1.findACook(i+1)->queue.peopleInLine();
	}
	// 再看有沒有兩個(含)以上的佇列都是最小，且同長度
	for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
		if (kitchen_1.findACook(i+1)->queue.peopleInLine() == minLength) counter++;
	}
	if (counter == 1) return true;
	else return false;
}


void SQF(int nowTime, int &i_list, bool cookCalling) {
	int minCID;
	int minLength;
	int Delay = 0;

	bool keepRunning = true;
	// 如果此時有訂單要進來
	while (i_list < line_3.peopleInLine() && nowTime == line_3.findAGuest(i_list)->Arrival && keepRunning) {

		// 如果有任何一位廚師有空
		if (numOfFreeCook(nowTime) > 0) {
			// 如果有空的廚師剛好只有一位
			if (numOfFreeCook(nowTime) == 1) {
				minCID = 99999;
				for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
					// 找出有空的那一位廚師
					if (kitchen_1.isFreeNow(nowTime, i + 1)) minCID = kitchen_1.findACook(i+1)->CID;
				}
				// 那就把訂單交給他

			} // (如果有空的廚師剛好只有一位)

			// 若不只一位有空
			else {
				minCID = 99999;
				for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
					// 找出有空且編號最小的廚師
					if (kitchen_1.isFreeNow(nowTime, i + 1) && kitchen_1.findACook(i+1)->CID < minCID) minCID = kitchen_1.findACook(i+1)->CID;
				}
				// 使用最小編號的廚師來處理該筆訂單

			} // (若不只一位有空)

			// 上面的if跟else最後都要做這動作，所以移到這裡，共用程式碼
			// 使用有空且最小編號的廚師來處理該筆訂單
			kitchen_1.findACook(minCID)->nowDoing.addAGuest(line_3.findAGuest(i_list)->OID, line_3.findAGuest(i_list)->Arrival, line_3.findAGuest(i_list)->Duration, line_3.findAGuest(i_list)->TimeOut);
			kitchen_1.findACook(minCID)->freeTime_pre = kitchen_1.findACook(minCID)->freeTime;
			kitchen_1.findACook(minCID)->freeTime = line_3.findAGuest(i_list)->Arrival + line_3.findAGuest(i_list)->Duration;
			// 把佇列中第一張單移除掉 (此處用途為何?)
			kitchen_1.findACook(minCID)->queue.removeFirstOne();
			i_list++;

		} // (如果有任何一位廚師有空)
		// 如果都沒空
		else {

			// 如果每個佇列都全滿
			if (allQueueFull()) {

				// 把此訂單放入取消訂單，且把該廚師的ID登記為0 (因為根本沒人處裡)
				Delay = nowTime - line_3.findAGuest(i_list)->Arrival;
				totalDelay += Delay;
				abortList.addACancel(line_3.findAGuest(i_list)->OID, Delay, nowTime, 0);
				i_list++;

			} // (如果每個佇列都全滿)
			// 有佇列有空間
			else {
				minLength = 99999;
				if (onlyOneShortest(minLength)) {

					// 將此訂單放入最短的佇列中
					for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
						if (kitchen_1.findACook(i+1)->queue.peopleInLine() == minLength) {
							kitchen_1.findACook(i+1)->queue.addAGuest(line_3.findAGuest(i_list)->OID, line_3.findAGuest(i_list)->Arrival, line_3.findAGuest(i_list)->Duration, line_3.findAGuest(i_list)->TimeOut);
							i_list++;
						}
					}

				}
				// 兩個(含)以上的佇列一樣短
				else {

					minCID = 99999;
					for (int i = 0; i < kitchen_1.cooksInKitchen(); i++) {
						// 找出編號最小的廚師(的編號+1)
						if (kitchen_1.findACook(i+1)->CID < minCID) minCID = kitchen_1.findACook(i+1)->CID;
					}
					// 把該筆訂單放入最小編號的廚師的佇列
					kitchen_1.findACook(minCID)->queue.addAGuest(line_3.findAGuest(i_list)->OID, line_3.findAGuest(i_list)->Arrival, line_3.findAGuest(i_list)->Duration, line_3.findAGuest(i_list)->TimeOut);
					i_list++;
				}

			} // (有佇列有空間)

		} // (如果都沒空)

		if (cookCalling) keepRunning = false;

	} // (如果此時有訂單要進來)
}


void checkAndDo(int nowTime, int CID, int &i_list) {

	int Delay = 0;
	int Departure = 0;


	// 廚師上一件事情做好了，把目前的餐點交出去後，開始執行佇列中的任務
	if (nowTime > 0 && nowTime == kitchen_1.findACook(CID)->freeTime) {

		// 廚師處理完訂單之後才發現已經逾時
		if (kitchen_1.findACook(CID)->nowDoing.findAGuest(0)->TimeOut < nowTime) {
			// 就立即寫入『逾時清單』Timeout List
			// 三個欄位包括「訂單編號」、「延誤時間」Delay（多少分鐘）為廚師從佇列取出訂單的閒置時刻減去「下單時刻」、
			// 「完成時刻」Departure（第幾分鐘）為「下單時刻」加上「延誤時間」和「製作耗時」（Departure = Arrival + Delay + Duration）
			Delay = kitchen_1.findACook(CID)->freeTime_pre - kitchen_1.findACook(CID)->nowDoing.findAGuest(0)->Arrival;
			Departure = kitchen_1.findACook(CID)->nowDoing.findAGuest(0)->Arrival + Delay + kitchen_1.findACook(CID)->nowDoing.findAGuest(0)->Duration;
			totalDelay += Delay;
			timeoutList.addATimeOut(kitchen_1.findACook(CID)->nowDoing.findAGuest(0)->OID, Delay, Departure, CID);

			// 把目前這張單移除掉
			kitchen_1.findACook(CID)->nowDoing.removeFirstOne();
			// 載入新訂單
			// newOrder(nowTime, freeTime, i);

		} // (廚師處理完訂單之後才發現已經逾時)
		  // 若沒有逾時
		  // 順利出貨
		else {
			// 把目前這張單移除掉
			kitchen_1.findACook(CID)->nowDoing.removeFirstOne();
		} // (若沒有逾時)



		  // 廚師看佇列中的第一張單時，若發現已經逾時，就予以取消
		while (kitchen_1.findACook(CID)->queue.peopleInLine() != 0 && kitchen_1.findACook(CID)->queue.findAGuest(0)->TimeOut <= nowTime) {
			// 把此訂單放入取消清單
			Delay = nowTime - kitchen_1.findACook(CID)->queue.findAGuest(0)->Arrival;
			totalDelay += Delay;
			abortList.addACancel(kitchen_1.findACook(CID)->queue.findAGuest(0)->OID, Delay, nowTime, CID);
			// 把佇列中第一張單移除掉
			kitchen_1.findACook(CID)->queue.removeFirstOne();
			// 載入新訂單
			// newOrder(nowTime, freeTime, freeTime_pre, i, true);
			SQF(nowTime, i_list, true); // 但要注意只能抽一張
		}

		// 若是有機會做好，就開始執行
		// 事情做好的時間會是:現在時間+佇列中排第一張單所需的執行時間
		if (kitchen_1.findACook(CID)->queue.peopleInLine() != 0) {
			kitchen_1.findACook(CID)->nowDoing.addAGuest(kitchen_1.findACook(CID)->queue.findAGuest(0)->OID, kitchen_1.findACook(CID)->queue.findAGuest(0)->Arrival, kitchen_1.findACook(CID)->queue.findAGuest(0)->Duration, kitchen_1.findACook(CID)->queue.findAGuest(0)->TimeOut);
			kitchen_1.findACook(CID)->freeTime_pre = kitchen_1.findACook(CID)->freeTime;
			kitchen_1.findACook(CID)->freeTime = nowTime + kitchen_1.findACook(CID)->queue.findAGuest(0)->Duration;
			// 把佇列中第一張單移除掉
			kitchen_1.findACook(CID)->queue.removeFirstOne();
		}


	} // if

}

void mission_3_Core()
{
	int freeTime = 0;
	int freeTime_pre = 0;
	int nowTime = 0;
	int maxFreeTime = 0;
	int Delay = 0;
	totalDelay = 0;
	double failurePercent;

	for (int i = 0; i < line_3.peopleInLine() || maxFreeTime >= nowTime; nowTime++) {

		// 讓每個廚師都執行一次目前狀態檢查及操作
		for (int i_2 = 0; i_2 < kitchen_1.cooksInKitchen(); i_2++) {
			checkAndDo(nowTime, i_2 + 1, i);
		}

		// 載入新訂單
		// newOrder(nowTime, freeTime, freeTime_pre, i, false);
		SQF(nowTime, i, false);

		// 檢查還有沒有廚師在忙的，以免提前結束
		for (int i_3 = 0; i_3 < kitchen_1.cooksInKitchen(); i_3++) {
			if (kitchen_1.findACook(i_3 + 1)->freeTime > maxFreeTime) maxFreeTime = kitchen_1.findACook(i_3 + 1)->freeTime;
		}

	}

	abortList.storeCancelListWithCID();
	timeoutList.storeTimeoutListWithCID();
	storeFinalResult_V2();

	abortList.showCancelListWithCID();
	timeoutList.showTimeoutListWithCID();

	cout << "[Total Delay] : " << totalDelay << " min\n";

	if (line_3.peopleInLine() == 0) cout << "[Failure Percentage] : Not Defined ! \n\n";
	else {
		failurePercent = (double)(abortList.peopleInLine() + timeoutList.peopleInLine()) * 100 / line_3.peopleInLine();
		cout << "[Failure Percentage] : " << fixed << setprecision(2) << failurePercent << " %\n\n";
		cout.unsetf(ios::fixed);
	}

}


void mission_3()
{
	
	int fileNum;
	char fileNumStr[20] = { 0 };
	char fileName[30] = { 0 };
	ifstream file;
	ofstream outputFile;
	for (int i = 0; i < 30; i++) {
		outputFileName[i] = 0;
	}
	cout << "Input a file number (e.g., 401, 402, 403, ...):";
	cin >> fileNum;
	sprintf(fileNumStr, "%d", fileNum);
	strcat(fileName, "sort");
	strcat(fileName, fileNumStr);
	strcat(fileName, ".txt");

	strcat(outputFileName, "two");
	strcat(outputFileName, fileNumStr);
	strcat(outputFileName, ".txt");

	cout << fileName << "\n\n";
	
	int cooksNum;
	cout << "How many cooks would you want ? ";
	cin >> cooksNum;
	for (int i = 0; i < cooksNum; i++) {
		kitchen_1.addACook();
	}
	

	file.open(fileName);
	// 如果有找到檔案
	if (file.is_open()) {

		if (file.peek() == EOF) {
			cout << "\nEmpty file is not supported, please try anothoer one ! \n";
			return;
		}

		// 把第一行吃掉
		char trash;
		do {
			file.get(trash);
		} while (trash != '\n' && file.peek() != EOF);

		int OID;
		int Arrival;
		int Duration;
		int TimeOut;

		// 在結束之前
		// 把該顧客的資料依序讀入
		// 並將該顧客加到隊伍內
		while (file.peek() != EOF) {

			file >> OID;
			file >> Arrival;
			file >> Duration;
			file >> TimeOut;

			line_3.addAGuest(OID, Arrival, Duration, TimeOut);

			while (file.peek() == ' ' || file.peek() == '\n' || file.peek() == '	') {
				file.get(trash);
			}

		} // while

		// line_3.showAllGuest();

		mission_3_Core();

		// line_3.storeAllGuest( outputFileName );
		// line_3.showAllGuest();


		line_3.cleanThisList();

		// queue.cleanThisList();
		abortList.cleanThisList();
		timeoutList.cleanThisList();


	} // 如果有找到檔案
	// 如果沒找到檔案
	else {
		cout << "\nFile Not Found ! \n";
	} // else

	kitchen_1.cleanAllCooks();
}


int main()
{

	char work_type[20];

	do {
		cout << "Simulate FIFO Queues by SQF\n";
		cout << "0. Quit\n";
		cout << "1. Sort a file\n";
		cout << "2. Simulate one FIFO queue\n";
		cout << "3. Simulate two queues by SQF\n";
		cout << "Input a command(0, 1, 2, 3):";

		do {
			cin >> work_type;
		} while (cin.peek() != '\n');

		if (strcmp(work_type, "1") == 0) {
			mission_1();
		} // if
		else if (strcmp(work_type, "2") == 0) {
			mission_2();
		} // if
		else if (strcmp(work_type, "3") == 0) {
			mission_3();
		} // if


		else if (strcmp(work_type, "0") != 0) {
			cout << "\nCommand Not Found ! \n";
		} // if


		cout << "\n";

	} while (strcmp(work_type, "0") != 0); // do


	return 0;
}


