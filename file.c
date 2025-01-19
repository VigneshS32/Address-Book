/*
 * Project      : Address Book
 * Name         : Vignesh S
 * Date         : OCT 03 2024
 * Description  : address_book file used to do required process
 * 		before doing the actual process.
 *		1) opening file
 * 		2) finding the user count
 *		2) allocationg memory and cpy the data 
 *		3) call the operation based on user requirement
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include"file.h"

/* Address_book function used to modify the data */
Status address_book(Abk_file *file)
{
    /* open the file */
    if (!open_file(file))
    {
	/* find user count */
	if (!fetch_rec_size(file))
	{
	    /* allocate memory for user info */
	    if (!allocate_memory_cpy_data(file))
	    {
		/* Based on the user choice call related function */
		int user_choice;
		while (SUPER_LOOP)
		{
		    printf("\nEnter your choice:\n");
		    printf("1.Add contact\n");
		    printf("2.Edit contact\n");
		    printf("3.Search contact\n");
		    printf("4.Delete contact\n");
		    printf("5.save contact in ABK\n");
		    printf("6.List contact\n");
		    printf("7.Exit\n");
		    printf("Please select an option:");
		    __fpurge(stdin);
		    if (!scanf("%d", &user_choice))
		    {
			user_choice = VALUE_ZERO;
		    }
			char con ='n';
		    switch (user_choice)
		    {
			/* choice one used for add the new user */
			case e_add_contact:
			do{
			    printf("-----------------------ADD CONTACT-----------------------\n");
			    file->save_flag = VALUE_ONE;
			    add_contact(file);
				// Ask the user if they want to add another contact
                   printf("Do you want to add another contact? (y/n): ");
                  __fpurge(stdin);
                    scanf(" %c", &con); // Note the space before %c to consume any leftover newline
    } while (con == 'y' || con == 'Y');
			    break;
			    /* choice two used for edit the given user info */
			case e_edit_contact:
			    printf("-----------------------EDIT CONTACT-----------------------\n");
			    file->save_flag = VALUE_ONE;
			    edit_contact(file);
				printf("Contact edited successfully..");
			    break;
			    /* choice three used for search the given user */
			case e_search_contact:
			    printf("-----------------------SEARCH CONTACT-----------------------\n");
			    file->save_flag = VALUE_ONE;
			    search_contact(file);
			    break;
			    /* choice four used for delete the given user info */
			case e_delete_contact:
			    printf("-----------------------DELETE CONTACT-----------------------\n");
			    file->save_flag = VALUE_ONE;
			    delete_contact(file);
			    break;
			    /* choice five used for save the modification*/
			case e_save_contact:
			    printf("-----------------------SAVE CONTACT-----------------------\n");
			    file->save_flag = VALUE_ZERO;
			    save_contact(file);
			    printf("INFO: Data saved successfully\n");
			    printf("----------------------------------------------------------\n");
			    break;
			    /* choice six used for print all the user info */
			case e_print_contact:
			    printf("-----------------------------------PRINT CONTACT---------------------------------------\n");
			    print_contact(file);
			    break; 
			    /* choice seven used for exit. */
			case e_exit:
			    if (file->save_flag)
			    {
				printf("ALERT: File not updated!\n");
				printf("ALERT: Do you want to continue(y/n)?\n");
				char conformation_ch = 'n';
				__fpurge(stdin);
				scanf("%c", &conformation_ch);
				if (conformation_ch == 'y' || conformation_ch == 'Y')
				{
				    return e_true;
				}
			    }
			    else
			    {
				return e_true;
			    }
			    break;
			default:
			    printf("Enter the correct choice.\n");
		    }
		}
	    }
	}
    }
    return e_false;
}


/* function open_file used to open the .csv file */
Status open_file(Abk_file *file)
{
    file->input_fptr = fopen(file->input_file, "r");
    if (file->input_fptr == NULL)
    {
	fprintf(stderr,"ERROR: File not opened\n");
	return e_false;
    }
    return e_true;
}

/* function fetch_rec_size used to fetch 
 * how many user info present in .csv   */
Status fetch_rec_size(Abk_file *file)
{
    /* if file empty return success */
    fseek(file->input_fptr, VALUE_ZERO, SEEK_END);
    if(!ftell(file->input_fptr))
    {
	return e_true;
    }

    fseek(file->input_fptr, VALUE_ZERO, SEEK_SET);
    char arr[MAX_SIZE];
    fgets(arr, MAX_SIZE, file->input_fptr);
    file->rec_size = extract_line_count(arr);
    return e_true;
}

/* function allocate_memory_cpy_data used to 
 * allocate memory dynamically and copy 
 * the .csv info into allocated memory 
 */
Status allocate_memory_cpy_data(Abk_file *file)
{

    /* In 2d array allocate column dynamically to store each 1d array address */
    file->record = calloc(file->rec_size, sizeof(char*));
    if (file->record == NULL)
    {
	fprintf(stderr, "Memory not allocated\n");
	return e_false;
    }

    /* To store one line of user data */
    char user_data_one_line[MAX_SIZE];

    /* for fetch data bring file pointer to 0th position */
    fseek(file->input_fptr, VALUE_ZERO, SEEK_SET);

    /* fetch the first line and ignore it bcz it has user count */
    fgets(user_data_one_line, MAX_SIZE, file->input_fptr);

    /* Based on the string size dynamically allocate memory
     * and store fetched data to the allocated memory
     * and store address to the corresponding index 
     */
    for (int i = VALUE_ZERO; i < file->rec_size; i++)
    {
	/* fetch the user data line by line */
	fgets(user_data_one_line, MAX_SIZE, file->input_fptr);

	int string_length = strlen(user_data_one_line);
	
	/* allocate memory */
	file->record[i] = calloc(string_length + VALUE_ONE, sizeof(char));
	
	if (file->record[i] == NULL)
	{    
	    fprintf(stderr, "Memory not allocated\n");
	    return e_false;
	}
	/* copy to record */
	strcpy(file->record[i], user_data_one_line);
    }
    return e_true;
}

/* Function extract_line_count used to fetch how many user data are present */
unsigned int extract_line_count(char *arr)
{
    int sum = VALUE_ZERO, index = VALUE_ONE;

    /* check if the line start with # */
    if (arr[VALUE_ZERO] == '#')
    {
	/* run the loop until reach # */
	while (arr[index] != '#')
	{
	    /* if the element is character '0' to '9' then convert to int */
	    if (arr[index] >= CHAR_ZERO && arr[index] <= CHAR_NINE)
	    {
		sum = (TEN * sum) + (arr[index] - 48);
	    }
	    /* if any other character then generete error */
	    else
	    {
		fprintf(stderr,"Error: Invalid line number\n");
		exit(VALUE_ONE);
	    }
	    index++;
	}
    }
    else
    {
	fprintf(stderr,"ERROR: This csv file is not correct format\n");
	fprintf(stderr,"Usage: First line must contain how many contact present in the address book\n");
	fprintf(stderr,"Ex: #22#\n");
	exit(VALUE_ONE);
    }
    return sum;
}
