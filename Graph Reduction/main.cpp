#include "Solver.h"

Solver solver;

void init()
{
	// 0: no output matching ans, 1: output matching ans
	solver.init(1);
}

void input()
{
	solver.input();//input ReadDB ReadFile(path, DBGraph);
}

void solve()//��solve����ÿ��solveһ�Σ��ĵ�DBGraph�е�����
{
	solver.solve();
}

void output()
{
	solver.output();
}

int main()
{
	init();
	input();
	solve();
	output();
}