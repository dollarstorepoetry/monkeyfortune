#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main(){
	FILE *quotefp = fopen("monkeytype-quotes/english.json", "r");
	if (quotefp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    }

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
  
  	
    // delete the JSON object 
    cJSON_Delete(json); 
	return 0; 
}
