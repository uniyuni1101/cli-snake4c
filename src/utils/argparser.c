#include "utils/argparser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char HELP_MSG[] =
    "-s --area-size=<9|15|21>\n"
    "\tグリッドのサイズの指定\n"
    "\tDefault: 15\n\n"
    "-d --delay-ms=(int)\n"
    "\t蛇が動くまでの猶予時間\n"
    "\tDefault: 750\n\n"
    "-h --help\n\n"
    "\tヘルプの表示\n\n"
    "Usage:\n"
    "\tw key: ↑\n"
    "\ta key: ←\n"
    "\ts key: ↓\n"
    "\td key: →\n";

Options get_default_options() { return (Options){300, (AreaSize)x15}; }

typedef int msec;

int get_exist_index(int argc, char const *argv[], char *search_short,
                    char *search_long) {
  int exist_index = -1;
  for (int i = 1; i < argc; i++) {
    if (strcmp(search_short, argv[i]) == 0 ||
        strcmp(search_long, argv[i]) == 0) {
      exist_index = i;
    }
  }
  return exist_index;
}

int set_delay_option(int argc, char const *argv[],
                     msec *ms) {  // return int is exist option
  int exist_index = get_exist_index(argc, argv, "-d", "--delay");
  if (exist_index == -1) {
    return 0;
  } else if (exist_index < -1) {
    return -1;
  } else {
    *ms = atoi(argv[exist_index + 1]);
  }
}

int set_area_size_option(int argc, char const *argv[], AreaSize *size) {
  int exist_index = get_exist_index(argc, argv, "-s", "--area-size");

  if (exist_index == -1) {
    return 0;
  } else if (exist_index < -1) {
    return -1;
  } else {
    int s = atoi(argv[exist_index + 1]);
    switch (s) {
      case x9:
      case x15:
      case x21:
        *size = s;
        break;
      default:
        break;
    }
  }
}

int exist_help_option(int argc, char const *argv[]) {
  int exist_help = get_exist_index(argc, argv, "-h", "--help");
  if (exist_help != -1) {
    return 1;
  } else {
    return 0;
  }
}

Options args_load(int argc, char const *argv[]) {
  if (exist_help_option(argc, argv)) {
    exit(EXIT_SUCCESS);
  }
  printf("%s", HELP_MSG);
  Options opt = get_default_options();
  set_area_size_option(argc, argv, &opt.size);
  set_delay_option(argc, argv, &opt.delay_ms);
  return opt;
}
