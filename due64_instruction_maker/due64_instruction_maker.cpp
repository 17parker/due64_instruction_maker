//This is a helper program, to make controller instructions easier
//Angle only mode - only the analog stick data is being updated 

#include <array>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <bitset>
#include <string>

using namespace std;

void angles_and_buttons();
void angles_only();
void show_buttons();

const uint8_t analog_max = 95;
array<string, 16> buttons = { "A","B","Z","P","DU","DD","DL","DR","RST","UNUSED","LTRIGGER","RTRIGGER","CU","CD","CL","CR" }; //P is start ("pause")


int main() {

	/*
	for personal refernce
	enum button_offsets {
		A,
		B,
		Z,
		START,
		DU,
		DD,
		DL,
		DR,
		RST,
		UNUSED,
		L,
		R,
		CU,
		CD,
		CL,
		CR,
		X = 16,
		Y = 24
	};
	*/

	cout << "Enter mode - 1 for angles, 2 for angles and buttons" << endl;
	char response;
	cin >> response;
	cin.clear();
	cin.ignore(10000, '\n');
	switch (response) {
	case '1':
		show_buttons();
		angles_only();
		break;
	case '2':
		show_buttons();
		angles_and_buttons();
		break;

	}
	return 0;
}

void show_buttons() {
	cout << endl << "    ";
	for (uint8_t i = 0; i < 9; ++i) {
		cout << buttons[i] << "  ";
	}
	cout << endl << "         " << buttons[10] << "  " << buttons[11] << endl << "           "
		<< buttons[12] << "  " << buttons[13] << "  " << buttons[14] << "  " << buttons[15]
		<<endl << endl << endl;
}

void angles_only() {
	while (1) {
		float angle = 0.0;
		float magnitude = 0;
		string input;
		int8_t x = 0;
		int8_t y = 0;
		uint32_t output = 0;
		int frames = 0;
		output = 0;
		cout << "Enter angle of the stick (0 is right, 90 is forward and so on...\n";
		cin >> angle;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Magnitude of the stick (percentage of max in decimal, 0 <= x <= 1)\n";
		cin >> magnitude;
		cin.clear();
		cin.ignore(10000, '\n');
		if (magnitude > 1 || magnitude < 0)
			magnitude = 0;
		for (uint8_t i = 0; i < 16; ++i) {
			if (input.find(buttons[i]) != string::npos) 
				output |= (1 << (i));
			
		}
		x = analog_max * cos(angle * 0.017453) * magnitude;
		y = analog_max * sin(angle * 0.017453) * magnitude;
		uint8_t new_x = 0;
		uint8_t new_y = 0;
		for (uint8_t i = 0; i <= 7; ++i) {	//the bits need to be reversed
			new_x |= (x & 1) << (7 - i);
			x = x >> 1;
		}
		for (uint8_t i = 0; i <= 7; ++i) {
			new_y |= (y & 1) << (7 - i);
			y = y >> 1;
		}
		output |= (new_x << 16) & 0b11111111 << 16;
		output |= (new_y << 24) & 0b11111111 << 24;

		cout << "0x" << hex << output << endl << endl;
	}
}

void angles_and_buttons() {
	while (1) {
		float angle = 0.0;
		float magnitude = 0;
		string input;
		int8_t x = 0;
		int8_t y = 0;
		uint32_t output = 0;
		int frames = 0;
		output = 0;
		cout << "Pressed buttons (ALL UPPERCASE):\n";
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Angle of the stick (0 is right, 90 is forward and so on...\n";
		cin >> angle;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Magnitude of the stick (percentage of max in decimal, 0 <= x <= 1)\n";
		cin >> magnitude;
		cin.clear();
		cin.ignore(10000, '\n');
		if (magnitude > 1 || magnitude < 0)
			magnitude = 0;
		cout << "How many frames to repeat this movement\n";
		cin >> frames;
		cin.clear();
		cin.ignore(10000, '\n');
		for (uint8_t i = 0; i < 16; ++i) {
			if (input.find(buttons[i]) != string::npos) 
				output |= (1 << (i));
			
		}
		x = analog_max * cos(angle * 0.017453) * magnitude;
		y = analog_max * sin(angle * 0.017453) * magnitude;
		uint8_t new_x = 0;
		uint8_t new_y = 0;
		for (uint8_t i = 0; i <= 7; ++i) {	//the bits need to be reversed
			new_x |= (x & 1) << (7 - i);
			x = x >> 1;
		}
		for (uint8_t i = 0; i <= 7; ++i) {
			new_y |= (y & 1) << (7 - i);
			y = y >> 1;
		}
		output |= (new_x << 16) & 0b11111111 << 16;
		output |= (new_y << 24) & 0b11111111 << 24;

		cout << "{ 0x" << hex << output << ", " << dec << frames << " }\n\n";
	}
}