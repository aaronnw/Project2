
#include <iostream>
using namespace std;
///Sets all characters in a string of a given length to \0
void strEmpty(char* someStr, int length) {
	for (int i = 0; i < length; i++) {
		someStr[i] = '\0';
	}
}

template<class DT>
class arrayClass {
private:
	DT* arrayOfDT;
	int numElements;
	int capacity;
	const int multiplier = 2;
	const int defaultCapacity = 50;
public:
	arrayClass(); //Default constructor
	arrayClass(DT* existingArray); // Initalizer constructor
	arrayClass(int c); //Initializer constructor
	arrayClass(const arrayClass<DT>& ac); // Copy constructor
	~arrayClass(); // Destructor
	void operator= (const arrayClass<DT>& ac); //Overloaded assignment operator
	DT& operator[](int i);
	void add(DT& x);
	void insertAt(int i, DT& x);
	void remove();
	void removeAt(int i);
	void expand();
	int getCapacity();
};
///Class for web address information
class webAddressInfo {
private:
	char url[201]; //allow a maximum of 200 characters
public:
	webAddressInfo();
	webAddressInfo(char* inputString);
	void setWebAddressInfo(char* inputString);
	char* getWebAddressInfo();
	void display();
};

///Class for each browser tab
class browserTab {
protected:
	int numAddress; //Current number of web addresses in this tab
	arrayClass<webAddressInfo> webAddresses; //Web addreses in this tab
	int currentAddress; //index of current location in webAddresses
						// other private methods if necessary for this class
public:
	browserTab();
	browserTab(char* inputString); //creates a new tab with the inputString
	webAddressInfo& forward();
	webAddressInfo& backward();
	void addAddress(char* inputString);
	void display();
	// and other public methods if necessary
};

//////////////////////////////////////////////////////////////////////////// 

///Default constructor
template<class DT>
arrayClass<DT>::arrayClass() {
	numElements = 0;
	capacity = defaultCapacity;
	arrayOfDT = new DT[capacity];
}
///Initializer constructor
template<class DT>
arrayClass<DT>::arrayClass(DT * existingArray) {
	//TODO
}
///Initializer constructor
template<class DT>
arrayClass<DT>::arrayClass(int c) {
	numElements = 0;
	capacity = c;
	arrayOfDT = new DT[capacity];
}
///Copy constructor
template<class DT>
arrayClass<DT>::arrayClass(const arrayClass & ac) {
	numElements = ac.numElements;
	capacity = ac.capacity;
	arrayOfDT = new DT[capacity];
	for (int i = 0; i < capacity; i++) {
		arrayOfDT[i] = ac.arrayOfDT[i];
	}
}
///Destructor
template<class DT>
arrayClass<DT>::~arrayClass() {
}
///Overloaded assignment operator
template<class DT>
void arrayClass<DT>::operator=(const arrayClass & ac) {
	numElements = ac.numElements;
	capacity = ac.capacity;
	arrayOfDT = new DT[capacity];
	for (int i = 0; i < capacity; i++) {
		arrayOfDT[i] = ac.arrayOfDT[i];
	}
}
///Overloaded square bracket operator
template<class DT>
DT & arrayClass<DT>::operator[](int i) {
	//TODO if ((i < 0) || (i >= (capacity - 1))) throw errors;
	return arrayOfDT[i];
}
template<class DT>
void arrayClass<DT>::add(DT & x) {
	//If there is room, add to the end of current array
	if (numElements < capacity) {
		arrayOfDT[numElements] = x;
		numElements++;
	}
	else {
		expand();
		add(x);
	}

}

template<class DT>
void arrayClass<DT>::insertAt(int i, DT & x) {
	if ((numElements < capacity) && (i < capacity)) {
		for (int k = (numElements + 1); k > i; k--) {
			arrayOfDT[k] = arrayOfDT[k - 1];
		}
		arrayOfDT[i] = x;
		numElements++;
	}
	else {
		expand();
		insertAt(i, x);
	}
}

template<class DT>
void arrayClass<DT>::remove() {
	//TODO do iaeven need this
}

template<class DT>
void arrayClass<DT>::removeAt(int i) {
	if (i < capacity) {
		for (i; i < (numElements - 1); i++) {
			arrayOfDT[i] = arrayOfDT[i + 1];
		}
		numElements--;
	}
	//error input
}
template<class DT>
void arrayClass<DT>::expand() {
	//Create a copy of the current array with a larger capacity
	capacity = capacity * multiplier;
	DT* newArray = new DT[capacity];
	for (int i = 0; i < capacity; i++) {
		newArray[i] = arrayOfDT[i];
	}
	delete[] arrayOfDT;
	arrayOfDT = new DT[capacity];
	for (int i = 0; i < capacity; i++) {
		arrayOfDT[i] = newArray[i];
	}
	delete[] newArray;
}
template<class DT>
int arrayClass<DT>::getCapacity() {
	return capacity;
}
///Default constructor
webAddressInfo::webAddressInfo() {
}
///Initializer
webAddressInfo::webAddressInfo(char* inputString) {
	int i = 0;
	strEmpty(url, 201);
	//Make a deep copy from the input string to the url
	while (inputString[i] != '\0') {
		url[i] = inputString[i];
		i++;
	}
}
///Sets the url to a given string
void webAddressInfo::setWebAddressInfo(char * inputString) {
	int i = 0;
	while (inputString[i] != '\0') {
		url[i] = inputString[i];
	}
}
///Returns the character array for the web address
char* webAddressInfo::getWebAddressInfo() {
	return url;
}
///Displays the information for a single web address
void webAddressInfo::display() {
	int i = 0;
	//Print out each valid character in the url
	while (url[i] != '\0') {
		cout << url[i];
		i++;
	}
}
///Default constructor
browserTab::browserTab() {
	numAddress = 0;
}
///Initializer
browserTab::browserTab(char* inputString) {
	numAddress = 1;
	webAddresses[numAddress - 1] = webAddressInfo(inputString);
	currentAddress = numAddress - 1;
}
///Returns the information for an address forward from the current
webAddressInfo& browserTab::forward() {
	//If told to go forward from the last address, just return the current
	if ((currentAddress + 1) < numAddress) {
		return webAddresses[currentAddress + 1];
	}
	else {
		return webAddresses[currentAddress];
	}
}
///Returns the information for an address backward from the current
webAddressInfo& browserTab::backward() {
	//If told to go backward from the first address, just return the current
	if (currentAddress > 0) {
		return webAddresses[currentAddress - 1];
	}
	else {
		return webAddresses[currentAddress];
	}
}
///Adds a new address to a tab
void browserTab::addAddress(char* inputString) {
	numAddress++;
	webAddresses[numAddress - 1] = webAddressInfo(inputString);
	currentAddress = numAddress - 1;
}
///Displays all the addresses contained in a tab
void browserTab::display() {
	for (int i = 0; i < numAddress; i++) {
		webAddresses[i].display();
	}
}
///Main method
int main() {
	arrayClass<browserTab> myTabs;
	int tabNumber = 0;
	int i;
	char webAddress[201];
	char c;
	char blank = ' ';
	char action;
	// while end of file is not reached
	while (!cin.eof()) {
		//Read in the first characters
		cin >> tabNumber;
		cin.get(blank);
		cin.get(action);
		strEmpty(webAddress, 201);
		switch (action) {
			//Create a new address information object with the url and add it to a tab
		case 'N': {
			i = 0;
			do {
				cin.get(c);
				if (c != '\n') {
					webAddress[i++] = c;
				}
			} while ((c != '\n') && (i < 201) && !cin.eof());
			new webAddressInfo(webAddress);
			myTabs[tabNumber].addAddress(webAddress);
			cout << tabNumber << " " << action << " " << webAddress;
			break;
		}
				  //Move to the next address in the tab and display the url
		case 'F': {
			if (!cin.eof()) {
				cout << tabNumber << " " << action << " ";
				myTabs[tabNumber].forward().display();
			}
			break;
		}
				  //Move to the previous address in the tab and display the url
		case 'B': {
			if (!cin.eof()) {
				cout << tabNumber << " " << action << " ";
				myTabs[tabNumber].backward().display();

			}
			break;
		}
				  //Print all the address information in the tab
		case 'P': {
			if (!cin.eof()) {
				cout << tabNumber << " " << action << " ";
				myTabs[tabNumber].display();
			}
			break;
		}

		default: {
		}
		}
		cout << endl;

	}
	return 0;
}
