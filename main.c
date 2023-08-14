#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Function for login
void loginInfo()
{
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
    }

    else
    {
        printf("Login failed. Invalid username or password.\n");
        loginInfo();
    }
}

// Function to display main menu
void mainMenu()
{
    int choice = 0;

    system("cls");

    loginInfo();

    system("cls");

    do
    {
        // system("cls");
        printf("\n\n________________WELCOME TO STUDENT GRADING SYSTEM ________________\n\n");
        printf("\n 1. Add  New Records");
        printf("\n 2. Update Previous Records");
        printf("\n 3. Show All Records");
        printf("\n 4. Search Records");
        printf("\n 5. Edit Records");
        printf("\n 6. Delete Records");
        printf("\n 7. Exit");

        printf("\n\n Please enter your choice: ");
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
            printf("\nProgram terminated successfully.");
            exit(0);
            break;

        default:
            printf("\nPlease choose the correct options.\n");
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

    if (students.studentID <= 0 || students.studentID >= 1000)
    {
        printf("Please enter in the range from 1 to 999.\n");
        goto labelStudentID;
    }

    f2 = fopen("StudentInfo.txt", "r");

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

labelMarks:
    printf("Enter your marks of semester %d.\n", i + 1);

    printf("Enter marks in five subject : ");
    scanf("%f %f %f %f %f", &students.marks[i].subject1, &students.marks[i].subject2, &students.marks[i].subject3, &students.marks[i].subject4, &students.marks[i].subject5);

    if (students.marks[i].subject1 >= 0 && students.marks[i].subject1 <= 100 && students.marks[i].subject2 >= 0 && students.marks[i].subject2 <= 100 && students.marks[i].subject3 >= 0 && students.marks[i].subject3 <= 100 && students.marks[i].subject4 >= 0 && students.marks[i].subject4 <= 100 && students.marks[i].subject5 >= 0 && students.marks[i].subject5 <= 100)
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
        if (studentID == students.studentID)
        {
            students.semester = students.semester + 1;

            printf("You are adding in %d semester.\n", students.semester);

            int i = students.semester - 1;

        updateLabelMarks:

            printf("Enter your marks of semester %d.\n", i + 1);

            printf("Enter marks in five subject : ");
            scanf("%f %f %f %f %f", &students.marks[i].subject1, &students.marks[i].subject2, &students.marks[i].subject3, &students.marks[i].subject4, &students.marks[i].subject5);

            if (students.marks[i].subject1 >= 0 && students.marks[i].subject1 <= 100 && students.marks[i].subject2 >= 0 && students.marks[i].subject2 <= 100 && students.marks[i].subject3 >= 0 && students.marks[i].subject3 <= 100 && students.marks[i].subject4 >= 0 && students.marks[i].subject4 <= 100 && students.marks[i].subject5 >= 0 && students.marks[i].subject5 <= 100)
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
        printf("\n Student ID    : %d", students.studentID);
        printf("\n Name          : %s", students.name);
        printf("\n Faculty       : %s", students.faculty);
        printf("\n Address       : %s", students.address);
        printf("\n Phone Number  : %lld", students.phoneNumber);
        printf("\n Joined Year   : %d", students.intakeYear);

        for (int i = 0; i < students.semester; i++)
        {
            printf("\n Semester      : %d", i + 1);
            printf("\n Subject 1     : %.2f", students.marks[i].subject1);
            printf("\n Subject 2     : %.2f", students.marks[i].subject2);
            printf("\n Subject 3     : %.2f", students.marks[i].subject3);
            printf("\n Subject 4     : %.2f", students.marks[i].subject4);
            printf("\n Subject 5     : %.2f", students.marks[i].subject5);
            printf("\n Subject 1     : %.2f", students.marks[i].subject1);
            printf("\n Gpa 1         : %.2f", students.marks[i].gpa1);
            printf("\n Gpa 2         : %.2f", students.marks[i].gpa2);
            printf("\n Gpa 3         : %.2f", students.marks[i].gpa3);
            printf("\n Gpa 4         : %.2f", students.marks[i].gpa4);
            printf("\n Gpa 5         : %.2f", students.marks[i].gpa5);
            printf("\n Total Marks   : %.2f", students.marks[i].totalMarksObtained);
            printf("\n Total GPA     : %.2f", students.marks[i].totalGpa);
            printf("\n Percentage    : %.2f %", students.marks[i].percentage);
            printf("\n ________________________________________\n");
        }
    }
    fclose(f1);
}

// Functionf to search student records (case 4)
void searchStudent()
{
    int studentID, semester, matched = 0;

    f1 = fopen("StudentInfo.txt", "r");

    printf("\n\n________________SEARCH RECORDS________________\n\n");

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

    printf("Enter Semester: ");
    scanf("%d", &semester);

    while (fread(&students, sizeof(students), 1, f1) > 0)
    {
        if (students.studentID == studentID && students.semester == semester)
        {
            matched = 1;

            printf("\n ________________________________________\n");
            printf("\n Student ID    : %d", students.studentID);
            printf("\n Name          : %s", students.name);
            printf("\n Semester      : %d", students.semester);
            printf("\n Faculty       : %s", students.faculty);
            printf("\n Address       : %s", students.address);
            printf("\n Phone Number  : %lld", students.phoneNumber);
            printf("\n Joined Year   : %d", students.intakeYear);

            for (int i = 0; i < students.semester; i++)
            {
                printf("\n Subject 1     : %.2f", students.marks[i].subject1);
                printf("\n Subject 2     : %.2f", students.marks[i].subject2);
                printf("\n Subject 3     : %.2f", students.marks[i].subject3);
                printf("\n Subject 4     : %.2f", students.marks[i].subject4);
                printf("\n Subject 5     : %.2f", students.marks[i].subject5);
                printf("\n Subject 1     : %.2f", students.marks[i].subject1);
                printf("\n Gpa 1         : %.2f", students.marks[i].gpa1);
                printf("\n Gpa 2         : %.2f", students.marks[i].gpa2);
                printf("\n Gpa 3         : %.2f", students.marks[i].gpa3);
                printf("\n Gpa 4         : %.2f", students.marks[i].gpa4);
                printf("\n Gpa 5         : %.2f", students.marks[i].gpa5);
                printf("\n Total Marks   : %.2f", students.marks[i].totalMarksObtained);
                printf("\n Total GPA     : %.2f", students.marks[i].totalGpa);
                printf("\n Percentage    : %.2f \%", students.marks[i].percentage);
            }
            printf("\n ________________________________________\n");
        }
    }

    if (!matched)
    {
        printf("\nStudent ID of %d not found.", studentID);
    }

    fclose(f1);
}

// Function to edit student record (case 5)
void editStudent()
{
    int studentID, matched = 0, size = 0;

    printf("\n\n________________EDIT RECORDS________________\n\n");

    f1 = fopen("StudentInfo.txt", "r");
    if (NULL != f1)
    {
        fseek(f1, 0, SEEK_END);
        size = ftell(f1);

        if (0 == size)
        {
            printf("File is empty\n");
            // mainMenu();
        }
    }

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
        editStudent();
    }

    rewind(f1);

    while (fread(&students, sizeof(students), 1, f1) > 0)
    {
        if (students.studentID == studentID)
        {
            matched = 1;
            printf("Student ID found.\n");

        labelName:

            printf("Enter edited Name: ");
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
            scanf("%f %f %f %f %f", &students.marks[i].subject1, &students.marks[i].subject2, &students.marks[i].subject3, &students.marks[i].subject4, &students.marks[i].subject5);

            if (students.marks[i].subject1 >= 0 && students.marks[i].subject1 <= 100 && students.marks[i].subject2 >= 0 && students.marks[i].subject2 <= 100 && students.marks[i].subject3 >= 0 && students.marks[i].subject3 <= 100 && students.marks[i].subject4 >= 0 && students.marks[i].subject4 <= 100 && students.marks[i].subject5 >= 0 && students.marks[i].subject5 <= 100)
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
    int studentID, matched = 0;

    f1 = fopen("StudentInfo.txt", "r");
    f2 = fopen("temp.txt", "w");

    printf("\n\n________________DELETE RECORDS________________\n\n");

    if (f1 == NULL)
    {
        fprintf(stderr, "Unable to open file.\n");
        exit(0);
    }

    printf("Enter Student ID: ");
    scanf("%d", &studentID);

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

int main()
{
    system("cls");

    mainMenu();

    return 0;
}