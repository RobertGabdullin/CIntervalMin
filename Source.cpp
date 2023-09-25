#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
using namespace std;


template <typename T>
struct Funct {
	bool operator()(T const& a, T const& b) {
		return a < b;
	}
};

template<typename T_, typename Cmp_ = Funct<T_> >
class CIntervalMin
{
public:

	CIntervalMin() {
		M = 0;
		sz = 0;
	}
	CIntervalMin(Cmp_ cmp) : Less(cmp) {
		M = 0;
		sz = 0;
	}
	CIntervalMin(typename vector<T_>::const_iterator left, typename vector <T_>::const_iterator right) {
		M = 0; sz = 0;
		for (auto i = left; i != right; i++)
			push_back(*i);
	}
	CIntervalMin(typename vector <T_>::const_iterator left, typename vector <T_>::const_iterator right, Cmp_ cmp) : Less(cmp) {
		M = 0; sz = 0;
		for (auto i = left; i != right; i++)
			push_back(*i);
	}

	void push_back(T_ cur) {
		val.push_back(cur);
		sz++;
		if (Max.empty()) Max.push_back(cur);
		else if (!Less(cur, Max.back())) Max.back() = cur;
		update(val.size() - 1, cur);
	}

	void pop_back() {
		val.pop_back();
		sz--;
	}

	T_ min(typename vector <T_>::const_iterator a, typename vector<T_>::const_iterator b) {
		if (b <= a) throw invalid_argument("");
		int fir = a - val.cbegin(), sec = (b - val.cbegin()) - 1;
		return GetMin(1, 0, M - 1, fir, sec);
	}

	typename vector <T_>::const_iterator begin() {
		return val.cbegin();
	}

	typename vector <T_>::const_iterator end() {
		return val.cend();
	}

	int size() {
		return sz;
	}

private:

	int MinInt(int a, int b) {
		if (a < b) return a;
		return b;
	}

	T_ Min(T_ a, T_ b) {
		if (Less(b, a)) return b;
		return a;
	}

	void increase() {
		if (M >= sz) return;
		if (t.empty()) M = 1;
		else M *= 2;
		t.clear();
		t.resize(2 * M, Max.back());

		for (int i = 0; i < sz; i++)
			t[i + M] = val[i];
		for (int i = M - 1; i; i--)
			t[i] = Min(t[i * 2], t[i * 2 + 1]);

	}

	void update(int pos, T_ x) {
		increase();
		pos += M;
		t[pos] = x;
		pos /= 2;
		while (pos > 0) {
			t[pos] = Min(t[pos * 2], t[pos * 2 + 1]);
			pos /= 2;
		}
	}

	T_ GetMin(int v, int tl, int tr, int l, int r) {
		if (l > r) return Max.back();
		if (tl == l && tr == r) return t[v];
		int tm = (tl + tr) / 2;
		T_ temp1 = GetMin(v * 2, tl, tm, l, MinInt(r, tm));
		T_ temp2 = GetMin(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
		return Min(temp1, temp2);
	}

	vector <T_> val, t, Max;
	int sz, M;
	Cmp_ Less;
};


#ifndef __PROGTEST__
//-------------------------------------------------------------------------------------------------
class CStrComparator
{
public:
	CStrComparator(bool byLength = true)
		: m_ByLength(byLength)
	{
	}
	bool       operator () (const string& a, const string& b) const
	{
		return m_ByLength ? a.length() < b.length() : a < b;
	}
private:
	bool       m_ByLength;
};
//-------------------------------------------------------------------------------------------------
bool strCaseCmpFn(const string& a, const string& b)
{
	return strcasecmp(a.c_str(), b.c_str()) < 0;
}
//-------------------------------------------------------------------------------------------------

int main(void)
{
	CIntervalMin <int> a1;
	for (auto x : initializer_list<int>{ 5, 15, 79, 62, -3, 0, 92, 16, 2, -4 })
		a1.push_back(x);

	assert(a1.size() == 10);

	ostringstream oss;
	for (auto x : a1)
		oss << x << ' ';

	assert(oss.str() == "5 15 79 62 -3 0 92 16 2 -4 ");
	assert(a1.min(a1.begin(), a1.end()) == -4);
	assert(a1.min(a1.begin() + 2, a1.begin() + 3) == 79);
	assert(a1.min(a1.begin() + 2, a1.begin() + 9) == -3);

	try
	{
		a1.min(a1.begin(), a1.begin());
		assert("Missing an exception" == nullptr);
	}
	catch (const invalid_argument& e)
	{
	}
	catch (...)
	{
		assert("Invalid exception" == nullptr);
	}

	a1.pop_back();
	assert(a1.size() == 9);
	a1.push_back(42);

	assert(a1.min(a1.begin(), a1.end()) == -3);

	vector<string> words{ "auto", "if", "void", "NULL" };
	CIntervalMin <string> a2(words.begin(), words.end());
	assert(a2.min(a2.begin(), a2.end()) == "NULL");

	CIntervalMin <string, bool(*)(const string&, const string&)> a3(words.begin(), words.end(), strCaseCmpFn);
	assert(a3.min(a3.begin(), a3.end()) == "auto");

	CIntervalMin <string, CStrComparator> a4(words.begin(), words.end());
	assert(a4.min(a4.begin(), a4.end()) == "if");

	CIntervalMin <string, CStrComparator> a5(words.begin(), words.end(), CStrComparator(false));
	assert(a5.min(a5.begin(), a5.end()) == "NULL");

	CIntervalMin <string, function<bool(const string&, const string&)> > a6([](const string& a, const string& b)
		{
			return a > b;
		});
	for (const auto& w : words)
		a6.push_back(w);
	assert(a6.min(a6.begin(), a6.end()) == "void");
	return 0;
}
#endif /* __PROGTEST__ */

