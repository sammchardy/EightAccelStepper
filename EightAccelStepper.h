//
//  EightAccelStepper.h
//  EightAccelStepper
//
//  Created by Sam McHardy on 7/10/12.
//  Copyright (c) 2012 Josephmark. All rights reserved.
//

#ifndef EightAccelStepper_EightAccelStepper_h
#define EightAccelStepper_EightAccelStepper_h

#include <AccelStepper.h>

class EightAccelStepper : public AccelStepper {

public: 
    EightAccelStepper(uint8_t pins = 4, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5);

    boolean runSpeed();
    
    void step(uint8_t step);
    
protected:
    void step4(uint8_t step);
    void step8(uint8_t step);
    
};
#endif
