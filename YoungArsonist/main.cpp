#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <set>
#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    cin.tie(0);
    freopen("f.in", "r", stdin);
    freopen("f.out", "w", stdout);
    int n, p = 3, k1, k2, k3, s = 0;
    cin >> n;

    vector <pair <long double, pair <int, int>>> sp;
    vector <pair <int, int>> st;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        long double q;
        cin >> x1 >> y1 >> x2 >> y2 >> q;
        x1 *= 2;
        x2 *= 2;
        y1 *= 2;
        y2 *= 2;
        int xt = (x1 + x2) / 2;
        int yt = (y1 + y2) / 2;
        if (st.empty())
        {
            st.push_back({ x1, y1 }); k1 = 0;
            st.push_back({ xt, yt }); k2 = 1;
            st.push_back({ x2, y2 }); k3 = 2;
        }
        else
        {
            for (int i = 0; i < int(st.size()); i++)
                if (st[i] == make_pair(x1, y1)) s++;
            for (int i = 0; i < int(st.size()); i++)
            {
                if (s == 0)
                {
                    st.push_back({ x1, y1 });
                    k1 = p;
                    p++;
                    break;
                }
                else if (s == 1 && st[i] == make_pair(x1, y1)) { k1 = i; break; }
            } s = 0;
            for (int i = 0; i < int(st.size()); i++)
                if (st[i] == make_pair(xt, yt)) s++;
            for (int i = 0; i < int(st.size()); i++)
            {
                if (s == 0)
                {
                    st.push_back({ xt, yt });
                    k2 = p;
                    p++;
                    break;
                }
                else if (s == 1 && st[i] == make_pair(xt, yt)) { k2 = i; break; }
            } s = 0;
            for (int i = 0; i < int(st.size()); i++)
                if (st[i] == make_pair(x2, y2)) s++;
            for (int i = 0; i < int(st.size()); i++)
            {
                if (s == 0)
                {
                    st.push_back({ x2, y2 });
                    k3 = p;
                    p++;
                    break;
                }
                else if (s == 1 && st[i] == make_pair(x2, y2)) { k3 = i; break; }
            } s = 0;
        }
        sp.push_back({ q / 2, {k1, k2} });
        sp.push_back({ q / 2, {k2, k3} });
    }
    long double** g = (long double**)malloc(int(sp.size()) * sizeof(long double*));
    for (int i = 0; i < int(sp.size()); i++)
    {
        g[i] = (long double*)malloc(int(sp.size()) * sizeof(long double));
        g[i][i] = 0;
        for (int j = 0; j < int(sp.size()); j++)
            if (i != j) g[i][j] = 1e8;
    }
    for (int i = 0; i < int(sp.size()); i++)
    {
        g[sp[i].second.first][sp[i].second.second] = sp[i].first;
        g[sp[i].second.second][sp[i].second.first] = sp[i].first;
    }
    for (int i = 0; i < int(st.size()); i++)
        for (int j = 0; j < int(st.size()); j++)
            for (int k = 0; k < int(st.size()); k++)
                if (g[j][k] > g[j][i] + g[i][k]) g[j][k] = g[j][i] + g[i][k];
    long double max = 1e8, time, t1, t2, now, min;
    int dot;
    for (int i = 0; i < int(st.size()); i++)
    {
        min = 0;
        if (st[i].first % 2 != 0 || st[i].second % 2 != 0) continue;
        for (int j = 0; j < int(sp.size()); j++)
        {
            time = sp[j].first;
            t1 = g[i][sp[j].second.first];
            t2 = g[i][sp[j].second.second];
            if (t2 > t1) swap(t1, t2);
            now = t1 - t2;
            time -= now;
            now += time / 2;
            now += t2;
            if (now > min) min = now;
        }
        if (min < max) { max = min; dot = i; }
    }
    cout << st[dot].first / 2 << ' ' << st[dot].second / 2 << '\n' << fixed << setprecision(5) << max;
    return 0;
}
