/**
 * @file manageStudents.c
 * @author  Michael Merzlyak <michael.merzlyak@mail.huji.ac.il>
 * @version 1.0
 * @date 12 November 2019
 *
 * @brief System to keep track of students.
 *
 *
 * @section DESCRIPTION
 * The system keeps track of given students.
 * Input  : The amount of students to store when MAX is 5000.
 * Process: Storing students and it either sorts them using merge
 *          ,quickSort or just returning the best students by grade/age.
 * Output : For Best it returns the details of the best student according to grade/age
 *        for merge the system will return the array sorted using MergeSort by grade
 *        for quick the system will return array sorted using QuickSort by name
 */
// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ------------------------------ cost define ------------------------------
#define MAX_SIZE  41
#define MAX_LENGTH 151
#define ID_ILLEGAL_SIGN "ERROR: ID must contain only numbers between 1-9\n"

#define PRINT_REQUEST_INPUT "Enter student info. To exit press q, then enter\n"
#define LEGAL_FORMAT "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t"
#define END_PROGRAM_START_OPERATION "q\n"
#define END_PROGRAM_START_OPERATION_WITHR "q\r\n"
#define GET_BEST "best"
#define SORT_BY_GRADE_USING_MERGE "merge"
#define SORT_BY_NAME_USING_QUICKSORT "quick"
#define ERROR_NUMBER_PARAMETERS_INCORRECT "ERROR: number of parameters is incorrect, please make \
sure the format is: ID, Name, Grade, Age, Country, City\n"
#define LEGAL_CHARACTERS "%[0-9]"
#define ID_0_ERROR "ERROR: ID can't start with 0 , please re-enter\n"
#define ID_LENGTH_ERROR "ERROR: id is not in the correct length , please enter ID with 10 digits\n"
#define ERROR_NAME_CHARACTERS "ERROR: name must contain only letters ,- and spacebar\n"
#define ERROR_ILLEGAL_GRADE_CHARACTERS "ERROR: grade is invalid, contains illegal characters, \
make sure it contains only digits\n"
#define ERROR_GRADE_ILLEGAL_NUMBER "ERROR: grade is invalid,\
make sure it a number between 0 and 100\n"
#define ERROR_AGE_ILLEGAL_CHARACTERS "ERROR: age is invalid, make sure it contains only digits\n"
#define ERROR_AGE_ILLEGAL_NUMBER "ERROR: age is invalid,make sure it a number between 18 and 100\n"
#define ERROR_COUNTRY_ILLEGAL_CHARACTERS "ERROR: country given is invalid, \
May only contain letters and '-'\n"
#define ERROR_CITY_ILLEGAL_CHARACTERS "ERROR: city given is invalid,\
 May only contain letters and '-'\n"
#define LEGAL_CITY_COUNTRY_FORMAT "%[A-Za-z-]"
#define LEGAL_NAME_FORMAT "%[A-Za-z- ]"
#define MAX_AGE 120
#define MAX_GRADE 100
#define MIN_GRADE 18
#define HALF_OF_MAX_STUDENT_SIZE 2500
#define OUT_FORMAT "best student info is: %s\t%s\t%d\t%d\t%s\t%s\t\n"
#define FORMAT  "in line %d\n"
#define MAX_STUDENT_AMOUNT  5000
#define BEST_SELECTED 1
#define MERGE_SELECTED 2
#define QUICK_SELECTED 3
#define FINISH_PARAMETERS_ALLOWED 2
#define ERROR_USAGE_OUTPUT "USAGE: Available operations are merge , quick or best"
#define PRINT_FORMAT "%s\t%s\t%d\t%d\t%s\t%s\t\n"
#define ILLEGAL_ID_START '0'
#define ENDLESS_LOOP_UNTIL_BREAK 1
#define MAX_ID_LENGTH 10
#define FAILED 0
#define SUCCESS 1
const int INPUT_SIZE = 6;
// ------------------------------ structs -----------------------------
/**
 * Struct for a single Student
 */
typedef struct Student
{
    char ID[MAX_SIZE];
    char name[MAX_SIZE];
    char country[MAX_SIZE];
    char city[MAX_SIZE];
    int grade;
    int age;

} student;
// ------------------------------ functions -----------------------------
/**
 * Find the best student according to grade/age ratio.
 * @param curArray Array holding the given students.
 * @param len the number of students successfully added
 * @return returns the info of the best students according to grade/age ratio
 */
void calcBestStudent(const student curArray[], int len);
/**
 * Check that the given ID is valid.
 * @param gID ID of the current given student
 * @return 0 if ID not valid 1 otherwise
 */
int checkID(const char gID[]);
/**
 * Check that the given Name is valid.
 * @param name Name of the current given student.
 * @return 0 if Name is invalid 1 otherwise
 */
int checkName(const char name[]);
/**
 * Check that the given grade is valid.
 * @param stringGrade Grade of the given student
 * @return 0 if grade is invalid 1 otherwise
 */
int checkGrade(const char stringGrade[]);
/**
 * Check that the given Age is valid.
 * @param stringAge The age of the current student
 * @return 0 if age is invalid 1 otherwise
 */
int checkAge(const char stringAge[]);
/**
 * Check that the given country is valid.
 * @param input Country of the given student.
 * @return 0 if Country invalid 1 otherwise
 */
int checkCountry(const char input[]);
/**
 * Check that the given city is valid
 * @param input City of the current student.
 * @return 0 if city is invalid 1 otherwise
 */
int checkCity(const char input[]);
/**
 * Checks if all of the given student information is valid
 * @param gID Current ID of student
 * @param name Current name of student
 * @param grade Current grade of student
 * @param age Current age of student
 * @param country Current country of student
 * @param city Current city of student
 * @return 0 if any of the inputs is not valid 1 otherwise
 */
int checkInputs(const char gID[], const char name[], const char grade[],
                const char age[], const char country[], const char city[]);
/**
 * Sorts the given student array using QuickSort by name
 * @param curArray Current student array.
 * @param left Leftmost index to sort from
 * @param right Rightmost index to sort to.
 */
void sortByQuick(student curArray[], int left, int right);
/**
 * Function the merge the seperated arrays
 * @param curArray Current student array.
 * @param left Leftmost index to sort from
 * @param right Rightmost index to sort to.
 * @param middle middles index of the next index to sort
 */
void merge(student curArray[], int left, int right, int middle);
/**
 * Sorts the given student array using MergeSort by grade
 * @param curArray Current student array.
 * @param left Leftmost index to sort from
 * @param right Rightmost index to sort to.
 * @param middle middles index of the next index to sort
 */
void sortByMerge(student curArray[], int left, int right);
/**
 * Function to find the next index to sort from
 * @param curArray  Current student Array
 * @param left Leftmost index to sort
 * @param right Rightmost index to sort
 * @return Index to split the arrays by.
 */
int partition(student curArray[], int left, int right);
/**
 * prints the current array.
 * @param curArray Current student array.
 */
void printArray(student const curArray[]);
/**
 * Chooses the wanted operation to perform from best/merge/quick
 * when best - returns best student to grade/age ratio
 * merge- sorts the array using MergeSort by grade
 * quick - sorts the array using QuickSort by name.
 * @param argc Number of parameters in the input.
 * @param argv The parameters of the input.
 * @return 1 if parameters not valid 0 otherwise
 */
int checkArgs(int argc, char *argv[]);
// ------------------------------ global var -----------------------------
int gOperation;
int gStudentCounter = 0;

int main(int argc, char *argv[])
{
    student studentArray[MAX_STUDENT_AMOUNT];
    int lineCounter = 0;
    char legalFormat[MAX_LENGTH], stringAge[MAX_SIZE], ID[MAX_SIZE], grade[MAX_SIZE],
    country[MAX_SIZE], name[MAX_SIZE], city[MAX_SIZE];
    // check if the terminal input is valid and chooses the
    // operation.
    if(checkArgs(argc, argv) == 1)
    {
        return 1;
    }
    while (ENDLESS_LOOP_UNTIL_BREAK)
    {
        printf(PRINT_REQUEST_INPUT);
        fgets(legalFormat, MAX_LENGTH, stdin);
        int len = sscanf(legalFormat, LEGAL_FORMAT, ID, name, grade, stringAge, country, city);
        if (strcmp(ID, END_PROGRAM_START_OPERATION) == 0 ||
            strcmp(ID, END_PROGRAM_START_OPERATION_WITHR) == 0)
        {
            break;
        }
        if (len != INPUT_SIZE)
        {
            fprintf(stdout, ERROR_NUMBER_PARAMETERS_INCORRECT);
            printf(FORMAT, lineCounter);
        }
        else
        {
            int validtedInput = checkInputs(ID, name, grade, stringAge, country, city);
            if (validtedInput == SUCCESS)
            {
                studentArray[gStudentCounter].age = ((int) strtol(stringAge, NULL, 10));
                studentArray[gStudentCounter].grade = ((int) strtol(grade, NULL, 10));
                strcpy(studentArray[gStudentCounter].ID, ID);
                strcpy(studentArray[gStudentCounter].name, name);
                strcpy(studentArray[gStudentCounter].country, country);
                strcpy(studentArray[gStudentCounter].city, city);
                gStudentCounter++;
            }
            else
            {
                printf(FORMAT, lineCounter);
            }
        }
        lineCounter++;
    }
    if (gOperation == BEST_SELECTED && gStudentCounter > 0)
    {
        calcBestStudent(studentArray, gStudentCounter);
    }
    else if (gOperation == MERGE_SELECTED && gStudentCounter > 0)
    {
        sortByMerge(studentArray, 0, gStudentCounter - 1);
        printArray(studentArray);
    }
    else if (gOperation == QUICK_SELECTED && gStudentCounter > 0)
    {
        sortByQuick(studentArray, 0, gStudentCounter - 1);
        printArray(studentArray);
    }

    return 0;
}
int checkArgs(int argc, char *argv[])
{
    if (argc == FINISH_PARAMETERS_ALLOWED && strcmp(argv[1], GET_BEST) == 0)
    {
        gOperation = BEST_SELECTED;
    }
    else if (argc == FINISH_PARAMETERS_ALLOWED && strcmp(argv[1], SORT_BY_GRADE_USING_MERGE) == 0)
    {
        gOperation = MERGE_SELECTED;
    }
    else if (argc == FINISH_PARAMETERS_ALLOWED && strcmp(argv[1], SORT_BY_NAME_USING_QUICKSORT) == 0)
    {
        gOperation = QUICK_SELECTED;
    }
    else
    {
        fprintf(stdout, ERROR_USAGE_OUTPUT);
        return 1;
    }
    return 0;
}

int checkInputs(const char ID[], const char name[], const char grade[],
                const char age[], const char country[], const char city[])
{
    if (checkID(ID) == FAILED)
    {
        return 0;
    }
    if (checkName(name) == FAILED)
    {
        return 0;
    }
    if (checkGrade(grade) == FAILED)
    {
        return 0;
    }
    if (checkAge(age) == FAILED)
    {
        return 0;
    }
    if (checkCountry(country) == FAILED)
    {
        return 0;
    }
    if (checkCity(city) == FAILED)
    {
        return 0;
    }
    return 1;
}

int checkID(const char ID[])
{
    char temp[MAX_SIZE];
    sscanf(ID, LEGAL_CHARACTERS, temp);
    if (strcmp(ID, temp) != 0)
    {
        fprintf(stdout, ID_ILLEGAL_SIGN);
        return 0;
    }
    if (ID[0] == ILLEGAL_ID_START)
    {
        fprintf(stdout, ID_0_ERROR);
        return 0;
    }
    if (strlen(ID) != MAX_ID_LENGTH)
    {
        printf(ID_LENGTH_ERROR);
        return 0;
    }
    return 1;
}

int checkName(const char name[])
{
    char temp[MAX_SIZE];
    sscanf(name, LEGAL_NAME_FORMAT, temp);
    if (strcmp(name, temp) != 0)
    {
        printf(ERROR_NAME_CHARACTERS);
        return 0;
    }
    return 1;
}

int checkGrade(const char stringGrade[])
{
    char temp[MAX_SIZE];
    sscanf(stringGrade, LEGAL_CHARACTERS, temp);
    if (strcmp(stringGrade, temp) != 0)
    {
        printf(ERROR_ILLEGAL_GRADE_CHARACTERS);
        return 0;
    }
    int num = (int) strtol(stringGrade, NULL, 10);
    if (num < 0 || num > MAX_GRADE)
    {
        printf(ERROR_GRADE_ILLEGAL_NUMBER);
        return 0;
    }
    return 1;
}

int checkAge(const char stringAge[])
{
    char temp[MAX_SIZE];
    sscanf(stringAge, LEGAL_CHARACTERS, temp);
    if (strcmp(stringAge, temp) != 0)
    {
        printf(ERROR_AGE_ILLEGAL_CHARACTERS);
        return 0;
    }
    int num = (int) strtol(stringAge, NULL, 10);
    if (num < MIN_GRADE || num > MAX_AGE)
    {
        printf(ERROR_AGE_ILLEGAL_NUMBER);
        return 0;
    }
    return 1;

}

int checkCountry(const char input[])
{
    char temp[MAX_SIZE];
    sscanf(input, LEGAL_CITY_COUNTRY_FORMAT, temp);
    if (strcmp(input, temp) != 0)
    {
        printf(ERROR_COUNTRY_ILLEGAL_CHARACTERS);
        return 0;
    }
    return 1;
}

int checkCity(const char input[])
{
    char temp[MAX_SIZE];
    sscanf(input, LEGAL_CITY_COUNTRY_FORMAT, temp);
    if (strcmp(input, temp) != 0)
    {
        printf(ERROR_CITY_ILLEGAL_CHARACTERS);
        return 0;
    }
    return 1;
}

void calcBestStudent(const student curArray[], int len)
{
    double maxStudent = 0.0;
    int indexOfBestStudent = 0;
    for (int index = 0; index < len; index++)
    {
        double curRatio = ((double) curArray[index].grade / (double) curArray[index].age);
        if (maxStudent < curRatio)
        {
            indexOfBestStudent = index;
            maxStudent = curRatio;
        }
    }

    printf(OUT_FORMAT, curArray[indexOfBestStudent].ID, curArray[indexOfBestStudent].name,
            curArray[indexOfBestStudent].grade, curArray[indexOfBestStudent].age,
            curArray[indexOfBestStudent].country, curArray[indexOfBestStudent].city);
}

void merge(student curArray[], int left, int right, int middle)
{
    int leftMostIndexToSort = 0, rightMostIndexToSort = 0, curIndex = left; // initialize index
    // counters
    int leftEdge = middle - left + 1;
    int rightEdge = right - middle;
    int indexLeft = 0;
    int rightIndex = 0;

    // initialize 2 temp arrays to hold data
    student leftArray[HALF_OF_MAX_STUDENT_SIZE], rightArray[HALF_OF_MAX_STUDENT_SIZE];

    while ( indexLeft < leftEdge) // copying both arrays to temp arrays
    {
        leftArray[indexLeft] = curArray[left + indexLeft];
        indexLeft++;
    }
    while (rightIndex < rightEdge)
    {
        rightArray[rightIndex] = curArray[rightIndex + middle + 1];
        rightIndex++;
    }

    while (leftMostIndexToSort < leftEdge && rightMostIndexToSort < rightEdge) // while we didnt
        // pass our rightEdge or left Edge
    {
        if (leftArray[leftMostIndexToSort].grade <= rightArray[rightMostIndexToSort].grade)
        {
            curArray[curIndex] = leftArray[leftMostIndexToSort];
            leftMostIndexToSort++; // if we copied add 1 to counter
        }
        else
        {
            curArray[curIndex] = rightArray[rightMostIndexToSort];
            rightMostIndexToSort++; // if we copied add 1 to counter
        }
        curIndex++; // counter of main array
    }
    // if one of the arrays we shorter just copy the reminder
    while (leftMostIndexToSort < leftEdge)
    {
        curArray[curIndex] = leftArray[leftMostIndexToSort];
        leftMostIndexToSort++;
        curIndex++;
    }
    while (rightMostIndexToSort < rightEdge)
    {
        curArray[curIndex] = rightArray[rightMostIndexToSort];
        rightMostIndexToSort++;
        curIndex++;
    }
}

void sortByMerge(student curArray[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2; // calcs the middle of the array

        sortByMerge(curArray, left, middle); //sort the left side
        sortByMerge(curArray, middle + 1, right); //sorts the right side

        merge(curArray, left, right, middle); // merges both
    }
}

void sortByQuick(student curArray[], int left, int right)
{
    if (left < right)
    {
        int curPivot = partition(curArray, left, right);

        sortByQuick(curArray, left, curPivot - 1); //sort left side until out index
        sortByQuick(curArray, curPivot + 1, right); // sort right side
    }
}

int partition(student curArray[], int left, int right)
{
    student pivot = curArray[right]; // student to compare with

    int swapIndex = left - 1; // index of swap

    for (int index = left; index < right; index++)
    {
        if (strcmp(curArray[index].name, pivot.name) <= 0) // if swap needed
        {
            student temp;
            swapIndex++;
            temp = curArray[swapIndex];
            curArray[swapIndex] = curArray[index];
            curArray[index] = temp;
        }
    }
    student temp2;
    temp2 = curArray[swapIndex + 1];
    curArray[swapIndex + 1] = curArray[right];
    curArray[right] = temp2;
    return swapIndex + 1;
}
void printArray(student const curArray[])
{
    for (int i = 0; i < gStudentCounter; i++)
    {
        printf( PRINT_FORMAT, curArray[i].ID, curArray[i].name,
                curArray[i].grade, curArray[i].age, curArray[i].country, curArray[i].city);
    }
}