#include <stdio.h>
//#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 3 
double amount =0;
int withdraw_input;
int deposit_input;
// the mutex identifier
pthread_mutex_t mutex;

//withdraw function
void* withdraw(){
pthread_mutex_lock(&mutex);
amount = amount - withdraw_input;
printf("Withdrawal amount = %.2f",amount);
printf("\n");
pthread_mutex_unlock(&mutex);

}

//deposit function 
void* deposit(){
pthread_mutex_lock(&mutex);
amount = amount + deposit_input;
printf("Deposit amount = %.2f",amount);
printf("\n");
pthread_mutex_unlock(&mutex);

}

int main(int argc, char *argv[]){
    deposit_input=atoi(argv[1]);
    withdraw_input=atoi(argv[2]);

    // the thread identifier
    pthread_t threads_withdraw[MAX_THREAD];
    pthread_t threads_deposit[MAX_THREAD]; 
    
    pthread_mutex_init(&mutex,NULL);
    for (int i = 0; i < MAX_THREAD; i++)
		{
            pthread_create(&threads_withdraw[i], NULL, withdraw, (void*)NULL);
            pthread_create(&threads_deposit[i], NULL, deposit, (void*)NULL);
        }

    //joins the threads 
    for (int i = 0; i < MAX_THREAD; i++) 
		{
            pthread_join(threads_withdraw[i], NULL); 
            pthread_join(threads_deposit[i], NULL); 
        }

    pthread_mutex_destroy(&mutex);
    printf("Final amount = %.2f",amount);
    printf("\n");
    return 0;

}

