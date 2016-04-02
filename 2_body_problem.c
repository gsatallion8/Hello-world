#include <stdio.h>
#include <math.h>

typedef struct particle_profile
{
    float m;

    float r[3];
    float v[3];
    float a[3];
    float d[3];
} particle;

float mod(float);

main()
{
    particle par[2];

    int i,j,k;
    float g,e,rr[3],t,rd;
    FILE *fp;

    fp=fopen("2bp.txt","w");

    scanf("%f %f",&g,&e);


    for(i=0;i<2;i++)
    {
        scanf("%f",&par[i].m);

        scanf("%f %f %f",&par[i].r[0],&par[i].r[1],&par[i].r[2]);

        scanf("%f %f %f",&par[i].v[0],&par[i].v[1],&par[i].v[2]);

        for(j=0;j<3;j++)
        {
            par[i].d[j]=0;
        }
    }

    for(i=0;i<10000;i++)
    {
        for(j=0;j<3;j++)
        {
            rr[j]=par[1].r[j]-par[0].r[j];
        }

        rd=sqrt(pow(rr[0],2)+pow(rr[1],2)+pow(rr[2],2));

        for(k=0;k<3;k++)
        {
            par[0].a[k]=g*(par[1].m)*rr[k]/(pow(rd,3));
            par[1].a[k]=-g*(par[0].m)*rr[k]/(pow(rd,3));
        }

        for(t=1;1;t/=10)
        {
            for(j=0;j<2;j++)
            {
                for(k=0;k<3;k++)
                {
                    par[j].d[k]=(par[j].v[k])*t+0.5*(par[j].a[k])*t*t;
                }
            }

            if(mod(par[0].d[0])<e&&mod(par[0].d[1])<e&&mod(par[0].d[2])<e&&mod(par[1].d[0])<e&&mod(par[1].d[1])<e&&mod(par[1].d[2])<e)
            break;
        }

        for(j=0;j<2;j++)
        {
            for(k=0;k<3;k++)
            {
                par[j].r[k]+=par[j].d[k];
                fprintf(fp,"%f\t",par[j].r[k]);

                par[j].v[k]+=(par[j].a[k])*t;
                par[j].a[k]=0;
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
