#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    typedef struct star
    {
        float r[2];
        float v[2];
        float ac[2];
        float m;
        float s;
        struct star *next[4];
    } node;

    float G;

void expand(node*,node*,int,float,float,float);
void acceleration(node*,node*,float);

main ()
{
    node*universe,*particle;

    node*temp,*x;

    int n,i,j,k,count;
    float a=0,error;

    printf("Enter the required error and gravity constant\n");
    scanf("%f %f",&error,&G);

    printf("Enter the number of particles\n");
    scanf("%d",&n);

    particle=(node*)malloc(n*(sizeof(node)));

    for(i=0;i<n;i++)
    {
        scanf("%f %f",&(particle[i].r[0]),&(particle[i].r[1]));

        if(a<abs(particle[i].r[0]))
        a=abs(particle[i].r[0]);

        if(a<abs(particle[i].r[1]))
        a=abs(particle[i].r[1]);

        scanf("%f %f",&(particle[i].v[0]),&(particle[i].v[1]));

        particle[i].s=0;
        particle[i].ac[0]=0;
        particle[i].ac[1]=0;

        for(j=0;j<4;j++)
        {
            particle[i].next[j]=NULL;
        }
    }

    for(count=0;count<60;count++)
    {
        expand(universe,particle,n,0,0,a);

        for(i=0;i<n;i++)
        {
            acceleration(universe,&particle[i],error);
        }
    }
}

void expand(node*n,node*par,int np,float x,float y,float a)
{
    if(n=NULL)
    return;

    n->s=a;

    int i,j;

    n->next[0]->r[0]=0;
    n->next[0]->r[1]=0;
    n->next[0]->m=0;

    n->next[1]->r[0]=0;
    n->next[1]->r[1]=0;
    n->next[1]->m=0;

    n->next[2]->r[0]=0;
    n->next[2]->r[1]=0;
    n->next[2]->m=0;

    n->next[3]->r[0]=0;
    n->next[3]->r[1]=0;
    n->next[3]->m=0;


    for(i=0;i<np;i++)
    {
        if(par[i].r[0]<x+a && par[i].r[0]>x && par[i].r[1]<y+a && par[i].r[1]>y)
        {
            n->next[0]->r[0]+=par[i].m*par[i].r[0];
            n->next[0]->r[1]+=par[i].m*par[i].r[1];
            n->next[0]->m+=par[i].m;
        }

        if(par[i].r[0]<x && par[i].r[0]>x-a && par[i].r[1]<y+a && par[i].r[1]>y)
        {
            n->next[1]->r[0]+=par[i].m*par[i].r[0];
            n->next[1]->r[1]+=par[i].m*par[i].r[1];
            n->next[1]->m+=par[i].m;
        }

        if(par[i].r[0]<x && par[i].r[0]>x-a && par[i].r[1]<y && par[i].r[1]>y-a)
        {
            n->next[2]->r[0]+=par[i].m*par[i].r[0];
            n->next[2]->r[1]+=par[i].m*par[i].r[1];
            n->next[2]->m+=par[i].m;
        }

        if(par[i].r[0]<x+a && par[i].r[0]>x && par[i].r[1]<y && par[i].r[1]>y-a)
        {
            n->next[3]->r[0]+=par[i].m*par[i].r[0];
            n->next[3]->r[1]+=par[i].m*par[i].r[1];
            n->next[3]->m+=par[i].m;
        }

    }

    if(n->next[0]->m==0)
    n->next[0]=NULL;

    else
    {
        n->next[0]->r[0]/=n->next[0]->m;
        n->next[0]->r[1]/=n->next[0]->m;
    }

    if(n->next[1]->m==0)
    n->next[1]=NULL;

    else
    {
        n->next[1]->r[0]/=n->next[1]->m;
        n->next[1]->r[1]/=n->next[1]->m;
    }

    if(n->next[2]->m==0)
    n->next[2]=NULL;

    else
    {
        n->next[2]->r[0]/=n->next[2]->m;
        n->next[2]->r[1]/=n->next[2]->m;
    }

    if(n->next[3]->m==0)
    n->next[3]=NULL;

    else
    {
        n->next[3]->r[0]/=n->next[3]->m;
        n->next[3]->r[1]/=n->next[3]->m;
    }

    expand(n->next[0],par,np,x+a/2,y+a/2,a/2);
    expand(n->next[1],par,np,x-a/2,y+a/2,a/2);
    expand(n->next[2],par,np,x-a/2,y-a/2,a/2);
    expand(n->next[3],par,np,x+a/2,y-a/2,a/2);
}

void acceleration(node*x,node*y,float e)
{
    int i;
    float r,d;

    d=x->s;
    r=0;

    for(i=0;i<2;i++)
    {
        r=(y->r[i]-(x->r[i]))*(y->r[i]-(x->r[i]));
    }
    r=sqrt(r);

    if(d/r<e)
    {
        for(i=0;i<2;i++)
        {
            y->ac[i]+=G*(x->m)*(y->r[i]-(x->r[i]))/(r*r*r);
        }
    }

    else
    {
        for(i=0;i<4;i++)
        {
            acceleration(x->next[i],y,e);
        }
    }
}
