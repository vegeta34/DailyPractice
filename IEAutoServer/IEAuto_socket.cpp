#include "unp.h"

static int  read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t my_read(int fd, char *ptr)
{

    if (read_cnt <= 0) {
again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return(-1);
        } else if (read_cnt == 0)
            return(0);
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return(1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = (char*)vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;  /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return(n - 1);  /* EOF, n - 1 bytes were read */
        } else
            return(-1);     /* error, errno set by read() */
    }

    *ptr = 0;   /* null terminate like fgets() */
    return(n);
}

ssize_t readlinebuf(void **vptrptr)
{
    if (read_cnt)
        *vptrptr = read_ptr;
    return(read_cnt);
}
/* end readline */

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t     n;

    if ( (n = readline(fd, ptr, maxlen)) < 0)
        err_sys("readline error");
    return(n);
}

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
    int             listenfd, n;
    const int       on = 1;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("tcp_listen error for %s, %s: %s",
                host, serv, gai_strerror(n));
    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;       /* error, try next one */

        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */

        Close(listenfd);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL)    /* errno from final socket() or bind() */
        err_sys("tcp_listen error for %s, %s", host, serv);

    Listen(listenfd, LISTENQ);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;    /* return size of protocol address */

    freeaddrinfo(ressave);

    return(listenfd);
}
/* end tcp_listen */

/*
 *  * We place the wrapper function here, not in wraplib.c, because some
 *   * XTI programs need to include wraplib.c, and it also defines
 *    * a Tcp_listen() function.
 *     */

int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
    return(tcp_listen(host, serv, addrlenp));
}

Sigfunc * signal(int signo, Sigfunc *func)
{
    struct sigaction    act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;   /* SunOS 4.x */
#endif
    } else {
#ifdef  SA_RESTART
        act.sa_flags |= SA_RESTART;     /* SVR4, 44BSD */
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}
/* end signal */

Sigfunc * Signal(int signo, Sigfunc *func)    /* for our signal() function */
{
    Sigfunc *sigfunc;

    if ( (sigfunc = signal(signo, func)) == SIG_ERR)
        err_sys("signal error");
    return(sigfunc);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int     n;

again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef  EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
            if (errno == ECONNABORTED)
#endif
                goto again;
            else
                err_sys("accept error");
    }
    return(n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        err_sys("bind error");
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        err_sys("connect error");
}

void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    if (getpeername(fd, sa, salenptr) < 0)
        err_sys("getpeername error");
}

void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    if (getsockname(fd, sa, salenptr) < 0)
        err_sys("getsockname error");
}

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
{
    if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
        err_sys("getsockopt error");
}

#ifdef  HAVE_INET6_RTH_INIT
int Inet6_rth_space(int type, int segments)
{
    int ret;

    ret = inet6_rth_space(type, segments);
    if (ret < 0)
        err_quit("inet6_rth_space error");

    return ret;
}

void * Inet6_rth_init(void *rthbuf, socklen_t rthlen, int type, int segments)
{
    void *ret;

    ret = inet6_rth_init(rthbuf, rthlen, type, segments);
    if (ret == NULL)
        err_quit("inet6_rth_init error");

    return ret;
}

void Inet6_rth_add(void *rthbuf, const struct in6_addr *addr)
{
    if (inet6_rth_add(rthbuf, addr) < 0)
        err_quit("inet6_rth_add error");
}

void Inet6_rth_reverse(const void *in, void *out)
{
    if (inet6_rth_reverse(in, out) < 0)
        err_quit("inet6_rth_reverse error");
}

int Inet6_rth_segments(const void *rthbuf)
{
    int ret;

    ret = inet6_rth_segments(rthbuf);
    if (ret < 0)
        err_quit("inet6_rth_segments error");

    return ret;
}

struct in6_addr * Inet6_rth_getaddr(const void *rthbuf, int idx)
{
    struct in6_addr *ret;

    ret = inet6_rth_getaddr(rthbuf, idx);
    if (ret == NULL)
        err_quit("inet6_rth_getaddr error");

    return ret;
}
#endif

#ifdef HAVE_KQUEUE
int Kqueue(void)
{
    int ret;

    if ((ret = kqueue()) < 0)
        err_sys("kqueue error");
    return ret;
}

int Kevent(int kq, const struct kevent *changelist, int nchanges,
        struct kevent *eventlist, int nevents, const struct timespec *timeout)
{
    int ret;

    if ((ret = kevent(kq, changelist, nchanges,
                    eventlist, nevents, timeout)) < 0)
        err_sys("kevent error");
    return ret;
}
#endif


/* include Listen */
void Listen(int fd, int backlog)
{
    char    *ptr;

    /*4can override 2nd argument with environment variable */
    if ( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);

    if (listen(fd, backlog) < 0)
        err_sys("listen error");
}
/* end Listen */

#ifdef  HAVE_POLL
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout)
{
    int     n;

    if ( (n = poll(fdarray, nfds, timeout)) < 0)
        err_sys("poll error");

    return(n);
}
#endif

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags)
{
    ssize_t     n;

    if ( (n = recv(fd, ptr, nbytes, flags)) < 0)
        err_sys("recv error");
    return(n);
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
        struct sockaddr *sa, socklen_t *salenptr)
{
    ssize_t     n;

    if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
        err_sys("recvfrom error");
    return(n);
}

ssize_t Recvmsg(int fd, struct msghdr *msg, int flags)
{
    ssize_t     n;

    if ( (n = recvmsg(fd, msg, flags)) < 0)
        err_sys("recvmsg error");
    return(n);
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
        struct timeval *timeout)
{
    int     n;

    if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
        err_sys("select error");
    return(n);      /* can return 0 on timeout */
}

void Send(int fd, const void *ptr, size_t nbytes, int flags)
{
    if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
        err_sys("send error");
}

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
        const struct sockaddr *sa, socklen_t salen)
{
    if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
        err_sys("sendto error");
}

void Sendmsg(int fd, const struct msghdr *msg, int flags)
{
    unsigned int    i;
    ssize_t         nbytes;

    nbytes = 0; /* must first figure out what return value should be */
    for (i = 0; i < msg->msg_iovlen; i++)
        nbytes += msg->msg_iov[i].iov_len;

    if (sendmsg(fd, msg, flags) != nbytes)
        err_sys("sendmsg error");
}

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
    if (setsockopt(fd, level, optname, optval, optlen) < 0)
        err_sys("setsockopt error");
}

void Shutdown(int fd, int how)
{
    if (shutdown(fd, how) < 0)
        err_sys("shutdown error");
}

int Sockatmark(int fd)
{
    int     n;

    if ( (n = sockatmark(fd)) < 0)
        err_sys("sockatmark error");
    return(n);
}

/* include Socket */
int Socket(int family, int type, int protocol)
{
    int     n;

    if ( (n = socket(family, type, protocol)) < 0)
        err_sys("socket error");
    return(n);
}
/* end Socket */

void Socketpair(int family, int type, int protocol, int *fd)
{
    int     n;

    if ( (n = socketpair(family, type, protocol, fd)) < 0)
        err_sys("socketpair error");
}

ssize_t writen(int fd, const void *vptr, size_t n) /* Write "n" bytes to a descriptor. */
{
    size_t      nleft;
    ssize_t     nwritten;
    const char  *ptr;

    ptr = (const char*)vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;       /* and call write() again */
            else
                return(-1);         /* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}
/* end writen */

void Writen(int fd, void *ptr, size_t nbytes)
{
    if (writen(fd, ptr, nbytes) != nbytes)
        err_sys("writen error");
}

void Close(int fd)    
{
    if (close(fd) == -1)    
        err_quit("close error");    
}    
