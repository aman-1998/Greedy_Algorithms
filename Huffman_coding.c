#include<stdio.h>
#include<stdlib.h>
struct node
{
    struct node *left,*right;
    int f;
    char ch;
};
int a[20],heap_size,flag;
struct node *min1,*min2;
struct node *create_node();
struct node *huffman_tree(struct node A[],int n);
struct node *insert_node(struct node A[],struct node *temp);
struct node *min_heapify(struct node A[],int i);
struct node *build_heap(struct node A[]);
struct node *delete_min(struct node A[]);
void display_codes(struct node *root,int top);
int main()
{
    int i,n;
    printf("Enter no. of characters in a file: ");
    scanf("%d",&n);
    heap_size=n;
    struct node *A=(struct node*)malloc((n+1)*sizeof(struct node));
    if(A==NULL)
    {
        printf("\nOops! Memory can't be allocated\n");
        exit(1);
    }
    fflush(stdin);
    for(i=1;i<=n;i++)
    {
        printf("Enter %d character and its frequency: ",i);
        scanf("%c %d",&A[i].ch,&A[i].f);
        A[i].left=NULL;
        A[i].right=NULL;
        fflush(stdin);
    }
    struct node *root=huffman_tree(A,n);
    display_codes(root,0);
    return 0;
}
struct node *create_node()
{
    struct node *t=(struct node*)malloc(sizeof(struct node));
    if(t==NULL)
    {
        printf("\nOops! Memory can't be allocated\n");
        exit(1);
    }
    t->ch='#';
    t->left=NULL;
    t->right=NULL;
    return t;
}
struct node *huffman_tree(struct node A[],int n)
{
    int i;
    A=build_heap(A);
    for(i=1;i<=n-1;i++)
    {
        struct node *temp=create_node();
        flag=1 //min1;
        A=delete_min(A);
        temp->left=min1;
        flag=2 //min2;
        A=delete_min(A);
        temp->right=min2;
        temp->f=(min1->f)+(min2->f);
        A=insert_node(A,temp);
    }
    flag=2;
    A=delete_min(A);
    return min2;
}
struct node *insert_node(struct node A[],struct node *temp)
{
    A[1].f=temp->f;
    A[1].ch=temp->ch;
    A[1].left=temp->left;
    A[1].right=temp->right;
    A=min_heapify(A,1);
    return A;
}
struct node *min_heapify(struct node A[],int i)
{
    int l,r,smallest;
    struct node temp;
    l=2*i;
    r=2*i+1;
    if(l<=heap_size && A[l].f<A[i].f)
        smallest=l;
    else
        smallest=i;
    if(r<=heap_size && A[r].f<A[smallest].f)
        smallest=r;
    if(smallest!=i)
    {
        temp.f=A[i].f;
        temp.ch=A[i].ch;
        temp.left=A[i].left;
        temp.right=A[i].right;

        A[i].f=A[smallest].f;
        A[i].ch=A[smallest].ch;
        A[i].left=A[smallest].left;
        A[i].right=A[smallest].right;

        A[smallest].f=temp.f;
        A[smallest].ch=temp.ch;
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
struct node *delete_min(struct node A[])
{
    if(flag==1)
    {
        min1=create_node();

        min1->f=A[1].f;
        min1->ch=A[1].ch;
        min1->left=A[1].left;
        min1->right=A[1].right;

        A[1].f=A[heap_size].f;
        A[1].ch=A[heap_size].ch;
        A[1].left=A[heap_size].left;
        A[1].right=A[heap_size].right;

        heap_size--;
        A=min_heapify(A,1);
    }
    if(flag==2)
    {
        min2=create_node();

        min2->f=A[1].f;
        min2->ch=A[1].ch;
        min2->left=A[1].left;
        min2->right=A[1].right;
    }
    return A;
}
void display_codes(struct node *root,int top)
{
    if(root->left!=NULL)
    {
        a[top]=0;
        display_codes(root->left,top+1);
    }
    if(root->right!=NULL)
    {
        a[top]=1;
        display_codes(root->right,top+1);
    }
    // if 'root' is a leaf
    if(root->left==NULL && root->right==NULL)
    {
        printf("%c - ",root->ch);
        int i;
        for(i=0;i<top;i++)
            printf("%d",a[i]);
        printf("\n");
    }
}
