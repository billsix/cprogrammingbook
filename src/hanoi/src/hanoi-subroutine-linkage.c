#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  const int32_t numberOfDisks = 4;
  struct local_variables_of_hanoi_instance // i.e. frame frame
  {
    int32_t numberOfDisks;
    int32_t source;
    int32_t temp;
    int32_t target;
    void *whatToDoAfterProcedureCall; // i.e. return address
    struct local_variables_of_hanoi_instance
        *local_variables_to_restore_before_returning;
  };

  const int32_t sizeOfFrame =
      numberOfDisks * sizeof(struct local_variables_of_hanoi_instance);
  struct local_variables_of_hanoi_instance *theFrame =
      (struct local_variables_of_hanoi_instance *)malloc(sizeOfFrame);

  struct local_variables_of_hanoi_instance *framePointer;
  // create first frame frame
  {
    // make room for first frame frame
    framePointer = &theFrame[sizeOfFrame - 1];
    // initialize first frame frame
    framePointer->numberOfDisks = numberOfDisks;
    framePointer->source = 1;
    framePointer->temp = 2;
    framePointer->target = 3;
    framePointer->whatToDoAfterProcedureCall = &&endMain;
    framePointer->local_variables_to_restore_before_returning = NULL;
  }

applyHanoiProcedure:

  if (framePointer->numberOfDisks != 1)
    goto notOne;
  printf("Move from %d to %d\n", framePointer->source, framePointer->target);
  goto endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked;
notOne:
moveNMinus1FromSourceToTemp:
  // prepare for function call
  // create new frame frame
  {
    struct local_variables_of_hanoi_instance
        *local_variables_for_nested_call_to_hanoi = framePointer - 1;
    local_variables_for_nested_call_to_hanoi->numberOfDisks =
        framePointer->numberOfDisks - 1;
    local_variables_for_nested_call_to_hanoi->source = framePointer->source;
    local_variables_for_nested_call_to_hanoi->temp = framePointer->target;
    local_variables_for_nested_call_to_hanoi->target = framePointer->temp;
    local_variables_for_nested_call_to_hanoi->whatToDoAfterProcedureCall =
        &&move1ToTarget;
    local_variables_for_nested_call_to_hanoi
        ->local_variables_to_restore_before_returning = framePointer;
    framePointer = local_variables_for_nested_call_to_hanoi;
  }
  goto applyHanoiProcedure;
move1ToTarget :
  {
  struct local_variables_of_hanoi_instance
      *local_variables_for_nested_call_to_hanoi = framePointer - 1;
  local_variables_for_nested_call_to_hanoi->numberOfDisks = 1;
  local_variables_for_nested_call_to_hanoi->source = framePointer->source;
  local_variables_for_nested_call_to_hanoi->temp = framePointer->temp;
  local_variables_for_nested_call_to_hanoi->target = framePointer->target;
  local_variables_for_nested_call_to_hanoi->whatToDoAfterProcedureCall =
      &&moveNMinus1FromTempToTarget;
  local_variables_for_nested_call_to_hanoi
      ->local_variables_to_restore_before_returning = framePointer;
  framePointer = local_variables_for_nested_call_to_hanoi;
  }
  goto applyHanoiProcedure;
moveNMinus1FromTempToTarget :
  {
  struct local_variables_of_hanoi_instance
      *local_variables_for_nested_call_to_hanoi = framePointer - 1;
  local_variables_for_nested_call_to_hanoi->numberOfDisks =
      framePointer->numberOfDisks - 1;
  local_variables_for_nested_call_to_hanoi->source = framePointer->temp;
  local_variables_for_nested_call_to_hanoi->temp = framePointer->source;
  local_variables_for_nested_call_to_hanoi->target = framePointer->target;
  local_variables_for_nested_call_to_hanoi->whatToDoAfterProcedureCall =
      &&endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked;
  local_variables_for_nested_call_to_hanoi
      ->local_variables_to_restore_before_returning = framePointer;
  framePointer = local_variables_for_nested_call_to_hanoi;
  }
  goto applyHanoiProcedure;
endProcedureSoRestoreCalleesLocalVarsAndContinueItWhereCalleeBlocked :
  {
  void *goBackToCallee = framePointer->whatToDoAfterProcedureCall;
  framePointer = framePointer->local_variables_to_restore_before_returning;
  goto *goBackToCallee;
  }

endMain:
  return 0;
}
