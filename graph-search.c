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