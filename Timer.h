#ifndef Timer_h
#define Timer_h

class Timer
{
public:
  Timer();
  void reset();
  bool check(unsigned long milliseconds);
private:
  unsigned long last_reset_;
};

#endif
