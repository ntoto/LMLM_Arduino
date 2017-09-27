#ifndef BACKFLUSH_H_
#define BACKFLUSH_H_


enum backflush {
 B_CYCLE_START,
 B_CYCLE_1,
 B_CYCLE_2,
 B_CYCLE_CLEAN,
 B_CYCLE_3,
 B_CYCLE_END
};


enum backflushFlowStates {
  STATE_REST,
  STATE_FLOW
};


class Backflush {

  unsigned int state;
  unsigned int counter;
  unsigned long startTime;
  enum backflushFlowStates flowState;

  void displayInfo(int seconds, int flushSeconds, int restSeconds, int repeat);
  void displayRinse();
  void setFlowState(backflushFlowStates bstate);
  void startNextCycle();
  int getCycleNumber();
  void updateState(int flushSeconds, int restSeconds, int repeat);

public:
  Backflush();
  void start();
  int update();
};

#endif
