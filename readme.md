# Lambda C Data Structures

Data structures implemented in C

THIS LIBRARY IS JUST FOR WINDOWS UNTIL I RELEASE A VERSION FOR LINUX

## About Lambda C Data Structures (ldaCds)

I made this library in order to use it on future C app development.

You are free to collab with me sending more data structures, documentation or any content that could help.

## How to compile/install

You can either download the source code and compile it by yourself or download the library files (.a, .o, .h) and use it. You will find how to do so in the following sections.

### Compile

Download the source code, be sure that you also have make (to use the makefile) and GCC (15.0 i recommend) to compile the library.

Once you are sure you have all of this, you just need to open your command line, go to the folder where the source code is and type 'make'. If make aren't working then you can try to run those commands declared in the makefile but directly into the command line.

Once you do this (without ANY error) you will have the object files (.o), the library file (.a) and a copy of the headers (.h) into the build folder, you just need to move those file onto your working folder.

### Install

Once you have the ldaCds_vX.Y.Z.zip, you need to decompress the zip file and then locate the library files on your project folder, i recommend the following structure:

    MyProject/
        include/ <-- All the headers here
        lib/ <-- The libldaCds.a here
        obj/ <-- Optionally, if you want to use the object files alone

Once you have defined your structure, you can compile your executable file with, for example:

    gcc src/main.c -o myapp -Iinclude -Llib -lldaCds

## Documentation

This library includes many different data structures (DS) and all of them follow a simple standard of the library.

### Philosophy of LDA C DS

This library tries to make some following of errors when it comes to use data structure functions. The functions on this library just returns a pointer to a data structure, a pointer to a data structure node or a boolean, so, the functions just return a pointer or a boolean.

If the function returns pointer then you need to check if the result was NULL. If the result was NULL then it can be one of 2 options here:
- The main DS you passed as a parameter (with main im refering to the DS not to the DS node) is NULL
- Something went wrong at the function

If this happens, then you can check if the DS you passed is NULL, if it isn't NULL then you can check the status of the DS by seeking the (DS in low case)status member and compare it with a value of ldaCds_StatusCode (wich is a typedef enum). If the status is ldaCds_StatusNoErrorDetected (or 0) means the DS has no error, so maybe you passed a NULL value to the function, otherwise means the function went into an error and the DS save that error.

If the result is not NULL, then the function worked just fine (i assume).

This same mechanism works for the functions that return a boolean but instead of seeking for a NULL result you need to seek for the false result.

Not all the functions change the status of a DS, i would document this but i prefer not because is a lot of work.

All the functions that modify the data structure set the status code, if the function went wrong then a error status code is set, if the function went all right then NoErrorDetected status code is set. For example, ldaCds_StackPeek does not set any status code, because it does not modify anything on the DS so, please be careful, because if there's an error and you call another function and that function doesn't fail, then the error code will be cleaned.

Most functions have 1 or 2 function pointers on their parameters, this functions are user-defined functions to clean or do whatever they want. 

For example, the function ldaCds_StackPush takes 4 arguments: _stack, _stacknode and 2 function pointers _callbackSN and _callbackS. _stack is the stack where you are going to push the element, _stacknode is the node to be pushed to the stack. _callbackSN is a function that will be called at the end of the function if there is no errors, you can see that _callbackSN takes 1 argument that is ldaCds_StackNode (thats the reason of the SN at the end), well, the stack node that is going to be passed is the stack node that is being pushed.

Then, after calling _callbackSN, _callbackS will be called (the S means Stack in this case) with _stack as its parameter. This functions are present whenever there is a DS (_callbackS for Stack, _callbackSN for Stack Node in this example) or a DSN (Data Structure Node) and they will be executed before the function returns (and only if all inside the function went well). The functions that deletes (free from memory) DSN's or DS's change a little bit, they do what the usual function does but at the end, before setting the NoErrorDetected status code and return the function, they use free over the object to release the memory allocation.

Also is better to known that, once you popped, dequeued or removed an element, that element will not have reference to other nodes, for example, if i have this stack [1,2,3,4,5] where the 5 is at the top of the stack and the 1 is at the bottom, then the stack node that contains the 5 have a pointer to the node that contains the 4 and the node that contains the 4 have a pointer to the node with the 3 and so on. If i use ldaCds_StackPop i will get the node with the 5 BUT the member of the structure that is saving the memory address of the next node (in this case that member is called 'nodebelow') will not hold that address now, instead it will be NULL.

If by any chance you use states (either for DS or DSN) be sure to pass a cleaning function to the callbacks in order to release memory because the free function might not clean those pointers or the members pointed by those pointers.

All the functions and types start with the "ldaCds_" prefix, all the macros made by #define start with the "LDACDS_" prefix.

### ldaCds.h

This header includes just 2 things:
- LDACDS_CBF
- ldaCds_StatusCode

LDACDS_CBF is a preprocessor macro to create function pointers to use them as parameters in other functions, it takes 3 arguments: fn, type and name in that order. fn is the function name, anything you put as fn will be added to _callback and will form something like _callback(your fn name). type is the ldaCds data structure type, for example Stack, Queue, List, etc. name is the name of the variable you are going to use as a parameter for that function. For example LDACDS_CBF(TN,TreeNode,tn) will generate the parameter function pointer:

    void (*_callbackTN)(ldaCds_TreeNode *_tn)

The type ldaCds_StatusCode is a typedef enum used to defined the types of error codes for all the DS's. ldaCds_StatusNoErrorDetected is the default error code for all the new DS's.

You don't need (in theory) to include this header file because all the structures header files (for example ldaCds_Stack.h) already include it.

### Other header files

All the functions and types works as described before, so if you want to know wich functions belong to a DS, you just need to type ldaCds_ and the name of the DS, for example ldaCds_List to see all the List and ListNode functions, or ldaCds_Create to see the creation functions.

All the status code constants start with ldaCds_Status and the name of the status code