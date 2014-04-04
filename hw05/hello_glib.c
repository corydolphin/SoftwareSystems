/*
Hello World for Glib!

*/

#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>

int main() {
     GHashTable *my_table = g_hash_table_new(NULL,NULL);
     GString *my_string = g_string_new("Hello world");
     gint my_int = 42;
     g_hash_table_insert(my_table, &my_int, my_string);

     GString *result = g_hash_table_lookup(my_table,&my_int);
     g_printf("%s\n", my_string->str); 
     g_printf("The solution to life is %s", result->str);

     return 0;
}
