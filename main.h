#ifndef MAIN_H
#define MAIN_H


#define ZERO 0
#define ONE  1
#define TWO  2

#define IS_STR_EQUAL(x, y) (strcmp((x), (y)) == 0)

/* enum for returning success and failure */
typedef enum
{
    e_success,
    e_failure
}Status;


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

/* read and validate the cmd line arguments */
Status read_and_validate_args(char*[]);

/* used to call the requied function */
Status address_book(Abk_file*);

#endif
