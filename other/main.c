#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INFINITY 20

//typedef 别名
//会用到哪些结构体，
//1. 点（x,y,index,bool enable）
//2. 边（start，end，length）
//3. 图（int[n][n]) n -> 点的个数

typedef struct _Vertex { //顶点的数据结构，用 Vertex 代替 struct _vertex
    int x;
    int y;
    int id; //从 0 开始
    int available; //是否可用，1 - 可用，0 - 不可用
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
    Edge *edges[INFINITY * (INFINITY - 1) / 2];
} Result;

const char PATH[] = "data.txt";     //文件的路径

/**
 * 检测文件是否存在
 * @return
 */
int checkFileValid() {
    FILE *fp;
    fp = fopen(PATH, "r");
    if (fp == NULL) return 0;
    else return 1;
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
void readData(Graph *graph) {
    FILE *fp = NULL;
    fp = fopen(PATH, "r");
    int vertexNum;
    fscanf(fp, "%d", &vertexNum);   //从文件中读取点的个数
    graph->vertexNum = vertexNum;
    if (graph->vertexNum == 0)  //如果点的个数为空
        return;
    int id, x, y;
    for (int i = 0; i < graph->vertexNum; i++) {  //读取所有点的坐标
        Vertex *tempVertex = (Vertex *) malloc(sizeof(Vertex *));  //创建一个点的指针并为其分配内存空间
        fscanf(fp, "%d %d %d", &id, &x,
               &y);
        tempVertex->id = id;
        tempVertex->x = x;
        tempVertex->y = y;
        tempVertex->available = 1; //初始化为可用
        graph->vertexs[tempVertex->id] = tempVertex;
    }
    int edgeNum;
    fscanf(fp, "%d", &edgeNum); //从文件中读取边的个数
    graph->edgeNum = edgeNum;
    int start, end;
    double length;
    for (int i = 0; i < graph->edgeNum; i++) {
        Edge *tempEdge = (Edge *) malloc(sizeof(Edge *));   //创建一个边的指针并为其分配内存空间
        fscanf(fp, "%d %d", &start, &end);
        length = getDistance(graph->vertexs[start]->x,
                             graph->vertexs[start]->y,
                             graph->vertexs[end]->x,
                             graph->vertexs[end]->y);   //计算边的权值
        graph->matrix[start][end] = length;
        graph->matrix[end][start] = length;
        graph->vertexs[start]->available = 0;  //设置为不可用
        graph->vertexs[end]->available = 0;    //设置为不可用
    }
    fclose(fp);
    fp = NULL;
}

/**
 * 向文件中写入数据
 * @param graph
 */
void writeData(Graph graph) {
    printf("写文件\n");
    FILE *fp = NULL;
    fp = fopen(PATH, "w+");
    if (fp == NULL) {
        printf("文件打开失败。\n");
        return;
    }
    fprintf(fp, "%d\n", graph.vertexNum);  //把点的个数写入文件中
    for (int i = 0; i < graph.vertexNum; i++) {  //把点的信息依次写入文件中
        fprintf(fp, "%d %d %d\n", graph.vertexs[i]->id, graph.vertexs[i]->x,
                graph.vertexs[i]->y);
    }
    fprintf(fp, "%d\n", graph.edgeNum); //向文件中写入边的个数
    for (int i = 0; i < graph.vertexNum - 1; i++) {  //向文件中写入各条边的信息
        for (int j = i + 1; j < graph.vertexNum; j++) {
            if (graph.matrix[i][j] != 0) { //i 与 j 连通
                fprintf(fp, "%d %d\n", i, j);     //将边的两个顶点写入文件中
            }
        }
    }
    fclose(fp);
    fp = NULL;
}

/**
 * 从控制台输入图的相关信息
 * @return
 */
void readFromConsole(Graph *graph) {
    printf("请输入点的个数: ");
    int vertexNum;
    scanf("%d", &vertexNum);
    if (vertexNum <= 0) {
        return;
    }
    graph->vertexNum = vertexNum;
    printf("输入点的信息：\n");
    int x, y;
    Vertex *tempVertex;
    for (int i = 0; i < graph->vertexNum; i++) {  //读取所有点的坐标
        tempVertex = (Vertex *) malloc(sizeof(Vertex *));  //创建一个点的指针并为其分配内存空间
        scanf("%d %d", &x, &y);
        tempVertex->id = i;     //id 递增
        tempVertex->x = x;
        tempVertex->y = y;
        tempVertex->available = 1; //初始化为可用
        graph->vertexs[tempVertex->id] = tempVertex;
    }
    printf("输入边的个数：\n");
    int edgeNum;
    scanf("%d", &edgeNum); //读取边的个数
    graph->edgeNum = edgeNum;
    int start, end;
    double length;
    printf("输入边的信息：\n");
    for (int i = 0; i < graph->edgeNum; i++) {
        scanf("%d %d", &start, &end);
        length = getDistance(graph->vertexs[start]->x,
                             graph->vertexs[start]->y,
                             graph->vertexs[end]->x,
                             graph->vertexs[end]->y);   //计算边的权值
        graph->matrix[start][end] = length;
        graph->matrix[end][start] = length;
        graph->vertexs[start]->available = 0;  //设置为不可用
        graph->vertexs[end]->available = 0;    //设置为不可用
    }
}

/**
 * 当边的两个点都不可用的时候，就代表该边无法使用
 * 获取所有可用的边
 * 进行排序
 * @return 数组
 */
void getAvailableEdges(Graph graph, Result *result) {
    for (int i = 0; i < graph.vertexNum - 1; i++) {  //向文件中写入各条边的信息
        for (int j = i + 1; j < graph.vertexNum; j++) {
            if (graph.vertexs[i]->available != 0 ||
                graph.vertexs[j]->available != 0) {     //这条边可用
                Edge *tempEdge = (Edge *) malloc(sizeof(Edge *));
                tempEdge->start = i;
                tempEdge->end = j;
                tempEdge->length = getDistance(graph.vertexs[i]->x,
                                               graph.vertexs[i]->y,
                                               graph.vertexs[j]->x,
                                               graph.vertexs[j]->y);   //计算边的权值
                if (result->length == 0) {  //没有边的时候
                    result->edges[0] = tempEdge;
                    result->length = 1;
                } else {
                    //向数组里插入该边
                    int m;
                    for (m = 0; m < result->length; m++) {
                        if (tempEdge->length < result->edges[m]->length) {  //新边的权值小于当前边的权值
                            for (int n = result->length; n > m; n--) {    //后面的元素向后移
                                result->edges[n] = result->edges[n - 1];
                            }
                            result->edges[m] = tempEdge;
                            result->length++;
                            break;
                        }
                    }
                    if (m == result->length) {
                        result->edges[result->length] = tempEdge;    //放在最后一位
                        result->length++;
                    }
                }
            }
        }
    }
}

/**
 * @param graph
 * @param result
 */
void kruskal(Graph graph, Result *result) {
    /*
    for (int i = 0; i < availableEdges.length; ++i) {
        printf("start: %d end: %d length: %f\n",
               availableEdges.edges[i]->start,
               availableEdges.edges[i]->end,
               availableEdges.edges[i]->length);
    }*/
    //点的数目 - 1 - 边的数目
    for (int i = 0;i < graph.vertexNum - 1 - graph.edgeNum;i++) {
        Result availableEdges;
        availableEdges.length = 0;
        getAvailableEdges(graph, &availableEdges);  //获取可用的边，选取最小的一个
        result->length = i + 1;
        Edge* tempEdge = availableEdges.edges[0];
        result->edges[i] = tempEdge;
        graph.vertexs[tempEdge->start]->available = 0; //设置该节点为不可用
        graph.vertexs[tempEdge->end]->available = 0; //设置该节点为不可用=
    }
}

Graph createGraph() {
    Graph graph;
    graph.vertexNum = 0;
    graph.edgeNum = 0;
    for (int i = 0; i < INFINITY; i++) {
        for (int j = 0; j < INFINITY; j++) {
            graph.matrix[i][j] = 0;
        }
    }
    return graph;
}

/**
 * 释放内存
 * @param graph
 */
void freeGraph(Graph *graph) {
    if (graph == NULL)
        return;
    for (int i = 0; i < graph->vertexNum; i++) {  //读取所有点的坐标
        free(graph->vertexs[i]);
    }
}

int main() {
    /*
     * 1. 判断文件是否存在以及文件中是否有内容
     * 2. 如果没有的话，就向文件中写入数据
     * 3. 如果有的话，就读取文件数据
     * 4. Prim 算法
     * 5. 输出
     */
    printf("开始\n");
    Graph graph = createGraph();
    if (checkFileValid() == 1) {     //文件存在
        printf("文件存在\n");
        readData(&graph);     //从文件中读取数据
    } else {    //文件不存在
        //从控制台输入数据，构造 graph 同时写到文件中
        printf("文件不存在\n");
        readFromConsole(&graph);
        printf("点的个数：%d\n", graph.vertexNum);
        printf("边的个数：%d\n", graph.edgeNum);
        writeData(graph);
    }
    printf("-------\n");
    printf("点的个数：%d\n", graph.vertexNum);
    printf("边的个数：%d\n", graph.edgeNum);
    Result result;
    result.length = 0;
    kruskal(graph, &result);
    if (result.length == 0) {
        printf("没有可用的边\n");
    } else {
        printf("选择的边共： %d 条：\n", result.length);
        double total = 0;
        for (int i = 0; i < result.length; i++) {
            total += result.edges[i]->length;
            printf("%d -- %d, 长度为：%f \n", result.edges[i]->start,
                   result.edges[i]->end,
                   result.edges[i]->length);
        }
        printf("总长度为：%.3f\n",total);
    }
    freeGraph(&graph);
    printf("-------\n");
    printf("结束\n");
    return 0;
}
