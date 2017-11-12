#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace std;

std::vector<int> last_item;
std::vector<int> last_item_idx;
std::vector<int> prev_idx;


int find_lis(int* arr, int n) {
	last_item.resize(n + 1, std::numeric_limits<int>::max());
	last_item[0] = std::numeric_limits<int>::min();

	prev_idx.resize(n + 1, -1);
	last_item_idx.resize(n + 1, -1);

	for (int i = 0; i < n; i++) {
		auto it = std::lower_bound(last_item.begin(), last_item.end(), arr[i]);
		assert(it != last_item.cend());

		// finding last of equals
		if (*it != std::numeric_limits<int>::max()) {
			it = std::upper_bound(it, last_item.end(), *it);
			it--;
		}

		int j = std::distance(last_item.begin(), it);

		//if (arr[i] < last_item[j]) {
			last_item[j] = arr[i];
			last_item_idx[j] = i;
			prev_idx[i] = last_item_idx[j - 1];
		/*}
		else { // arr[i] == last_item[j], for longest NON-DECREASING subsequence
			assert(arr[i] == last_item[j]);
			last_item[j + 1] = arr[i];
			last_item_idx[j + 1] = i;
			prev_idx[i] = last_item_idx[j];
		}*/


		//*it = arr[i];
	}

	/*
	for (int x : last_item)
		cout << x << " ";
	cout << endl;
	*/

	auto res = std::lower_bound(last_item.begin(), last_item.end(), std::numeric_limits<int>::max());
	res--;
	return std::distance(last_item.begin(), res);
}


const int maxn = 100000;

int a[maxn];
int n, k, b, m;

int main() {
	/*	cin >> n >> a[0] >> k >> b >> m;

		for (int i = 1; i < n; i++)
			a[i] = (k * a[i - 1] + b) % m;*/

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int ll = find_lis(a, n);

	vector<int> res;

	int cur_idx = last_item_idx[ll];
	while (cur_idx != -1) {
		res.push_back(a[cur_idx]);
		cur_idx = prev_idx[cur_idx];
	}


	for (auto it = res.crbegin(); it != res.crend(); it++)
		cout << *it << " ";



	return 0;
}