//
//  EightAccelStepper.cpp
//  EightAccelStepper
//
//  Created by Sam McHardy on 7/10/12.
//  Copyright (c) 2012 Josephmark. All rights reserved.
//

#include <AccelStepper.h>
#include "EightAccelStepper.h"

    
EightAccelStepper::EightAccelStepper(uint8_t pins, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) : AccelStepper(pins, pin1, pin2, pin3, pin4)
    {    
    }

    // Implements steps according to the current speed
    // You must call this at least once per step
    // returns true if a step occurred
    boolean EightAccelStepper::runSpeed()
    {
        unsigned long time = millis();
        
        if (time > getLastStepTime() + getStepInterval())
        {
            if (getSpeed() > 0)
            {
                // Clockwise
                setCurrentPos(getCurrentPos() + 1);
            }
            else if (getSpeed() < 0)
            {
                // Anticlockwise
                setCurrentPos(getCurrentPos() - 1);            
            }
            if (getPins() == 8) {
                step(getCurrentPos() & 0x7); // Bottom 3 bits (same as mod 8, but works with + and - numbers)                 
            } else {
                step(getCurrentPos() & 0x3); // Bottom 2 bits (same as mod 4, but works with + and - numbers) 
            }
            
            setLastStepTime(time);
            return true;
        }
        else
            return false;
    }

    
    // Subclasses can override
    void EightAccelStepper::step(uint8_t step)
    {
        switch (getPins())
        {
            case 0:
                step0();
                break;
            case 1:
                step1(step);
                break;
                
            case 2:
                step2(step);
                break;
                
            case 4:
                step4(step);
                break; 
                
            case 8:
                step8(step);
                break;   
        }
    }

/**
 * 4 pin step function
 * This is passed the current step number (0 to 3)
 */
void EightAccelStepper::step4(uint8_t step)
{
    switch (step)
    {
        case 0:    // 1010
            digitalWrite(getPin(0), LOW);
            digitalWrite(getPin(1), LOW);
            digitalWrite(getPin(2), HIGH);
            digitalWrite(getPin(3), HIGH);
            break;
            
        case 1:    // 0110
            digitalWrite(getPin(0), LOW);
            digitalWrite(getPin(1), HIGH);
            digitalWrite(getPin(2), HIGH);
            digitalWrite(getPin(3), LOW);
            break;
            
        case 2:    //0101
            digitalWrite(getPin(0), HIGH);
            digitalWrite(getPin(1), HIGH);
            digitalWrite(getPin(2), LOW);
            digitalWrite(getPin(3), LOW);
            break;
            
        case 3:    //1001
            digitalWrite(getPin(0), HIGH);
            digitalWrite(getPin(1), LOW);
            digitalWrite(getPin(2), LOW);
            digitalWrite(getPin(3), HIGH);
            break;
    }
}

/**
 * 8 pin step function
 * This is passed the current step number (0 to 7)
 * Based on pin states from
 * http://www.geeetech.com/wiki/index.php/Stepper_Motor_5V_4-Phase_5-Wire_%26_ULN2003_Driver_Board_for_Arduino
 */
void EightAccelStepper::step8(uint8_t step)
{
    switch (step)
    {
        case 0: 
            digitalWrite(getPin(0), LOW);  
            digitalWrite(getPin(1), LOW); 
            digitalWrite(getPin(2), LOW); 
            digitalWrite(getPin(3), HIGH); 
            break;  
        case 1: 
            digitalWrite(getPin(0), HIGH);  
            digitalWrite(getPin(1), LOW); 
            digitalWrite(getPin(2), LOW); 
            digitalWrite(getPin(3), HIGH);  
            break;
        case 2: 
            digitalWrite(getPin(0), HIGH);  
            digitalWrite(getPin(1), LOW); 
            digitalWrite(getPin(2), LOW); 
            digitalWrite(getPin(3), LOW); 
            break;  
        case 3: 
            digitalWrite(getPin(0), HIGH);  
            digitalWrite(getPin(1), HIGH); 
            digitalWrite(getPin(2), LOW); 
            digitalWrite(getPin(3), LOW);
            break;  
        case 4: 
            digitalWrite(getPin(0), LOW);  
            digitalWrite(getPin(1), HIGH); 
            digitalWrite(getPin(2), LOW); 
            digitalWrite(getPin(3), LOW); 
            break;  
        case 5:
            digitalWrite(getPin(0), LOW);  
            digitalWrite(getPin(1), HIGH); 
            digitalWrite(getPin(2), HIGH); 
            digitalWrite(getPin(3), LOW);   
            break;  
        case 6: 
            digitalWrite(getPin(0), LOW);  
            digitalWrite(getPin(1), LOW); 
            digitalWrite(getPin(2), HIGH); 
            digitalWrite(getPin(3), LOW); 
            break;
        case 7:
            digitalWrite(getPin(0), LOW);  
            digitalWrite(getPin(1), LOW); 
            digitalWrite(getPin(2), HIGH); 
            digitalWrite(getPin(3), HIGH);
            break;  
        default: 
            break;  
    }
}