#include <Wire.h>
//defines the address for the accelerometer
#define Addr 0x1D

static TwoWire orbitWire(0);

//prepares the accelerometer to send and receive data over i2c
void WireStart(){
  orbitWire.begin();
}

/*retreives the current accelerometer values
 * int val[]: will be assigned the 10 bit values representing the x,y and z accelerations
 * int data[6]: holds values obtained from accelerometer
 * converts all the values for use(method obtained through the documentation and online reasource)
 * "https://github.com/ControlEverythingCommunity/MMA7455/blob/master/Particle/MMA7455.ino" * 
 */
void accelVal(int val[]){
  unsigned int data[6];
  for(int x = 0; x < 6; x++) {
    WireWriteByte(Addr,50 + x);
    orbitWire.requestFrom(Addr, 1);
    if(orbitWire.available() == 1)
    {
      data[x] = orbitWire.read();
    }
  }
  int xA = (((data[1] & 0x03) * 256) + data[0]);
  if(xA > 511){
    xA -= 1024;
  }
  int yA = (((data[3] & 0x03) * 256) + data[2]);
  if(yA > 511){
    yA -= 1024;
  }
  int zA = (((data[5] & 0x03) * 256) + data[4]);
  if(zA > 511){
    zA -= 1024;
  }
  val[0]= xA;
  val[1]= yA;
  val[2]= zA;
}
/*begins transmission to the adresss (only used for accelerometer(0X1D))
uint8_t reg: chooses the register
uint8_t value: writes value to registry
source: rollen
*/
void WireWriteRegister(int address, uint8_t reg, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();
}
/*begins transmission to the adresss (only used for accelerometer(0X1D))
 *uint8_t value: writes value to address
 */
void WireWriteByte(int address, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

