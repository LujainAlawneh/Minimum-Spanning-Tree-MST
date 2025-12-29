   #include <stdio.h> // lujain alawneh 1230127 sec4
#include <stdlib.h>
#include <string.h>
#include <time.h>
int graphSize =0 ;
int graphOrder =  0 ;
typedef struct node {
    char name[100];
    int cost ;
    int isInserted ;
  struct node * next;
}node;
typedef  node* city ;
typedef struct edge {
    char src[100];
    char dest[100];
    int cost ;
}edge;
  struct minHeap {
int size ;
int maxsize  ;
   edge* *heapArray ;
 }minheap;
typedef struct  minHeap *Heap;
void displayMainMenu( ) ;
void  loadTasks(  FILE *input , node* graph[ ] , int TableSize );
int findCorrectIndex(char* key, int TableSize,node* graph[ ]) ;
void   insertData( char cityName1[]  ,  char cityName2[] ,  int cost  ,  node* graph[ ] , int TableSize) ;
node* creatNode(node*l);
Heap CreateHeap(int maxSize);
void swap(int pos1, int pos2, Heap H);
int parent(int pos) ;
int isLeaf(Heap heap, int pos) ;
int rightChild(int pos) ;
int leftChild(int pos) ;
edge* deleteFromHeap(Heap H) ;
void insertToHeap(edge* destination,Heap H);
int buildMSTUByPrims( node*graph[ ],int tableSize ) ;
int  buildMSTUByKruskal( node*graph[ ],int tableSize ) ;
int isSycle(edge*  menimumTree[ ] ,int mstSize , edge*minNode, node* graph[ ] , int tableSize);
int isConnected(int currentIndex  ,char*target,int mstSize , edge*  menimumTree[ ] ,node* graph[ ] , int tableSize ,int visited[] ) ;
void printGraph ( node* graph[ ] , int graphSize );
int main(void) {
    FILE *input = fopen("cities.txt", "r");
    if (input == NULL) {
        printf("Error opening file\n");
        return 1 ;
    }
    int choice  ,kcost ,pcost;
   node * graph[10000] ;
  int   TableSize = 4000;
    clock_t prims_t ;
    clock_t kruskal_t ;
    double prims_time_taken;
    double kruskal_time_taken;
    for (int i = 0; i < TableSize; i++) { //  initializing each index in the array
        graph[i] = NULL;
    }
    do {
        displayMainMenu( );
        scanf("%d",&choice);
        switch(choice) {

            case 1:
              loadTasks(  input ,  graph ,  TableSize );

                break;
            case 2:
                prims_t =clock();

             pcost =  buildMSTUByPrims(  graph ,  TableSize ) ;
            prims_t=clock() - prims_t;
              prims_time_taken = ((double)prims_t)/CLOCKS_PER_SEC;
            printf("total cost  =%d\n",pcost);
                break;
            case 3:
                kruskal_t =clock();
           kcost  =buildMSTUByKruskal(  graph , TableSize );
            kruskal_t =clock() - kruskal_t;
             kruskal_time_taken = ((double)kruskal_t)/CLOCKS_PER_SEC;
               kcost  =  buildMSTUByKruskal(  graph , TableSize );
            printf("total cost  = %d\n",kcost);
                break;
            case 4:

            printf("result of calculations :\n");
            printf("prims total  cost = %d\n",pcost);
            printf("kruskal total cost = %d\n",kcost );
            printf("----------------") ;
            printf("\n");
            printf("prims time calculation :%lf\n",prims_time_taken);
            printf("kruskal time calculation :%lf\n",kruskal_time_taken) ;
             if (prims_time_taken > kruskal_time_taken) {
                 printf("kruskal time calculation is less than prims\n");
             }
            else if (kruskal_time_taken > prims_time_taken) {
                printf("kruskal time calculation is greater than prims\n");
            }
            else
                printf("prims time calculation is equal to kruskal's  \n");
                break ;

            case 5:
                printf("Thank you for using this System .GoodBye.\n");
            break;
            default :
                printf("\nNo such operation! Please try again.\n");
            break;

        }
    }while(choice != 5 );
    fclose(input);
    return 0;
}

void displayMainMenu( ) {
    printf("\n");
    printf("\nWelcome to  the Task Management System\n");
    printf("please select an operation.....\n");
    printf("1-Load cities:\n");
    printf("2-Apply Prim s Algorithm :\n");
    printf("3-Apply Kruskal s Algorithm:\n");
    printf("4-Compare the two algorithms::\n");
    printf("5-Exit\n");
    printf("please enter your choice \n") ;
    printf("\n");
}
void  loadTasks(  FILE *input ,node* graph[ ] , int TableSize ) {

    char array[100];
    char temp  [100];
    int cost ;
    char cityName1[100];
    char cityName2[100];

    while ( fgets(array,sizeof(array),input) != NULL) {
        char *token = strtok(array,"#");
        strcpy (temp,token);
        strcpy ( cityName1,temp ) ;
        strcpy (temp,strtok(NULL,"#")) ;
        strcpy (  cityName2,temp ) ;
       cost = atoi(strtok(NULL,"#"));

        insertData( cityName1 ,   cityName2  ,    cost  , graph ,   TableSize) ;
        insertData( cityName2     ,  cityName1  ,    cost  , graph,   TableSize) ;


    }
    for (int i = 0 ; i <graphOrder; i++) {
        graph[i ]->isInserted = 0;
    }
     printGraph (   graph  ,   graphSize );
    printf("the size is %d",graphSize/2 ) ;
    printf("the order is %d",graphOrder ) ;
    printf("\ndata loaded successfully !\n");
}
int findCorrectIndex(char* key, int TableSize,node*graph[ ]) {
     for (int i = 0; i < TableSize; i++) {
         if ( graph[i] != NULL && strcmp(graph[i]->name,key) == 0) {
             return i;
         }
     }
    return -1 ;// which means that we can contenue normally cause index is not exist before
}
void   insertData( char cityName1[]  ,  char cityName2[] ,  int cost  ,  node*graph[ ] , int TableSize ) {
    int number = findCorrectIndex(cityName1,   TableSize, graph );
     if (number == -1) { //  that means that the city is not repeated and we will index it normally
number = graphOrder ;
         graph[graphOrder] = malloc(sizeof(node));
        if ( graph[graphOrder] == NULL) {
            printf("There is no  space !\n");
            return ;
        }
        strcpy(  graph[graphOrder]->name,cityName1) ;
         graph[graphOrder]  ->cost = -1  ;
        graph[graphOrder]  -> next = NULL;
        graphOrder++;
        }
                node* p  = creatNode(graph[number] );
    if ( p != NULL ) {
          p->cost = cost  ;
          strcpy(p->name,cityName2) ;
          graphSize++;
    }
            }
node* creatNode(node*l) {
    node*p = ( node * )malloc(sizeof(node));
    if  (p == NULL) {
        printf("out of memory ") ;
    }
    node*temp = l->next  ;
    if (l->next ==NULL) {
        l->next =p;
        p->next =NULL;
        return p;
    }
    while (temp -> next !=NULL) {
        temp = temp->next ;
    }

    temp->next =p;
    p->next =NULL;
    return p;
}
Heap CreateHeap(int maxSize)
{
    Heap H = ( Heap)malloc(sizeof( struct minHeap));
    if(H == NULL)
    {
        printf("Out of memory.\n");
        return NULL;
    }
    H->heapArray = (edge **)malloc(sizeof( edge*)*(maxSize+1));
    if(H->heapArray == NULL)
    {
        printf("Out of memory.\n");
        return NULL;
    }


    H->maxsize = maxSize+1;
    H->size = 0; //  must be initiallized to  zero
    H->heapArray[0]  = (edge*) malloc( sizeof(edge));
    if(H->heapArray[0] == NULL) {
        printf("Out of memory.\n");
        return NULL;
    }
    H->heapArray[0]->cost= -1;
    return H;
}
void insertToHeap(edge* destination,Heap H)
{
    if (H->size >= H->maxsize)
        return;
    int pos = ++H->size;
    H->heapArray[pos] = destination;


    while (pos > 1 && H->heapArray[pos]->cost  < H->heapArray[parent(pos)]->cost)
    {
        swap(pos, parent(pos), H);
        pos = parent(pos);
    }
}

void swap(int pos1, int pos2, Heap H)
{
    edge*temp =  H->heapArray[pos1] ;
    H->heapArray[pos1] = H->heapArray[pos2] ;
    H->heapArray[pos2] = temp;

}
int parent(int pos)
{
    return (pos/2);
}
void minHeapify(int pos, Heap H)
{
    int left = leftChild(pos);
    int right = rightChild(pos);
    int smallest = pos;

    if (left <= H->size && H->heapArray[left]->cost  < H->heapArray[smallest]->cost)
        smallest = left;

    if (right <= H->size && H->heapArray[right]->cost < H->heapArray[smallest]->cost)
        smallest = right;

    if (smallest != pos)
    {
        swap(pos, smallest, H);
        minHeapify(smallest, H);
    }
}
int rightChild(int pos)
{
    return ((pos*2) + 1);
}


int isLeaf(Heap heap, int pos)
{
    return (pos > heap->size / 2 && pos <= heap->size);
}
int leftChild(int pos)
{
    return (pos*2);
}
edge* deleteFromHeap(Heap H){
    if (H->size == 0)
    {
        printf("The Heap is empty!!\n");
        return NULL;
    }

    edge* minNode = H->heapArray[1];
    H->heapArray[1] = H->heapArray[H->size--];
    minHeapify(1, H);

    return minNode;
}

int  buildMSTUByPrims( node*graph[ ],int tableSize ) {
    for (int i = 1; i < graphOrder; i++) { //  to reset the isInserted flag
        if (graph!=NULL) {
            graph[i]->isInserted = 0 ;
        }
    }
    char temp [100 ] ;
    int mstSize =0  ;
    int totalcost = 0 ;
    printf("enter the city name you want to start from   " ) ; //  finding the index from the user
    scanf("%s",temp);
    int index=findCorrectIndex(   temp,  tableSize, graph );

    if (index == -1) {
        printf("couldnt found the city!!\n");
        return 0;
    }


        Heap H = CreateHeap(graphSize ); //  now i want to add the choosen index to the   mst
       edge*  menimumTree[graphOrder-1] ;// # of edges = #vertix-1
        graph[index]->isInserted = 1 ;
        node*p = graph[index]->next ;
        while (p != NULL) {
            edge* ptr =(edge*)malloc(sizeof(edge));
            strcpy(ptr-> src ,graph[index]->name);
            strcpy(ptr->dest,p->name);
            ptr->cost = p->cost;
            insertToHeap(ptr,H) ;
            p=p->next;

        }

        while (H->size > 0 &&mstSize<graphOrder-1) { //  means that the heap is not empty
            edge*  minNode = deleteFromHeap(H) ;
            int n = findCorrectIndex(   minNode ->dest,  tableSize, graph );
           if (n == -1|| graph[n]->isInserted == 1) {
               free(minNode);
               continue ;
           }


            menimumTree[mstSize]= minNode  ;
            mstSize ++;
            totalcost += minNode->cost;
            graph[n] ->isInserted = 1 ;

            city neighbour = graph[n]->next ;// inserting the  nodes of the minimum city  after taking it out and store it in the mst
            while (neighbour != NULL  ) {
                int s = findCorrectIndex( neighbour->name,  tableSize, graph );
                if (  graph[s]->isInserted == 0) {
                    edge* theEdge= (edge*)malloc(sizeof(edge));
                    strcpy(theEdge->src,graph[n]->name);
                    strcpy(theEdge->dest,neighbour->name);
                    theEdge->cost =neighbour->cost;
                    insertToHeap( theEdge,H) ;
                }

                neighbour =neighbour->next;
            }

        }
    printf("\nMST (Prim's) includes these cities:\n");
    for (int i = 0; i < mstSize; i++) {
        printf("- %s---(%d)-----%s\n", menimumTree[i]->src ,menimumTree[i]->cost , menimumTree[i]->dest);
        free(menimumTree[i]); //  fre the edge so  we dont waste memory
    }

    free(H->heapArray[0]);
    free(H->heapArray);
    free(H);
return totalcost;
}
int  buildMSTUByKruskal( node*graph[ ],int tableSize ) {
    int mstSize =0 ;
  int totalcost =0   ;
    Heap H = CreateHeap(graphSize );
    edge*  menimumTree[graphOrder-1] ;

    for (int i = 0; i < graphOrder; i++) {
        city neighbour = graph[i]->next ;

        while (neighbour != NULL  ) {// taking all  the edges fron the graph with the cost and dist
                edge* theEdge= (edge*)malloc(sizeof(edge));
                strcpy(theEdge->src,graph[i]->name);
                strcpy(theEdge->dest,neighbour->name);
                theEdge->cost =neighbour->cost;
                insertToHeap( theEdge,H) ;
            neighbour =neighbour->next;
        }
    }

  while ( mstSize <graphOrder-1&&H->size > 0 ) {
        edge* minNode = deleteFromHeap(H) ;
      if (   isSycle(   menimumTree  ,  mstSize ,  minNode,   graph  ,  tableSize)  ) {
          free(minNode);
          continue  ;
      }


      menimumTree[mstSize]= minNode  ;
      mstSize ++;
      totalcost += minNode->cost ;

    }
    printf("\nMST (Kruskal) includes these cities:\n");
    for (int i = 0; i < mstSize; i++) {
        printf("- %s---(%d)-----%s\n", menimumTree[i]->src ,menimumTree[i]->cost , menimumTree[i]->dest);
        free(menimumTree[i]);
    }

    free(H->heapArray[0]);
    free(H->heapArray);
    free(H);
    return totalcost;
}

int isSycle(edge*  menimumTree[ ] ,int mstSize , edge*minNode, node* graph[ ] , int tableSize) {
    if (mstSize == 0 ) {
        return 0;
    }
    int index =findCorrectIndex(   minNode ->src,  tableSize, graph ); // take index for the src and the name if dist
    char* target =minNode->dest;

    int visited[graphOrder];
    for (int i = 0; i < graphOrder; i++) {
        visited[i] =0;
    }

    if ( isConnected(index , target,  mstSize ,  menimumTree ,  graph  , tableSize  , visited )) {
        return 1;
    }
    return 0;

}
int isConnected(int currentIndex  ,char*target,int mstSize , edge*  menimumTree[ ] ,node* graph[ ] , int tableSize ,int visited[]) {
    visited[currentIndex] = 1 ;
    for (int i = 0; i < mstSize ; i++) {
        char*src = menimumTree [i]->src;
        char*dest = menimumTree [i]->dest;
        int nextIndex = -1;


        if (strcmp(graph[currentIndex]->name,src)==0) {
            if (strcmp(dest,target )==0) {
                return 1;
            }
            nextIndex = findCorrectIndex(dest,tableSize,graph);
        }
        else if (strcmp(graph[currentIndex]->name,dest)==0) {
            if (strcmp(src,target )==0) {
                return 1;
            }
            nextIndex = findCorrectIndex(src,tableSize,graph);
        }
        if (nextIndex !=-1  &&  visited[nextIndex]==0) {
            if (isConnected(  nextIndex,target, mstSize ,   menimumTree,graph ,   tableSize ,  visited )) {
                return 1;
            }
        }


    }
    return 0;
}
void printGraph ( node* graph[ ] , int graphSize ) {
    for (int i = 0; i < graphSize; i++) {
        if (graph[i] != NULL) {
            printf("\n\n%s",graph[i]->name) ;
            node*ptr = graph[i]->next;
            while (ptr != NULL) {
                printf("--%s",ptr->name);
                printf("(%d)",ptr->cost);
                ptr = ptr->next;
            }
            printf("\n");
        }



    }
}