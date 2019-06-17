#include<stdio.h>
#include<stdlib.h>
struct node
{
    int records;
    struct node *left,*right;
};
int heap_size;
struct node *min1,*min2;
struct node *create_node();
struct node *optimal_merge_pattern(struct node A[],int n);
struct node *insert(struct node A[],struct node *temp);
struct node *delete_min(struct node A[],int flag);
struct node *min_heapify(struct node A[],int i);
struct node *build_heap(struct node A[]);
int movements(struct node *root,int length,int sum);
int main()
{
    int i,n,min_mov;
    printf("Enter no. of files: ");
    scanf("%d",&n);
    heap_size=n;
    struct node *A=(struct node*)malloc((n+1)*sizeof(struct node));
    for(i=1;i<=n;i++)
    {
        printf("Enter no. of records in file%d: ",i);
        scanf("%d",&A[i].records);
        A[i].left=NULL;
        A[i].right=NULL;
    }
    struct node *root=optimal_merge_pattern(A,n);
    printf("\nsuccess\n");
    min_mov=movements(root,0,0);
    printf("\nMinimum no. of movements = %d\n",min_mov);
    return 0;
}
struct node *create_node()
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct node *optimal_merge_pattern(struct node A[],int n)
{
    int i;
    A=build_heap(A);
    for(i=1;i<=n-1;i++)
    {
        struct node *temp=create_node();
        A=delete_min(A,1);
        temp->left=min1;
        A=delete_min(A,2);
        temp->right=min2;
        temp->records=(min1->records)+(min2->records);
        A=insert(A,temp);
    }
    A=delete_min(A,2);
    return min2;
}
struct node *insert(struct node A[],struct node *temp)
{
    A[1].records=temp->records;
    A[1].left=temp->left;
    A[1].right=temp->right;
    A=min_heapify(A,1);
    return A;
}
struct node *delete_min(struct node A[],int flag1)
{
    if(flag1==1)
    {
        min1=create_node();
        min1->records=A[1].records;
        min1->left=A[1].left;
        min1->right=A[1].right;

        A[1].records=A[heap_size].records;
        A[1].left=A[heap_size].left;
        A[1].right=A[heap_size].right;

        heap_size--;
        A=min_heapify(A,1);
    }
    if(flag1==2)
    {
        min2=create_node();
        min2->records=A[1].records;
        min2->left=A[1].left;
        min2->right=A[1].right;
    }
    return A;
}
struct node *min_heapify(struct node A[],int i)
{
    int l,r,smallest;
    struct node temp;
    l=2*i;
    r=2*i+1;
    if(l<=heap_size && A[l].records<A[i].records)
        smallest=l;
    else
        smallest=i;
    if(r<=heap_size && A[r].records<A[smallest].records)
        smallest=r;
    if(smallest!=i)
    {
        temp.records=A[i].records;
        temp.left=A[i].left;
        temp.right=A[i].right;

        A[i].records=A[smallest].records;
        A[i].left=A[smallest].left;
        A[i].right=A[smallest].right;

        A[smallest].records=temp.records;
        A[smallest].left=temp.left;
        A[smallest].right=temp.right;

        A=min_heapify(A,smallest);
    }
    return A;
}
struct node *build_heap(struct node A[])
{
    int i;
    for(i=heap_size/2;i>=1;i--)
        A=min_heapify(A,i);
    return A;
}
int movements(struct node *root,int length,int sum)
{
    if(root->left!=NULL)
        sum=movements(root->left,length+1,sum);
    if(root->right!=NULL)
        sum=movements(root->right,length+1,sum);
    if(root->left==NULL && root->right==NULL)
        sum+=length*(root->records);
    return sum;
}
