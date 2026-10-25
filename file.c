#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

	FILE*fp=fopen("contacts.txt","w");
	
	if(fp==NULL)
	{
		printf("file cannot be open\n");
		return;
	}

	fprintf(fp,"#%d\n",addressBook->contactCount);

	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,
				 	addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
	}
	

    fclose(fp);
    
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    
	FILE *fp=fopen("contacts.txt","r");
	addressBook->contactCount = 0;
    
   if(fp==NULL)
   {
	  return;
   
   }

   fscanf(fp,"#%d\n",&addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++)
  {
	  fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,
			 		 addressBook->contacts[i].phone,
					 addressBook->contacts[i].email);
  }
	  fclose(fp);
}
