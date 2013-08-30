#ifndef __gaineffect__
#define __gaineffect__

#include "public.sdk/source/vst2.x/audioeffectx.h"

class Gaineffect : public AudioEffectX
{
public:
    Gaineffect(audioMasterCallback audioMaster);
    ~Gaineffect();

    //Processing
    virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
//    virtual void processDoubleReplacing(double** inputs, double** outputs, VstInt32 sampleFrames);

    //Parameters
    virtual void setParameter(VstInt32 index, float value);
    virtual float getParameter(VstInt32 index);
    virtual void getParameterLabel(VstInt32 index, char* label);
    virtual void getParameterDisplay(VstInt32 index, char* text);
    virtual void getParameterName(VstInt32 index, char* text);

    //State Transitions
    virtual void open();

protected:
    float clipLevel;
    float preGain;
    float postGain;
};

#endif // GAINEFFECT_H_INCLUDED
