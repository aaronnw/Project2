#include <iostream>
using namespace std;
class WrongTabError {};
class WrongActionError {};

template<class DT>
class arrayClass {
	template<class T>
	friend ostream& operator<< (ostream& s, arrayClass<T>& ac); //Overloaded ostream operator
private:
	DT* arrayOfDT;
	int numElements;
	int capacity;
	const int multiplier = 2;
	const int defaultCapacity = 50;
public:
	arrayClass(); //Default constructor
	arrayClass(int c); //Initializer constructor
	arrayClass(const arrayClass<DT>& ac); // Copy constructor
	~arrayClass(); // Destructor
	void operator= (const arrayClass<DT>& ac); //Overloaded assignment operator
	DT& operator[](int i);
	void add(DT& x);
	void insertAt(int i, DT& x);
	void removeAt(int i);
	void expand();
	void empty();
	int getCapacity();
	int getSize();
};
///Class for web address information
class webAddressInfo {
	friend ostream& operator<< (ostream& s, webAddressInfo& info); //Overloaded ostream operator
private:
	arrayClass<char> url; //allow a a dynamic amount of characters
public:
	webAddressInfo(); //Default constructor
	webAddressInfo(arrayClass<char> inputString); //Initalizer constructor
	webAddressInfo(webAddressInfo& info); // Copy constructor
	~webAddressInfo(); // Destructor
	void operator= (const webAddressInfo& info); //Overloaded assignment operator
	void setWebAddressInfo(arrayClass<char> inputString); 
	arrayClass<char> getWebAddressInfo();
	void display();
};

///Class for each browser tab
class browserTab {
	friend ostream& operator<< (ostream& s, browserTab& tab); //Overloaded ostream operator
protected:
	int numAddress; //Current number of web addresses in this tab
	arrayClass<webAddressInfo> webAddresses; //Web addreses in this tab
	int currentAddress; //index of current location in webAddresses
public:
	browserTab();  //Default constructor
	browserTab(arrayClass<char> inputString); //Initalizer constructor
	browserTab(browserTab& tab); // Copy constructor
	~browserTab(); // Destructor
	void operator= (const browserTab& tab); //Overloaded assignment operator
	webAddressInfo& forward();
	webAddressInfo& backward();
	webAddressInfo& getCurrentAddress();
	void changeCurrentAddress(arrayClass<char> inputString);
	void addAddress(arrayClass<char> inputString);
	void display();
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
arrayClass<DT>::arrayClass(int c) {
	numElements = 0;
	capacity = c;
	arrayOfDT = new DT[capacity];
}
///Copy constructor
template<class DT>
arrayClass<DT>::arrayClass(const arrayClass<DT>& ac) {
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
	delete[] arrayOfDT;
}
///Overloaded assignment operator
template<class DT>
void arrayClass<DT>::operator= (const arrayClass<DT>& ac) {
	arrayOfDT = new DT[ac.capacity];
	for (int i = 0; i < ac.capacity; i++) {
		arrayOfDT[i] = ac.arrayOfDT[i];
	}
	numElements = ac.numElements;
	capacity = ac.capacity;
}
///Overloaded square bracket operator
template<class DT>
DT & arrayClass<DT>::operator[](int i) {
	//TODO if ((i < 0) || (i >= (capacity - 1))) throw errors;
	return arrayOfDT[i];
}
///Add an element to the end of the array
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
///Insert an element into the array
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
///Remove an element from a given index
template<class DT>
void arrayClass<DT>::removeAt(int i) {
	for (i; i < (numElements); i++) {
		arrayOfDT[i] = arrayOfDT[i + 1];
	}
	numElements--;
	//error input
}
///Increase the size of the array
template<class DT>
void arrayClass<DT>::expand() {
/*	//Create a copy of the current array with a larger capacity
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
		*///Create a copy of the current array with a larger capacity
	
	DT* newArray = new DT[capacity * multiplier];
	for (int i = 0; i < capacity; i++) {
		newArray[i] = arrayOfDT[i];
	}
//	for (int i = capacity; i < capacity * multiplier; ++i) 		
//	{
//		newArray[i] = 0;
//	}
	delete[] arrayOfDT;
	arrayOfDT = newArray;// new DT[capacity];
	
	capacity = capacity * multiplier;

}
///Show the array as empty
template<class DT>
void arrayClass<DT>::empty() {
	numElements = 0;
}
///Return the capacity
template<class DT>
int arrayClass<DT>::getCapacity() {
	return capacity;
}
///Return the number of elements
template<class DT>
int arrayClass<DT>::getSize() {
	return numElements;
}
///Overloaded ostream operator
template<class DT>
ostream& operator<< (ostream& s, arrayClass<DT>& ac) {
	for (int i = 0; i < ac.getSize(); i++) {
		s << ac[i];
	}
	return s;

}

//////////////////////////////////////////////////////////////////////////// 

///Default constructor
webAddressInfo::webAddressInfo() {
}
///Initializer constructor
webAddressInfo::webAddressInfo(arrayClass<char> inputString) {
	int i = 0;
	url.empty();
	//Make a deep copy from the input string to the url
	//while (inputString[i] != '\0') {
	//	url[i] = inputString[i];
	//	i++;
	//}
	url = inputString;
}
///Copy constructor
webAddressInfo::webAddressInfo(webAddressInfo & info) {
	url = info.url;
}
///Destructor
webAddressInfo::~webAddressInfo() {
}
///Overloaded assignment operator
void webAddressInfo::operator=(const webAddressInfo & info) {
	url = info.url;
}
///Sets the url to a given string
void webAddressInfo::setWebAddressInfo(arrayClass<char> inputString) {
	int i = 0;
	//while (inputString[i] != '\0') {
	//	url[i] = inputString[i];
	//}
	//for (int i = 0; i < inputString.getSize(); ++i) 		{
	//	url[i] = inputString[i];
	//}
	url = inputString;
}
///Returns the character array for the web address
arrayClass<char> webAddressInfo::getWebAddressInfo() {
	return url;
}
///Displays the information for a single web address
void webAddressInfo::display() {
	int i = 0;
	//Print out each valid character in the url
	//while (url[i] != '\0') {
	//	cout << url[i];
	//	i++;
	//}
	for (int i = 0; i < url.getSize(); ++i)
		cout << url[i];
}
///Overloaded ostream operator
ostream& operator<< (ostream& s, webAddressInfo& info) {
	//TODO
	return s;

}

//////////////////////////////////////////////////////////////////////////// 

///Default constructor
browserTab::browserTab() {
	numAddress = 0;
}
///Initializer constructor
browserTab::browserTab(arrayClass<char> inputString) {
	numAddress = 1;
	webAddresses[numAddress - 1] = webAddressInfo(inputString);
	currentAddress = numAddress - 1;
}
///Copy constructor
browserTab::browserTab(browserTab & tab) {
}
///Destructor
browserTab::~browserTab() {
}
///Overloaded assignment operator
void browserTab::operator=(const browserTab & tab) {
	numAddress = tab.numAddress;
	currentAddress = tab.currentAddress;
	webAddresses = tab.webAddresses;
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
///Returns the information at the current address
webAddressInfo & browserTab::getCurrentAddress() {
	return webAddresses[currentAddress];
}
///Changes the current address of the tab
void browserTab::changeCurrentAddress(arrayClass<char> inputString) {
	webAddresses[currentAddress].setWebAddressInfo(inputString);
}
///Adds a new address to a tab
void browserTab::addAddress(arrayClass<char> inputString) {
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
///Overloaded ostream operator
ostream& operator<< (ostream& s, browserTab& tab) {
	//TODO
	return s;

}
//////////////////////////////////////////////////////////////////////////// 

///Main method
int main() {
	arrayClass<browserTab> myTabs;
	int tabNumber = 0;
	int targetTabNumber;
	int i;
	arrayClass<char> webAddress;
	char c;
	char blank = ' ';
	char action;
	// while end of file is not reached
	while (!cin.eof()) {
		try {
			//Read in the first characters
			cin >> tabNumber;
			cin.get(blank);
			cin.get(action);
			//If a new action is not read
			if (action == 'q')
				break;
			webAddress.empty();
			switch (action) {
				//Create a new address information object with the url and add it to a tab
			case 'N': {
				i = 0;
				do {
					cin.get(c);
					if (c != '\n') {
						webAddress.add(c);// [i++] = c;
					}
				} while ((c != '\n') && !cin.eof());
				webAddressInfo webAddressInfo(webAddress);
				browserTab newTab;
				newTab.addAddress(webAddress);
				if (tabNumber > myTabs.getSize()) {
					myTabs.add(newTab);
				}else
					myTabs[tabNumber-1].addAddress(webAddress);
				cout << tabNumber << " " << action << " " << webAddress;
				break;
			}
					  //Move to the next address in the tab and display the url
			case 'F': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				if (!cin.eof()) {
					cout << tabNumber << " " << action << " ";
					myTabs[tabNumber-1].forward().display();
				}
				break;
			}
					  //Move to the previous address in the tab and display the url
			case 'B': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				if (!cin.eof()) {
					cout << tabNumber << " " << action << " ";
					myTabs[tabNumber-1].backward().display();
				}
				break;
			}
					  //Print all the address information in the tab
			case 'P': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				if (!cin.eof()) {
					cout << tabNumber << " " << action << " ";
					myTabs[tabNumber-1].display();
				}
				break;
			}
					  //Move the information from the first listed tab to the second
			case 'M': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				cin.get(blank);
				cin >> targetTabNumber;
				cout << tabNumber << " " << action<< " " << targetTabNumber << "  Move tab " << tabNumber << " to " << targetTabNumber;
				if (tabNumber > targetTabNumber) {
					myTabs.insertAt(targetTabNumber - 1, myTabs[tabNumber]);
					myTabs.removeAt(myTabs.getSize() - 1);
				}
				else if(tabNumber < targetTabNumber){
					myTabs.insertAt(targetTabNumber, myTabs[tabNumber - 1]);
					myTabs.removeAt(tabNumber - 1);
				}
				break;
			}
					  //Remove a tab completely
			case 'R': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				cin.get(c);
				while ((c != '\n') && !cin.eof()){
					cin.get(c);
				}
				cout << tabNumber << " " << action << " " << " Removed tab " << tabNumber;
				myTabs.removeAt(tabNumber);
				break;
			}
					//Change the address of a tab
			case 'C': {
				if (tabNumber > myTabs.getSize()) {
					throw WrongTabError();
				}
				i = 0;
				do {
					cin.get(c);
					if (c != '\n') {
						webAddress.add(c);// [i++] = c;
					}
				} while ((c != '\n') && !cin.eof());
				myTabs[tabNumber-1].changeCurrentAddress(webAddress);
				cout << tabNumber << " " << action << " " << webAddress;
				break;
			}

			default: {
				throw WrongActionError();
			}
			}
			cout << endl;
		}
		///Handle errors if an incorrect tab or action is entered
		catch (WrongActionError) {
			cout << "Wrong action" << endl;
			cin.get(c);
			while ((c != '\n')&& !cin.eof()) {
				cin.get(c);
			}
		}
		catch (WrongTabError) {
			cout << "Wrong tab" << endl;
			cin.get(c);
			while ((c != '\n') && !cin.eof()) {
				cin.get(c);
			}

		}
		action = 'q';
	}
	return 0;
}