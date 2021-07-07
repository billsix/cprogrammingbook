#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define x86_64_linux
//#define x86_64_linux
//#define x86_64_linux

#ifdef x86_64_linux
#define SIZE_OF_INT32_T 4
#define SIZE_OF_BYTE_ADDRESS 8
#endif

#ifdef mips_linux
#define SIZE_OF_INT32_T 4
#define SIZE_OF_BYTE_ADDRESS 4
#endif

#ifdef arm32_linux
#define SIZE_OF_INT32_T 4
#define SIZE_OF_BYTE_ADDRESS 4
#endif

#define OFFSET_TO_NUMBER_OF_DISKS 0
#define OFFSET_TO_SOURCE OFFSET_TO_NUMBER_OF_DISKS + SIZE_OF_INT32_T
#define OFFSET_TO_TEMP OFFSET_TO_SOURCE + SIZE_OF_INT32_T
#define OFFSET_TO_TARGET OFFSET_TO_TEMP + SIZE_OF_INT32_T
#define OFFSET_TO_INSTRUCTION_OF_CALLER OFFSET_TO_TARGET + SIZE_OF_INT32_T
#define OFFSET_TO_FRAME_POINTER_OF_CALLER                                      \
  OFFSET_TO_INSTRUCTION_OF_CALLER + SIZE_OF_BYTE_ADDRESS
#define SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION                         \
  OFFSET_TO_FRAME_POINTER_OF_CALLER + OFFSET_TO_INSTRUCTION_OF_CALLER

#define BYTE uint8_t
#define BYTE_ADDRESS BYTE *

#define KILOBYTE 1024
#define MEGABYTE (KILOBYTE * KILOBYTE)

#define RAM_SIZE (10 * MEGABYTE)
BYTE random_access_memory[RAM_SIZE];

// byte of the begining of the frame
BYTE_ADDRESS frame_pointer = (BYTE_ADDRESS)(random_access_memory + RAM_SIZE);

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  const int32_t number_of_disks = 4;

  // create first frame frame
  {
    // the frame pointer is the current stack frame, aka, where the local
    // variables are
    frame_pointer =
        frame_pointer - SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
    // initialize first frame frame
    memcpy(frame_pointer + OFFSET_TO_NUMBER_OF_DISKS, /*dest*/
           &number_of_disks,                          /*src*/
           SIZE_OF_INT32_T                            /*numberOfBytes*/
    );
    {
      int32_t parameter = 1;
      memcpy(frame_pointer + OFFSET_TO_SOURCE, /*dest*/
             &parameter,                       /*src*/
             SIZE_OF_INT32_T);                 /*numberOfBytes*/
    }
    {
      int32_t parameter = 2;
      memcpy(frame_pointer + OFFSET_TO_TEMP, /*dest*/
             &parameter,                     /*src*/
             SIZE_OF_INT32_T);               /*numberOfBytes*/
    }
    {
      int32_t parameter = 3;
      memcpy(frame_pointer + OFFSET_TO_TARGET, /*dest*/
             &parameter,                       /*src*/
             SIZE_OF_INT32_T);                 /*numberOfBytes*/
    }
    {
      BYTE_ADDRESS label = &&endMain;
      memcpy(frame_pointer + OFFSET_TO_INSTRUCTION_OF_CALLER, /*dest*/
             &label,                                          /*src*/
             SIZE_OF_BYTE_ADDRESS                             /*numberOfBytes*/
      );
    }
    {
      BYTE_ADDRESS parameter = NULL;
      memcpy(frame_pointer + OFFSET_TO_FRAME_POINTER_OF_CALLER, /*dest*/
             &parameter,                                        /*src*/
             SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
      );
    }
  }

applyHanoiProcedure : {

  {
    int32_t number_of_disks_to_compare_to_one;
    memcpy(&number_of_disks_to_compare_to_one,        /*dest*/
           frame_pointer + OFFSET_TO_NUMBER_OF_DISKS, /*src*/
           SIZE_OF_INT32_T                            /*numberOfBytes*/
    );
    if (number_of_disks_to_compare_to_one != 1)
      goto notOne;
  }

  {
    int32_t source;
    memcpy(&source,                          /*dest*/
           frame_pointer + OFFSET_TO_SOURCE, /*src*/
           SIZE_OF_INT32_T                   /*numberOfBytes*/
    );
    int32_t target;
    memcpy(&target,                          /*dest*/
           frame_pointer + OFFSET_TO_TARGET, /*src*/
           SIZE_OF_INT32_T                   /*numberOfBytes*/
    );
    printf("Move from %d to %d\n", source, target);
  }
  goto endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked;
notOne:
moveNMinus1FromSourceToTemp:
  // prepare for function call
  // create new frame frame
  {
    BYTE_ADDRESS stack_frame_of_callee;
    stack_frame_of_callee =
        frame_pointer - 1 * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
    {
      int32_t number_of_disks;
      memcpy(&number_of_disks,                          /*dest*/
             frame_pointer + OFFSET_TO_NUMBER_OF_DISKS, /*src*/
             SIZE_OF_INT32_T                            /*numberOfBytes*/
      );
      int32_t parameter = number_of_disks - 1;
      memcpy(stack_frame_of_callee + OFFSET_TO_NUMBER_OF_DISKS, /*dest*/
             &parameter,                                        /*src*/
             SIZE_OF_INT32_T /*numberOfBytes*/
      );
    }
    memcpy(stack_frame_of_callee + OFFSET_TO_SOURCE, /*dest*/
           frame_pointer + OFFSET_TO_SOURCE,         /*src*/
           SIZE_OF_INT32_T                           /*numberOfBytes*/
    );
    memcpy(stack_frame_of_callee + OFFSET_TO_TEMP, /*dest*/
           frame_pointer + OFFSET_TO_TARGET,       /*src*/
           SIZE_OF_INT32_T                         /*numberOfBytes*/
    );
    memcpy(stack_frame_of_callee + OFFSET_TO_TARGET, /*dest*/
           frame_pointer + OFFSET_TO_TEMP,           /*src*/
           SIZE_OF_INT32_T                           /*numberOfBytes*/
    );
    {
      BYTE_ADDRESS label = &&move1ToTarget;
      memcpy(stack_frame_of_callee + OFFSET_TO_INSTRUCTION_OF_CALLER, /*dest*/
             &label,                                                  /*src*/
             SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
      );
    }
    memcpy(stack_frame_of_callee + OFFSET_TO_FRAME_POINTER_OF_CALLER, /*dest*/
           &frame_pointer,                                            /*src*/
           SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
    );
    frame_pointer = (BYTE_ADDRESS)stack_frame_of_callee;
  }
  goto applyHanoiProcedure;
move1ToTarget : {
  BYTE_ADDRESS stack_frame_of_callee;
  stack_frame_of_callee =
      frame_pointer - 1 * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
  {
    int32_t parameter = 1;
    memcpy(stack_frame_of_callee + OFFSET_TO_NUMBER_OF_DISKS, /*dest*/
           &parameter,                                        /*src*/
           SIZE_OF_INT32_T                                    /*numberOfBytes*/
    );
  }
  memcpy(stack_frame_of_callee + OFFSET_TO_SOURCE, /*dest*/
         frame_pointer + OFFSET_TO_SOURCE,         /*src*/
         SIZE_OF_INT32_T                           /*numberOfBytes*/
  );
  memcpy(stack_frame_of_callee + OFFSET_TO_TEMP, /*dest*/
         frame_pointer + OFFSET_TO_TEMP,         /*src*/
         SIZE_OF_INT32_T                         /*numberOfBytes*/
  );
  memcpy(stack_frame_of_callee + OFFSET_TO_TARGET, /*dest*/
         frame_pointer + OFFSET_TO_TARGET,         /*src*/
         SIZE_OF_INT32_T                           /*numberOfBytes*/
  );
  {
    BYTE_ADDRESS label = &&moveNMinus1FromTempToTarget;
    memcpy(stack_frame_of_callee + OFFSET_TO_INSTRUCTION_OF_CALLER, /*dest*/
           &label,                                                  /*src*/
           SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
    );
  }
  memcpy(stack_frame_of_callee + OFFSET_TO_FRAME_POINTER_OF_CALLER, /*dest*/
         &frame_pointer,                                            /*src*/
         SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
  );
  frame_pointer = stack_frame_of_callee;
}
  goto applyHanoiProcedure;
moveNMinus1FromTempToTarget : {
  BYTE_ADDRESS stack_frame_of_callee;
  stack_frame_of_callee =
      frame_pointer - 1 * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
  {
    int32_t number_of_disks;
    memcpy(&number_of_disks,                          /*dest*/
           frame_pointer + OFFSET_TO_NUMBER_OF_DISKS, /*src*/
           SIZE_OF_INT32_T                            /*numberOfBytes*/
    );
    int32_t parameter = number_of_disks - 1;
    memcpy(stack_frame_of_callee + OFFSET_TO_NUMBER_OF_DISKS, /*dest*/
           &parameter,                                        /*src*/
           SIZE_OF_INT32_T                                    /*numberOfBytes*/
    );
  }
  memcpy(stack_frame_of_callee + OFFSET_TO_SOURCE, /*dest*/
         frame_pointer + OFFSET_TO_TEMP,           /*src*/
         SIZE_OF_INT32_T                           /*numberOfBytes*/
  );
  memcpy(stack_frame_of_callee + OFFSET_TO_TEMP, /*dest*/
         frame_pointer + OFFSET_TO_SOURCE,       /*src*/
         SIZE_OF_INT32_T                         /*numberOfBytes*/
  );
  memcpy(stack_frame_of_callee + OFFSET_TO_TARGET, /*dest*/
         frame_pointer + OFFSET_TO_TARGET,         /*src*/
         SIZE_OF_INT32_T                           /*numberOfBytes*/
  );
  {
    BYTE_ADDRESS label =
        &&endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked;
    memcpy(stack_frame_of_callee + OFFSET_TO_INSTRUCTION_OF_CALLER, /*dest*/
           &label,                                                  /*src*/
           SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
    );
  }
  memcpy(stack_frame_of_callee + OFFSET_TO_FRAME_POINTER_OF_CALLER, /*dest*/
         &frame_pointer,                                            /*src*/
         SIZE_OF_BYTE_ADDRESS /*numberOfBytes*/
  );
  frame_pointer = (BYTE_ADDRESS)stack_frame_of_callee;
}
  goto applyHanoiProcedure;
endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked : {
  BYTE_ADDRESS goBackToCallee;
  memcpy(&goBackToCallee,                                 /*dest*/
         frame_pointer + OFFSET_TO_INSTRUCTION_OF_CALLER, /*src*/
         SIZE_OF_BYTE_ADDRESS                             /*numberOfBytes*/
  );
  memcpy(&frame_pointer, frame_pointer + OFFSET_TO_FRAME_POINTER_OF_CALLER,
         SIZE_OF_BYTE_ADDRESS);
  goto *goBackToCallee;
}
}
endMain:

  return 0;
}
