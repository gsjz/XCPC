#include<bits/stdc++.h>  
using namespace std;  
const double eps = 1e-9; 
pair<double, double> getCircle(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
    double A = p2.first - p1.first;
    double B = p2.second - p1.second;
    double C = p3.first - p1.first;
    double D = p3.second - p1.second;
    double E = A * (p1.first + p2.first) + B * (p1.second + p2.second);
    double F = C * (p1.first + p3.first) + D * (p1.second + p3.second);
    double det = 2 * (A * D - B * C);
    if (abs(det) < eps) 
    {
        return {0, 0};
    }
    double centerX = (D * E - B * F) / det;
    double centerY = (A * F - C * E) / det;
    return {centerX, centerY};
}
void solve()
{
    int n;
    cin>>n;
    vector<pair<double, double> > p(n);
    for(int i=0; i<n; i++) cin>>p[i].first>>p[i].second;
    random_shuffle(p.begin(), p.end());
    auto dis = [&](pair<double, double> x, pair<double, double> y)
    {
        return sqrt( pow(x.first - y.first, 2) + pow(x.second - y.second, 2) );
    };
    pair<double, double> O = p[0];
    double R = 0;
    for(int i=1; i<n; i++)
    {
        if(dis(p[i], O) > R + eps)
        {
            O = p[i], R = 0;
            for(int j=0; j<i; j++)
            {
                if(dis(p[j], O) > R + eps)
                {
                    O.first = (p[i].first + p[j].first)/2;
                    O.second = (p[i].second + p[j].second)/2;
                    R = dis(p[j], O);
                    for(int k=0; k<j; k++)
                    {
                        if(dis(p[k], O) > R + eps)
                        {
                            O = getCircle(p[i], p[j], p[k]);
                            R = dis(p[k], O);
                        }
                    }
                }
            }
        }
    }
    cout<<R<<"\n"<<O.first<<" "<<O.second<<"\n";
    return;
}
int main()
{  
    ios::sync_with_stdio(0);  
    cin.tie(0); 
    cout.tie(0);  
    cout<<fixed<<setprecision(10);
    int T = 1;  
    // cin>>T;  
    while(T--)
    {   
        solve();
    }
    return 0;  
} 