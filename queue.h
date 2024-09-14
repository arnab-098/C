#ifndef MYHEADER_H
#define MYHEADER_H

#define SIZE 100

typedef struct Queue {
  int values [SIZE];
  int front, rear;
} queue;


queue create();
int isEmpty(queue *q);
int isFull(queue *q);
void enQueue(queue *q, int num);
int deQueue(queue *q);
void display(queue q);

#endif // !MYHEADER_H

queue create() {
  queue q;
  q.front = q.rear = -1;
  return q;
}


int isEmpty(queue *q) {
  return q->front == -1;
}

int isFull(queue *q) {
  return (q->front == 0 && q->rear == SIZE - 1) || (q->rear == q->front - 1);
}


void enQueue(queue *q, int num) {
  if (isFull(q)) {
    printf("QUEUE OVERFLOW\n");
    return;
  }
  if (q->front == -1) {
    q->front++;
  }
  q->rear = (q->rear+1)%SIZE;
  q->values[q->rear] = num;
}

int deQueue(queue *q) {
  if (isEmpty(q)) {
    printf("QUEUE UNDERFLOW\n");
    return EXIT_FAILURE;
  }
  int result = q->values[q->front];
  if (q->front == q->rear) {
    q->front = q->rear = 0;
  }
  else {
    q->front = (q->front+1)%SIZE;
  }
  return result;
}


void display(queue q) {
  if (isEmpty(&q)) {
    printf("QUEUE IS EMPTY\n");
    return;
  }
  for (int i=q.front; i!=q.rear; i=(i+1)%SIZE) {
    printf("%d\t", q.values[i]);
  }
  printf("%d\n", q.values[q.rear]);
}

