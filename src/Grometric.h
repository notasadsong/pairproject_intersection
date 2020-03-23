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

class Solve 
{
public:
	void LLintersect(set<pair<double, double>, cmp>* intersections, Line l1, Line l2)
	{
		if (!l1.parallel(l2))
		{
			double x = (l1.c * l2.b - l2.c * l1.b) / (l2.a * l1.b - l1.a * l2.b);
			double y = (l1.a * l2.c - l2.a * l1.c) / (l2.a * l1.b - l1.a * l2.b);
			intersections->insert(make_pair(x, y));
		}

	}

	void LRintersect(set<pair<double, double>, cmp>* intersections, Line l, Line r) 
	{
		set<pair<double, double>, cmp> temp;

		LLintersect(&temp, l, r);
		for (auto it : temp) {
			if (r.isInR(it.first, it.second))
			{
				intersections->insert(it);
			}
		}

	}

	void LSintersect(set<pair<double, double>, cmp>* intersections, Line l, Line s)
	{
		//判断线段两个端点是否在直线两侧，只有不在同一侧时才有交点
		if (l.calc(s.x0, s.y0) * l.calc(s.x1, s.y1) <= 0)
		{
			LLintersect(intersections, l, s);
		}
	}

	void RRintersect(set<pair<double, double>, cmp>* intersections, Line r1, Line r2)
	{
		set<pair<double, double>, cmp> temp;

		LLintersect(&temp, r1, r2);
		for (auto it : temp) {
			if (r1.isInR(it.first, it.second) && r2.isInR(it.first, it.second))
			{
				intersections->insert(it);
			}
		}

	}

	void SSintersect(set<pair<double, double>, cmp>* intersections, Line s1, Line s2)
	{
		if (s1.calc(s2.x0, s2.y0) * s1.calc(s2.x1, s2.y1) <= 0 
			&& s2.calc(s1.x0, s1.y0) * s2.calc(s1.x1, s1.y1) <= 0)
		{
			LLintersect(intersections, s1, s2);
		}
	}

	void SRintersect(set<pair<double, double>, cmp>* intersections, Line s, Line r)
	{
		if (r.calc(s.x0, s.y0) * r.calc(s.x1, s.y1) <= 0)
		{
			LRintersect(intersections, s, r);
		}
	}

	void LCintersect(set<pair<double, double>, cmp>* intersections, Line l, Circle c)
	{
		double dis = l.disPL(c.x, c.y);
		if (dis > c.r) return;
		//先找到圆心在直线上的投影点,用与直线垂直的线做交点得到
		Line l_(l.b, -l.a, c.y * l.a - c.x * l.b);

		set<pair<double, double>, cmp> temp;
		LLintersect(&temp, l, l_);
		pair<double, double> p;
		for (auto it : temp) p = it;
		if (dis < c.r) {
			double delta_x = l.b * sqrt((c.r * c.r - dis * dis) / (l.a * l.a + l.b * l.b));
			double delta_y = - l.a * sqrt((c.r * c.r - dis * dis) / (l.a * l.a + l.b * l.b));
			intersections->insert(make_pair(p.first + delta_x, p.second + delta_y));
			intersections->insert(make_pair(p.first - delta_x, p.second - delta_y));
		}
		else {
			intersections->insert(p);
			return;
		}
	}

	void RCintersect(set<pair<double, double>, cmp>* intersections, Line r, Circle c)
	{
		set<pair<double, double>, cmp> temp;
		LCintersect(&temp, r, c);
		for (auto it : temp)
		{
			if (r.isInR(it.first, it.second)) intersections->insert(it);
		}
	}

	void SCintersect(set<pair<double, double>, cmp>* intersections, Line s, Circle c)
	{
		set<pair<double, double>, cmp> temp;
		LCintersect(&temp, s, c);
		for (auto it : temp)
		{
			if (s.isInS(it.first, it.second)) intersections->insert(it);
		}
	}

	void CCintersect(set<pair<double, double>, cmp>* intersections, Circle c1, Circle c2)
	{
		double dis_center = sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
		//外离
		if (dis_center > c2.r + c1.r) return;
		//包含
		if (dis_center < fabs(c2.r - c1.r)) return;
		//有交点
		double a_ = -2 * (c2.x - c1.x);
		double b_ = -2 * (c2.y - c1.y);
		double c_ = c2.x * c2.x + c2.y * c2.y - c2.r * c2.r - c1.x * c1.x - c1.y * c1.y + c1.r * c1.r;
		Line l_(a_, b_, c_);

		LCintersect(intersections, l_, c1);
	}

};