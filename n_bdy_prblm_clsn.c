#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float mod(float);
void clsn(float*,float*,float*,float,float,float,float);

typedef struct particle_profile
{
    float m;

    float r[3];
    float v[3];
    float a[3];
    float d[3];
} particle;

main()
{
    particle*par;
    FILE *fp;
    fp=fopen("nbp_clsn.txt","w");

    int n,i,j,k,m;
    float t,e,g,max,rp[3],cf=0,cr=1;

    scanf("%f %f",&g,&e);
    scanf("%d",&n);

    par=(particle*)malloc(n*sizeof(particle));

    for(i=0;i<n;i++)
    {
        scanf("%f",&par[i].m);

        for(j=0;j<3;j++)
        {
            scanf("%f",&par[i].r[j]);

            par[i].a[j]=0;
        }

        for(j=0;j<3;j++)
        {
            scanf("%f",&par[i].v[j]);
        }
    }

    for(m=0;m<10000;m++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i==j) continue;

                if(i>j && mod(par[i].r[0]-par[j].r[0])<e && mod(par[i].r[0]-par[j].r[0])<e && mod(par[i].r[0]-par[j].r[0])<e)
                {
                    for(k=0;k<3;k++)
                    {
                        rp[k]=par[i].r[k]-par[j].r[k];
                    }

                    clsn(&par[i].v[0],&par[i].v[0],rp,par[i].m,par[j].m,cr,cf);
                }

                for(k=0;k<3;k++)
                {
                    par[i].a[k]+=g*par[j].m*(par[j].r[k]-par[i].r[k])/(pow(pow(par[j].r[0]-par[i].r[0],2)+pow(par[j].r[1]-par[i].r[1],2)+pow(par[j].r[2]-par[i].r[2],2),1.5));
                }
            }
        }

        for(t=1;1;t/=10)
        {
            max=0;

            for(i=0;i<n;i++)
            {
                for(j=0;j<3;j++)
                {
                    par[i].d[j]=par[i].v[j]*t+0.5*par[i].a[j]*t*t;

                    if(mod(par[i].d[j])>max) max=mod(par[i].d[j]);
                }
            }

            if(max<e) break;
        }

        for(i=0;i<n;i++)
        {
            for(j=0;j<3;j++)
            {
                par[i].r[j]+=par[i].d[j];
                par[i].v[j]+=par[i].a[j]*t;
                par[i].a[j]=0;

                fprintf(fp,"%f\t",par[i].r[j]);
            }
        }

        fprintf(fp,"\n");
    }
}

float mod(float z)
{
    if(z>=0)
    return z;
    else
    return(-z);
}

void clsn(float*v1,float*v2,float*r,float m1,float m2,float e,float m)
{
    float vn1,vn2,vt1[3],vt2[3],vtf1[3],vtf2[3],v01,v02,j;
    int i;

    v01=(v1[0]*r[0]+v1[1]*r[1]+v1[2]*r[2])/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    v02=(v2[0]*r[0]+v2[1]*r[1]+v2[2]*r[2])/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);

    for(i=0;i<3;i++)
    {
        vt1[i]=v1[i]-v01*r[i]/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
        vt2[i]=v2[i]-v02*r[i]/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    }

    vn1=((m1-e*m2)*v01+(1+e)*m2*v02)/(m1+m2);
    vn2=((m2-e*m1)*v02+(1+e)*m1*v01)/(m1+m2);

    j=mod(m1*(v01-vn1));

    for(i=0;i<3;i++)
    {
        vtf1[i]-=j*m*(vt1[i]-vt2[i])/(m1*sqrt((vt1[0]-vt2[0])*(vt1[0]-vt2[0])+(vt1[1]-vt2[1])*(vt1[1]-vt2[1])+(vt1[2]-vt2[2])*(vt1[2]-vt2[2])));
        vtf2[i]-=j*m*(vt2[i]-vt1[i])/(m2*sqrt((vt1[0]-vt2[0])*(vt1[0]-vt2[0])+(vt1[1]-vt2[1])*(vt1[1]-vt2[1])+(vt1[2]-vt2[2])*(vt1[2]-vt2[2])));

        if((vtf1[i]-vtf2[i])*(vt1[i]-vt2[i])<=0)
        {
            vtf1[i]=vtf2[i]=(m1*vt1[i]+m2*vt2[i])/(m1+m2);
        }
    }

    for(i=0;i<3;i++)
    {
        v1[i]=vtf1[i]+vn1*r[i]/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
        v2[i]=vtf2[i]+vn2*r[i]/sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
    }
}
