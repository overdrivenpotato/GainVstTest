#include "Gaineffect.h"
#include <stdlib.h>

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
    return new Gaineffect(audioMaster);
}

Gaineffect::Gaineffect(audioMasterCallback audioMaster)
: AudioEffectX(audioMaster, 1, 3)
{
    clipLevel = 1.f;
    preGain = 1.f;
    postGain = 1.f;
    setUniqueID('Gaintesting');
    setNumInputs(2);
    setNumOutputs(2);
    canProcessReplacing(true);
//    canProcessDoubleReplacing();
}

Gaineffect::~Gaineffect()
{
    //nothing
}

void Gaineffect::open()
{
    setParameterAutomated(0, 0.5);
    setParameterAutomated(1, 0.5);
    setParameterAutomated(2, 0.5);
}

float Gaineffect::getParameter(VstInt32 index)
{
    switch(index)
    {
    case 0:
        return clipLevel;
    case 1:
        return preGain;
    case 2:
        return postGain;
    }
}

void Gaineffect::setParameter(VstInt32 index, float value)
{
    //snap
    switch(index)
    {
    case 0:
    case 1:
    case 2:
        if(abs(0.5f - value) < 0.01)
        {
            //value = 0.5;
        }
    }
    value = (0.5f - value);
    switch(index)
    {
    case 0:
        value *= 2;
        clipLevel = value;
        break;
    case 1:
        value *= 2;
        preGain = value;
        break;
    case 2:
        value *= 2;
        postGain = value;
        break;
    }
}

void Gaineffect::getParameterLabel(VstInt32 index, char* label)
{
    switch(index)
    {
    case 0:
    case 1:
    case 2:
        vst_strncpy(label, "db", kVstMaxParamStrLen);
        break;
    }
}

void Gaineffect::getParameterDisplay(VstInt32 index, char* text)
{
    switch(index)
    {
    case 0:
    case 1:
    case 2:
        dB2string(getParameter(index), text, kVstMaxParamStrLen);
        break;
    }
}

void Gaineffect::getParameterName(VstInt32 index, char* text)
{
    switch(index)
    {
    case 0:
        vst_strncpy(text, "Clip Level", kVstMaxParamStrLen);
        break;
    case 1:
        vst_strncpy(text, "Pre Clip Gain", kVstMaxParamStrLen);
        break;
    case 2:
        vst_strncpy(text, "Post Clip Gain", kVstMaxParamStrLen);
        break;
    }
}

void Gaineffect::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
        *in1 *= preGain;
        *in2 *= preGain;

        *out1++ = (*in1 > clipLevel? clipLevel : (*in1 < -clipLevel ? -clipLevel : *in1));
        *out2++ = (*in2 > clipLevel? clipLevel : (*in2 < -clipLevel ? -clipLevel : *in2));

        *in1 *= postGain;
        *in2 *= postGain;

        *in1++;
        *in2++;
    }
}
