#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_POINTS (15)
#define FILE_NOT_OPEN (-1)

typedef struct _student
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    double bodovi;

}Student;

int readNoRowsInFile()
{
    int counter = 0;

    FILE* filePointer = NULL;
    char buffer[MAX_SIZE] = { 0 };

    filePointer = fopen("students.txt", "r");
    if (!filePointer)
    {
        printf("Neuspjesno otvaranje datoteke.");
        return FILE_NOT_OPEN;
    }
    while (!feof(filePointer))
    {
        fgets(buffer, MAX_SIZE, filePointer);
        counter++;
    }


    fclose(filePointer);
    return counter;
}
student* allocateMemoryAndReadStudents(int noRows, char* datoteka)
{
    int i;
    FILE* filePointer = NULL;
    student* students = NULL;

    students = (student*)malloc(noRows * sizeof(student));
    filePointer = fopen("datoteka.txt", "r");

    if (!filePointer)
    {
        printf("Neuspjesna alokacija memorije.\n");
        return FILE_NOT_OPENED;
    }
    for (i = 0; i < noRows; i++)
    {
        fscanf(filePointer, " %s %s %lf", students[i].name, students[i].surname, &students[i].points);
    }

    fclose(filePointer);

    return students;
}


double calculateRelativePoints(int noRows, student* students)
{
    int i = 0;
    double maxPoints = 0;

    for (i = 0; i < noRows; i++)
    {
        if (students[i].points > maxPoints)
        {
            maxPoints = students[i].points;
        }
    }
    return maxPoints;
}

int showStudents(int noRows, student* students)
{
    int i;
    double maxPoints = 0;
    maxPoints = calculateRelativePoints(noRows, students);

    printf("NAME\tSURNAME\tPOINTS\tRELATIVE POINTS\n");
    for (i = 0; i < noRows; i++)
    {
        printf("%s\t%s\t%.3lf\t%.3lf%\n", students[i].name, students[i].surname, students[i].points, students[i].points / maxPoints * 100);
    }
}


int main()
{

    int noRows = 0;
    student* students = NULL;
    noRows = readNoRowsInFile("datoteka.txt");
    students = allocateMemoryAndReadStudents(noRows, "datoteka.txt");
    showStudents(noRows, students);
    free(students);

    return 0;
}