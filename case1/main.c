#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define BUF_SIZE    1024 //1KB
#define BUF_NUM     2

static struct buffer_struct {
    char buffer[BUF_NUM][BUF_SIZE];
    int size[BUF_NUM];

/* id's SM: IDLE => SOCK_READ => READ_DONE => FILE_WRITE => IDLE
**
** read-process     write-process
** ------------     -------------
**    IDLE      (↓)
**   SOCK_READ  (↓)
**   READ_DONE  (↓)
**
**              (↓) FILE_WRITE
**              (↑)    IDLE
*/
#define ST_IDLE        0
#define ST_SOCK_READ   1
#define ST_READ_DONE   2
#define ST_FILE_WRITE  3
    int state[BUF_NUM];

    int exit_r;
    int exit_w;
} *gbuf;

static FILE *gin, *gout;
static size_t gsize;

static int buffer_get_done(struct buffer_struct* buf)
{
    int i;

    for(i = 0; i < BUF_NUM; i++) {
        if (ST_READ_DONE == buf->state[i])
            return i;
    }

    return -1;
}

static int buffer_block_idle(struct buffer_struct* buf, int *exit)
{
    int i;

    for( ; !*exit; ) {
        for(i = 0; i < BUF_NUM; i++) {
            if(ST_IDLE == buf->state[i])
                return i;
        }

        usleep(1000);
    }

    return -1;
}

static void buffer_set_state(struct buffer_struct* buf, int dev_id, int state)
{
    if(dev_id < 0 || dev_id >= BUF_NUM)
        return;

    buf->state[dev_id] = state;
}

static int transfer_async(struct buffer_struct* buf, FILE* fpp[2])
{
    pid_t pid;
    int res = 0;
    size_t remain = gsize;

    printf("%s\n", __FUNCTION__);
    printf("remain %ld\n", remain);

    if((pid=fork()) == 0) {
        int dev_w;
        size_t put;

        printf("write-process\n");

        do {
            if((dev_w = buffer_get_done(buf)) != -1) {
                buffer_set_state(buf, dev_w, ST_FILE_WRITE);

                put = fwrite(buf->buffer[dev_w], 1, buf->size[dev_w], fpp[1]);
                if(put != buf->size[dev_w]) {
                    res = -1;
                    break;
                }
                remain -= put;

                buffer_set_state(buf, dev_w, ST_IDLE);
            }
        } while (remain > 0 && !buf->exit_r);

        buf->exit_w = 1;
        printf("write-process exit with %d\n", res);
        exit(res);
    }
    else if(pid > 0) {
        size_t maxium = BUF_SIZE;
        size_t count, got;
        int dev_r;
        int res_w;

        printf("read-process\n");

        if(remain > 0) {
            do {
                if((dev_r = buffer_block_idle(buf, &buf->exit_w)) != -1) {
                    buffer_set_state(buf, dev_r, ST_SOCK_READ);

                    count = remain < maxium ? remain : maxium;
                    if((got = fread(buf->buffer[dev_r], 1, count, fpp[0])) <= 0) {
                        res = -1;
                        buf->exit_r = 1;
                        break;
                    }
                    buf->size[dev_r] = got;
                    buffer_set_state(buf, dev_r, ST_READ_DONE);

                    remain -= got;
                }
                // printf("remain %ld bytes\n", remain);
            } while (remain > 0 && !buf->exit_w);
        }
        else {
            res = -1;
        }

        printf("read exit with %d\n", res);

        // waiting for write-process exit
        waitpid(pid, (int*)&res_w, 0);
        if(res_w) res = res_w;

        // buf->exit_r = 1;
        printf("read-process exit with %d\n", res);
    }
    else {
        res = -2;
        printf("fork error\n");
    }

    return res;
}

static void setup_res(void)
{
    printf("%s\n", __FUNCTION__);

    gin = fopen("in.jpg", "r");
    gout = fopen("out.jpg", "w+");
    gbuf = (struct buffer_struct*)mmap(NULL, sizeof(struct buffer_struct), PROT_READ|PROT_WRITE,
                MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    assert(gin);
    assert(gout);
    assert(gbuf);

    fseek(gin, 0, SEEK_END);
    gsize = ftell(gin);
    fseek(gin, 0, SEEK_SET);

    bzero(gbuf, sizeof(struct buffer_struct));
}

static void shutdown_res(void)
{
    printf("%s\n", __FUNCTION__);

    fclose(gin);
    fclose(gout);
    munmap(gbuf, sizeof(struct buffer_struct));
}

int main()
{
    FILE* fpp[2];

    setup_res();

    fpp[0] = gin;
    fpp[1] = gout;
    transfer_async(gbuf, fpp);

    shutdown_res();
    return 0;
}
