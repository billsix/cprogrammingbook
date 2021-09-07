#include <inttypes.h>
#include <stdio.h>

void hanoi(int32_t numberOfDisks, int32_t source, int32_t temp, int32_t target);

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  printf("Enter the number of disks\n");
  int32_t number_of_disks;
  scanf("%d", &number_of_disks);

  hanoi(number_of_disks, source, temp, dest);
  printf("completed hanoi\n");

  return 0;
}

void hanoi(int32_t numberOfDisks, int32_t source, int32_t temp,
           int32_t target) {
  if (numberOfDisks == 1) {
    printf("Move from %d to %d\n", source, target);
  } else {
    hanoi(numberOfDisks - 1, source, target, temp);
    hanoi(1, source, temp, target);
    hanoi(numberOfDisks - 1, temp, source, target);
  }
}
