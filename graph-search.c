#include<stdio.h>
#include<stdlib.h>

#define MAX_VTX 10 
#define TRUE 1
#define FALSE 0

typedef struct Node {
    int vertex; 
    struct GraphNode* link; 
}GraphNode;

typedef struct Type {
    int vn; 
    GraphNode adj_list[MAX_VTX]; 
}GraphType;

int queue[MAX_VTX];
int front = -1;
int rear = -1;

int deQueue(); 
void enQueue(int q);
void init_queue();

int InitializeGraph(GraphType** h); 
void InsertVertex(GraphType* h, int vn); 
void InsertEdge(GraphType* h, int edgekey1, int edgekey2); 
int FindVertex(GraphType* h, int edgekey); 
void PrintGraph(GraphType* h); 
void sort(GraphNode* n1, GraphType* h, int v); 
void DFS_Graph(GraphType* h, int u); 
void bfs_list(GraphType* h, int v); 
void init_visited(); 
void freegraph(GraphType** h); 
int visited[MAX_VTX]; 

int main()
{
    char command;
    GraphType* h = NULL;
    int key;
    int edgekey1, edgekey2;
    int key2, key3;
    int u = 0;
    int v = 0;
    printf("[----- [SeokWonPark] [2017018003] -----]\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Grape     = z  \n");
        printf(" Insert Vertex        = v          Insert Edge             = e \n");
        printf(" Depth First Search   = d          Breath First Search     = b\n");
        printf(" Print Graph          = p          Quit                    = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        fflush(stdout);
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            InitializeGraph(&h);
            break;
        case 'v': case 'V':
            printf("Insert Vertex : ");
            fflush(stdout);
            scanf("%d", &key);
            InsertVertex(h, key);
            break;
        case 'e': case 'E':
            printf("Select Vertex :");
            fflush(stdout);
            scanf("%d", &edgekey1);
            printf("\n");
            printf("\nSelect Vertex to Connect : ");
            fflush(stdout);
            scanf("%d", &edgekey2);
            printf("\n");

            InsertEdge(h, edgekey1, edgekey2);
            break;
        case 'd': case 'D':
            printf("Choose First Vertex : ");
            fflush(stdout);
            scanf("%d", &key2);
            u = key2;
            DFS_Graph(h, u);
            init_visited();
            break;
        case 'b': case 'B':
            printf("Choose First Vertex : ");
            fflush(stdout);
            scanf("%d", &key3);
            v = key3;
            bfs_list(h, v);
            init_visited();
            init_queue();
            break;
        case 'p': case 'P':
            PrintGraph(h);
            break;
        case 'q': case 'Q':
            freegraph(&h);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int InitializeGraph(GraphType** h)
{
    int i;
    *h = (GraphType*)malloc(sizeof(GraphType)); 
    (*h)->vn = 0; 
    for (i = 0; i < MAX_VTX; i++)
    {
        (*h)->adj_list[i].vertex = -9999;
        (*h)->adj_list[i].link = NULL;
    }
    for (int x = 0; x < MAX_VTX; x++)
    {
        visited[x] = FALSE;
    }

    return h;
}


void InsertVertex(GraphType* h, int key)
{
    if ((h->vn) + 1 > MAX_VTX) 
    {
        printf("Cannot Create Vertex!\n");
        return;
    }
    if (key >= MAX_VTX)
    {
        printf("Key Value Error!\n");
        return;
    }
    for (int i = 0; i < h->vn; i++) 
    {
        if (h->adj_list[i].vertex == key) 
        {
            return;
        }
    }
    h->adj_list[h->vn].vertex = key; 
    h->adj_list[h->vn].link = NULL; 
    h->vn = (h->vn) + 1; 
}

void InsertEdge(GraphType* h, int edgekey1, int edgekey2)
{
    short int a = 0;
    int v1, v2 = 0;
    GraphNode* node1, * node2,*cur ,*cur1;


    for (int i = 0; i < h->vn; i++)
    {
        if (h->adj_list[i].vertex == edgekey1) 
        {
            a++;
        }
        if (h->adj_list[i].vertex == edgekey2) 
        {
            a++;
        }
    }
    if (a != 2) {
        return;
    }

    v1 = FindVertex(h, edgekey1);
    v2 = FindVertex(h, edgekey2);
    node1 = (GraphNode*)malloc(sizeof(GraphNode));
    node1->link = NULL;
    node1->vertex = edgekey1;
    node2 = (GraphNode*)malloc(sizeof(GraphNode));
    node2->link = NULL;
    node2->vertex = edgekey2;
    sort(node2, h, v1);
    sort(node1, h, v2);

    return;
}
void DFS_Graph(GraphType* h, int u)
{
    int u1 = 0;
    u1 = FindVertex(h, u); 
    int u2 = 0;

    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    cur = h->adj_list; 
    cur1 = cur[u1].link; 
    visited[u1] = TRUE;
    printf("%d", cur[u1].vertex); 
    printf("\n");

    for (cur1; cur1; cur1 = cur1->link) 
    {
        u2 = FindVertex(h, cur1->vertex); 
        if (visited[u2] != TRUE) 
            DFS_Graph(h, cur[u2].vertex); 
    }


}

void bfs_list(GraphType* h, int v)
{
    int u1 = 0;
    int u2 = 0;
    u1 = FindVertex(h, v); 
    GraphNode* cur, * cur1 = NULL; 
    cur = h->adj_list;

    init_queue(); 
    visited[u1] = TRUE; 

    printf("%d ", cur[u1].vertex); 
    printf("\n");
    enQueue(u1);
    while (u2 != -9999)
    {
        u2 = deQueue(); 
        if (u2 != -9999)  
        {
            for (cur1 = cur[u2].link; cur1; cur1 = cur1->link) 
            {
                u2 = FindVertex(h, cur1->vertex); 
                if (visited[u2] != TRUE) 
                {
                    visited[u2] = TRUE; 
                    printf("%d ", cur[u2].vertex); 
                    printf("\n");
                    enQueue(u2);
                }

            }
        }
    }
}

void init_queue()
{
    int x = 0;
    rear = front = -1;
    for (x; x < MAX_VTX; x++)
    {
        queue[x] = -9999;
    }
}

void PrintGraph(GraphType* h)
{
    int i = 0;
    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    if (h->adj_list[0].vertex == -9999)
    {
        printf("�׷����� ����ֽ��ϴ�.\n");
        return;
    }
    cur = h->adj_list;
    for (i; i < (h->vn); i++) 
    {
        printf("%d -> ", cur[i].vertex); 
        cur1 = cur[i].link; 
        while (cur1) 
        {
            printf("  %d  ", cur1->vertex); 
            cur1 = cur1->link; 
        }
        printf("\n");
    }
}


int FindVertex(GraphType* h, int edgekey)
{
    for (int i = 0; i < h->vn; i++) 
    {
        if (h->adj_list[i].vertex == edgekey) 
        {
            return i; 
        }
    }
    return -1;
}
void sort(GraphNode* n1, GraphType* h, int v)
{
    GraphNode* cur = h->adj_list[v].link; 
    GraphNode* stocur = NULL;
    if (h->adj_list[v].link == NULL)
    {
        h->adj_list[v].link = n1; 
        return;
    }
    else if (cur->vertex > n1->vertex) 
    {
        n1->link = cur; 
        h->adj_list[v].link = n1; 
        return;
    }
    while (cur != NULL) 
    {
        if (cur->vertex > n1->vertex) 
        {
            stocur->link = n1; 
            n1->link = cur; 
            return;

        }
        stocur = cur;
        cur = cur->link; 

    }
    n1->link = cur; 
    stocur->link = n1; 
}

void init_visited()
{
    int x;
    for (x = 0; x < MAX_VTX; x++)
    {
        visited[x] = FALSE;
    }
}

int deQueue()
{
    if (front == rear && rear == -1) 
    {
        printf("Queue is Empty");
        return NULL;
    }
    else
    {
        front = front + 1; 
        return queue[front]; 
    }

}

void enQueue(int q)
{
    if (rear == MAX_VTX) 
    {
        printf("Queue is Full");
    }

    else
    {
        rear = rear + 1; 
        queue[rear] = q; 
    }
}

void freegraph(GraphType** h)
{
    int n;
    GraphNode* cur = (*h)->adj_list; 
    GraphNode* cur1 = NULL;
    GraphNode* cur2 = NULL;
    for (n = 0; n < MAX_VTX; n++) 
    {
        cur1 = cur[n].link; 
        while (cur1 != NULL) 
        {
            cur2 = cur1; 
            cur1 = cur1->link; 
            free(cur2); 
        }
        free(cur1); 
    }

    free(*h); 
    (*h) = NULL;
}