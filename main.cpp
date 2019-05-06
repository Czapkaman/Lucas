#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

unsigned int fast_mod(unsigned long int a, unsigned long long int b, unsigned int c, unsigned int n = 0)
{
	if (n > 0)
	{
		if ((static_cast<unsigned long int>(1) << n - 1) > b) return 1;
		a = (a * a) % c;
	}
	n++;
	if ((b >> n - 1) & 1) return (a * fast_mod(a, b, c, n)) % c;
	return fast_mod(a, b, c, n);
}

std::vector<unsigned int> operator+(std::vector<unsigned int> lhs, std::vector<unsigned int> rhs)
{
	lhs.insert(lhs.end(), rhs.begin(), rhs.end());
	return lhs;
}

std::vector<unsigned int> Fermat_Part2(unsigned int a)
{
	int y = 0;
	unsigned int x = static_cast<unsigned int>(sqrt(a));
	if (x == sqrt(a))
	{
		return std::vector<unsigned int>{ x };
	}
	x++;
	while (x < (a + 1) / 2)
	{
		y = x * x - a;
		if (y > 0 && (static_cast<unsigned int>(sqrt(y)) == sqrt(y)))
		{
			y = static_cast<unsigned int>(sqrt(y));
			return Fermat_Part2(x + y) + Fermat_Part2(x - y);
		}
		x++;
	}
	return std::vector<unsigned int>{ a };
}

std::vector<unsigned int> Fermat(unsigned int a)
{
	std::vector<unsigned int> result;
	result.reserve(128);
	bool check = 1;
	while (!((a >> 0) & 1)) 
	{
		for (auto test : result)
		{
			if (test == 2)
				check = 0;
		}
		if (check)
			result.emplace_back(2);
		a = a >> 1;
	}
	result = result + Fermat_Part2(a);
	std::sort(result.begin(), result.end());
	result.erase(std::unique(result.begin(), result.end()), result.end());
	return result;
}

int main()
{
	unsigned int n, q, result;
	bool check = 1;
	std::cout << "Gimme a: ";
	std::cin >> n;
	std::cout << "Gimme b: ";
	std::cin >> q;
	std::cout << "Gimme c: ";
	std::cin >> result;
	std::cout << fast_mod(q, n, result) << std::endl;

	std::cout << "Gimme a: ";
	std::cin >> n;
	for (auto i : Fermat(n))
	{
		std::cout << i << std::endl;
	}

	std::cout << "Gimme n: ";
	std::cin >> n;
	std::cout << "Gimme q: ";
	std::cin >> q;
	std::cout << fast_mod(q, n-1, n) << std::endl;
	for (auto i : Fermat(n - 1))
	{
		result = fast_mod(q, (n - 1) / i, n);
		std::cout << result << std::endl;
		if (result == 1) check = 0;
	}
	if (check)
		std::cout << n << " jest liczba pierwsza" << std::endl;
	else
		std::cout << "Test nie rozstrzyga" << std::endl;
	return 0; 
}
