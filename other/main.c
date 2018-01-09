#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define INFINITY 1000

//typedef 别名
//会用到哪些结构体，
//1. 点（x,y,index,bool enable）
//2. 边（start，end，length）
//3. 图（int[n][n]) n -> 点的个数

typedef struct _Vertex { //顶点的数据结构，用 Vertex 代替 struct _vertex
    int x;
    int y;
    int id; //从 0 开始
    int enable;    //是否可用
} Vertex;

typedef struct _Edge {
    int start;  // 点的 id
    int end;    // 点的 id
    double length;  //长度
} Edge;

typedef struct _Graph {
    int vertexNum;
    int edgeNum;
    double matrix[INFINITY][INFINITY];    //矩阵，表示点之间的连接关系
    Vertex *vertexs[INFINITY];  //点的数组
} Graph;

//执行 prime 算法的结果
typedef struct _Result {
    int length;
    Edge *edges[INFINITY];
} Result;

const char PATH[] = "data.txt";     //文件的路径

/**
 * 检测文件是否存在
 * @return
 */
bool checkFileValid() {
    FILE *fp;
    return fp == fopen(PATH, "r") != NULL;
}

/*
 * 获取两个点之间的距离
 */
double getDistance(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

/**
 * 从文件中读取数据
 * @return Graph*
 */
Graph *readData() {
    FILE *fp;
    fp = fopen(PATH, "r");
    Graph *graph = (Graph *) malloc(sizeof(Graph *));  //创建一个图的指针并为其分配内存空间
    fscanf(fp, "%d", graph->vertexNum);   //从文件中读取点的个数
    if (graph->vertexNum == 0)  //如果点的个数为空
        return graph;
    for (int i = 0; i < graph->vertexNum; i++) {  //读取所有点的坐标
        Vertex *tempVertex = (Vertex *) malloc(sizeof(Vertex *));  //创建一个点的指针并为其分配内存空间
        fscanf(fp, "%d %d %d %d", tempVertex->id, tempVertex->x,
               tempVertex->y, tempVertex->enable);
        graph->vertexs[tempVertex->id] = tempVertex;
    }
    fscanf(fp, "%d", graph->edgeNum); //从文件中读取边的个数
    for (int i = 0; i < graph->edgeNum; i++) {
        Edge *tempEdge = (Edge *) malloc(sizeof(Edge *));   //创建一个边的指针并为其分配内存空间
        fscanf(fp, "%d %d", tempEdge->start, tempEdge->end);
        tempEdge->length = getDistance(graph->vertexs[tempEdge->start]->x,
                                       graph->vertexs[tempEdge->start]->y,
                                       graph->vertexs[tempEdge->end]->x,
                                       graph->vertexs[tempEdge->end]->y);   //计算边的权值
        graph->matrix[tempEdge->start][tempEdge->end] = tempEdge->length;
        graph->matrix[tempEdge->end][tempEdge->start] = tempEdge->length;
    }
    return graph;
}

Result *prim() {
    return NULL;
}

int main() {
    /*
     * 1. 判断文件是否存在以及文件中是否有内容
     * 2. 如果没有的话，就向文件中写入数据
     * 3. 如果有的话，就读取文件数据
     * 4. Prim 算法
     * 5. 输出
     */
    Graph *graph;
    if (checkFileValid()) {     //文件存在
        graph = readData();     //从文件中读取数据
    } else {    //文件不存在
        //从控制台输入数据，构造 graph 同时写到文件中
    }
    Result *result = prim();
    if (result == NULL || result->length == 0) {
        printf("没有可用的边");
        exit(-1);
    }
    printf("选择的边共： %d 条：\n", result->length);
    for (int i = 0; i < result->length; i++) {
        printf("%d ---- %d, 长度为：%f \n", result->edges[i]->start,
               result->edges[i]->end,
               result->edges[i]->length);
    }
    return 0;
}

/*
#define INFINITY 1000
#define max_name 50
#define max_vertex_num 50
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MaxVertexNum 100//最大城市数
typedef int Status;
typedef struct Decr {
    int x;
    int y;
} Decr;
typedef char vertex[max_name];
typedef int adjMatrix[max_vertex_num][max_vertex_num];
typedef struct {
    vertex adjvex;//邻接矩阵
    int lowcost;//权值
};
close[max_vertex_num];

typedef struct {
    int n; */
/*图的顶点个数 *//*

    int m; */
/* 图的边个数 *//*

    TownType towns[MAXVEX]; */
/* 顶点信息 *//*

    RoadType roads[MAXVEX][MAXVEX];*/
/*边信息 *//*

} GraphMatrix;
typedef struct {
    int start_town, stop_town; */
/* 边的起点和终点 *//*

    RoadType weight; */
/* 边的权 *//*

    enum {
        EXIST, UNEXIST
    } ex;*/
/*区别已经建好的公路和未修建的公路 *//*

} Edge;
Edge mst[50];

typedef char VertexType//顶点类型用户自定义
typedef int EdgeType, Status;//边上的权值用户自己定义
typedef struct {
    VertexType vexs[MaxVertexNum];//顶点表
    EdgeType edges[MaxVertexNum][MaxVertexNum];//邻接矩阵
    int n, e; //图中当前顶点数和边数
} MGragh;

Status writeFile(Decr &dr, int n) {
    FILE *fp;
    if ((fp = fopen("datd.txt", "wb")) == NULL)//打开输出文件
    {
        printf("cannot open file\n");
        return ERROR;
    }
    for (int i = 0; i < n; i++)
        if (fwrite(dr + i, sizeof(struct Decr), 1, fp) != 1)
            printf("file write error\n");
    fclose(fp);
    return OK;

}

Status readFile(int n) {
    FILE *fp;
    Decr dr[n];
    if ((fp = fopen("data.txt"."rb"))==NULL)//打开输出文件
    {
        printf("cannot open file\n");
        exit(OVERFLOW);
        return ERROR;
    }
    for (int i = 0; i < n; i++) {
        fread(&dr[i], sizeof(struct Decr), 1, fp);
        printf("%d%d\n", dr[i].x, dr[i].y);
    }
    fclose(fp);
    return OK;
}

void dfsMatrix(GraphMatrix GM, int i, int n, int &visited[]) {
    int j;
    printf("%d", i);
    visited[i] = 1;
    for (int j = 0; j < n; j++)
        if (GM[i][j] != 0 && GM[i][j] != MaxValue)&&!visited[j])
    dfsMatrix(GM, j, n);
}

GraphThrough(GraphMatrix
GM){
fro(i = 0;
i<n;
i++)
visited[i]=0;
dfsMatrix(GM,
0,n,visited);
for(
i = 0;
i<n;
i++)
if(visited[i]==1) num++;
if(num==n) return 1;
else return 0;
}

void QSort(Edge mst[50], int low, int hight) {
    if (low < high) {
        pivotloc = Partition(mst[50], low, high);
        QSort(mst[50], low, pivotloc - 1);
        QSort(mst[50], pivotloc + 1;
        high);
    }
}

int easy(GraphMatrix &GM, Edge mst[]) {
    int i, j, num = 0, th, weight;
    for (i = 0; i < GM.m; i++) {
        if (mst[i].ex == UNEXIST) {
            weight = GM.roads[start_town][stop_town];
            GM.roads[start_town][stop_town] = 0
        }
        th = GraphThrough(GM);
        if (th == 1) continue;
        else GM.roads[start_town][stop_town] = weight;
    }

}

void MiniSpanTree_PRIM(MGraph G, VertexType u) {
    k = LocateVex(G, u);
    for (j = 0; j < G.vexnum; ++j)
        if (j != k) closedge[j] = {u，G。arcs[k][j].adj};
    closedge[k].lowcost = 0;
    for (i = 1; i<G.vexnum; ++i) {
        k = minimum(closedge);
        printf(closedge[k].adjvex, Gvexs[k]);
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; ++j)
            if (G.arcs[k][j].adj < closedge[j].lowcost)
                closedge[j] = {G.vexs[k], G.arcs[k][j].adj}
    }

}

int main() {
    */
/*
     * 1. 判断文件是否存在以及文件中是否有内容
     * 2. 如果没有的话，就向文件中写入数ßß据
     * 3. 如果有的话，就读取文件数据
     * 4. Prim 算法
     * 5. 输出
     *//*

    return 0;
}*/
