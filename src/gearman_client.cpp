/*
# Gearman server and library
# Copyright (C) 2012 Data Differential, http://datadifferential.com/
# All rights reserved.
#
# Use and distribution licensed under the BSD license.  See
# the COPYING file in this directory for full text.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <libgearman/gearman.h>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "custom_timer.h"

bool LoadFile(const char* filePath, std::vector<char>& content) {
    int input_fd;
    const int BUF_SIZE = 8192;
    ssize_t ret_in;
    char buffer[BUF_SIZE] = {0};

    input_fd = open(filePath, O_RDONLY);
    if (input_fd == -1) {
        return false;
    }

    while((ret_in = read(input_fd, &buffer, BUF_SIZE)) > 0) {
        size_t pos = content.size();
        content.resize(pos + (size_t)ret_in);
        memcpy(&content[pos], buffer, (size_t)ret_in);
    }

    close (input_fd);
    return true;
}

struct worker_data {
    int thread;
    int ms, delay;
    char* servers;
    char* function;
    std::vector<char>* input;
    worker_data() {
        delay = ms = thread = 0;
        input = NULL;
        servers = function = NULL;
    };
};

extern "C" void* worker(void* data) {

    worker_data* wd = (worker_data*)data;
    if(wd->delay)
        usleep(wd->delay);

    gearman_client_st *client = gearman_client_create(NULL);

    gearman_return_t ret = gearman_client_add_servers(client, wd->servers);
    if (gearman_failed(ret))
    {
        fprintf(stderr, "Can't create gearman client\n");
        gearman_client_free(client);
        return NULL;
    }
    //printf("gearman_client_add_server(%s, %d) DONE\n", wd->argv[1], atoi(wd->argv[2]));

    gearman_argument_t value = gearman_argument_make(0, 0, &(*wd->input)[0], wd->input->size());
    //printf("gearman_argument_make() DONE\n");

    msTimer timer;
    gearman_task_st *task = gearman_execute(client,
                                         wd->function, strlen(wd->function),  // function
                                         NULL, 0,  // no unique value provided
                                         NULL,
                                         &value, 0);
    if (task == NULL) // If gearman_execute() can return NULL on error
    {
        fprintf(stderr, "Error: %s\n", gearman_client_error(client));
        gearman_client_remove_servers(client);
        gearman_client_free(client);
        return NULL;
    }
    wd->ms = (int)timer.elapsedMs();
    //printf("gearman_execute() DONE\n");

    // Make sure the task was run successfully
    gearman_return_t task_ret = gearman_task_return(task);
    if (gearman_success(task_ret))
    {
        // Make use of value
        gearman_result_st *result = gearman_task_result(task);
//        if(!wd->thread) // print value only for first
//            printf("%s = %.*s\n", wd->argv[3], (int)gearman_result_size(result), gearman_result_value(result));
    }
    else {
        printf("ERROR: %s\n", gearman_strerror(task_ret));
        gearman_client_remove_servers(client);
        gearman_client_free(client);
        return NULL;
    }
 //   printf("gearman_task_return(%.2lf ms) DONE\n", time);

    gearman_client_remove_servers(client);
    gearman_client_free(client);
    return data;
}

int main(int argc, char* argv[])
{
    if(argc < 5) {
        printf("USAGE: gearman-client <servers> <function> <input_file> <num_threads = opt> <delay (ms) before nest thread = opt>\n");
        return EXIT_FAILURE;
    }

    std::vector<char> input;
    if(!LoadFile(argv[3], input)) {
        fprintf(stderr, "Can't load file %s\n", argv[4]);
        return EXIT_FAILURE;
    }
    printf("Input file %s with size %lu loaded.\n", argv[4], input.size());

    int num_threads = 1;
    if(argc > 4)
        num_threads = atoi(argv[4]);
    int delay = 0;
    if(argc > 5)
        delay = atoi(argv[5]) * 1000;
    std::vector<worker_data> data(num_threads);
    std::vector<pthread_t> threads(num_threads);
    for(int i = 0; i < num_threads; i++) {
        data[i].thread = i;
        data[i].input =& input;
        data[i].servers = argv[1];
        data[i].function = argv[2];
        if(delay)
            data[i].delay = rand() % delay;
        int created = pthread_create(&threads[i], NULL, worker, (void *)&data[i]);
        if(created) {
            printf("ERROR: thread %d is NOT created\n", i);
            return EXIT_FAILURE;
        }
    }

    int succeeded = 0;
    for(int i = 0; i < num_threads; i++) {
        void* success = NULL;
        pthread_join(threads[i], &success);
        if(success)
            succeeded++;
    }
    // wait for completion of all threads

    int ms = data[0].ms;
    int min_ms = ms, max_ms = ms, average_ms = 0;
    for(int i = 0; i < num_threads; i++) {
        ms = data[i].ms;
        if(ms < min_ms)
            min_ms = ms;
        if(ms > max_ms)
            max_ms = ms;
        average_ms += ms;
        printf("[% 3d] = % 8d ", data[i].thread, ms);
        if(!((i + 1) % 5))
            printf("\n");
    }
    average_ms /= num_threads;
    printf("\nSUCCEEDED %d of %d\nMIN = %d MAX = %d AVERAGE = %d\n", succeeded, num_threads, min_ms, max_ms, average_ms);

    return EXIT_SUCCESS;
}
