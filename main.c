#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

// Structure to store marks in 5 subjects
struct Marks
{
    float subject1;
    float subject2;
    float subject3;
    float subject4;
    float subject5;
};

// Student structure
struct Student
{
    int studentID;
    int semester;
    char faculty[11];
    char name[31];
    char gender;
    char address[31];
    long long int phoneNumber;
    int intakeYear;
    struct Marks marks;
} students, temp;

// Global Variables
FILE *f1;
FILE *f2;
char confirm;

// Function to validate Student Information (ID, Phonenumber, Intake Year,)
void isValidInfo(struct Student students)
{
    while (fread(&temp, sizeof(temp), 1, f2))
    {
        if (temp.studentID == students.studentID)
        {
            printf("This ID already exists.\n");
            addStudent();
        }

        else if (students.studentID <= 0 || students.studentID >= 1000)
        {
            printf("ID range does not match.\n");
            addStudent();
        }

        else if (students.semester <= 0 || students.semester >= 8)
        {
            printf("Semester range does not match.\n");
            addStudent();
        }

        else if (temp.phoneNumber == students.phoneNumber)
        {
            printf("Phone Number can't be same.\n");
            addStudent();
        }

        else if (students.phoneNumber < 9700000000 || students.phoneNumber >= 9999999999)
        {
            printf("Phone number cannot be less or exceed 10 digit.\n");
            addStudent();
        }

        else if (students.intakeYear < 2015 || students.intakeYear > 2022)
        {
            printf("Intake Year does not match.\n");
            addStudent();
        }

        else
        {
            return;
        }
    }
}

// Function to check if the marks are valid (between 0 and 100)
bool isValidMarks(struct Marks marks)
{
    return (marks.subject1 >= 0 && marks.subject1 <= 100 && marks.subject2 >= 0 && marks.subject2 <= 100 && marks.subject3 >= 0 && marks.subject3 <= 100 && marks.subject4 >= 0 && marks.subject4 <= 100 && marks.subject5 >= 0 && marks.subject5 <= 100);
}

// Function to add student (case 1)
void addStudent()
{
    f1 = fopen("StudentInfo.txt", "a+");

    if (f1 == NULL)
    {
        printf("Unable to open file.\n");
        exit(1);
    }

    printf("Enter Student ID (1 to 999): ");
    scanf("%d", &students.studentID);

    f2 = fopen("StudentInfo", "r");

    printf("Enter Semester (1 to 8): ");
    scanf("%d", &students.semester);

    // Number paxi Character enter garnu paryo vane use garne
    fflush(stdin);

    printf("Enter Faculty: ");
    scanf("%s", &students.faculty);

    printf("Enter Name: ");
    scanf(" %[^\n]", students.name);

    printf("Enter Gender (M/F): ");
    scanf(" %c", students.gender);

    fflush(stdin);

    printf("Enter Address: ");
    scanf(" %[^\n]", students.address);

    printf("Enter Phone Number (10 Digits): ");
    scanf(" %lld", &students.phoneNumber);

    printf("Enter Intake Year (2015 to 2022): ");
    scanf(" %d", &students.intakeYear);

    isValidInfo(students);

    printf("Enter marks in five subjects: ");
    scanf("%f %f %f %f %f", &students.marks.subject1, &students.marks.subject2, &students.marks.subject3, &students.marks.subject4, &students.marks.subject5);

    if (!isValidMarks(students.marks))
    {
        printf("Invalid marks entered.\n Marks should be between 0 and 100.\n Student not added.\n");
        return;
    }

    fwrite(&students, sizeof(students), 1, f1);

    fflush(stdin);

    printf("Do you want to add another record ? (y/n)\n");
    scanf("%c", &confirm);

    fclose(f1);
    fclose(f2);

    if (confirm == 'y' || confirm == 'Y')
    {
        addStudent();
    }

    printf("Student added successfully!\n");
}

// Function to display details of all students in a tabular format
void showRecords()
{
    f1 = fopen("StudentInfo.txt", "r");

    printf("\n\n-----SHOW RECORDS-----\n\n");

    if (f1 == NULL)
    {
        printf("Unable to open file.");
        exit(1);
    }


    while (fread(&students, sizeof(students), 1, f1))
    {

    float totalMarks = 500;
    float totalMarksObtained = students.marks.subject1 + students.marks.subject2 + students.marks.subject3 + students.marks.subject4 + students.marks.subject5;
    float averageMarks = totalMarksObtained / 5;
    float percentage = (totalMarksObtained / totalMarks) * 100;

        printf("\n ________________________________________\n");
        printf("\n Student ID    : %d", students.studentID);
        printf("\n Name          : %s", students.name);
        printf("\n Semester      : %d", students.semester);
        printf("\n Faculty       : %s", students.faculty);
        printf("\n Address       : %s", students.address);
        printf("\n Phone Number  : %lld", students.phoneNumber);
        printf("\n Joined Year   : %d", students.intakeYear);
        printf("\n Subject 1     : %.2f", students.marks.subject1);
        printf("\n Subject 2     : %.2f", students.marks.subject2);
        printf("\n Subject 3     : %.2f", students.marks.subject3);
        printf("\n Subject 4     : %.2f", students.marks.subject4);
        printf("\n Subject 5     : %.2f", students.marks.subject5);
        printf("\n Total Marks   : %.2f", totalMarksObtained);
        printf("\n Average Marks : %.2f", averageMarks);
        printf("\n Percentage    : %.2f\%", percentage);
        printf("\n ________________________________________\n");
    }
    fclose(f1);
}

int main()
{
    int numStudents = 0;

    int choice = 0;

    do
    {
        // system("cls");
        printf("\n----- WELCOME TO STUDENT GRADING SYSTEM -----\n");
        printf("\n 1. Add Records");
        printf("\n 2. Show Records");
        printf("\n 3. Update Records");
        printf("\n 4. Delete Records");
        printf("\n 5. Exit");

        printf("\n\n Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            addStudent();
            break;

        case 2:
            showRecords();
            break;

        case 3:

            break;

        case 4:

            break;

        case 5:
            printf("\nProgram terminated successfully.");
            break;

        default:
            printf("\nPlease choose the correct options.\n");
            break;
        }
    } while (choice != 5);

    // // Save the student records in "students.dat" file name
    // FILE *file = fopen("students.txt", "a+");
    // if (file)
    // {
    //     fwrite(&students, sizeof(students), 1, file);
    //     fclose(file);
    // }
    // else
    // {
    //     printf("Error opening file to save student records.\n");
    // }

    return 0;
}