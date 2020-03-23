#pragma once
#include<set>
#include<cmath>
#include<utility>

using namespace std;

#define EPS (1e-12)
#define equal_(a,b) (fabs((a) - (b)) < EPS)

class Line {

public:

	double a, b, c;
	char type;  //L, S, R分别代表直线，线段，射线
	double x0, y0, x1, y1;

	Line(double x_0, double y_0, double x_1, double y_1, char t) {
		//将直线的ax+by+c=0中的系数求出
		a = y_1 - y_0;
		b = x_0 - x_1;
		c = x_1 * y_0 - x_0 * y_1;
		type = t;
		x0 = x_0;
		y0 = y_0;
		x1 = x_1;
		y1 = y_1;
	}

	Line(double a0, double b0, double c0) {
		a = a0;
		b = b0;
		c = c0;
		type = 'L';
		x0 = 0;
		y0 = 0;
		x1 = 0;
		y1 = 0;
	}

	bool parallel(Line l) {
		return (l.a * b == l.b * a);
	}

	double calc(double x, double y)
	{
		return a * x + b * y + c;
	}

	double disPL(double x, double y)
	{
		return fabs(calc(x, y)) / sqrt(a * a + b * b);
	}

	bool isInS(double x, double y)
	{
		if ((x - x0) * (x - x1) <= 0) return true;
		else return false;
	}

	bool isInR(double x, double y)
	{
		if ((x - x0) * (x1 - x0) >= 0) return true;
		else return false;
	}

};

class Circle {

public:

	double x, y, r;

	Circle(double x1, double y1, double r1) {
		x = x1;
		y = y1;
		r = r1;
	}
};

struct cmp
{
	bool operator() (const pair<double, double> a, const pair<double, double> b) const
	{
		if (equal_(a.first, b.first) && equal_(a.second, b.second)) {
			return false;
		}
		else if (!equal_(a.first, b.first))
		{
			return a.first < b.first;
		}
		else
		{
			return a.second < b.second;
		}
	}
};

class _declspec(dllexport) Solve
{
public:
	void LLintersect(set<pair<double, double>, cmp>* intersections, Line l1, Line l2);

	void LRintersect(set<pair<double, double>, cmp>* intersections, Line l, Line r);

	void LSintersect(set<pair<double, double>, cmp>* intersections, Line l, Line s);

	void RRintersect(set<pair<double, double>, cmp>* intersections, Line r1, Line r2);

	void SSintersect(set<pair<double, double>, cmp>* intersections, Line s1, Line s2);

	void SRintersect(set<pair<double, double>, cmp>* intersections, Line s, Line r);

	void LCintersect(set<pair<double, double>, cmp>* intersections, Line l, Circle c);

	void RCintersect(set<pair<double, double>, cmp>* intersections, Line r, Circle c);

	void SCintersect(set<pair<double, double>, cmp>* intersections, Line s, Circle c);

	void CCintersect(set<pair<double, double>, cmp>* intersections, Circle c1, Circle c2);

};


