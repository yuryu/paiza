#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

const int MAX_N = 500000;
const int MAX_D = 300;

typedef std::vector<int> intvec_t;

intvec_t read_list(const int n)
{
	intvec_t result;
	
	result.reserve(n);
	for(int i = 0; i < n; ++i)
	{
		int m;
		std::cin >> m;
		result.push_back(m);
	}
	return result;
}

int find_pair(const intvec_t& N, int budget)
{
	int r = 0;

	intvec_t::const_iterator n2 = N.end();
	for(intvec_t::const_iterator n1
			= std::upper_bound(N.begin(), N.end(), budget, std::greater<int>());
		n1 != N.end();
		++n1)
	{
//		std::cout << "n1: " << *n1 << std::endl;
		if( (budget - r) <= (budget - *n1 * 2) ) break;
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
	intvec_t N = read_list(n);
	intvec_t D = read_list(d);
	std::sort(N.begin(), N.end(), std::greater<int>());
	
/*
	std::cout << "N: ";
	for(int i: N) { std::cout << i << ", "; }
	std::cout << std::endl;
	std::cout << "D: ";
	for(int i: D) { std::cout << i << ", "; }
	std::cout << std::endl;
*/
	for(intvec_t::const_iterator d = D.begin(); d != D.end(); ++d)
	{
		std::cout << find_pair(N, *d) << '\n';
	}
	std::cout << std::flush;
	return 0;
}
