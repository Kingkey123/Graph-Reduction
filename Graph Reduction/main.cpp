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

void solve()//在solve这里每次solve一次，改掉DBGraph中的数据
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