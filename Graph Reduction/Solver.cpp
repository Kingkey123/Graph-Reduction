#include "Solver.h"

void Solver::init(bool _isOutput)
{
	ofstream fout;
	fout.open("time.txt");
	fout.close();

	queryPath.clear();
	DBGraph.clear();
	QueryGraph.clear();
	outputPath.clear();

	isOutput = _isOutput;
}

void Solver::Dataset() {
	dbPath = "Data/mygraphdb.data";
	queryPath.push_back("Data/four_circle_1.my");
	queryPath.push_back("Data/four_circle_2.my");
	queryPath.push_back("Data/other_graphs.my");
	queryPath.push_back("Data/three_circle.my");
	

	// Test data set
	/*dbPath = "db.txt";
	queryPath.push_back("query.txt");*/
}

void Solver::ReadFile(string path, vector<Graph> &vec)
{
	vec.clear();

	ifstream fin;
	fin.open(path.c_str());

	Graph tmp;
	string buff;
	int n;
	int m, l;
	int p, q;
	while (getline(fin, buff))
	{
		//cout << buff << endl;
		//getchar();//ÿ���ĵ���
		if (buff.size() == 0) continue;
		if (buff == "t # -1")
		{
			vec.push_back(tmp);
			
			break;
		}
		if (buff[0] == 't')
		{
			sscanf_s(buff.c_str(), "t # %d", &n);
			if (n == 0) continue;
			vec.push_back(tmp);
			
			tmp.init();
		}
		else if (buff[0] == 'v')
		{
		sscanf_s(buff.c_str(), "v %d %d", &m, &l);
		tmp.addv(m, l);
		}
		else if (buff[0] == 'e')
		{
		sscanf_s(buff.c_str(), "e %d %d %d", &p, &q, &l);
		tmp.adde(p, q, l);
		}
		else puts("Error!");
	}

	fin.close();
}

void Solver::ReadDB(string path)
{
	ReadFile(path, DBGraph);
}

void Solver::ReadQuery(string path)
{
	ReadFile(path, QueryGraph);
}


void Solver::input()
{
	ofstream fout;

	// Standard data set
	Dataset();

	// Output path: ./Output/ans_.txt
	_rmdir("Output");
	_mkdir("Output");
	string tt = "Output/ans";
	for (int i = 0; i < (int)queryPath.size(); i++)
		outputPath.push_back(tt + (char)(i + '1') + ".txt");


	for (int i = 0; i < (int)outputPath.size(); i++)
	{
		fout.open(outputPath[i].c_str());
		fout.close();
	}

	ReadDB(dbPath);
	puts("Read Data Finished!");
}

void Solver::PrintQueryAns(int id, int cnt)
{
	/*ofstream fout;
	fout.open(outputPath[id].c_str(), ios::app);

	fout << "+++++" << endl;
	fout << "Query ID: " << vf2.QueryID << endl;
	fout << "Count: " << vf2.match.size() << endl;

	// Not output match details
	fout << "Match List:" << endl;
	for (int i = 0; i < (int)vf2.match.size(); i++)
		fout << vf2.QueryID << " " << vf2.match[i] << endl;

	// Output match details
	for (int i = 0; i < (int)vf2.match.size(); i++)
	{
		fout << "-----" << endl;
		fout << "Graph ID: " << vf2.match[i] << endl;
		fout << "pat" << "\t" << "g" << endl;*/
		// Not output match details
		/*for (int j = 0;j < (int)vf2.match[i].s.size();j++)
			fout << vf2.match[i].s[i].first << "\t" << vf2.match[i].s[i].second << endl;*/
		/*fout << "-----" << endl;
	}

	fout << "+++++" << endl;

	fout << endl;

	fout.close();*/
}




void Solver::solve()
{
	//cout << "SOLBE ONCE" << endl;
	int matches;//����Ƿ�match�ķ���ֵ
	bool isContract;
	time_t stTime, edTime;
	int flag = 0;
	vf2.init(DBGraph);//��ʱ��solve�е�DBGraph����Vf2�е�DBGraph
	ReadFile("Data/two_circle.my",two_Circle);



	ofstream ftimeout;
	ftimeout.open("time.txt", ios::app);
	//Quantity of file input in Dataset

	for (int k = 0;k < (int)DBGraph.size();k++) {////��ô���solve ��Ҫ��ͼ���м�⣬solve�����Ӳ��������Ƿ���1��solve�������Ѿ����㣬���Ƿ���0�������Ҳ�����������ˣ����˳���������һ��while(true or false)����
		tempGraph = DBGraph;//�����ʼֵ
	
		here:
		struct VF2::State tempState;//��ʼ��ÿ�ε�stateһ��ʼΪ��
		for (int i = 0; i < (int)queryPath.size(); i++)//��ÿ������ʱreadQuery����ÿ��inputʱreadData
		{
			if (i == 0) {//queryPath == 0, Data/four_circle_1.my ��ŵ�һ������Ȧ
				ReadQuery(queryPath[i]);
				stTime = clock();

				cout << "QueryGraph.size: " << (int)QueryGraph.size() << endl;

				for (int j = 0; j < (int)QueryGraph.size(); j++)
				{
					if (QueryGraph[j].vn > tempGraph[0].vn || QueryGraph[j].en > tempGraph[0].en) continue;
					//cout << "Query four_circle_1 " << queryPath[i] << ": id : " << j << endl;
					if (j == 0) {
						isContract = 0;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1||matches == 2) {
							tempState = vf2.finalState;
						}
						else {
							tempState = VF2::State();
							break;
						}


						cout << " Four circle Matches found " << matches << endl;
					}
					if (j == 1) {
						//cout << "test1" << endl;
						isContract = 0;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						//cout << "cout tempState" << endl;
						//for (auto ite = tempState.s.begin(); ite != tempState.s.end(); ite++)
							//cout << ite->first << " " << ite->second << endl;//�����Ӧ������id
						//cout << "matches: " << matches << endl;
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1 || matches == 2) {
							tempState = vf2.finalState;
						}
						else {
							tempState = VF2::State();
							break;
						}
							

						cout << " Double Four circle Matches found " << matches << endl;
					}
					if (j == 2) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L1 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt",tempGraph);
							goto here;
							
						}
						if (matches == 2) {//���ر�
							cout << " L1 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);//�ȶ�ͼ
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}
							
							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}

						
					}
					if (j == 3) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L3 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							goto here;
						}
						if (matches == 2) {
							cout << " L3 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}
					}
					if (j == 4) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L4 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							goto here;
						}
						if (matches == 2) {
							cout << " L4 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}
					}
					if (j == 5) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L6 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							goto here;
						}
						if (matches == 2) {
							cout << " L6 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}
					}
				}

				edTime = clock();
				double dur = (double)(edTime - stTime) / 1000.0;

				ftimeout << queryPath[i] << " Time: " << dur << endl;
				cout << queryPath[i] << " Time: " << dur << endl;
				cout << endl;
			}

			if (i == 1) {//queryPath == 1, ��Ȧ2��
				ReadQuery(queryPath[i]);

				stTime = clock();

				for (int j = 0; j < (int)QueryGraph.size(); j++)
				{
					if (QueryGraph[j].vn > tempGraph[0].vn || QueryGraph[j].en > tempGraph[0].en) continue;
					//cout << "Query four_circle_1 " << queryPath[i] << ": id : " << j << endl;
					if (j == 0) {
						isContract = 0;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j,tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1 || matches == 2) {
							tempState = vf2.finalState;
						}
						else {
							tempState = VF2::State();
							break;
						}
							

						cout << " Four circle Matches found " << matches << endl;
					}
					if (j == 1) {
						isContract = 0;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1 || matches == 2) {
							tempState = vf2.finalState;
						}
						else {
							tempState = VF2::State();
							break;
						}


						cout << " Double Four circle_2 Matches found " << matches << endl;
					}
					if (j == 2) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L5 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							goto here;
						}
						if (matches == 2) {
							cout << " L5 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}

					}
					if (j == 3) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j,  tempState,isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " L7 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							goto here;
						}
						if (matches == 2) {
							cout << " L7 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << "two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;
						}
					}
				}

				edTime = clock();
				double dur = (double)(edTime - stTime) / 1000.0;

				ftimeout << queryPath[i] << " Time: " << dur << endl;
				cout << queryPath[i] << " Time: " << dur << endl;
				cout << endl;
			}

			if (i == 2) {//queryPath == 2, otehr graphs. now is only K33
				ReadQuery(queryPath[i]);
				stTime = clock();

				for (int j = 0; j < (int)QueryGraph.size(); j++)
				{
					if (QueryGraph[j].vn > tempGraph[0].vn || QueryGraph[j].en > tempGraph[0].en) continue;
					//cout << "Query threecircle_1 " << queryPath[i] << ": id : " << j << endl;
					if (j == 0) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " K33 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);

							edTime = clock();
							double dur = (double)(edTime - stTime) / 1000.0;


							ftimeout << queryPath[i] << " Time: " << dur << endl;
							cout << queryPath[i] << " Time: " << dur << endl;
							cout << endl;

							goto here;
						}
						if (matches == 2) {
							cout << " K33 Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							isContract = 1;
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << " Two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							edTime = clock();
							double dur = (double)(edTime - stTime) / 1000.0;


							ftimeout << queryPath[i] << " Time: " << dur << endl;
							cout << queryPath[i] << " Time: " << dur << endl;
							cout << endl;

							goto here;
						}
						else {
							tempState = VF2::State();
							continue;

						}

						cout << " K33 Matches found " << matches << endl;
					}
				}

				edTime = clock();
				double dur = (double)(edTime - stTime) / 1000.0;


				ftimeout << queryPath[i] << " Time: " << dur << endl;
				cout << queryPath[i] << " Time: " << dur << endl;
				cout << endl;
				if (flag == 1)//��������˳�����ѭ��
					break;
			}

			if (i == 3) {//queryPath == 2, ��Ȧ
				ReadQuery(queryPath[i]);
				stTime = clock();

				for (int j = 0; j < (int)QueryGraph.size(); j++)
				{
					if (QueryGraph[j].vn > tempGraph[0].vn || QueryGraph[j].en > tempGraph[0].en) continue;
					//cout << "Query threecircle_1 " << queryPath[i] << ": id : " << j << endl;
					if (j == 0) {
						isContract = 1;
						matches = vf2.vf2(QueryGraph[j], tempGraph[0], j, tempState, isOutput, isContract);
						/*if (isOutput)
							PrintQueryAns(i, matches);*/
						if (matches == 1) {
							cout << " Three circle Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);

							edTime = clock();
							double dur = (double)(edTime - stTime) / 1000.0;


							ftimeout << queryPath[i] << " Time: " << dur << endl;
							cout << queryPath[i] << " Time: " << dur << endl;
							cout << endl;

							goto here;
						}
						if (matches == 2) {
							cout << " Three circle Matches found " << matches << endl;
							ReadFile("Temp/temp.txt", tempGraph);
							isContract = 1;
							while (matches == 2) {
								isContract = 1;
								matches = vf2.contract2(tempGraph[0]);
								//matches = vf2.vf2(two_Circle[0], tempGraph[0], j , isOutput, isContract);
								cout << " Two_Circle Matches found" << matches << endl;
								ReadFile("Temp/temp.txt", tempGraph);
							}

							edTime = clock();
							double dur = (double)(edTime - stTime) / 1000.0;


							ftimeout << queryPath[i] << " Time: " << dur << endl;
							cout << queryPath[i] << " Time: " << dur << endl;
							cout << endl;

							goto here;
						}
						else {
							flag = 1;
							
							//output();
							break;//��Ȧ���Ҳ��� �Ѿ�����������㣬��һ����ʼֵ����
							
						}

						cout << " Three circle Matches found " << matches << endl;
					}
				}

				edTime = clock();
				double dur = (double)(edTime - stTime) / 1000.0;

				
				ftimeout << queryPath[i] << " Time: " << dur << endl;
				cout << queryPath[i] << " Time: " << dur << endl;
				cout << endl;
				if (flag == 1)//��������˳�����ѭ��
					break;
			}
		}
		
	}
	
	ftimeout.close();
}

int Solver::output()
{
	ifstream fin("Temp/temp.txt"); //Դ�ļ���
	ofstream fout;
	fout.open("Output/ans.txt",ios::app); //Ŀ���ļ�д
	if (!fin) {
		cout << "open source file error!" << endl;
		return -1;
	}
	while (!fin.eof()) //�ļ�δ������ѭ��
	{
		char str[1024];
		fin.getline(str, sizeof(str), '\n'); //��һ��
		//cout << str << endl; //�������Ļ
		fout << str << endl; //������ļ�
	}
	fin.close();
	fout.close();
	return 0;

}