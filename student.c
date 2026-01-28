#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_NAME "data.bin"

struct Student {
    char name[50];
    int roll_no;
    int age;
    float marks;
};

void add_student(void);
void list_students(void);
void search_student(int roll);

int main() {

    int choice, roll;

    while (1) {
        printf("-------Student Record Management------\n\n");
        printf("1. Add a student\n");
        printf("2. List students\n");
        printf("3. Search a student\n");
        printf("4. Save and Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                list_students();
                break;
            case 3:
                printf("\nEnter the roll number of a student: ");
                scanf("%d", &roll);
                search_student(roll);
                break;
            case 4:
                exit(0);
            default:
                printf("\nInvalid option! Try again.\n\n");
        }
    }
    return 0;
}

void add_student() {

    struct Student s;

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("\nError opening file\n\n");
        return;
    }

    printf("\nEnter roll number: ");
    scanf("%d", &s.roll_no);

    printf("Enter the name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter the age: ");
    scanf("%d", &s.age);

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    printf("\nRecord saved.\n\n");

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
}

void list_students() {

    struct Student s;

    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp) {
        printf("\nRecord not found\n\n");
        return;
    }

    printf("\n\n-------List of Students-------\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%d\t%-15s\t%d\t%.2f%%\n", s.roll_no, s.name, s.age, s.marks);
    }

    printf("\n");

    fclose(fp);
}

void search_student(int roll) {

    struct Student s;
    int found = 0;

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("\nRecord not found\n\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll_no == roll) {
            printf("\nRecord found\n\n");
            printf("Name: %s\n", s.name);
            printf("Roll Number: %d\n", s.roll_no);
            printf("Age: %d\n", s.age);
            printf("Marks: %.2f%%\n\n", s.marks);
            found++;
            break;
        }
    }

    if (!found) 
        printf("\nStudent not found\n\n");

    fclose(fp);
}