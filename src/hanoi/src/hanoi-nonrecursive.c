#include <inttypes.h>
#include <stdio.h>

void hanoi1(int32_t source, int32_t temp, int32_t target);

void hanoi2(int32_t source, int32_t temp, int32_t target);

void hanoi3(int32_t source, int32_t temp, int32_t target);

void hanoi4(int32_t source, int32_t temp, int32_t target);

void hanoiBad(int32_t number_of_disks, int32_t source, int32_t temp,
              int32_t target);

int main(int argc, char *argv[]) {

  int32_t source = 1;
  int32_t temp = 2;
  int32_t dest = 3;

  hanoi1(source, temp, dest);
  printf("completed hanoi1\n");
  hanoi2(source, temp, dest);
  printf("completed hanoi2\n");
  hanoi3(source, temp, dest);
  printf("completed hanoi3\n");
  hanoi4(source, temp, dest);
  printf("completed hanoi4\n");

  printf("Enter the number of disks\n");
  int32_t number_of_disks;
  scanf("%d", &number_of_disks);

  hanoiBad(number_of_disks, source, temp, dest);
  printf("completed hanoi\n");

  return 0;
}

void hanoi1(int32_t source, int32_t temp, int32_t target) {
  printf("Move from %d to %d\n", source, target);
}

void hanoi2(int32_t source, int32_t temp, int32_t target) {
  hanoi1(source, target, temp);
  hanoi1(source, temp, target);
  hanoi1(temp, source, target);
}

void hanoi3(int32_t source, int32_t temp, int32_t target) {
  hanoi2(source, target, temp);
  hanoi1(source, temp, target);
  hanoi2(temp, source, target);
}

void hanoi4(int32_t source, int32_t temp, int32_t target) {
  hanoi3(source, target, temp);
  hanoi1(source, temp, target);
  hanoi3(temp, source, target);
}

// gets stuck in infinite loop
void hanoiBad(int32_t number_of_disks, int32_t source, int32_t temp,
              int32_t target) {
  hanoiBad(number_of_disks, source, target, temp);
  printf("Move from %d to %d\n", source, target);
  hanoiBad(number_of_disks, temp, source, target);
}
