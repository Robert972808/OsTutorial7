#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct{
	char name[256];
	int priority,pid,runtime;
}proc;
typedef struct node{
    proc process;
    struct node* next;
}node_t;
node_t * head = NULL;
node_t * tail = NULL;
node_t * new_node;

void push(proc process) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->process = process;
    new_node->next = NULL;
    if(head == NULL && tail == NULL){
	head = tail = new_node;
	return;
    }
    tail->next = new_node;
    tail = new_node;
}
void pop() {
	node_t * new_node = head;
	if(head == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	printf("%s, %d, %d, %d\n", new_node->process.name,new_node->process.priority,new_node->process.pid,new_node->process.runtime);
	if(head == tail) {
		head = tail = NULL;
	}
	else {
		head = head->next;
	}
	free(new_node);
}

void delete_name(char* name)
{
	node_t * new_node = head;
	node_t * temp_node = NULL;
	int i = 0;

    	for (i = 0; i < 9; i++) {
        	if (new_node->next != NULL && strcmp(new_node->next->process.name, name) !=0) {
            		new_node = new_node->next;
        	}
    	}

   	temp_node = new_node->next;
    	new_node->next = temp_node->next;
    	free(temp_node);
}
void delete_pid(int pid)
{
	node_t * new_node = head;
	node_t * temp_node = NULL;
	int i = 0;

    	for (i = 0; i < 9; i++) {
        	if (new_node->next != NULL && pid != new_node->next->process.pid) {
            		new_node = new_node->next;
        	}
    	}

   	temp_node = new_node->next;
    	new_node->next = temp_node->next;
    	free(temp_node);
}
void print_list() {
    node_t * current = head;

    while (current != NULL) {
        printf("%s, %d, %d, %d\n", current->process.name,current->process.priority,current->process.pid,current->process.runtime);
        current = current->next;
    }
}


int main(void)
{
	char buffer[1024];
	FILE *fp;
	fp = fopen("processes.txt", "r");
	const char s[2] = ", ";
	char *token;
	int i;
	char* data;
	proc process;
	if(fp != NULL)
	{
		while(fgets(buffer, sizeof buffer, fp) != NULL)
		{
		    data = strdup(buffer);
		    token = strtok(data, s);
		    for(i=0;i<4;i++)
		    {
			if(i==0)
			{   
			    strcpy(process.name,token);
			    token = strtok(NULL,s);
			} else if (i==1){
			    process.priority = atoi(token);
			    token = strtok(NULL,s);
			}else if (i==2){
			    process.pid = atoi(token);
			    token = strtok(NULL,s);
			}else if (i==3){
			    process.runtime = atoi(token);
			    token = strtok(NULL,s);
			}                     
		    }
		    push(process);
		}
		fclose(fp);
	} else {
	perror("processes.txt");
	}   
	delete_name("emacs");
	delete_pid(12235);
	for(i=0;i<8;i++)
	{
		pop();
	}
}   







