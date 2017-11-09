

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 50
#define MAX_CANIDATE_TABLE_SIZE 100

typedef struct node{
    char* word;
    struct node* next;
    struct node* prev;
}node;

typedef struct canidate{
    char fname[MAX_WORD_LEN];
    char lname[MAX_WORD_LEN];
    int writScore;
    int progScore;
    char prefDept[MAX_WORD_LEN];
    int prefOrder;
    float totalScore;
}canidate;


canidate canidate_list[MAX_CANIDATE_TABLE_SIZE];

void insertNode(node** head, node** tail);
node* startsWithLetter(FILE* input, char firstLetter, node** tail);

int check;

int main(int argc,char* argv[]){
    FILE* inputFile=fopen("candidates.txt","r");
    char* deptCheck;
    strcpy(deptCheck,argv[1]);
    strcat(deptCheck,".txt");

    //printf("%s", deptCheck);

    FILE* outputFile= fopen(deptCheck, "w");

    //int arguments=0;
    //for (arguments=1; arguments<argc; arguments++)
      //  printf("%s\n", argv[arguments]);


    //lol bunch of nonsense to check for choosing the department to sort
    /*char deptCheck[MAX_WORD_LEN];
    strcpy(deptCheck,argv[2]);
    char* deptSubString=deptCheck;
    deptSubString++;
    deptSubString[strlen(deptSubString)-4] = 0;
    //printf("%s", deptCheck);
    char actualCheck[MAX_WORD_LEN];
    strcpy(actualCheck,deptSubString);

    */
    //initialize nodes
    node* tail=NULL;
    node* head=NULL;

    //creates first node
    insertNode(&head, &tail);

    char firstC;
    firstC=fgetc(inputFile);

    while(firstC!=EOF){
        //if letter adds entire word to a node then gets then next char
        if(isalpha(firstC)){
            tail=startsWithLetter(inputFile, firstC, &tail);
            insertNode(&head,&tail);
            firstC=fgetc(inputFile);
        }
        //if number adds entire word to a node then gets then next char
        else if(isdigit(firstC)){
            tail=startsWithLetter(inputFile, firstC, &tail);
            insertNode(&head,&tail);
            firstC=fgetc(inputFile);
        }
         //if symbol adds entire word to a node then gets then next char
        else if(ispunct(firstC)){
            //printf("%c",firstC);
            firstC=fgetc(inputFile);
        }
        else{
         //if whitespace, prints it out to keep everything in order
      //      printf("%c",firstC);
            firstC=fgetc(inputFile);
        }
    }

    printf("\n\n");
    int i=0;
    while(head->next!=NULL){
        //printf("%s ",head->word);

        strcpy(canidate_list[i].fname,head->word);
      //  printf("%s ",canidate_list[i].fname);
        head=head->next;

        strcpy(canidate_list[i].lname,head->word);
        //printf("%s ",canidate_list[i].lname);
        head=head->next;

        canidate_list[i].writScore=atoi(head->word);
        //printf("%d ",canidate_list[i].writScore);
        head=head->next;

        canidate_list[i].progScore=atoi(head->word);
        //printf("%d ",canidate_list[i].progScore);
        head=head->next;

        strcpy(canidate_list[i].prefDept,head->word);
        //printf("%s ",canidate_list[i].prefDept);
        head=head->next;

        canidate_list[i].prefOrder=atoi(head->word);
        //printf("%d ",canidate_list[i].prefOrder);
        head=head->next;

        canidate_list[i].totalScore=(canidate_list[i].writScore*0.4)+(canidate_list[i].progScore*0.6);
        //printf("%.1f ",canidate_list[i].totalScore);

        //printf("\n");
        i++;
    }





    //bubble sorts the total scores
    int j,k;
    for(j=0;j<i;j++){
        for(k=0;k<i-j;k++){
            if(canidate_list[k].totalScore<canidate_list[k+1].totalScore){
                canidate temp=canidate_list[k+1];
                canidate_list[k+1]=canidate_list[k];
                canidate_list[k]=temp;
            }
        }
    }


    int count, second;
    for(second=0; second<i; second++){
        for(count=0; count<i;count++){
            if(canidate_list[count].totalScore - canidate_list[count+1].totalScore <= 1){
                if(canidate_list[count].prefOrder > canidate_list[count+1].prefOrder){
                    canidate temp=canidate_list[count];
                    canidate_list[count]=canidate_list[count+1];
                    canidate_list[count+1]=temp;
                }
            }
        }
    }


    printf("\n\n");
    int flag;
    int nameCounter=0;
    for(flag=0;flag<i;flag++){
           // printf("%d ",strcmp(canidate_list[flag].prefDept,argv[2]));
        if(strcmp(canidate_list[flag].prefDept,argv[1])==0){
            //correctly sorted canidates printed to standard output
            fprintf(outputFile,"%s ",canidate_list[flag].fname);
            fprintf(outputFile,"%s ",canidate_list[flag].lname);
            fprintf(outputFile,"\n");
            nameCounter++;
            if(nameCounter==4)
                break;
        }
    }


    fclose(outputFile);
    fclose(inputFile);
    return 0;
}

node* startsWithLetter(FILE* input, char firstLetter, node** tail){
    int nextLetter,len=30;
    char* word=calloc(len+1,sizeof(char));
    int i=1;

    word[0]=firstLetter;
    nextLetter=fgetc(input);

    //while next char is letter or number keeps scanning to make char array
    while(isalpha(nextLetter)||isdigit(nextLetter)){
        if(i>=len){
            len*=2;
            word=realloc(word,len+1);
        }

        word[i]=nextLetter;
        i++;
        nextLetter=fgetc(input);
    }

    if (nextLetter != EOF )
        fseek(input, -1, SEEK_CUR);

    //used to print input without comments
    //printf("%s ",word);
    (*tail)->word=word;

    return *tail;
}


void insertNode(node** head, node** tail){
    if(*head==NULL){
        *head=(node*)malloc(sizeof(node));
        (*head)->next=NULL;
        (*head)->prev=NULL;
        *tail=*head;
    }
    else{

        (*tail)->next=(node*)malloc(sizeof(node));
        (*tail)->prev=*tail;
        *tail=(*tail)->next;
        (*tail)->next=NULL;
    }
}
