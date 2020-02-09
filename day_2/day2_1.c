#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void calculate(int length, int * inputs){
	int index = 0;
	while(index < length){
		int result;	
		int operator = inputs[index];
		printf("Operator: %d\n", operator);
		int l_oper_index = inputs[index+1];
		int r_oper_index = inputs[index+2];
		int output_index = inputs[index+3];

		int l_number = inputs[l_oper_index];
		int r_number = inputs[r_oper_index];
		if(operator==1){
			result = l_number + r_number;
			printf("%d + %d = %d\n", l_number, r_number, result);
		} else if(operator==2){
			result = l_number * r_number;
			printf("%d * %d = %d\n", l_number, r_number, result);
		} else if(operator==99){
			printf("Finish!\n");
			break;
		} else{
			printf("Something wrong...\n");
			int * empty = {0};
			break;
		}
		inputs[output_index] = result;
		index += 4;
	
		printf("New array: ");
		for (int i=0; i<length; i++){
			printf("%d,", inputs[i]);
			if((i+1)%4==0){
				printf(" / ");
			}
		}
		printf("\n\n");
	}		
}


void read_file(int * inputs, int length){
	FILE *fp = fopen("input", "r");
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	
	line_size = getline(&line_buf, &line_buf_size, fp);
	while(line_size >= 0){
		//printf("contents: %s\n", line_buf);
		
		//split line
		char * token = strtok(line_buf, ",");

		int i = 0;
		while(token != NULL){
			inputs[i] = atoi(token);
			//printf("content: %s\n", token);
			//read next item
			//NULL means the place we stopped before
			token = strtok(NULL, ",");
			i++;
		}
		//printf("*Line length: %d\n", i);
		line_size = getline(&line_buf, &line_buf_size, fp);
	}	
	free(line_buf);
	line_buf = NULL;
	fclose(fp);
}

int main(){
	//int result;
	int length = 121;
	int inputs[length];

	read_file(inputs, length);

	//printf("Array: ");
	//for (int i=0; i<length; i++){
	//	printf("%d,", inputs[i]);
	//	if((i+1)%4==0){
	//		printf(" / ");
	//	}
	//}
	//printf("\n\n");
	
	calculate(length, inputs);

	printf("Result: ");
	for (int i=0; i<length; i++){
		printf("%d,", inputs[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
