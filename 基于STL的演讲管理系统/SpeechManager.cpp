#include	"SpeechManager.h"

SpeechManager::SpeechManager(){
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
SpeechManager::~SpeechManager(){

}
void SpeechManager::clearRecord(){
	cout << "�Ƿ�����ļ�?" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1){
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::showRecord(){
	if (this->fileIsEmpty){
		cout << "�ļ�Ϊ�ջ��߲����ڣ�" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++){
		cout << "��" << i + 1 << "��"
			<< "�ھ����:" << this->m_Record[i][0]
			<< "�÷֣�" << this->m_Record[i][1] << " "
			<< "�Ǿ����:" << this->m_Record[i][2]
			<< "�÷֣�" << this->m_Record[i][3] << " "
			<< "�������:" << this->m_Record[i][4]
			<< "�÷֣�" << this->m_Record[i][5] << " " << endl;

	}
	system("pause");
	system("cls");
}
void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem(){
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::saveRecord(){
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin();
		it != vVictory.end(); it++){
		ofs << *it << "," 
			<< this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��ѱ���!" << endl;
	this->fileIsEmpty = false; 
}

void SpeechManager::loadRecord(){
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()){
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()){
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data){
		//cout << data << endl;
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true){
			
			pos = data.find(",", start);
			if (pos == -1){
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeechManager::initSpeech(){
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker(){
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++){
			sp.m_Score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

void SpeechManager::startSpeech(){
	startDraw();
	speechContest();
	showScore();
	this->m_Index++;
	startDraw();
	speechContest();
	showScore();saveRecord();
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
	
	cout << "����������!" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::startDraw(){
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------" << endl;
	cout << "��ǩ����ݽ�ѭ�����£�" << endl;
	if (this->m_Index == 1){
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();
			it != v1.end(); it++){
			cout << *it << " ";
		}
		cout << endl;

	}
	else{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();
			it != v2.end(); it++){
			cout << *it << " ";

		}
		cout << endl;

	}
	cout << "------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::speechContest(){
	cout << "------------- ��" << this->m_Index << "����ʽ������ʼ��------------- " << endl;

	multimap<double, int, greater<int>> groupScore; //��ʱ����������key���� value ѡ�ֱ��

	int num = 0; //��¼��Ա����6��Ϊ1��

	vector <int>v_Src;   //��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());				//����
		d.pop_front();												//ȥ����߷�
		d.pop_back();												//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);				//��ȡ�ܷ�
		double avg = sum / (double)d.size();									//��ȡƽ����

		//ÿ����ƽ����
		//cout << "��ţ� " << *it  << " ѡ�֣� " << this->m_Speaker[*it].m_Name << " ��ȡƽ����Ϊ�� " << avg << endl;  //��ӡ����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{

			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ������ " << this->m_Speaker[it->second].m_Name << " �ɼ��� " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();

			cout << endl;

		}
	}
	cout << "------------- ��" << this->m_Index << "�ֱ������  ------------- " << endl;
	system("pause");
}

void SpeechManager::showScore(){
	cout << "-----------��" << this->m_Index
		<< "�ֽ�����ѡ����Ϣ���£�" << endl;
	vector<int>v;
	if (this->m_Index == 1){
		v = v2;
	}
else
{
	v = vVictory;
}
	for (vector<int>::iterator it = v.begin();
		it != v.end(); it++){
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_Speaker[*it].m_Name << " �÷֣� " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}