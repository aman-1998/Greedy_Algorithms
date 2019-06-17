#include<stdio.h>
#include<stdlib.h>
int Prim_MST(int **cost,int n,int min,int k,int l);
int main()
{
    int n,i,j,min=999,k,l;
    printf("Enter no. of vertices: ");
    scanf("%d",&n);
    int **cost=(int**)malloc((n+1)*sizeof(int*));
    for(i=1;i<=n;i++)
        cost[i]=(int*)malloc((n+1)*sizeof(int));
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            printf("Enter cost[%d][%d] ",i,j);
            scanf("%d",&cost[i][j]);
            if(min>cost[i][j] && i!=j)
            {
                min=cost[i][j];
                k=i;
                l=j;
            }
        }
    }
    printf("\nAdjacency Matrix:-\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(cost[i][j]==999)
                printf("%c ",236);
            else
                printf("%d ",cost[i][j]);
        }
        printf("\n");
    }
    int min_cost=Prim_MST(cost,n,min,k,l);
    printf("\nMinimum cost = %d\n",min_cost);
    return 0;
}
int Prim_MST(int **cost,int n,int min,int k,int l)
{
    int i,j,min_cost=min;
    int *near=(int*)malloc((n+1)*sizeof(int));
    int **st=(int**)malloc((n-1)*sizeof(int*));
    for(i=0;i<=n-2;i++)
        st[i]=(int*)malloc(2*sizeof(int));
    for(i=1;i<=n;i++)
    {
        if(cost[i][k]<cost[i][l])
            near[i]=k;
        else
            near[i]=l;
    }
    near[k]=0;
    near[l]=0;
    st[0][0]=k;
    st[0][1]=l;
    for(i=1;i<=n-2;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(near[j]!=0)
            {
                min=999;
                if(cost[j][near[j]]<min)
                {
                    min=cost[j][near[j]];
                    k=j;
                    l=near[j];
                }
            }
        }
        min_cost+=min;
        near[k]=0;
        st[i][0]=l;
        st[i][1]=k;
        for(j=1;j<=n;j++)
        {
            if(near[j]!=0)
            {
                if(cost[j][near[j]]>cost[j][k])
                    near[j]=k;
            }
        }
    }
    printf("\nMST:-\n");
    for(i=0;i<=n-2;i++)
        printf("%d --- %d\n",st[i][0],st[i][1]);
    return min_cost;
}
