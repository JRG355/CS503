#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here


int setup_buff(char *buff, char *user_str, int len){

    //TODO: #4:  Implement the setup buff as per the directions
    int user_str_len = 0;
    while (user_str[user_str_len] != '\0') {
        user_str_len++;
    }

    if (user_str_len > len) {
        return -1; // User supplied string is too large
    }

    int i = 0, j = 0;
    int last_was_space = 0;

    while (user_str[i] != '\0' && j < len) {
        // Custom check for whitespace characters
        if (user_str[i] == ' ') {
            if (!last_was_space && j < len - 1) {
                buff[j++] = ' ';
                last_was_space = 1;
            }
        } else {
            buff[j++] = user_str[i];
            last_was_space = 0;
        }
        i++;
    }

    while (j < len) {
        buff[j++] = '.';
    }

    return i; // Return the length of the user supplied string
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int wc = 0;
    int word_start = 0;

    for (int i = 0; i < str_len; i++) { 
	    char current_char = buff[i]; 
	    if (!word_start) { 
		if (current_char == ' ') { 
			continue;
		    }
		    else { 
			wc++; 
			word_start = 1; }
	    } else { 
		    if (current_char == ' ') { 
			    word_start = 0; 
		    } 
	    }
    }
    return wc;
}

void  reverse_string(char *buff, int len, int str_len){
    int end_idx = str_len-1;        
    int start_idx = 0;
    char tmp_char;

    while (end_idx > start_idx) {
	    tmp_char = buff[start_idx];
	    buff[start_idx] = buff[end_idx];
	    buff[end_idx] = tmp_char;

	    start_idx++;
	    end_idx--;
    }

    return;
}

void  word_print(char *str){
    int wc = 0;         //counts words
    int wlen = 0;       //length of current word
    int word_start = 0;    //am I at the start of a new word
    char current_char = str[0];
    int i = 0;
    // Please implement
    while (current_char != '\0') {
	    current_char = str[i];

	    if (!word_start) {
		    if (current_char == ' ') {
			    continue;
		    } else { 
			    wc++;
			    word_start = 1;
			    wlen = 0;
			    printf("%d. ",wc);
		    }
	    }

	    if (word_start) {
		    if (current_char != ' ') { 
			    printf("%c", current_char);
			    wlen++;
		    }

		    if (current_char == ' '|| current_char == '\0') { 
			    printf(" (%d)\n", wlen);
			    word_start = 0;
			    wlen = 0;
		    }
	    }
        i++;
    }
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if argv[1] does not exist?
    //      Because if argv[1] didn't exist, the first test in the if statement would evaluate to true, so the section after the or (||) would be ignored.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      Because if you don't have three arguments, then you don't have a string. You are essentially telling the program what to do, but not what to do it with. 
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    
    buff = malloc(BUFFER_SZ);
    if (buff == NULL){
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;
        case 'r':
            reverse_string(buff, BUFFER_SZ, user_str_len);
            printf("Reversed string: %s\n", buff);
            break;
        case 'w':
            printf("Word Print\n----------\n");
            word_print(buff);
            break;
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          It is good to be safe and make sure we check the buffer size in case we somehow ended up with less than 50 bytes in the buffer.