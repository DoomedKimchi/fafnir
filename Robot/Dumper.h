#ifndef DUMPER_H
#define DUMPER_H

#include <WPILib.h>
#include "Constants.h"
#include "NumberPID.h"
#include "LinearVictor.h"

class Dumper {
 private:
  LinearVictor motor;

 public:
  Dumper();
  void dump(bool go);
  void autoDump();
  void rotateS();
  void update();
};

#endif /* DUMPER_H */
