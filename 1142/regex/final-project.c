// username: collint@mtu.edu

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fnmatch.h>
#include <string.h>


int main(int argc, char *argv[]){
	if(argc <= 2){
		printf("Expected --wildcard <wildcard> or --regex <regex> command line arguments\n");
		return 1;
	}

	char* string[8];

	if(!strcmp(argv[1], "--wildcard")){ //wildcard 
		char* string[8];
		while(scanf("%s[^\n]", string) != EOF){

			if(!fnmatch(argv[2], (const char*)string, 0)){
				printf("%s\n", string);
			}
		}


	} else if(!strcmp(argv[1], "--regex")){//regex
		regex_t regex;
		if(!regcomp(&regex, argv[2], REG_EXTENDED)){
			while(scanf("%s[^\n]", string) != EOF){
				if(!regexec(&regex, (const char*)string, 0, NULL, 0)){
					printf("%s\n", string);
				}
			}
		} else{
			printf("Regular expression failed to compile\n");
			return -2;
		}
		
		regfree(&regex);
	} else{
		printf("Expected --wildcard <wildcard> or --regex <regex> command line arguments\n");
		return 1;
	}
	return 0;
}
