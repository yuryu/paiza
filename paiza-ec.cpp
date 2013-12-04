#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

const int MAX_N = 500000;
const int MAX_D = 300;

std::vector<int> read_sorted(const int n)
{
	std::vector<int> result;

	result.reserve(n);
	for(int i = 0; i < n; ++i){
		int m;
		std::cin >> m;
		result.push_back(m);
		std::push_heap(result.begin(), result.end(), std::greater<int>());
	}
	std::sort_heap(result.begin(), result.end(), std::greater<int>());
	return result;
}

std::vector<int> read_list(const int n)
{
	std::vector<int> result;
	result.reserve(n);
	for(int i = 0; i < n; ++i)
	{
		int m;
		std::cin >> m;
		result.push_back(m);
	}
	return result;
}

int find_pair(const std::vector<int>& N, int budget)
{
	int r = 0;

	for(std::vector<int>::const_iterator n1
			= std::lower_bound(N.begin(), N.end(), budget, std::greater<int>());
		n1 != N.end();
		++n1)
	{
//		std::cout << "n1: " << *n1 << std::endl;
		if( (budget - r) <= (budget - (*n1 + N[0]) ) ) break;
		const int remaining = budget - *n1;
		std::vector<int>::const_iterator n2
			= std::lower_bound(N.begin(), N.end(), remaining, std::greater<int>());
		if( n2 == N.end() ) continue;
		if( n1 == n2 ) ++n2;
		if( n2 == N.end() ) continue;
//		std::cout << "remaining: " << remaining << ", n2: " << *n2 << std::endl;
		const int candidate = *n1 + *n2;
		if( (budget - r) > (budget - candidate) )
		{
			r = candidate;
		}
	}
	return r;
}

int main()
{
	std::vector<int> N, D;
	int n, d;
	std::cin >> n >> d;
	N = read_sorted(n);
	D = read_list(d);

/*
	std::cout << "N: ";
	for(int i: N) { std::cout << i << ", "; }
	std::cout << std::endl;
	std::cout << "D: ";
	for(int i: D) { std::cout << i << ", "; }
	std::cout << std::endl;
*/
	for(std::vector<int>::const_iterator d = D.begin(); d != D.end(); ++d)
	{
		std::cout << find_pair(N, *d) << '\n';
	}
	std::cout << std::flush;
	return 0;
}
