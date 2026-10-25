#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
void listContacts(AddressBook *addressBook) 
{
   int i,j;
   Contact temp;
   
   if(addressBook->contactCount==0)
   {
	   printf(RED"No contacts found!\n"RESET);
	   return;
   }

    for(i=0; i < addressBook->contactCount-1; i++)
    {
	    for(j=0;j<addressBook->contactCount-i-1;j++)
	    {
		    if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
		    {
			    temp=addressBook->contacts[j];
			    addressBook->contacts[j]=addressBook->contacts[j+1];
			    addressBook->contacts[j+1]=temp;
		    }
	    }
    }
    printf(MAGENTA"\n---------------contact list---------------\n"RESET);
    printf(CYAN"%-5s %-15s %-12s %-25s\n","S.no","Name","phone","Email"RESET);
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("%-5d %-15s %-12s %-25s\n",
		       	i+1,
		       	addressBook->contacts[i].name,
			addressBook->contacts[i].phone,
			addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount=0;
    loadContactsFromFile(addressBook);
    
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook);
       exit(EXIT_SUCCESS);
}

//to validate the contact name
int validate_name(char name[])
{
	for(int i=0;name[i];i++)
	{
  		if((name[i]>='a'&&name[i]<='z')||
		     (name[i]>='A'&&name[i]<='Z')||
		     name[i]=='.'||name[i]==' ')
		{
			//valid
		}
		else
		{
			return 0;
		}
        }
	return 1;
}
//to check entered numbere is valid or not
int validate_phone(char phone[])
{
	int l=0;
	for(int i=0;phone[i];i++)
	{
		if(phone[i]>='0'&&phone[i]<='9')
		{
			l++;
		}
	
	}
	if(l!=10)
	{
	  return 0;
        }
	  return 1;
}
//to check email is valid or not
int validate_email(char email[])
{
	int at=0,dot=0;
	if(!((email[0]>='a'&&email[0]<='z')||    
	     (email[0]>='A'&&email[0]<='Z')))	//email should start with alphabets only
	{
		return 0;
	}

	for(int i=0;email[i];i++)
	{
	    if(!((email[i]>='a'&&email[i]<='z')||
		(email[i]>='A'&&email[i]<='Z')||
		(email[i]>='0'&&email[i]<='9')||
		email[i]=='@'||email[i]=='.'||email[i]=='_'||email[i]=='-'))
	    {
		return 0;
            }

	    if(email[i]=='.'&&email[i+1]=='.')
	    {
			 return 0;
	    }

	    if(email[i]=='@')
		    at++;
	    if(email[i]=='.'&&at>0)
		    dot++;
	}

	if(at==1&&dot>=1)
	return 1;

	return 0;
}


void createContact(AddressBook *addressBook)
{
	/* logic to create Contacts */

    char str1[50];
    char str2[20];
    char str3[50]; 
    int res1,res2,res3;

    do{
        printf("name : ");
        scanf(" %[^\n]",str1);
	
        res1 = validate_name(str1);
	if(res1==0)
	{
		printf("Inavalid name!\n");
	}
    }while(res1== 0);

    do{
	    printf("phone: ");
	    scanf("%s",str2);

	    res2=validate_phone(str2);
	    if(res2==0)
	    {
		    printf("Invalid phone number!\n");
	    }
    }while(res2==0);

    do{
	    printf("Email: ");
	    scanf("%s",str3);

	    res3=validate_email(str3);
	    if(res3==0)
	    {
		    printf("Invalid email\n");
	    }
      }while(res3==0);


    strcpy(addressBook->contacts[addressBook->contactCount].name, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email,str3);
    addressBook->contactCount++;
    printf(GREEN"contact created successfully!\n"RESET);
    
}

void searchContact(AddressBook *addressBook) 
{
    int i,choice,found=0;
    char name[50];
    char phone[20];
    char email[50];

    printf("\n1.search by name\n");
    printf("2.search by phone\n");
    printf("3.search by email\n");
    printf(YELLOW"\nEnter your choice: "RESET);
    
   if(scanf("%d",&choice)!=1)
   {
	   printf(RED"Invalid choice!\n"RESET);
	   while(getchar()!='\n');
	   return;
   }

    switch(choice)
    {
	    case 1 :
		    printf("Enter name: ");
		    scanf(" %[^\n]",name);

		    for(i=0;i<addressBook->contactCount;i++)
		    {
			    if(strstr(addressBook->contacts[i].name,name)!=NULL)
			    {
				    printf("\nName:%s\n",addressBook->contacts[i].name);
				    printf("Phone:%s\n",addressBook->contacts[i].phone);
				    printf("Email:%s\n",addressBook->contacts[i].email);

				    found=1;
			    }
		    }
		    if(found==0)
		    {
			    printf("Contact not found");
		    }
		    break;

	    case 2 :
		    printf("Enter phone: ");
		    scanf("%s",phone);

		    for(i=0;i<addressBook->contactCount;i++)
		    {
			    if(strcmp(addressBook->contacts[i].phone,phone)==0)
			    {

				    printf("Name:%s\n",addressBook->contacts[i].name);
				    printf("Phone:%s\n",addressBook->contacts[i].phone);		    
				    printf("Email:%s\n",addressBook->contacts[i].email);

				    found=1;
			    }
		    }
		    if(found==0)
		    {
			    printf("Contact not found");
		    }
		    break;

	    case 3 :
		    printf("Enter Email: ");
		    scanf("%s",email);

		    for(i=0;i<addressBook->contactCount;i++)
		    {
			    if(strcmp(addressBook->contacts[i].email,email)==0)
			    {

				    printf("Name:%s\n",addressBook->contacts[i].name);
				    printf("Phone:%s\n",addressBook->contacts[i].phone);		    
				    printf("Email:%s\n",addressBook->contacts[i].email);

				    found=1;
			    }
		    }
		    if(found==0)
		    {
			    printf("Contact not found");
		    }
		    break;

	    default:
		    printf("Invalid choice!\n");
    }

}

void editContact(AddressBook *addressBook)
{
	int choice,res;
	int i,index=-1;
	char name[50];
	char phone[20];
	char email[50];

	printf("1.Edit  name\n");
	printf("2.Edit  phone\n");
	printf("3.Edit email\n");
	printf(YELLOW"Enter your choice: "RESET);
	if(scanf("%d",&choice)!=1)
	{
		printf(RED"Invalid choice!\n"RESET);
		while(getchar()!='\n');
		return;
	}

	switch(choice)
	{
		case 1 :
           		 printf("Enter existing name: ");
           		 scanf(" %[^\n]",name);
            		 for(i=0;i<addressBook->contactCount;i++)
		{
               		 if(strcmp(addressBook->contacts[i].name,name)==0)
		   {
                   	 index=i;
                   	 break;
             	   }
           	 }

            if(index==-1)
	    { printf("Contact not found!\n"); return; }

            do{
                printf("Enter new name: ");
                scanf(" %[^\n]",name);
                res = validate_name(name);
                if(res==0) printf("Invalid name!\n");
            }while(res==0);

            strcpy(addressBook->contacts[index].name,name);
            break;

           case 2: 
           	 printf("Enter existing phone: ");
           	 scanf("%s",phone);
           	 for(i=0;i<addressBook->contactCount;i++)
  	   {
                 	if(strcmp(addressBook->contacts[i].phone,phone)==0)
		{
                   	 index=i;
                   	 break;
                }
            }
            if(index==-1){ printf("Contact not found!\n"); return; }

            do{
                printf("Enter new phone: ");
                scanf("%s",phone);
                res = validate_phone(phone);
                if(res==0) printf("Invalid phone!\n");
            }while(res==0);

            strcpy(addressBook->contacts[index].phone,phone);
            break;

        case 3: 
           	 printf("Enter existing email: ");
           	 scanf("%s",email);
           	 for(i=0;i<addressBook->contactCount;i++)
		 {
                 	if(strcmp(addressBook->contacts[i].email,email)==0)
		 	{
                   	 index=i;
                   	 break;
               	        }
                 }
            if(index==-1)
	    { printf("Contact not found!\n"); return; }

            do{
                printf("Enter new email: ");
                scanf("%s",email);
                res = validate_email(email);
                if(res==0) printf("Invalid email!\n");
            }while(res==0);
            strcpy(addressBook->contacts[index].email,email);
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf(GREEN"Contact edited successfully!\n"RESET);
}
		



void deleteContact(AddressBook *addressBook)
{
	int choice,i,j;
	int found=0;
	char name[50];
	char phone[20];
	char email[50];

	printf("1.Delete by name\n");
	printf("2.Delete by phone\n");
	printf("3.Delete by email\n");
	printf(YELLOW"Enter your choice: "RESET);
	if(scanf("%d",&choice)!=1)
	{
		printf(RED"Invalid choice\n"RESET);
		while(getchar()!='\n');
		return;
	}

	switch(choice)
	{
		case 1:
			printf("Enter name: ");
			scanf(" %[^\n]",name);

			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].name,name)==0)
				{
					for(j=i;j<addressBook->contactCount-1;j++)
					{
						addressBook->contacts[j]=addressBook->contacts[j+1];
					}
					addressBook->contactCount--;
					found=1;
					printf("Contact deleted successfully!\n");
					break;
				}
			}
			break;

		case 2:
			printf("Enter phone: ");
			scanf("%[^\n]",phone);

			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].phone,phone)==0)
				{
					for(j=i;j<addressBook->contactCount-1;j++)
					{
						addressBook->contacts[j]=addressBook->contacts[j+1];
					}
					addressBook->contactCount--;
					found=1;
					printf("Contact deleted successfully!\n");
					break;
				}
			}
			break;

		case 3:
			printf("Enter email: ");
			scanf("%[^\n]",email);

			for(i=0;i<addressBook->contactCount;i++)
			{
				if(strcmp(addressBook->contacts[i].email,email)==0)
				{
					for(j=i;j<addressBook->contactCount-1;j++)
					{
						addressBook->contacts[j]=addressBook->contacts[j+1];
					}
					addressBook->contactCount--;
					found=1;
					printf("Contact deleted successfully!\n");
					break;
				}
			}
			break;

		default:
			printf(RED"Invalid choice\n"RESET);
	}
	if(found==0)
	{
		printf(RED"contact not found!\n"RESET);
	}
   
}
