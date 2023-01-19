#include<stdio.h>
#include<stdlib.h>
#include"node.h"
#include"edge.h"
#include<limits.h>


typedef struct graph {
    int NumberOfNodes;
    node *Head;
} graph;

graph *graphAlloc() {

    graph *pg = (graph *) malloc(sizeof(graph));
    pg->NumberOfNodes = 0;
    pg->Head = NULL;

    return pg;
}

int insertNode(graph *pg, int id) {                       
    if (pg->Head == NULL) {
        pg->Head = nodeAllloc(id, NULL);
        return 1;
    }
    else{
    node* tempNodeP=pg->Head;
    int flag=0;
    while (flag==0&&tempNodeP!= NULL) {      
        if(tempNodeP->id==id)
            flag=1;
        tempNodeP = tempNodeP->nextNode;
    }
    if(flag==0) {
            node *tempNode = pg->Head;
            while (tempNode->nextNode != NULL) {
                tempNode = tempNode->nextNode;
            }
            tempNode->nextNode = nodeAllloc(id, NULL);
        return 1;
        }
    }
    return 0;
}

int insertEdge(graph *pg, int srcId, int destId, int w) {

    int flag = 0;
    node *tempNodeP = pg->Head;
    for (int i = 0;tempNodeP!=NULL && i < pg->NumberOfNodes; ++i) {
        if (tempNodeP->id == destId) {
            flag = 1;
        }
        tempNodeP = tempNodeP->nextNode;
    }
    if (flag==0&&insertNode(pg, destId)) {
        pg->NumberOfNodes+=1;
    }

    node *tempNode = pg->Head;
    while (tempNode->id != srcId) {
        tempNode = tempNode->nextNode;
    }
    tempNode->nextEdge = edgeAlloc(destId, w, tempNode->nextEdge);

    return 0;
}

void removeEdge(node *pn, int destId) {
    edge *tempEdgeP = pn->nextEdge;
    edge *prevEdgeP = NULL;

    while (tempEdgeP != NULL && destId != tempEdgeP->id) {    
        prevEdgeP = tempEdgeP;
        tempEdgeP = tempEdgeP->next;
    }
    if (tempEdgeP == NULL) {   
    } else if (prevEdgeP == NULL) {
        tempEdgeP = NULL;
    } else prevEdgeP->next = tempEdgeP->next;
    free(tempEdgeP);
}

int getTheDestNodeIndex(node arr[], int dest, int numberOfNodes) {
    for (int i = 0; i < numberOfNodes; ++i) {
        if (arr[i].id == dest)                       
            return i;
    }
    return -1;
}

void AFunction(graph *pg) {
    char nChar;
    int saveSrc;
    int saveDest;
    int saveW;
    int counter = 0;
    int nodeSize;

    scanf("%d", &nodeSize);      
    while (counter < nodeSize) {
        scanf("%c", &nChar);                 
        scanf("%c", &nChar);
        counter++;
        scanf("%d", &saveSrc);               
        if(insertNode(pg, saveSrc))       
            pg->NumberOfNodes+=1;

        while (scanf("%d", &saveDest)) {       
            scanf("%d", &saveW);             
            insertEdge(pg, saveSrc, saveDest, saveW);  

        }
    }
}

void BFunction(graph *pg) {
    int dest;
    int w;
    int srcId;
    edge* tempToDelete;
    scanf("%d", &srcId);

    node *tempNode = pg->Head;
    node* pre=NULL; 
    while (tempNode != NULL && tempNode->id != srcId) {
        pre=tempNode;
        tempNode = tempNode->nextNode;
    }
    if(tempNode == NULL)                                
        tempToDelete=NULL;
    else 
        tempToDelete=tempNode->nextEdge;

    if (tempNode == NULL) {                              
        pre->nextNode = nodeAllloc(srcId, NULL);
        tempNode=pre->nextNode;
        (pg->NumberOfNodes)++;
    }

    

    edge *tempEdgeP = NULL;
    if (scanf("%d", &dest)) {

        scanf("%d", &w);
        tempEdgeP = edgeAlloc(dest, w, NULL);            
        tempNode->nextEdge = tempEdgeP;
        if(insertNode(pg,dest))
            pg->NumberOfNodes+=1;

        while (scanf("%d", &dest)) {
            scanf("%d", &w);
            tempEdgeP->next = edgeAlloc(dest, w, NULL);
            tempEdgeP = tempEdgeP->next;
            if(insertNode(pg,dest))
                pg->NumberOfNodes+=1;
        }
    }
    while(tempToDelete!=NULL){
        edge* prevtemp=tempToDelete;
        tempToDelete=tempToDelete->next;
        free(prevtemp);
    }


}

void DFunction(graph *pg) {
    int flag=1;
    int srcId;
    scanf("%d", &srcId);
    node *tempNodeP = pg->Head;
    node *prevNodeP = NULL;

    while (tempNodeP != NULL) {

        if (srcId == tempNodeP->id) {                  
            pg->NumberOfNodes -= 1;
            if (tempNodeP == NULL && prevNodeP == NULL) {
            } 
            else if (prevNodeP == NULL) {
                pg->Head=pg->Head->nextNode;
                free(tempNodeP);
                edge* tempEdge2=tempNodeP->nextEdge;
            while (tempEdge2!=NULL)
            {   edge* prevEdge2=tempEdge2;
                tempEdge2=tempEdge2->next;
                free(prevEdge2);
            }
                return;
            } 
            else prevNodeP->nextNode = tempNodeP->nextNode;
            edge* tempEdge=tempNodeP->nextEdge;
            while (tempEdge!=NULL)
            {   edge* prevEdge=tempEdge;
                tempEdge=tempEdge->next;
                free(prevEdge);
            }
            prevNodeP = tempNodeP;                        
            tempNodeP = tempNodeP->nextNode;
            free(prevNodeP);
            flag=0;
        }
        else {
            removeEdge(tempNodeP, srcId);            
            return;
        }
       if(flag==1){
        prevNodeP = tempNodeP;                        
        tempNodeP = tempNodeP->nextNode;
       }
       else flag=1;
    }
}


int SFunction(graph *pg, int src, int dest) {
    int srcId = src;
    int destId = dest;
    int dist;
    int counter = 0;
    int NumNodes = pg->NumberOfNodes;
    int check=0;             
    node *tempNodeP = pg->Head;
    if(tempNodeP==NULL){
     return -1;}

    node *arrNodes = (node*)malloc(sizeof(node) * (NumNodes));

    for (int i = 0; i < NumNodes&&tempNodeP!=NULL; ++i) {     
        arrNodes[i] = *tempNodeP;
        tempNodeP = tempNodeP->nextNode;

        if (dest==arrNodes[i].id)
            check++;
        
        if (srcId == arrNodes[i].id) {            
            node temp = arrNodes[i];
            arrNodes[i] = arrNodes[0];
            arrNodes[0] = temp;
            arrNodes[0].length = 0;
            check++;
        }
    }
    if(check!=2){
    free(arrNodes);
    return -1 ;
    }
    while (counter != NumNodes) {         

        int index;
        edge *tempEdgeP = arrNodes[counter].nextEdge;  
        counter++;                      

        while (tempEdgeP != NULL) {         

            if(arrNodes[counter-1].length==INT_MAX)
                dist=INT_MAX;
            else
                dist = arrNodes[counter - 1].length + tempEdgeP->w;
            index = getTheDestNodeIndex(arrNodes, tempEdgeP->id, NumNodes);

            if (index != -1 && arrNodes[index].length > dist) {                     
                arrNodes[index].length = dist;
                arrNodes[index].prev = &arrNodes[counter - 1];
            }
            if (index != -1 && arrNodes[index].length <
                               arrNodes[counter-1].length) {   
                node tempNodeP = arrNodes[index];
                arrNodes[index] = arrNodes[counter-1];
                arrNodes[counter-1] = tempNodeP;
            }
            tempEdgeP = tempEdgeP->next;
        }
    }
    int save=-1;
    int index = getTheDestNodeIndex(arrNodes, destId, NumNodes);
    if (arrNodes[index].length == INT_MAX)
        arrNodes[index].length = -1;
    save=arrNodes[index].length;
    free(arrNodes);
    return save;

}

void Tfunction(graph *pg) {

   int shortestLength = INT_MAX;
   int size;
   int temp;
   int tempLength=0;

   scanf("%d", &size);                        
   int *arr = (int *) malloc(sizeof(int) * size);
   for (int i = 0; i < size; ++i) {
       scanf("%d", &arr[i]);
   }
   for (int j = 1; j <= size; j++) {
       tempLength=0;
        for (int i = 0; i < size-1; i++) {
            temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    for(int k=0;k<size-1&&tempLength!=INT_MAX;k++){

        int saveL=SFunction(pg,arr[k],arr[k+1]);
        if(saveL==-1)
            tempLength=INT_MAX;
        else    
            tempLength+=saveL ;
    }
    if(tempLength<shortestLength)
        shortestLength=tempLength;
    }
    if(shortestLength==INT_MAX)
        shortestLength=-1;
    printf("TSP shortest path: %d \n",shortestLength);
    free(arr);
}

void freeA(graph *pg){

    node* tempnode=pg->Head;
    edge* tempedge;
    while(tempnode!=NULL){
        node* prevNode=tempnode;
        tempedge=tempnode->nextEdge;
        while(tempedge!=NULL){
            edge* prevEdge=tempedge;
            tempedge=tempedge->next;
            free(prevEdge);
        }
        tempnode=tempnode->nextNode;
        free(prevNode);
    }
    free(pg);
}


int main() {
    graph *pg = NULL;
    int srcId;
    int destId;
    char c;
                          
    
    while (scanf("%c", &c)!= EOF){
        
        switch (c) {

            case 'A':
                if(pg!=NULL)
                    freeA(pg);
                pg = graphAlloc();
                AFunction(pg);
                break;

            case 'B':
                BFunction(pg);
                break;

            case 'D':
                DFunction(pg);
                break;

            case 'S':
                scanf("%d", &srcId);
                scanf("%d", &destId);
                int s=SFunction(pg, srcId, destId);
                printf("Dijsktra shortest path: %d \n",s);

                break;

            case 'T':
                Tfunction(pg);
        }

    } 

    freeA(pg);
    return 0;

}