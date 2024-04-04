#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define filename "marks.csv"
#define maxstudents_marks 5000
struct marks
{
    char rollno[10];
    float marks[5];
    int grade_weightage[5];
    float cgpa;
};

int numstudent_marks = 0;
struct marks mark[maxstudents_marks];
float grade_array[7][5];
int credit[5];

void merge_marks(float a[], int low, int mid, int high);
void mergesort(float a[], int low, int high);
void loaddata();
void save_marks_details_to_file();
void set_credits();
void input_marks();
void sort_marks();
void assign_grade();
void view_marks_for_teacher();
void view_cgpa_for_student(char str[]);
void marks_input_main();
void marks_main();

void merge_marks(float a[], int low, int mid, int high)
{
    float b[high + 1];
    int i, j, k;
    i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            i++;
            k++;
        }
        else
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= high)
    {
        b[k] = a[j];
        j++;
        k++;
    }
    for (int i = low; i <= high; i++)
    {
        a[i] = b[i];
    }
}
void mergesort(float a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(a, low, mid);
        mergesort(a, mid + 1, high);
        merge_marks(a, low, mid, high);
    }
}

void loaddata()
{
    FILE *file1 = fopen(filename, "a");
    fclose(file1);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error :");
        return;
    }
    while (fscanf(file, "%[^,],%f,%f,%f,%f,%f,%f\n", &mark[numstudent_marks].rollno, &mark[numstudent_marks].marks[0], &mark[numstudent_marks].marks[1], &mark[numstudent_marks].marks[2], &mark[numstudent_marks].marks[3], &mark[numstudent_marks].marks[4], &mark[numstudent_marks].cgpa) == 7)
    {
        numstudent_marks++;
        if (numstudent_marks >= maxstudents_marks)
        {
            break;
        }
    }
}
void save_marks_details_to_file()
{
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < numstudent_marks; i++)
    {
        fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", mark[i].rollno, mark[i].marks[0], mark[i].marks[1], mark[i].marks[2], mark[i].marks[3], mark[i].marks[4], mark[i].cgpa);
    }
}
void set_credits()
{
    credit[0] = 4;
    credit[1] = 4;
    credit[2] = 3;
    credit[3] = 3;
    credit[4] = 2;
}

void input_marks()
{
    printf("Enter roll no.: ");
here1:
    scanf("%s", &mark[numstudent_marks].rollno);
    strupr(mark[numstudent_marks].rollno);
    for (int i = 0; i < numstudent_marks; i++)
    {
        if (strcmp(mark[i].rollno, mark[numstudent_marks].rollno) == 0)
        {
            printf("Enter correct roll no. : ");
            goto here1;
        }
    }
    printf("Enter marks for ");
    for (int i = 0; i < 5; i++)
    {
        printf("sub %d\n", i + 1);
    here2:
        scanf("%f", &mark[numstudent_marks].marks[i]);
        if (mark[numstudent_marks].marks[i] >= 0 && mark[numstudent_marks].marks[i] <= 100)
        {
            continue;
        }
        else
        {
            printf("please enter a value between 0 to 100\n");
            goto here2;
        }
    }
    numstudent_marks++;
    sort_marks();
    assign_grade();
    printf("Marks added Successfully\n");
    save_marks_details_to_file();
}

void sort_marks()
{
    for (int sub = 0; sub < 5; sub++)
    {
        float temp[numstudent_marks];
        for (int i = 0; i < numstudent_marks; i++)
        {
            temp[i] = mark[i].marks[sub];
        }
        mergesort(temp, 0, numstudent_marks - 1);
        for (int i = 0; i < numstudent_marks / 2; i++)
        {
            float temp_var = temp[i];
            temp[i] = temp[numstudent_marks - i];
            temp[numstudent_marks - i] = temp_var;
        }
        int no_ex = ceil(numstudent_marks / 10);
        int no_a = ceil(3 * numstudent_marks / 10);
        int no_b = ceil(3 * numstudent_marks / 10);
        int no_c = ceil(15 * numstudent_marks / 100);
        int no_d = ceil(5 * numstudent_marks / 100);
        int no_p = ceil(5 * numstudent_marks / 100);
        int no_f = numstudent_marks - no_ex - no_a - no_b - no_c - no_d - no_p;
        grade_array[0][sub] = temp[no_ex];
        grade_array[1][sub] = temp[no_ex + no_a];
        grade_array[2][sub] = temp[no_ex + no_a + no_b];
        grade_array[3][sub] = temp[no_ex + no_a + no_b + no_c];
        grade_array[4][sub] = temp[no_ex + no_a + no_b + no_c + no_d];
        grade_array[5][sub] = temp[no_ex + no_a + no_b + no_c + no_d + no_p];
        grade_array[6][sub] = temp[no_ex + no_a + no_b + no_c + no_d + no_p + no_f];
    }
}

void assign_grade()
{
    for (int sub = 0; sub < 5; sub++)
    {
        for (int i = 0; i < numstudent_marks; i++)
        {
            if (mark[i].marks[sub] >= grade_array[0][sub])
            {
                mark[i].grade_weightage[sub] = 10;
            }
            else if (mark[i].marks[sub] >= grade_array[1][sub])
            {
                mark[i].grade_weightage[sub] = 9;
            }
            else if (mark[i].marks[sub] >= grade_array[2][sub])
            {
                mark[i].grade_weightage[sub] = 8;
            }
            else if (mark[i].marks[sub] >= grade_array[3][sub])
            {
                mark[i].grade_weightage[sub] = 7;
            }
            else if (mark[i].marks[sub] >= grade_array[4][sub])
            {
                mark[i].grade_weightage[sub] = 6;
            }
            else if (mark[i].marks[sub] >= grade_array[5][sub])
            {
                mark[i].grade_weightage[sub] = 5;
            }
            else if (mark[i].marks[sub] >= grade_array[6][sub])
            {
                mark[i].grade_weightage[sub] = 0;
            }
        }
    }
    int total_credits = 0;
    for (int sub = 0; sub < 5; sub++)
    {
        total_credits += credit[sub];
    }
    for (int i = 0; i < numstudent_marks; i++)
    {
        mark[i].cgpa = 0;
        for (int sub = 0; sub < 5; sub++)
        {
            mark[i].cgpa += (mark[i].grade_weightage[sub] * credit[sub]) / (float)total_credits;
        }
    }
}
void view_marks_for_teacher()
{
    printf("%-10s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Sr.no", "Roll no.", "Sub 1", "Sub 2", "Sub 3", "Sub 4", "Sub 5", "CGPA");
    for (int i = 0; i < numstudent_marks; i++)
    {
        printf("%-8d :%-15s%-15d%-15d%-15d%-15d%-15d%-15.2f\n", i + 1, mark[i].rollno, mark[i].grade_weightage[0], mark[i].grade_weightage[1], mark[i].grade_weightage[2], mark[i].grade_weightage[3], mark[i].grade_weightage[4], mark[i].cgpa);
    }
}
void view_cgpa_for_student(char str[])
{
    int index = -1;
    for (int i = 0; i < numstudent_marks; i++)
    {
        if (strcmp(str, mark[i].rollno) == 0)
        {
            index = i;
        }
    }
    if (index != -1)
    {
        printf("Roll no. : %s ", mark[index].rollno);
        printf("CGPA : %d\n", mark[index].cgpa);
    }
}

void marks_input_main()
{
    set_credits();
    loaddata();
    input_marks();
    sort_marks();
    assign_grade();
}
void marks_main()
{
    set_credits();
    sort_marks();
    assign_grade();
}
