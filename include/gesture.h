#pragma once
#include <math.h>
#include <stdbool.h>
#include <string.h>

// threshholds
#define THUMB_THRES 60
#define INDEX_THRES 40
#define MIDDLE_THRES 50
#define RING_THRES 35
#define PINKY_THRES 42

typedef enum Gestures
{
    /*
    Having a letter implies that the finger is flexed.
    T - thumb
    I - index finger
    M - middle finger
    R - ring finger
    P - pinky finger
    */

    // five fingers
    TIMRP,

    // four fingers
    TIMR,
    TMRP,
    TIRP,
    TIMP,
    IMRP,

    // three fingers
    TIM,
    TIR,
    TIP,
    TMR,
    TMP,
    TRP,
    IMR,
    IMP,
    IRP,
    MRP,

    // two fingers
    TI,
    TM,
    TR,
    TP,
    IM,
    IR,
    IP,
    MR,
    MP,
    RP,

    // one finger
    T,
    I,
    M,
    R,
    P,

    // no gesture
    NONE
} Gestures;

// this function returns the gesture from the sensor values
static inline Gestures gesture(float thumb, float index, float middle, float ring, float pinky)
{
    bool thumbBool, indexBool, middleBool, ringBool, pinkyBool;

    thumbBool = thumb > THUMB_THRES;
    indexBool = index > INDEX_THRES;
    middleBool = middle > MIDDLE_THRES;
    ringBool = ring > RING_THRES;
    pinkyBool = pinky > PINKY_THRES;

    // turning it into a bitmap for fast checking
    int mask = (thumbBool << 4) |
               (indexBool << 3) |
               (middleBool << 2) |
               (ringBool << 1) |
               (pinkyBool << 0);

    // fingers go from most flexed to least flexed
    // to avoid ordering issues
    switch (mask)
    {

    // five fingers
    case 0b11111:
        return TIMRP;

    // four fingers
    case 0b11110:
        return TIMR;
    case 0b10111:
        return TMRP;
    case 0b11011:
        return TIRP;
    case 0b11101:
        return TIMP;
    case 0b01111:
        return IMRP;

    // three fingers
    case 0b11100:
        return TIM;
    case 0b11010:
        return TIR;
    case 0b11001:
        return TIP;
    case 0b10110:
        return TMR;
    case 0b10101:
        return TMP;
    case 0b10011:
        return TRP;
    case 0b01110:
        return IMR;
    case 0b01101:
        return IMP;
    case 0b01011:
        return IRP;
    case 0b00111:
        return MRP;

    // two fingers
    case 0b11000:
        return TI;
    case 0b10100:
        return TM;
    case 0b10010:
        return TR;
    case 0b10001:
        return TP;
    case 0b01100:
        return IM;
    case 0b01010:
        return IR;
    case 0b01001:
        return IP;
    case 0b00110:
        return MR;
    case 0b00101:
        return MP;
    case 0b00011:
        return RP;

    // one finger
    case 0b10000:
        return T;
    case 0b01000:
        return I;
    case 0b00100:
        return M;
    case 0b00010:
        return R;
    case 0b00001:
        return P;

    default:
        return NONE;
    }
}
