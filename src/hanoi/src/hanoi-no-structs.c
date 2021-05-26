#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE uint8_t
#define BYTE_ADDRESS BYTE *

// we will no longer use this struct directly, but have
// it here only so that the compiler can deduce offsets
// from the base of the struct for each variable.

struct hanoi_stack_frame // i.e. frame frame
{
  int32_t number_of_disks;
  int32_t source;
  int32_t temp;
  int32_t target;
  BYTE_ADDRESS what_to_do_after_procedure_call; // i.e. return address
  BYTE_ADDRESS pointer_to_frame_of_caller;
};

// these are all computed at compile time, and some values (but not int32_t) may
// vary across different Operating Systems/CPUs
const int32_t SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION =
    sizeof(struct hanoi_stack_frame);
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS = 0;
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE =
    OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS + sizeof(int32_t);
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP =
    OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE + sizeof(int32_t);
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET =
    OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP + sizeof(int32_t);
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER =
    OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET + sizeof(int32_t);
const size_t OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER =
    OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER +
    sizeof(BYTE_ADDRESS);

#define KILOBYTE 1024
#define MEGABYTE (KILOBYTE * KILOBYTE)

BYTE random_access_memory[10 * MEGABYTE];

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  const int32_t number_of_disks = 4;

  // byte of the begining of the frame
  BYTE_ADDRESS frame_pointer;
  // create first frame frame
  {
    // the frame pointer is the current stack frame, aka, where the local
    // variables are
    frame_pointer =
        random_access_memory +
        (number_of_disks - 1) * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
    // initialize first frame frame
    memcpy(/*dest*/ frame_pointer +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
           /*src*/ &number_of_disks,
           /*numberOfBytes*/ sizeof(int32_t));
    {
      int32_t parameter = 1;
      memcpy(/*dest*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      int32_t parameter = 2;
      memcpy(/*dest*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      int32_t parameter = 3;
      memcpy(/*dest*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      BYTE_ADDRESS label = &&endMain;
      memcpy(/*dest*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER,
             /*src*/ &label,
             /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
    }
    {
      BYTE_ADDRESS parameter = NULL;
      memcpy(/*dest*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
    }
  }

applyHanoiProcedure : {

  {
    int32_t number_of_disks_to_compare_to_one;
    memcpy(/*dest*/ &number_of_disks_to_compare_to_one,
           /*src*/ frame_pointer +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
           /*numberOfBytes*/ sizeof(int32_t));
    if (number_of_disks_to_compare_to_one != 1)
      goto notOne;
  }

  {
    int32_t source;
    memcpy(/*dest*/ &source,
           /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
           /*numberOfBytes*/ sizeof(int32_t));
    int32_t target;
    memcpy(/*dest*/ &target,
           /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
           /*numberOfBytes*/ sizeof(int32_t));
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
      memcpy(/*dest*/ &number_of_disks,
             /*src*/ frame_pointer +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
             /*numberOfBytes*/ sizeof(int32_t));
      int32_t parameter = number_of_disks - 1;
      memcpy(/*dest*/ stack_frame_of_callee +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
           /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
           /*numberOfBytes*/ sizeof(int32_t));
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
           /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
           /*numberOfBytes*/ sizeof(int32_t));
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
           /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
           /*numberOfBytes*/ sizeof(int32_t));
    {
      BYTE_ADDRESS label = &&move1ToTarget;
      memcpy(/*dest*/ stack_frame_of_callee +
                 OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER,
             /*src*/ &label,
             /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
    }
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER,
           /*src*/ &frame_pointer,
           /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
    frame_pointer = (BYTE_ADDRESS)stack_frame_of_callee;
  }
  goto applyHanoiProcedure;
move1ToTarget : {
  BYTE_ADDRESS stack_frame_of_callee;
  stack_frame_of_callee =
      frame_pointer - 1 * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
  {
    int32_t parameter = 1;
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
           /*src*/ &parameter,
           /*numberOfBytes*/ sizeof(int32_t));
  }
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
         /*numberOfBytes*/ sizeof(int32_t));
  {
    BYTE_ADDRESS label = &&moveNMinus1FromTempToTarget;
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER,
           /*src*/ &label,
           /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
  }
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER,
         /*src*/ &frame_pointer,
         /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
  frame_pointer = stack_frame_of_callee;
}
  goto applyHanoiProcedure;
moveNMinus1FromTempToTarget : {
  BYTE_ADDRESS stack_frame_of_callee;
  stack_frame_of_callee =
      frame_pointer - 1 * SIZE_REQUIRED_FOR_INSTANCE_OF_HANOI_INVOCATION;
  {
    int32_t number_of_disks;
    memcpy(/*dest*/ &number_of_disks,
           /*src*/ frame_pointer +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
           /*numberOfBytes*/ sizeof(int32_t));
    int32_t parameter = number_of_disks - 1;
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_NUMBER_OF_DISKS,
           /*src*/ &parameter,
           /*numberOfBytes*/ sizeof(int32_t));
  }
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TEMP,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_SOURCE,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
         /*src*/ frame_pointer + OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_TARGET,
         /*numberOfBytes*/ sizeof(int32_t));
  {
    BYTE_ADDRESS label =
        &&endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked;
    memcpy(/*dest*/ stack_frame_of_callee +
               OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER,
           /*src*/ &label,
           /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
  }
  memcpy(/*dest*/ stack_frame_of_callee +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER,
         /*src*/ &frame_pointer,
         /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
  frame_pointer = (BYTE_ADDRESS)stack_frame_of_callee;
}
  goto applyHanoiProcedure;
endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked : {
  BYTE_ADDRESS goBackToCallee;
  memcpy(/*dest*/ &goBackToCallee,
         /*src*/ frame_pointer +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_INSTRUCTION_OF_CALLER,
         /*numberOfBytes*/ sizeof(BYTE_ADDRESS));
  memcpy(&frame_pointer,
         frame_pointer +
             OFFSET_FROM_FRAME_POINTER_IN_BYTES_TO_FRAME_POINTER_OF_CALLER,
         sizeof(BYTE_ADDRESS));
  goto *goBackToCallee;
}
}
endMain:

  return 0;
}
