#include "compare.h"
#include "LinkedList.h"
#include "print.h"
#include <string.h>

int main(void)
{
    LinkedList *ll_str = LinkedList_construct(compare_string, print_string);

    const char *const string = "Hello_World";
    for (size_t i = 1; i <= strlen(string); ++i) {
        char *const temp = (char*) malloc( (i+1) * sizeof(char) ); // The number of chars + 1 for the null terminator
        memcpy( temp, string, i * sizeof(char) ); // Copy the number of chars wanted
        temp[i] = '\0'; //Last index should always be null-terminating char

        ll_str->insert_back(ll_str, strlen(temp) + 1, temp);

        free(temp);
    }

    printf("Printing list\n");
    ll_str->print_list(ll_str);

    bool is_found = ll_str->contains(ll_str, string);
    printf("\nstring was %sfound!\n", (is_found) ? "" : "not ");
    if (is_found) {
        printf("The string is: %s\n",
            (const char*)ll_str->get(ll_str, string)->data);
    }

    LinkedList_destruct(&ll_str);
    return 0;
}
