/**
 * Problem: Count the number of prime numbers less than non-negative number, n
 * Solve: use Sieve of Eratosthenes
 * Tips: see below
 */
int countPrimes(int n) {
	vector<bool> is_prime(n, true);
	if (n <= 2) return 0;

	int i,count = 1;
	int end = sqrt(n);
	// add 2
	for (i = 3; i <= end; i += 2) {
		if (!is_prime[i]) continue;

		++count;
		// i*i is odd and i is odd, then i*i + x*i is even when x is odd
		for (int j = i*i, k = i<<1; j < n; j += k) {
			is_prime[j] = false;
		}
	}

	// add 2
	for (; i < n; i += 2) {
		if (is_prime[i]) ++count;
	}

	return count;
}

class Solution {
    public:
        int countPrimes(int n) {
            vector<bool> prime(n, true);

            int cnt = 0, root = sqrt(n);
            for (int i = 2; i <= root; ++i) {
                if (prime[i]) {
                    for (int j = i*i; j < n; j += i) {
                        prime[j] = false;

                    }
                    ++cnt;
                }
            }

            for (int i = root + 1; i < n; ++i)
                if (prime[i])
                    ++cnt;

            return cnt;

        }

};
