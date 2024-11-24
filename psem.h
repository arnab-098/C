#ifndef MYHEADER

#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>

typedef struct {
  sem_t *semp;
  char *sname;
  int ival;
} psem_t;

int psem_holdon(psem_t *s);
int psem_init(psem_t *s, const char *sname, int ival);
int psem_wait(psem_t *s);
int psem_post(psem_t *s);
int psem_destroy(psem_t *s);

#endif // !MYHEADER

int psem_holdon(psem_t *s) {
  int sval = -1;
  while (sval) {
    sem_getvalue(s->semp, &sval);
  }
  return (sval);
}

int psem_init(psem_t *s, const char *sname, int ival) {
  if (ival >= 0) {
    sem_unlink(sname);
  }
  s->semp = sem_open(sname, O_CREAT, 0666, ival);

  s->sname = (char *)malloc(strlen(sname)+1);
  strcpy(s->sname, sname);
  s->ival = ival;

  return (s->semp != SEM_FAILED);
}

int psem_wait(psem_t *s) {
  return (sem_wait(s->semp) != -1);
}

int psem_post(psem_t *s) {
  return (sem_post(s->semp) != -1);
}

int psem_destroy(psem_t *s) {
  sem_close(s->semp);
  int ret = sem_unlink(s->sname);
  free(s->sname);
  return (ret);
}
