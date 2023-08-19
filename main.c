#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

// Structure to store marks in 5 subjects
struct Marks
{
    float subject1;
    float subject2;
    float subject3;
    float subject4;
    float subject5;
    char subject1Name[30];
    char subject2Name[30];
    char subject3Name[30];
    char subject4Name[30];
    char subject5Name[30];
    float gpa1;
    float gpa2;
    float gpa3;
    float gpa4;
    float gpa5;
    float totalGpa;
    float percentage;
    float averageMarks;
    float totalMarksObtained;
};

// Student structure
struct Student
{
    int studentID;
    int semester;
    char faculty[10];
    char name[30];
    char gender;
    char address[50];
    long long int phoneNumber;
    int intakeYear;
    struct Marks marks[8];
} students, temp;

// Global Variables
FILE *f1;
FILE *f2;
char confirm;
float totalMarks = 500;

// Function for login (first to get called)
void loginInfo()
{
    system("cls");

    char username[8], password[8], c;

    int i = 0;

    printf("\n\n________________ LOGIN PAGE ________________\n\n");

    printf("Enter your Username: \n");
    scanf("%s", username);

    printf("Enter your Password: \n");

    while (true)
    {
        c = getch();

        // check if Enter key is pressed
        if (c == '\r' || c == '\n')
        {
            break;
        }

        // Display a '*' instead of the character typed by user
        putchar('*');

        password[i++] = c;
    }

    password[i] = '\0';

    printf("\n");

    // Check if the entered username and password match the predefined values (Compares ASCII value difference)
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        printf("Login successful!\n");
        printf("Press any key to goto the next page.\n");
        getch();
        mainMenu();
    }

    else
    {
        printf("Login failed. Invalid username or password.\n");
        printf("Press any key to continue.\n");
        getch();

        loginInfo();
    }
}

// Function to display main menu
void mainMenu()
{
    int choice = 0;

    system("cls");

    do
    {
        printf("\n\n________________WELCOME TO STUDENT GRADING SYSTEM ________________\n\n");
        printf("\n 1. Add  New Records");
        printf("\n 2. Update Previous Records");
        printf("\n 3. Show All Records");
        printf("\n 4. Search Records");
        printf("\n 5. Edit Records");
        printf("\n 6. Delete Records");
        printf("\n 7. Delete All Records");
        printf("\n 8. Exit");

        printf("\n\nPlease enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            addStudentNew();
            break;

        case 2:
            updateStudentPrevious();
            break;

        case 3:
            showRecords();
            break;

        case 4:
            searchStudent();
            break;

        case 5:
            editStudent();
            break;

        case 6:
            deleteStudentRecord();
            break;

        case 7:
            deleteAllRecords();
            break;

        case 8:
            exitProject();
            break;

        default:
            printf("\nPlease choose the correct options.\n");
            getch();
            printf("Press any key to continue.\n");
            break;
        }

    } while (1);
}

// Function to calculate marks to GPA
float marksToGpa(float marks)
{
    float gpa;

    if (marks <= 100 && marks > 90)
    {
        gpa = 4.0;
        return gpa;
    }
    else if (marks <= 90 && marks > 80)
    {
        gpa = 3.6;
        return gpa;
    }
    else if (marks <= 80 && marks > 70)
    {
        gpa = 3.2;
        return gpa;
    }
    else if (marks <= 70 && marks > 60)
    {
        gpa = 2.8;
        return gpa;
    }
    else if (marks <= 60 && marks > 50)
    {
        gpa = 2.4;
        return gpa;
    }
    else if (marks <= 50 && marks > 40)
    {
        gpa = 2.0;
        return gpa;
    }
    else if (marks <= 40 && marks > 30)
    {
        gpa = 1.6;
        return gpa;
    }
    else if (marks <= 30 && marks > 20)
    {
        gpa = 1.2;
        return gpa;
    }
    else
    {
        gpa = 0.8;
        return gpa;
    }
}

// Function to add new student records (case 1)
void addStudentNew()
{
    printf("\n\n________________ADD RECORDS________________\n\n");

    f1 = fopen("StudentInfo.txt", "a+");

    if (f1 == NULL)
    {
        printf("Unable to open file.\n");
        exit(1);
    }

labelStudentID:

    printf("Enter Student ID (1 to 999): ");
    scanf("%d", &students.studentID);

    f2 = fopen("StudentInfo.txt", "r");

    if (students.studentID <= 0 || students.studentID >= 1000)
    {
        printf("Please enter in the range from 1 to 999.\n");

        goto labelStudentID;
    }

    while (fread(&temp, sizeof(temp), 1, f2))
    {
        if (students.studentID == temp.studentID)
        {
            printf("\nStudent ID already exits.\n");

            fclose(f2);

            goto labelStudentID;
        }
    }

    fclose(f2);

    students.semester = 1;

    // Number paxi Character enter garnu paryo vane use garne
    fflush(stdin);

    printf("Enter Faculty: ");
    scanf("%s", &students.faculty);
    strupr(students.faculty);

labelName:

    printf("Enter Name: ");
    scanf(" %[^\n]", students.name);
    strupr(students.name);

    for (int i = 0; students.name[i] != '\0'; i++)
    {
        if ((students.name[i] >= 65 && students.name[i] <= 90) || (students.name[i] >= 97 && students.name[i] <= 122) || students.name[i] == ' ')
        {
            continue;
        }

        else
        {
            printf("Please do not enter any digits or symbols.\n");
            goto labelName;
        }
    }

labelGender:

    fflush(stdin);

    printf("Enter Gender (M/F): ");
    scanf("%c", &students.gender);

    if (students.gender == 'M' || students.gender == 'm' || students.gender == 'F' || students.gender == 'f')
    {
    }
    else
    {
        printf("Please enter (M or F).\n");
        goto labelGender;
    }

    fflush(stdin);

    printf("Enter Address: ");
    scanf(" %[^\n]", students.address);
    strupr(students.address);

labelPhoneNumber:

    printf("Enter Phone Number (10 Digits): ");
    scanf(" %lld", &students.phoneNumber);

    if (students.phoneNumber >= 9700000000 && students.phoneNumber < 10000000000)
    {
    }
    else
    {
        printf("Please enter your correct phone number.\n");
        goto labelPhoneNumber;
    }

labelIntakeYear:

    printf("Enter Intake Year (2015 to 2022): ");
    scanf(" %d", &students.intakeYear);

    if (students.intakeYear > 2015 && students.intakeYear <= 2022)
    {
    }
    else
    {
        printf("Please enter in the correct range.\n");
        goto labelIntakeYear;
    }

    int i = students.semester - 1;

    fflush(stdin);

    printf("Enter the name of 1st subject.\n");
    scanf("%[^\n]", &students.marks[i].subject1Name);
    strupr(students.marks[i].subject1Name);

    fflush(stdin);

    printf("Enter the name of 2nd subject.\n");
    scanf("%[^\n]", &students.marks[i].subject2Name);
    strupr(students.marks[i].subject2Name);

    fflush(stdin);

    printf("Enter the name of 3rd subject.\n");
    scanf("%[^\n]", &students.marks[i].subject3Name);
    strupr(students.marks[i].subject3Name);

    fflush(stdin);

    printf("Enter the name of 4th subject.\n");
    scanf("%[^\n]", &students.marks[i].subject4Name);
    strupr(students.marks[i].subject4Name);

    fflush(stdin);

    printf("Enter the name of 5th subject.\n");
    scanf("%[^\n]", &students.marks[i].subject5Name);
    strupr(students.marks[i].subject5Name);

labelMarks:
    printf("Enter your marks of semester %d.\n", i + 1);

    printf("Enter marks in five subject : ");
    scanf("%f %f %f %f %f",
          &students.marks[i].subject1,
          &students.marks[i].subject2,
          &students.marks[i].subject3,
          &students.marks[i].subject4,
          &students.marks[i].subject5);

    if (students.marks[i].subject1 >= 0 &&
        students.marks[i].subject1 <= 100 &&
        students.marks[i].subject2 >= 0 &&
        students.marks[i].subject2 <= 100 &&
        students.marks[i].subject3 >= 0 &&
        students.marks[i].subject3 <= 100 &&
        students.marks[i].subject4 >= 0 &&
        students.marks[i].subject4 <= 100 &&
        students.marks[i].subject5 >= 0 &&
        students.marks[i].subject5 <= 100)
    {
    }

    else
    {
        printf("Invalid marks entered.\nMarks should be between 0 and 100.\nStudent record was not added.\n");
        goto labelMarks;
    }

    students.marks[i].totalMarksObtained = students.marks[i].subject1 + students.marks[i].subject2 + students.marks[i].subject3 + students.marks[i].subject4 + students.marks[i].subject5;
    students.marks[i].averageMarks = students.marks[i].totalMarksObtained / 5;
    students.marks[i].percentage = (students.marks[i].totalMarksObtained / totalMarks) * 100;

    students.marks[i].gpa1 = marksToGpa(students.marks[i].subject1);
    students.marks[i].gpa2 = marksToGpa(students.marks[i].subject2);
    students.marks[i].gpa3 = marksToGpa(students.marks[i].subject3);
    students.marks[i].gpa4 = marksToGpa(students.marks[i].subject4);
    students.marks[i].gpa5 = marksToGpa(students.marks[i].subject5);

    students.marks[i].totalGpa = (students.marks[i].gpa1 + students.marks[i].gpa2 + students.marks[i].gpa3 + students.marks[i].gpa4 + students.marks[i].gpa5) / 5;

    fwrite(&students, sizeof(students), 1, f1);

    fflush(stdin);

    printf("Do you want to add another record ? (y/n)\n");
    scanf("%c", &confirm);

    fclose(f1);
    fclose(f2);

    if (confirm == 'y' || confirm == 'Y')
    {
        addStudentNew();
    }

    printf("Student added successfully!\n");
}

// Function to add new marks for new semester for the existing student ID (case 2)
void updateStudentPrevious()
{
    int studentID, semester, matched = 0;

    printf("\n\n________________UPDATE SEMESTER RECORDS________________\n\n");

    printf("Enter Student ID.\n");
    scanf("%d", &studentID);

    f1 = fopen("StudentInfo.txt", "r");
    f2 = fopen("temp.txt", "w+");

    while (fread(&students, sizeof(students), 1, f1))
    {
        if (studentID == students.studentID)
        {
            matched = 1;
            break;
        }
    }

    if (matched == 0)
    {
        printf("Student ID not found.\n");
        updateStudentPrevious();
    }

    rewind(f1);

    while (fread(&students, sizeof(students), 1, f1))
    {
        if (students.semester + 1 > 8)
        {
            printf("\nNo more semesters can be added.\n ");
            printf("\nPress any key to contiinue ");

            getch();

            mainMenu();
        }

        if (studentID == students.studentID)
        {
            students.semester = students.semester + 1;

            printf("You are adding in %d semester.\n", students.semester);

            int i = students.semester - 1;

            fflush(stdin);

            printf("Enter the name of 1st subject.\n");
            scanf("%[^\n]", &students.marks[students.semester - 1].subject1Name);

            fflush(stdin);

            printf("Enter the name of 2nd subject.\n");
            scanf("%[^\n]", &students.marks[students.semester - 1].subject2Name);

            fflush(stdin);

            printf("Enter the name of 3rd subject.\n");
            scanf("%[^\n]", &students.marks[students.semester - 1].subject3Name);

            fflush(stdin);

            printf("Enter the name of 4th subject.\n");
            scanf("%[^\n]", &students.marks[students.semester - 1].subject4Name);

            fflush(stdin);

            printf("Enter the name of 5th subject.\n");
            scanf("%[^\n]", &students.marks[students.semester - 1].subject5Name);

        updateLabelMarks:

            printf("Enter your marks of semester %d.\n", i + 1);

            printf("Enter marks in five subject : ");
            scanf("%f %f %f %f %f",
                  &students.marks[i].subject1,
                  &students.marks[i].subject2,
                  &students.marks[i].subject3,
                  &students.marks[i].subject4,
                  &students.marks[i].subject5);

            if (students.marks[i].subject1 >= 0 &&
                students.marks[i].subject1 <= 100 &&
                students.marks[i].subject2 >= 0 &&
                students.marks[i].subject2 <= 100 &&
                students.marks[i].subject3 >= 0 &&
                students.marks[i].subject3 <= 100 &&
                students.marks[i].subject4 >= 0 &&
                students.marks[i].subject4 <= 100 &&
                students.marks[i].subject5 >= 0 &&
                students.marks[i].subject5 <= 100)
            {
            }

            else
            {
                printf("Invalid marks entered.\nMarks should be between 0 and 100.\nStudent record was not added.\n");
                goto updateLabelMarks;
            }

            students.marks[i].totalMarksObtained = students.marks[i].subject1 + students.marks[i].subject2 + students.marks[i].subject3 + students.marks[i].subject4 + students.marks[i].subject5;
            students.marks[i].averageMarks = students.marks[i].totalMarksObtained / 5;
            students.marks[i].percentage = (students.marks[i].totalMarksObtained / totalMarks) * 100;

            students.marks[i].gpa1 = marksToGpa(students.marks[i].subject1);
            students.marks[i].gpa2 = marksToGpa(students.marks[i].subject2);
            students.marks[i].gpa3 = marksToGpa(students.marks[i].subject3);
            students.marks[i].gpa4 = marksToGpa(students.marks[i].subject4);
            students.marks[i].gpa5 = marksToGpa(students.marks[i].subject5);

            students.marks[i].totalGpa = (students.marks[i].gpa1 + students.marks[i].gpa2 + students.marks[i].gpa3 + students.marks[i].gpa4 + students.marks[i].gpa5) / 5;

            fwrite(&students, sizeof(students), 1, f2);
        }

        else
        {
            fwrite(&students, sizeof(students), 1, f2);
        }
    }

    fclose(f1);
    fclose(f2);

    remove("StudentInfo.txt");
    rename("temp.txt", "StudentInfo.txt");

    fflush(stdin);

    printf("Do you want to update another record ? (y/n)\n");
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        updateStudentPrevious();
    }

    printf("Student updated successfully!\n");
}

// Function to display details of all students (case 3)
void showRecords()
{
    int size = 0;
    f1 = fopen("StudentInfo.txt", "r");

    printf("\n\n________________SHOW RECORDS________________\n\n");

    if (f1 == NULL)
    {
        printf("Unable to open file.");
        exit(1);
    }

    while (fread(&students, sizeof(students), 1, f1))
    {
        printf("\n ________________________________________\n");
        printf("\n Student ID    \t: %d", students.studentID);
        printf("\n Name          \t: %s", students.name);
        printf("\n Faculty       \t: %s", students.faculty);
        printf("\n Address       \t: %s", students.address);
        printf("\n Phone Number  \t: %lld", students.phoneNumber);
        printf("\n Joined Year   \t: %d", students.intakeYear);
        printf("\n");

        for (int i = 0; i < students.semester; i++)
        {
            printf("\n              Semester : %d", i + 1);
            printf("\nSubject Name    | Marks \t GPA ");
            printf("\n %-15s: %.2f \t %.2f", students.marks[i].subject1Name, students.marks[i].subject1, students.marks[i].gpa1);
            printf("\n %-15s: %.2f", students.marks[i].subject2Name, students.marks[i].subject2);
            printf("\n %-15s: %.2f", students.marks[i].subject3Name, students.marks[i].subject3);
            printf("\n %-15s: %.2f", students.marks[i].subject4Name, students.marks[i].subject4);
            printf("\n %-15s: %.2f", students.marks[i].subject5Name, students.marks[i].subject5);

            // printf("\n ", "Gpa 1", );
            printf("\n %-15s: %.2f", "Gpa 2", students.marks[i].gpa2);
            printf("\n %-15s: %.2f", "Gpa 3", students.marks[i].gpa3);
            printf("\n %-15s: %.2f", "Gpa 4", students.marks[i].gpa4);
            printf("\n %-15s: %.2f", "Gpa 5", students.marks[i].gpa5);

            // printf("\n Gpa 1         : %.2f", students.marks[i].gpa1);
            // printf("\n Gpa 2         : %.2f", students.marks[i].gpa2);
            // printf("\n Gpa 3         : %.2f", students.marks[i].gpa3);
            // printf("\n Gpa 4         : %.2f", students.marks[i].gpa4);
            // printf("\n Gpa 5         : %.2f", students.marks[i].gpa5);

            printf("\n Total Marks   \t: %.2f", students.marks[i].totalMarksObtained);
            printf("\n Total GPA     \t: %.2f", students.marks[i].totalGpa);
            printf("\n Percentage    \t: %.2f %%", students.marks[i].percentage);
            printf("\n ________________________________________\n");
        }
    }

    fclose(f1);
}

// Function to search student records (case 4)
void searchStudent()
{
    int studentID, semester, matched = 0;

    f1 = fopen("StudentInfo.txt", "r");

    printf("\n\n________________SEARCH RECORDS________________\n\n");

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    while (fread(&students, sizeof(students), 1, f1) > 0)
    {
        if (students.studentID == studentID)
        {
            printf("\nSudent's record found.\n");

            printf("\nEnter Semester you want to find: ");
            scanf("%d", &semester);

            int i = semester - 1;

            printf("\n ________________________________________\n");
            printf("\n Student ID    : %d", students.studentID);
            printf("\n Name          : %s", students.name);
            printf("\n Faculty       : %s", students.faculty);
            printf("\n Address       : %s", students.address);
            printf("\n Phone Number  : %lld", students.phoneNumber);
            printf("\n Joined Year   : %d", students.intakeYear);
            printf("\n Semester      : %d", semester);
            printf("\n");
            printf("\n %-15s         : %.2f", students.marks[i].subject1Name, students.marks[i].subject1);
            printf("\n %-15s         : %.2f", students.marks[i].subject2Name, students.marks[i].subject2);
            printf("\n %-15s         : %.2f", students.marks[i].subject3Name, students.marks[i].subject3);
            printf("\n %-15s         : %.2f", students.marks[i].subject4Name, students.marks[i].subject4);
            printf("\n %-15s         : %.2f", students.marks[i].subject5Name, students.marks[i].subject5);
            printf("\n Gpa 1         : %.2f", students.marks[i].gpa1);
            printf("\n Gpa 2         : %.2f", students.marks[i].gpa2);
            printf("\n Gpa 3         : %.2f", students.marks[i].gpa3);
            printf("\n Gpa 4         : %.2f", students.marks[i].gpa4);
            printf("\n Gpa 5         : %.2f", students.marks[i].gpa5);
            printf("\n Total Marks   : %.2f", students.marks[i].totalMarksObtained);
            printf("\n Total GPA     : %.2f", students.marks[i].totalGpa);
            printf("\n Percentage    : %.2f %%", students.marks[i].percentage);
            printf("\n ________________________________________\n");

            matched = 1;
        }
    }

    if (matched == 0)
    {
        printf("\nStudent record not found.\n");
    }

    fclose(f1);
}

// Function to edit student record (case 5)
void editStudent()
{
    int studentID, matched = 0, size = 0;

    printf("\n\n________________EDIT RECORDS________________\n\n");

    f1 = fopen("StudentInfo.txt", "r");

    f2 = fopen("temp.txt", "w+");

    printf("Enter the student ID to edit.\n");
    scanf("%d", &studentID);

    while (fread(&students, sizeof(students), 1, f1))
    {
        if (studentID == students.studentID)
        {
            matched = 1;
            break;
        }
    }

    if (matched == 0)
    {
        printf("Student ID not found.\n");
        mainMenu();
    }

    rewind(f1);

    while (fread(&students, sizeof(students), 1, f1) > 0)
    {
        if (students.studentID == studentID)
        {
            matched = 1;
            printf("Student ID found.\n");

        labelName:

            printf("Enter Name: ");
            scanf(" %[^\n]", students.name);

            for (int i = 0; students.name[i] != '\0'; i++)
            {
                if ((students.name[i] >= 65 && students.name[i] <= 90) || (students.name[i] >= 97 && students.name[i] <= 122) || students.name[i] == ' ')
                {
                    continue;
                }

                else
                {
                    printf("Please do not enter any digits or symbols.\n");
                    goto labelName;
                }
            }

        labelGender:

            fflush(stdin);

            printf("Enter edited Gender (M/F): ");
            scanf("%c", &students.gender);

            if (students.gender == 'M' || students.gender == 'm' || students.gender == 'F' || students.gender == 'f')
            {
            }
            else
            {
                printf("Please enter (M or F).\n");
                goto labelGender;
            }

            fflush(stdin);

            printf("Enter edited Address: ");
            scanf(" %[^\n]", students.address);

        labelPhoneNumber:

            printf("Enter edited Phone Number (10 Digits): ");
            scanf(" %lld", &students.phoneNumber);

            if (students.phoneNumber >= 9700000000 && students.phoneNumber < 10000000000)
            {
            }
            else
            {
                printf("Please enter your correct phone number.\n");
                goto labelPhoneNumber;
            }

        labelIntakeYear:

            printf("Enter edited Intake Year (2015 to 2022): ");
            scanf(" %d", &students.intakeYear);

            if (students.intakeYear > 2015 && students.intakeYear <= 2022)
            {
            }
            else
            {
                printf("Please enter in the correct range.\n");
                goto labelIntakeYear;
            }

            int i = students.semester - 1;

        labelMarks:
            printf("Enter your edited marks of semester %d.\n", i + 1);

            printf("Enter marks in five subject : ");
            scanf("%f %f %f %f %f",
                  &students.marks[i].subject1,
                  &students.marks[i].subject2,
                  &students.marks[i].subject3,
                  &students.marks[i].subject4,
                  &students.marks[i].subject5);

            if (students.marks[i].subject1 >= 0 &&
                students.marks[i].subject1 <= 100 &&
                students.marks[i].subject2 >= 0 &&
                students.marks[i].subject2 <= 100 &&
                students.marks[i].subject3 >= 0 &&
                students.marks[i].subject3 <= 100 &&
                students.marks[i].subject4 >= 0 &&
                students.marks[i].subject4 <= 100 &&
                students.marks[i].subject5 >= 0 &&
                students.marks[i].subject5 <= 100)
            {
            }

            else
            {
                printf("Invalid marks entered.\nMarks should be between 0 and 100.\nStudent record was not added.\n");
                goto labelMarks;
            }

            students.marks[i].totalMarksObtained = students.marks[i].subject1 + students.marks[i].subject2 + students.marks[i].subject3 + students.marks[i].subject4 + students.marks[i].subject5;
            students.marks[i].averageMarks = students.marks[i].totalMarksObtained / 5;
            students.marks[i].percentage = (students.marks[i].totalMarksObtained / totalMarks) * 100;

            students.marks[i].gpa1 = marksToGpa(students.marks[i].subject1);
            students.marks[i].gpa2 = marksToGpa(students.marks[i].subject2);
            students.marks[i].gpa3 = marksToGpa(students.marks[i].subject3);
            students.marks[i].gpa4 = marksToGpa(students.marks[i].subject4);
            students.marks[i].gpa5 = marksToGpa(students.marks[i].subject5);

            students.marks[i].totalGpa = (students.marks[i].gpa1 + students.marks[i].gpa2 + students.marks[i].gpa3 + students.marks[i].gpa4 + students.marks[i].gpa5) / 5;

            fwrite(&students, sizeof(students), 1, f2);
        }

        else
        {
            fwrite(&students, sizeof(students), 1, f2);
        }
    }

    fclose(f1);
    fclose(f2);

    remove("StudentInfo.txt");
    rename("temp.txt", "StudentInfo.txt");

    fflush(stdin);

    printf("Do you want to edit another record ? (y/n)\n");
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        editStudent();
    }

    printf("Student edited successfully!\n");
}

// Function to delete student's record (case 6)
void deleteStudentRecord()
{
    int studentID, matched = 0, size;
    char confirm;

    f1 = fopen("StudentInfo.txt", "r");
    f2 = fopen("temp.txt", "w");

    printf("\n\n________________DELETE RECORDS________________\n\n");

    if (NULL != f1)
    {
        fseek(f1, 0, SEEK_END);
        size = ftell(f1);

        if (0 == size)
        {
            printf("No records found in file.\nPlease add records to delete.\n");
            printf("Press any key to continue.\n");

            getch();

            mainMenu();
        }
    }

    // if (f1 == NULL)
    // {
    //     printf("Unable to open file.\n");
    //     exit(0);
    // }

    fseek(f1, 0, SEEK_SET);

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    fflush(stdin);

    printf("Are you sure you want to delete the record for Student ID %d? (Y/N): ", studentID);
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y')
    {
        while (fread(&students, sizeof(students), 1, f1))
        {
            if (students.studentID == studentID)
            {
                matched = 1;
            }
            else
            {
                fwrite(&students, sizeof(students), 1, f2);
            }
        }

        fclose(f1);
        fclose(f2);

        if (!matched)
        {
            printf("\nStudent ID of %d not found.", studentID);
        }

        if (matched)
        {
            remove("StudentInfo.txt");
            rename("temp.txt", "StudentInfo.txt");

            printf("\nRecord deleted succesfully\n");
        }
    }

    else
    {
        printf("\nRecord deletion aborted.\n");
    }
}

// Function to delete all records (case 7)
void deleteAllRecords()
{
    char confirm;

    fflush(stdin);

    printf("Do you wish to delete all records (y/n) ?\n");
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        remove("StudentInfo.txt");
        printf("All Records Deleted.\n");
    }

    else
    {
        printf("Your records are safe.\n");

        printf("Press any key to continue.\n");

        getch();

        mainMenu();
    }
}

// Function to exit project (case 8)
void exitProject()
{
    system("cls");
    int i;
    char thankYou[100] = "--------- Thank You For Using This Software ---------\n";
    char end[100] = ("--------- Program terminated successfully. ---------");

    for (i = 0; i < strlen(thankYou); i++)
    {
        printf("%c", thankYou[i]);
        Sleep(35);
    }

    for (i = 0; i < strlen(end); i++)
    {
        printf("%c", end[i]);
        Sleep(30);
    }

    exit(0);
}

// Main function (Entry point)
int main()
{
    system("cls");

    loginInfo();

    return 0;
}