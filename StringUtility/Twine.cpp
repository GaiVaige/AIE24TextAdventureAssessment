﻿#include "Twine.h"
#include <iostream>
#include <time.h>



Twine::Twine() {
	//initialise an empty twine 
	twine = new char[1];
	//ensure that twine contains a null pointer
	twine[0] = '\0';
}

Twine::Twine(const char* c) {
	//get the length of C by calling 
	size_t cLen = Length(c);
	twine = new char[cLen + 1];
	//Individually copy each char
	for (int i = 0; i < cLen; i++) {
		twine[i] = c[i];
	}
	twine[cLen] = '\0';
}

Twine::Twine(const Twine& c) {
	//call the twine assignment function to copy the data from c to the new twine
	this->twine = new char[1] {'\0'};
	this->SetTwine(c.twine);
}

Twine::~Twine() {
	//ensure any attached twine is destroyed in deletion/exiting scope
	delete[] twine;
}

//void Twine::SetTwine(Twine c) {
//	//confirm length of char array
//	size_t l = c.Length();
//	//destroy previous twine 
//	delete[] this->twine;
//	//copy each value in array to new array
//	twine = new char[l + 1];
//	for (int i = 0; i < l; i++) {
//		twine[i] = c[i];
//	}
//	twine[l] = '\0';
//}

void Twine::SetTwine(const Twine c) {
	//confirm length of char array
	size_t l = c.Length();
	//destroy previous twine 
	delete[] this->twine;
	//copy each value in array to new array
	twine = new char[l+1];
	for (int i = 0; i < l; i++) {
			twine[i] = c[i];
	}
	twine[l] = '\0';
}

void Twine::Copy(Twine& twineA, const Twine& twineB) {
	//functions the same as copy constructor
	twineA.SetTwine(twineB.twine);
}

void Twine::GetTwine(){
	//initalise a single char to be referenced for taking in characters from input
	char c;

	//place characters immediately into input buffer

	std::cin.get(c);
	std::cin.putback(c);
	
	//std::cin stops when enter is pressed
	//check size of buffer when enter is pressed (cin halts at this point)
	//this is used as a reference to create the new array to ensure that nothing beyond
	//what has been inputted to cin is used
	std::streamsize size = std::cin.rdbuf()->in_avail();
	//create a pointer to a new array, newTwi, to have the data copied to from buffer, and size to buffer+1
	// to account for nullchar
	char* newTwine = new char[size];
	//read an amount of characters equal to the read characters from buffer
	std::cin.readsome(newTwine, size);
	//failsafe to ensure that there is definitely a nullchar and overrides the \n char at the end
	newTwine[size - 1] = '\0';
	SetTwine(newTwine);
	//flush the memory and input stream to ensure no leakages
	delete[] newTwine;
	&std::ostream::flush;
}

const char* Twine::TStr() const {
	//returns twine for use with std::Cout<<
	//redundant as operator overloaded
	return this->twine;
}

void Twine::DisplayTwine()  const {
    //cleaner method of displaying twine
	std::cout << twine << '\n';
}

size_t Twine::Length() const{
	for (int i = 0; ; i++) {
		//if end of string detected, return value of i
		if (this->twine[i] == '\0') {
			return i;
		}
	}
}

size_t Twine::Length(const char* c) {
	for (int i = 0; ; i++) {
		if (c[i] == '\0') {
			//if end of string detected, return value of i
			return i;
		}
	}
}

char Twine::CharAt(int i) const {
	//if the index checked is a null terminator, or i lies out of range, return 0
	if (this->twine[i] == '\0' || i > this->Length() || i < 0) {
		return '\0';
	}
	else {
		return this->twine[i];
	}
}

size_t Twine::CharFind(char c) const {
	for (int i = 0; i < this->Length(); i++) {

		if (this->twine[i] == c) {
			return i;

		}

	}
	return (size_t)-1;
}

size_t Twine::Find(const Twine& subString) const {

	size_t a = this->Length();
	size_t b = subString.Length();
	int cL = 0;
	int t = 0;

	for (int i = 0; i < a; i++) {
		//if the first char in substring matches the current char
		if (this->twine[i] == subString[cL]) {
			//iterate through both w/o incrementing i
			for (int j = 0; j < b; j++) {
				//if it reaches beyond the end of twine return that it is not found
				if (i + j > a) {
					return (size_t)-1;
				}

				if (this->twine[i + j] != subString[j]) {
					break;
				}
				//if the internal loop counter is the maximum index of the new string, return the index
				if (j == b - 1) {
					return i;
				}
			}


		}

	}
	t = -1;
	return t;


}

size_t Twine::Find(const Twine& subString, int sIn) const {

	size_t a = this->Length();
	size_t b = subString.Length();
	int cL = 0;
	int t = 0;


	for (int i = sIn; i < a; i++) {

		if (this->twine[i] == subString[cL]) {
			//if the first char in substring matches the current char
			for (int j = 0; j < b; j++) {
				//iterate through both w/o incrementing i
				if (i + j > a) {
					return (size_t)- 1;
				}

				if (this->twine[i + j] != subString[j]) {
					break;
				}
				//if the internal loop counter is the maximum index of the new string, return the index
				if (j == b - 1) {
					return i;
				}
			}


		}

	}
	t = -1;
	return t;
}

Twine Twine::ToLower() const{

	size_t l = this->Length();
	Twine newT;
	char* newArr = new char[l + 1];

	for (int i = 0; i < l; i++) {

		//swaps any given letter to lowercase
		newArr[i] = (char)tolower(this->twine[i]);


	}
	newArr[l] = '\0';
	//internally sets the twine of newT to newArr
	newT.SetTwine(newArr);
	delete[] newArr;
	return newT;
}
	 
Twine Twine::ToUpper() const{


	size_t l = this->Length();
	Twine newT;
	char* newArr = new char[l + 1];

	for (int i = 0; i < l; i++) {

		//swaps any given letter to uppercase
		newArr[i] = (char)toupper(this->twine[i]);


	}
	newArr[l] = '\0';
	//internally sets the twine of newT to newArr
	newT.SetTwine(newArr);
	delete[] newArr;
	return newT;
}

bool Twine::EqualTo(const Twine& c) const{


	size_t i = this->LengthNoSpace();
	size_t cI = c.LengthNoSpace();
	//only enter if the same length
	if (i == cI) {


		for (int a = 0; a < i; a++) {
			//check against lowercase versions of eaech char
			if (this->ToLower()[a] == c.ToLower()[a]) {
			}
			else {
				//at any point they are not equal, exit
				return false;
			}

		}
		return true;
	}
	else {
		return false;
	}
}

void Twine::Replace(const Twine& find, const Twine& newc) {
	size_t replaceStringPos = this->Find(find);
	if (replaceStringPos == -1) {
		return;
	}
	//ensures multiple copies can be swapped
	while (replaceStringPos != -1) {
		size_t findLength = find.Length();
		size_t newStringLen = newc.Length();
		int currentSwapPos = 0;
		size_t returnStringLen = (newStringLen - findLength) + this->Length() + 1;
		char* newT = new char[returnStringLen];

		int newCTracker = 0;
		int checkTrack = 0;
		//copy until the beginning of replacement
		for (currentSwapPos; currentSwapPos < replaceStringPos && currentSwapPos < returnStringLen; currentSwapPos++) {

			newT[currentSwapPos] = this->twine[currentSwapPos];
		}
		//until currentSwapPos reaches the end of the replaceString
		for (currentSwapPos; currentSwapPos < replaceStringPos + newStringLen && currentSwapPos < returnStringLen; currentSwapPos++) {
			newT[currentSwapPos] = newc[newCTracker];
			newCTracker++;
			checkTrack = currentSwapPos;
		}
		//copy any remanining data
		for (int finalTracker = 0; currentSwapPos < returnStringLen; currentSwapPos++) {
			size_t j = replaceStringPos + findLength + finalTracker;
			newT[currentSwapPos] = this->twine[j];
			finalTracker++;
		}
		newT[returnStringLen] = '\0';
		this->SetTwine(newT);
		//check if there is another instance in string
		replaceStringPos = this->Find(find, checkTrack);
		delete[] newT;
	}
}

void Twine::Prepend(const Twine& c) {

	size_t curCSize = this->Length();
	size_t cSize = c.Length();
	size_t newSize = cSize + curCSize + 1;
	char* newC = new char[newSize];
	//copies new characters to start of new array
	for (int i = 0; i < cSize && i < newSize; i++) {

		newC[i] = c[i];

	}
	//copies old twine over
	for (int i = 0; i < curCSize && cSize + i < newSize; i++) {

		newC[cSize + i] = this->twine[i];

	}


	newC[newSize - 1] = '\0';
	this->SetTwine(newC);
	delete[] newC;

}

void Twine::Prepend(char c) {

	size_t curCSize = this->Length() + 2;
	char* newC = new char[curCSize];
	//sets first char of new array to c
	newC[0] = c;
	for (int i = 0; i < curCSize; i++) {

		newC[i] = this->twine[i];

	}
	newC[curCSize-1] = '\0';
	this->SetTwine(newC);
	delete[] newC;

}

void Twine::Append(const Twine& c) {

	size_t curCSize = this->Length();
	size_t cSize = c.Length();
	size_t newSize = cSize + curCSize + 1;
	char* newC = new char[newSize];
	//copies original twine to new array
	for (int i = 0; i < newSize; i++) {

		newC[i] = this->twine[i];

	}
	//copies new data
	for (int i = 0; i < cSize && i < newSize; i++) {

		newC[curCSize + i] = c[i];

	}
	newC[newSize -1] = '\0';
	this->SetTwine(newC);
	delete[] newC;

}

void Twine::Append(char c) {

	size_t curCSize = this->Length() + 2;
	char* newC = new char[curCSize];

	for (int i = 0; i < curCSize; i++) {

		newC[i] = this->twine[i];

	}
	//copies new character to end of array
	newC[curCSize] = c;
	newC[curCSize - 1] = '\0';
	this->SetTwine(newC);
	delete[] newC;

}

std::ostream& operator << (std::ostream &out, const Twine &t) {

	int i = 0;
	char* c = t.twine;

	for (;c[i] != '\0';i++) {
		out << c[i];
	}
	return out;

}

std::istream& operator >> (std::istream& in, Twine& t) {

	t.GetTwine();

	return in;

}

Twine& Twine::operator = (const Twine& t1) {

	if (this == &t1) {
		return *this;
	}

	this->SetTwine(t1);
	return *this;
}

bool Twine::operator == (const Twine& t) const {

	if (this->EqualTo(t)) {
		return true;
	}
	else {
		return false;
	}


}

bool Twine::operator != (const Twine& t) const{
	if (this->EqualTo(t)) {
		return false;
	}
	else {
		return true;
	}
}

Twine& Twine::operator += (Twine& t) {

	if (this == &t) {
		return *this;
	}

	this->Append(t.twine);
	return *this;

}

Twine Twine::operator + (Twine& t) {

	Twine tw;
	Twine* newTwine = new Twine;
	newTwine->SetTwine(this->twine);
	tw.SetTwine(newTwine->twine);
	tw.Append(t.twine);

	delete newTwine;

	return tw;

}

char& Twine::operator [] (size_t i) const{

	return this->twine[i];

}

bool Twine::operator < (const Twine& t) const {
	
	Twine t2 = t.ToLower();
	Twine t1 = this->ToLower();


	char cA = t1.twine[0];
	char cB = t2.twine[0];

	for (int i = 0; ; i++) {

		cA = t1[i];
		cB = t2[i];

		if (isspace(cA)) {
			return true;
		}
		else if (isspace(cB)) {
			return false;
		}
		else if (cA < cB) {
			return true;
		}
		else if (cA > cB) {
			return false;
		}

		if (t1[i + 1] == '\0') {
			return false;
		}
		else if (t2[i + 1] == '\0') {
			return true;
		}


	}
	return false;
}

bool Twine::operator > (const Twine& t) const{

	if (!this->EqualTo(t) && !(*this < t)) {
		return true;
	}
	else {
		return false;
	}
}








//extra functions below!!!

size_t Twine::LengthNoSpace()  const {
	int y = 0;
	for (int i = 0; ; i++) {
		//only increments return value y if there is no space
		if (!isspace(this->twine[i])) {
			//if end of string detected, return current value of y
			if (this->twine[i] == '\0') {
				return y;
			}
			y++;
		}
	}
	return y;
}

size_t Twine::ParseForInt() {


	size_t l = this->Length();
	int digits = 0;
	for (int i = 0; i < l; i++) {

		if (isdigit(this->twine[i])) {
			digits++;


		}

	}


	int* retInt = new int[digits];
	retInt[0] = 0;
	int digTracker = 0;
	for (int i = 0; i < l; i++) {

		if (isdigit(this->twine[i])) {
			if (digTracker < digits) {

				int x = this->twine[i] - 48;
				retInt[digTracker] = x;
				digTracker++;
			}

		}

	}

	long long int finalNum = 0;


	for (int i = digits - 1; i >= 0; --i) {
		long long int multi = 0;
		multi = (long long int)pow(10, (digits - 1) - i);
		long long int adder = (retInt[i] * multi);
		finalNum += adder;
	}

	delete[] retInt;
	return finalNum;
}

bool Twine::FindExclusive(const Twine& c) {

	size_t curLen = this->Length();
	size_t checkLen = Length(c.TStr());
	int searchIndex = 0;
	int previousWordSpot = 0;

	for (int i = 0; i < curLen + 1; i++) {

		if (isspace(this->twine[i]) || this->twine[i] == '\0') {
			int wordGap = i - previousWordSpot;
			previousWordSpot = i + 1;
			//cout << "Word length is: " << wordGap << '\n';


			if (wordGap != checkLen) {
				//cout << "Word length didn't match" << '\n';
			}
			else {
				searchIndex = i - wordGap;
				for (int x = 0; x < checkLen; x++) {
					if (this->twine[searchIndex] == c[x]) {
						//cout << this->twine[searchIndex] << " & " << c[x] << " are the same!!" << '\n';
					}
					else {
						//cout << this->twine[searchIndex] << " & " << c[x] << " are NOT the same!!" << '\n';
						break;
					}
					searchIndex++;
				}
				if (searchIndex == i) {
					return true;
				}
			}
		}

	}

	return false;

}

bool Twine::FindExclusive(const Twine& c, int sIn) {

	size_t curLen = this->Length();
	size_t checkLen = Length(c.TStr());
	int searchIndex = 0;
	int previousWordSpot = 0;

	for (int i = sIn; i < curLen + 1; i++) {

		if (isspace(this->twine[i]) || this->twine[i] == '\0') {
			int wordGap = i - previousWordSpot;
			previousWordSpot = i + 1;
			//cout << "Word length is: " << wordGap << '\n';


			if (wordGap != checkLen) {
				//cout << "Word length didn't match" << '\n';
			}
			else {
				searchIndex = i - wordGap;
				for (int x = 0; x < checkLen; x++) {
					if (this->twine[searchIndex] == c[x]) {
						//cout << this->twine[searchIndex] << " & " << c[x] << " are the same!!" << '\n';
					}
					else {
						//cout << this->twine[searchIndex] << " & " << c[x] << " are NOT the same!!" << '\n';
						break;
					}
					searchIndex++;
				}
				if (searchIndex == i) {
					return true;
				}
			}
		}

	}

	return false;
}

Twine Twine::Capital() {
	if (isalpha(this->twine[0])) {
		this->twine[0] = (char)toupper(this->twine[0]);
	}
	return *this;
}

void Twine::Wobble() {

	size_t l = this->Length();
	char* nt = new char[l + 1];

	for (int i = 0; i < l; i++) {

		if (!isspace(this->twine[i])) {

			srand(((unsigned int)time(NULL)) + (i % 5) - 1);
			if (rand() % 2 == 0) {
				nt[i] = (char)toupper(this->twine[i]);
			}
			else {
				nt[i] = (char)tolower(this->twine[i]);
			}

		}
		else {
			nt[i] = this->twine[i];
		}


	}
	nt[l] = '\0';
	this->SetTwine(nt);
	delete[] nt;


}

void Twine::Insert(const Twine& c, size_t insertIndex) {

	size_t curLen = this->Length();

	if (insertIndex >= curLen || insertIndex < 0) {
		return;
	}
	size_t insInd = insertIndex;
	size_t insStringLen = c.Length();
	size_t newSize = curLen + insStringLen + 1;

	size_t i = 0; //tracker for for loops
	size_t inserti = 0;


	char* newTwine = new char[newSize];

	for (i; i < insInd && i < newSize; i++) {
		newTwine[i] = this->twine[i];
	}
	size_t finalTracker = i;

	for (i;i < insInd + insStringLen && i < newSize;i++) {
		newTwine[i] = c[inserti];
		inserti++;
	}

	for (i;i < newSize; i++) {
		newTwine[i] = this->twine[finalTracker];
		finalTracker++;
	}

	this->SetTwine(newTwine);
	delete[] newTwine;
}

void Twine::Erase(int delInt, size_t startIndex) {

	if (startIndex >= this->Length()) {
		return;
	}

	size_t newsize = this->Length() - delInt + 1;
	char* newTwine = new char[newsize];

	int i = 0; //tracker for for loops

	for (i; i < startIndex && i < newsize;i++) {
		newTwine[i] = this->twine[i];
	}

	for (i;i < newsize;i++) {
		newTwine[i] = this->twine[i + delInt];
	}
	this->SetTwine(newTwine);
	delete[] newTwine;

}

void Twine::Caesar(int displaceVal) {

	Twine cc = this->ToUpper();

	for (int i = 0; i < this->Length(); i++) {
		if (cc.twine[i] >= 'A' && cc.twine[i] <= 'Z') {
			cc.twine[i] = cc.twine[i] + displaceVal % 26;
			if (cc.twine[i] > 'Z' || cc.twine[i] < 'A') {
				cc.twine[i] = cc.twine[i] - 'Z' + 'A' - 1;
			}
		}



	}
	this->SetTwine(cc);

}

Twine& Twine::Colour(int r, int g, int b, bool fg) {

	char buff[64];

	if (fg) {
		sprintf_s(buff, "\x1B[38;2;%d;%d;%dm", r, g, b);
	}
	else {
		sprintf_s(buff, "\x1B[48;2;%d;%d;%dm", r, g, b);
	}


	this->Prepend(buff);
	this->Append("\x1b[0m");
	return *this;
}

