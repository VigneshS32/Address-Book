/*
 * Project      : Address book    
 * Name         : Vignesh S
 * Date         : OCT 03 2024
 * Description  : Address book is an application to store and query contacts. 
 *	      	  Fuction implemented in this file: 
 * 			1. main function
 *			2. read and validate arguments
 */ 

 
#include <stdio.h>
#include <string.h>
#include "main.h"
#define DEFAULT_FILENAME "address.csv"
 

/* main function */
int main(int argc, char *argv[])
{
    /* If no arguments are provided, set default filename */
    if (argc == 1) 
    {
        argv[ONE] = DEFAULT_FILENAME;  // Set the default file name
        argc = TWO;  // Update argument count to reflect default file
    }

    /* Validate the arguments */
    if (argc == TWO && !read_and_validate_args(argv))
    {
        printf("----------------------------------------------\n");
        printf("                   Address Book\n");
        printf("----------------------------------------------\n");
        
        /* Struct variable to handle files and data */
        Abk_file file = {NULL, NULL, ZERO, NULL, ZERO, NULL, ZERO};
        file.input_file = argv[ONE];

        /* Call the address_book function and allow the user to modify the data */
        address_book(&file);
    }
    else
    {
        /* Else generate the error message */
        fprintf(stderr, "Error: Invalid Arguments\n");
        fprintf(stderr, "Usage: ./a.out [input.csv]\n");
        return e_failure;
    }
    return e_success;
}

/* Function used to read and validate the arguments */ 
Status read_and_validate_args(char *argv[]) 
{
    /* File must have .csv extension */
    char *fetch_dot_address = strstr(argv[ONE], ".");
    if (fetch_dot_address != NULL && IS_STR_EQUAL(fetch_dot_address, ".csv"))
    {
        return e_success;
    }
    return e_failure;
}
