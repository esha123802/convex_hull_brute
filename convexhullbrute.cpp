#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
#include <fstream>
typedef long long ll;

using namespace std;

const int maxn = 10005;

typedef struct Point
{
    int x;
    int y;
} point;

point p[maxn];
set<pair<int, int>> convex_hull;
int n;

int check_collinear(point p1, point p2, point p3) // checks whether the points come in the same side of the line
{
    int flag = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
    if (flag > 0)
        return 1; // on left of line
    else if (flag == 0)
        return 2; // on the line
    else
        return 0; // on right of the line
}

void convex_hull_brute(ll n)
{
    for (ll i = 0; i < n; i++)
    {
        int check_side = 0;

        for (int j = i + 1; j < n; j++)
        {
            int flag = -1;

            for (int k = 0; k < n; k++)
            {
                if (k == i || k == j)
                    continue;

                if (flag == -1)
                    flag = check_collinear(p[i], p[j], p[k]);
                else
                {
                    int temp = check_collinear(p[i], p[j], p[k]); // for the first coordinate
                    if (flag == temp || temp == 2)
                        check_side = 1; // if three points are collinear or on the same side
                    else                // if not on the same side, break
                    {
                        check_side = 0;
                        break;
                    }
                }
            }

            if (check_side)
            {
                convex_hull.insert(make_pair(p[i].x, p[i].y));
                convex_hull.insert(make_pair(p[j].x, p[j].y));
            }
        }
    }
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("sample.txt");
    fout.open("output.txt");

    ll i = 0;
    while (!fin.eof())
    {
        fin >> p[i].x;
        fin >> p[i].y;
        i++;
    }

    fin.close();

    auto start = high_resolution_clock::now();
    convex_hull_brute(i);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "\nTime taken by function : " << (duration.count() * 1e-9) << " seconds" << endl;

    set<pair<int, int>>::iterator it = convex_hull.begin();

    fout << "The points are : \n";
    while (it != convex_hull.end())
    {
        fout << "(" << it->first << ", " << it->second << ")" << endl;
        it++;
    }

    fout.close();
    convex_hull.clear();

    return 0;
}