#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100;

typedef struct
{
    char id[50];
    char firstName[50];
    char middleName[50];
    char lastName[50];
    char birthDate[30];
    float algebraScore;
    float calculusScore;
    float basicProgrammingScore;
} Student;

Student GetStudent();
Student findYoungestStudent(int n, Student studentList[]);
Student searchStudentById(int n, char studentId[], Student studentList[]);
int searchStudentHandle(int count, Student studentList[]);
int writeContactsToFile(Student studentList[], int count, const char *fileName);
int GetNumberOfStudents(Student studentList[]);
int mainMenu();
int readContactsFromFile(Student studentList[], int *count, const char *fileName);
int arrayCount(Student arr[]);
Student findHighestGPA(int n, Student studentList[]);
Student findLowestGPA(int n, Student studentList[]);
void Line();
void getString(char *str, int length);
void PressEnterToContinue();
void longTitle(char title[30]);
float GPA(float firstScore, float secondScore, float thirdScore);
void savingSuccess();
void chooseAlert(int from, int to);
void printAllStudents(int n, Student studentList[]);
void printStudent(Student student);
float findMax(float arr[], int n);
float findMin(float arr[], int n);
int getYearOfBirth(char birthDate[]);
int calculateAge(int yearOfBirth, int currentYear);

int main()
{
    int count = 0, mainChoice;
    int n = 0;
    char isSave[50];
    char temp[50];
    Student studentList[1000];
    printf("Enter Number Of Students In System: "); // TASK 1
    scanf("%d", &n);
    readContactsFromFile(studentList, &count, "students.csv"); // TASK 4
    do
    {
        int mainChoice = mainMenu();
        switch (mainChoice)
        {
        case 1:
            searchStudentHandle(count, studentList);
            PressEnterToContinue();
            break;
        case 2:
            studentList[count] = GetStudent(); // TASK 2
            count++;
            printf("Do you want to save? (y/n): ");
            getString(isSave, 50);
            if (strcmp(isSave, "y") == 0)
            {
                writeContactsToFile(studentList, count, "students.csv"); // TASK 4
                savingSuccess();
            }
            else if (isSave == "n")
                printf("Saving.. False!");
            else
                printf("Invalid Choice!");
            PressEnterToContinue();
            break;
        case 3:
            longTitle("YOUNGEST STUDENT");
            printf("======================================================================================================================\n");
            printStudent(findYoungestStudent(count, studentList));
            printf("======================================================================================================================\n");
            PressEnterToContinue();
            break;
        case 4:
            printAllStudents(count, studentList); // TASK 3
            PressEnterToContinue();
            break;
        case 5:
            longTitle("HIGHEST GPA");
            printf(" %-3s | %-20s | %-15s | %-17s | %-17s | %-17s | %-17s |\n", "ID", "Full Name", "BirthDate", "Algebra", "Calculus", "Basic Programming", "GPA");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            printStudent(findHighestGPA(count, studentList));
            longTitle("lOWEST GPA");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            printf(" %-3s | %-20s | %-15s | %-17s | %-17s | %-17s | %-17s |\n", "ID", "Full Name", "BirthDate", "Algebra", "Calculus", "Basic Programming", "GPA");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            printStudent(findLowestGPA(count, studentList));
            printf("======================================================================================================================\n");
            PressEnterToContinue();
            break;
        case 6:
            exit(0);
            break;
        default:
            chooseAlert(1, 6);
            break;
        }
    } while (mainChoice != 5);
    return 0;
}
int GetNumberOfStudents(Student studentList[])
{
    int n = 0;
    printf("Enter Number Of Students In System: ");
    scanf("%d", &n);
    return n;
}
Student searchStudentById(int n, char studentId[], Student studentList[])
{
    Student student;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(studentList[i].id, studentId) == 0)
        {
            student = studentList[i];
        }
    }
    return student;
}
int searchStudentHandle(int count, Student studentList[])
{
    char studentId[50];
    printf("Enter Student Id: ");
    getString(studentId, 50);
    printf("======================================================================================================================\n");
    printf(" SEARCH STUDENT ID %s\n", studentId);
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf(" %-3s | %-20s | %-15s | %-17s | %-17s | %-17s | %-17s |\n", "ID", "Full Name", "BirthDate", "Algebra", "Calculus", "Basic Programming", "GPA");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printStudent(searchStudentById(count, studentId, studentList));
}
Student findHighestGPA(int n, Student studentList[])
{
    float gpas[n];
    for (int i = 0; i < n; i++)
    {
        float gpa = GPA(studentList[i].algebraScore, studentList[i].calculusScore, studentList[i].basicProgrammingScore);
        gpas[i] = gpa;
    }
    float max = findMax(gpas, n);
    Student student;
    for (int i = 0; i < n; i++)
    {
        if (GPA(studentList[i].algebraScore, studentList[i].calculusScore, studentList[i].basicProgrammingScore) == max)
        {
            student = studentList[i];
        }
    }
    return student;
}
Student findLowestGPA(int n, Student studentList[])
{
    float gpas[n];
    for (int i = 0; i < n; i++)
    {
        float gpa = GPA(studentList[i].algebraScore, studentList[i].calculusScore, studentList[i].basicProgrammingScore);
        gpas[i] = gpa;
    }
    float min = findMin(gpas, n);
    Student student;
    for (int i = 0; i < n; i++)
    {
        if (GPA(studentList[i].algebraScore, studentList[i].calculusScore, studentList[i].basicProgrammingScore) == min)
        {
            student = studentList[i];
        }
    }
    return student;
}
Student findYoungestStudent(int n, Student studentList[])
{
    int ages[n];
    for (int i = 0; i < n; i++)
    {
        int age = getYearOfBirth(studentList[i].birthDate);
        ages[i] = age;
    }
    int highestYear = ages[0];
    for (int i = 1; i < n; i++)
    {
        if (ages[i] > highestYear)
            highestYear = ages[i];
    }
    Student student;
    for (int i = 0; i < n; i++)
    {
        if (getYearOfBirth(studentList[i].birthDate) == highestYear)
        {
            student = studentList[i];
        }
    }
    return student;
}
float findMax(float arr[], int n)
{
    float max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
float findMin(float arr[], int n)
{
    float min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

int getYearOfBirth(char birthDate[])
{
    int length = strlen(birthDate);

    char lastFour[5];

    for (int i = 0; i < 4; i++)
    {
        lastFour[i] = birthDate[length - 4 + i];
    }
    int yearOfBirth = atoi(lastFour);
    return yearOfBirth;
}

int calculateAge(int yearOfBirth, int currentYear)
{
    int age = currentYear - yearOfBirth;
    return age;
}

void savingSuccess()
{
    Line();
    printf(" Saving.. Success!\n");
    Line();
}

void chooseNoAlert()
{
    printf("\nPlease, Choose no from the list!\n");
    PressEnterToContinue();
}

void chooseAlert(int from, int to)
{
    printf("\nPlease, Choose numbers between %d and %d!\n\n", from, to);
    PressEnterToContinue();
}

int mainMenu()
{
    int choice;
    Line();
    printf("            --- STUDENT MANAGEMENT ---\n");
    Line();
    printf("  1. SEARCH STUDENT BY ID\n");
    printf("  2. ADD STUDENT\n");
    printf("  3. YOUNGEST STUDENT\n");
    printf("  4. DISPLAY ALL STUDENT\n");
    printf("  5. HIGHEST GPA, LOWEST GPA\n");
    printf("  6. EXIT APPLICATION\n");
    Line();
    printf(" #YOUR CHOICE: ");
    scanf("%d", &choice);
    Line();
    return choice;
}

char searchName(char inputSearchName[20])
{
    printf("Enter name you want to search: ");
    getString(inputSearchName, 20);
    return inputSearchName[20];
}

int DetailMenuUI()
{
    int choice;
    printf(" 1. ADD TO FAVOURITES\n");
    printf(" 2. UPDATE\n");
    printf(" 3. DELETE\n");
    printf(" 4. ADD FIELD\n");
    printf(" 5. BACK TO MAIN MENU\n");
    Line();
    printf(" #CHOICE: ");
    scanf("%d", &choice);
    Line();
    return choice;
}

Student GetStudent()
{
    Student student;
    printf(" Student Id: ");
    getString(student.id, 50);
    printf(" First Name: ");
    getString(student.firstName, 50);
    printf(" Middle Name: ");
    getString(student.middleName, 50);
    printf(" Last Name: ");
    getString(student.lastName, 50);
    printf(" BirthDate (dd/mm/yyyy): ");
    getString(student.birthDate, 50);
    printf(" Algebra Score: ");
    scanf("%f", &student.algebraScore);
    printf(" Calculus Score: ");
    scanf("%f", &student.calculusScore);
    printf(" Basic Programming Score: ");
    scanf("%f", &student.basicProgrammingScore);
    return student;
}

void printAllStudents(int n, Student studentList[])
{
    printf(" %-10s | %-20s | %-15s | %-17s | %-17s | %-17s | %-17s |\n", "ID", "Full Name", "BirthDate", "Algebra", "Calculus", "Basic Programming", "GPA");
    for (int i = 0; i < n; i++)
    {
        printStudent(studentList[i]);
    }
}

void printStudent(Student student)
{
    float gpa = GPA(student.algebraScore, student.calculusScore, student.basicProgrammingScore);
    printf(" %-10s | %-20s | %-15s | %-17f | %-17f | %-17f | %-17f |\n", student.id, student.firstName, student.birthDate, student.algebraScore, student.calculusScore, student.basicProgrammingScore, gpa);
}

float GPA(float algebraScore, float calculusScore, float basicProgrammingScore)
{
    return (algebraScore + calculusScore + basicProgrammingScore) / 3;
}

void longTitle(char title[30])
{
    printf("======================================================================================================================\n");
    printf(" %s\n", title);
    printf("----------------------------------------------------------------------------------------------------------------------\n");
}

int readContactsFromFile(Student studentList[], int *count, const char *fileName)
{
    FILE *f;                   // tạo file để xử lí
    f = fopen(fileName, "rb"); // mở file
    if (f == NULL)             // nếu file rỗng return 0
    {
        return 0;
    }
    int i;
    for (i = 0; !feof(f); i++) // vòng lặp sử dụng hàm feof để đọc dữ liệu đến cuối file
    {
        fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f,%f\n", &(studentList + i)->id, &(studentList + i)->firstName, &(studentList + i)->middleName, &(studentList + i)->lastName, &(studentList + i)->birthDate, &(studentList + i)->algebraScore, &(studentList + i)->calculusScore, &(studentList + i)->basicProgrammingScore);
    } // %[^,] => đọc dữ liệu string trong file và bỏ qua dấu phẩy
    // fscanf => xuất dữ liệu khỏi file
    *count = i;
    fclose(f); // dong file
    return 1;
}

int writeContactsToFile(Student studentList[], int count, const char *fileName)
{
    FILE *f;
    f = fopen(fileName, "wb");
    if (f == NULL)
    {
        return 0;
    }
    int i;
    for (i = 0; i < count; i++) // vong lap dung de nhap du lieu vao file
    {
        fprintf(f, "%s,%s,%s,%s,%s,%f,%f,%f\n", studentList[i].id, studentList[i].firstName, studentList[i].middleName, studentList[i].lastName, studentList[i].birthDate, studentList[i].algebraScore, studentList[i].calculusScore, studentList[i].basicProgrammingScore);
    }
    // fprintf => nhập dữ liệu vào file
    fclose(f);
    return 1;
}

void getString(char *str, int length)
{
    fflush(stdin);
    fgets(str, length, stdin);
    str[strlen(str) - 1] = '\0';
    fflush(stdin);
}

void Line()
{
    printf("==================================================\n");
}

void PressEnterToContinue()
{
    printf(" Press Enter To Continue..");
    fflush(stdin);
    getchar();
}