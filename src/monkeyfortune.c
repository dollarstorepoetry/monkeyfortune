#include <stdio.h>
#include <stdlib.h>
// #include <cjson/cJSON.h>
#include "cJSON.h"
// #include <cJSON.h>
#include <time.h>  // just for random :^)

int main(){
	FILE *quotefp = fopen("monkeytype-quotes/english.json", "r");
	if (quotefp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    }

	//fseek(quotefp, 0, SEEK_END);
	//unsigned long long file_size = ftell(quotefp);
	//rewind(quotefp);

	// read contents from file
	char *buffer = (char *)malloc(1 << 23); // 2^23 should be big enough to store this file forever.
	                                        // either way i'm not making that optimization rn
    unsigned long long len = fread(buffer, 1, 1 << 23, quotefp);
    fclose(quotefp); 

	/* grab random quote from file and output */
 	cJSON *json = cJSON_Parse(buffer); 	
	free(buffer); // should probably be able to free the buffer atp. delete this comment later
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 

	cJSON *quotes = cJSON_GetObjectItemCaseSensitive(json, "quotes");
	char** quote_text = (char **)malloc((len+1) * sizeof(char *));
	char** author_info = (char **)malloc((len+1) * sizeof(char *));
	int nq = 0;
	if (cJSON_IsArray(quotes)){
		printf("Quotes:\n");
		cJSON *quote_obj;
		cJSON_ArrayForEach(quote_obj, quotes){
			// wtf is error checking
			char* text = cJSON_GetObjectItemCaseSensitive(quote_obj, "text")->valuestring;
			char* source = cJSON_GetObjectItemCaseSensitive(quote_obj, "source")->valuestring;
			quote_text[nq] = text;
			author_info[nq] = source;
			// printf("\"%s\"\n\t-%s\n\n", text, source);
			nq++;
		}
	}

	srand(time(NULL));
	int ridx = rand() % nq;
	// printf("%d\n", ridx);
	printf("\"%s\"\n\t-%s\n", quote_text[ridx], author_info[ridx]);

    // delete the JSON object and free ya shit
    cJSON_Delete(json); 
	free(quote_text);
	free(author_info);
	return 0; 
}
