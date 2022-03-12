#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;
// global data
semaphore customers = 0;
semaphore barbers = 0;
semaphore cutting = 0;
pthread_mutex_t mutexs =0;


int customer1 = 0;

//start hair cut
void perform_hair_cut(){
    //update number of customers waiting for hair cut
    waiting(cutting);
}

//function to call for a hair cut
void request_haircut(){

    //get hair cut for a period of time
    signal(cutting);
}


//Barber function use to process
// let customers in for hair cut
void Barber(){
    while(true) {
        wait(customers);
        wait(mutexs);
        customer1 = customer1 - 1;
        signal(barbers);
        signal(mutexs);
        //start doing hair cut for customers
        perform_hair_cut();
    }
}

//Customer function to keep provide input how many customers
//entered into waiting room
void Customer(int n) {
    wait(mutexs); //mutex for getting customers
    if (customers < n) {
        customer1 = customer1 + 1; //update customer list
        signal(customers); //alert customers
        signal(mutexs);
        wait(barbers); //wait for available barber
        request_haircut();
    }
    else {
        signal(mutexs);
    }
}

//to run the barber shop rogram
int main() {

    printf("hello from %s!\n", "BarberShop2");
    //set number of customers come to Barber shop is 10 customers
    //each time.
    Customer(10);
    return 0;
}





