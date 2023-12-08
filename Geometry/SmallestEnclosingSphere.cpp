// 최소 외접구
// worst case O(N^4)
// main 함수 사용 예시는 boj 11930
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct p { double x, y, z; };

double eps = 1e-4;

double dis(p a, p b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
pair<double, p> SmallestEnclosingSphere(const vector<p>& v) {
    int N = v.size();
    p cen = {0, 0, 0};
    double r = 0;

    for(int i = 0; i < N; i++) {
        if(dis(cen, v[i]) <= r) continue;

        cen = v[i], r = 0;

        for(int j = 0; j < i; j++) {
            if(dis(cen, v[j]) <= r) continue;

            cen = {(v[i].x + v[j].x) / 2, (v[i].y + v[j].y) / 2, (v[i].z + v[j].z) / 2};
            r = dis(cen, v[i]);

            for(int k = 0; k < j; k++) {
                if(dis(cen, v[k]) <= r) continue;

                double ax = v[i].x, ay = v[i].y, az = v[i].z;
                double bx = v[j].x, by = v[j].y, bz = v[j].z;
                double cx = v[k].x, cy = v[k].y, cz = v[k].z;

                double Cx = bx - ax, Cy = by - ay, Cz = bz - az;
                double Bx = cx - ax, By = cy - ay, Bz = cz - az;

                double B2 = ax*ax - cx*cx + ay*ay - cy*cy + az*az - cz*cz;
                double C2 = ax*ax - bx*bx + ay*ay - by*by + az*az - bz*bz;

                double CByz = Cy*Bz - Cz*By;
                double CBxz = Cx*Bz - Cz*Bx;
                double CBxy = Cx*By - Cy*Bx;

                double zz1 = - (Bz - Cz*Bx/Cx) / (By - Cy*Bx/Cx);
                double z01 = - (B2 - Bx/Cx*C2) / ((By - Cy*Bx/Cx) * 2);
                double zz2 = - (zz1*Cy + Cz) / Cx;
                double z02 = - (z01*Cy*2 + C2) / (Cx * 2);

                cen.z = - ((z02 - ax) * CByz - (z01 - ay) * CBxz - az * CBxy) / (zz2 * CByz - zz1 * CBxz + CBxy);
                cen.x = zz2 * cen.z + z02;
                cen.y = zz1 * cen.z + z01;

                r = dis(cen, v[i]);

                for(int l = 0; l < k; l++) {
                    if(dis(cen, v[l]) <= r) continue;

                    double x1 = v[i].x, x2 = v[j].x, x3 = v[k].x, x4 = v[l].x;
                    double y1 = v[i].y, y2 = v[j].y, y3 = v[k].y, y4 = v[l].y;
                    double z1 = v[i].z, z2 = v[j].z, z3 = v[k].z, z4 = v[l].z;

                    double a11 = x2 - x1, a12 = y2 - y1, a13 = z2 - z1;
                    double a21 = x3 - x2, a22 = y3 - y2, a23 = z3 - z2;
                    double a31 = x4 - x1, a32 = y4 - y1, a33 = z4 - z1;

                    double det = a11 * (a22*a33 - a23*a32) - a12 * (a21*a33 - a23*a31) + a13 * (a21*a32 - a22*a31);

                    double c11 = a22*a33 - a32*a23, c12 = - (a12*a33 - a32*a13), c13 = a12*a23 - a22*a13;
                    double c21 = - (a21*a33 - a31*a23), c22 = a11*a33 - a31*a13, c23 = - (a11*a23 - a21*a13);
                    double c31 = a21*a32 - a31*a22, c32 = - (a11*a32 - a31*a12), c33 = a11*a22 - a21*a12;

                    double xx = x2*x2 - x1*x1 + y2*y2 - y1*y1 + z2*z2 - z1*z1;
                    double yy = x3*x3 - x2*x2 + y3*y3 - y2*y2 + z3*z3 - z2*z2;
                    double zz = x4*x4 - x1*x1 + y4*y4 - y1*y1 + z4*z4 - z1*z1;

                    cen.x = (c11*xx + c12*yy + c13*zz) / (det * 2);
                    cen.y = (c21*xx + c22*yy + c23*zz) / (det * 2);
                    cen.z = (c31*xx + c32*yy + c33*zz) / (det * 2);

                    r = dis(cen, v[i]);
                }
            }
        }
    }

    if(abs(cen.x) < eps) cen.x = 0;
    if(abs(cen.y) < eps) cen.y = 0;
    if(abs(cen.z) < eps) cen.z = 0;

    return {r, cen};
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cout << fixed;
    cout.precision(2);

    int N; cin >> N;
    vector<p> v(N);
    for(int i = 0; i < N; i++) cin >> v[i].x >> v[i].y >> v[i].z;

    pair<double, p> sphere = SmallestEnclosingSphere(v);
    //cout << sphere.second.x << " " << sphere.second.y << " " << sphere.second.z << "\n";
    cout << sphere.first << "\n";

    return 0;
}
