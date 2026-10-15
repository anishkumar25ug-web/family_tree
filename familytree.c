
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person *create_person(const char *name, int age) {
    Person *person = malloc(sizeof(Person));

    if (person == NULL) {
        return NULL;
    }

    snprintf(person->name, sizeof(person->name), "%s", name);
    person->age = age;
    person->father = NULL;
    person->mother = NULL;

    return person;
}

void read_person_info(const char *role, char *name_out, int *age_out) {
    printf("Enter name for %s: ", role);

    if (fgets(name_out, 50, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }

    name_out[strcspn(name_out, "\n")] = '\0';

    printf("Enter age for %s: ", role);

    if (scanf("%d", age_out) != 1 || *age_out < 0) {
        printf("Invalid age.\n");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void) {
    const char *roles[7] = {
        "Paternal Grandfather",
        "Paternal Grandmother",
        "Maternal Grandfather",
        "Maternal Grandmother",
        "Father",
        "Mother",
        "Yourself"
    };

    Person *people[7] = {NULL};
    char name[50];
    int age;

    for (int i = 0; i < 7; i++) {
        read_person_info(roles[i], name, &age);

        people[i] = create_person(name, age);

        if (people[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++) {
                free(people[j]);
            }

            return 1;
        }
    }

    printf("\n=== FAMILY MEMBERS ===\n");

    for (int i = 0; i < 7; i++) {
        printf("%s: %s | Age: %d\n",
               roles[i], people[i]->name, people[i]->age);
    }

    for (int i = 0; i < 7; i++) {
        free(people[i]);
    }

    return 0;
}
