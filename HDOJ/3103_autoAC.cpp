#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
const double eps = 1e-5;
const double PI = acos(-1.0);
struct point
{
    double x, y;
};
struct gao
{
    double mz,zc;
};
struct gao gg[10];
bool cmp(gao a,gao b)
{
    if(a.mz!=b.mz)
        return a.mz>b.mz;
    return a.zc>b.zc;
}
double xmult(double x1,double y1,double x2,double y2,double x0,double y0)
{
    return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}
int same_side(point p1,point p2,point l1,point l2)
{
    return xmult(l1.x,l1.y,p1.x,p1.y,l2.x,l2.y)*xmult(l1.x,l1.y,p2.x,p2.y,l2.x,l2.y)>0;
}
double dis(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
point intersection(point u1,point u2,point v1,point v2)
{
    point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
             /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
double aera(point a,point b,point c)
{
    double aa,bb,cc,q;
    aa=dis(c,b);
    bb=dis(a,c);
    cc=dis(b,a);
    q=(aa+bb+cc)/2;
    double h=sqrt(q*(q-aa)*(q-bb)*(q-cc));
    h=(int)(h*1000+0.5);
    return h*0.001;
}
double get_zc(point a,point b,point c)
{
    double aa,bb,cc,q;
    aa=dis(c,b);
    bb=dis(a,c);
    cc=dis(b,a);
    q=(aa+bb+cc);
    return q;
}
int main()
{
    int i;
    double x1,y1,x2,y2,x3,y3,x4,y4;
    point a,b,c,d,e;
    while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4)!=EOF)
    {
        if(x1==0 && y1==0 && x2==0 && y2==0 && x3==0 && y3==0 && x4==0 && y4==0)
            break;
        a.x=x1;
        a.y=y1;
        b.x=x2;
        b.y=y2;
        c.x=x3;
        c.y=y3;
        d.x=x4;
        d.y=y4;
        if(same_side(a, b, c,d)==0)
            e = intersection(d,c,a,b);
        else if(same_side(d, b, c, a)==0)
            e = intersection(d,b,c,a);
        else
            e = intersection(b,c,d,a);
        gg[0].mz=aera(a,b,e);
        gg[1].mz=aera(b,c,e);
        gg[2].mz=aera(c,d,e);
        gg[3].mz=aera(a,d,e);
        gg[0].zc=get_zc(a,b,e);
        gg[1].zc=get_zc(b,c,e);
        gg[2].zc=get_zc(c,d,e);
        gg[3].zc=get_zc(a,d,e);
        sort(gg,gg+4,cmp);
        for(i=0; i<3; i++)
            printf("%.3lf %.3lf ",gg[i].mz,gg[i].zc);
        printf("%.3lf %.3lf\n",gg[i].mz,gg[i].zc);
    }
    return 0;
}
