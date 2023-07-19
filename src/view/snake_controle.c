#include "view/snake_controle.h"

#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

typedef long msec;
typedef enum { UP, RIGHT, DOWN, LEFT, EXIT, TIMEOUT } Actions;

msec get_now_msec() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return ((t.tv_sec) * 1000) + (t.tv_usec / 1000);
}

void console_setup(struct termios *backup_attr) {
  struct termios attr;
  tcgetattr(STDIN_FILENO, &attr);
  *backup_attr = attr;

  attr.c_lflag &= (~ICANON);
  attr.c_lflag &= (~ECHO);
  attr.c_cc[VMIN] = 0;
  attr.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

void console_finish(struct termios *backup_attr) {
  tcsetattr(STDIN_FILENO, TCSANOW, backup_attr);
}

Actions get_kbd(fd_set *rfds) {
  static struct timeval timeout = {0, 10 * 1000};
  static struct timeval quick_return = {0, 0};

  FD_SET(STDIN_FILENO, rfds);
  int select_state = select(STDIN_FILENO + 1, rfds, NULL, NULL, &timeout);
  if (select_state == 0) {
    // timeout;
    return TIMEOUT;
  }
  if (select_state < 0) {
    printf("Error");
  }

  int c = getchar();
  ungetc(0x00, stdin);
  int t = getchar();
  if (t != 0x00 && t == 0x5b) {
    c = getchar();
    getchar();
  }
  c = (t << 8) | c;

  switch (c) {
    case 0x0077:
    case 0x5b41:
      return UP;
      break;
    case 0x0064:
    case 0x5b43:
      return RIGHT;
      break;
    case 0x0073:
    case 0x5b42:
      return DOWN;
      break;
    case 0x0061:
    case 0x5b44:
      return LEFT;
      break;
    case 0x001b:
      return EXIT;
      break;

    default:
      return 100;
      break;
  }
}

void tick_wait(int delay_ms, SetDirectionFuncP funcp) {
  struct termios backup;
  msec timeout_time = (get_now_msec() + delay_ms);

  fd_set rfds;
  FD_ZERO(&rfds);
  for (msec t = get_now_msec(); timeout_time > t; t = get_now_msec()) {
    switch (get_kbd(&rfds)) {
      case UP:
        funcp.up_func_p();
        break;
      case RIGHT:
        funcp.right_func_p();
        break;
      case DOWN:
        funcp.down_func_p();
        break;
      case LEFT:
        funcp.left_func_p();
        break;
      case EXIT:
        funcp.exit_func_p();
        break;
      default:
        break;
    }
  }
}

static struct termios backup_attr;

void init_controle() {
  static int is_calld = 0;

  if (is_calld == 1) {
    printf("init_controle dup(snake_controle)");
    return;
  }
  console_setup(&backup_attr);
}

void final_controle() { console_finish(&backup_attr); }
