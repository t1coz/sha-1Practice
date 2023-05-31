#include "sha.h"
#include "menuInterface.h"
int main(){
    char* message = NULL;
    printf("\nImplementation of SHA-1 algorithm.\n");
    while(1){
        printf("\n\033[0;32mChoose what to do:\033[0m"
               "\n1. Test SHA-1 algorithm;"
               "\n\033[0;31m99. End the program.\033[0m\n"
               "\n\033[0;32mDecision: \033[0m");
        int choice;
        choice = methodOfInput(1);
        if (choice == 99){
            printf("\n\033[0;31mFinishing the program.\n\033[0m");
            free(message);
            return 0;
        }
        printf("Enter the text for hashing: ");
        getStr(&message);
        writeMessageToFile(message);
        tempSHA();
        printf("\n");
    }
}