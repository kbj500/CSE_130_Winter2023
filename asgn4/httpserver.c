// Asgn 2: A simple HTTP server.
// By: Eugene Chou
//     Andrew Quinn
//     Brian Zhao

#include "asgn2_helper_funcs.h"
#include "connection.h"
#include "response.h"
#include "request.h"
#include "debug.h"
#include "queue.h"
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/file.h>
#include <sys/stat.h>

#define CON_SIZE 30

void handle_connection(int);

void handle_get(conn_t *);
void handle_put(conn_t *);
void handle_unsupported(conn_t *);
void *worker_handle(void *arg);
//void *listener_handle(void*arg);
queue_t *conq = NULL;
size_t port;

int main(int argc, char **argv) {
    printf("\nargc %d\n", argc);
    if (argc < 2 || argc > 4) {
        warnx("wrong arguments: %s port_num", argv[0]);
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int c, tflag;
    unsigned int nthread;
    char *numThreads = NULL;

    while ((c = getopt(argc, argv, "t:")) != -1) {
        switch (c) {
        case 't':
            if (argc <= 3) {
                warnx("wrong arguments: %s port_num", argv[0]);
                fprintf(stderr, "usage: %s <port>\n", argv[0]);
                return EXIT_FAILURE;
            }
            tflag = 1;
            nthread = (unsigned int) strtoull(optarg, &numThreads, 10);
            if (numThreads && *numThreads != '\0') {
                warnx("invalid port number: %s", optarg);
                return EXIT_FAILURE;
            }
            printf("\nt flag true, number of threads: %d\n", nthread);
            break;
        }
    }
    if (!tflag) {
        nthread = 4;
        if (argc > 2) {
            warnx("wrong arguments: %s port_num", argv[0]);
            fprintf(stderr, "usage: %s <port>\n", argv[0]);
            return EXIT_FAILURE;
        }
        printf("\nt flag false, number of threads: %d\n", nthread);
    }

    char *endptr = NULL;
    port = (size_t) strtoull(argv[optind], &endptr, 10);
    if (endptr && *endptr != '\0') {
        warnx("invalid port number: %s", argv[optind]);
        return EXIT_FAILURE;
    }

    printf("\n port number: %zu\n", port);

    conq = queue_new(CON_SIZE);

    //    pthread_t tlis = pthread_create(&tlis, NULL, listener_handle, NULL);

    pthread_t tpool[nthread];

    for (unsigned int i = 0; i < nthread; i++) {
        pthread_create(&tpool[i], NULL, worker_handle, NULL);
    }

    signal(SIGPIPE, SIG_IGN);
    Listener_Socket sock;
    listener_init(&sock, port);

    while (1) {
        uintptr_t connfd = listener_accept(&sock);
        queue_push(conq, (void *) connfd);
        //        close(connfd);
    }

    return EXIT_SUCCESS;
}

/*
//this function is only for dispatch to listen and add connections to queue
void * listener_handle(){

	signal(SIGPIPE, SIG_IGN);
    	Listener_Socket sock;
    	listener_init(&sock, port);
	while(1){
		uintptr_t connfd = listener_accept(&sock);
		queue_push(conq,(void*) connfd);
	}
}*/

//this function is only for workers to handle connections on the queue
void *worker_handle() {

    while (1) {
        uintptr_t popcon;
        queue_pop(conq, (void **) &popcon);
        handle_connection(popcon);
        close(popcon);
    }
}

void handle_connection(int connfd) {

    conn_t *conn = conn_new(connfd);

    const Response_t *res = conn_parse(conn);

    if (res != NULL) {
        conn_send_response(conn, res);
    } else {
        debug("%s", conn_str(conn));
        const Request_t *req = conn_get_request(conn);
        if (req == &REQUEST_GET) {
            handle_get(conn);
        } else if (req == &REQUEST_PUT) {
            handle_put(conn);
        } else {
            handle_unsupported(conn);
        }
    }

    conn_delete(&conn);
}

void handle_get(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    //debug("GET request not implemented. But, we want to get %s", uri);
    const Response_t *res = NULL;

    // What are the steps in here?

    // 1. Open the file.
    // If  open it returns < 0, then use the result appropriately
    //   a. Cannot access -- use RESPONSE_FORBIDDEN
    //   b. Cannot find the file -- use RESPONSE_NOT_FOUND
    //   c. other error? -- use RESPONSE_INTERNAL_SERVER_ERROR
    // (hint: check errno for these cases)!
    uint64_t fsize = 0;
    int fd = open(uri, O_RDONLY, 0600);

    if (fd < 0) {
        //	debug("%s: %d", uri, errno);
        if (errno == EACCES || errno == EISDIR) {
            res = &RESPONSE_FORBIDDEN;
            goto out;
        } else if (errno == ENOENT) {
            res = &RESPONSE_NOT_FOUND;
            goto out;
        } else {
            res = &RESPONSE_INTERNAL_SERVER_ERROR;
            goto out;
        }
    }

    flock(fd, LOCK_SH);

    // 2. Get the size of the file.
    // (hint: checkout the function fstat)!
    struct stat fs;
    fstat(fd, &fs);

    // Get the size of the file.

    fsize = fs.st_size;

    // 3. Check if the file is a directory, because directories *will*
    // open, but are not valid.
    // (hint: checkout the macro "S_IFDIR", which you can use after you call fstat!)

    if (fs.st_mode & S_IFDIR) {
        debug("File is a directory");
        res = &RESPONSE_FORBIDDEN;
        goto out;
    }

    // 4. Send the file
    // (hint: checkout the conn_send_file function!)

    conn_send_file(conn, fd, fsize);

    if (res == NULL) {
        res = &RESPONSE_OK;
    }
    fprintf(stderr, "%s,%s,%d,%s\n", request_get_str(conn_get_request(conn)), conn_get_uri(conn),
        response_get_code(res), conn_get_header(conn, "Request-Id"));
    flock(fd, LOCK_UN);
    close(fd);

    return;

out:

    fprintf(stderr, "%s,%s,%d,%s\n", request_get_str(conn_get_request(conn)), conn_get_uri(conn),
        response_get_code(res), conn_get_header(conn, "Request-Id"));

    conn_send_response(conn, res);
}

void handle_unsupported(conn_t *conn) {
    debug("handling unsupported request");

    // send responses
    fprintf(stderr, "%s,%s,%d,%s\n", request_get_str(conn_get_request(conn)), conn_get_uri(conn),
        501, conn_get_header(conn, "Request-Id"));
    conn_send_response(conn, &RESPONSE_NOT_IMPLEMENTED);
}

void handle_put(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    const Response_t *res = NULL;
    debug("handling put request for %s", uri);

    // Check if file already exists before opening it.
    bool existed = access(uri, F_OK) == 0;
    debug("%s existed? %d", uri, existed);

    // Open the file..
    int fd = open(uri, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd < 0) {
        debug("%s: %d", uri, errno);
        if (errno == EACCES || errno == EISDIR || errno == ENOENT) {
            res = &RESPONSE_FORBIDDEN;
            goto out;
        } else {
            res = &RESPONSE_INTERNAL_SERVER_ERROR;
            goto out;
        }
    }

    flock(fd, LOCK_EX);
    res = conn_recv_file(conn, fd);

    if (res == NULL && existed) {
        res = &RESPONSE_OK;
    } else if (res == NULL && !existed) {
        res = &RESPONSE_CREATED;
    }

    flock(fd, LOCK_UN);

    close(fd);

out:

    fprintf(stderr, "%s,%s,%d,%s\n", request_get_str(conn_get_request(conn)), conn_get_uri(conn),
        response_get_code(res), conn_get_header(conn, "Request-Id"));

    conn_send_response(conn, res);
}
