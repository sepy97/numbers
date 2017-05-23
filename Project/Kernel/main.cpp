//
//  main.cpp
//  numbers
//
//  Created by Семен Пьянков on 10.06.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#include <iostream>
#include "SmallNumber.h"
#include "LargeNumber.h"
#include "RationalNumber.h"
#include "Primes.h"
#include <time.h>
#include "Error.h"
#include "NumberException.h"
#include "Tree.h"
#include "Test.h"
#include "VarTable.h"
#include "GrammarTree.h"
#include "LexicalScaner.h"
#include "PrimeFactoring.h"
#include "Primes.h"
#include "Executor.h"
#include "Random.h"

using namespace std;

//static const int MAXPRIME = 32000;

#include <set>

void test_var()
{
    VarTable vt;
    {
        Variable v1; v1.name = "x"; v1.values.push_back("123");
        Variable v2; v2.name = "y"; v2.values.push_back("7654");
        Variable v3; v3.name = "z"; v3.values.push_back("456");
        vt.add(v1);
        vt.add(v2);
        vt.add(v3);
    }
    Variable abc, none;
    //int code = vt.find("x", abc);
    //code = vt.find("none", none);
}

string readString()
{
    string ret;
    int c = 0;
    c = getchar();
    while (c != EOF && c != 0 && c != '\n' && c != '\r')
    {
        ret.push_back((char)c);
        c = getchar();
    }
    return ret;
}

#if 0
int main(int /*argc*/, char ** /*argv*/)
{
     Test t;
     t.check();
	 clock_t start, end;
#if 1
	 {
		 Executor executor;
 		 string s("(x^2-y^2) / (x-y)");
		 string outp = executor.exec(s);
		 printf("%s\n", outp.c_str());
		 exit(0);
	 }
#endif
#if 0
	 try
	 {
		LargeNumber pt(2);
		LargeNumber r(5);
		for (int i = 0; i < 3000; i++)
		{
			  pt *= 10;
			  r *= 5;
		}
		start = clock();
		for (int i = 0; i < 10000; i++)
		{
			LargeNumber q(pt);
			q /= r;
			if (i % 100 == 0)
			{
				printf("."); fflush(stdout);
			}
		}
		end = clock();
		printf("Total %d ticks\n", end - start);
	 } catch (const char *s)
	 {
		 printf("Excaption: %s\n", s);
	 }
	exit(0);
#endif
#if 0
	 //RationalNumber::setPrecision(100);
     GrammarTree gp("(16x^4+8x^3-116x^2+122x-30)");
	 Polynom p(gp.getPolynom());
	 start = clock();
	 deque<Polynom> roots = p.factor();
	 end = clock();
	 for (size_t i = 0; i < roots.size(); i++)
     {
         printf("%s", roots[i].toString().c_str());
		 if (i != roots.size() - 1)
		 {
			 printf ("*");
		 }
     }
	 printf("\nTotal %d ticks\n", end - start);
	 exit(0);
#endif
	Executor executor;
	for (;;)
	{
		char inp[1512];
		// RationalNumber::setPrecision(100);
		printf("> ");
		fgets(inp, 1512, stdin);
		//strcpy(inp, "factor x^2+1");
		for (size_t i = 0; i < sizeof inp; i++)
		{
			if (inp[i] == '\n')
			{
				inp[i] = 0;
			}
		}
		if (inp[0] == 0) break;
		clock_t start = clock();
		string outp = executor.exec(inp);
		clock_t end = clock();
		printf("%s\n", outp.c_str());
		printf("Total %u ticks\n", (end-start));
		//break;
	}
#if 0
	try 
    {
        VarTable vt;
        Variable x("x");
        Tree t0(x);
        Tree t1(RationalNumber("2"));
        Tree t2(O_SUB, t0, t1);
        Tree t3(O_MUL, t2, t2);
        Tree t4(RationalNumber("-4"));
        Tree t5(O_ADD, t3, t4);
        Tree t6(O_DIV, t5, t0);
        Tree t7(O_MOD, t6, t0);
        Tree t8(O_POWER, t6, t4);
        Polynom p(t8);
        string pts = p.toString();
        printf("%s %s\n", pts.c_str(), "");
	} catch (std::exception const &e)
	{
		cout << "exception: " << e.what() << endl;
	} catch (const char *s)
	{
		cout << "exception: " << s << endl;
	} catch (NumberException const &e)
    {
        cout << "NumberException: " << Error::explainCode(e.getCode()) << "(" << e.getMessage() << ") in " << e.getSource() << endl;
    }
#endif
}
#endif


#define _USE_MATH_DEFINES 1
#include <math.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include "Polynom.h"
using namespace std;

static Executor exec;
int
main(int /*argc*/, char ** /* argv */)
{
//	Test t;
//	t.check();
	try 
	{
		Executor executor;
		for (;;)
		{
			char inp[1512];
			// RationalNumber::setPrecision(100);
			printf("> ");
			fgets(inp, 1512, stdin);
			//strcpy(inp, "factor x^2+1");
			for (size_t i = 0; i < sizeof inp; i++)
			{
				if (inp[i] == '\n')
				{
					inp[i] = 0;
				}
			}
			if (inp[0] == 0) break;
			clock_t start = clock();
// 			GrammarTree<DoubleNumber> gt(inp);
// 			Tree<DoubleNumber> tr = gt.getTree();
// 			for (double x = -10; x <= 10; x += 0.5) {
// 				DoubleNumber dn(x);
// 				DoubleNumber val = tr.evaluate(dn);
// 				printf("%f->%f\n", x, val.toDouble());
// 			}
			string outp = executor.execAll(inp);
			clock_t end = clock();
			// printf("%s\n", outp.c_str());
 			//string outp = tr.debugPrint(inp, 0);
			printf("------%s\n", outp.c_str());
			printf("Total %u ticks\n", (end-start));
			//break;
		}
	}
	catch (std::exception const &e)
	{
		cout << "exception: " << e.what() << endl;
	} 
	catch (const char *s)
	{
		cout << "exception: " << s << endl;
	} 
	catch (NumberException const &e)
	{
		cout << "NumberException: " << Error::explainCode(e.getCode()) << "(" << e.getMessage() << ") in " << e.getSource() << endl;
	}
}



