#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

const int MAX_N = 500000;
const int MAX_D = 300;
const int MAX_PRICE = 1000000;
const size_t BUFFER_SIZE = 5000000;

typedef std::vector<int> intvec_t;
typedef std::map<int, int> intmap_t;

static unsigned char price_array[MAX_PRICE];

int find_pair(const intvec_t& N, const int budget)
{
	int r = 0;

	const intvec_t::const_iterator start
		= std::upper_bound(N.begin(), N.end(), budget, std::greater<int>());

	for(intvec_t::const_iterator n1 = start;
		n1 != N.end() && budget / 2 <= *n1;
		++n1)
	{
		if((n1 + 1) != N.end() && *(n1 + 1) == *n1) continue;
		const int remaining = budget - *n1;
		if( price_array[remaining] > 0 )
		{
			if( remaining != *n1 ) return budget;
			if( price_array[remaining] > 1) return budget;
		}
	}

	intvec_t::const_iterator n2 = N.end();
	for(intvec_t::const_iterator n1 = start;
		n1 != N.end() && r < (*n1 * 2);
		++n1)
	{
		if((n1 + 1) != N.end() && *(n1 + 1) == *n1) continue;
		const int remaining = budget - *n1;

		intvec_t::const_iterator n2c = std::lower_bound(n1, n2, remaining, std::greater<int>());
		if( n2c == N.end() ) continue;
		if( n1 == n2c ) ++n2c;
		if( n2c == N.end() ) continue;
		n2 = n2c;
//		std::cout << "remaining: " << remaining << ", n2: " << *n2 << std::endl;
		r = std::max(r, *n1 + *n2);
	}
	return r;
}

int main()
{
	static char buf[BUFFER_SIZE];

	read(0, buf, BUFFER_SIZE);

	char *iptr = buf;
	const int n = std::strtol(iptr, &iptr, 10);
	const int d = std::strtol(iptr, &iptr, 10);

	intvec_t N;
	N.reserve(n);
	for(int i = 0; i < n; ++i)
	{
		const int m = std::strtol(iptr, &iptr, 10);
		N.push_back(m);
		++price_array[m];
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

	static int answers1[MAX_PRICE];

	static char outbuf[BUFFER_SIZE];
	char *outp = outbuf;
	for(int i = 0; i < d; ++i)
	{
		const int d = std::strtol(iptr, &iptr, 10);
		int v;
		if( answers1[d] )
		{
			v = answers1[d] - 1;
		} else {
			v = find_pair(N, d);
			answers1[d] = v + 1;
		}

		outp += std::snprintf(outp, BUFFER_SIZE - (outp - outbuf), "%d\n", v);
	}
	write(1, outbuf, outp - outbuf);
	return 0;
}
