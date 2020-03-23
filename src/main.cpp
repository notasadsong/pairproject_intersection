#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<utility>
//#include "Grometric.h"
#include "core.h"
#include<windows.h>

#pragma comment(lib,"pairproject_dll.lib")

using namespace std;

void getInput(vector<Line>* lines, vector<Circle>* circles, int argc, char* argv[]) 
{
	ifstream input;
	int n, i;

	input = ifstream(argv[2]);

	input >> n;
	char op;
	int a, b, c, d;
	for (i = 0; i < n; i++) 
	{
		input >> op;
		if (op == 'L' || op == 'S' || op == 'R') 
		{
			input >> a >> b >> c >> d;
			Line l((double)a, (double)b, (double)c, (double)d, op);
			lines->push_back(l);
		}
		else 
		{
			input >> a >> b >> d;
			Circle c((double)a, (double)b, (double)d);
			circles->push_back(c);
		}
	}

}

void getIntersection(vector<Line> lines, vector<Circle> circles, set<pair<double, double>, cmp>* intersections)
{

	Solve solve;

	for (unsigned int i = 0; i < lines.size(); i++) 
	{
		for (unsigned int j = i + 1; j < lines.size(); j++)
		{
			if (lines[i].type == 'L' && lines[j].type == 'L')  solve.LLintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'R') solve.RRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'S' && lines[j].type == 'S') solve.SSintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'L') solve.LRintersect(intersections, lines[j], lines[i]);
			else if (lines[i].type == 'L' && lines[j].type == 'R') solve.LRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'L' && lines[j].type == 'S') solve.LSintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'S' && lines[j].type == 'L') solve.LSintersect(intersections, lines[j], lines[i]);
			else if (lines[i].type == 'S' && lines[j].type == 'R') solve.SRintersect(intersections, lines[i], lines[j]);
			else if (lines[i].type == 'R' && lines[j].type == 'S') solve.SRintersect(intersections, lines[j], lines[i]);
		}
	}
	
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		for (unsigned int j = 0; j < circles.size(); j++)
		{
			if (lines[i].type == 'L') solve.LCintersect(intersections, lines[i], circles[j]);
			else if (lines[i].type == 'R') solve.RCintersect(intersections, lines[i], circles[j]);
			else if (lines[i].type == 'S') solve.SCintersect(intersections, lines[i], circles[j]);
		}
	}

	for (unsigned int i = 0; i < circles.size(); i++)
	{
		for (unsigned int j = i + 1; j < circles.size(); j++) solve.CCintersect(intersections, circles[i], circles[j]);
	}
}

int main(int argc, char* argv[]) 
{
	vector<Line> lines;
	vector<Circle> circles;
	set<pair<double, double>, cmp> intersections;

	getInput(&lines, &circles, argc, argv);
	
	getIntersection(lines, circles, &intersections);

	ofstream output;
	output = ofstream(argv[4]);
	output << intersections.size() << endl;
}
