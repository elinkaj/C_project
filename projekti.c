#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_COURSE_LENGTH 50
#define MAX_GRADES 10

// This is struct for course data
typedef struct {
    char name[MAX_COURSE_LENGTH];
    int grade;
} Course;

// Functions
int isValidCourse(const char *line);
int isValidGrade(const char *line);
void trimWhiteSpace(char *str);

int main() {
    FILE *file = fopen("Cprojekti.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Course courses[MAX_GRADES];
    int numCourses = 0;

    char line[100];
    char studentName[MAX_NAME_LENGTH];
    while (1) {
        printf("Enter student name (or 'stop' to exit): ");
        fgets(studentName, sizeof(studentName), stdin);
        trimWhiteSpace(studentName);

        if (strcmp(studentName, "stop") == 0) {
            break;
        }
        // Printing the student name
        printf("Student: %s\n", studentName);

        // Print courses and grades
        int totalGrade = 0;
        int numTaken;
        int courseAmount = 0;
        rewind(file); // Move file pointer to the beginning of the file
        while (fgets(line, sizeof(line), file) != NULL) {
            trimWhiteSpace(line); // Removing whitespaces

            if (isValidCourse(line)) {
                sscanf(line, "[%[^]:]:%d", courses[numCourses].name, &courses[numCourses].grade);
                numCourses++;
            } else if (isValidGrade(line)) {
                char name[MAX_NAME_LENGTH];
                int grade;
                sscanf(line, "%[^:]:%d", name, &grade);
                if (strcmp(name, studentName) == 0) {
                    printf("Course: %s Grade: %d\n", courses[numCourses - 1].name, grade);
                    totalGrade += grade;
                    numTaken++;
                    courseAmount++;
                }
            }
        }

        // Print the average grade
        if (courseAmount == 0) {
            printf("No courses found for student.\n");
        } else {
            printf("Average grade: %.2f\n", (float)totalGrade / courseAmount);
        }
    }

    fclose(file);
    return 0;
}

// Function to check course line and maximum length
int isValidCourse(const char *line) {
    char course[MAX_COURSE_LENGTH];
    int credits;
    if (sscanf(line, "[%49[^]:]:%d", course, &credits) == 2) {
        return strlen(course) <= MAX_COURSE_LENGTH;
    }
    return 0; // Invalid format
}

// Function to check grade line
int isValidGrade(const char *line) {
    char name[MAX_NAME_LENGTH];
    int grade;
    return sscanf(line, "%[^:]:%d", name, &grade) == 2;
}

// Function to trim whitespace from a string
void trimWhiteSpace(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\n' || str[i] == '\r')) {
        str[i] = '\0';
        i--;
    }
}