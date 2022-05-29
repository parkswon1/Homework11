#include<stdio.h>
#include<stdlib.h>

#define MAX_VTX 10 //최대 VERTEX지정
#define TRUE 1 //TURE는 1로 정의
#define FALSE 0 //FALSE는 0으로 정의

typedef struct Node { //graphnode구조체 생성
    int vertex; //int형 변수 vertex지정
    struct GraphNode* link; //graphnode형 포인터link지정
}GraphNode; //graphnode로 호출가능

typedef struct Type { //graphtype구조체 생성
    int vn; //int형 변수 vn
    GraphNode adj_list[MAX_VTX]; //graphnode형 adj_list생성 후 10개의 vertex가 들어갈수있게 지정
}GraphType; //graphtype으로 호출가능

int queue[MAX_VTX]; //int형 배열 queue 10개만큼 들어갈수있음
int front = -1; //int형 변수 front를 -1로 초기화지정
int rear = -1; //int형 변수 rear를 -1로 초기화 지정

int deQueue(); //int형 deQueue()함수
void enQueue(int q); //void형 enQueue함수 int q를 인자로 받아온다.
void init_queue(); //void형 init_queue() 함수
int InitializeGraph(GraphType** h); //int형 InitializeGraph함수 graphtype이중포인터형 h를 인자로가져온다
void InsertVertex(GraphType* h, int vn); //void형 InsertVertex함수 graphtype포인터형 h, int형 vn를 인자로 받아온다
void InsertEdge(GraphType* h, int edgekey1, int edgekey2); //void형 InsertEdge함수 graphtype* h, int edgekey1, int edgekey2를 인자로 받아온다
int FindVertex(GraphType* h, int edgekey); //int형 FindVertex graphtype* h, int edgekey를 인자로받아온다.
void PrintGraph(GraphType* h); //void형 PrintGraph함수 graphtype* h를 인자로 받아온다.
void sort(GraphNode* n1, GraphType* h, int v); //void형 sort함수 graphtype* n1, graphtype* h, int v를 인자로 받아온다.
void DFS_Graph(GraphType* h, int u); //void형 DFS_Graph함수 graphtype* h, int u를 인자로 받아온다.
void bfs_list(GraphType* h, int v); //void형 bfs_list함수 graphtype* h, int v를 인자로 받아온다.
void init_visited(); //void형 init_visited()함수 
void freegraph(GraphType** h); //void형 freegraph함수 graphtype** h를 인자로 받아온다.
int visited[MAX_VTX]; //int형 배열 visited 10개만큼 들어갈수 있음

int main()
{
    char command; //command받아올 char형 선언
    GraphType* h = NULL; //해드포인터를 잡아줄 graphtype형 포인터 h
    int key; //int형 key선언
    int edgekey1, edgekey2; //int형 edgekey1,key2선언
    int key2, key3; //int형 key2,key3선언
    int u = 0; //int형 u 0으로 초기화 선언
    int v = 0; //int형 v 0으로 초기화 선언
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

int InitializeGraph(GraphType** h) //동적할당을 받아오는 함수
{
    int i; //int형 변수 i
    *h = (GraphType*)malloc(sizeof(GraphType)); //헤드에 동정할당받아온다
    (*h)->vn = 0; //h해드의 vn을 0으로 초기화
    for (i = 0; i < MAX_VTX; i++) //VERTEX =10 만큼 i증가시키면서 돌리기
    {
        (*h)->adj_list[i].vertex = -9999; //adj_list의 vertex를 초기화
        (*h)->adj_list[i].link = NULL; //adj_list의 link를 초기화
    }
    for (int x = 0; x < MAX_VTX; x++) //VERTEX = 10만큼 x 증가시키면서
    {
        visited[x] = FALSE; //visited배열의 값을 FALSE로 설정
    }

    return h;
}


void InsertVertex(GraphType* h, int key)//VERTEX를 넣어주는 함수
{
    if ((h->vn) + 1 > MAX_VTX) //vn이 VERTEX보다 클경우 오류 출력후 정지
    {
        printf("Cannot Create Vertex!\n");
        return;
    }
    if (key >= MAX_VTX)//key값이 VERTEX보다 크거나 같으면 오류
    {
        printf("Key Value Error!\n");
        return;
    }
    for (int i = 0; i < h->vn; i++) //i를 h->vn만큼 증가시키면서 반복
    {
        if (h->adj_list[i].vertex == key) //h->adj_list[i]의 veretx가 key라면 중복으로 있는거라 return
        {
            return;
        }
    }
    h->adj_list[h->vn].vertex = key; //h->adj_list의 h->vn의 vertex를 key로 지정
    h->adj_list[h->vn].link = NULL; //h->adj_list의 h->vn의 link를 NULL로 지정
    h->vn = (h->vn) + 1; //h->vn를 1만큼 증가
}

void InsertEdge(GraphType* h, int edgekey1, int edgekey2) //edge를 연결해주는 함수
{
    short int a = 0; //short int형 a를 0으로 지정
    int v1, v2 = 0; //int형 v1, v2 0으로 선언
    GraphNode* node1, * node2,*cur ,*cur1;  //graphnode포인터형 node1,node2,cur,cur2생성


    for (int i = 0; i < h->vn; i++) //i를 h->vn만큼 증가시키면서
    {
        if (h->adj_list[i].vertex == edgekey1) //edgekey1와 같은 값을 가지는 정점이 존재하면 a에 1을 더해준다
        {
            a++;
        }
        if (h->adj_list[i].vertex == edgekey2) //edgekey2와 같은 값을 가지는 정점이 존재하면 a에 1을 더해준다
        {
            a++;
        }
    }
    if (a != 2) { //a가 2가 아니면 정점이 없는것임으로 return
        return;
    }

    v1 = FindVertex(h, edgekey1); //FindVertex함수를 호출 v1에 해당 인덱스 번호를 받아옴
    v2 = FindVertex(h, edgekey2); //FindVertex함수를 호출 v2에 해당 인덱스 번호를 받아옴
    node1 = (GraphNode*)malloc(sizeof(GraphNode)); //node1 동적할당
    node1->link = NULL; //node1의 link NULL로 초기화
    node1->vertex = edgekey1; //node1의 vertex를 edgekey1로 지정
    node2 = (GraphNode*)malloc(sizeof(GraphNode)); //node2 동적할당
    node2->link = NULL; //node2의 link를 NULL로 초기화
    node2->vertex = edgekey2; //node2의 vertex를 edgekey2로 초기화
    sort(node2, h, v1); //sort함수 호출후 node2를 정렬해준다
    sort(node1, h, v2);//sort함수 호출후 node1를 정렬해준다

    return;
}
void DFS_Graph(GraphType* h, int u) //DFS방식 탐색
{
    int u1 = 0; //int형 u1변수 0으로 초기화
    u1 = FindVertex(h, u); //FindVertex함수 호출로 u1에 vertex index값 받아오기
    int u2 = 0; //u2 0으로 지정

    GraphNode* cur = NULL; //graphnode형 포인터 cur을 NULL로 초기화
    GraphNode* cur1 = NULL; //graphnode형 포인터 cur1 NULL로 초기화
    cur = h->adj_list;  //cur은 h->adj_list가 됨
    cur1 = cur[u1].link;  //cur1은 cur[u1]의 link가됨
    visited[u1] = TRUE;  //viseited[u1]은 1이됨
    printf("%d", cur[u1].vertex);  //u1의 인덱스 값에 해당하는 vertex값 출력
    printf("\n");

    for (cur1; cur1; cur1 = cur1->link) //cur[u1]의 link에 해당하는 노드부터 NULL값이 될때까지 link를 반복이동하며 탐색
    {
        u2 = FindVertex(h, cur1->vertex); //u2에 cur1의 vertex에 해당하는 인덱스값을 설정
        if (visited[u2] != TRUE) //방문한 곳이 아니라면
            DFS_Graph(h, cur[u2].vertex); //DFS_Graph함수 호출
    }


}

void bfs_list(GraphType* h, int v) //BFS방식의 탐색
{
    int u1 = 0; //int형 u1 0으로 초기화
    int u2 = 0; //int형 u2 0으로 초기화
    u1 = FindVertex(h, v); //FindVertex함수 호출 로 VERTEX찾아 u1에 저장
    GraphNode* cur, * cur1 = NULL; //graphnode포인터형 cur,cur1선언후 NULL로 초기화
    cur = h->adj_list; //h->adj_list를 cur에다가 넣어주기

    init_queue(); //init_queue()함수 호출 
    visited[u1] = TRUE; //index가 u1에 해당하는 visited의 값을 1로 변경 

    printf("%d ", cur[u1].vertex); //cur[u1]의 veretx 출력 
    printf("\n");
    enQueue(u1); //enQueue함수 호출 후 u1넣어주기
    while (u2 != -9999) //u2가 -9999가 아니라면 (큐에 값이 없으면 종료)
    {
        u2 = deQueue(); //u2에 deQueue함수 호출한 값 넣어주기 
        if (u2 != -9999)  //만약 u2가 -9999가 아니라면 (큐에 값이 있으면)  
        {
            for (cur1 = cur[u2].link; cur1; cur1 = cur1->link) //cur1은 cur[u2]의 link가 되고 cur1이 cur1->link가 될떄까지 반복 
            {
                u2 = FindVertex(h, cur1->vertex); //cur1->vertex를 FindVertex함수에 넣어주고 u2에 저장 
                if (visited[u2] != TRUE) //u2에 해당하는 곳에 방문하지 않았으면 
                {
                    visited[u2] = TRUE; //u2를 방문했다는 표시 
                    printf("%d ", cur[u2].vertex); //cur[u2]의 veretx출력 
                    printf("\n");
                    enQueue(u2);//enQueue함수 호출후 u2집어넣기
                }

            }
        }
    }
}

void init_queue() //큐초기화
{
    int x = 0; //int형 변수 x는 0
    rear = front = -1; //rear값과 front값을 -1로 초기화
    for (x; x < MAX_VTX; x++) //x증가시키면서
    {
        queue[x] = -9999;//-9999값으로 배열 초기화
    }
}

void PrintGraph(GraphType* h) //그래프 출력
{
    int i = 0; //int형 변수 i는 0
    GraphNode* cur = NULL; //graphnode포인터형 cur을 NULL로 초기화
    GraphNode* cur1 = NULL; //graphnode포인터형 cur1을 NULL로 초기화
    if (h->adj_list[0].vertex == -9999) //배열의 처음이 -9999면 값이 없는것임으로 오류출력
    {
        printf("Graph is Empty!\n");
        return;
    }
    cur = h->adj_list; //cur은 h->의 list가됨
    for (i; i < (h->vn); i++)  //i를 h->vn만큼 증가
    {
        printf("%d -> ", cur[i].vertex);  //cur[i].vertex출력
        cur1 = cur[i].link; //cur[i].link가 cur1이됨
        while (cur1)  //cur1이 참이면
        {
            printf("  %d  ", cur1->vertex);  //cur1->vertex출력
            cur1 = cur1->link;  //cur1->link를 cur1에 저장 
        }
        printf("\n");
    }
}

int FindVertex(GraphType* h, int edgekey) //VERTEX의 index값 찾는 함수
{
    for (int i = 0; i < h->vn; i++) //h->vn만큼 반복하며 i증가 
    {
        if (h->adj_list[i].vertex == edgekey) //h->list[i]의 vertex의 값이 edgekey와 같다면 
        {
            return i; //i리턴(index값) 
        }
    }
    return -1;
}
void sort(GraphNode* n1, GraphType* h, int v) //edge 정렬함수
{
    GraphNode* cur = h->adj_list[v].link; //graphnode포인터 cur선언후 h->list[v]의 link로 지정 
    GraphNode* stocur = NULL; //graphnode포인터 stocur NULL로 초기화
    if (h->adj_list[v].link == NULL) //h->list[v].link값이 NULL이면
    {
        h->adj_list[v].link = n1; //h->list[v].link를 n1으로 지정하고 return 
        return;
    }
    else if (cur->vertex > n1->vertex) //cur->vertex가 n1->vertex보다 크면 
    {
        n1->link = cur; //n1->link는 cur로 지정 
        h->adj_list[v].link = n1;  //h->list[v].link를 n1으로 지정
        return;
    }
    while (cur != NULL)  //cur이 NULL이 아니면
    {
        if (cur->vertex > n1->vertex)  //cur->vertex이 n1->vertex보다 크면
        {
            stocur->link = n1; //stocur->link를 n1으로 지정 
            n1->link = cur; //n1->link를 cur로 지정 
            return;

        }
        stocur = cur; //stocur를 cur로 지정하고
        cur = cur->link; //cur를 cur->link로 지정 

    }
    n1->link = cur; //n1->link에 cur값 넣어주기
    stocur->link = n1; //stocur->link에 n1값 넣어주기 
}

void init_visited() //방문한곳 초기화 함수
{
    int x; //int형 변수 x선언
    for (x = 0; x < MAX_VTX; x++)//x를 VERTEX만큼 증가시키면서 
    {
        visited[x] = 0;//방문노드[x]를 0으로 초기화
    }
}

int deQueue() //큐삭제
{
    if (front == rear && rear == -1) //fornt가 rear값과 같거나 rear가 -1라면
    {
        printf("Queue is Empty!"); //queue가 비엇음
        return NULL; //NULL 출력
    }
    else
    {
        front = front + 1; //fornt 1증가
        return queue[front]; //queue[front]증가
    }
}

void enQueue(int q)//q를 큐에삽입
{
    if (rear == MAX_VTX) //rear이 VERTEX랑 같다면 오류 출력
    {
        printf("Queue is Full!");
    }
    else
    {
        rear = rear + 1; //rear증가시키고
        queue[rear] = q; //q값 넣어주기
    }

}
void freegraph(GraphType** h) //그래프 동적할당 해제
{
    int n; //int형 변수 n
    GraphNode* cur = (*h)->adj_list; //graphnode포인터형 cur변수에 (*h)->list값 넣어주기
    GraphNode* cur1 = NULL; //graphnode포인터형 cur1변수 NULL로 초기화
    GraphNode* cur2 = NULL; //graphnode포인터형 cur2변수 NULL로 초기화
    for (n = 0; n < MAX_VTX; n++) //n을 VERTEX만큼 증가시키면서
    {
        cur1 = cur[n].link; //cur1에 cur[n].link값 넣어주기
        while (cur1 != NULL) //cur1이 NULL이 아니라면
        {
            cur2 = cur1; //cur2에 cur1값 넣어주기
            cur1 = cur1->link; //cur1에 cur1->link값 넣어주기
            free(cur2); //cur2초기화
        }
        free(cur1); //cur1초기화
    }

    free(*h); //해드노드 동적할당 해제
    (*h) = NULL; //NULL로 초기화
}