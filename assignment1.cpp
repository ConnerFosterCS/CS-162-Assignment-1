/**********************************************************************
 ** Program: assignment1.cpp (Spellbook Catalog)
 ** Author: Conner Foster
 ** Date: 04/09/2019
 ** Decription: 
 ** Ouput:
 *********************************************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

/*********************************************************************
** Struct: wizards
** Description: This is a struct that stores the wizard personal info and login info.
*********************************************************************/ 
struct wizard {
    string name;
    int id;
    string password;
    string position_title; 
    float beard_length;
};

/*********************************************************************
** Struct: spellbook
** Description: This is a struct that stores the all of the spellbook info except details about the spells.
*********************************************************************/ 
struct spellbook {
    string title;
    string author;
    int num_pages;
    int edition;
    int num_spells;
    float avg_success_rate;
    struct spell *s;
};

/*********************************************************************
** Struct: spellbook
** Description: This is a struct that stores the all of the spell info that is not included in the spellbook struct.
*********************************************************************/ 
struct spell {
    string name;
    float success_rate;
    string effect; 
};

//function prototype for the function "spell *create_spells(int)". The function that cretes and fills the spellbook struct arrays.
spell *create_spells(int);

/*********************************************************************
** Function: error
** Description: This function takes all user input and makes sure that it is a float or an int.
** Parameters: none
** Pre-Conditions: user input = to function.
** Post-Conditions: i/user input or error msg.
*********************************************************************/ 
float error() {
	float i;
	string s;
	bool error;
	do {
		error = false;
		cin >> s;

		for (float i = 0; i < s.size(); i++) {
			if(!(s.at(i) >= '0' && s.at(i) <= '9')) {
				cout << "error: your input must be a whole number or a decimal number." << endl;
                cout << "Enter your input here: ";
				error = true;
                break;
			}
		}
	} while(error);
    
	i = atof(s.c_str());
    return i;
}

/*********************************************************************
** Function: error_one_two
** Description: This function takes all user input and makes sure that it is either a 1 or a 2.
** Parameters: none
** Pre-Conditions: user input = to function.
** Post-Conditions: i/user input or error msg.
*********************************************************************/ 
int error_two() {
    int i;
	string s;
	bool error;
	do {
		error = false;
		cin >> s;
        cout << endl;

		for (int i = 0; i < s.size(); i++) {
			if(!(s.at(i) >= '1' && s.at(i) <= '2')) {
				cout << "error: your input needs to be 1 or 2." << endl;
                cout << "Enter your input here: ";
				error = true;
                break;
			}
		}
	} while(error);
	
	i =atoi(s.c_str());
    return i;
}

/*********************************************************************
** Function: error_one_four
** Description: This function takes all user input and makes sure that it is an input that is 1, 2, 3, or 4.
** Parameters: none
** Pre-Conditions: user input = to function.
** Post-Conditions: i/user input or error msg.
*********************************************************************/ 
int error_four() {
    int i;
	string s;
	bool error;
	do {
		error = false;
		cin >> s;
        cout << endl;

		for (int i = 0; i < s.size(); i++) {
			if(!(s.at(i) >= '1' && s.at(i) <= '4')) {
				cout << "error: your input needs to be 1, 2, 3, or 4." << endl;
                cout << "Enter your input here: ";
				error = true;
                break;
			}
		}
	} while(error);
	
	i =atoi(s.c_str());
    return i;
}

/*********************************************************************
** Function: get_wizard_data
** Description: This function takes the file input from the file wizards.txt and stores the info into a struct array.
** Parameters: size(number of wizards), wizards(wizard struct), ifstream wiz(file input).
** Pre-Conditions: file exists and is opened by ifstream.
** Post-Conditions: wizards[i]
*********************************************************************/ 
void get_wizard_data(int size, wizard *wizards, ifstream &wiz) {
    for (int i = 0; i < size; i++) {
        wiz >> wizards[i].name;
        wiz >> wizards[i].id;
        wiz >> wizards[i].password;
        wiz >> wizards[i].position_title;
        wiz >> wizards[i].beard_length;

        //cout << wizards[i].name << wizards[i].id << wizards[i].password << wizards[i].position_title << wizards[i].beard_length << endl;
    }
}

/*********************************************************************
** Function: get_spellbook_data
** Description: This function takes the file input from the file spellbooks.txt and stores the info into a struct array.
** Parameters: size(number of books), spellbooks(spellbook struct), ifstream spell(file input).
** Pre-Conditions: file exists and is opened by ifstream.
** Post-Conditions: spellbooks[i] and spellbooks[i].s[j]
*********************************************************************/ 
void get_spellbook_data(int size, spellbook *spellbooks, ifstream &spell) {
    for (int i = 0; i < size; i++) {
        spell >> spellbooks[i].title;
        spell >> spellbooks[i].author;
        spell >> spellbooks[i].num_pages;
        spell >> spellbooks[i].edition;
        spell >> spellbooks[i].num_spells;
        
        spellbooks[i].s = create_spells(spellbooks[i].num_spells);
        for (int j = 0; j < spellbooks[i].num_spells; j++) {
            spell >> spellbooks[i].s[j].name;
            spell >> spellbooks[i].s[j].success_rate;
            spell >> spellbooks[i].s[j].effect;
        }    
    }
}

/*********************************************************************
** Function: calc_average
** Description: This function takes the spell succsess rates and calculates an overall average average sucsessrate for the spellbook.
** Parameters: size(number of spellbooks), spellbooks (wizard struct).
** Pre-Conditions: spellbooks[i] struct and spellbook[i].s[j] is filled with correct info.
** Post-Conditions: spellbooks[i].avg_success_rate is filled with correct info.
*********************************************************************/ 
void calc_average(int size, spellbook *spellbooks) {
    for (int i = 0; i < size; i++) {
        spellbooks[i].avg_success_rate = 0;
        for (int j = 0; j < spellbooks[i].num_spells; j++) {
            spellbooks[i].avg_success_rate += spellbooks[i].s[j].success_rate;
        }
        spellbooks[i].avg_success_rate = spellbooks[i].avg_success_rate/spellbooks[i].num_spells;
    }
}

/*********************************************************************
** Function: create_spells
** Description: This function creates the spell struct array.
** Parameters: spells_size
** Pre-Conditions: n/a
** Post-Conditions: spells[spells_size] (struct the size of the number of spells in the book).
*********************************************************************/ 
spell * create_spells(int spells_size) {
    spell* spells = new struct spell[spells_size];
    return spells;
}

/*********************************************************************
** Function: login
** Description: This function takes the wizards struct array and compares the user input info to check login info. After successful user login the function displays that users info.
** Parameters: wizards struct, counter, status.
** Pre-Conditions: wizards struct is filled correctly and main ran correctly.
** Post-Conditions: information is displayed and status string is passed.
*********************************************************************/ 
void login(wizard *wizards, int &counter, string &status) {
    int id;
    string password;
    cout << "Please enter your ID number here: ";
    id = error();
    cout << "Please enter your password here: ";
    cin >> password;
    for (int i = 0; i < 20; i++) {
        if (counter == 2) {
            cout << "\n" << "error: Too many password attempts." << "\n" <<endl;
            exit(0);
        }
        else if (id == wizards[i].id && password == wizards[i].password) {
            cout << "\nWelcome" << wizards[i].name << "\nID: " << wizards[i].id << "\nStatus: " << wizards[i].position_title << "\nBeard Length: " << wizards[i].beard_length << endl;
            status = wizards[i].position_title;
        }
        else if (id != wizards[i].id && password == wizards[i].password) {
            cout << "Incorrect ID or password." << endl;
            counter++;
            login(wizards, counter, status);
        }
        else if (id == wizards[i].id && password != wizards[i].password) {
            cout << "Incorrect ID or password." << endl;
            counter++;
            login(wizards, counter, status);
        }
    }
}

/*********************************************************************
** Function: sort_pages
** Description: This function uses buble sorting to arange the page numbers smallest to pargest
** Parameters: size(number of spellbooks), spellbooks(struct).
** Pre-Conditions: spellbooks struct is filled correctly.
** Post-Conditions: spellbooks[j].num_pages is sorted small to large.
*********************************************************************/ 
void sort_pages(int size, spellbook *spellbooks) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-1; j++) {
            if (spellbooks[j].num_pages > spellbooks[j+1].num_pages) {
                int temp = spellbooks[j].num_pages;
                spellbooks[j].num_pages = spellbooks[j+1].num_pages;
                spellbooks[j+1].num_pages = temp;
            }
        } 
    }
}

/*********************************************************************
** Function: print_pages
** Description: This function prints the sorted number of pages or wirtes the to a files based off of the user input.
** Parameters: size(number of spellbooks), spellbooks(struct).
** Pre-Conditions: spellbooks struct is sorted.
** Post-Conditions: spellbooks[j].num_pages is printed or written to a file.
*********************************************************************/
void print_pages(int size, spellbook *spellbooks) {
    int choice = 0;
    string output_file;
    ofstream outfile;
    cout << "\nHow would you like the information displayed? \n" << "Print to screen (Enter 1) \n" << "Print to file (Enter 2) \n" << "Enter your input here: ";
    choice = error_two();
    if (choice == 1) {
        for (int i = 0; i < size; i++) {
            cout << spellbooks[i].title << " " <<spellbooks[i].num_pages << " pages" <<endl;
        }
    }
    else {
        cout << "Enter the file name: ";
        cin >> output_file;
        outfile.open(output_file.c_str(), ios::out | ios::trunc);
        for (int i = 0; i < size; i++) {
            outfile << spellbooks[i].title << " " <<spellbooks[i].num_pages << " pages" <<endl;
        }  
    }
}

/*********************************************************************
** Function: print_effect
** Description: This function prints the grouped spell effects and prints the spelles based off of the status of the logged in user.
** Parameters: size(number of spellbooks), spellbooks(struct), status(logged in user's status).
** Pre-Conditions: The spellbooks structed is filled and the user is logged in
** Post-Conditions: effects are printed based off of logged in users status.
*********************************************************************/
void print_effect(int size, spellbook *spellbooks, string status) {
    int length = 5;
    if (status == "Student") {
        length = 3;
    }

    string effects[5] = {"bubble", "memory_loss", "fire", "poison", "death"};
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < spellbooks[j].num_spells; k++) {
                if (spellbooks[j].s[k].effect == effects[i]) {
                    cout << spellbooks[j].s[k].effect << ' ' <<spellbooks[j].s[k].name << endl;
                }
            }
        }
    }
}

/*********************************************************************
** Function: write_effect
** Description: This function writes the grouped spell effects into the user inpued file name.
** Parameters: size(number of spellbooks), spellbooks(struct), status(logged in user's status).
** Pre-Conditions: The spellbooks structed is filled and the user is logged in
** Post-Conditions: effects are written in a file based off of logged in users status.
*********************************************************************/
void write_effect(int size, spellbook *spellbooks, string status) {
    string effects[5] = {"bubble", "memory_loss", "fire", "poison", "death"};
    
    int length = 5;
    if (status == "Student") {
        length = 3;
    }
    
    string output_file;
    ofstream outfile;
    cout << "Enter the file name: ";
    cin >> output_file;
    outfile.open(output_file.c_str(), ios::out | ios::trunc);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < spellbooks[j].num_spells; k++) {
                if (spellbooks[j].s[k].effect == effects[i]) {
                    outfile << spellbooks[j].s[k].effect << ' ' <<spellbooks[j].s[k].name << endl;
                }
            }
        }
    }
}

/*********************************************************************
** Function: sort_success
** Description: This function takes the average succsess rate for each book and sorts them smallest to highest success rate.
** Parameters: size(number of spellbooks), spellbooks(struct).
** Pre-Conditions: The spellbooks average success rate is averaged by book.
** Post-Conditions: the avg_success_rate is sorted.
*********************************************************************/
void sort_success(int size, spellbook *spellbooks) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-1; j++) {
            if (spellbooks[j].avg_success_rate > spellbooks[j+1].avg_success_rate) {
                int temp = spellbooks[j].avg_success_rate;
                spellbooks[j].avg_success_rate = spellbooks[j+1].avg_success_rate;
                spellbooks[j+1].avg_success_rate = temp;
            }
        } 
    }
}

/*********************************************************************
** Function: print_success
** Description: This function prints the sorted number of pages or wirtes the to a files based off of the user input.
** Parameters: size(number of spellbooks), spellbooks(struct).
** Pre-Conditions: spellbooks struct is sorted.
** Post-Conditions: spellbooks[j].num_pages is printed or written to a file.
*********************************************************************/
void print_success(int size, spellbook *spellbooks) {
    int choice = 0;
    string output_file;
    ofstream outfile;
    cout << "\nHow would you like the information displayed? \n" << "Print to screen (Enter 1) \n" << "Print to file (Enter 2) \n" << "Enter your input here: ";
    choice = error_two();
    if (choice == 1) {
        for (int i = 0; i < size; i++) {
            cout << spellbooks[i].title << " " <<spellbooks[i].avg_success_rate << " percent" <<endl;
        }
    }
    else {
        cout << "Enter the file name: ";
        cin >> output_file;
        outfile.open(output_file.c_str(), ios::out | ios::trunc);
        for (int i = 0; i < size; i++) {
            outfile << spellbooks[i].title << " " <<spellbooks[i].num_pages << " pages" <<endl;
        }
    }
}

/*********************************************************************
** Function: effect_choice
** Description: This function takes the user input of ther decision to call the functions print_effect and write_effect.
** Parameters: size(number of spellbooks), spellbooks(struct), string status.
** Pre-Conditions: user chooses to sort spell effect.
** Post-Conditions: print_effect or write_effect are called.
*********************************************************************/
void effect_choice (int size, spellbook *spellbooks, string status) {
    int option = 0;
    cout << "\nHow would you like the information displayed? \n" << "Print to screen (Enter 1) \n" << "Print to file (Enter 2) \n" << "Enter your input here: ";
    option = error_two();

    if (option == 1)
        print_effect(size, spellbooks, status);
    else if (option == 2)
        write_effect(size, spellbooks, status);

}

/*********************************************************************
** Function: call_sort
** Description: This function the user input of ther decision to run the correct sorting functions.
** Parameters: size(number of spellbooks), spellbooks(struct), string status.
** Pre-Conditions: main runs the function
** Post-Conditions: correct sorting functions are ran.
*********************************************************************/
void call_sort(int size, spellbook *spellbooks, string status) {
    int option = 0;
    cout << "\nWhich option would you like to choose? \n" << "Sort spellbooks by number of pages (Enter 1): \n" << "Group spells by their effect (Enter 2): \n" << "Sort spellbooks by average success rate (Enter 3): \n" << "Quit (Enter 4): \n" << "Enter your input here: ";
    option = error_four();

    if (option == 1) {
        sort_pages(size, spellbooks);
        print_pages(size, spellbooks);
        call_sort(size, spellbooks, status);
    }
    else if (option == 2) {
        effect_choice(size, spellbooks, status);
        call_sort(size, spellbooks, status);
    }
    else if (option == 3) {
        sort_success(size, spellbooks);
        print_success(size, spellbooks);
        call_sort(size, spellbooks, status);
    }
    else if (option == 4)
        exit(0);
}

/*********************************************************************
** Function: delete_info
** Description: This function deallocates the array mem.
** Parameters: wizards(array), spellbooks(array).
** Pre-Conditions: main runs the function
** Post-Conditions: memory is deallocated.
*********************************************************************/
void delete_info(wizard *wizards, spellbook *spellbooks) {
    delete [] wizards;
    delete [] spellbooks;
}

/*********************************************************************
 * Function: main()
 * Description: This function lets the user inputs the values from the command line arguments and runs the start and end functions.
 * Parameters: every variable
 * Pre-Conditions: n/a
 * Post-Conditions: The program runs.
 ********************************************************************/
int main(int argc, char** argv) {
    int size, counter = 0;
    string status;
    if (argc != 3) {
        cout << "error: Incorrect number of arguments. Please enter three command line arguments." << endl;
        return 0;
    }
    ifstream wiz, spell;
    ofstream outfile;
    wiz.open(argv[1]);
    spell.open(argv[2]);
    if (wiz.is_open() && spell.is_open()) {
        wiz >> size;
        wizard* wizards = new struct wizard[size];
        get_wizard_data(size, wizards, wiz);
        
        spell >> size;
        spellbook* spellbooks = new struct spellbook[size];

        get_spellbook_data(size, spellbooks, spell);
        calc_average(size, spellbooks);

        login(wizards, counter, status);
        call_sort(size, spellbooks, status);
        delete_info(wizards, spellbooks);
    }
    else {
        cout << "Atleast one file did not exist." << endl;
        return 0;
    }
    wiz.close();
    spell.close();
    outfile.close();
}