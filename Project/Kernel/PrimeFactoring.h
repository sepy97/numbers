#pragma once
#include "LargeNumber.h"
#include "Primes.h"
#include <algorithm>

class PrimeFactoring
{
public:
	static bool MillerRabin(LargeNumber const &m)
	{
		if (m.isEven()) return false;
		int r = m.getNumberOfSignificantDigits() * 3;
		LargeNumber m1(m);
		m1 -= LargeNumber::one;
		int s = 0;
		LargeNumber t(m1);
		while (t.isEven()) 
		{
			s++;
			t /= LargeNumber::two;
		}
		for (int i = 0; i < r; i++)
		{
			LargeNumber a = LargeNumber::random(m1);
		}
        return false;
	}
#if 0
	Ввод: m > 2, нечётное натуральное число, которое необходимо проверить на простоту;
    r — количество раундов.
Вывод: составное, означает, что m является составным числом;
    вероятно простое, означает, что m с высокой вероятностью является простым числом.
Представить m − 1 в виде 2s·t, где t нечётно, можно сделать последовательным делением m - 1 на 2.
цикл А: повторить r раз:
Выбрать случайное целое число a в отрезке [2, m − 2]
x ← at mod m, вычисляется с помощью алгоритма возведения в степень по модулю (англ.)
если x = 1 или x = m − 1, то перейти на следующую итерацию цикла А
цикл B: повторить s − 1 раз
    x ← x2 mod m
    если x = 1, то вернуть составное
    если x = m − 1, то перейти на следующую итерацию цикла A
вернуть составное
вернуть вероятно простое
#endif

    static LargeNumber RhoPollard(LargeNumber const& N)
    { 
        LargeNumber N2 = N;
        N2 -= LargeNumber::two;
        LargeNumber x = LargeNumber::random(N2);
        LargeNumber y = 1; 
        LargeNumber i = LargeNumber::zero; 
        LargeNumber stage = 2;
        LargeNumber xy;
        LargeNumber xyGCD;
        while (xy = x, xy -= y, xy.abs(), xyGCD = LargeNumber::GCD(N, xy), xyGCD == 1)
        {
            if (i == stage )
            {
                y = x;
                stage += stage; 
            }
            x *= x;
            x += LargeNumber::one;
            x %= N;
            i += 1;
        }
        return xy = x, xy -= y, xy.abs(), LargeNumber::GCD(N, xy);
    }

    static vector<LargeNumber> factor2(LargeNumber const &l, Primes const &pr)
    {
        vector<LargeNumber> ret;
        bool done = false;
        LargeNumber c = l;
        while (!done)
        {
            LargeNumber d, q;
            for(size_t i = 0; i < pr.size(); )
            {
                int j = (int) i;
                LargeNumber lpr(pr[j]);
                LargeNumber::divmod(c, lpr, d, q);
                if (q.isZero())
                {
//                    cout << lpr << endl;
                    ret.push_back(lpr);
                    c = d;
                    continue;
                }
                else
                {
                    if (lpr > d)
                    {
                        done = true;
                        break;
                    }
                    i++;
                }
            }
            if (!(c == LargeNumber::one))
            {
                ret.push_back(c);
            }
            done = true;
        }
        return ret;
    }

    static vector<LargeNumber> factor(LargeNumber const &l, Primes const &pr)
    {
//		printf("factor(%s)\n", l.toString().c_str());
        vector<LargeNumber> ret2;
		vector<LargeNumber> ret;
        LargeNumber c = l;
        for (;;)
        {
            if (c < 10000)
            {
                vector<LargeNumber> f2 = factor2(c, pr);
				for (size_t i = 0; i < f2.size(); i++)
				{
					ret.push_back(f2[i]);
				}
// 				sort(ret.begin(), ret.end());
// 				printf("factor(%s)= ", l.toString().c_str());
// 				for (size_t i = 0; i < ret.size(); i++)
// 				{
// 					printf("[%s] ", ret[i].toString().c_str());
// 				}
// 				printf("\n");
//                 return ret; // break;
				break;
            }
            LargeNumber d = RhoPollard(c);
//			printf("Rho(%s)=%s\n", c.toString().c_str(), d.toString().c_str());
            if (c > d)
            {
                vector<LargeNumber> f2 = factor(d, pr);
                for (size_t i = 0; i < f2.size(); i++)
                {
                    ret2.push_back(f2[i]);
                }
            }
            else
            {
                ret.push_back(d);
            }
            c /= d;
//            cout << d << "*" << c << endl;
            if (c.isOne())
                break;
        }
        for (size_t i = 0; i < ret2.size(); i++)
        {
			vector<LargeNumber> f2 = factor(ret2[i], pr);
			for (size_t i = 0; i < f2.size(); i++)
			{
				ret.push_back(f2[i]);
			}
        }
		sort(ret.begin(), ret.end());
//		printf("factor(%s)= ", l.toString().c_str());
		for (size_t i = 0; i < ret.size(); i++)
		{
//			printf("[%s] ", ret[i].toString().c_str());
		}
//		printf("\n");
        return ret;
    }
};
