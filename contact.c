/*
 * Projecct     : Address Book
 * Author       :  Vignesh S
 * Date         : OCT 03 2024
 * Description  : In this file we are going to do the actual operation
 *              	1) add contact
 *	       		2) edit contact
 *	       		3) search contact
 *	       		4) delete contact
 *	       		5) save contact
 *	       		6) printing the contact
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include"contact.h"
#include <stdbool.h>
 

/* function get_field used to fetch the corresponding detail */
char *get_field(char *line_of_data, int count)
{
    int index = INIT_ZERO;
    char *temp_ptr = line_of_data;

    /* run the loop till reching the corresponding field */
    while (count)
    {
	/* check if the character is comma or newline the make it as null */
	if (line_of_data[index] == COMMA || line_of_data[index] == NEWLINE)
	{
	    count--;

	    /* make corresponding index as null */
	    line_of_data[index] = CHAR_NUL;

	    if (count != LOOP_END)
	    {
		/* if count not equal to zero then make the temp_ptr to point next field*/
	    	temp_ptr = (line_of_data + index + INDEX_PLUS_ONE);
	    }
	}
	index++;
    }
    /* return the corresponding field */
    return temp_ptr; 
}



/* function check_name used to check if the entered name 
 * already pressent in the .csv file or not
 */
Status check_name(const char *name, Abk_file *file)
{
    char name_arr[MAX_SIZE] = {INIT_ZERO};

    int user_count = file->rec_size;

    /* run the loop user_count times */
    while (--user_count >= LOOP_END)
    {
	/* copy the line by line to name_arr */
	strcpy(name_arr, file->record[user_count]);

	/* fetch the field if field is there generate error */
	char *fetched_name_field = get_field(name_arr, INDEX_PLUS_ONE);
	if (fetched_name_field != NULL && !strcmp(name, fetched_name_field))
	{
	    return failure;
	}
    }
    return success;
}


/* function check_mobile used to check 
 * the entered number in correct format
 */
 
Status check_mobile(char *mobile) {
    int mobile_len = strlen(mobile);

    /* if mobile number size equal to ten then check all are digits or not */
    if (mobile_len == MOBILE_LENGTH) {
        for (int index = INIT_ZERO; index < MOBILE_LENGTH; index++) {
            /* if character not digit then return failure */
            if (!(mobile[index] >= CHAR_ZERO && mobile[index] <= CHAR_NINE)) {
                return failure;
            }
        }
        return success;
    }
    return failure; // Return failure if not 10 digits
}

Status check_email(char *email) {
    int email_len = strlen(email);
    if (email_len > LENGTH_ZERO) {
        /* if the email consist @ and . return success else failure */
        char *ptr_to_at = strstr(email, "@gmail");
        if (ptr_to_at != NULL) {
            char *ptr_to_dot = strstr(ptr_to_at, ".com");
            if (ptr_to_dot != NULL) {
                return success;
            }
        }
    }
    return failure; // Return failure if email format is invalid
}

bool is_mobile_exist(Abk_file *file, char *mobile) {
    for (int i = 0; i < file->rec_size; i++) {
        if (strstr(file->record[i], mobile) != NULL) {
            return true; // Mobile number already exists
        }
    }
    return false;
}

bool is_email_exist(Abk_file *file, char *email) {
    for (int i = 0; i < file->rec_size; i++) {
        if (strstr(file->record[i], email) != NULL) {
            return true; // Email already exists
        }
    }
    return false;
}

/* function add_contact used to add the new user info to the list */
Status add_contact(Abk_file *file) {
    char name[MAX_SIZE] = { INIT_ZERO };
    char mobile[MAX_SIZE] = { INIT_ZERO };
    char email[MAX_SIZE] = { INIT_ZERO };
    char loc[MAX_SIZE] = { INIT_ZERO };
      
        printf("Enter the name: ");
        __fpurge(stdin);
        scanf("%[^\n]", name);

        int flag_mobile = FALSE, flag_email = FALSE, flag_loc = FALSE;
        

        while (true) {
            int choice = INIT_ZERO; 
            printf("\nEnter the choice:\n");
            printf("1. Mobile no\n");
            printf("2. Email add\n");
            printf("3. Location\n");
            printf("4. Exit\n");
            __fpurge(stdin);
            scanf("%d", &choice);
            switch (choice) {
                case e_mobile_no:
                    if (!flag_mobile) {
                        flag_mobile = TRUE;
                        printf("Enter the mobile no: ");
                        __fpurge(stdin);
                        scanf("%[^\n]", mobile);

                        if (check_mobile(mobile) == failure) {
                            flag_mobile = FALSE;
                            fprintf(stderr, "Enter a valid mobile no. (10 digits)\n");
                            fprintf(stderr, "Usage: 1234567890\n");
                        }
                        if (is_mobile_exist(file, mobile) == failure) {
                            flag_mobile = FALSE;
                            fprintf(stderr, "Entered mobile number already exists.\n");
                            fprintf(stderr, "Usage: 1234567890\n");
                        }
                    } else {
                        printf("INFO: Mobile no already entered. Choose other choice.\n");
                    }
                    break;
                case e_email:
                    if (!flag_email) {
                        flag_email = TRUE;
                        printf("Enter the email: ");
                        __fpurge(stdin);
                        scanf("%[^\n]", email);

                        if (check_email(email) == failure) {
                            flag_email = FALSE;
                            fprintf(stderr, "Enter a valid Email.\n");
                            fprintf(stderr, "Usage: ABC@gmail.com\n");
                        }
                        if (is_email_exist(file, email) == failure) {
                            flag_email = FALSE;
                            fprintf(stderr, "Entered email id already exists.\n");
                            fprintf(stderr, "Usage: ABC@gmail.com\n");
                        }
                    } else {
                        printf("INFO: Email already entered. Choose other choice.\n");
                    }
                    break;
                case e_location:
                    if (!flag_loc) {
                        flag_loc = TRUE;
                        printf("Enter the location: ");
                        __fpurge(stdin);
                        scanf("%[^\n]", loc);
                    } else {
                        printf("INFO: Location already entered. Choose other choice.\n");
                    }
                    break;
                case e_exit: {
                    file->rec_size++;

                    /* Reallocate memory for records */
                    char **ptr = realloc(file->record, file->rec_size * sizeof(char*));  //2d array dynamiclly allocate mem do col and last row 
					                                                                     //mem allocation 
                    if (ptr == NULL) {
                        fprintf(stderr, "Error: Memory not created\n");
                        return failure;
                    }
                    file->record = ptr;

                    /* Allocate memory for new record */
                    int len = strlen(name) + strlen(mobile) + strlen(email) + strlen(loc) + 10;
                    file->record[file->rec_size - INDEX_MINUS_ONE] = calloc(len, sizeof(char));

                    if (file->record[file->rec_size - INDEX_MINUS_ONE] == NULL) {
                        fprintf(stderr, "Error: Memory not created");
                        return failure;
                    }

                    /* Store data to the allocated memory */
                    sprintf(file->record[file->rec_size - INDEX_MINUS_ONE], "%s,%s,%s,%s\n", name, mobile, email, loc);
                    printf("------------------------NEW USER DATA-------------------------------\n");
                    printf("%s", file->record[file->rec_size - INDEX_MINUS_ONE]);
                    printf("--------------------------------------------------------------------\n");
                    return success;
                }
                default:
                    printf("NOTE: Enter the correct choice.\n");
            }
        }

         

    return success; // Return success when done adding contacts
}


/* function edit_contact used to edit the existing contact detail */
Status edit_contact(Abk_file *file)
{
    printf("Choose the choice to search the user data:\n");

    /* To choose the contact, call the search_contact function */
    search_contact(file);

    int index = INIT_ZERO;

    /* Based on the search result edit the list 
     * no index found mean return failure 
     */
    if (!file->search_ind)
    {
	return failure;
    }
    /* if only one index mean send the corresponding index */
    else if (file->search_ind == IS_EQUAL_ONE)
    {
	index = file->search_ind;
    }
    else if (file->search_ind > IS_EQUAL_ONE)
    {
	/* if more result found mean ask the userr to choose the contact */
	while (WHILE_ONE)
	{
	    printf("Which detatil you want to delete?\n");
	    __fpurge(stdin);
	    scanf("%d", &index);
	    /* if correct choice mean break else ask again */
	    if (index <= file->search_ind)
	    {
		break;
	    }
	    else
	    {
		printf("Enter the correct choice\n");
	    }
	}
    }
    /* Getting conformation from the user to want edit the selected info */
    printf("Are you sure! do you want edit the below data(y/n)?\n");
    printf("%s\n", file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
    __fpurge(stdin);

    char conform;
    scanf("%c", &conform);
    if (conform == 'y' || conform == 'Y')
    {
	/* Based on the length allocate temporary memory */
	int len = strlen(file->record[file->search_rec[index - INDEX_MINUS_ONE]]) + PLUS_ONE ;
	char *temp_ptr = calloc(len, sizeof(char));
	if (temp_ptr == NULL)
	{
	    printf("ERROR:Memory not allocated\n");
	    return failure;
	}

	/* Based on the select info get each field and store to a array of pointer */
	char *field[SIZE_OF_PTR_TO_ARRAY];

	/* store name to array of ptr */
	strcpy(temp_ptr, file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
	field[INDEX_ZERO] = get_field(temp_ptr, FIRST_DATA_FIELD);

	/* store mobile no to array of ptr */
	strcpy(temp_ptr, file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
	field[INDEX_ONE] = get_field(temp_ptr, SECOND_DATA_FIELD);

	/* store email to array of ptr */
	strcpy(temp_ptr, file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
	field[INDEX_TWO] = get_field(temp_ptr, THIRD_DATA_FIELD);

	/* store location to array of ptr */
	strcpy(temp_ptr, file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
	field[INDEX_THREE] = get_field(temp_ptr, FORTH_DATA_FIELD);

	printf("%s %s %s %s\n", field[INDEX_ZERO], field[INDEX_ONE], field[INDEX_TWO], field[INDEX_THREE]);

	char name[MAX_SIZE]   = {INIT_ZERO};
	char mobile[MAX_SIZE] = {INIT_ZERO};
	char email[MAX_SIZE]  = {INIT_ZERO};
	char loc[MAX_SIZE]    = {INIT_ZERO};

	int flag_name =INIT_ZERO, flag_mob = INIT_ZERO, flag_email = INIT_ZERO, flag_loc = INIT_ZERO;
	
	/* Based on the user choice edit the corresponding detail */
	while (WHILE_ONE)
	{
	    int choice;
	    printf("\nEnter the choice you want to edit\n");
	    printf("1.Name\n");
	    printf("2.Mobile\n");
	    printf("3.Gmail\n");
	    printf("4.Location\n");    
	    printf("5.Exit\n");    
	    __fpurge(stdin);
	    scanf("%d", &choice);
	    switch (choice)
	    {
		/* choice one used to edit the name */
		case edit_name:
		    {
			/* already name not edited mean allow the user to edit */
			if (!flag_name)
			{
			    printf("---------------Edit the name-----------------\n");
			    if (field[INDEX_ZERO] != NULL)
			    {
				printf("Existing name => \" %s \"\n", field[INDEX_ZERO]);
			    }

			    /* getting new name */
			    printf("Enter the new name:");
			    __fpurge(stdin);
			    scanf("%[^\n]",name);

			    /* If name is correct mean don't allow the user to edit again */
			    if (!check_name(name, file))
			    {
				flag_name = TRUE;
			    }
			    else
			    {
				flag_name = FALSE;
			    }
			}
			else
			{
			    printf("ERROR: Name already edited\n");
			}
		    }
		    break;
		/* choice TWO used to edit the mobile number */
		case edit_mobile_no:
		    {
			/* already mobile not edited mean allow the user to edit */
			if (!flag_mob)
			{
			    printf("--------------Edit the mobile no--------------\n");
			    if (field[INDEX_ONE] != NULL)
			    {
				printf("Existing mobile => \" %s \"\n", field[INDEX_ONE]);
			    }

			    /* getting new mobile no */
			    printf("Enter the new mobile no:");
			    __fpurge(stdin);
			    scanf("%[^\n]",mobile);

			    /* If mobile no is correct mean don't allow the user to edit again */
			    if (!check_mobile(mobile))
			    {
				flag_mob = TRUE;
			    }
			    else
			    {
				flag_mob = FALSE;
			    }
			}
			else
			{
			    printf("ERROR: Mobile no. already edited\n");
			}
		    }
		    break;
		/* choice three used to edit the email */
		case edit_email:
		    {
			/* already email not edited mean allow the user to edit */
			if (!flag_email)
			{
			    printf("--------------Edit the email-----------------\n");
			    if (field[INDEX_TWO] != NULL)
			    {
				printf("Existing email is \" %s \"\n", field[INDEX_TWO]);
			    }

			    /* getting new email */
			    printf("Enter the new email:");
			    __fpurge(stdin);
			    scanf("%[^\n]",email);

			    /* If email is correct mean don't allow the user to edit again */
			    if (!check_email(email))
			    {
				flag_email = TRUE;
			    }
			    else
			    {
				flag_email = FALSE;
			    }
			}
			else
			{
			    printf("ERROR: Email already edited\n");
			}

		    }
		    break;
		/* choice four used to edit the location */
		case edit_location:
		    {
			/* already location not edited mean allow the user to edit */
			if (!flag_loc)
			{
			    printf("----------------Edit the location------------\n");
			    if (field[INDEX_THREE] != NULL)
			    {
				printf("Existing location => \" %s \"\n", field[INDEX_THREE]);
			    }

			    /* getting new location */
			    printf("Enter the new location:");
			    __fpurge(stdin);
			    scanf("%[^\n]", loc);

			    /* If location is correct mean don't allow the user to edit again */
			    flag_loc = TRUE;
			}
			else
			{
			    printf("ERROR: Location already edited\n");
			}

		    }
		    break;
		/* choice five used to store the edited info into corresponding position */
		case edit_exit:
		    {
			/* based on the modification store the modified value to the array of ptr */
			if (flag_name)
			{
			    field[INDEX_ZERO] = name;
			}
			if (flag_mob)
			{	
			    field[INDEX_ONE] = mobile;
			}
			if (flag_email)
			{
			    field[INDEX_TWO] = email;
			}
			if (flag_loc)
			{
			    field[INDEX_THREE] = loc;
			}

			/* based on the string length allocate new memory and store the new info */
			int len = strlen(field[INDEX_ZERO]) + strlen(field[INDEX_ONE]) +strlen(field[INDEX_TWO]) + strlen(field[INDEX_THREE]) + 10;
			char *temp_ptr = calloc(len, sizeof(char)); 
   			if (temp_ptr == NULL)
			{
			    return failure;
			}

			/* free the old memory */
			if(file->record[file->search_rec[index - INDEX_MINUS_ONE]]!=NULL)
			{
			free(file->record[file->search_rec[index - INDEX_MINUS_ONE]]);
			file->record[file->search_rec[index - INDEX_MINUS_ONE]]=NULL; // to prevent dangling pointer....
			}

			/* store the data to the newly created memory */
			sprintf(temp_ptr, "%s,%s,%s,%s\n", field[INDEX_ZERO], field[INDEX_ONE], field[INDEX_TWO], field[INDEX_THREE]);
			
			/* add the new memory to the array of index */
			file->record[file->search_rec[index - INDEX_MINUS_ONE]] = temp_ptr;

			return success;
		    }
		    break;
	    }
	}
    }
    return success;
}

/* function search_contact used to search the user info in the record */
Status search_contact(Abk_file *file)
{
    /* Based on the user choice search the info */
    int choice = INDEX_ZERO;
    while (WHILE_ONE)
    {
	printf("\nEnter the choice:\n");
	printf("1.Name\n");
	printf("2.Mobile\n");
	printf("3.Gmail\n");
	printf("4.Location\n");

	__fpurge(stdin);
	scanf("%d", &choice);

	/* IF choice within range then break */
	if (choice >= MIN_CHOICE && choice <= MAX_CHOICE)
	{
	    break;
	}
    }

    char arr[MAX_SIZE];
    switch (choice)
    {
	/* choice ONE used to get the user name want to search */
	case search_name:
	    {
		printf("Enter the name:");
		__fpurge(stdin);
		scanf("%[^\n]", arr);
	    }
	    break;
	/* choice TWO used to get the user mobile want to search */
	case search_mobile_no:
	    {
		printf("Enter the mobile:");
		__fpurge(stdin);
		scanf("%[^\n]", arr);
	    }
	    break;
	/* choice THREE used to get the user gmail want to search */
	case search_email:
	    {
		printf("Enter the gmail:");
		__fpurge(stdin);
		scanf("%[^\n]", arr);
	    }
	    break;
	/* choice FOUR used to get the user location want to search */
	case search_location:
	    {
		printf("Enter the location:");
		__fpurge(stdin);
		scanf("%[^\n]", arr);
	    }
	    break;
    }

    /* search index always start from 0th index */
    file->search_ind = INIT_ZERO; 

    for (int i=INIT_ZERO; i<file->rec_size; i++)
    {
	/* getting size of each line */
	int len = strlen(file->record[i]) + PLUS_ONE;
	
	/* allocate memory for storing that line */
	char *ptr = calloc(len, sizeof(char));

	/* copy the data */
	strcpy(ptr, file->record[i]);

	/* Get the corresponding field */
	char *field = get_field(ptr, choice);

	if (field != NULL)
	{
	    /* compare the field till n character */
	    int n = strlen(arr);
	    if (!strncmp(field, arr, n))
	    {
		/* if field find mean store the corresponding index in seach_rec array */
		file->search_ind++;
		file->search_rec = realloc(file->search_rec, file->search_ind);
		if (file->search_rec == NULL)
		{
		    return failure;
		}
		/* store the search result in the search_rec array */
		file->search_rec[file->search_ind - INDEX_MINUS_ONE] = i; 
	    }	
	}
    }

    /* print the search result */
    printf("----------------------Search result-------------------------\n");

    if(!file->search_ind)
    {
	printf("INFO: No context present in the address_book based on the search!\n");
    }
    else
    {
	for(int i=INIT_ZERO; i<file->search_ind; i++)
	{
	    printf("%d) %s", i + PLUS_ONE, file->record[file->search_rec[i]]);
	}
    }
    printf("------------------------------------------------------------\n");
    return success;
}

/* function delete_contact used to delete the contact */
Status delete_contact(Abk_file *file)
{ 
    /* To delete particular info first search in the record */
    printf("Choose the choise to search the user data:\n");
    search_contact(file);

    int choice;
    /* Based on the search result edit the list 
     * no index found mean return failure 
     */
    if (!file->search_ind)
    {
	return failure;
    }
     /* if only one index mean send the corresponding index */
    else if (file->search_ind == IS_EQUAL_ONE)
    {
	choice = file->search_ind;
    }
    /* if more result found mean ask the userr to choose the contact */

    else if (file->search_ind > IS_EQUAL_ONE)
    {
	while (WHILE_ONE)
	{
	    printf("Which contact detatil you want to delete?\n");
	    __fpurge(stdin);
	    scanf("%d", &choice);
	    /* if correct choice mean break else ask again */
	    if (choice <= file->search_ind)
	    {
		break;
	    }
	    else
	    {
	    	printf("Enter the correct choice\n");
	    }
	}
    }
    char ch = 'n';

    /* Getting conformation from the user */
    printf("Are you sure! do you want delete the below user data(y/n)?\n");
    printf("%s", file->record[file->search_rec[choice - INDEX_MINUS_ONE]]);
    __fpurge(stdin);
    scanf("%c", &ch);

    if (ch == 'y' || ch == 'Y')
    {
	/* free the memory */
	if(file->record[file->search_rec[choice - INDEX_MINUS_ONE]]!=NULL)
	{
	free(file->record[file->search_rec[choice - INDEX_MINUS_ONE]]);
	file->record[file->search_rec[choice - INDEX_MINUS_ONE]]=NULL;
	}

	/* shift all the indexes by one from the deleted index */
	for (int i=file->search_rec[choice - INDEX_MINUS_ONE]; i<file->rec_size - MINUS_ONE; i++)
	{
	    file->record[i] = file->record[i + INDEX_PLUS_ONE];
	}
    printf("Contact deleted successfully....");
	/*reallocate the record */
	char **ptr = realloc(file->record, (file->rec_size - MINUS_ONE) * sizeof(char*));
	if (ptr == NULL)
	{
	    printf("ERROR: Error in reallocating\n");
	    return failure;
	}
	else
	{
	    /* assign the temporary ptr to record */
	    file->record = ptr;

	    /* and retude the size */
	    file->rec_size--;

	    return success;
	}
    }
    return success;
}

/* function save_contact used to save the record to .csv file */
Status save_contact(Abk_file *file) {
    if (file->input_fptr) {
        fclose(file->input_fptr);
    }

    file->input_fptr = fopen(file->input_file, "w");
    if (file->input_fptr == NULL) {
        perror("Failed to open file for writing");
        return failure;
    }

    // Write data
    fprintf(file->input_fptr, "#%d#\n", file->rec_size);
    for (int i = INIT_ZERO; i < file->rec_size; i++) {
        fprintf(file->input_fptr, "%s", file->record[i]);
    }

    fclose(file->input_fptr); // Remember to close the file after writing
    return success;
}

Status print_contact(Abk_file *file) {
    printf("Name                      Phone Number    Email                          Address\n");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < file->rec_size; i++) {
        char *record = strdup(file->record[i]); // Duplicate the string
        if (record == NULL) {
            perror("Failed to allocate memory");
            return failure; // Handle memory allocation failure
        }
        
        char *name = strtok(record, ",");
        char *mobile = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *loc = strtok(NULL, ",");

        // Handle missing data
        if (!mobile) mobile = "N/A";
        if (!email) email = "N/A";
        if (!loc) loc = "N/A";
        if (!name) name = "N/A"; // Check for null name

        printf("%-25s %-15s %-30s %-15s\n", name, mobile, email, loc);
        if(record!=NULL)
		{
		free(record); // Free the duplicated string
		record=NULL;
		}
    }
	printf("------------------------------------------------------------------------------------------\n");
}