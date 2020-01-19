#include <stdio.h>
#include <stdlib.h>

int calculate(int mass);

int calculate(int mass){
	int a = (mass/3) - 2;
	return a;
}

int main(){
	int result;
	int total;

	FILE *fp = fopen("input", "r");
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	
	line_size = getline(&line_buf, &line_buf_size, fp);
	while(line_size >= 0){
		int buff = atoi(line_buf);
		//printf("contents: %d\n", buff);
		result = calculate(buff);
		//printf("Result: %d\n", result);
		total += result;
		//printf("Added result: %d\n", total);

		line_size = getline(&line_buf, &line_buf_size, fp);
	}
	free(line_buf);
	line_buf = NULL;
	fclose(fp);
	
	printf("Total result: %d\n", total);
	return EXIT_SUCCESS;
}
		

