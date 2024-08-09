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



