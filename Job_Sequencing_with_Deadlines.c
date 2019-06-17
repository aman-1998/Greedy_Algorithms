#include<stdio.h>
#include<stdlib.h>
struct node
{
    int job,D;
    float P;
};
int heap_size;
float job_sequencing(struct node A[],int n,int max_deadline);
struct node *build_heap(struct node A[]);
struct node *min_heapify(struct node A[],int i);
struct node *heap_sort_min_heap(struct node A[]);
int main()
{
    int n,i,max_deadline=0;
    printf("Enter no. of jobs: ");
    scanf("%d",&n);
    struct node *A=(struct node*)malloc((n+1)*sizeof(struct node));
    heap_size=n;
    for(i=1;i<=n;i++)
    {
        printf("Enter deadline and profit for job%d: ",i);
        scanf("%d %f",&A[i].D,&A[i].P);
        A[i].job=i;
        if(A[i].D>max_deadline)
            max_deadline=A[i].D;
    }
    float max_profit=job_sequencing(A,n,max_deadline);
    printf("Max profit = %f",max_profit);
    return 0;
}
float job_sequencing(struct node A[],int n,int max_deadline)
{
    int i,j,x;
    float profit=0;
    int *t=(int*)calloc(max_deadline,sizeof(int));
    A=build_heap(A);
    A=heap_sort_min_heap(A);
    for(i=1;i<=n;i++)
    {
        x=A[i].D;
        for(j=x-1;j>=0;j--)
        {
            if(t[j]==0)
            {
                t[j]=1;
                printf("Job%d is to be done between %d to %d\n",A[i].job,j,j+1);
                profit+=A[i].P;
                break;
            }
        }
    }
    return profit;
}
struct node *build_heap(struct node A[])
{
    int i;
    for(i=heap_size/2;i>=1;i--)
        A=min_heapify(A,i);
    return A;
}
struct node *min_heapify(struct node A[],int i)
{
    int l,r,smallest;
    struct node temp;
    l=2*i;
    r=2*i+1;
    if(l<=heap_size && A[l].P<A[i].P)
        smallest=l;
    else
        smallest=i;
    if(r<=heap_size && A[r].P<A[smallest].P)
        smallest=r;
    if(smallest!=i)
    {
        temp.job=A[i].job;
        temp.D=A[i].D;
        temp.P=A[i].P;

        A[i].job=A[smallest].job;
        A[i].D=A[smallest].D;
        A[i].P=A[smallest].P;

        A[smallest].job=temp.job;
        A[smallest].D=temp.D;
        A[smallest].P=temp.P;

        A=min_heapify(A,smallest);
    }
    return A;
}
struct node *heap_sort_min_heap(struct node A[])
{
    struct node min;
    while(heap_size>=1)
    {
        min.job=A[1].job;
        min.D=A[1].D;
        min.P=A[1].P;

        A[1].job=A[heap_size].job;
        A[1].D=A[heap_size].D;
        A[1].P=A[heap_size].P;

        A[heap_size].job=min.job;
        A[heap_size].D=min.D;
        A[heap_size].P=min.P;

        heap_size--;
        A=min_heapify(A,1);
    }
    return A;
}
