/*
 * SPI Master library for Arduino Zero.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "SPI.h"
#include <Arduino.h>
#include <wiring_private.h>
#include <assert.h>

#define SPI_IMODE_NONE 0
#define SPI_IMODE_EXTINT 1
#define SPI_IMODE_GLOBAL 2

SPIClass::SPIClass( SERCOM *p_sercom, uint8_t uc_pinMISO, uint8_t uc_pinSCK,
                    uint8_t uc_pinMOSI, SercomSpiTXPad PadTx,
                    SercomRXPad PadRx )
{
    _initialized = false;
    assert( p_sercom != NULL );
    _p_sercom = p_sercom;

    // pins
    _uc_pinMiso = uc_pinMISO;
    _uc_pinSCK = uc_pinSCK;
    _uc_pinMosi = uc_pinMOSI;

    // SERCOM pads
    _padTx = PadTx;
    _padRx = PadRx;

    // Default setup
    _clock = 4000000;
    _bitOrder = MSBFIRST;
    _dataMode = SPI_MODE0;
    _settingsInternal = SPISettings( _clock, _bitOrder, _dataMode );
}

void SPIClass::begin()
{
    init();
    _settingsInternal.init_AlwaysInline( _clock, _bitOrder, _dataMode );
    config( _settingsInternal );
}

void SPIClass::init()
{
    if( _initialized ) return;
    _interruptMode = SPI_IMODE_NONE;
    _interruptSave = 0;
    _interruptMask = 0;
    _initialized = true;
}

void SPIClass::config( SPISettings settings )
{
    // PIO init
    pinPeripheral( _uc_pinMiso, g_APinDescription[_uc_pinMiso].ulPinType );
    pinPeripheral( _uc_pinSCK, g_APinDescription[_uc_pinSCK].ulPinType );
    pinPeripheral( _uc_pinMosi, g_APinDescription[_uc_pinMosi].ulPinType );

    _p_sercom->initSPI( _padTx, _padRx, SPI_CHAR_SIZE_8_BITS,
                        settings.bitOrder );
    _p_sercom->initSPIClock( settings.dataMode, settings.clockFreq );

    _p_sercom->enableSPI();
}

void SPIClass::end()
{
    if( _initialized ) {
        _p_sercom->resetSPI();
        _p_sercom->endSPI();
        _initialized = false;
    }

    pinMode( _uc_pinMiso, OUTPUT );
    pinMode( _uc_pinSCK, OUTPUT );
    pinMode( _uc_pinMosi, OUTPUT );
    digitalWrite( _uc_pinMiso, HIGH );
    digitalWrite( _uc_pinSCK, HIGH );
    digitalWrite( _uc_pinMosi, HIGH );
}

#ifndef interruptsStatus
#define interruptsStatus() __interruptsStatus()
static inline unsigned char __interruptsStatus( void )
    __attribute__( ( always_inline, unused ) );
static inline unsigned char __interruptsStatus( void )
{
    // See
    // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0497a/CHDBIBGJ.html
    return ( __get_PRIMASK() ? 0 : 1 );
}
#endif

void SPIClass::usingInterrupt( int interruptNumber )
{
    if( ( interruptNumber == NOT_AN_INTERRUPT ) ||
        ( interruptNumber == EXTERNAL_INT_NMI ) )
        return;

    uint8_t irestore = interruptsStatus();
    noInterrupts();

    if( interruptNumber >= EXTERNAL_NUM_INTERRUPTS )
        _interruptMode = SPI_IMODE_GLOBAL;
    else {
        _interruptMode |= SPI_IMODE_EXTINT;
        _interruptMask |= ( 1 << interruptNumber );
    }

    if( irestore ) interrupts();
}

void SPIClass::notUsingInterrupt( int interruptNumber )
{
    if( ( interruptNumber == NOT_AN_INTERRUPT ) ||
        ( interruptNumber == EXTERNAL_INT_NMI ) )
        return;

    if( _interruptMode & SPI_IMODE_GLOBAL )
        return; // can't go back, as there is no reference count

    uint8_t irestore = interruptsStatus();
    noInterrupts();

    _interruptMask &= ~( 1 << interruptNumber );

    if( _interruptMask == 0 ) _interruptMode = SPI_IMODE_NONE;

    if( irestore ) interrupts();
}

void SPIClass::beginTransaction( SPISettings settings )
{
    if( _interruptMode != SPI_IMODE_NONE ) {
        if( _interruptMode & SPI_IMODE_GLOBAL ) {
            _interruptSave = interruptsStatus();
            noInterrupts();
        }
        else if( _interruptMode & SPI_IMODE_EXTINT )
            EIC->INTENCLR.reg = EIC_INTENCLR_EXTINT( _interruptMask );
    }

    config( settings );
}

void SPIClass::endTransaction( void )
{
    if( _interruptMode != SPI_IMODE_NONE ) {
        if( _interruptMode & SPI_IMODE_GLOBAL ) {
            if( _interruptSave ) interrupts();
        }
        else if( _interruptMode & SPI_IMODE_EXTINT )
            EIC->INTENSET.reg = EIC_INTENSET_EXTINT( _interruptMask );
    }
}

void SPIClass::setBitOrder( BitOrder order )
{
    _bitOrder = order;
}

void SPIClass::setDataMode( uint8_t mode )
{
    _dataMode = mode;
}

void SPIClass::setClockDivider( uint8_t div )
{
    _clock = SystemCoreClock / div;
}

byte SPIClass::transfer( uint8_t data )
{
    return _p_sercom->transferDataSPI( data );
}

uint16_t SPIClass::transfer16( uint16_t data )
{
    union
    {
        uint16_t val;
        struct
        {
            uint8_t lsb;
            uint8_t msb;
        };
    } t;

    t.val = data;

    if( _p_sercom->getDataOrderSPI() == LSB_FIRST ) {
        t.lsb = transfer( t.lsb );
        t.msb = transfer( t.msb );
    }
    else {
        t.msb = transfer( t.msb );
        t.lsb = transfer( t.lsb );
    }

    return t.val;
}

void SPIClass::transfer( void *buf, size_t count )
{
    uint8_t *buffer = reinterpret_cast<uint8_t *>( buf );
    for( size_t i = 0; i < count; i++ ) {
        *buffer = transfer( *buffer );
        buffer++;
    }
}

void SPIClass::attachInterrupt()
{
    // Should be enableInterrupt()
}

void SPIClass::detachInterrupt()
{
    // Should be disableInterrupt()
}

#if SPI_INTERFACES_COUNT > 0
/* In case new variant doesn't define these macros,
 * we put here the ones for Arduino Zero.
 *
 * These values should be different on some variants!
 *
 * The SPI PAD values can be found in cores/arduino/SERCOM.h:
 *   - SercomSpiTXPad
 *   - SercomRXPad
 */
#ifndef PERIPH_SPI
#define PERIPH_SPI sercom4
#define PAD_SPI_TX SPI_PAD_2_SCK_3
#define PAD_SPI_RX SERCOM_RX_PAD_0
#endif // PERIPH_SPI
SPIClass SPI( &PERIPH_SPI, PIN_SPI_MISO, PIN_SPI_SCK, PIN_SPI_MOSI, PAD_SPI_TX,
              PAD_SPI_RX );
#endif
#if SPI_INTERFACES_COUNT > 1
SPIClass SPI1( &PERIPH_SPI1, PIN_SPI1_MISO, PIN_SPI1_SCK, PIN_SPI1_MOSI,
               PAD_SPI1_TX, PAD_SPI1_RX );
#endif
#if SPI_INTERFACES_COUNT > 2
SPIClass SPI2( &PERIPH_SPI2, PIN_SPI2_MISO, PIN_SPI2_SCK, PIN_SPI2_MOSI,
               PAD_SPI2_TX, PAD_SPI2_RX );
#endif
#if SPI_INTERFACES_COUNT > 3
SPIClass SPI3( &PERIPH_SPI3, PIN_SPI3_MISO, PIN_SPI3_SCK, PIN_SPI3_MOSI,
               PAD_SPI3_TX, PAD_SPI3_RX );
#endif
#if SPI_INTERFACES_COUNT > 4
SPIClass SPI4( &PERIPH_SPI4, PIN_SPI4_MISO, PIN_SPI4_SCK, PIN_SPI4_MOSI,
               PAD_SPI4_TX, PAD_SPI4_RX );
#endif
#if SPI_INTERFACES_COUNT > 5
SPIClass SPI5( &PERIPH_SPI5, PIN_SPI5_MISO, PIN_SPI5_SCK, PIN_SPI5_MOSI,
               PAD_SPI5_TX, PAD_SPI5_RX );
#endif
