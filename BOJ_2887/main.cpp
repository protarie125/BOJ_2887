#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int N;
vll xs;
vll ys;
vll zs;
vector<pair<ll, pll>> dists;

vi root;
ll par(ll x) {
	if (root[x] == x) {
		return x;
	}

	return root[x] = par(root[x]);
}

void joint(ll a, ll b) {
	a = par(a);
	b = par(b);

	if (a < b) {
		root[b] = a;
	}
	else {
		root[a] = b;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N;
	xs.reserve(N);
	ys.reserve(N);
	zs.reserve(N);
	dists.reserve(3 * N);

	root = vi(N);
	for (auto i = 0; i < N; ++i) {
		root[i] = i;
	}

	for (auto i = 0; i < N; ++i) {
		ll x, y, z;
		cin >> x >> y >> z;
		xs.push_back({ x, i });
		ys.push_back({ y, i });
		zs.push_back({ z, i });
	}

	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	sort(zs.begin(), zs.end());

	for (auto i = 0; i < N - 1; ++i) {
		dists.push_back({ xs[i + 1].first - xs[i].first, { xs[i].second, xs[i + 1].second } });
		dists.push_back({ ys[i + 1].first - ys[i].first, { ys[i].second, ys[i + 1].second } });
		dists.push_back({ zs[i + 1].first - zs[i].first, { zs[i].second, zs[i + 1].second } });
	}

	sort(dists.begin(), dists.end());

	auto ans = ll{ 0 };
	for (const auto& [d, p] : dists) {
		const auto& [a, b] = p;

		if (par(a) != par(b)) {
			joint(a, b);
			ans += d;
		}
	}

	cout << ans;

	return 0;
}