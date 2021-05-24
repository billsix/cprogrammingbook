#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  const int32_t numberOfDisks = 4;
  struct hanoi_stack_frame // i.e. frame frame
  {
    int32_t numberOfDisks;
    int32_t source;
    int32_t temp;
    int32_t target;
    void *whatToDoAfterProcedureCall; // i.e. return address
    struct hanoi_stack_frame *stack_frame_of_callee;
  };

  const int32_t sizeOfFrame = numberOfDisks * sizeof(struct hanoi_stack_frame);
  struct hanoi_stack_frame *theFrames =
      (struct hanoi_stack_frame *)malloc(sizeOfFrame);

  struct hanoi_stack_frame *current_stack_frame;
  // create first frame frame
  {
    // make room for first frame frame
    current_stack_frame = &theFrames[sizeOfFrame - 1];
    // initialize first frame frame
    current_stack_frame->numberOfDisks = numberOfDisks;
    current_stack_frame->source = 1;
    current_stack_frame->temp = 2;
    current_stack_frame->target = 3;
    current_stack_frame->whatToDoAfterProcedureCall = &&endMain;
    current_stack_frame->stack_frame_of_callee = NULL;
  }

applyHanoiProcedure:

  if (current_stack_frame->numberOfDisks != 1)
    goto notOne;
  printf("Move from %d to %d\n", current_stack_frame->source,
         current_stack_frame->target);
  goto endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked;
notOne:
moveNMinus1FromSourceToTemp:
  // prepare for function call
  // create new frame frame
  {
    struct hanoi_stack_frame *stack_frame_of_callee = current_stack_frame - 1;
    stack_frame_of_callee->numberOfDisks =
        current_stack_frame->numberOfDisks - 1;
    stack_frame_of_callee->source = current_stack_frame->source;
    stack_frame_of_callee->temp = current_stack_frame->target;
    stack_frame_of_callee->target = current_stack_frame->temp;
    stack_frame_of_callee->whatToDoAfterProcedureCall = &&move1ToTarget;
    stack_frame_of_callee->stack_frame_of_callee = current_stack_frame;
    current_stack_frame = stack_frame_of_callee;
  }
  goto applyHanoiProcedure;
move1ToTarget : {
  struct hanoi_stack_frame *stack_frame_of_callee = current_stack_frame - 1;
  stack_frame_of_callee->numberOfDisks = 1;
  stack_frame_of_callee->source = current_stack_frame->source;
  stack_frame_of_callee->temp = current_stack_frame->temp;
  stack_frame_of_callee->target = current_stack_frame->target;
  stack_frame_of_callee->whatToDoAfterProcedureCall =
      &&moveNMinus1FromTempToTarget;
  stack_frame_of_callee->stack_frame_of_callee = current_stack_frame;
  current_stack_frame = stack_frame_of_callee;
}
  goto applyHanoiProcedure;
moveNMinus1FromTempToTarget : {
  struct hanoi_stack_frame *stack_frame_of_callee = current_stack_frame - 1;
  stack_frame_of_callee->numberOfDisks = current_stack_frame->numberOfDisks - 1;
  stack_frame_of_callee->source = current_stack_frame->temp;
  stack_frame_of_callee->temp = current_stack_frame->source;
  stack_frame_of_callee->target = current_stack_frame->target;
  stack_frame_of_callee->whatToDoAfterProcedureCall =
      &&endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked;
  stack_frame_of_callee->stack_frame_of_callee = current_stack_frame;
  current_stack_frame = stack_frame_of_callee;
}
  goto applyHanoiProcedure;
endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked : {
  void *goBackToCallee = current_stack_frame->whatToDoAfterProcedureCall;
  current_stack_frame = current_stack_frame->stack_frame_of_callee;
  goto *goBackToCallee;
}

endMain:

  free(theFrames);
  return 0;
}
