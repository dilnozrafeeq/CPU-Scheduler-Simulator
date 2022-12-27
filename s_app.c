#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct process {
    
int burst_time;
int arrival_time;
int priority;
} Process;


void error() {
    printf("Required: -f <input.txt> | -o <output.txt>\n" );
    exit(2);
}
int main (int argc, char *argv []) 


{
//Declarations
    int inputOpt;
    int f_flag =0, o_flag = 0;

    if (argc<4){
        error();
    }
    
    while ((inputOpt = getopt(argc, argv, "f:o:")) != -1 ){

        switch (inputOpt)
        {
        case 'f':
            printf("f: %s\n", optarg);
            f_flag = 1;
            break;
        case 'o':
            printf("o: %s\n", optarg);
            o_flag = 1;
        default:
            printf("Invalid option: %c\n", inputOpt);
            error();
            break;
        }
    }
//  Check if required options are given
   if (!f_flag || !o_flag) {
    printf("Both -f and -o options are required\n");
    error();
}
//   Open input file
FILE *input_file = fopen(optarg, "r");
if (input_file == NULL) {
printf("Error opening input file\n");
return 1;
}

// Read data from file and parse into linked list
Process *head = NULL;
Process *current = NULL;
char line[MAX_LINE_LENGTH];
char *delimiter = ":";
char *token;


while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
// Create new node in linked list
Process *node = malloc(sizeof(Process));
if (head == NULL) {
head = node;
current = head;
} else {
current->next = node;
current = current->next;
}

// Split line into fields and convert to appropriate data types
token = strtok(line, delimiter);
node->burst_time = atoi(token);
token = strtok(NULL, delimiter);
node->arrival_time = atoi(token);
token = strtok(NULL, delimiter);
node->priority = atof(token);
}

// Close input file
fclose(input_file);

return 0;

// Open output file
FILE *output_file = fopen(out_fl, "w");
if (output_file == NULL) {
    printf("Error opening output file\n");
    return 1;
}

// Iterate through linked list and write data to output file
Process *current = head;
while (current != NULL) {
    fprintf(output_file, "%d:%d:%d\n", current->burst_time, current->arrival_time, current->priority);
    current = current->next;
}

// Close output file
fclose(output_file);

}
}
