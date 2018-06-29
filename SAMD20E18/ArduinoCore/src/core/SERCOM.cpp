/*
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "SERCOM.h"
#include "variant.h"
#include "wiring.h"

#ifndef WIRE_RISE_TIME_NANOSECONDS
// Default rise time in nanoseconds, based on 4.7K ohm pull up resistors
// you can override this value in your variant if needed
#define WIRE_RISE_TIME_NANOSECONDS 125
#endif

SERCOM::SERCOM(Sercom* s)
{
  sercom = s;
}

/* 	=========================
 *	===== Sercom UART
 *	=========================
*/
void SERCOM::initUART(SercomUartMode mode, SercomUartSampleRate sampleRate, uint32_t baudrate)
{
  enableSerial();
  resetUART();

  //Setting the CTRLA register
  sercom->USART.CTRLA.reg =	SERCOM_USART_CTRLA_MODE(mode) 
#ifndef SAMD20
                 | SERCOM_USART_CTRLA_SAMPR(sampleRate)
#endif /* SAMD20 */
  ;
			   
  //Setting the Interrupt register
  sercom->USART.INTENSET.reg =	SERCOM_USART_INTENSET_RXC /* Receive */
#ifndef SAMD20
                                |  SERCOM_USART_INTENSET_ERROR /* Errors */
#endif /* SAMD20 */
  ;

  if ( mode == UART_INT_CLOCK )
  {
    uint16_t sampleRateValue;

    if (sampleRate == SAMPLE_RATE_x16) {
      sampleRateValue = 16;
    } else {
      sampleRateValue = 8;
    }

#ifndef SAMD20
    // Asynchronous fractional mode (Table 24-2 in datasheet)
    //   BAUD = fref / (sampleRateValue * fbaud)
    // (multiply by 8, to calculate fractional piece)
    uint32_t baudTimes8 = (SystemCoreClock * 8) / (sampleRateValue * baudrate);

    sercom->USART.BAUD.FRAC.FP   = (baudTimes8 % 8);
    sercom->USART.BAUD.FRAC.BAUD = (baudTimes8 / 8);
#else
    float baudF = (float)baudrate;
    float ratio = (baudF / (float)SystemCoreClock);
    float baudReg = 65536.0 * (1.0 - (16.0 * ratio));
    sercom->USART.BAUD.reg = (uint16_t) baudReg;
#endif /* SAMD20 */
  }
}

void SERCOM::initFrame(SercomUartCharSize charSize, SercomDataOrder dataOrder, SercomParityMode parityMode, SercomNumberStopBit nbStopBits)
{
  //Setting the CTRLA register
  sercom->USART.CTRLA.reg |=	SERCOM_USART_CTRLA_FORM( (parityMode == SERCOM_NO_PARITY ? 0 : 1) ) |
                dataOrder << SERCOM_USART_CTRLA_DORD_Pos;

  //Setting the CTRLB register
  sercom->USART.CTRLB.reg |=	SERCOM_USART_CTRLB_CHSIZE(charSize) |
                nbStopBits << SERCOM_USART_CTRLB_SBMODE_Pos |
                (parityMode == SERCOM_NO_PARITY ? 0 : parityMode) << SERCOM_USART_CTRLB_PMODE_Pos; //If no parity use default value
}

void SERCOM::initPads(SercomUartTXPad txPad, SercomRXPad rxPad)
{
  //Setting the CTRLA register
#ifndef SAMD20
  sercom->USART.CTRLA.reg |=	SERCOM_USART_CTRLA_TXPO(txPad) |
                SERCOM_USART_CTRLA_RXPO(rxPad);
#else
    sercom->USART.CTRLA.reg |=	SERCOM_USART_CTRLA_TXPO | 
                SERCOM_USART_CTRLA_RXPO(rxPad);
#endif /* SAMD20 */

  // Enable Transceiver and Receiver
  sercom->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN ;
}

void SERCOM::resetUART()
{
  // Start the Software Reset
  sercom->USART.CTRLA.bit.SWRST = 1;

#ifndef SAMD20
  while ( sercom->USART.CTRLA.bit.SWRST || sercom->USART.SYNCBUSY.bit.SWRST )
#else
  while ( sercom->USART.CTRLA.bit.SWRST || sercom->USART.STATUS.bit.SYNCBUSY )
#endif /* SAMD20 */
  {
    // Wait for both bits Software Reset from CTRLA and SYNCBUSY coming back to 0
  }
}

void SERCOM::enableUART()
{
  //Setting  the enable bit to 1
  sercom->USART.CTRLA.bit.ENABLE = 0x1u;

#ifndef SAMD20
  //Wait for then enable bit from SYNCBUSY is equal to 0;
  while(sercom->USART.SYNCBUSY.bit.ENABLE);
#else
  //Wait for the clocks to sync
  while ( sercom->USART.STATUS.bit.SYNCBUSY );
#endif /* SAMD20 */
}

void SERCOM::flushUART()
{
  // Skip checking transmission completion if data register is empty
  if(isDataRegisterEmptyUART())
    return;

  // Wait for transmission to complete
  while(!sercom->USART.INTFLAG.bit.TXC);
}

void SERCOM::clearStatusUART()
{
  //Reset (with 0) the STATUS register
  sercom->USART.STATUS.reg = SERCOM_USART_STATUS_RESETVALUE;
}

bool SERCOM::availableDataUART()
{
  //RXC : Receive Complete
  return sercom->USART.INTFLAG.bit.RXC;
}

bool SERCOM::isUARTError()
{
  bool rtn = 
#ifndef SAMD20
        sercom->USART.INTFLAG.bit.ERROR;
#else
        sercom->USART.STATUS.reg & (SERCOM_USART_STATUS_BUFOVF 
          | SERCOM_USART_STATUS_FERR | SERCOM_USART_STATUS_PERR);
#endif /* SAMD20 */
  return rtn;
}

void SERCOM::acknowledgeUARTError()
{
#ifndef SAMD20
  sercom->USART.INTFLAG.bit.ERROR = 1;
#else
  if( isBufferOverflowErrorUART() )
    sercom->USART.STATUS.reg |= SERCOM_USART_STATUS_BUFOVF;
  if( isFrameErrorUART() )
    sercom->USART.STATUS.reg |= SERCOM_USART_STATUS_FERR;
  if( isParityErrorUART() )
    sercom->USART.STATUS.reg |= SERCOM_USART_STATUS_PERR;
#endif /* SAMD20 */
}

bool SERCOM::isBufferOverflowErrorUART()
{
  //BUFOVF : Buffer Overflow
  return sercom->USART.STATUS.bit.BUFOVF;
}

bool SERCOM::isFrameErrorUART()
{
  //FERR : Frame Error
  return sercom->USART.STATUS.bit.FERR;
}

bool SERCOM::isParityErrorUART()
{
  //PERR : Parity Error
  return sercom->USART.STATUS.bit.PERR;
}

bool SERCOM::isDataRegisterEmptyUART()
{
  //DRE : Data Register Empty
  return sercom->USART.INTFLAG.bit.DRE;
}

uint8_t SERCOM::readDataUART()
{
  return sercom->USART.DATA.bit.DATA;
}

int SERCOM::writeDataUART(uint8_t data)
{
  // Wait for data register to be empty
  while(!isDataRegisterEmptyUART());

  //Put data into DATA register
  sercom->USART.DATA.reg = (uint16_t)data;
  return 1;
}

void SERCOM::enableDataRegisterEmptyInterruptUART()
{
  sercom->USART.INTENSET.reg = SERCOM_USART_INTENSET_DRE;
}

void SERCOM::disableDataRegisterEmptyInterruptUART()
{
  sercom->USART.INTENCLR.reg = SERCOM_USART_INTENCLR_DRE;
}

/*	=========================
 *	===== Sercom SPI
 *	=========================
*/
void SERCOM::initSPI(SercomSpiTXPad mosi, SercomRXPad miso, SercomSpiCharSize charSize, SercomDataOrder dataOrder)
{
  enableSPI();
  resetSPI();

  //Setting the CTRLA register
  sercom->SPI.CTRLA.reg =	SERCOM_SPI_CTRLA_MODE_SPI_MASTER |
                          SERCOM_SPI_CTRLA_DOPO(mosi) |
                          SERCOM_SPI_CTRLA_DIPO(miso) |
                          dataOrder << SERCOM_SPI_CTRLA_DORD_Pos;

  //Setting the CTRLB register
  sercom->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_CHSIZE(charSize) |
                          SERCOM_SPI_CTRLB_RXEN;	//Active the SPI receiver.


}

void SERCOM::initSPIClock(SercomSpiClockMode clockMode, uint32_t baudrate)
{
  //Extract data from clockMode
  int cpha, cpol;

  if((clockMode & (0x1ul)) == 0 )
    cpha = 0;
  else
    cpha = 1;

  if((clockMode & (0x2ul)) == 0)
    cpol = 0;
  else
    cpol = 1;

  //Setting the CTRLA register
  sercom->SPI.CTRLA.reg |=	( cpha << SERCOM_SPI_CTRLA_CPHA_Pos ) |
                            ( cpol << SERCOM_SPI_CTRLA_CPOL_Pos );

  //Synchronous arithmetic
  sercom->SPI.BAUD.reg = calculateBaudrateSynchronous(baudrate);
}

void SERCOM::resetSPI()
{
  //Setting the Software Reset bit to 1
  sercom->SPI.CTRLA.bit.SWRST = 1;

#ifndef SAMD20
  //Wait both bits Software Reset from CTRLA and SYNCBUSY are equal to 0
  while(sercom->SPI.CTRLA.bit.SWRST || sercom->SPI.SYNCBUSY.bit.SWRST);
#else
  while(sercom->SPI.CTRLA.bit.SWRST || sercom->SPI.STATUS.bit.SYNCBUSY);
#endif /* SAMD20 */
}

void SERCOM::enableSPI()
{
  //Setting the enable bit to 1
  sercom->SPI.CTRLA.bit.ENABLE = 1;

#ifndef SAMD20
  while(sercom->SPI.SYNCBUSY.bit.ENABLE)
#else
  while(sercom->SPI.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    //Waiting then enable bit from SYNCBUSY is equal to 0;
  }
}

void SERCOM::disableSPI()
{
#ifndef SAMD20
  while(sercom->SPI.SYNCBUSY.bit.ENABLE)
#else
  while(sercom->SPI.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    //Waiting then enable bit from SYNCBUSY is equal to 0;
  }

  //Setting the enable bit to 0
  sercom->SPI.CTRLA.bit.ENABLE = 0;
}

void SERCOM::setDataOrderSPI(SercomDataOrder dataOrder)
{
  //Register enable-protected
  disableSPI();

  sercom->SPI.CTRLA.bit.DORD = dataOrder;

  enableSPI();
}

SercomDataOrder SERCOM::getDataOrderSPI()
{
  return (sercom->SPI.CTRLA.bit.DORD ? LSB_FIRST : MSB_FIRST);
}

void SERCOM::setBaudrateSPI(uint8_t divider)
{
  //Can't divide by 0
  if(divider == 0)
    return;

  //Register enable-protected
  disableSPI();

  sercom->SPI.BAUD.reg = calculateBaudrateSynchronous( SERCOM_FREQ_REF / divider );

  enableSPI();
}

void SERCOM::setClockModeSPI(SercomSpiClockMode clockMode)
{
  int cpha, cpol;
  if((clockMode & (0x1ul)) == 0)
    cpha = 0;
  else
    cpha = 1;

  if((clockMode & (0x2ul)) == 0)
    cpol = 0;
  else
    cpol = 1;

  //Register enable-protected
  disableSPI();

  sercom->SPI.CTRLA.bit.CPOL = cpol;
  sercom->SPI.CTRLA.bit.CPHA = cpha;

  enableSPI();
}

uint8_t SERCOM::transferDataSPI(uint8_t data)
{
  sercom->SPI.DATA.bit.DATA = data; // Writing data into Data register

  while( sercom->SPI.INTFLAG.bit.RXC == 0 )
  {
    // Waiting Complete Reception
  }

  return sercom->SPI.DATA.bit.DATA;  // Reading data
}

bool SERCOM::isBufferOverflowErrorSPI()
{
  return sercom->SPI.STATUS.bit.BUFOVF;
}

bool SERCOM::isDataRegisterEmptySPI()
{
  //DRE : Data Register Empty
  return sercom->SPI.INTFLAG.bit.DRE;
}

//bool SERCOM::isTransmitCompleteSPI()
//{
//	//TXC : Transmit complete
//	return sercom->SPI.INTFLAG.bit.TXC;
//}
//
//bool SERCOM::isReceiveCompleteSPI()
//{
//	//RXC : Receive complete
//	return sercom->SPI.INTFLAG.bit.RXC;
//}

uint8_t SERCOM::calculateBaudrateSynchronous(uint32_t baudrate)
{
  return SERCOM_FREQ_REF / (2 * baudrate) - 1;
}


/*	=========================
 *	===== Sercom WIRE
 *	=========================
 */
void SERCOM::resetWIRE()
{
  //I2CM OR I2CS, no matter SWRST is the same bit.

  //Setting the Software bit to 1
  sercom->I2CM.CTRLA.bit.SWRST = 1;

#ifndef SAMD20
  //Wait both bits Software Reset from CTRLA and SYNCBUSY are equal to 0
  while(sercom->I2CM.CTRLA.bit.SWRST || sercom->I2CM.SYNCBUSY.bit.SWRST);
#else
  while(sercom->I2CM.CTRLA.bit.SWRST || sercom->I2CM.STATUS.bit.SYNCBUSY);
#endif /* SAMD20 */
}

void SERCOM::enableWIRE()
{
  // I2C Master and Slave modes share the ENABLE bit function.

  // Enable the I2C master mode
  sercom->I2CM.CTRLA.bit.ENABLE = 1 ;

#ifndef SAMD20
  while ( sercom->I2CM.SYNCBUSY.bit.ENABLE != 0 )
#else
  while(sercom->I2CM.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    // Waiting the enable bit from SYNCBUSY is equal to 0;
  }

  // Setting bus idle mode
  sercom->I2CM.STATUS.bit.BUSSTATE = 1 ;

#ifndef SAMD20
  while ( sercom->I2CM.SYNCBUSY.bit.SYSOP != 0 )
#else
  while(sercom->I2CM.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    // Wait the SYSOP bit from SYNCBUSY coming back to 0
  }
}

void SERCOM::disableWIRE()
{
  // I2C Master and Slave modes share the ENABLE bit function.

  // Enable the I2C master mode
  sercom->I2CM.CTRLA.bit.ENABLE = 0 ;

#ifndef SAMD20
  while ( sercom->I2CM.SYNCBUSY.bit.ENABLE != 0 )
#else
  while(sercom->I2CM.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    // Waiting the enable bit from SYNCBUSY is equal to 0;
  }
}

void SERCOM::initSlaveWIRE( uint8_t ucAddress, bool enableGeneralCall )
{
  enableWIRE();
  resetWIRE();

  // Set slave mode
  sercom->I2CS.CTRLA.bit.MODE = I2C_SLAVE_OPERATION;

  sercom->I2CS.ADDR.reg = SERCOM_I2CS_ADDR_ADDR( ucAddress & 0x7Ful ) | // 0x7F, select only 7 bits
                          SERCOM_I2CS_ADDR_ADDRMASK( 0x00ul );          // 0x00, only match exact address
  if (enableGeneralCall) {
    sercom->I2CS.ADDR.reg |= SERCOM_I2CS_ADDR_GENCEN;                   // enable general call (address 0x00)
  }

  // Set the interrupt register
  sercom->I2CS.INTENSET.reg = SERCOM_I2CS_INTENSET_PREC |   // Stop
                              SERCOM_I2CS_INTENSET_AMATCH | // Address Match
                              SERCOM_I2CS_INTENSET_DRDY ;   // Data Ready

#ifndef SAMD20
  while ( sercom->I2CM.SYNCBUSY.bit.SYSOP != 0 )
#else
  while(sercom->I2CM.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
  {
    // Wait the SYSOP bit from SYNCBUSY to come back to 0
  }
}

void SERCOM::initMasterWIRE( uint32_t baudrate )
{
  enableWire();
  resetWIRE();

  // Set master mode and enable SCL Clock Stretch mode (stretch after ACK bit)
  sercom->I2CM.CTRLA.reg =  SERCOM_I2CM_CTRLA_MODE( I2C_MASTER_OPERATION )/* |
                            SERCOM_I2CM_CTRLA_SCLSM*/ ;

  // Enable Smart mode and Quick Command
  //sercom->I2CM.CTRLB.reg =  SERCOM_I2CM_CTRLB_SMEN /*| SERCOM_I2CM_CTRLB_QCEN*/ ;


  // Enable all interrupts
//  sercom->I2CM.INTENSET.reg = SERCOM_I2CM_INTENSET_MB | SERCOM_I2CM_INTENSET_SB | SERCOM_I2CM_INTENSET_ERROR ;

  // Synchronous arithmetic baudrate
  sercom->I2CM.BAUD.bit.BAUD = SystemCoreClock / ( 2 * baudrate) - 5 - (((SystemCoreClock / 1000000) * WIRE_RISE_TIME_NANOSECONDS) / (2 * 1000));
}

void SERCOM::prepareNackBitWIRE( void )
{
  if(isMasterWIRE()) {
    // Send a NACK
    sercom->I2CM.CTRLB.bit.ACKACT = 1;
  } else {
    sercom->I2CS.CTRLB.bit.ACKACT = 1;
  }
}

void SERCOM::prepareAckBitWIRE( void )
{
  if(isMasterWIRE()) {
    // Send an ACK
    sercom->I2CM.CTRLB.bit.ACKACT = 0;
  } else {
    sercom->I2CS.CTRLB.bit.ACKACT = 0;
  }
}

void SERCOM::prepareCommandBitsWire(uint8_t cmd)
{
  if(isMasterWIRE()) {
    sercom->I2CM.CTRLB.bit.CMD = cmd;

#ifndef SAMD20
    while(sercom->I2CM.SYNCBUSY.bit.SYSOP)
#else
    while(sercom->I2CM.STATUS.bit.SYNCBUSY)
#endif /* SAMD20 */
    {
      // Waiting for synchronization
    }
  } else {
    sercom->I2CS.CTRLB.bit.CMD = cmd;
  }
}

bool SERCOM::startTransmissionWIRE(uint8_t address, SercomWireReadWriteFlag flag)
{
  // 7-bits address + 1-bits R/W
  address = (address << 0x1ul) | flag;

  // Wait idle or owner bus mode
  while ( !isBusIdleWIRE() && !isBusOwnerWIRE() );

  // Send start and address
  sercom->I2CM.ADDR.bit.ADDR = address;

  // Address Transmitted
  if ( flag == WIRE_WRITE_FLAG ) // Write mode
  {
    while( !sercom->I2CM.INTFLAG.bit.MB )
    {
      // Wait transmission complete
    }
  }
  else  // Read mode
  {
    while( !sercom->I2CM.INTFLAG.bit.SB )
    {
        // If the slave NACKS the address, the MB bit will be set.
        // In that case, send a stop condition and return false.
        if (sercom->I2CM.INTFLAG.bit.MB) {
            sercom->I2CM.CTRLB.bit.CMD = 3; // Stop condition
            return false;
        }
      // Wait transmission complete
    }

    // Clean the 'Slave on Bus' flag, for further usage.
    //sercom->I2CM.INTFLAG.bit.SB = 0x1ul;
  }


  //ACK received (0: ACK, 1: NACK)
  if(sercom->I2CM.STATUS.bit.RXNACK)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool SERCOM::sendDataMasterWIRE(uint8_t data)
{
  //Send data
  sercom->I2CM.DATA.bit.DATA = data;

  //Wait transmission successful
  while(!sercom->I2CM.INTFLAG.bit.MB) {

    // If a bus error occurs, the MB bit may never be set.
    // Check the bus error bit and bail if it's set.
    if (sercom->I2CM.STATUS.bit.BUSERR) {
      return false;
    }
  }

  //Problems on line? nack received?
  if(sercom->I2CM.STATUS.bit.RXNACK)
    return false;
  else
    return true;
}

bool SERCOM::sendDataSlaveWIRE(uint8_t data)
{
  //Send data
  sercom->I2CS.DATA.bit.DATA = data;

  //Problems on line? nack received?
  if(!sercom->I2CS.INTFLAG.bit.DRDY || sercom->I2CS.STATUS.bit.RXNACK)
    return false;
  else
    return true;
}

bool SERCOM::isMasterWIRE( void )
{
  return sercom->I2CS.CTRLA.bit.MODE == I2C_MASTER_OPERATION;
}

bool SERCOM::isSlaveWIRE( void )
{
  return sercom->I2CS.CTRLA.bit.MODE == I2C_SLAVE_OPERATION;
}

bool SERCOM::isBusIdleWIRE( void )
{
  return sercom->I2CM.STATUS.bit.BUSSTATE == WIRE_IDLE_STATE;
}

bool SERCOM::isBusOwnerWIRE( void )
{
  return sercom->I2CM.STATUS.bit.BUSSTATE == WIRE_OWNER_STATE;
}

bool SERCOM::isDataReadyWIRE( void )
{
  return sercom->I2CS.INTFLAG.bit.DRDY;
}

bool SERCOM::isStopDetectedWIRE( void )
{
  return sercom->I2CS.INTFLAG.bit.PREC;
}

bool SERCOM::isRestartDetectedWIRE( void )
{
  return sercom->I2CS.STATUS.bit.SR;
}

bool SERCOM::isAddressMatch( void )
{
  return sercom->I2CS.INTFLAG.bit.AMATCH;
}

bool SERCOM::isMasterReadOperationWIRE( void )
{
  return sercom->I2CS.STATUS.bit.DIR;
}

bool SERCOM::isRXNackReceivedWIRE( void )
{
  return sercom->I2CM.STATUS.bit.RXNACK;
}

int SERCOM::availableWIRE( void )
{
  if(isMasterWIRE())
    return sercom->I2CM.INTFLAG.bit.SB;
  else
    return sercom->I2CS.INTFLAG.bit.DRDY;
}

uint8_t SERCOM::readDataWIRE( void )
{
  if(isMasterWIRE())
  {
    while( sercom->I2CM.INTFLAG.bit.SB == 0 )
    {
      // Waiting complete receive
    }

    return sercom->I2CM.DATA.bit.DATA ;
  }
  else
  {
    return sercom->I2CS.DATA.reg ;
  }
}

