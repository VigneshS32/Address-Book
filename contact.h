#ifndef CONTACT_H
#define CONTACT_H

#define INIT_ZERO  		0
#define INDEX_ZERO 		0
#define LENGTH_ZERO 		0
#define LOOP_END   		0
#define FALSE   		0
#define MIN_CHOICE              0
#define TRUE    		1
#define WHILE_ONE  		1
#define MINUS_ONE               1
#define PLUS_ONE                1
#define INDEX_PLUS_ONE  	1
#define IS_EQUAL_ONE    	1
#define INDEX_ONE               1
#define INDEX_MINUS_ONE 	1
#define FIRST_DATA_FIELD        1
#define SECOND_DATA_FIELD       2
#define INDEX_TWO               2
#define INDEX_THREE             3
#define THIRD_DATA_FIELD        3
#define FORTH_DATA_FIELD        4
#define SIZE_OF_PTR_TO_ARRAY  	4
#define MAX_CHOICE              4
#define MOBILE_LENGTH 		10
#define MAX_SIZE   		500 
#define CHAR_ZERO  		'0'
#define CHAR_NINE  		'9'
#define COMMA      		','
#define CHAR_NUL   		'\0'
#define NEWLINE    		'\n'


/* enum for returning success and failure */
typedef enum
{
    success,
    failure
}Status;


/* enum choice for add_data */
enum
{
    e_mobile_no = 1,
    e_email,
    e_location,
    e_exit
};

/* enum choice for edit_data */
enum
{
    edit_name = 1,
    edit_mobile_no,
    edit_email,
    edit_location,
    edit_exit
};

/* enum choice for search_data */
enum
{
    search_name = 1,
    search_mobile_no,
    search_email,
    search_location,
};


/* struct used to handle the .csv file data */
typedef struct file
{
    /* members used to handle .csv file */
    char *input_file;
    FILE *input_fptr;
 
    /* members used to handle .csv file data */
    int rec_size;
    char **record;

    /* members used to point the record index in search function */
    int search_ind;
    int *search_rec;

    /* save_flag represent the file is updated or not */
    int save_flag;

}Abk_file;


/* function declarations */

/* To add the contact */
Status add_contact(Abk_file *);

/* To edit the contact */
Status edit_contact(Abk_file *);

/* To search the contact */
Status search_contact(Abk_file *);

/* To delete the contact */
Status delete_contact(Abk_file *);

/* To save the contact */
Status save_contact(Abk_file *);

/* To print the contact */
Status print_contact(Abk_file *);

/* To extract the field */
char *get_field(char *, int );

/* To check if the name present in the abk */
Status check_name(const char *, Abk_file *file);

/* To check if the mobile number is valid */
Status check_mobile(char *);

/* To check if the email is valid*/
Status check_email(char *);

#endif
