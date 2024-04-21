
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <pi_lw_gpio.h>

// <CTF_Settings>

	#define HINT_1
	//#define HINT_2
	#define HINT_3

// <CTF_Settings/>

// Setting-up the pins for the keypad
#define GPIO_BCM_KEYPAD_MIN (2)
#define GPIO_BCM_KEYPAD_MAX (11)

// 0xff end of string
const char PASSCODE_TERMINATE_CHAR = '\xff';

// 13371985 First release of Windows
char *passcode_combination = "\x01\x03\x03\x07\x01\x09\x08\x05\xff";

// Correct substring that entered so far from user
char *passcode_combination_try;

struct keypad_button_handler
{
	char currentPush[10];
	char lastPush[10];
} typedef keypad_button_handler;

keypad_button_handler g_btnHandler;

int keypad_button_handler__getPushedButton(keypad_button_handler *btnHandler){
	for (int i = 0; i < 10; i++)
	{
		// On peak rise, return current index of button
		if(btnHandler->currentPush[i] && !btnHandler->lastPush[i])
			return i;
	}
	
	return -1;
}

void read_keypad(keypad_button_handler *btnHandler){
	int val;
	int ind = 0;
	
	// Iterate over all 10 pins and update the handler bitmap
	for (int i = GPIO_BCM_KEYPAD_MIN; i <= GPIO_BCM_KEYPAD_MAX; i++)
	{
		val = gpio_read_level(i);

		// last = current
		btnHandler->lastPush[ind] = btnHandler->currentPush[ind];

		// current = read()
		btnHandler->currentPush[ind] = val;

		++ind;
	}
}

void setup_keypad_gpio(){
	for (int i = GPIO_BCM_KEYPAD_MIN; i <= GPIO_BCM_KEYPAD_MAX; i++)
	{
		gpio_set_mode(i, GPIO_INPUT);
	}	
}

// This is our WIN function
void openDoor(){
	puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	puts("                DOOR OPENED                ");
	puts("~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~");
}

int main(){
	puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	puts("      Welcome to s3kur1ty 5y5tem v1.0      ");
	puts("~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~");

	// Initialize I/O
	setup_keypad_gpio();
	#ifdef HINT_1
	puts("[+] Keypad initialized!");
	#endif


	// Initialize Keypad struct handler
	memset(&g_btnHandler, 0, sizeof(g_btnHandler));
	
	// Reset progress of combination
	passcode_combination_try = passcode_combination;
	
	#ifdef HINT_3
	puts("[!] Reading keys...");
	#endif

	// Let user guess passcode while correct passcode entered hasn't reached the end
	do{
		char rise_btn;

		read_keypad(&g_btnHandler);
		rise_btn = (char)keypad_button_handler__getPushedButton(&g_btnHandler);

		if(rise_btn != -1){

			// If correct digit entered, increment passcode pointer
			if(rise_btn == *passcode_combination_try){
				++passcode_combination_try;
			}
			// Otherwise, zero progress
			else{
				passcode_combination_try = passcode_combination;
			}
		}
	}while(*passcode_combination_try != PASSCODE_TERMINATE_CHAR);

	// # Hint end condition
	#ifdef HINT_2
	if(*passcode_combination_try == PASSCODE_TERMINATE_CHAR){
	#endif
	{
		// Eventually open door!
		openDoor();
	}

}
