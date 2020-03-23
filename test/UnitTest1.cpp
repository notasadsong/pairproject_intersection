#include "pch.h"
#include "CppUnitTest.h"
#include "../PairProject/Grometric.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		Solve solve;

		///////////////////////////测试直线与直线求交点////////////////////////////

		TEST_METHOD(TestMethod1) //LL非平行
		{
			set<pair<double, double>, cmp> inter;
			Line l1(0, 0, 1, 1, 'L');
			Line l2(0, 0, 0, 1, 'L');

			solve.LLintersect(&inter, l1, l2);
			pair<double, double> p = *inter.begin();
			
			Assert::AreEqual(true, p.first == 0 && p.second == 0);
		}

		TEST_METHOD(TestMethod2) //SL非平行有交点
		{
			set<pair<double, double>, cmp> inter;
			Line l(1, 1, 2.5, 0, 'L');
			Line s(-1, 5, 1, 1, 'S');

			solve.LSintersect(&inter, l, s);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 1 && p.second == 1);
		}

		TEST_METHOD(TestMethod3) //RL非平行有交点
		{
			set<pair<double, double>, cmp> inter;
			Line l(1, 1, 2.5, 0, 'L');
			Line r(-1, 5, 1, 1, 'R');

			solve.LRintersect(&inter, l, r);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 1 && p.second == 1);
		}

		TEST_METHOD(TestMethod4) //SS非平行有交点
		{
			set<pair<double, double>, cmp> inter;
			Line s1(1, 1, 2.5, 0, 'S');
			Line s2(-1, 5, 1, 1, 'S');

			solve.SSintersect(&inter, s1, s2);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 1 && p.second == 1);
		}

		TEST_METHOD(TestMethod5) //SR非平行有交点
		{
			set<pair<double, double>, cmp> inter;
			Line s(1, 1, 2.5, 0, 'S');
			Line r(-1, 5, 1, 1, 'R');

			solve.SRintersect(&inter, s, r);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 1 && p.second == 1);
		}

		TEST_METHOD(TestMethod6) //RR非平行有交点
		{
			set<pair<double, double>, cmp> inter;
			Line r1(1, 1, 2.5, 0, 'R');
			Line r2(-1, 5, 1, 1, 'R');

			solve.RRintersect(&inter, r1, r2);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 1 && p.second == 1);
		}

		TEST_METHOD(TestMethod7) //线平行
		{
			set<pair<double, double>, cmp> inter;
			Line l1(0, 0, 1, 0, 'L');
			Line l2(0, 1, 1, 1, 'L');
			Line r1(0, 2, 1, 2, 'R');
			Line r2(0, 3, 1, 3, 'R');
			Line s1(0, 4, 1, 4, 'S');
			Line s2(0, 5, 1, 5, 'S');

			solve.LLintersect(&inter, l1, l2);
			solve.LRintersect(&inter, l1, r1);
			solve.LSintersect(&inter, l1, s1);
			solve.SRintersect(&inter, s1, r1);
			solve.SSintersect(&inter, s1, s2);
			solve.RRintersect(&inter, r1, r2);

			Assert::AreEqual(true, inter.size() == 0);
		}

		///////////////////////////////测试直线与圆求交点////////////////////////////////////

		TEST_METHOD(TestMethod8) //相离
		{
			set<pair<double, double>, cmp> inter;
			Line l(2, 2, 4, 2, 'L');
			Circle c(1, 0, 1);

			solve.LCintersect(&inter, l, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod9) //相切
		{
			set<pair<double, double>, cmp> inter;
			Line l(2, 2, 4, 2, 'L');
			Circle c(2, 0, 2);

			solve.LCintersect(&inter, l, c);
			pair<double, double> p = *inter.begin();

			Assert::AreEqual(true, p.first == 2 && p.second == 2);
		}

		TEST_METHOD(TestMethod10) //相交
		{
			set<pair<double, double>, cmp> inter;
			Line l(0, 0, 1, 0, 'L');
			Circle c(1, 0, 1);

			solve.LCintersect(&inter, l, c);
			
			Assert::AreEqual(true, inter.size() == 2);
		}

		////////////////////////////////测试射线与圆交点///////////////////////////////////

		TEST_METHOD(TestMethod11) //相离
		{
			set<pair<double, double>, cmp> inter;
			Line r(2, 2, 4, 2, 'R');
			Circle c(1, 0, 1);

			solve.RCintersect(&inter, r, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod12) //相切无交点
		{
			set<pair<double, double>, cmp> inter;
			Line r(3, 2, 4, 2, 'R');
			Circle c(2, 0, 2);

			solve.RCintersect(&inter, r, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod13) //相交一个交点
		{
			set<pair<double, double>, cmp> inter;
			Line r(0.5, 0, 1, 0, 'R');
			Circle c(1, 0, 1);

			solve.RCintersect(&inter, r, c);

			Assert::AreEqual(true, inter.size() == 1);
		}

		////////////////////////////////测试线段与圆交点///////////////////////////////////

		TEST_METHOD(TestMethod14) //相离
		{
			set<pair<double, double>, cmp> inter;
			Line s(2, 2, 4, 2, 'S');
			Circle c(1, 0, 1);

			solve.SCintersect(&inter, s, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod15) //相切无交点
		{
			set<pair<double, double>, cmp> inter;
			Line s(3, 2, 4, 2, 'S');
			Circle c(2, 0, 2);

			solve.RCintersect(&inter, s, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod16) //相交一个交点
		{
			set<pair<double, double>, cmp> inter;
			Line s(0.5, 0, 3, 0, 'S');
			Circle c(1, 0, 1);

			solve.SCintersect(&inter, s, c);

			Assert::AreEqual(true, inter.size() == 1);
		}

		TEST_METHOD(TestMethod17) //相交无交点
		{
			set<pair<double, double>, cmp> inter;
			Line s(0.5, 0, 1, 0, 'S');
			Circle c(1, 0, 1);

			solve.SCintersect(&inter, s, c);

			Assert::AreEqual(true, inter.size() == 0);
		}

		////////////////////////////////测试圆和圆求交点///////////////////////////////////

		TEST_METHOD(TestMethod18) //外离
		{
			set<pair<double, double>, cmp> inter;
			Circle c1(0, 0, 1);
			Circle c2(5, 4, 2);

			solve.CCintersect(&inter, c1, c2);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod19) //内切
		{
			set<pair<double, double>, cmp> inter;
			Circle c1(0, 0, 2);
			Circle c2(1, 0, 1);

			solve.CCintersect(&inter, c1, c2);

			Assert::AreEqual(true, inter.size() == 1);
		}

		TEST_METHOD(TestMethod20) //外切
		{
			set<pair<double, double>, cmp> inter;
			Circle c1(0, 0, 2);
			Circle c2(3, 0, 1);

			solve.CCintersect(&inter, c1, c2);

			Assert::AreEqual(true, inter.size() == 1);
		}

		TEST_METHOD(TestMethod21) //内含
		{
			set<pair<double, double>, cmp> inter;
			Circle c1(0, 0, 1);
			Circle c2(5, 4, 20);

			solve.CCintersect(&inter, c1, c2);

			Assert::AreEqual(true, inter.size() == 0);
		}

		TEST_METHOD(TestMethod22) //相交
		{
			set<pair<double, double>, cmp> inter;
			Circle c1(0, 0, 5);
			Circle c2(6, 0, 5);

			solve.CCintersect(&inter, c1, c2);

			Assert::AreEqual(true, inter.size() == 2);
		}
	};
}
