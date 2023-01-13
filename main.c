#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <unistd.h>

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
{    node *curr = *head, *prev;
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

int main(){
    char choice;
    int numOfVertex;
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
        //shortsPath_cmd(pnode head);
       }
       if(choice=='T'){
        //TSP_cmd(pnode head);
       } 
       if(choice=='W')
       break;
    }
    printGraph_cmd(*head);
    return 0;
}