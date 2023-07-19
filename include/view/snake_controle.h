#ifndef SNAKE_CONTROLE_H
#define SNAKE_CONTROLE_H
typedef struct {
  void (*up_func_p)(void);
  void (*left_func_p)(void);
  void (*down_func_p)(void);
  void (*right_func_p)(void);
  void (*exit_func_p)(void);
} SetDirectionFuncP;

void tick_wait(int delay_ms, SetDirectionFuncP funcp);
void init_controle();
void final_controle();
#endif
