#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Inputs{
	int * data;
	size_t size;
	size_t capacity;
} vector;

int vector_init(vector * v, size_t init_capacity){
	v->data = (int *) malloc(init_capacity * sizeof(int));
	if (!v->data) return -1;

	v->size = 0;
	v->capacity = init_capacity;
	return 0;
}

int vector_resize(vector * v, size_t new_capacity) {
	v->capacity = new_capacity;
	v->data = realloc(v->data, new_capacity * sizeof(int));
	if (!v->data) return -1;

	return 0;
}

void read_file(vector * input){
	FILE *fp = fopen("input", "r");
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	
	line_size = getline(&line_buf, &line_buf_size, fp);
	while(line_size >= 0){
		//printf("contents: %s\n", line_buf);
		
		//split line
		char * token = strtok(line_buf, ",");

		while(token != NULL){
			printf("Size: %lu\n", input->size);

			input->data[input->size] = atoi(token);
			//printf("content: %s\n", token);
			
			//read next item
			//NULL means the place we stopped before
			token = strtok(NULL, ",");
			
			input->size++;
			if (input->size == input->capacity) {
				vector_resize(input, 200);
				printf("New capacity: %lu\n", input->capacity);
			}
		}
		printf("*Line length: %lu\n", input->size);
		line_size = getline(&line_buf, &line_buf_size, fp);
	}	
	free(line_buf);
	line_buf = NULL;
	fclose(fp);
}

void calculate(vector * input){
	int index = 0;
	while(index < input->size){
		int result;	
		int operator = input->data[index];
		printf("Operator: %d\n", operator);
		int l_oper_index = input->data[index+1];
		int r_oper_index = input->data[index+2];
		int output_index = input->data[index+3];

		int l_number = input->data[l_oper_index];
		int r_number = input->data[r_oper_index];
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
			break;
		}
		input->data[output_index] = result;
		index += 4;
	
		//printf("New array: ");
		//for (int i=0; i<input->size; i++){
		//	printf("%d,", input->data[i]);
		//	if((i+1)%4==0){
		//		printf(" / ");
		//	}
		//}
		//printf("\n\n");
	}		
}

int main(){	
	int max_size = 100;

	//if (inputs.data == NULL) {
        //	printf("Memory not allocated.\n");
        //	exit(0);
    	//} 

	vector input;
	vector_init(&input, max_size);
	printf("Size: %lu\n", input.size);
	printf("Capacity: %lu\n", input.capacity);

	read_file(&input);

	printf("Array: ");
	for (int i=0; i<input.size; i++){
		printf("%d,", input.data[i]);
		if((i+1)%4==0){
			printf(" / ");
		}
	}
	printf("\n\n");	
	calculate(&input);

	printf("Result: ");
	for (int i=0; i<input.size; i++){
		printf("%d,", input.data[i]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
