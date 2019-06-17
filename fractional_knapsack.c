#include<stdio.h>
#include<stdlib.h>
struct node
{
    int ob;
    float w,p,pw;
};
int heap_size;
float frac_knapsack(struct node A[],int n,float W);
struct node *build_heap(struct node A[]);
struct node *min_heapify(struct node A[],int i);
struct node *heap_sort_min_heap(struct node A[]);
int main()
{
    int n,i;
    float W;
    printf("Enter the capacity of the knapsack: ");
    scanf("%f",&W);
    printf("Enter no. of objects: ");
    scanf("%d",&n);
    heap_size=n;
    struct node *A=(struct node*)malloc((n+1)*sizeof(struct node));
    for(i=1;i<=n;i++)
    {
        printf("Enter weight and profit for obj%d: ",i);
        scanf("%f %f",&A[i].w,&A[i].p);
        A[i].ob=i;
    }
    float max_profit=frac_knapsack(A,n,W); // T(n)=O(n.log(n))
    printf("Maximum profit = %f",max_profit);
    return 0;
}
float frac_knapsack(struct node A[],int n,float W)
{
    int i;
    float profit=0;
    for(i=1;i<=n;i++)
        A[i].pw=A[i].p/A[i].w;
    A=build_heap(A);
    A=heap_sort_min_heap(A); // decreasing order
    for(i=1;i<=n;i++)
    {
        if(A[i].w<=W)
        {
            profit+=A[i].p;
            W-=A[i].w;
        }
        else
        {
            profit+=(A[i].p/A[i].w)*W;
            W=0;
            break;
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
    int smallest,l,r;
    struct node temp;
    l=2*i;
    r=2*i+1;
    if(l<=heap_size && A[l].pw<A[i].pw)
        smallest=l;
    else
        smallest=i;
    if(r<=heap_size && A[r].pw<A[smallest].pw)
        smallest=r;
    if(smallest!=i)
    {
        temp.ob=A[smallest].ob;
        temp.p=A[smallest].p;
        temp.w=A[smallest].w;
        temp.pw=A[smallest].pw;

        A[smallest].ob=A[i].ob;
        A[smallest].p=A[i].p;
        A[smallest].w=A[i].w;
        A[smallest].pw=A[i].pw;

        A[i].ob=temp.ob;
        A[i].p=temp.p;
        A[i].w=temp.w;
        A[i].pw=temp.pw;

        A=min_heapify(A,smallest);
    }
    return A;
}
struct node *heap_sort_min_heap(struct node A[])
{
    struct node min;
    while(heap_size>=1)
    {
        min.ob=A[1].ob;
        min.p=A[1].p;
        min.w=A[1].w;
        min.pw=A[1].pw;

        A[1].ob=A[heap_size].ob;
        A[1].p=A[heap_size].p;
        A[1].w=A[heap_size].w;
        A[1].pw=A[heap_size].pw;

        A[heap_size].ob=min.ob;
        A[heap_size].p=min.p;
        A[heap_size].w=min.w;
        A[heap_size].pw=min.pw;

        heap_size--;
        A=min_heapify(A,1);
    }
    return A;
}
