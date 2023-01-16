#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

pnode findNode(pnode *head,int num){
    node *curr = *head;
    while (curr != NULL && curr->node_num != num) 
        curr = curr->next;

return curr;
}

void buildEdges(pnode* head,int numOfVertex){
    
    pnode vertex=findNode(head,numOfVertex);

    int num;
    if(scanf("%d",&num)==1){
    pedge headEdge,prevEdge;
    headEdge=(pedge)malloc(sizeof(edge));
    headEdge->endpoint=findNode(head,num);
    scanf("%d",&num);
    headEdge->weight=num;

    vertex->edges=headEdge;

    prevEdge=headEdge;
    pedge currEdge;
    while(scanf("%d",&num)==1){
        currEdge=(pedge)malloc(sizeof(edge));
        currEdge->endpoint=findNode(head,num);
        scanf("%d",&num);
        currEdge->weight=num;
        prevEdge->next=currEdge;

        prevEdge=currEdge;
    }
    }
}

void insert_node_cmd(pnode *head){
    node *curr = *head;
    while (curr->next != NULL) 
        curr = curr->next;

    int num;
    scanf("%d",&num);
    if(findNode(head,num)!=NULL){
        buildEdges(head,num);
    }
    else{
    pnode vertex;
    vertex=(pnode) malloc(sizeof(node));
    vertex->node_num =num;
    vertex->next =NULL;
    vertex->edges=NULL;
    curr->next =vertex;
    buildEdges(head,num);
    }
}

void print_list(edge* H){
    while(H){
        printf(" %d(%d) -> ", H->endpoint->node_num,H->weight);
        H = H->next;
    }
    printf("|");
}

void printGraph_cmd(pnode head){
    // pnode tmp = head;
    while(head){
        printf("%d (", head -> node_num);
        print_list(head -> edges);
        printf(") -> ");
        head = head->next;
    }
    printf("||\n");
    // free(tmp);
}


void build_graph_cmd(pnode *head){
   
    pnode vertex;
    vertex=(pnode) malloc(sizeof(node));
    vertex->next =NULL;
    vertex->node_num=0;
    vertex->edges=NULL;
   *head=vertex;
    pnode curr =*head;
    int numOfVertex;
    scanf("%d",&numOfVertex);
    for (int i = 1; i < numOfVertex; i++) {
        vertex = (pnode) malloc(sizeof(node));
        if(vertex == NULL)
        {
        printf("Error\n");
          return;  
        }
        vertex->node_num = i;
        vertex->next = NULL;
        vertex->edges = NULL;
        
            curr->next = vertex;
            curr = curr->next;
    
    }
           return;

}


void deleteEdges(pnode node){
    pedge curr = node-> edges;
    while (curr != NULL ) {
        node-> edges = curr->next; 
        free(curr); 
        curr=node-> edges;
    }
}

void deleteOutEdges(edge** head, int data)
{
    // Store head node
    edge *curr = *head, *prev;
    // If head node itself holds the key to be deleted
    if (curr != NULL && curr->endpoint->node_num == data) {
        *head = curr->next; // Changed head
        free(curr); // free old head
        curr=*head;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (curr != NULL) {
        if(curr->endpoint->node_num != data){
        prev = curr;
        curr = curr->next;
        }
    
    // Unlink the node from linked list
    else if(curr->endpoint->node_num == data){
        prev->next = curr->next;
        free(curr); // Free memory
        curr=prev->next;
    }
 
}
}

void delete_node_cmd(node** head, int data)
{   node *curr = *head, *prev;
    pedge* headEdge;
    while (curr != NULL ) {
        headEdge=&curr->edges;
        deleteOutEdges(headEdge,data);
        curr=curr->next;
    }
    // Store head node
    curr = *head;
    // If head node itself holds the key to be deleted
    if (curr != NULL && curr->node_num == data) {
        *head = curr->next; // Changed head
        deleteEdges(curr);
        free(curr); // free old head
        curr=*head;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (curr != NULL) {
        if(curr->node_num != data){
        prev = curr;
        curr = curr->next;
        }
    
    // Unlink the node from linked list
    else if(curr->node_num == data){
        prev->next = curr->next;
        deleteEdges(curr);
        free(curr); // Free memory
        curr=prev->next;
    }
 
}
}

int graphSize(pnode head){
    if (head == NULL)
        return 0;

    pnode curr = head;
    int count=0;
    while (curr != NULL ) {
        curr = curr->next;
        count++;
    }
return count;
}



void deleteGraph_cmd(pnode* head){
    node *curr = *head;
 
    while (curr != NULL ) {
        *head = curr->next; 
        deleteEdges(curr);
        free(curr); 
        curr=*head;
    }
}

typedef struct queueNode_{
    int node_num;
    int dis;
    struct queueNode_ *next; 
}qNode, *pqNode;

pqNode createQNode(int num,int currDis){
    pqNode newNode=(pqNode)malloc(sizeof(qNode));
    newNode -> node_num=num;
    newNode -> dis= currDis;
    newNode -> next = NULL;
    return newNode;
}

void insertQNode(pqNode *headQ1,pqNode newNode){
    if((*headQ1)==NULL)
        *headQ1= newNode;

    if((*headQ1) -> node_num > newNode -> node_num){
        newNode -> next =*headQ1;
        *headQ1= newNode;
    }

    pqNode curr = *headQ1;
    while(curr ->next != NULL){
        if(curr ->next ->node_num > newNode -> node_num){
            newNode -> next = curr ->next;
            curr -> next = newNode;
            return;
        }
    }
    curr->next = newNode;
}

pqNode pollQNode(pqNode *head){
    pqNode curr= *head;
    *head= curr -> next;
    return curr;

}

int isEmpty(pqNode head){
	if( head == NULL);
        return 1;
    return 0;
}

int findIndex(int arr[],int size,int name){
    for(int i=0;i<size;i++){
        if(arr[i]==name)
        return i;
    }
    return -1;
}

int findMax(pnode *head){
    int max=-1;
    pnode curr=*head;
    while(curr!= NULL){
        if(curr->node_num>max)
        max= curr ->node_num;
    }
    return max;
}

int dijkstra(pnode *head,int source,int desitination){
    if (head == NULL)
        return -1;


    // int sizeOfGraph=graphSize(*head);
     //int names[sizeOfGraph];
    // int dist[sizeOfGraph];
    // int visited[sizeOfGraph];
    int max =findMax(head) +1;

    int *dist = (int *)malloc(sizeof(int) * max);
    int *visited = (int *)malloc(sizeof(int) * max);
   // int * names = (int *)malloc(sizeof(int) * max);
    pnode curr= *head;
    // int i=0;
    // while(curr!=NULL){
    //     names[i]=curr -> node_num;
    //     curr=curr ->next;
    //     i++;
    // }

    pqNode *headQ=(pqNode)malloc(sizeof(pqNode));
    pqNode sourceNode;
    for(int i=0;i<max;i++){
        if(i==source){
            dist[i]=0;
            sourceNode= createQNode(i,0);
            insertQNode(headQ,sourceNode);
            visited[i]=1;
        }

        else dist[i]=INT_MAX;    
    } 

    for (int i = 0; i < max; i++){
        visited[i] = 0;
        if (findNode(head, i) == NULL)
            visited[i] = 1;
    }

     
    pedge currEdge;
    //int index;
       

    while(isEmpty(*headQ)==0){
       pqNode now=pollQNode(headQ);
        curr=findNode(head,now->node_num);
        currEdge=curr -> edges;
        while(currEdge!=NULL){
            if(visited[curr->node_num]!=1){
                if(now->dis + currEdge ->weight < dist[curr->node_num]){
                    dist[curr->node_num]=now->dis + currEdge ->weight;
                    insertQNode(headQ,createQNode(currEdge ->endpoint ->node_num,dist[curr->node_num]));
                }
                visited[curr->node_num]=1;
            } 
        }
        
        free(now);
    }

    int disFar =dist[desitination];
    free(*headQ);
    free(dist);
    //free(names);
    free(visited);

    if(disFar==INT_MAX)
        return -1;

    return disFar;
}
int shortest_path(pnode* head, int src, int dest){
    int node_max_size = 0;
    pnode tmp = *head;
    while(tmp){
        if(node_max_size < tmp -> node_num){
            node_max_size = tmp -> node_num;
        }
        tmp = tmp -> next;
    }
    int dist[node_max_size+1];
    int visited [node_max_size+1];
    int i;
    for(i = 0; i < node_max_size+1; i++){
        dist[i] = (INT_MAX);
        visited[i] = -1;
    }
    tmp = *head;
    while (tmp){
        visited[tmp->node_num] = 1;
        tmp=tmp->next;
    }
    dist[src]=0;
    while(1){
        int min_node_id;
        int min_size = INT_MAX;
        tmp=*head;
        while (tmp){
            if (dist[tmp->node_num]<min_size && visited[tmp->node_num]==1){
                min_size = dist[tmp->node_num];
                min_node_id = tmp->node_num;
            }
            tmp = tmp->next;
        }
        if(min_size == INT_MAX){
            break;
        }
        int current_value;
        int new_value;
        tmp = *head;
        while(tmp->node_num!=min_node_id){
            tmp=tmp->next;
        }
        pedge tmp_edge=tmp->edges;
        while(tmp_edge){
            current_value=dist[tmp_edge->endpoint->node_num];
            new_value=dist[min_node_id]+tmp_edge->weight;
            if(new_value<current_value){
                dist[tmp_edge->endpoint->node_num]=new_value;
            }
            tmp_edge=tmp_edge->next;
        }
        visited[min_node_id]=-1;
    }
    if(dist[dest]==INT_MAX || dist[dest]==INT_MIN){
        return -1;
    }
    return dist[dest];
}
int TSP(pnode *head){
    int size = 0;
    scanf("%d", &size);
    int nodes[size];
    int j;
    for (j = 0; j < size; j++) {
        scanf("%d", &nodes[j]);
    }
    int min_dist=INT_MAX;
    pnode tmp = *head;
    // pnode point_to_list = *head;
    int i;
    for(i=0; i<size;i++){
        int current=0;
        int src_id = nodes[i];
        int nodes_temp[size];
        int j;
        for(j=0;j<size;j++){
            nodes_temp[j]=nodes[j];
        }
        nodes_temp[i]=-1;
        while(1){
            int ans;
            int current_dest;
            int min_current=INT_MAX;
            for(j=0;j<size;j++) {
                if (nodes_temp[j] != -1) {
                    tmp = *head;
                    ans = shortest_path(&tmp, src_id,nodes_temp[j]);
                    if(ans<min_current && ans!=-1 && ans>0){
                        min_current=ans;
                        current_dest=j;
                    }
                    if(ans<0 || ans == -1){
                        min_current=INT_MAX;
                        current=INT_MAX;
                        break;
                    }
                }
            }
            if(min_current==INT_MAX){
                break;
            }
            current+=min_current;
            nodes_temp[current_dest]=-1;
            src_id=nodes[current_dest];
        }
        if(current<min_dist){
            min_dist=current;
        }
    }
    if(min_dist==INT_MAX){
        return -1;
    }
    return min_dist;
}
int main(){
    
    char choice;
    int numOfVertex, ver1 ,ver2;
    
    pnode *head=(pnode)malloc(sizeof(pnode));
    while((scanf("%c",&choice)!=EOF)){
        
        if(choice=='A'){
            deleteGraph_cmd(head);
            build_graph_cmd(head);
        }
        if(choice=='n'){
            scanf("%d",&numOfVertex);
            buildEdges(head,numOfVertex);
        }
       if(choice=='B'){
            insert_node_cmd(head);
       }
       if(choice=='D'){
            scanf("%d",&numOfVertex);
            delete_node_cmd(head,numOfVertex);
       }
       if(choice=='S'){
            scanf("%d",&ver1);
            scanf("%d",&ver2);
            int answer =shortest_path(head,ver1,ver2);
            printf("Dijsktra shortest path: %d \n",answer);
       }
       if(choice=='T'){
        int answer =TSP(head);
        printf("TSP shortest path: %d \n",answer);
            }
       
    //    if(choice=='W')
    //    break;
    }
    // printGraph_cmd(*head);
    free(head);
    return 0;
}