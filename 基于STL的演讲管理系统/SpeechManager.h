#pragma once
#include	<iostream>
#include	"speaker.h"
using namespace std;
#include	<vector>
#include	<map>
#include	<algorithm>
#include	<functional>
#include	<numeric>
#include	<deque>
#include	<string>
#include	<fstream>

class SpeechManager{
public:
	SpeechManager();
	~SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeech();
	void createSpeaker();
	void startSpeech();
	void startDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void showRecord();
	void clearRecord();

	bool fileIsEmpty;
	map<int, vector<string>>m_Record;
	
	vector<int>v1;
	vector<int>v2;
	vector<int>vVictory;
	map<int, Speaker> m_Speaker;
	int m_Index;
};