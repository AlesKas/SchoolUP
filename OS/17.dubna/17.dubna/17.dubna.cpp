#include "pch.h"
#include <stdio.h>
#include <iostream>
using namespace std;

double obvod_obdelnika(double a, double b){
	_asm{
		fld a
		fld b
		fadd st, st(1)
		fadd st, st
	}
}

double obsah_obdelnika(double a, double b) {
	_asm {
		fld a
		fld b
		fmul
	}
}

double obvod_ctverce(double a) {
	_asm {
		push 4
		fld a
		fimul dword ptr[esp]
		add esp, 4
	}
}

double obsah_ctverce(double a) {
	_asm {
		fld a
		fmul st, st
	}
}

double obvod_kruhu(double r) {
	_asm {
		fldpi
		fld r
		fmul
		fadd st, st
	}
}

double obsah_kruhu(double d) {
	_asm {
		fld d
		push 2
		fidiv dword ptr[esp]
		add esp, 4
		fmul st, st
		fldpi
		fmul
	}
}

float avg(float a, float b, float c) {
	_asm {
		fld a
		fld b
		fadd
		fld c
		fadd
		push 3
		fidiv dword ptr[esp]
		add esp, 4
	}
}

double heron(double a, double b, double c) {
	double s;
	_asm {
		fld a
		fld b
		fadd
		fld c
		fadd
		push 2
		fidiv dword ptr[esp]
		add esp, 4

		fst s

		fld a
		fsub

		fld s
		fld b
		fsub
		fmul

		fld s
		fld c
		fsub
		fmul

		fld s
		fmul

		fabs
		fsqrt
	}
}

int main()
{
	cout << "Obvod obdelniku (5.3, 6.5) je " << obvod_obdelnika(5.3, 6.5) << endl;
	cout << "Obsah obdelniku (5.3, 6.5) je " << obsah_obdelnika(5.3, 6.5) << endl;
	cout << "Obvod ctverce (5.5) je " << obvod_ctverce(5.5) << endl;
	cout << "Obsah ctverce (5.5) je " << obsah_ctverce(5.5) << endl;
	cout << "Obvod kruhu (5.5) je " << obvod_kruhu(5.5) << endl;
	cout << "Obsah kruhu (5.5) je " << obsah_kruhu(5.5) << endl;
	cout << "Prumer cisel (3.5, 4.3, 5.8) je " << avg(3.5, 4.3, 5.8) << endl;
	cout << "Obsah trojuhelnika (3.5, 4.3, 5.8) je " << heron(3.5, 4.3, 5.8) << endl;
}
