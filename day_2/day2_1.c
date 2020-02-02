#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate(int mass);

int calculate(int mass){
	int a = (mass/3) - 2;
	return a;
}

int main(){
	int result;
	int total;
	int inputs[255];

	FILE *fp = fopen("small_input", "r");
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	
	line_size = getline(&line_buf, &line_buf_size, fp);
	while(line_size >= 0){
		printf("contents: %s\n", line_buf);
		
		//split line
		char * token = strtok(line_buf, ",");
		int i = 0;
		while(token != NULL){
			inputs[i] = atoi(token);
			printf("content: %s\n", token);
			//read next item
			//NULL means the place we stopped before
			token = strtok(NULL, ",");
			i++;

			line_size = getline(&line_buf, &line_buf_size, fp);
		}
	}	
	free(line_buf);
	line_buf = NULL;
	fclose(fp);
	
	// print array
	for (int i=0; i<20; i++){
		printf("%d,", inputs[i]);
		//result = calculate(buff);
		//printf("Result: %d\n", result);
		//total += result;
		//printf("Added result: %d\n", total);
	}
		
	//printf("Total result: %d\n", total);
	return EXIT_SUCCESS;
}
		

