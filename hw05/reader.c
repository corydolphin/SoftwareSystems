/*
Hello World for Glib!

*/

#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>


// Read our file into memory.
// Since the text file is so small, it can easily fit in memory.
gchar *get_file_contents(){
    GError *err = NULL;
    GMappedFile *infile = g_mapped_file_new("monte_cristo.txt",FALSE,&err);
    if (err != NULL)
    {
        /* Report error to user, and free error */
        fprintf (stderr, "Unable to read file: %s\n", err->message);
        g_error_free (err);
        exit(1);
    }
    return g_mapped_file_get_contents(infile);
}

// Compile our regular expression, handling errors.
GRegex *get_regex(){
    GError *err = NULL;
    // Matches one or more non-word characters
    GRegex *word_regex = g_regex_new("\\W+", G_REGEX_OPTIMIZE, 0, &err);
    if (err != NULL)
    {
        /* Report error to user, and free error */
        fprintf (stderr, "Unable to compile regex: %s\n", err->message);
        g_error_free (err);
        exit(1);
    }
    return word_regex;
}

// Increments our histogram when a word is seen
//
void increment_table(GHashTable *table, gchar* word){
    gint *count = g_hash_table_lookup(table,word);

    if(count==NULL){ // first time seeing a word
        count = g_malloc(sizeof(gint));
        *count = 1;
        g_hash_table_insert(table,word,count);
    }
    else{
        *count+=1;
    }
}

// Prints a key,value pair from the key, looking up the value in
// the `table`
void print_from_key(gpointer key, gpointer table){
    printf("%s -> %d\n", (gchar*)key, *(int*)g_hash_table_lookup(table,key));
}

gint _compare_key(gconstpointer word1,
                 gconstpointer word2,
                 gpointer table){
    int *val1 = g_hash_table_lookup(table,word1);
    int *val2 = g_hash_table_lookup(table,word2);

    g_assert(val1 != NULL);
    g_assert(val2 != NULL);
   
    return *val1 - *val2; // After disucssing with noam, no need to return -1 or 1. Any postivie/negative value is chill
}

// Prints a GHashTable sorted by value
void print_sorted_by_value(GHashTable *table){
    GList *keys = g_hash_table_get_keys(table);
    GList *sorted = g_list_sort_with_data(keys, _compare_key, table);
    g_list_foreach (sorted, print_from_key, table);
}

// Splits a string on a given regex handling errors and 
// exiting in the case of failure.
gchar **get_words(gchar* contents, GRegex* reg){
    GError *err = NULL;
    gchar **words = g_regex_split(reg, contents, G_REGEX_MATCH_NEWLINE_ANY);
    if (err != NULL)
    {
        /* Report error to user, and free error */
        fprintf (stderr, "Unable to split words: %s\n", err->message);
        g_error_free (err);
        exit(1);
    }
    return words;

}

int main() {
    GHashTable *my_table = g_hash_table_new(g_str_hash,g_str_equal);
    gchar **words = get_words(get_file_contents(),get_regex());

    for(int i = 0; words[i] != NULL; i++)
    {
        increment_table(my_table,words[i]);
    }

    print_sorted_by_value(my_table);
    return 0;
}
