#include <stdio.h>
#include <stdlib.h>
#include <string.h>



FILE *input, *output;

struct node
{
	char* name;
	char* question;
	struct node* yes_ptr;
	struct node* no_ptr;
};
struct node hardCodedNodes[] = 
{
	{NULL, "Does it have a tail?", hardCodedNodes+1, hardCodedNodes+2}
 ,{NULL, "Does it chase mice?", hardCodedNodes+3, hardCodedNodes+4}
 ,{NULL, "Is it flat, round and edible?", hardCodedNodes+5, hardCodedNodes+6}
 ,{"a bird", NULL, NULL, NULL}
 ,{"a pangolin", NULL, NULL, NULL}
 ,{NULL, "Can you dip it in your tea?", hardCodedNodes+7, hardCodedNodes+8}
 ,{"Pete", NULL, NULL, NULL}
 ,{"a biscuit", NULL, NULL, NULL}
 ,{"a pizza", NULL, NULL, NULL}	
};

/*void nodePrint(struct node* currentNode)
{
	if(currentNode != NULL)
	{
		if(currentNode-> name != NULL)
			printf("Name of object: %s\n", currentNode->name );
		else
			printf("Name of object: [NOTHING]\n");

		if(currentNode -> question != NULL)
			printf("Question: %s\n", currentNode->question );
		else
			printf("Question: [NOTHING]\n");

		if(currentNode->yes_ptr)
			printf("Yes: %s\n", (currentNode->yes_ptr)->name );
		if(currentNode->no_ptr)
			printf("No: %s\n", (currentNode->no_ptr)->name);

		printf("\n");
	}
}*/

void treePrint(struct node* currentNode)
{
	if(currentNode)
	{
		if(currentNode->question)
		{
			fprintf(output, "Question: %s\n", currentNode->question);
			treePrint(currentNode->yes_ptr);
			treePrint(currentNode->no_ptr);
		}
		
		else
			fprintf(output, "Object: %s\n", currentNode->name);
	}
}

struct node* treeRead()
{
	char *str = (char*)malloc(100*sizeof(char));
	fgets(str, 100, input);

	int i = strlen(str) - 1;
	if (i > 0 && str[i] == '\n')
		str[i] = '\0';
	
	if(!str || strcmp(str, "") == 0)
		return NULL;
	else
	{
		struct node* ptr = (struct node*)malloc(sizeof(struct node));
		if(strstr(str, "Question:"))
		{
			ptr->question = (char*)malloc(100*sizeof(char));
			strcpy(ptr->question, str +10);
			ptr->yes_ptr = treeRead();
			ptr->no_ptr = treeRead();
		}
		else
		{
			ptr->name = (char*)malloc(100*sizeof(char));
			strcpy(ptr->name, str+8);
			ptr->yes_ptr = ptr->no_ptr = NULL;
		}
		free(str);
		return ptr;
	}
} 

void freeWholeTree(struct node* start) {
	if (start->yes_ptr)
		freeWholeTree(start->yes_ptr);
	if(start->no_ptr)
		freeWholeTree(start->no_ptr);
	if(start->question)
		free(start->question);
	if(start->name)
		free(start->name);
	free(start);
}

char* getInput()
{
	char* string = (char*)malloc(100*sizeof(char));
	fgets(string, 100, stdin);

	int i = strlen(string) - 1;
	if (i > 0 && string[i] == '\n')
		string[i] = '\0';
	return string;
}

int verifyAnswer(char* ans)
{
	if((strcmp(ans, "yes") == 0) || (strcmp(ans,"yeah") == 0) || (strcmp(ans,"ye")==0)|| (strcmp(ans,"y")==0))
		return 1;
	if((strcmp(ans, "no")==0)|| (strcmp(ans, "neah") == 0) || (strcmp(ans, "ne")== 0))
		return 0;
	return -1;
}	

int main(int argc, char **argv)
{
	//struct node *currentNode = hardCodedNodes;
	struct node *root = NULL;
	if(argc == 3)
	{
		if(strcmp(argv[1], "readfile") == 0)
			input = fopen(argv[2], "r");
		if(strcmp(argv[1], "writefile") == 0)
			output = fopen(argv[2], "w");
	}
	else if(argc == 4)
	{
		if(strcmp(argv[1], "rwfile") == 0)
		{
			input = fopen(argv[2], "r");
			output = fopen(argv[3], "w");
		}
	}
	if(input)
	{
		root = treeRead();
		fclose(input);
	}

	if (root == NULL)
	{
		root = (struct node*)malloc(sizeof(struct node));
		root->name = (char*)malloc(100*sizeof(char));
		strcpy(root->name, "a pangolin");
	}

	char *ans = NULL;
	struct node* currentNode = root;
	int finish = 0;
	while(finish == 0)
	{
		if(currentNode->name != NULL)
		{
			printf("Is the answer %s ?\n", currentNode->name);
			ans = getInput();
			if (verifyAnswer(ans))
			{
				free(ans);
				printf("I made the right guess!\n");
				printf("Do you want to play again?\n");
				ans = getInput();
				if(verifyAnswer(ans) == 0)
					finish = 1;
				else
					currentNode = root;
				free(ans);
			}
			else
			{
				free(ans);
				currentNode->yes_ptr = (struct node*)malloc(sizeof(struct node));
				currentNode->no_ptr = (struct node*)malloc(sizeof(struct node));
				char* aux = currentNode->name;
				currentNode->name = NULL;
				printf("Congrats! You have beat me! What were you thinking of?\n");
				(currentNode->yes_ptr)->name = getInput();

				printf("Insert a question about %s: \n", (currentNode->yes_ptr)->name );
				currentNode->question = getInput();
				(currentNode->no_ptr)->name = aux;

				printf("Do you want to play again?\n");
				ans = getInput();
				if(verifyAnswer(ans) == 0)
					finish = 1;
				else
					currentNode = root;
				free(ans);
			}
		}
		else
		{
			printf("%s\n", currentNode->question );
			ans = getInput();
			if(verifyAnswer(ans)==0)
				currentNode = currentNode->no_ptr;
			else
				currentNode = currentNode->yes_ptr;
			free(ans);
		}
	}
	
		//nodePrint(currentNode);*/

	if (output) { 
		treePrint(root);
		fclose(output);
	}

	freeWholeTree(root);
		return 0;
}