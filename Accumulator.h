#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

class Accumulator {
private:
  Victor[] motors;
  bool start();
  bool kill();
public:
  bool collect();
  bool update();
};

#endif /* ACCUMULATOR_H */
