#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "DabbleInputs.h"

DabbleInputs::DabbleInputs() : ModuleParent(EVIVEINTERFACES_ID)
{
}

uint16_t DabbleInputs::getvalue_Pot1()
{
return uint16_t(data_1 << 8) + uint16_t (data_2);
}

uint16_t DabbleInputs::getvalue_Pot2()
{
return uint16_t(data_3 << 8) + uint16_t (data_4);
}

uint8_t DabbleInputs::getStatus_SlideSwitch1()
{
	if((data_5 & 0x04) == 0x04)
	{
		state_ss1 =2;
	
	}
	else if((data_5 & 0x02) == 0x02)
	{
		state_ss1 =0;
		
	}
	else if((data_5 & 0x01) == 0x01)
	{
		state_ss1 =1;
		
	}
	return state_ss1;
}

uint8_t DabbleInputs::getStatus_SlideSwitch2()
{
	if((data_5 & 0x20) == 0x20)
	{
		state_ss2=2;
	}
	else if((data_5&0x10) == 0x10)
	{
	state_ss2=0;
	}
	else if((data_5&0x08) == 0x08)
	{
	state_ss2=1;
	}
	return state_ss2;
}

bool DabbleInputs::getStatus_TactileSwitch1()
{
	return ((data_5 & 0x40) == 0x40);
}

bool DabbleInputs::getStatus_TactileSwitch2()
{
	return ((data_5 & 0x80) == 0x80);
}

uint16_t DabbleInputs::getInputsData(uint8_t a)
{
	if(a==0)
	{
		return uint16_t(data_1 << 8) + uint16_t (data_2);
	}
	else if(a==1)
	{
		return uint16_t(data_3 << 8) + uint16_t (data_4);
	}
	else if(a==2)
	{
		if((data_5 & 0x04) == 0x04)
	    {
		state_ss1 =3;
	    }
	    else if((data_5 & 0x02) == 0x02)
	    {
		state_ss1 =2;
		}
	    else if((data_5 & 0x01) == 0x01)
	    {
		state_ss1 =1;
		}
	    return state_ss1;
	}
	else if(a==3)
	{
		if((data_5 & 0x20) == 0x20)
	    {
		state_ss2=3;
	    }
	    else if((data_5&0x10) == 0x10)
	    {
	    state_ss2=2;
	    }
	    else if((data_5&0x08) == 0x08)
	    {
	    state_ss2=1;
	    }
	    return state_ss2;
	}
	else if(a==4)
	{
	  return ((data_5 & 0x40) == 0x40);	
	}
	else if(a==5)
	{
		return ((data_5 & 0x80) == 0x80);
	}
}

void DabbleInputs::processData()
{
	#ifdef DEBUG
	Serial.println("DabbleInputs:processData");
	#endif
	
	//Checking Function-ID
    byte functionId =getDabbleInstance().getFunctionId();
	if(functionId == Potentiometer_1)
	{
	data_1=getDabbleInstance().getArgumentData(0)[0]; 
	data_2=getDabbleInstance().getArgumentData(0)[1];
    }
	else if(functionId == Potentiometer_2)
	{
	data_3=getDabbleInstance().getArgumentData(0)[0]; 
	data_4=getDabbleInstance().getArgumentData(0)[1];
	
	}
	else if(functionId == Switches) 
	{
	data_5=getDabbleInstance().getArgumentData(0)[0]; 
    }
	
}