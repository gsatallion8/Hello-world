#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float mod(float);

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
    fp=fopen("nbp.txt","w");
    int n,i,j,k,m;
    float t,e,g,max;

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
