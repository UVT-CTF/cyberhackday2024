#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void x(char *text, char key)
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        text[i] = text[i] ^ key;
    }
}

void c(char *text, int shift)
{
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = 'a' + (text[i] - 'a' + shift) % 26;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = 'A' + (text[i] - 'A' + shift) % 26;
        }
    }
}

int main()
{
    FILE *file;
    char text[10000];
    int s = 3;
    char xk = '-';

    file = fopen("flag.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    if (fgets(text, sizeof(text), file) == NULL)
    {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    fclose(file);

    text[strcspn(text, "\n")] = '\0';

    c(text, s);
    x(text, xk);
    printf("Super secret code:\n");
    int l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        printf("%d ", (int)(text[i]));
    }

    return 0;
}
   	  	   
	
     	    		
	
     		    	
	
     		 		 	
	
     			    
	
     				 		
	
     			   	
	
     			 	 	
	
     		 	  	
	
     			 	  
	
     		  	 	
	
     	 					
	
     			  		
	
     			    
	
     		    	
	
     		   		
	
     		 	  	
	
     		 				
	
     			 	 	
	
     			  		
	
     	 					
	
     		 	  	
	
     		 			 
	
     		 			 
	
     		 	  	
	
     			 	  
	
     					 	
	
  


