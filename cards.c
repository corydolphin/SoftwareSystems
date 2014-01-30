/*
    A simple card counting cli interface. Do not use this to count cards,
    you will lose.

    Written by Cory Dolphin for Allen Downey's Software Systems at Olin College, 2014
    No rights reserved.
*/


#include <stdio.h>
#include <stdlib.h>




/* Prompts the user for input, storing the reply in the card_name buffer.

   User input is at most two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name){
    puts(prompt);
    scanf("%2s", card_name);    
}


/* Adjusts the current score according to a newly seen card's value

    count: a pointer to the int where the current count is stored.
    val:   the value of the newly seen card.
*/
void adjust_score(int *count, int val){
    if ((val > 2) && (val < 7)) {
        ++*count;
    } else if (val == 10) {
        --*count;
    }
}

/* Converts a card name to a card value.

    If card_name is 'X', or an unrecognized value, the value -1 is returned.

    card_name: the buffer where the card's name is stored.
*/
int get_card_value(char *card_name){
    int temp_val; //A temporary value used only in the default case

    switch(card_name[0]) {
        case 'K':
        case 'Q': //Face cards King, Queen, Jack all receive the same value
        case 'J':
            return 10;
        case 'A':
            return 11;
        case 'X':
            return -1;
        default:
            temp_val = atoi(card_name);
            if((temp_val < 1) || (temp_val > 10)){ //The card was unrecognized. Print and re-prompt
                puts("I don't understand that value!");
                return -1;
            }
            return temp_val;
        }
}

int main()
{
    char card_name[3];
    int count = 0;
    int card_value;
    char prompt[] = "Enter a cardname!";

    while ( card_name[0] != 'X'){
        get_card_name(prompt, card_name);
        card_value = get_card_value(card_name);

        if(card_value <= -1){ //The card was either unrecognized, or EXIT was requested.
            continue;
        }
        adjust_score(&count, card_value);
        printf("Current count: %i\n", count);
    }
    return 0;
}
