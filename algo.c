#include <stdio.h>>
#include <stdlib.h>>
#include "graph.h"
#include <unistd.h>

typedef struct queueNode_{
    int node_num;
    int dis;
    struct queueNode_ *next; 
}qNode, *pqNode;

void createQNode(int num,int currDis){
    pqNode newNode=(pqNode)malloc(sizeof(qNode));
    newNode -> node_num=num;
    newNode -> dis= currDis;
    newNode -> next = NULL;
}

void insertQNode(*pqNode head,pqNode newNode){
    if(*head -> node_num > newNode -> node_num){
        newNode -> next =*head;
        *head= newNode;
    }

    pqNode curr = *head;
    while(curr ->next != NULL){
        if(curr ->next ->node_num > newNode -> node_num){
            newNode -> next = curr ->next;
            curr -> next = newNode;
            return;
        }
    }
    curr_>next = newNode;
}

pqNode pollQNode(*pqNode head){
    pqNode curr= *head;
    *head= curr -> next;
    return curr;

}

int isEmpty(*pqNode head){
	return (*head) == NULL;
}