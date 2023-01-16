#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>

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




void deleteGraph_cmd(pnode* head){
    node *curr = *head;
 
    while (curr != NULL ) {
        *head = curr->next; 
        deleteEdges(curr);
        free(curr); 
        curr=*head;
    }
}

int findMax(pnode *head){
    int max=-1;
    pnode curr=*head;
    while(curr!= NULL){
        if(curr->node_num>max)
        max= curr ->node_num;
        curr=curr ->next;
    }
    return max;
}


int shortest_path(pnode* head, int src, int dest){
    int max = findMax(head);
    
    int dist[max+1];
    int visited [max+1];
    int i;
    for(i = 0; i < max+1; i++){
        dist[i] = (INT_MAX);
        visited[i] = -1;
    }

    pnode tmp = *head;

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
        while(tmp->node_num != min_node_id){
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

// int TSP(pnode *head){
//     int size = 0;
//     scanf("%d", &size);
//     int nodes[size];
//     int j;
//     for (j = 0; j < size; j++) {
//         scanf("%d", &nodes[j]);
//     }
//     int min_dist=INT_MAX;
//     pnode tmp = *head;
//     // pnode point_to_list = *head;
//     int i;
//     for(i=0; i<size;i++){
//         int current=0;
//         int src_id = nodes[i];
//         int nodes_temp[size];
//         int j;
//         for(j=0;j<size;j++){
//             nodes_temp[j]=nodes[j];
//         }
//         nodes_temp[i]=-1;
//         while(1){
//             int ans;
//             int current_dest;
//             int min_current=INT_MAX;
//             for(j=0;j<size;j++) {
//                 if (nodes_temp[j] != -1) {
//                     tmp = *head;
//                     ans = shortest_path(&tmp, src_id,nodes_temp[j]);
//                     if(ans<min_current && ans!=-1 && ans>0){
//                         min_current=ans;
//                         current_dest=j;
//                     }
//                     if(ans<0 || ans == -1){
//                         min_current=INT_MAX;
//                         current=INT_MAX;
//                         break;
//                     }
//                 }
//             }
//             if(min_current==INT_MAX){
//                 break;
//             }
//             current+=min_current;
//             nodes_temp[current_dest]=-1;
//             src_id=nodes[current_dest];
//         }
//         if(current<min_dist){
//             min_dist=current;
//         }
//     }
//     if(min_dist==INT_MAX){
//         return -1;
//     }
//     return min_dist;
// }
// void TSP_helper_cmd(pnode head, int *arr,int num, int curr,int *pmin)
// {
//     if(num==2)
//     {
//         int finshdist = shortest_path(head,arr[0],arr[1]);
//         if(finshdist!=INT_MAX)
//         {
//             if((curr + finshdist)<*pmin)
//             {
//                 *pmin = (curr+finshdist);
//             }
//         }
//         return;
//     }
//     for(int i=1;i<num;i++)
//     {
//         swap_place(arr,1,i);
//         int dist = shortest_path(head,arr[0],arr[1]);
//         if(dist==INT_MAX)
//         {
//             return;
//         }
//         TSP_helper_cmd(head,arr+1,num-1,curr+dist,pmin);
//         swap_place(arr,i,1);
//     }
// }

// void swap_place(int *arr, int num1, int num2)
// {
//     int temp = arr[num1];
//     arr[num1]=arr[num2];
//     arr[num2]=temp;
// }
// int TSP_cmd(pnode head)
// {
//     int num;
//     scanf("%d", &num);
//     int arr = (int)(malloc(sizeof(int)*num));
//     int min = INT_MAX;
//     int * pmin=&min;
//     for(int i =0 ; i<num; i++)
//     {
//         scanf("%d", &arr[i]);
//     }
//     for(int i=0;i<num;i++)
//     {
//         swap_place(arr,0,i);
//         TSP_helper_cmd(head,arr,num,0,pmin);
//         swap_place(arr,i,0);
//     }
//     free(arr);
//     return *pmin;
// }
int min(int num1, int num2) {
    return (num1 >= num2) ? num2 : num1;
}
void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}


void reverse(int *permutation, int start_index, int size) {
    int i = start_index;
    int j = size - 1;
    while (i < j) {
        swap(&permutation[i], &permutation[j]);
        i++;
        j--;
    }
}


int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

bool next_permutation(int *permutation, int size) {
    int i = size - 2;
    while (i >= 0 && permutation[i] >= permutation[i + 1]) {
        i--;
    }
    if (i == -1) {
        return false;
    }
    int j = size - 1;
    while (permutation[j] <= permutation[i]) {
        j--;
    }
    swap(&permutation[i], &permutation[j]);
    reverse(permutation, i + 1, size);
    return true;
}
void TSP_cmd(pnode head) {
    int size, dijskAns;
    scanf("%d", &size);
//    int *permutation=(int*) malloc(sizeof(int)*size);
    int permutation[size];
    for (int i = 0; i < size; i++) {
        scanf("%d", &permutation[i]);
    }
    qsort(permutation, size, sizeof(int), compare);
    int min_path = INT_MAX;

    do {
        int current_path_weight = 0;
        for (int i = 0; i < size-1; i++) {
            dijskAns = shortest_path(&head, permutation[i], permutation[i + 1]);
            if (dijskAns == INT_MAX) {
                current_path_weight = INT_MAX;
                break;
            }
            current_path_weight += dijskAns;

        }
        min_path = min(min_path, current_path_weight);

    } while (next_permutation(permutation, size));

    if (min_path != INT_MAX) {
        printf("TSP shortest path: %d \n", min_path);
    } else printf("TSP shortest path: -1 \n");
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
       if(choice == 'T')
        {
            // int ans = TSP_cmd(head);
            // if(ans ==INT_MAX)
            // {
            //     printf("TSP shortest path: -1 \n");
            // }
            // else
            // {
            //     printf("TSP shortest path: %d \n",ans);
            // }
            TSP_cmd(*head);
        }
       
    //    if(choice=='W')
    //    break;
    }
    // printGraph_cmd(*head);
    free(head);
    return 0;
}