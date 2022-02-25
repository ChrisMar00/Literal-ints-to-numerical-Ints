#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1024
char numbers[10][LEN] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};//Numbers array

//Functions prototypes
FILE *openFile(char *mode);
int *literalStringToInt(FILE *fp);
void outputArray(int *arr);

int main(){
    FILE *fp;
    int *arr;

    fp = openFile("r");
    arr = literalStringToInt(fp);
    outputArray(arr);
    return 0;
}

//Opens a file in the user designed mode
FILE *openFile(char *mode){
    char fileName[LEN];
    FILE *fptr;

    printf("Insert file name: ");
    scanf("%s", fileName);
    if((fptr = fopen(fileName, mode)) == NULL){
        printf("Cannot open %s!", fileName);
        exit(EXIT_SUCCESS);
    }

    return fptr;
}

//Reads literal numbers inside of a file and outputs it in array
int *literalStringToInt(FILE *fp){
    char line[LEN];
    int size = 1;
    int *arr = malloc(2 * sizeof(int));//Creates the returning array with 2 starting cells, one for the size of the array and one for the first number
    arr[0] = size;//The first position of the array contains the size of the array

    //Starts by reading the nth line
    while(fgets(line, sizeof(line), fp)){
        int i = 0, newNum = 0;

        //Reads the line until the newline character
        while(line[i] != '\n'){
            int j, k;
            char num[8];

            //If the nth character isn't a space or newline insert it in the num array
            for(j = 0;line[i] != ' ' && line[i] != '\n';i++, j++){
                num[j] = line[i];
            }
            num[j] = '\0';//Creates the string

            //Checks if the read num corresponds to a known number in the numbers array    
            for(k = 0;k < 10;k++){
                if(!strncmp(num, numbers[k], strlen(num))){//If the num corresponds to the number in the nth position of the number array
                    newNum = (k * 10) + (newNum * 10);//Assigns the number to newNum, shifting to left of one position leaving space for the next number
                }
            }
            
            //If the nth character is a space, continue
            if(line[i] == ' ') i++;
        }

        memset(line, 0, sizeof(line));//Sets to NULL the entire line. Without this there would be numbers left in the array so we use this to flush the string
        arr[size++] = newNum / 10;//Sets the nth cell of the array to the newNum divided by 10
        arr[0] = size;//Updates the size of the array
        arr = realloc(arr, (size + 1) * sizeof(int));//Reallocates the array with the new size
    }

    return arr;//Returns the final array
}

//Outputs the array taking in count the fact that the first position is the size of the latter
void outputArray(int *arr){
    int i;

    for(i = 1;i < arr[0];i++){
        printf("%d\n", arr[i]);
    }
}