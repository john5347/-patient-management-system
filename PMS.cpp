#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;
//Structure to represent a patient
struct Patient {
    string id;
    string first_name;
    string last_name;
    string age;
    string gender;
    string condition;
    Patient *next;
};
Patient *head = NULL;
//Structure for Condition of Patients
struct Condition {
	string id;
	string condition;
	string Date;
	Condition *next;
};
Condition *head1 = NULL;
//Function declaration for the function checkForId
string checkForId(string id);
//Function to check the string value does/does'nt contain a letter in it
string checkForDigit(string num){
    bool flag = false;
    for (int i = 0; i < num.length(); i++)
    {
        if (!isdigit(num[i])) {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout<<"\n Enter a number. \"" << num << "\" is not  a number: ";
        cin>>num;
        checkForDigit(num);
    }
    return num;
}
//Function to check the age is between 0-120
string checkForAge(string age){
	age=checkForDigit(age);
	int num = stoi(age);
	if (num < 0 || num > 120){
		cout<<"\n Enter appropirate Age( 0 - 120 ) : ";
		cin>>age;
		checkForAge(age);
	}
    return age;
}
//Function to check the string value does/does'nt contain a number in it
string checkForPureString(string name){
    bool flag = false;
    for (int i = 0; i < name.length(); i++){
        if (isdigit(name[i])) {
            flag = true;
            break;
        }
    }
    if (flag) {
        cout<<"\n Enter an appropriate value. \"" << name << "\" contains a number: ";
        cin>>name;
        checkForPureString(name);
    }
    return name;
}
//Function to check appropirate value to Gender
string checkForGender(string gender) {
    if (gender == "male" || gender == "female" || gender == "Male" || gender == "Female" || gender == "MALE" || gender == "FEMALE" ) {
        return gender;
    } else {
        cout << "\n Enter Male or Female: ";
        cin >> gender;
        return checkForGender(gender);
    }
}
//Function to create condition
Condition *createcondition(string id){
	Condition* newCondition = new Condition;
    newCondition->id = id;
    char date[9];
	newCondition->Date = _strdate(date);
    cin.ignore();
    cout << "\n Enter Condition: ";
    getline(cin, newCondition->condition);
    newCondition->condition = checkForPureString(newCondition->condition);
    newCondition->next = nullptr;
    return newCondition;
}
//Function to add condition
void addCondition(string id){
	 Condition* newCondition = createcondition(id);
    if (head1 == nullptr)
        head1 = newCondition;
    else if (head1->next == nullptr)
        head1->next = newCondition;
    else {
        Condition* temp = head1;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newCondition;
    }      
}
//Function For Search Condition of specific Patient
void searchForPatientCondition(string id) {
    Condition* temp = head1;
    while (temp != NULL) {
        if (temp->id == id)
            cout<<temp->Date<<" "<<temp->condition<<", ";
        temp=temp->next;
    }
}
//Function to create new patient
Patient * createPatient (){
	Patient *patient = new Patient;
	cout<<"\n Enter ID : ";
	cin>>patient->id;
	patient->id=checkForId(patient->id);
	cout<<"\n Enter First Name : ";
	cin>>patient->first_name;
	patient->first_name=checkForPureString(patient->first_name);
	cout<<"\n Enter Last Name : ";
	cin>>patient->last_name;
	patient->last_name=checkForPureString(patient->last_name);
	cout<<"\n Enter Age : ";
	cin>>patient->age;
	patient->age = checkForAge(patient->age);
	cout<<"\n Enter Gender( Male / Female ) : ";
	cin>>patient->gender;
	patient->gender=checkForGender(patient->gender);
	addCondition(patient->id);
    cout<<"\n Successfully patient added to the list.\n";
    	cin.ignore();
	cout<<endl;
	patient->next =NULL;
	return patient;
}
//Function to check the existence  of the ID
string checkForId(string id){
	id=checkForDigit(id);
	if (head == NULL)
        return id;
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
        	cout<<"\n Enter another ID (ID = "<<id<<" )is taken: ";
			cin>>id;
			checkForId(id);
        }
        temp = temp->next;
    }
    return id;
}
//Function to add a node at the Beginning of the list
void addPatientAtBeginning(){
	Patient *newPatient = createPatient();
	if(head == NULL)
		head = newPatient;
	else{
    newPatient->next = head;
    head = newPatient;}
}
//Function to add a node at the end of the list
void addPatientAtEnd(){
	Patient *newPatient = createPatient();
	if(head == NULL)
		head = newPatient;
	else if(head->next == NULL)
		head->next = newPatient;
	else{
		Patient *temp = head;
		while(temp->next != head)
		temp = temp->next;
		temp->next = newPatient;
	}
}
//Function to add a node after a specific node
void addPatientAfter(){
	if(head == NULL)
		cout<<"\n List is empty.\n";
	else{
		string targetID;
    	cout<<"\n Enter the target ID of the patient : ";
    	cin>> targetID;
		Patient *temp = head;
		bool found = false;
		while(temp!= NULL){
			if(temp->id == targetID){
				Patient *temp1 = temp->next;
				Patient	*newPatient = createPatient();
				temp->next = newPatient;
				newPatient->next = temp1;
				found = true;
				break;
			}
		temp = temp->next;
		}
		if (found)
        	cout<<"\n Successfully added the patient after patient ID = "<<targetID<<".\n";
    	else
        	cout<<"\n Patient with the specified ID not found.\n";
	}
}
//Function to add a node before a specific node
void addPatientBefore() {
    if (head == NULL) {
        cout << "\n List is empty.\n";
        return;
    }
    string targetID;
    	cout<<"\n Enter the target ID of the patient : ";
    	cin>>targetID;
    if (head->id == targetID) {
        addPatientAtBeginning();
        return;
    }
    Patient *temp = head;
    bool found = false;
    while (temp->next != NULL) {
        if (temp->next->id == targetID) {
            Patient *newPatient = createPatient();
            newPatient->next = temp->next;
            temp->next = newPatient;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (found)
        cout<<"\n Successfully added the patient before the specified node.\n";
    else
        cout<<"\n Patient with the specified ID not found.\n";
}
//Function to update specific node information
void updatePatient(string id) {
    Patient *temp = head;
    bool found = false;
    while (temp != NULL) {
        if (temp->id == id) {
            cout<<"\n Enter new information for the patient:\n";
            cout<<"\n Enter First Name: ";
            cin>>temp->first_name;
            temp->first_name=checkForPureString(temp->first_name);
            cout<<"\n Enter Last Name: ";
            cin>>temp->last_name;
            temp->last_name=checkForPureString(temp->last_name);
            cout<<"\n Enter Age: ";
            cin>>temp->age;
            temp->age = checkForAge(temp->age);
            cout<<"\n Enter Gender( Male / Female ) : ";
			cin>>temp->gender;
			temp->gender=checkForGender(temp->gender);
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (found)
        cout<<"\n Patient information updated successfully.\n";
    else
        cout<<"\n Patient with the specified ID not found.\n";
}
//Function to delete the first node from the list
void deleteFirstPatient(){
    Patient *temp = head;
    head = head->next;
    delete temp;
    cout<<"\n First patient deleted successfully.\n";
}
// Function to delete the last node from the list
void deleteLastPatient(){
    if (head->next == NULL) {
        delete head;
        head = NULL;
        cout<<"\n Last patient deleted successfully.\n";
        return;
    }
    Patient *temp = head;
    Patient *prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    delete temp;
    cout<<"\n Last patient deleted successfully.\n";
}
//Function to delete any node by searching
void deletePatient(){
    string targetID;
    cout<<"\n Enter the ID of the patient to delete: ";
    cin>>targetID;
    Patient *temp = head;
    Patient *prev = NULL;
    bool found = false;
    while (temp != NULL) {
        if (temp->id == targetID) {
            found = true;
            break;
    	}
        prev = temp;
        temp = temp->next;
    }

    if (found) {
        if (prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        cout<<"\n Patient with ID "<<targetID<<" deleted successfully.\n";
    } else {
        cout<<"\n Patient with ID "<< targetID<<" not found.\n";
    }
}
//************Displaying Function**************//
void displayList(){
	 Patient *temp = head;
	if (temp == NULL){
        cout<<"\n List is empty. No patients to display.\n" << endl;
        return;
    }
    cout<<"\t Patient List:\n" << endl;
    cout<<"  ID  | First Name | Last Name  | Age | Gender |           Condition"<< endl;
    cout<<"----------------------------------------------------------------------------"<< endl;
    while (temp != NULL) {
        cout<<setw(4)<<temp->id<<"  | "<<setw(10)<<temp->first_name<<" | "<<setw(10)<<temp->last_name <<" | "<<setw(3)<<temp->age <<" | "<<setw(6)<<temp->gender<<" | ";
		searchForPatientCondition(temp->id);
		cout<<endl;
        temp = temp->next;
    }
    cout<<"----------------------------------------------------------------------------\n"<<endl;
}
//Function to swap the data of two patient
void swapPatients(Patient* a, Patient* b) {
    string tempId = a->id;
    string tempFirstName = a->first_name;
    string tempLastName = a->last_name;
    string tempAge = a->age;
    string tempgender = a->gender;

    a->id = b->id;
    a->first_name = b->first_name;
    a->last_name = b->last_name;
    a->age = b->age;
    a->gender = b->gender;

    b->id = tempId;
    b->first_name = tempFirstName;
    b->last_name = tempLastName;
    b->age = tempAge;
    b->gender=tempgender;
}
//Function to sort the patient list by ID in ascending order
void sortById() {
    bool swapped;
    Patient* temp;
    do {
        swapped = false;
        temp = head;
        while (temp->next != NULL) {
        	int num1 = stoi(temp->id);
        	int num2 = stoi(temp->next->id);
            if (num1 > num2) {
                swapPatients(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    cout<<"\nPatient list sorted by ID in ascending order.\n";
}
//Function to sort the patient list by first name in ascending order
void sortByFirstName() {
    bool swapped;
    Patient* temp;
    do {
        swapped = false;
        temp = head;
        while (temp->next != NULL) {
            if (temp->first_name > temp->next->first_name) {
                swapPatients(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    cout<<"\nPatient list sorted by first name in alphabetical order.\n";
}
//Function to sort the patient list by last name in ascending order
void sortByLastName() {
    bool swapped;
    Patient* temp;
    do {
        swapped = false;
        temp = head;
        while (temp->next != NULL) {
            if (temp->last_name > temp->next->last_name) {
                swapPatients(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    cout<<"\nPatient list sorted by last name in alphabetical order.\n";
}
//Function to search for a patient by ID
void searchById() {
    if (head == NULL) {
        cout<<" List is empty. No patients to search." << endl;
        return;
    }
    string targetId;
    cout<<" Enter the ID of the patient you want to search for: ";
    cin>> targetId;
    targetId = checkForDigit(targetId);
    
    Patient* temp = head;
    bool found = false;
    
    while (temp != NULL) {
        if (temp->id == targetId) {
            cout<<"\n\tPatient found!" << endl;
            cout<<"  ID  | First Name | Last Name  | Age | Gender |           Condition"<< endl;
   			cout<<"----------------------------------------------------------------------------"<< endl;
       		cout<<setw(4)<<temp->id<<"  | "<<setw(10)<<temp->first_name<<" | "<<setw(10)<<temp->last_name <<" | "<<setw(3)<<temp->age <<" | "<<setw(6)<<temp->gender<<" | "<<temp->condition<<endl;
   			 cout<<"----------------------------------------------------------------------------"<<endl;
            found=true;
            break;
        }
        temp=temp->next;
    }
    
    if (!found) {
        cout<<"Patient with ID " <<targetId<<" not found in the list."<<endl;
    }
}
//Function to search for list items by first name
void searchByFirstName() {
    if (head == NULL) {
        cout<<"\nList is empty. No patients to search.\n";
        return;
    }
    string targetFirstName;
    cout<<"\nEnter the first name to search for: ";
    cin>>targetFirstName;
    targetFirstName = checkForPureString(targetFirstName);
    Patient* temp = head;
    bool found = false,flag = true;

    while (temp != NULL) {
        if (temp->first_name == targetFirstName) {
        	if(flag){
            cout<< "\n\t Patient found:\n";
            cout<< "--------------------------------------------------------------------------------------" << endl;}
        	cout<< "ID: " << temp->id << ", First Name: " << temp->first_name <<",  Last Name: " << temp->last_name << ", Age: " << temp->age << ", Condition: " << temp->condition << endl;
   			 cout<< "---------------------------------------------------------------------------------------" << endl;
            found = true;
            flag = false;
        }
        temp = temp->next;
    }

    if (!found) {
        cout<<"\nNo patients found with the specified first name.\n";
    }
}
//Function to search for list items by last name
void searchByLastName() {
    if (head == NULL) {
        cout<<"\nList is empty. No patients to search.\n";
        return;
    }

    string targetLastName;
    cout<<"\nEnter the last name to search for: ";
    cin>>targetLastName;
    targetLastName = checkForPureString(targetLastName);

    Patient* temp = head;
    bool found = false,flag = true;

    while (temp != NULL) {
        if (temp->last_name == targetLastName) {
            if(flag){
            cout<< "\n\t Patient found:\n";
            cout<< "--------------------------------------------------------------------------------------" << endl;}
        	cout<< "ID: " << temp->id << ", First Name: " << temp->first_name <<",  Last Name: " << temp->last_name << ", Age: " << temp->age << ", Condition: " << temp->condition << endl;
   			 cout<< "---------------------------------------------------------------------------------------" << endl;
            found = true;
            flag = false;
        }
        temp = temp->next;
    }

    if (!found) {
        cout<<"\nNo patients found with the specified last name.\n";
    }
}
//Function that Display options
void showMenu(){
		cout<<"*************MENU*************\n";
        cout<< "\t1. Add" << endl;
        cout<< "\t2. Edit" << endl;
        cout<< "\t3. Delete" << endl;
        cout<< "\t4. Sort"<<endl;
        cout<< "\t5. Search"<<endl;
        cout<< "\t6. Display all" << endl;
        cout<< "\t0. Exit" << endl;
        cout<<"******************************\n";
}
int main(){
	int repeat = 0, choice= 0,choice1;
	while(repeat==0){
		showMenu();
        cout<< "Enter your choice: ";
        cin>> choice;
        system("Cls");
        switch (choice) {
        	case 1: 
        	cout<<"\t1. Add a node at the Beginning of the list" << endl;
        	if(head != NULL){
        	cout<<"\t2. Add a node at the end of the list " << endl;
        	cout<<"\t3. Add a node after a specific Patient" << endl;
        	cout<<"\t4. Add a node before a specific Patient" << endl;
			}
        	cout<<"Enter your choice: ";
  				cin >> choice1;
  				system("Cls");
  				if(head == NULL){
  					switch (choice1) {
        				case 1: 
							addPatientAtBeginning();
							break;
						default:
							cout<<"\n\tInvalid choice\n";
				  			}
				  }
  				else{		    				  				
  				 switch (choice1) {
        			case 1: 
						addPatientAtBeginning();
						break;
					case 2:
						addPatientAtEnd();
						break;
					case 3:
						addPatientAfter();
						break;
					case 4:
						addPatientBefore();
						break;
					default:
						cout<<"\n\tInvalid choice\n";
						}
				}
    			break;
    		case 2:
    			if(head==NULL){
					cout<<"\tList is empty\n";
					break;
				}
				else{
					cout<<"\n Enter ID of the patient to update: ";
					string id;
   					cin>>id;
					cout<<"\n\t1. Edit Personal Information " << endl;
					cout<<"\n\t2. Add condition\n" << endl;
					cout<< "Enter your choice: ";
					cin >> choice1;
  					system("Cls");
  				 switch (choice1) {
        			case 1: 
						updatePatient(id);
						break;
					case 2:
						addCondition(id);
						break;
					default:
						cout<<"Invalid choice";
						}
				}
    			break;
			case 3:
				if(head==NULL){
					cout<<"\tList is empty\n";
					break;
				}
				else{
				cout<< "\t1. Delete the first Patient" << endl;
			   	cout<< "\t2. Delete the last Patient" << endl;
       			 cout<< "\t3. Delete specific Patient" << endl;
				cout<< "Enter your choice: ";
  				cin>> choice1;
  				system("Cls");
  				 switch (choice1) {
        			case 1: 
						deleteFirstPatient();
						break;
					case 2:
						deleteLastPatient();
						break;
					case 3:
						deletePatient();
						break;
					default:
						cout<<"Invalid choice\n";
						}
				break;}
			case 4:
			if (head == NULL) {
  			cout<<"\tList is empty\n";
  			 break;
				}
			else if(head->next == NULL) {
    			cout << "\n\tThe list only contains one patient, no need to be sorted.\n\n";
    			break;
				}
				else{
				cout<< "\t1. Sort by ID" << endl;
  				cout<< "\t2. Sort by First Name" << endl;
 				cout<< "\t3. Sort by Last Name" << endl;
  			  	cout<< "Enter your choice: ";
  				cin>> choice1;
  				system("Cls");
  				 switch (choice1) {
        			case 1: 
						sortById();
						break;
					case 2:
						sortByFirstName();
						break;
					case 3:
						sortByLastName();
						break;
					default:
						cout<<"Invalid choice";
						}
    			break;}
    		case 5:
    			if(head==NULL){
					cout<<"\tList is empty\n";
					break;
				}
				else{
				cout<< "\t1. Search by ID" << endl;
  				cout<< "\t2. Search by First Name" << endl;
 				cout<< "\t3. Search by Last Name" << endl;
  			  	cout<< "Enter your choice: ";
  				cin>> choice1;
  				system("Cls");
  				 switch (choice1) {
        			case 1: 
						searchById();
						break;
					case 2:
						searchByFirstName();
						break;
					case 3:
						searchByLastName();
						break;
					default:
						cout<<"Invalid choice";
						}
    			break;}
			case 6:
				displayList();
				break;
			case 0:
				cout<<"Thank you for using our system."<< endl;
				cout<<"\t Done By:\n" << endl;
   				cout<<"  NO  |      Name        |  ID  "<< endl;
    			cout<<"-------------------------------------"<< endl;
        		cout<<setw(4)<<"1."<<"  | "<<setw(15)<<"Hilina Seyfu"<<" | "<<setw(10)<<"BDU1405578\n";
        		cout<<setw(4)<<"2."<<"  | "<<setw(15)<<"Hizikyas Tamiru"<<" | "<<setw(10)<<"BDU1404545\n";
        		cout<<setw(4)<<"3."<<"  | "<<setw(15)<<"Ezedin Ahmed "<<" | "<<setw(10)<<"BDU1403734\n";
        		cout<<setw(4)<<"4."<<"  | "<<setw(15)<<"Biruk Nesibu "<<" | "<<setw(10)<<"BDU1404085\n";
        		cout<<setw(4)<<"5."<<"  | "<<setw(15)<<"Yohanees Sori"<<" | "<<setw(10)<<"BDU1405412\n";
        		cout<<setw(4)<<"6."<<"  | "<<setw(15)<<"Henok Eshetu "<<" | "<<setw(10)<<"BDU1404546\n";
        		cout<<setw(4)<<"7."<<"  | "<<setw(15)<<"Hewan Solomon"<<" | "<<setw(10)<<"BDU14005255\n";
   				cout<<"------------------------------------"<<endl;
				repeat=1;
				break;
		}
	}
}
//Developed on Dev-C++ 6.3
