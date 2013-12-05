#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <ext/hash_map>
#include <cstdlib>
#include <cstdio>

const int MAX_N = 500000;
const int MAX_D = 300;
const size_t BUFFER_SIZE = 5000000;

typedef std::vector<int> intvec_t;
typedef std::map<int, int> intmap_t;
typedef __gnu_cxx::hash_map<int, int> inthash_t;

inthash_t price_hash;

int find_pair(const intvec_t& N, const int budget)
{
	int r = 0;

	const intvec_t::const_iterator start
		= std::upper_bound(N.begin(), N.end(), budget, std::greater<int>());

	for(intvec_t::const_iterator n1 = start;
		n1 != N.end() && budget / 2 <= *n1;
		++n1)
	{
		const int remaining = budget - *n1;
		inthash_t::const_iterator h = price_hash.find(remaining);
		if(h != price_hash.end()){
			if(h->first != *n1 || h->second > 1) return budget;
		}
	}

	intvec_t::const_iterator n2 = N.end();
	for(intvec_t::const_iterator n1 = start;
		n1 != N.end();
		++n1)
	{
		if( r >= (*n1 * 2) ) break;
		const int remaining = budget - *n1;

		intvec_t::const_iterator n2c = std::lower_bound(n1, n2, remaining, std::greater<int>());
		if( n2c == N.end() ) continue;
		if( n1 == n2c ) ++n2c;
		if( n2c == N.end() ) continue;
		n2 = n2c;
//		std::cout << "remaining: " << remaining << ", n2: " << *n2 << std::endl;
		const int candidate = *n1 + *n2;
		if( (budget - r) > (budget - candidate) )
		{
			r = candidate;
			if( r == budget ) break;
		}
	}
	return r;
}

int main()
{
	int n, d;
	std::cin >> n >> d;
	char *buf = new char[BUFFER_SIZE];

	std::ios_base::sync_with_stdio(false);
	std::cin.read(buf, BUFFER_SIZE);
	intvec_t N;
	N.reserve(n);
	for(int i = 0; i < n; ++i)
	{
		const int m = std::strtol(buf, &buf, 10);
		N.push_back(m);
		inthash_t::iterator h = price_hash.find(m);
		if(h == price_hash.end()) {
			price_hash.insert(std::pair<int, int>(m, 1));
		} else {
			h->second = 2;
		}
	}

	std::sort(N.begin(), N.end(), std::greater<int>());
	
/*
	std::cout << "N: ";
	for(int i: N) { std::cout << i << ", "; }
	std::cout << std::endl;
	std::cout << "D: ";
	for(int i: D) { std::cout << i << ", "; }
	std::cout << std::endl;
*/

	inthash_t table;

	char *outbuf = new char[BUFFER_SIZE];
	char *dptr = buf;
	char *outp = outbuf;
	for(int i = 0; i < d; ++i)
	{
		const int d = std::strtol(dptr, &dptr, 10);
		inthash_t::const_iterator p = table.find(d);
		int v;
		if(p == table.end()) {
			v = find_pair(N, d);
			table.insert(std::pair<int, int>(d, v));
		} else {
			v = p->second;
		}

		outp += std::snprintf(outp, BUFFER_SIZE - (outp - outbuf), "%d\n", v);
	}
	*outp = 0;
	std::cout.write(outbuf, outp - outbuf);
	return 0;
}
