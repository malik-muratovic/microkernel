#include <stddef.h>
#include "lists.h"

typedef void (Function)(void);
typedef struct task Task;
typedef struct message Message;

#define MESSAGE_TYPE_NOREPLY ((Message_type) 1)

/* kernel_init: Initialize kernel data structures and start
the scheduler. This function may only be called once. */
void kernel_init(void);

/* task_create: Allocate and initialize a task. The task entry
point is given by entry. At least stacksize bytes will be
allocated for program stack. A pointer to the newly created
task is returned, or NULL if an error occured. */
Task *task_create(Function *entry, size_t stacksize);

/* task_start: Add a task to the scheduler. The return value
is task on success or NULL on error. */
Task *task_start(Task *task);

/* task_self: Find self. A pointer to the running task is
returned. */
Task *task_self(void);

/* task_set_priority: Set scheduling priority of the running
task. */
void task_set_priority(Task *task, Priority priority);

/* task_get_priority: Get task priority. */
Priority task_get_priority(Task *task);

/* message_create: Allocate and prepare a message for use. A
pointer to the newly created task is returned, or NULL if an
error occured. */
Message *message_create(void);

/* message_free: Free memory used by message. */
void message_free(Message *message);

/* message_put: Add a message to task's message queue. The
content of message is owned by the destination task at return
of the call. Reuse of message is allowed after it has been
replied to by the destination. The call never blocks but may
cause a task switch. FIXME: Describe the semantics when called
from an ISR. */
void message_put(Task *destination, Message *message);

/* message_put_isr: Send message from an Interrupt Service
Routine. See message_put(). */
void message_put_isr(Task *destination, Message *message);

/* message_get: Deliver the next message. The call blocks if
the task's message queue is empty. Messages are delivered in
FIFO order. The receiving task will get temporary access to
the message and may read and modify it. After the message is
replied to with message_reply(), access is forbidden. */
Message *message_get(void);

/* message_reply: Reply on a message. */
void message_reply(Message *message);
