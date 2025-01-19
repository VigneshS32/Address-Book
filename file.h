#ifndef FILE_H 
#define FILE_H

/* macro for constants */
#define SUPER_LOOP  1
#define VALUE_ZERO  0
#define VALUE_ONE   1
#define TEN         10
#define MAX_SIZE   500
#define CHAR_ZERO  '0'
#define CHAR_NINE  '9'

/* enum for returning success and failure */
typedef enum
{
    e_true,
    e_false
}Status;

/* enum used to represent user choice*/
enum
{
    e_add_contact =1,
    e_edit_contact,
    e_search_contact,
    e_delete_contact,
    e_save_contact,
    e_print_contact,
    e_exit
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

/* used to call the requied function */
Status address_book(Abk_file*);

/* open the .csv file */
Status open_file(Abk_file*);

/* fetch how many members data are there */
Status fetch_rec_size(Abk_file*);

/* DMA and copy data */
Status allocate_memory_cpy_data(Abk_file*);

/* fetch the line count */
unsigned int extract_line_count(char*);


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

#endif
