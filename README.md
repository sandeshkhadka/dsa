# DS
This repo contains code and explaination about following DS:
- [Stack](#stack)
- [Queue](#queue)
- [LinkedList](#linked-list)
- [Binary Search Tree](#binary-search-tree)

## Stack
A linear data structure where insertion and retrival of items can only be done from one end. Stack is LIFO
structure, meaning the last item added to the stack is the first one to be retrived. Stack is generally
implemented using either an array or a list. 
The last item inserted is commonly reffered to as TOS(Top of Stack).
### Operations on Stack
- push: 
    A push operation pushes or adds a new item to the stack. Implementation of push operation is straight forward
    and we can just append the new item to the underlying structure(list, array) and adjust the TOS to
    point to newly appended item.
- pop: 
    A pop operation removes the TOS from the stack. It also retrives and returns the TOS before removing from the stack.
    To implement the pop operation we just adjus the TOS to point to second last element, in array based
    implementation this can be done by simply decrementing the tos.
- peek: 
   Peek operation retrives the TOS without deleting it from the stack.

- isFull: 
    In static or array based implementation it is possible to exhaust the capacity of underling data structre
    i.e arry. In such implementation isFull operation is used to check if the stack is full. It returns
    boolean to indicate if the stack is full or not.

- isEmpty: 
    Checks if the stack is empty.

### Application of Stack

Stacks are generally used in scenario where we need to keep track of path or actions that led to some
condition and we may need to backtrack the path it took to reach the condition.

A simple real world example would be the "undo" feature. To implement "undo" action in any series of events,
we can store all the event as they occur in the stack and by the nature of stack the last occured event will be on
top so to undo it we can simply pop the stack and achieve the "undo" action.

Also in context of programming languages stack is used in function calls to keep track of return address and
local variables.
When a function call is made, the function itself may call other functions and so on, but at the end of
everything we want to return to the place from where the call was made, in other words we want to trace back
to calling function. So, a Stack is used.

Other similar application of stack:
- Evaluation mathematical expressions


## Queue
Queue is a linear data structure where items are inserted from one end and retrived or deleted from the other
end. Queue is FIFO structure, meaning the first item added to the queue is the first one to be retrived.
A queue can also be implemented using an array or a list.

Unlike stack, In Queue two pointers are used to keep track of items, a **front** pointer tracks the begining
of the queue from where the elements are accessed or deleted and a **rear** pointer that tracks the end of the
queue from where items enter the queue.

### Operations on Queue
- enqueue: 
    A enqueue operation adds a new item to the queue. Implementation of enqueue operation is straight forward
    and we can just append the new item to the underlying structure(list, array) and adjust the **rear**
    pointer to point to newly appended item.
- dequeue: 
    A dequeue operation removes the item pointed by **front** from the queue. It also retrives and returns the item before removing it from the queue.
    To implement dequeue we need to return the item pointer by front and increment front to point to next
    item in the queue.

- isFull: 
    Like in Stack in static or array based implementation it is possible to exhaust the capacity of underling data structure.
    In such implementation isFull operation is used to check if the queue is full. If rear pointer is equal to
    max size then the queue is said to be full.

- isEmpty: 
    Checks if the queue is empty. In array based linear queue this is implemented by comparing front and rear
    pointer. If front > rear then queue is said to be empty.


### Application of Queue
Queues are mostly used when we need to observe and process multiple events but the events may occur faster
then they can processed, in such cases a queue is maintained to keep all incomming events until they are
processed. Since insertion and deletion is performed on two different ends, incomming events does not distrub
the processing of previously enqueued event.

For example: In a registration system, multiple registration request can come before one registration is
processed. So, we use queue to store incomming registration requests and process them one by one.

Similarly, in a computer multiple processes may request CPU time but only one can use CPU time at a time, so a
queue is maintained to stored all the request and service them one by one.


### Types of Queue
- Simple Queue: It is the simplest type of queue and it is the queue we discussed above.

- Circular Queue: If first and last position of a simple queue are connected the resulting queue is a circular
  queue. It offers better memory usage then the simple queue because when we dequeue an item from a simple
  queue we simply move to next item but the memory used by recently dequeued item is wasted and never used, by
  connecting the first and last position in the queue we allowed to use that wasted memory to enqueue new
  items.

- Priority Queue: In simple queue the first item to be dequed is the one that was enqued first but in certain
  scenario this might not be the wisest thing to do. For example in the registration system mentioned above we
  might want to process VIP registrations first. What we have is different priority, when priority of all the
  events are not equal we need a priority queue.

  A priority queue uses some defined metric/property to determine the priority of items and the item with the
  highest priority is dequeued first.

