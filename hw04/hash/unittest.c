#include "hash.c"




// Helper function to test string comparison result to an expected result.
//
int test_string_equals_helper(char* s1, char* s2, int expected){
    int result = equal_string(s1,s2);

    if(expected != result){
        printf("Comparing %s==%s, expected %i received: %i\n", s1,s2,expected,result);
        return 1; //error
    }
    return 0;
}

// Helper function to test string comparison result to an expected result.
//
int test_int_equals_helper(int* i1, int* i2, int expected){
    int result = equal_int(i1,i2);

    if(expected != result){
        printf("Comparing %i==%i, expected %i received: %i\n", *i1,*i2,expected,result);
        return 1; //error
    }
    return 0;
}

int test_string_equals(){

    int result = 0;
    char* same1 = "example";
    char* same2 = "example";

    char* diff1 = "xyz";
    char* diff2 = "abc";

    char* empty1 = "";
    char* empty2 = "empty";


    result += test_string_equals_helper(same1,same2,1);
    result += test_string_equals_helper(diff1,diff2,0);
    result += test_string_equals_helper(empty1,empty2,0);
    return result==0;
}


int test_int_equals(){

    int result = 0;
    int one =1;
    int two=2;
    int three=3;


    result += test_int_equals_helper(&three,&three,1);
    result += test_int_equals_helper(&two,&three,0);
    result += test_int_equals_helper(&three,&one,0);
    return result==0;
}

int main ()
{
    int failure = 0; 
    if(!test_string_equals()){
        puts("Failed test_string_equals tests");
        failure +=failure;
    }
    if(!test_int_equals()){
        puts("Failed test_int_equals tests");
        failure +=failure;
    }

    

    return failure;
}