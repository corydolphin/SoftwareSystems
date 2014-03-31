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

     g_printf("%s", my_string); 
     g_printf("%d bottles of beer left in the fridge", 5);

     return 0;
}
