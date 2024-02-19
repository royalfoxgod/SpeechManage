#include	<iostream>
using namespace std;
#include	<string>
#include	"SpeechManager.h"
#include	<time.h>
int main(){
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	int choice = 0;
	while (true){
		sm.show_Menu();
		cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}