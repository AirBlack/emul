/*
 * using clk = std::chrono::steady_clock;
		auto pop = std::chrono::microseconds(tempo)/(cc*bb)/2;
		auto tp_now = clk::now();
		auto tp_next = tp_now;
		tp_now = clk::now();
 * */
#include "IO.h"
#include <chrono>

void IO::write(unsigned address, uint8_t value)
{
	if ((address & 1) == 0) {
		_port_fe = value;

			int lev = (_port_fe >> 3) & 0x03;//4?
			switch(lev) {
				case 0x00: _adrv->set_level(-16384 - 8192); break;
				case 0x01: _adrv->set_level(-16384); break;
				case 0x02: _adrv->set_level(16384); break;
				case 0x03: _adrv->set_level(16384 + 8192); break;
				default: ;
			}

	}
}

uint8_t IO::read(unsigned address) const
{
	uint8_t tap= (address >> 6);
	uint8_t a = (address >> 8);
	uint8_t p = (address & 0xff);

	if (p == 0xfe) {
		switch (a) {
		case 0x7f: return (_ear << 6) | _key_matrix[0];
		case 0xbf: return (_ear << 6) | _key_matrix[1];
		case 0xdf: return (_ear << 6) | _key_matrix[2];
		case 0xef: return (_ear << 6) | _key_matrix[3];
		case 0xf7: return (_ear << 6) | _key_matrix[4];
		case 0xfb: return (_ear << 6) | _key_matrix[5];
		case 0xfd: return (_ear << 6) | _key_matrix[6];
		case 0xfe: return (_ear << 6) | _key_matrix[7];
		default: return 0;
		}
	}


	return 0;
}

void IO::keydown(unsigned row, unsigned col)
{
	_key_matrix[row] &= ~(1<<col);
}

void IO::keyup(unsigned row, unsigned col)
{
	_key_matrix[row] |= (1<<col);
}
