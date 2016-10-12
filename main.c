//
//  main.c
//  6010A3
//
//  Created by Yuzhou Li on 10/10/16.
//  Copyright © 2016 Yuzhou Li. All rights reserved.
//

#include <stdio.h>
#include "time.h"
#include "string.h"
#include "stdlib.h"

#define N 10000
#define N0 3

int node[N];
int numberofedge[N];
int totaldeg = 0;
float prob[N];
int graph[N][2];

void initial(int n0){
    for (int i=0;i<n0;i++){
        for (int j=i+1;j<n0;j++){
            node[i] = 1;
            node[j] = 1;
            numberofedge[i]++;
            numberofedge[j]++;
            totaldeg+=2;
            printf("This is a node, node %d, and connected %d\n",i,j);
            graph[i][0] = i;
            graph[i][1] = j;
        }
    }
}

int randompick(){
    for(int k=0;k<N;k++){
        prob[k] = ((float)numberofedge[k]/(float)totaldeg);
        //printf("%f",prob[k]);
    }
    int flag = 0;
    int ii = 0;
    float acc = 0.0;
    float rd = ((float)rand()/(float)(RAND_MAX));
    //printf("%f\n",rd);
    while (flag==0){
        acc += prob[ii];
        ii++;
        if(acc>rd){
            flag = 1;
        }
        
    }
    //printf("ii-1 is %d\n",ii-1);
    return ii-1;
}

void insertnewnode(){
    for(int n = N0;n<N;n++){
        node[n] = 1;
        int selectednode = randompick();
        numberofedge[n]++;
        numberofedge[selectednode]++;
        totaldeg+=2;
        printf("This is a new node, node %d, and connected %d\n",n,selectednode);
        graph[n][0] = n;
        graph[n][1] = selectednode;
    }
}

int findmaxdegree(){
    int max = numberofedge[0];
    for (int ii = 0;ii<N;ii++){
        if(numberofedge[ii]>max){
            max = numberofedge[ii];
        }
    }
    return max;
}

void printarr(int a[], int x){
    for (int i=0;i<x-1;i++){
        printf("%d,",a[i]);
    }
    printf("%d",a[x-1]);
    printf("\n");
}


void histinfo(){
    FILE *fp;
    fp = fopen("DegreeDistribution.csv", "w+");
    //char header[2000] = "Degree,Number of Nodes,Detail\n";
    int max = findmaxdegree();
    for (int i = 1;i<=max;i++){
        int numN = 0;
        for(int j=0;j<N;j++){
            if (numberofedge[j]==i){
                numN++;
            }
        }
        if (numN!=0){
            int detailnumN[numN];
            int count = 0;
            for (int x = 0; x<N;x++){
                if(numberofedge[x]==i){
                    detailnumN[count]=x;
                    count++;
                }
            }
            printf("The degree %d has %d nodes, including ",i,numN);
            printarr(detailnumN, numN);
            fprintf(fp, "%d,%d,",i,numN);
            for(int ss = 0;ss<numN-1;ss++){
                fprintf(fp,"%d,",detailnumN[ss]);
            }
            fprintf(fp, "%d\n",detailnumN[numN-1]);
        }
        
    }
    fclose(fp);
}

void printoutgraph(){
    FILE *file;
    file = fopen("graph.csv", "w+");
    fprintf(file, "%d\n",N);
    for(int i=0;i<N;i++){
        int p1 = graph[i][0];
        int p2 = graph[i][1];
        fprintf(file, "%d,%d\n",p1,p2);
    }
    fclose(file);
}


int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    initial(N0);
    insertnewnode();
    // insert code here...
    //printf("%d,%d,%d\n",numberofedge[0],numberofedge[1],numberofedge[2]);
    /*
    for(int z = 0; z<N;z++){
        printf("The node %d has %d Edges\n",z,numberofedge[z]);
        printf("ij =%d,%d\n ",graph[z][0],graph[z][1]);
    }
    */
    histinfo();
    printoutgraph();
    
    return 0;
}
