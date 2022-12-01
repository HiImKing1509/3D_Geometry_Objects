/*
Nguyen Duc Anh Phuc _ Jacke
*/
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>


using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll>pll;
typedef pair<ld, ld>pld;
ifstream fi("bunny_in.txt");
ofstream fo("bunny_out.txt");

const ld EPS = 1e-9;
// 3D point structure
struct pt3
{
	ld x, y, z;
	pt3(ld xx = 0, ld yy = 0, ld zz = 0)
	{
		x = xx, y = yy, z = zz;
	}
	pt3 operator-(const pt3& o)
	{
		return pt3(x - o.x, y - o.y, z - o.z);
	}
	pt3 cross(const pt3& o) {
		return pt3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
	}
	ld dot(const pt3& o)
	{
		return x * o.x + y * o.y + z * o.z;
	}
};
// face: indices and outward vector
struct face
{
	ll a, b, c;
	pt3 q;
};

vector<face>incremental_hull(vector<pt3> points)
{
	ll n = points.size();
	assert(n >= 3);
	vector<face> f;

	//Add new faces on outside edges
	vector<vector<bool>> del(n, vector<bool>(n, true));
	auto add_face = [&](int a, int b, int c) {
		f.push_back({ a, b, c, (points[b] - points[a]).cross(points[c] - points[a]) });
		del[a][b] = del[b][c] = del[c][a] = false;
	};

	// 2 faces with 2 orientation outward vectors
	add_face(0, 1, 2);
	add_face(0, 2, 1);
	for (ll i = 3; i <= n - 1; i++)
	{
		cout << i << "\n";
		vector<face> f2;
		for (face& F : f)
		{
			if ((points[i] - points[F.a]).dot(F.q) > EPS)
				// this face is visible to the new point, so del its edges as
				del[F.a][F.b] = del[F.b][F.c] = del[F.c][F.a] = true;
			else
				f2.push_back(F);
		}
		// Add a new face for each exposed edge.
		// Only check edges of alive faces for being exposed.
		f.clear();
		for (face& F : f2)
		{
			ll arr[3] = { F.a, F.b, F.c };
			for (ll j = 0; j <= 2; j++)
			{
				ll a = arr[j], b = arr[(j + 1) % 3];
				if (del[b][a])
					add_face(b, a, i);
			}
		}
		f.insert(f.end(), f2.begin(), f2.end());
	}
	return f;
}

vector<pt3> read()
{
	ll n;
	fi >> n;
	vector<pt3>arr;
	for (ll i = 0; i <= n - 1; i++)
	{
		ld x, y, z;
		fi >> x >> y >> z;
		arr.push_back({ x,y,z });
	}
	return arr;
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	vector<face>f = incremental_hull(read());
	for (auto ff : f)
		fo << ff.a << " " << ff.b << " " << ff.c << " ";
	return 0;
}