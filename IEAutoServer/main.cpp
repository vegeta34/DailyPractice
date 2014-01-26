#include	"IEAuto_pthread.h"

static int			nthreads;

//clifd_mutex = PTHREAD_MUTEX_INITIALIZER;     
//clifd_cond = PTHREAD_COND_INITIALIZER;
#ifndef HAVE_GETRUSAGE_PROTO
int     getrusage(int, struct rusage *);
#endif

void pr_cpu_time(void)
{
    double          user, sys;
    struct rusage   myusage, childusage;

    if (getrusage(RUSAGE_SELF, &myusage) < 0)
        err_sys("getrusage error");
    if (getrusage(RUSAGE_CHILDREN, &childusage) < 0)
        err_sys("getrusage error");

    user = (double) myusage.ru_utime.tv_sec +
        myusage.ru_utime.tv_usec/1000000.0;
    user += (double) childusage.ru_utime.tv_sec +
        childusage.ru_utime.tv_usec/1000000.0;
    sys = (double) myusage.ru_stime.tv_sec +
        myusage.ru_stime.tv_usec/1000000.0;
    sys += (double) childusage.ru_stime.tv_sec +
        childusage.ru_stime.tv_usec/1000000.0;

    printf("\nuser time = %g, sys time = %g\n", user, sys);
}

void sig_int(int signo)
{
    int		i;
    void	pr_cpu_time(void);

    pr_cpu_time();

    for (i = 0; i < nthreads; i++)
        printf("thread %d, %ld connections\n", i, tptr[i].thread_count);

    exit(0);
}

int main(int argc, char **argv)
{
    int			i, listenfd, connfd;
    void		sig_int(int), thread_make(int);
    socklen_t	addrlen, clilen;
    struct sockaddr	*cliaddr;

    if (argc == 3)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 4)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv08 [ <host> ] <port#> <#threads>");
    cliaddr = (sockaddr*)malloc(addrlen);

    nthreads = atoi(argv[argc-1]);
    tptr = (Thread*)calloc(nthreads, sizeof(Thread));
    iget = iput = 0;

    /* 4create all the threads */
    for (i = 0; i < nthreads; i++)
        thread_make(i);		/* only main thread returns */

    Signal(SIGINT, sig_int);

    for ( ; ; ) {
        clilen = addrlen;
        connfd = Accept(listenfd, cliaddr, &clilen);

        pthread_mutex_lock(&clifd_mutex);
        clifd[iput] = connfd;
        if (++iput == MAXNCLI)
            iput = 0;
        if (iput == iget)
            err_quit("iput = iget = %d", iput);
        pthread_cond_signal(&clifd_cond);
        pthread_mutex_unlock(&clifd_mutex);
    }
}
/* end serv08 */

