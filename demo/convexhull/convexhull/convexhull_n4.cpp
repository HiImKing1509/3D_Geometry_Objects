/*
Nguyen Duc Anh Phuc _ Jacke
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll>pll;
typedef pair<ld, ld>pld;
ifstream fi("bunny_in.txt");
ofstream fo("bunny_out.txt");

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
struct face
{
	ll a, b, c;
};
void bruteforce(vector<pt3> points)
{
	ll n = (ll)points.size();
	vector<face>res;
	for (ll i = 0; i <= n - 1; i++)
	{
		for (ll j = 0; j <= n - 1; j++)
		{
			if (i == j)continue;
			for (ll k = 0; k <= n - 1; k++)
			{
				if (i == j || j == k || i == k)continue;
				// a=i, b=j, c=k
				pt3 tmp = (points[j] - points[i]).cross(points[k] - points[i]);
				ll neg = 0;
				ll pos = 0;
				for (ll z = 0; z <= n - 1; z++)
					if (z != i && z != j && z != k)
					{
						if ((points[z] - points[i]).dot(tmp) < 0)neg++;
						else pos++;
					}
				if (pos == 0 || neg == 0)
					res.push_back({ i,j,k });
			}
		}
	}
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
	bruteforce(read());
	cout << "ok";
	return 0;
}