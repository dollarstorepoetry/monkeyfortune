#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <time.h>  // just for random :^)
#include <libgen.h> // for getting the directory
#include <unistd.h> // for getting the directory
#include <string.h> // strcat

void get_binary_directory(char *buffer, size_t size) {
    char path[1024];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);

    if (len == -1) {
        fprintf(stderr, "readlink ???");
        exit(1);
    }

    path[len] = '\0'; // Null-terminate the path

    // Extract the directory using dirname
    char *dir = dirname(path);
    snprintf(buffer, size, "%s", dir);
}

int main(){
	char dir[1024];
	get_binary_directory(dir, sizeof(dir));
	// FILE *quotefp = fopen("monkeytype-quotes/english.json", "r");
	FILE *quotefp = fopen(strcat(dir, "/monkeytype-quotes/english.json"), "r");
	// TODO: make this directory-agnostic ???? idk that makes me sound smart
	// TODO: make this work with windows (although who's using this on windows tbh)
	if (quotefp == NULL) { 
		printf("Error: Unable to open the file.\n");
		return 1; 
   	}

	// read contents from file
	char *buffer = (char *)malloc(1 << 23); // 2^23 should be big enough to store this file forever.
	                                        // either way i'm not making that optimization rn
	unsigned long long len = fread(buffer, 1, 1 << 23, quotefp);
	fclose(quotefp); 

 	// initialize json parser
	cJSON *json = cJSON_Parse(buffer); 	
	free(buffer); 
	if (json == NULL) { 
		const char *error_ptr = cJSON_GetErrorPtr(); 
		if (error_ptr != NULL) { 
			fprintf(stderr, "Error: %s\n", error_ptr);
		} 
		cJSON_Delete(json); 
		exit(1);
	} 

	// loop through the ENTIRE quote array and store info in respective arrays
	// TODO: can this be more efficient? lol
	// TODO: add support for multiple languages
	cJSON *quotes = cJSON_GetObjectItemCaseSensitive(json, "quotes");
	char** quote_text = (char **)malloc((len+1) * sizeof(char *));  // array of quotes
	char** author_info = (char **)malloc((len+1) * sizeof(char *)); // array of sources
	int nq = 0;
	if (cJSON_IsArray(quotes)){
		cJSON *quote_obj;
		cJSON_ArrayForEach(quote_obj, quotes){
			cJSON* text = cJSON_GetObjectItemCaseSensitive(quote_obj, "text");
			cJSON* source = cJSON_GetObjectItemCaseSensitive(quote_obj, "source");

			if (!cJSON_IsString(text)){
				fprintf(stderr, "Quote text is not recognized as valid text.");
				exit(1);
			}
			else quote_text[nq] = text->valuestring;

			if (!cJSON_IsString(source)){
				fprintf(stderr, "Quote author is not recognized as valid text.");
				exit(1);
			}
			else author_info[nq] = source->valuestring;
			
			nq++;
		}
	} else {
		fprintf(stderr, "quotes object not recognized as array.");
		exit(1);
	}

	// finally, pick a random quote from our. giant. array and output
	srand(time(NULL));
	int ridx = rand() % nq;
	printf("\"%s\"\n\t-%s\n", quote_text[ridx], author_info[ridx]);

	// delete the JSON object and free all ya stuff.
	cJSON_Delete(json); 
	free(quote_text);
	free(author_info);
	return 0; 
}
