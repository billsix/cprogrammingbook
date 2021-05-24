#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_ADDRESS void *

// we will no longer use this struct directly, but have
// it here only so that the compiler can deduce offsets
// from the base of the struct for each variable.

struct hanoi_stack_frame // i.e. frame frame
{
  int32_t numberOfDisks;
  int32_t source;
  int32_t temp;
  int32_t target;
  MEMORY_ADDRESS whatToDoAfterProcedureCall; // i.e. return address
  MEMORY_ADDRESS stack_frame_of_caller;
};

// these are all computed at compile time, and some values (but not int32_t) may
// vary across different Operating Systems/CPUs
const int32_t sizeRequiredForInstanceOfHanoiInvocation =
    sizeof(struct hanoi_stack_frame);
const size_t offsetOfNumberOfDisks = 0;
const size_t offsetOfSource = offsetOfNumberOfDisks + sizeof(int32_t);
const size_t offsetOfTemp = offsetOfSource + sizeof(int32_t);
const size_t offsetOfTarget = offsetOfTemp + sizeof(int32_t);
const size_t offsetOfWhatToDoAfterProcedureCall =
    offsetOfTarget + sizeof(int32_t);
const size_t offsetOfStackFrameOfCaller =
    offsetOfWhatToDoAfterProcedureCall + sizeof(MEMORY_ADDRESS);

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  const int32_t numberOfDisks = 4;

  const int32_t sizeOfFrame = sizeRequiredForInstanceOfHanoiInvocation;
  uint8_t *theFrames = (uint8_t *)malloc(numberOfDisks * sizeOfFrame);

  // byte of the begining of the frame
  uint8_t *current_stack_frame;
  // create first frame frame
  {
    // make room for first frame frame
    current_stack_frame =
        theFrames +
        (numberOfDisks - 1) * sizeRequiredForInstanceOfHanoiInvocation;
    // initialize first frame frame
    memcpy(/*dest*/ current_stack_frame + offsetOfNumberOfDisks,
           /*src*/ &numberOfDisks,
           /*numberOfBytes*/ sizeof(int32_t));
    {
      int32_t parameter = 1;
      memcpy(/*dest*/ current_stack_frame + offsetOfSource, /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      int32_t parameter = 2;
      memcpy(/*dest*/ current_stack_frame + offsetOfTemp, /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      int32_t parameter = 3;
      memcpy(/*dest*/ current_stack_frame + offsetOfTarget, /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    {
      MEMORY_ADDRESS label = &&endMain;
      memcpy(/*dest*/ current_stack_frame + offsetOfWhatToDoAfterProcedureCall,
             /*src*/ &label,
             /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
    }
    {
      MEMORY_ADDRESS parameter = NULL;
      memcpy(/*dest*/ current_stack_frame + offsetOfStackFrameOfCaller,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
    }
  }

applyHanoiProcedure :

{
  int32_t numberOfDisksToCompareToOne;
  memcpy(/*dest*/ &numberOfDisksToCompareToOne,
         /*src*/ current_stack_frame + offsetOfNumberOfDisks,
         /*numberOfBytes*/ sizeof(int32_t));
  if (numberOfDisksToCompareToOne != 1)
    goto notOne;
}

  {
    int32_t source;
    memcpy(/*dest*/ &source, /*src*/ current_stack_frame + offsetOfSource,
           /*numberOfBytes*/ sizeof(int32_t));
    int32_t target;
    memcpy(/*dest*/ &target, /*src*/ current_stack_frame + offsetOfTarget,
           /*numberOfBytes*/ sizeof(int32_t));
    printf("Move from %d to %d\n", source, target);
  }
  goto endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked;
notOne:
moveNMinus1FromSourceToTemp:
  // prepare for function call
  // create new frame frame
  {
    uint8_t *stack_frame_of_callee;
    stack_frame_of_callee =
        current_stack_frame - 1 * sizeRequiredForInstanceOfHanoiInvocation;
    {
      int32_t numberOfDisks;
      memcpy(/*dest*/ &numberOfDisks,
             /*src*/ current_stack_frame + offsetOfNumberOfDisks,
             /*numberOfBytes*/ sizeof(int32_t));
      int32_t parameter = numberOfDisks - 1;
      memcpy(/*dest*/ stack_frame_of_callee + offsetOfNumberOfDisks,
             /*src*/ &parameter,
             /*numberOfBytes*/ sizeof(int32_t));
    }
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfSource,
           /*src*/ current_stack_frame + offsetOfSource,
           /*numberOfBytes*/ sizeof(int32_t));
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfTemp,
           /*src*/ current_stack_frame + offsetOfTarget,
           /*numberOfBytes*/ sizeof(int32_t));
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfTarget,
           /*src*/ current_stack_frame + offsetOfTemp,
           /*numberOfBytes*/ sizeof(int32_t));
    {
      MEMORY_ADDRESS label = &&move1ToTarget;
      memcpy(/*dest*/ stack_frame_of_callee +
                 offsetOfWhatToDoAfterProcedureCall,
             /*src*/ &label,
             /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
    }
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfStackFrameOfCaller,
           /*src*/ &current_stack_frame,
           /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
    current_stack_frame = (MEMORY_ADDRESS)stack_frame_of_callee;
  }
  goto applyHanoiProcedure;
move1ToTarget : {
  uint8_t *stack_frame_of_callee;
  stack_frame_of_callee =
      current_stack_frame - 1 * sizeRequiredForInstanceOfHanoiInvocation;
  {
    int32_t parameter = 1;
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfNumberOfDisks,
           /*src*/ &parameter,
           /*numberOfBytes*/ sizeof(int32_t));
  }
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfSource,
         /*src*/ current_stack_frame + offsetOfSource,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfTemp,
         /*src*/ current_stack_frame + offsetOfTemp,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfTarget,
         /*src*/ current_stack_frame + offsetOfTarget,
         /*numberOfBytes*/ sizeof(int32_t));
  {
    MEMORY_ADDRESS label = &&moveNMinus1FromTempToTarget;
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfWhatToDoAfterProcedureCall,
           /*src*/ &label,
           /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
  }
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfStackFrameOfCaller,
         /*src*/ &current_stack_frame,
         /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
  current_stack_frame = (uint8_t *)stack_frame_of_callee;
}
  goto applyHanoiProcedure;
moveNMinus1FromTempToTarget : {
  uint8_t *stack_frame_of_callee;
  stack_frame_of_callee =
      current_stack_frame - 1 * sizeRequiredForInstanceOfHanoiInvocation;
  {
    int32_t numberOfDisks;
    memcpy(/*dest*/ &numberOfDisks,
           /*src*/ current_stack_frame + offsetOfNumberOfDisks,
           /*numberOfBytes*/ sizeof(int32_t));
    int32_t parameter = numberOfDisks - 1;
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfNumberOfDisks,
           /*src*/ &parameter,
           /*numberOfBytes*/ sizeof(int32_t));
  }
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfSource,
         /*src*/ current_stack_frame + offsetOfTemp,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfTemp,
         /*src*/ current_stack_frame + offsetOfSource,
         /*numberOfBytes*/ sizeof(int32_t));
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfTarget,
         /*src*/ current_stack_frame + offsetOfTarget,
         /*numberOfBytes*/ sizeof(int32_t));
  {
    MEMORY_ADDRESS label =
        &&endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked;
    memcpy(/*dest*/ stack_frame_of_callee + offsetOfWhatToDoAfterProcedureCall,
           /*src*/ &label,
           /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
  }
  memcpy(/*dest*/ stack_frame_of_callee + offsetOfStackFrameOfCaller,
         /*src*/ &current_stack_frame,
         /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
  current_stack_frame = (MEMORY_ADDRESS)stack_frame_of_callee;
}
  goto applyHanoiProcedure;
endProcedureSoRestoreCallersLocalVarsAndContinueItWhereCallerBlocked : {
  MEMORY_ADDRESS goBackToCallee;
  memcpy(/*dest*/ &goBackToCallee,
         /*src*/ current_stack_frame + offsetOfWhatToDoAfterProcedureCall,
         /*numberOfBytes*/ sizeof(MEMORY_ADDRESS));
  memcpy(&current_stack_frame, current_stack_frame + offsetOfStackFrameOfCaller,
         sizeof(MEMORY_ADDRESS));
  goto *goBackToCallee;
}

endMain:

  free(theFrames);
  return 0;
}
