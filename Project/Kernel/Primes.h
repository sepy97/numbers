#pragma once
#include <vector>
#include <stdio.h>
using namespace std;

class Primes
{
public:
	Primes(unsigned long _MAX)
	{
        MAX = _MAX;
		vector<bool> s(MAX);
		s[0] = true;
		s[1] = true;
		s[2] = false;
		for (long f = 2; f < (long)MAX; f++)
		{
			if (!s[f]) 
			{
				p.push_back(f);
				for (size_t q = f+f; q < MAX; q += f)
				{
					s[q] = true;
				}
			}
		}
	}
	~Primes() {}
	int operator[](int num) const { return (int)p[num]; }
	size_t size() const { return p.size(); }
    size_t getMax() const { return MAX; }

	static vector<size_t> merge(vector<size_t> const &s1, vector<size_t> const &s2)
	{
		vector<size_t> ret;
		size_t p1 = 0;
		size_t p2 = 0;
		while (p1 < s1.size() && p2 < s2.size())
		{
			if (s1[p1] < s2[p2]) 
			{
				ret.push_back(s1[p1]);
				p1++;
			}
			else if (s2[p2] < s1[p1])
			{
				ret.push_back(s2[p2]);
				p2++;
			}
			else 
			{
				p1++;
				p2++;
			}
		}
		while (p2 < s2.size())
		{
			ret.push_back(s2[p2]);
			p2++;
		}
		while (p1 < s1.size())
		{
			ret.push_back(s1[p1]);
			p1++;
		}
		return ret;
	}

	vector<size_t> factor2(size_t n)
	{
		vector<size_t> ret;
		if (n < 2) return ret;

		for (size_t i = 0; i < p.size(); i++)
		{
			bool cnt = false;
			while (n % p[i] == 0)
			{
				cnt = !cnt;
				n /= p[i];
			}
			if (cnt)
			{
				ret.push_back(p[i]);
			}
		}
		return ret;
	}
#if 0
	void trio(FILE *fp, int a, int b, int c)
	{
		int n1 = a + b + c;
		int n2 = a + b - c; 
		if (n2 <= 0) return;
		int n3 = a + c - b;
		if (n3 <= 0) return;
		int n4 = b + c - a;
		if (n4 <= 0) return;
		vector<size_t> s1 = merge(vs[n1], vs[n2]);
		vector<size_t> s2 = merge(vs[n3], vs[n4]);
		vector<size_t> s  = merge(s1, s2);
		if (s.size() > 0 && s[s.size()-1] > 101) return;
		fprintf(fp, "%d,%d,%d=", a, b, c);
		for (vector<size_t>::const_iterator ci = s.begin(); ci != s.end(); ci++)
		{
			fprintf(fp, "%d,", *ci);
		}
		fprintf(fp,"\n");
	}
#endif

private:
	vector<long> p;
    size_t MAX;
//	vector< vector<size_t> > vs;
};
 