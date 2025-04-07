#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <random>
using namespace std;

//Forward declarations of existing species
class bear;
class hyena;
class lion;
class tiger;

//global map to store animal counts
//stores {{"hyena",0},{"lion",0},{"bear",0},{"tiger",0}}
map<string, int> Animals;

class Animal {
public:
    map<string, string>Animal_profile;

    Animal(const string &age, const string &Season_born, const string &color, const string &sex, const string &species, const string &weight, const string &origin) {
        Animal_profile["age"] = age;
        Animal_profile["season"] = Season_born;
        Animal_profile["color"] = color;
        Animal_profile["sex"] = sex;
        Animal_profile["species"] = species;
        Animal_profile["weight"] = weight;
        Animal_profile["origin"] = origin;
        updateAnimalCount();
        genUniqueID();
    }
    void updateAnimalCount(){
        Animals[Animal_profile["species"]]++;
    }
    void genUniqueID() {
        if (Animals[Animal_profile["species"]] <= 9)
            Animal_profile["ID"] =string(1, toupper(Animal_profile["species"][0])) + string(1, Animal_profile["species"][1]) + "0" + to_string(Animals[Animal_profile["species"]]);
        else
            Animal_profile["ID"] =string(1, toupper(Animal_profile["species"][0])) + string(1, Animal_profile["species"][1]) + to_string(Animals[Animal_profile["species"]]);
    }
};

//Didn't find a workaround to create derived classes manually,
//in fact didn't find time to do anything extra, unfortunately.
class bear: public Animal {
    public:
        using Animal::Animal;
    void roar() {
        cout << "A" << Animal_profile["color"] << Animal_profile["species"] << "lumbers into the Bear Habitat!";
        cout << "The bear lets out a Loud, deep, grunt.";
    }
};

class hyena: public Animal {
    public:
        using Animal::Animal;
    void roar() {
        cout << "A" << Animal_profile["color"] << Animal_profile["species"] << "scampers into the Hyena Habitat!";
        cout << "You hear a hyena";
    }
};

class lion: public Animal {
    public:
        using Animal::Animal;
};

class tiger: public Animal {
    public:
        using Animal::Animal;
};

//Function prototypes
void file_reading_func();
string name_parsing_func(string);
string genBirthDay(string, string);
void file_output_func();
void closed_for_cleaning();

/*Global Zoo of Habitats*/
map<string, map<string, Animal*>> Zoo;

int main() {

    //The Goal of the reading function is the following:
    //Read arrivingAnimals.txt line by line, Create a new Animal object,
    //then store the object in either a new or existing habitat by species in the Zoo...
    //Then update Map of Animal counts
    cout << "It's Fresno City College's Exotic Animal Zoo opening day and you are the new Intern!!\n";
    cout << "Thanks so much for volunteering to help track the Animals arrival!\n";
    cout << "We have a record of Arriving Animals to the Zoo...however we need your help!\n";
    cout << "The animals need to be recorded into our database, given a name, and assigned an ID number\n";
    cout << "Fortunately we had one of our students design this program to do just that!\n";
    cout << "All you have to do is insert this file arrivingAnimals.txt....\n";
    file_reading_func();
    cout << "File Reading function Done\n";
    file_output_func();
    cout << "File Finished running!\n";
    //The Goal of the output function is the following:
    //Use Map of Animal Counts and Zoo Map
    //Use Animal count to print number of animals in each habitat
    //Use Zoo Map to print each Animal in each corresponding habitat as well as relevant data
    cout << "EXCELLENT great job now all our animals are registered...\n";
    cout << "That's odd...the list is organized alphabetically by name and not ID?...\n";
    cout << "Well what can you expect from unpaid student labor... oh well!\n";
    //Don't forget to clean house!
    closed_for_cleaning();
    cout << "Program completed!\n";
    cout << "\nThis is CIT66 Zoo!!!\n";
    return 0;
}

void file_reading_func() {
    //TODO
    fstream myFile;
    //Below opens a file to READ from it
    myFile.open("C:/Users/eckst/Desktop/arrivingAnimals.txt", ios::in);//read mode

    //need to check if the file opened successfully
    if (myFile.is_open()) {
        string line_of_txt;
        string no_punct;
        vector<string> parse_by_comma;
        //getline(A,B) reads a line of data from A and stores it in variable B
    cout << "File opened successfully\n";
        //For every line in file
        while (getline(myFile,line_of_txt)) {
            parse_by_comma.clear();
            cout << line_of_txt << '\n';
            stringstream line(line_of_txt);

            //for this line
            while (getline(line, no_punct, ',')) {

                //for every comma section, if there is a space at start, erase
                if (no_punct[0] == ' ') {
                    no_punct.erase(0, 1);
                }

                //add section to vector without space at start
                parse_by_comma.push_back(no_punct);
            }

            //declare variables with known indexes for line
            string Animal_Age = parse_by_comma[0].substr(0,parse_by_comma[0].find(' '));
            string Season_born;
            string color = parse_by_comma[2];
            string weight = parse_by_comma[3];
            string origin = parse_by_comma[4] + ", " + parse_by_comma[5];
            string sex;
            string species;

            //for each comma separated section
            for (string i : parse_by_comma) {
                stringstream ss(i);
                string word;
                while (ss >> word) {
                    if (word == "spring" || word == "summer" || word == "fall" || word == "winter") {
                        Season_born = word;
                    }
                    if ( word == "season") {
                        Season_born = "unknown";
                    }
                    if (word == "lion" || word == "hyena" || word == "tiger" || word == "bear") {
                        species = word;
                    }
                    if (word == "male" || word == "female") {
                        sex = word;
                    }
                }
            }
            cout << "text line parsed\n";
            //create and initialize Animal class object, need to adjust this so animal class is called instead
            string New_name = name_parsing_func(species);
            cout << "Name parsing completed\n";
            cout << New_name << "\n";
            if (species == "bear") {
                bear* AnimalObj = new bear(Animal_Age, Season_born, color, sex, species, weight, origin);
                Zoo["Bear Habitat"][New_name] = AnimalObj;
            }
            else if (species == "hyena") {
                hyena* AnimalObj = new hyena(Animal_Age, Season_born, color, sex, species, weight, origin);
                Zoo["Hyena Habitat"][New_name] = AnimalObj;
            }
            else if (species == "lion") {
                lion* AnimalObj = new lion(Animal_Age, Season_born, color, sex, species, weight, origin);
                Zoo["Lion Habitat"][New_name] = AnimalObj;
            }
            else if (species == "tiger") {
                tiger* AnimalObj = new tiger(Animal_Age, Season_born, color, sex, species, weight, origin);
                Zoo["Tiger Habitat"][New_name] = AnimalObj;
            }
            cout << "Animal placed in habitat\n";
        }
        //Don't forget to close the file you opened when finished.
        myFile.close();
        cout << "File closed\n";
    }
}

string name_parsing_func(string Animal_species) {
    string which_species = Animal_species;
    //Capitalize first letter to find line match
    Animal_species[0]= toupper(Animal_species[0]);
    string species = Animal_species + " Names:";

    fstream Name_File;
    Name_File.open("C:/Users/eckst/Desktop/animalNames.txt", ios::in);

    if (Name_File.is_open()) {
        string line_of_names;

        while (getline(Name_File, line_of_names)) {

            line_of_names.erase(0, line_of_names.find_first_not_of(" \t\n\r"));
            line_of_names.erase(line_of_names.find_last_not_of(" \t\n\r") + 1);

            if (line_of_names == species) {

                while (getline(Name_File, line_of_names)) {

                    if (line_of_names.empty()) {
                        continue;
                    }

                    stringstream names(line_of_names);
                    string word;

                    while (getline(names, word, ',')) {
                        word.erase(0, word.find_first_not_of(" \t\n\r") );
                        word.erase(word.find_last_not_of(" \t\n\r") + 1);

                        if (which_species == "bear") {
                            if (Zoo["Bear Habitat"].find(word) == Zoo["Bear Habitat"].end()) {
                                return word;
                            }
                        }
                        else if (which_species == "hyena") {
                            if (Zoo["Hyena Habitat"].find(word) == Zoo["Hyena Habitat"].end()) {
                                return word;
                            }
                        }
                        else if (which_species == "lion") {
                            if (Zoo["Lion Habitat"].find(word) == Zoo["Lion Habitat"].end()) {
                                return word;
                            }
                        }
                        else if (which_species == "tiger") {
                            if (Zoo["Tiger Habitat"].find(word) == Zoo["Tiger Habitat"].end()) {
                                return word;
                            }
                        }
                    }
                }
            }
        }
        Name_File.close();
    }
    return "name_not_found";
}


void file_output_func() {
    //TODO
    //This function at some point will need to take into account the age of the animal
    //Once the age is accounted for and the season the animal was born in
    //Arrival will be todays date and birth date will be a random month from the season and age - 2025
    map<string, string> Season_months = {{"winter", "Dec"}, {"spring", "Mar"}, {"summer", "Jun"}, {"fall", "Sept"}};
    fstream myFile;

    //Below opens a file to APPEND to it
    myFile.open("C:/Users/eckst/Desktop/zooPopulation.txt", ios::app);//Appends to the end of existing file content)

    //need to check if the file opened successfully
    if (myFile.is_open()) {
        //This loops through the Animal MAP
        //It prints Animal type and #
        myFile << "Zoo Population Report April 6, 2025\n" << "\n";

        for (const auto&[fst, snd] : Animals) {
            string species = fst;
            species[0] = toupper(species[0]);
            string habitat_string  = species + " Habitat";
            cout << "Checking Zoo for Habitat\n";
            const map<string, Animal*> Habitat = Zoo.at(habitat_string);
            cout << "Habitat found\n";
            myFile << "\n";
            myFile << habitat_string << ":" << "\n";
            myFile << "\n";
            myFile << "Number of " << species << "'s: "<< snd << "\n";
            myFile << "\n";
            for (const auto&[name, Animal]: Habitat) {
                //This will eventually call each "species_habitat" loops through each object.
                //Each object's contents will print to file newAnimals.txt
                cout << "animal being parsed for print\n";
                int age = stoi(Animal->Animal_profile["age"]);
                int birthdate = 2025 - age;
                cout << "Pulling Animal_profile[season]\n";
                cout << Animal->Animal_profile["season"] << "\n";
                cout << "Season pulled successfully\n";
                string birth_month;
                if (Season_months.find(Animal->Animal_profile["season"]) != Season_months.end()) {
                    birth_month = Season_months.at(Animal->Animal_profile["season"]);
                }
                else {
                    birth_month = "Jan";
                }
                cout << "birth month assigned\n";
                //generate a random day of the month!
                random_device randomday;
                mt19937 gen(randomday());
                uniform_int_distribution<> dist(1, 28);
                int random_day = dist(gen);
                //generates a random day of the month!
                myFile << Animal->Animal_profile["ID"]<< "; " << name << "; " << Animal->Animal_profile["age"] << " years old; " << "birth date "<< genBirthDay(Animal->Animal_profile["age"], Animal->Animal_profile["season"]) << "; " << Animal->Animal_profile["color"] << "; " << Animal->Animal_profile["sex"] << "; " << Animal->Animal_profile["weight"] << "; " << Animal->Animal_profile["origin"] << "; " << "Arrived April " << random_day << ", " << "2025\n";
                myFile << "\n";
                cout << "Animal parsed for print successfully\n";
            }
        //This will eventually call each "species_habitat" loops through each object
        //Each object's contents will print to file newAnimals.txt

        }
        //close file when done
        myFile.close();
        cout << "Print to file closed!\n";
    }
}
string genBirthDay(string age, string season) {
    map<string, string> Season_months = {{"winter", "12"}, {"spring", "03"}, {"summer", "06"}, {"fall", "09"}};
    random_device randomday;
    mt19937 gen(randomday());
    uniform_int_distribution<> dist(1, 28);
    int random_day = dist(gen);
    int age_num = stoi(age);
    int birthdate = 2025 - age_num;
    string birth_month;
    if (Season_months.find(season) != Season_months.end()) {
        birth_month = Season_months.at(season);
    }
    else {
        birth_month = "01";
    }
    string birth_dateISO8061 = birth_month + "-" + to_string(random_day) + "-" + to_string(birthdate);
    //Needs to return
    return birth_dateISO8061;
    cout << "birth month assigned\n";
}

void closed_for_cleaning() {
    for (auto& [habitat_name, habitat] : Zoo) {
        for (auto& [animal_name, animal_ptr] : habitat) {
            delete animal_ptr;  // Free each Animal*
        }
    }
    cout << "After all that activity...The Zoo is now closed for Maintenance!!\n";
}




