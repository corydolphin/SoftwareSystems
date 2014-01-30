#include <stdio.h>
#include <stdlib.h>




/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name){
    puts(prompt);
    scanf("%2s", card_name);    
}


void adjust_score(int *count, int val){
    if ((val > 2) && (val < 7)) {
        ++*count;
    } else if (val == 10) {
        --*count;
    }
}


int main()
{
    char card_name[3];
    int count = 0;
    char prompt[] = "Enter a cardname!";

    while ( card_name[0] != 'X'){
        get_card_name(prompt, card_name);

        int val = 0;
        switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        case 'X':
            continue;
        default:
            val = atoi(card_name);
            if((val < 1) || (val > 10)){
                puts("I don't understand that value!");
                continue;
            }
        }

        adjust_score(&count, val);

        printf("Current count: %i\n", count);
    }
    return 0;
}