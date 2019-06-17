#include<stdio.h>
#include<stdlib.h>
struct node
{
    int f;
    char ch;
    struct node *left,*right;
};
struct info
{
    char ch;
    int code[20];
    int code_length;
};
int a[20],heap_size,flag;
struct node *min1,*min2;
char *build_heap_msg(char msg[]);
char *max_heapify(char msg[],int i);
char *heap_sort_Max_Heap(char msg[]);
struct node *create_node();
struct node *huffman_tree(struct node A[],int n);
struct node *insert(struct node A[],struct node *temp);
struct node *build_heap(struct node A[]);
struct node *min_heapify(struct node A[],int i);
struct node *delete_min(struct node A[]);
struct info *display_and_fetch_codes(struct node *root,int top,struct info C[]);
int main()
{
    int i,n,flag1,count,x,m,j,k;
    char character;
    printf("Enter length of the message: ");
    scanf("%d",&m);
    heap_size=m;
    char *msg=(char*)malloc((m+1)*sizeof(char));
    char *ori=(char*)malloc((m+1)*sizeof(char));
    struct node *A=(struct node*)malloc(sizeof(struct node));
    printf("\nEnter the message:-\n");
    fflush(stdin);
    for(i=1;i<=m;i++)
    {
        printf("Enter message[%d] ",i);
        scanf("%c",&msg[i]);
        ori[i]=msg[i];
        fflush(stdin);
    }
    printf("\nMessage:-\n");
    for(i=1;i<=m;i++)
        printf("%c",msg[i]);
    msg=build_heap_msg(msg);
    msg=heap_sort_Max_Heap(msg);
    character=msg[1];
    flag1=0;
    x=1;
    for(i=1;i<=m;i++)
    {
        if(character!=msg[i] || flag1==0)
        {
            character=msg[i];
            A=(struct node*)realloc(A,(x+1)*sizeof(struct node));
            A[x].ch=msg[i];
            A[x].left=NULL;
            A[x].right=NULL;
            x++;
            flag1=1;
            count=0;
        }
        count++;
        A[x-1].f=count;
    }
    struct info *C=(struct info*)malloc((x-1)*sizeof(struct info));
    n=x-1;
    heap_size=x-1;
    printf("\n\n");
    printf("char\tfrequency\n");
    for(i=1;i<=n;i++)
        printf(" %c\t   %d\n",A[i].ch,A[i].f);
    printf("\n");
    struct node *root=huffman_tree(A,n);
    printf("\nchar\tcode\n");
    C=display_and_fetch_codes(root,0,C);
    printf("\nHuffman Encoding:-\n");
    for(i=1;i<=m;i++)
    {
        for(j=0;j<=n-1;j++)
        {
            if(ori[i]==C[j].ch)
            {
                for(k=0;k<C[j].code_length;k++)
                    printf("%d",C[j].code[k]);
            }
        }
    }
    printf("\n");
    return 0;
}
char *build_heap_msg(char msg[])
{
    int i;
    for(i=heap_size/2;i>=1;i--)
        msg=max_heapify(msg,i);
    return msg;
}
char *max_heapify(char msg[],int i)
{
    int l,r,largest;
    char temp;
    l=2*i;
    r=2*i+1;
    if(l<=heap_size && msg[l]>msg[i])
        largest=l;
    else
        largest=i;
    if(r<=heap_size && msg[r]>msg[largest])
        largest=r;
    if(largest!=i)
    {
        temp=msg[i];
        msg[i]=msg[largest];
        msg[largest]=temp;
        msg=max_heapify(msg,largest);
    }
    return msg;
}
char *heap_sort_Max_Heap(char msg[])
{
    int max;
    while(heap_size>=1)
    {
        max=msg[1];
        msg[1]=msg[heap_size];
        msg[heap_size]=max;
        heap_size--;
        msg=max_heapify(msg,1);
    }
    return msg;
}
struct node *create_node()
{
    struct node *t;
    t=(struct node*)malloc(sizeof(struct node));
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
        flag=1;
        A=delete_min(A);
        temp->left=min1;
        flag=2;
        A=delete_min(A);
        temp->right=min2;
        temp->f=(min1->f)+(min2->f);
        A=insert(A,temp);
    }
    flag=2;
    A=delete_min(A);
    return min2;
}
struct node *insert(struct node A[],struct node *temp)
{
    A[1].f=temp->f;
    A[1].ch=temp->ch;
    A[1].left=temp->left;
    A[1].right=temp->right;
    A=min_heapify(A,1);
    return A;
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
struct info *display_and_fetch_codes(struct node *root,int top,struct info C[])
{
    static int x=0;
    if(root->left!=NULL)
    {
        a[top]=0;
        C=display_and_fetch_codes(root->left,top+1,C);
    }
    if(root->right!=NULL)
    {
        a[top]=1;
        C=display_and_fetch_codes(root->right,top+1,C);
    }
    if(root->left==NULL && root->right==NULL)
    {
        printf(" %c\t",root->ch);
        C[x].ch=root->ch;
        C[x].code_length=top;
        int i;
        for(i=0;i<top;i++)
        {
             printf("%d",a[i]);
             C[x].code[i]=a[i];
        }
        x++;
        printf("\n");
    }
    return C;
}
