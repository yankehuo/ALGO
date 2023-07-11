#include <cstring>
#include <algorithm>
#include <iostream>
#pragma GCC push_options
#pragma optimize("O0")

static const int N = 8;
int primes[N];
int v[N];
int idx = 0;

void get_prime(int n) {
	memset(v, 0, sizeof(v));
    idx = 0;
	for (int i = 2; i <= n; ++i) {
		if (!v[i]) {
			primes[idx++] = i;
		}
		for (int j = 0; primes[j] <= n / i; ++j) {
			v[primes[j] * i] = 1;
			if (i % primes[j] == 0) break;
		}
	}
}

int main()
{
    // 与N相同代码会出现问题，idx取地址错误 reason:数组越界
	get_prime(N);
	for (int i = 0; i < idx; ++i)
	{
		std::cout << primes[i] << std::endl;
	}
	return 0;
}

#pragma GCC pop_options