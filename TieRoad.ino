
//#include<Stepper.h>
#define STEP1 4
#define DIR1 5
#define STEP2 6
#define DIR2 7
//Stepper myStepper(800,41,43);

// Pins for two motors
//Using a microstepping driver with Pulse and direction inputs. Fairly Obvious.
// motor = 200 steps/rev , 1.13ohm coil resistance, 3.6mH inductance, 18.9kgcm HOLDING TORQUE. the speed vs torque curve gives about 10-11kgcm pullout torque on 200-250 RPM.

// microstepping to 800 steps/rev
//current setting to 2.8A
//float a=0.150390625f;
float angle1;
float angle2;
float anglex=0;
float angley=0;
float floatstepsx=0;
float floatstepsy=0;
int cintstepsx=0;
int prevstepsx=0;
int cintstepsy=0;
int prevstepsy=0;
int v=0;
float previouspot=0;
int differencex=0;
int differencey=0;
int pot1=0;

// Readings for the tierod.
float ADCxx[308]={0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10,10.5,11,11.5,12,12.5,13,13.5,14,14.5,15,15.5,16,16.5,17,17.5,18,18.5,19,19.5,20,20.5,21,21.5,22,22.5,23,23.5,24,24.5,25,25.5,26,26.5,27,27.5,28,28.5,29,29.5,30,30.5,31,31.5,32,32.5,33,33.5,34,34.5,35,35.5,36,36.5,37,37.5,38,38.5,39,39.5,40,40.5,41,41.5,42,42.5,43,43.5,44,44.5,45,45.5,46,46.5,47,47.5,48,48.5,49,49.5,50,50.5,51,51.5,52,52.5,53,53.5,54,54.5,55,55.5,56,56.5,57,57.5,58,58.5,59,59.5,60,60.5,61,61.5,62,62.5,63,63.5,64,64.5,65,65.5,66,66.5,67,67.5,68,68.5,69,69.5,70,70.5,71,71.5,72,72.5,73,73.5,74,74.5,75,75.5,76,76.5,77,77.5,78,78.5,79,79.5,80,80.5,81,81.5,82,82.5,83,83.5,84,84.5,85,85.5,86,86.5,87,87.5,88,88.5,89,89.5,90,90.5,91,91.5,92,92.5,93,93.5,94,94.5,95,95.5,96,96.5,97,97.5,98,98.5,99,99.5,100,100.5,101,101.5,102,102.5,103,103.5,104,104.5,105,105.5,106,106.5,107,107.5,108,108.5,109,109.5,110,110.5,111,111.5,112,112.5,113,113.5,114,114.5,115,115.5,116,116.5,117,117.5,118,118.5,119,119.5,120,120.5,121,121.5,122,122.5,123,123.5,124,124.5,125,125.5,126,126.5,127,127.5,128,128.5,129,129.5,130,130.5,131,131.5,132,132.5,133,133.5,134,134.5,135,135.5,136,136.5,137,137.5,138,138.5,139,139.5,140,140.5,141,141.5,142,142.5,143,143.5,144,144.5,145,145.5,146,146.5,147,147.5,148,148.5,149,149.5,150,150.5,151,151.5,152,152.5,153,153.5,154};
float ADCyy[308]={0.788432,0.836209,0.915758,1.026835,1.169195,1.342592,1.546777,1.781498,2.04650,2.341543,2.666355,3.020685,3.404272,3.816855,4.258172,4.727957,5.225943,5.751862,6.305443,6.886415,7.494503,8.129432,8.790924,9.478699,10.19248,10.93197,11.69691,12.48699,13.30193,14.14144,15.00522,15.89299,16.80445,17.73929,18.69723,19.67795,20.68116,21.70654,22.7538,23.82263,24.9127,26.02372,27.15536,28.3073,29.47923,30.67083,31.88178,33.11174,34.3604,35.62742,36.91247,38.21521,39.53532,40.87246,42.22628,43.59644,44.9826,46.38442,47.80154,49.2336,50.68027,52.14118,53.61598,55.1043,56.60579,58.12007,59.64678,61.18555,62.736,64.29776,65.87046,67.45371,69.04713,70.65033,72.26292,73.88452,75.51472,77.15314,78.79937,80.453,82.11364,83.78087,85.45428,87.13346,88.81799,90.50745,92.2014,93.89943,95.60111,97.30599,99.01364,100.7236,102.4355,104.1488,105.8631,107.5779,109.2928,111.0073,112.7209,114.4332,116.1436,117.8518,119.5572,121.2593,122.9577,124.6519,126.3413,128.0254,129.7037,131.3758,133.0411,134.699,136.3491,137.9908,139.6235,141.2468,142.8601,144.4627,146.0543,147.6341,149.2016,150.7563,152.2975,153.8247,155.3373,156.8346,158.3161,159.7811,161.229,162.6592,164.0711,165.464,166.8373,168.1902,169.5222,170.8325,172.1206,173.3856,174.627,175.8439,177.0357,178.2017,179.3411,180.4532,181.5372,182.5924,183.6181,184.6134,185.5775,186.5097,187.4091,188.275,189.1064,189.9027,190.6628,191.3859,192.0713,192.7179,193.3249,193.8914,194.4164,194.899,195.3382,195.7331,196.0828,196.3861,196.6421,196.8498,197.0081,197.116,197.1724,197.1762,197.1263,197.0215,196.8607,196.6429,196.3666,196.0309,195.6344,195.1759,194.6541,194.0678,193.4157,192.6963,191.9084,191.0506,190.1215,189.1195,188.0434,186.8916,185.6625,184.3547,182.9666,181.4965,179.9428,178.304,176.5782,174.7638,172.8589,170.8618,168.7706,166.5835,164.2985,161.9137,159.4271,156.8366,154.1401,151.3355,148.4206,145.3932,142.251,138.9916,135.6127,132.1118,128.4863,124.7338,120.8515,116.8369,112.687,108.3991,103.9703,99.39757,94.67784,89.80799,84.78477,79.60488,74.2649,68.76134,63.09058,57.24893,51.23258,45.0376,38.65995,32.09549,25.33991,18.38882,11.23765,3.881706,3.683854,11.46403,19.464,27.6891,36.14484,44.83693,53.77128,62.95399,72.39141,82.09008,92.05681,102.2987,112.8229,123.6372,134.7495,146.1679,157.901,169.9577,182.3472,195.0793,208.164,221.6118,235.4336,249.6411,264.2462,279.2615,294.7002,310.5762,326.9039,343.6988,360.9768,378.7548,397.0509,415.8837,435.2732,455.2406,475.8081,496.9995,518.84,541.3562,564.577,588.5326,613.2557,638.7814,665.147,692.393,720.5629,749.7036,779.8661,811.1056,843.4824,877.0622,911.9172,948.1265,985.7776,1024.967,1065.804,1108.407,1152.913,1199.476,1248.268,1299.49,1353.373,1410.184,1470.24,1533.915,1601.662,1674.033,1751.718,1835.589};


//ADCyy represents the steps to be taken. But they are in float, hence it is converted to interger in the program with floatToInt function
void setup()
{
  Serial.begin(9600);
  //myStepper.setSpeed(70);
  pinMode(STEP1,OUTPUT);
  pinMode(DIR1,OUTPUT);
  pinMode(STEP2,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(A0,INPUT);
  
  
}
  
void loop()
{
  int i;
    
 float pot1=0;

  pot1=analogRead(A0);
 Serial.println(pot1);
 if(pot1>511.5f)
 {
  angle1= ((pot1-511.5f)*154.0f)/511.5f;
  anglex=adcavg(angle1);
  floatstepsx=mapping(anglex);
   // Remember the last steps taken by the motor 1 or 2;
  cintstepsx=floatToInt(floatstepsx);
  
 differencex=cintstepsx-prevstepsx;
  prevstepsx=cintstepsx;
  Stepx(differencex,1,anglex);
 }
 else if(pot1<511.5f)
 {
  angle2= ((511.5-pot1)*154.0f)/511.5f; // Verify the same with map() func.
 angley=adcavg(angle2);
  floatstepsy=mapping(angley);
   // Remember the last steps taken by the motor 1 or 2;
  cintstepsy=floatToInt(floatstepsy);
  
 differencey=cintstepsy-prevstepsy;
  prevstepsy=cintstepsy;
  Stepx(differencey,2,anglex);
 }
 

  // cintsteps = current integer steps and prevsteps= previous steps.
  // Hence we are moving only motor in small steps.
 // as the pot value changes countionusly, motor should give smooth movement.
 

  

  
 
  
}

/*int directionx(float x)
{
   x=pot1-previouspot;
  previouspot=pot1;
  if(x>0)
  {
    return 1;
  }
  
  else if(x<0)
  {
    return 2;
  }
  
}*/


float adcavg(float angle)
{
  // To average the value of angle, so that it maps in the array ADCxx. Check the mapping() function.
  float intanglex;
 
  int intangle=(float) angle;
  float decimaL1=angle-intangle;
  int decimalL2=(float)decimaL1*10;
  if(decimalL2>=5)
  {
     intanglex=intangle+1;
    
  }
  else if(decimalL2<5)
  {
    intanglex=intangle;
    intanglex+=0.5;
    
  }
  return intanglex;
}


float mapping(float angley)
{
	uint16_t i;
float stepxy=0;
	for(i=0;i<308;i++)
	{
		if(angley==ADCxx[i])
		{
			stepxy=ADCyy[i];
            	}
                else
                {
                  
                }
        }
                	return stepxy;
}

int floatToInt(float nStepx)
{
  
	int nStep1=(float) nStepx;
	if(nStepx-nStep1>0.5)
	{
		nStep1+=1;
		return nStep1;
	}
	else if (nStepx-nStep1<0.5) {
		return nStep1;
	}

}

void Stepx(int nSteps,int MotorX,float angle)
{
	int i;
int nStepsx=0;
	// If steps are are positive i.e. difference variable is positive. Then check for two cases for the angle. the cases of angle are derived from the readings.
//For angle 119.7 to 154. motor moves CW and for 0 to 119.7 it moves CCW
 // Considered both cases of 0 to 119.7 and 119.7 to 154, as the motor has to adjust its relative position
 
  if(nSteps>0)
{
if(angle>=119.5 && angle<=154){
	
if(MotorX==1)
{
  		
			digitalWrite(DIR1,HIGH);
for(i=0;i<=nSteps;i++)
{
  digitalWrite(STEP1,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP1,LOW);
delayMicroseconds(700);
}
}
else if(MotorX==2)
{
  		
			digitalWrite(DIR2,HIGH);
for(i=0;i<=nSteps;i++)
{
  digitalWrite(STEP2,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP2,LOW);
delayMicroseconds(700);
}
}

else
{
  //nothing
}


	}
	

else if (angle>=0 && angle<=119.6) 
{

if(MotorX==1)
{
  
		
			digitalWrite(DIR1,LOW);
for(i=0;i<=nSteps;i++)
{
  digitalWrite(STEP1,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP1,LOW);
delayMicroseconds(700);
}
}
else if(MotorX==2)
{
  
		
			digitalWrite(DIR2,LOW);
for(i=0;i<=nSteps;i++)
{
  digitalWrite(STEP2,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP2,LOW);
delayMicroseconds(700);
}
}


			
	
	
	else {
			//NOthing
		}

}

}
        
else if(nSteps<0)
{

  nStepsx=nSteps*(-1);
if (angle>=0 && angle<=119.5) {

		if(MotorX==1)
{
  	
			digitalWrite(DIR1,HIGH);
for(i=0;i<=nStepsx;i++)
{
  digitalWrite(STEP1,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP1,LOW);
delayMicroseconds(700);
}

}

else if(MotorX==2)
{
  	
			digitalWrite(DIR2,HIGH);
for(i=0;i<=nStepsx;i++)
{
  digitalWrite(STEP2,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP2,LOW);
delayMicroseconds(700);
}
}
else
{
  //nothing
}
			}
	
	


else if(angle>=119.5 && angle<=154){
	
			if(MotorX==1)
{
  	
			digitalWrite(DIR1,LOW);
for(i=0;i<=nStepsx;i++)
{
  digitalWrite(STEP1,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP1,LOW);
delayMicroseconds(700);
}
}
else if(MotorX==2)
{
  	
			digitalWrite(DIR2,LOW);
for(i=0;i<=nStepsx;i++)
{
  digitalWrite(STEP2,HIGH);
  delayMicroseconds(700);
  digitalWrite(STEP2,LOW);
delayMicroseconds(700);
}
}

}
}

			
	
	
	//else {
			//do nothing
		//}



}
 

