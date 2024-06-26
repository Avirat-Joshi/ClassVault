#include "password_change.c"
#include "password_change_employee.c"
#include "password_generator.c"
#include "branch_change.c"
#include "input_csv_2_FINAL.c"
#include <stdio.h>
struct s_credentials
{
    char rollno[10];
    char password[20];
};
struct e_credentials
{
    char employeeID[20];
    char password[20];
};
struct s_credentials sc[5000];
struct e_credentials ec[5000];

// authenticate student credentials from credentials_students.csv file
int s_authenticate(char *str)
{
    int number_student_s = 0;
    FILE *file_s1s = fopen("credentials_student.csv", "a");
    fclose(file_s1s);
    FILE *file_s2s = fopen("credentials_student.csv", "r");
    if (file_s2s == NULL)
    {
        perror("Error in opening the file\n");
        return 0;
    }
    while (fscanf(file_s2s, "%[^,],%[^,],\n", &sc[number_student_s].rollno, &sc[number_student_s].password) == 2)
    {
        number_student_s++;
        if (number_student_s >= max_students)
        {
            break;
        }
    }
    fclose(file_s2s);
    printf("Enter password: ");
    char temp_pass[7];
here:
    fflush(stdin);
    gets(temp_pass);
    for (int i = 0; i < number_student_s; i++)
    {
        if (strcmp(str, sc[i].rollno) == 0)
        {
            if (strcmp(temp_pass, sc[i].password) == 0)
            {
                return 1;
            }
            else
            {
                printf("Wrong password\n ");
                printf("Enter Corect password : ");
                goto here;
            }
        }
    }
    return 0;
}
// authenticate employee credentials from credentials_employee.csv file
int e_authenticate(char *str)
{
    int number_employee_e = 0;
    FILE *file_e1e = fopen("credentials_employee.csv", "a");
    fclose(file_e1e);
    FILE *file_e2e = fopen("credentials_employee.csv", "r");
    if (file_e2e == NULL)
    {
        perror("Error in opening the file\n");
        return 0;
    }
    while (fscanf(file_e2e, "%[^,],%[^,],\n", &ec[number_employee_e].employeeID, &ec[number_employee_e].password) == 2)
    {
        number_employee_e++;
        if (number_employee_e >= max_employees)
        {
            break;
        }
    }
    fclose(file_e2e);
    printf("Enter password: ");
    char temp_pass[7];
here:
    fflush(stdin);
    gets(temp_pass);
    for (int i = 0; i < number_employee_e; i++)
        if (strcmp(str, ec[i].employeeID) == 0)
        {
            if (strcmp(temp_pass, ec[i].password) == 0)
                return 1;
            else
            {
                printf("Wrong password\n");
                printf("Enter Corect password : ");
                goto here;
            }
        }
    return 0;
}
int main()
{
    password_generator_main(); // generates and passwords
    loaddatafromfile();        // loading students data from file
    loadfeedbackfromfile();    // loading feedback data from file
    loadteacherdatafromfile(); // loading teachers data from file
    loaddata();                // loading student's marks from file
    Calculate_fees();          // calculating and assigning payable amount of fees
    marks_main();              // assigning grades to students
    assignCGPA();              // assigning CGPA to students
    printf("Welcome to Classvault\n");
    int login = 0;
    char roll[10];
    char empID[10];
    printf("Use Classvalue as a :\n1. Student\n2. Teacher\n");
goto1:
    scanf("%d", &login);

    switch (login)
    {
    case 1:
    {
        printf("Enter roll number: ");
        fflush(stdin);
        gets(roll);
        strupr(roll);
        if (s_authenticate(roll) == 1)
        {
            int choice, choice2;
            do
            {
                printf("\nStudent-list Menu\n");
                printf("0. Exit\n");
                printf("1. View your details\n");
                printf("2. Edit details\n");
                printf("3. Give Feedback\n");
                printf("4. Fee Details\n");
                printf("5. Apply for branch change\n");
                printf("6. Change Password\n");
                printf("Enter your choice(pls enter the number): ");
            gotohere:
                scanf("%d", &choice);

                switch (choice)
                {
                case 0:
                    printf("Exiting Classvault. Goodbye!\n");
                    break;
                case 1:
                    viewstudent_for_student(roll);
                    break;
                case 2:
                {
                    char roll_num[10];
                    printf("Enter the Roll no. of the student you want to edit : ");
                    fflush(stdin);
                    scanf("%s", &roll_num);
                    strupr(roll_num);
                    editstudent(roll_num);
                    break;
                }
                case 3:
                    givefeedback();
                    break;
                case 4:
                    show_fees(roll);
                    break;
                case 5:
                    branch_change_student_main();
                    break;
                case 6:
                    password_change_main();
                    break;
                default:
                    printf("Enter Correct number :");
                    goto gotohere;
                    break;
                }
                sleep(1);
            } while (choice != 0);
            break;
        }
    }
    case 2:
        printf("Enter Employee ID:");
        fflush(stdin);
        gets(empID);
        strupr(empID);
        if (e_authenticate(empID) == 1)
        {

            printf("Welcome to Classvault\n");
            int choice, choice2;

            do
            {
                printf("\nTeacher-list Menu\n");
                printf("0. Exit\n");
                printf("1. Add Person\n");
                printf("2. View \n");
                printf("3. Remove Person\n");
                printf("4. Search Teacher \n");
                printf("5. Search Student \n");
                printf("6. Enter marks\n");
                printf("7. View Results\n");
                printf("8. Initiate branch change\n");
                printf("9. Filter Student\n");
                printf("10. Show Feedback\n");
                printf("11. Change Password\n");
            start:
                printf("Enter your choice(pls enter the number): ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 0:
                    printf("Exiting Classvault. Goodbye!\n");
                    break;
                case 1:
                {
                    do
                    {
                        printf("\nAdd person\n");
                        printf("0. Exit\n");
                        printf("1. Add teacher\n");
                        printf("2. Add student\n");
                        printf("Enter your choice(pls enter the number): ");
                    goto2:
                        scanf("%d", &choice2);
                        getchar();

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting Add person.\n");
                            sleep(1);
                            break;
                        case 1:
                            addteacher();
                            password_generator_main();

                            break;
                        case 2:
                            addstudent();
                            password_generator_main();

                            break;
                        default:
                            printf("Enter Correct number :");
                            goto goto2;
                            break;
                        }
                    } while (choice2 != 0);
                    break;
                }

                case 2:
                {
                    do
                    {
                        printf("\nView person\n");
                        printf("0. Exit\n");
                        printf("1. View teachers\n");
                        printf("2. View students\n");
                        printf("Enter your choice(pls enter the number): ");
                    goto3:
                        scanf("%d", &choice2);
                        getchar();

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting View person.\n");
                            sleep(1);
                            break;
                        case 1:
                            viewteacher();
                            break;
                        case 2:
                            viewstudent_for_teacher();
                            break;
                        default:
                            printf("Enter Correct number :");
                            goto goto3;
                            break;
                        }
                    } while (choice2 != 0);
                    break;
                }
                case 3:
                {
                    do
                    {
                        printf("\nRemove person\n");
                        printf("0. Exit\n");
                        printf("1. Remove teacher\n");
                        printf("2. Remove student\n");
                        printf("Enter your choice(pls enter the number): ");
                    goto4:
                        scanf("%d", &choice2);
                        getchar();

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting Remove person.\n");
                            sleep(1);
                            break;
                        case 1:
                            removeteacher();
                            break;
                        case 2:
                            removestudent();
                            break;
                        default:
                            printf("Enter Correct number :");
                            goto goto4;
                            break;
                        }
                    } while (choice2 != 0);
                    break;
                }
                case 4:
                {
                    do
                    {
                        printf("\nTeacher-search Menu\n");
                        printf("0. Exit\n");
                        printf("1. Search by name.\n");
                        printf("2. Search by mobile number.\n");
                        printf("Enter your choice(pls enter the number): ");
                        scanf("%d", &choice2);
                        getchar();

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting Teacher-search.\n");
                            sleep(1);
                            break;
                        case 1:
                        {
                            char teacher_name[50];
                            printf("Enter the name : ");
                            scanf("%s", &teacher_name);
                            strupr(teacher_name);
                            searchbyteachername(teacher_name);
                            break;
                        }
                        case 2:
                        {
                            long long int mob_num;
                            printf("Enter your mobile no.: ");
                            while (1)
                            {
                                scanf("%lld", &mob_num);
                                long long int temp = mob_num;
                                int count = 0;
                                while (temp)
                                {
                                    temp /= 10;
                                    count++;
                                }
                                if (count == 10)
                                {
                                    break;
                                }
                                else
                                    printf("Enter a valid phone number\n");
                            }
                            searchbyteachermobno(mob_num);
                            break;
                        }
                        }
                    } while (choice2 != 0);
                    break;
                }
                case 5:
                {
                    do
                    {
                        printf("\nStudent-search Menu\n");
                        printf("0. Exit\n");
                        printf("1. Search by name.\n");
                        printf("2. Search by mobile number.\n");
                        printf("3. Search by Roll no.\n");
                        printf("Enter your choice(pls enter the number): ");
                    goto5:
                        scanf("%d", &choice2);
                        fflush(stdin);

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting student-search.\n");
                            sleep(1);
                            break;
                        case 1:
                        {
                            char stud_name[50];
                            printf("Enter the name : ");
                            gets(stud_name);
                            strupr(stud_name);
                            searchbyname(stud_name);
                            break;
                        }
                        case 2:
                        {
                            long long int mob_num;
                            printf("Enter your mobile no.: ");
                            while (1)
                            {
                                scanf("%lld", &mob_num);
                                long long int temp = mob_num;
                                int count = 0;
                                while (temp)
                                {
                                    temp /= 10;
                                    count++;
                                }
                                if (count == 10)
                                {
                                    break;
                                }
                                else
                                    printf("Enter a valid phone number\n");
                            }
                            searchbymobno(mob_num);
                            break;
                        }
                        case 3:
                        {
                            char roll_num[10];
                            printf("Enter the Roll no. : ");
                            scanf("%s", &roll_num);
                            getchar();
                            strupr(roll_num);
                            searchbyrollno(roll_num);
                            break;
                        }
                        default:
                            printf("Enter Correct number :");
                            goto goto5;
                            break;
                        }
                    } while (choice2 != 0);
                    break;
                }
                case 6:
                {
                    marks_input_main();
                    break;
                }
                case 7:
                {
                    marks_main();
                    view_marks_for_teacher();
                    break;
                }
                case 8:
                {
                    branch_change_admin_verify_main();
                    break;
                }
                case 9:
                {
                    do
                    {
                        printf("\nStudent-Filter Menu\n");
                        printf("0. Exit\n");
                        printf("1. Filter by branch.\n");
                        printf("2. Filter by state.\n");
                        printf("3. Filter by gender.\n");
                        printf("Enter your choice(pls enter the number): ");
                    goto6:
                        scanf("%d", &choice2);
                        getchar();

                        switch (choice2)
                        {
                        case 0:
                            printf("Exiting student-Filter\n");
                            sleep(1);
                            break;
                        case 1:
                        {
                            char stud_branch[4];
                            int choice;
                            printf("Enter the branch:\n");
                            printf("1 for CE.\n2 for CS.\n3 for EE.\n4 for MM.\n5 for EC.\n6 for ME.\n");
                        here3:
                            scanf("%d", &choice);
                            switch (choice)
                            {
                            case 1:
                                strcpy(stud_branch, "CE");
                                break;
                            case 2:
                                strcpy(stud_branch, "CS");
                                break;
                            case 3:
                                strcpy(stud_branch, "EE");
                                break;
                            case 4:
                                strcpy(stud_branch, "MM");
                                break;
                            case 5:
                                strcpy(stud_branch, "EC");
                                break;
                            case 6:
                                strcpy(stud_branch, "ME");
                                break;
                            default:
                                printf("Enter correct number:");
                                goto here3;
                                break;
                            }
                            groupbybranch(stud_branch);
                            break;
                        }
                        case 2:
                        {
                            char stud_state[15];
                            printf("Enter the state : ");
                            gets(stud_state);
                            strupr(stud_state);
                            groupbystate(stud_state);
                            break;
                        }
                        case 3:
                        {
                            char gender;
                            char stud_gender[10];
                            printf("Enter your gender.\n");
                        there:
                            printf("M for male and F for female.\n");
                            scanf("%c", &gender);
                            getchar();
                            if (gender == 'M' || gender == 'm')
                            {
                                strcpy(stud_gender, "MALE");
                            }
                            else if (gender == 'F' || gender == 'f')
                            {
                                strcpy(stud_gender, "FEMALE");
                            }
                            else
                            {
                                printf("Enter correct gender : ");
                                goto there;
                            }
                            groupbygender(stud_gender);
                            break;
                        }
                        default:
                            printf("Enter Correct number :");
                            goto goto6;
                            break;
                        }
                    } while (choice2 != 0);
                    break;
                }

                case 10:
                    showfeedback();
                    break;
                case 11:
                    password_change_employee_main();
                    break;
                default:
                    printf("Invalid choice. Please retry..\n");
                    goto start;
                }
                sleep(1);
            } while (choice != 0);
        }
        break;
    default:
        printf("Enter Correct number :");
        goto goto1;
        break;
    }

    return 0;
}
