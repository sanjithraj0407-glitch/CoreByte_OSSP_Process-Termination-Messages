#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* =========================================================
   COLORS
   ========================================================= */

#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"

/* =========================================================
   DASHBOARD
   ========================================================= */

void display_dashboard()
{
    printf("\n");

    /* Colored heading only */
    printf(BLUE BOLD);
    printf("===============================================================\n");
    printf("             PROCESS TERMINATION MESSAGE SYSTEM\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    /* Colored heading only */
    printf(MAGENTA BOLD);
    printf("                         DASHBOARD\n");
    printf(RESET);

    printf("---------------------------------------------------------------\n");
    printf("| %-25s | %-25s |\n", "Property", "Value");
    printf("---------------------------------------------------------------\n");

    /* Everything below is white */
    printf("| %-25s | %-25s |\n",
           "System", "Linux / Ubuntu");

    printf("| %-25s | %-25s |\n",
           "Project Type", "Process Management");

    printf("| %-25s | %-25s |\n",
           "Operations", "4");

    printf("| %-25s | %-25s |\n",
           "Process Model", "Parent - Child");

    printf("| %-25s | %-25s |\n",
           "System Calls", "fork / waitpid / exit");

    printf("| %-25s | %-25s |\n",
           "System Status", "READY");

    printf("---------------------------------------------------------------\n");

    printf("\n");

    printf("Press ENTER to continue...");
}


/* =========================================================
   AVAILABLE OPERATIONS
   ========================================================= */

void display_menu()
{
    printf("\n\n");

    /* Colored heading only */
    printf(BLUE BOLD);
    printf("===============================================================\n");
    printf("                     AVAILABLE OPERATIONS\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    /* White table */
    printf("+------+-----------------------------------------------+\n");
    printf("| %-4s | %-45s |\n", "No.", "Operation");
    printf("+------+-----------------------------------------------+\n");

    printf("| %-4d | %-45s |\n",
           1, "Successful Process");

    printf("| %-4d | %-45s |\n",
           2, "Process With Error");

    printf("| %-4d | %-45s |\n",
           3, "Process Terminated By Signal");

    printf("| %-4d | %-45s |\n",
           4, "Multiple Child Processes");

    printf("| %-4d | %-45s |\n",
           5, "Exit");

    printf("+------+-----------------------------------------------+\n");
}


/* =========================================================
   OPTION 1
   SUCCESSFUL PROCESS
   ========================================================= */

void successful_process()
{
    pid_t pid;
    int status;

    printf("\n");

    /* Colored heading */
    printf(GREEN BOLD);
    printf("===============================================================\n");
    printf("                  EXECUTION - OPTION 1\n");
    printf("                  SUCCESSFUL PROCESS\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    printf("[Parent] Creating child process using fork()...\n");

    pid = fork();

    if (pid < 0)
    {
        perror("[Parent] fork() failed");
        return;
    }

    if (pid == 0)
    {
        printf("\n");
        printf("-------------------- CHILD PROCESS --------------------\n");

        printf("[Child] PID  : %d\n", getpid());
        printf("[Child] PPID : %d\n", getppid());

        printf("[Child] Performing task...\n");

        sleep(2);

        printf("[Child] Task completed successfully.\n");
        printf("[Child] Calling exit(0)...\n");

        exit(0);
    }
    else
    {
        printf("[Parent] PID      : %d\n", getpid());
        printf("[Parent] Child PID: %d\n", pid);

        printf("[Parent] Waiting for child using waitpid()...\n");

        waitpid(pid, &status, 0);

        printf("\n");

        /* Colored heading */
        printf(GREEN BOLD);
        printf("---------------- TERMINATION RESULT ----------------\n");
        printf(RESET);

        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);

            printf("[Parent] Child terminated normally.\n");
            printf("[Parent] Exit Status : %d\n", exit_status);

            printf("\n");
            printf("RESULT: SUCCESS\n");
            printf("The child process completed successfully.\n");
        }
    }
}


/* =========================================================
   OPTION 2
   PROCESS WITH ERROR
   ========================================================= */

void error_process()
{
    pid_t pid;
    int status;

    printf("\n");

    /* Colored heading */
    printf(RED BOLD);
    printf("===============================================================\n");
    printf("                  EXECUTION - OPTION 2\n");
    printf("                    PROCESS WITH ERROR\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    printf("[Parent] Creating child process using fork()...\n");

    pid = fork();

    if (pid < 0)
    {
        perror("[Parent] fork() failed");
        return;
    }

    if (pid == 0)
    {
        printf("\n");
        printf("-------------------- CHILD PROCESS --------------------\n");

        printf("[Child] PID  : %d\n", getpid());
        printf("[Child] PPID : %d\n", getppid());

        printf("[Child] Performing task...\n");

        sleep(2);

        printf("[Child] Task failed.\n");
        printf("[Child] Calling exit(1)...\n");

        exit(1);
    }
    else
    {
        printf("[Parent] PID      : %d\n", getpid());
        printf("[Parent] Child PID: %d\n", pid);

        printf("[Parent] Waiting for child using waitpid()...\n");

        waitpid(pid, &status, 0);

        printf("\n");

        /* Colored heading */
        printf(RED BOLD);
        printf("---------------- TERMINATION RESULT ----------------\n");
        printf(RESET);

        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);

            printf("[Parent] Child terminated normally.\n");
            printf("[Parent] Exit Status : %d\n", exit_status);

            printf("\n");
            printf("RESULT: ERROR\n");
            printf("The child process terminated with an error status.\n");
        }
    }
}


/* =========================================================
   OPTION 3
   SIGNAL TERMINATION
   ========================================================= */

void signal_process()
{
    pid_t pid;
    int status;

    printf("\n");

    /* Colored heading */
    printf(YELLOW BOLD);
    printf("===============================================================\n");
    printf("                  EXECUTION - OPTION 3\n");
    printf("               SIGNAL BASED TERMINATION\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    printf("[Parent] Creating child process using fork()...\n");

    pid = fork();

    if (pid < 0)
    {
        perror("[Parent] fork() failed");
        return;
    }

    if (pid == 0)
    {
        printf("\n");
        printf("-------------------- CHILD PROCESS --------------------\n");

        printf("[Child] PID  : %d\n", getpid());
        printf("[Child] PPID : %d\n", getppid());

        printf("[Child] Running task...\n");

        sleep(2);

        printf("[Child] Sending SIGTERM to itself...\n");

        kill(getpid(), SIGTERM);

        /*
           This line normally will NOT execute because
           SIGTERM terminates the child process.
        */
        exit(0);
    }
    else
    {
        printf("[Parent] PID      : %d\n", getpid());
        printf("[Parent] Child PID: %d\n", pid);

        printf("[Parent] Waiting for child using waitpid()...\n");

        waitpid(pid, &status, 0);

        printf("\n");

        /* Colored heading */
        printf(YELLOW BOLD);
        printf("---------------- TERMINATION RESULT ----------------\n");
        printf(RESET);

        if (WIFSIGNALED(status))
        {
            int signal_number = WTERMSIG(status);

            printf("[Parent] Child was terminated by a signal.\n");
            printf("[Parent] Signal Number : %d\n", signal_number);

            printf("\n");
            printf("RESULT: SIGNAL TERMINATION\n");
            printf("The child process was terminated using SIGTERM.\n");
        }
    }
}


/* =========================================================
   OPTION 4
   MULTIPLE CHILD PROCESSES
   ========================================================= */

void multiple_process()
{
    pid_t child1, child2;
    int status1, status2;

    printf("\n");

    /* Colored heading */
    printf(MAGENTA BOLD);
    printf("===============================================================\n");
    printf("                  EXECUTION - OPTION 4\n");
    printf("                 MULTIPLE CHILD PROCESSES\n");
    printf("===============================================================\n");
    printf(RESET);

    printf("\n");

    printf("[Parent] Creating Child 1...\n");

    child1 = fork();

    if (child1 < 0)
    {
        perror("[Parent] fork() failed");
        return;
    }

    if (child1 == 0)
    {
        printf("\n");
        printf("-------------------- CHILD 1 --------------------\n");

        printf("[Child 1] PID  : %d\n", getpid());
        printf("[Child 1] PPID : %d\n", getppid());

        printf("[Child 1] Performing task...\n");

        sleep(2);

        printf("[Child 1] Task completed successfully.\n");
        printf("[Child 1] Calling exit(0)...\n");

        exit(0);
    }

    printf("\n");
    printf("[Parent] Creating Child 2...\n");

    child2 = fork();

    if (child2 < 0)
    {
        perror("[Parent] fork() failed");
        return;
    }

    if (child2 == 0)
    {
        printf("\n");
        printf("-------------------- CHILD 2 --------------------\n");

        printf("[Child 2] PID  : %d\n", getpid());
        printf("[Child 2] PPID : %d\n", getppid());

        printf("[Child 2] Performing task...\n");

        sleep(3);

        printf("[Child 2] Task completed with an error.\n");
        printf("[Child 2] Calling exit(1)...\n");

        exit(1);
    }

    printf("\n");
    printf("-------------------- PARENT PROCESS --------------------\n");

    printf("[Parent] PID     : %d\n", getpid());
    printf("[Parent] Child 1 : %d\n", child1);
    printf("[Parent] Child 2 : %d\n", child2);

    printf("\n");
    printf("[Parent] Waiting for Child 1...\n");

    waitpid(child1, &status1, 0);

    printf("[Parent] Child 1 Exit Status : %d\n",
           WEXITSTATUS(status1));

    printf("\n");
    printf("[Parent] Waiting for Child 2...\n");

    waitpid(child2, &status2, 0);

    printf("[Parent] Child 2 Exit Status : %d\n",
           WEXITSTATUS(status2));

    printf("\n");

    /* Colored heading */
    printf(MAGENTA BOLD);
    printf("---------------- TERMINATION SUMMARY ----------------\n");
    printf(RESET);

    printf("+------------+----------------+----------------+\n");
    printf("| Process    | Exit Status    | Result         |\n");
    printf("+------------+----------------+----------------+\n");

    printf("| Child 1    | %-14d | %-14s |\n",
           WEXITSTATUS(status1), "SUCCESS");

    printf("| Child 2    | %-14d | %-14s |\n",
           WEXITSTATUS(status2), "ERROR");

    printf("+------------+----------------+----------------+\n");
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main()
{
    int choice;

    while (1)
    {
        /*
           ===================================================
           FIRST SCREEN
           ONLY DASHBOARD
           ===================================================
        */

        system("clear");

        display_dashboard();

        /*
           Wait for ENTER.
           No operations are shown yet.
        */

        getchar();

        /*
           ===================================================
           SECOND SCREEN
           DASHBOARD + AVAILABLE OPERATIONS
           ===================================================
        */

        system("clear");

        display_dashboard();

        display_menu();

        printf("\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        /*
           ===================================================
           EXECUTE SELECTED OPERATION
           ===================================================
        */

        switch (choice)
        {
            case 1:
                successful_process();
                break;

            case 2:
                error_process();
                break;

            case 3:
                signal_process();
                break;

            case 4:
                multiple_process();
                break;

            case 5:

                system("clear");

                printf("\n");

                printf(BLUE BOLD);
                printf("===============================================================\n");
                printf("          PROCESS TERMINATION SYSTEM - EXIT\n");
                printf("===============================================================\n");
                printf(RESET);

                printf("\n");
                printf("System terminated successfully.\n");
                printf("Thank you!\n\n");

                exit(0);

            default:

                printf("\n");
                printf("Invalid choice! Please select 1-5.\n");
        }

        /*
           ===================================================
           RETURN TO DASHBOARD
           ===================================================
        */

        printf("\n");
        printf("Press ENTER to return to dashboard...");

        /*
           Remove the ENTER left by scanf()
        */
        while (getchar() != '\n');

        getchar();
    }

    return 0;
}