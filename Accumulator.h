#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

class Accumulator {
private:
  Victor motor;
  //pneumatic arm for flipping
  //beam sensor for frisbee?

  bool start();
  bool kill();
public:
  bool collect();
  bool update();
  Accumulator();
};

#endif /* ACCUMULATOR_H */
