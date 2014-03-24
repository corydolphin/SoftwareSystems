#include "hash.c"



int main ()
{
    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Allen");
    Hashable *hashable3 = make_hashable_int (2);


    puts("::Hashable 1");
    print_hashable(hashable1);
    puts("::Hashable 2");
    print_hashable(hashable2);
    puts("::Hashable 3");
    print_hashable(hashable3);
    // make a list by hand
    puts("====================================");
    Value *value1 = make_int_value (17);
    Node *node1 = make_node(hashable1, value1, NULL);
    puts("::Node1");
    print_node (node1);
    puts("====================================");

    Value *value2 = make_string_value ("Downey");
    Node *list = prepend(hashable2, value2, node1);
    print_list (list);

    puts("====================================");
    // run some test lookups
    Value *value = list_lookup (list, hashable1);
    print_lookup(value);

    value = list_lookup (list, hashable2);
    print_lookup(value);

    value = list_lookup (list, hashable3);
    print_lookup(value);

    puts("====================================");
    // make a map
    Map *map = make_map(10);
    map_add(map, hashable1, value1);
    map_add(map, hashable2, value2);

    printf ("Map\n");
    print_map(map);

    // run some test lookups
    value = map_lookup(map, hashable1);
    print_lookup(value);

    value = map_lookup(map, hashable2);
    print_lookup(value);

    value = map_lookup(map, hashable3);
    print_lookup(value);

    return 0;
}