#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

using namespace std;

vector<string> splitString(string str, char separator=' ');

class Date{
    private:
        int day, month, year;
    public:
    Date(){
        day = 0;
        month = 0;
        year = 0;
    }
    Date(int d, int m, int y){
        if (m > 12 || m < 1)
            throw "Invalid value for month";
        if (!checkDay(d, m, y))
            throw "Invalid value for day";
        day = d;
        month = m;
        year = y;
    }
    void setDay(int d) {
        // set day of date and check if it is valid
        if (!checkDay(d, month, year))
            throw "Invalid value for day";
        day = d;
    }
    void setMonth(int m) {
        // set month of date and check if it is valid
        if (!checkDay(day, m, year) || m < 1 || m > 12)
            throw "Invalid value for month";
        month = m;
    }
    void setYear(int y) {
        // set year of date and check if it is valid
        if (!checkDay(day, month, y))
            throw "Invalid value for year";
        year = y;
    }
    int getDay() {return day;} // return day of the date
    int getMonth() {return month;} // return month of the date
    int getYear() {return year;} // return year of the date
    string getString(){
        // return date as string in format day/month/year
        string str;
        str = to_string(day) + '/' + to_string(month) + '/' + to_string(year);
        return str; 
    }
    static bool checkDay(int d, int m, int y){
        /*
        check if introduced date is correct
        for leap year, maximum day in February is 29, else 28
        in April, June, September and November there are 30 days
        in other mothers 31
        */
        if (d < 1)
            return false;
        switch (m){
            case 2:{
                if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)){
                    if (d > 29)
                        return false;
                }
                else{
                    if (d > 28)
                        return false;
                }
                break;
            }
            case 4: case 6: case 9: case 11:{
                if (d > 30)
                    return false;
                break;
            }
            default:{
                if (d > 31)
                    return false;
                break;
            }
        }
        return true;
    }
    bool operator > (Date date){
        /*
        compare if first(current) date is bigger than another
        by bigger means is later
        */
        if (year < date.getYear())
            return false;
        if (year > date.getYear())
            return true;
        if (year == date.getYear()){
            if (month > date.getMonth())
                return true;
            if (month < date.getMonth())
                return false;
            if (month == date.getMonth()){
                if (day > date.getDay())
                    return true;
            }  
        }
        return false;
    }
    bool operator == (Date date){
        // check if dates are equal (same day, month and year)
        if (year == date.year && month == date.month && day == date.day)
            return true;
        return false;
    }
    void print_date(){ cout << day << "/" << month << "/" << year;} // print date in format day/month/year
    static Date convertToDate(string date_str){
        // convert string in format day/month/year to object of class Date and return it
        vector<string> date = splitString(date_str, '/');
        return Date(stoi(date[0]), stoi(date[1]), stoi(date[2]));
    }
};
class Trip{
private:
    Date date;
    string dep_stat, arr_stat;
    double fee, distance;
    int seat_num, wag_num;
public:
    Trip(){
        this->date = Date();
        this->fee = 0;
        this->dep_stat = "";
        this->arr_stat = "";
        this->distance = 0;
        this->seat_num = 0;
        this->wag_num = 0;
    }
    Trip(Date date, double fee, string dep_stat, string arr_stat, double distance, int seat_num, int wag_num){
        this->date = date;
        if (fee <= 0)
            throw "Invalid value for fee, it should be positive";
        this->fee = fee;
        this->dep_stat = dep_stat;
        this->arr_stat = arr_stat;
        if (distance <= 0)
            throw "Invalid value for distance, it should be positive";
        this->distance = distance;
        this->seat_num = seat_num;
        this->wag_num = wag_num;
    }
    Date getDate(){ return date;} // return date of the trip
    void setDate(Date date){ this->date = date; } // set date of the trip
    string getDep(){ return dep_stat;} // return departure station of the trip
    void setDep(string dep_stat){this->dep_stat = dep_stat; } // set departure station of the trip
    string getArr(){ return arr_stat;} // return arrival station of the trip
    void setArr(string arr_stat){this->arr_stat = arr_stat;} // set arrival station of the trip
    int getSeatNum(){ return seat_num;} // return number of the seat
    void setSeatNum(int seat_num){this->seat_num = seat_num; } // set number of the seat
    int getWagNum(){ return wag_num;} // return wagon number of the seat 
    void setWagNum(int wag_num){this->wag_num = wag_num; } // set wagon number of the seat 
    double getFee(){return fee;} // return fee of trip
    void setFee(double fee){
        // set fee of the trip
        if (fee <= 0)
            throw "Invalid value for fee, it should be positive";
        this->fee = fee; 
    }
    double getDistance(){ return distance;} // return distance of the trip
    void setDistance(double distance){
        // set distance of the trip
        if (distance <= 0)
            throw "Invalid value for distance, it should be positive";
        this->distance = distance;
    }
    bool operator== (Trip trip){
        // if all data if trips is the same, then it is the same trips
        if (date==trip.date && fee==trip.fee && dep_stat==trip.dep_stat && arr_stat==trip.arr_stat 
        && distance==trip.distance && seat_num==trip.seat_num && wag_num==trip.wag_num) return true;
        return false;
    }
    void showInfo(){
        // print essential data of a trip to console
        cout << "Date: ";
        date.print_date();
        cout << ". Departure station: " << dep_stat;
        cout << ". Arrival station: " << arr_stat;
    }
};
class Passenger{
static const int MAX_WEIGHT = 25;
private:
    int id, age;
    string name, address;
    char gender;
    double bag_weight;
    list<Trip> trips;
public:
    Passenger(){
        this->id = 0;
        this->name = "";
        this->age = 0;
        this->address = "";
        this->gender = ' ';
        this->trips = {};
        this->bag_weight = 0;
    }
    Passenger(int id, string name, int age, string address, char gender, int bag_weight = 0, list<Trip> trips={}){
        this->id = id;
        this->name = name;
        this->age = age;
        this->address = address;
        this->gender = gender;
        this->trips = trips;
        if (bag_weight > MAX_WEIGHT)
            throw "Invalid baggage weight, it cannot exceed 25 KG";
        this->bag_weight = bag_weight;
    }
    void setID(int id){ this->id = id;} // set id of the passenger
    int getID(){return id;} // return id of the passenger
    void setAge(int age){ this->age = age;} // set age of the passenger
    int getAge(){ return age;} // return age of the passenger
    void sortTrips(){
        /*
        sort trips by date in increasing order (the earliest trips first)
        */
        Trip tmp;
        for (auto i=trips.begin(); i!=trips.end(); i++){
            for (auto j=i; j!=trips.end(); j++){
                if ((*i).getDate() > (*j).getDate()){
                    tmp = *i;
                    *i = *j;
                    *j = tmp;
                }
            }
        }
    }
    double getFeeOfTrip(Date date, string dep_stat, string arr_stat){
        // get fee of trip of this passenger by date, departure and arrival station
        for (auto i=trips.begin(); i!=trips.end(); i++){
            if((*i).getArr() == arr_stat && (*i).getDate() == date && (*i).getDep() == dep_stat)
                return (*i).getFee();
        }
        return 0;
    }
    void setName(string name){ this->name = name;} // set name of the passenger
    string getName(){return name;} // return name of the passenger
    void setAddress(string address){ this->address = address;} // set address of the passenger
    string getAddress(){return address;} // return address of the passenger
    void setGender(char gender){ this->gender = gender;} // set gender of the passenger
    char getGender(){return gender;} // return gender of the passenger
    void setBagWeight(double bag_weight){ 
        // set weight of bag of the user if it is of valid weight
        if (bag_weight > MAX_WEIGHT)
            throw "Invalid baggage weight, it cannot exceed 25 KG";
        this->bag_weight = bag_weight;
    }
    double getBagWeight(){return bag_weight;} // return weight of bag of the passenger
    static Passenger createPassenger(int id){
        /*
        ask user all other necessary information to create passenger
        return created passenger with given id as parameter
        */
        Passenger person;
        person.id = id;
        cout << "Introduce information about new passenger:\n";
        cin.ignore(); // ignore \n in previous line
        cout << "Introduce the passengers name: ";
        getline(cin, person.name); // read whole line from \n to \n so we can get name with surname
        cout << "Introduce the passengers age: ";
        cin >> person.age;
        cin.ignore();
        cout << "Introduce the passengers address: ";
        getline(cin, person.address);
        cout << "Introduce the passengers gender: ";
        cin >> person.gender;
        cout << "Introduce the passengers bag weight: ";
        cin >> person.bag_weight;
        return person;
        
    }
    void addTrip(Trip trip){ trips.push_back(trip);} // add new trip to trip list
    void deleteTrip(Trip trip){
        // delete certain trip from trips list
        auto i = find(trips.begin(), trips.end(), trip);
        trips.erase(i);
    }
    void deleteTrip(Date date, string dep_stat, string arr_stat){
        // delete trip by date, departure and arrival station from trips list
        bool found = false;
        list<Trip>::iterator i = trips.begin();
        int j = 0;
        while (i != trips.end() && !found){
            if ((*i).getArr() == arr_stat && (*i).getDep() == dep_stat && (*i).getDate() == date){
                auto it = trips.begin();
                advance(it, j);
                trips.erase(it);
                found = true;
            }
            i++;
            j++;
        }
    }
    bool operator== (Passenger second){ return id == second.id;} // passengers have same id, it is same passenger
    list<string> getCities(){
        // for every trip we push_back to list arrival station so we have list of cities which passenger visited
        list<string> cities;
        for (auto i=trips.begin(); i!=trips.end(); i++)
            cities.push_back((*i).getArr());
        return cities;
    }
    void printPassengerInfo(){
        // print essential data of a passenger and all his trips to console
        cout << "Name and id: ";
        cout << name << ", " << id << endl;
        cout << "Information about trips:\n";
        showAllTrips();
    }
    void infoToFile(ofstream &info_file){
        // output all information about passenger to a given file
        info_file << "Passenger: ID: " << id << "; Name: " << name << "; Address: ";
        info_file << address << "; Age: " << age << "; Gender: " << gender;
        info_file << "; Baggage weight: " << bag_weight << " kg; ";
    }
    void showAllTrips(){
        /*
        sort trips of passenger
        for every trip print information about it
        if passenger has no trips, we inform user about it
        */
        int j = 1;
        sortTrips();
        for (auto i=trips.begin(); i!=trips.end(); i++){
            printf("Trip %d info: ", j);
            (*i).showInfo();
            cout << endl;
            j++;
        }
        if (j == 1)
            cout << "Passenger does not have any trip\n";
    }
};
class Wagon{
private:
    int num_wag, seats_num;
    map<int, int> seat_id; // key: seat and value: id
public:
    Wagon(){
        this->num_wag = 0;
        this->seats_num = 0;
        this->seat_id = {};
    }
    Wagon(int num_wag, int seats_num, map<int, int> seat_id={}){
        this->num_wag = num_wag;
        this->seats_num = seats_num;
        this->seat_id = seat_id;
    }
    void setSeat(int seat, int id) { seat_id[seat]=id;} // set id of passenger to a seat
    void setSeatId(map<int, int> seat_id){ this->seat_id=seat_id;} // set map of seats and ids
    void setWagNum(int num_wag) {this->num_wag = num_wag;} // set number of wagon
    void setSeatsNum(int seats_num) {this->seats_num = seats_num;} // set number of seats
    int getFirstFreeSeat() {
        // return first seat that is not occupied
        for (int i=1; i<=seats_num; i++){
            if (seat_id.find(i)==seat_id.end())
                return i;
        }
        return 0;
    }
    void deleteSeat(int seat){
        // delete passenger from certain seat
        auto i = seat_id.find(seat);
        seat_id.erase(i);
    }
    int getWagNum(){return num_wag;} // return the number of wagon
    int getSeatNum(){return seats_num;} // return number of seats
    int getPassengerSeat(Passenger passenger){
        /*
        return seat of certain passenger
        return 0 to indicate that passenger is not in wagon
        */
        for (auto i=seat_id.begin(); i!=seat_id.end(); i++){
            if ((*i).second==passenger.getID())
                return (*i).first;
        }
        return 0;
    }
    void showInfo(map <int, Passenger> passengers){
        // print information about every passenger of wagon and the number of place they occupy
        for (auto i=seat_id.begin(); i!=seat_id.end(); i++){
            cout << "ID: " << (*i).second << ". Name: " << passengers[(*i).second].getName();
            cout << ". Seat number: " << (*i).first << endl;
        }
    }
    void infoToFile(ofstream &info_file, map <int, Passenger> passengers, string dep_stat, string arr_stat, Date date){
        // output to file full information about wagon and each passenger in it
        info_file << "Wagon: Number: " << num_wag << "; Seats number: " << seats_num << endl;
        for (auto i=seat_id.begin(); i!=seat_id.end(); i++){
            passengers[(*i).second].infoToFile(info_file);
            info_file << "Seat number: " << (*i).first << "; Fee: ";
            info_file << passengers[(*i).second].getFeeOfTrip(date, dep_stat, arr_stat) << " €" << endl;
        }
        info_file << endl;
     }
};
class Train{
private:
    int code;
    Date date;
    string dep_stat, arr_stat;
    double distance;
    list<Wagon> wagons;
public:
    Train(){
        this->code = 0;
        this->dep_stat = "";
        this->arr_stat = "";
        this->distance = 0;
        this->wagons = {};
    }
    Train(int code, Date date, string dep_stat, string arr_stat, double distance, list<Wagon> wagons={}){
        this->code = code;
        this->date = date;
        this->dep_stat = dep_stat;
        this->arr_stat = arr_stat;
        this->distance = distance;
        this->wagons = wagons;
    } 
    Date getDate(){return date;} // return date of departure of the train
    string getDep(){return dep_stat;} // return departure station of the train
    string getArr(){return arr_stat;} // return arrival station of the train
    double getDistance(){return distance;} // return distance between departure and arrival stations of the train
    int getCode() {return code;} // return unique code  of the train
    void addWagon(Wagon wagon){ wagons.push_back(wagon);} // add wagon to list of wagons of train
    pair<int, int> setFirstFreeSeat(int id){
        /*
        go through every wagon to find first free seat in the train
        return pair 0,0 to indicate that free space was not found
        */
        list<Wagon>::iterator i = wagons.begin();
        bool state = false; // state of whether we find free space or not
        int seat_num;
        while (i != wagons.end() && !state){
            seat_num = (*i).getFirstFreeSeat();
            if (seat_num != 0){
                (*i).setSeat(seat_num, id);
                state = true;
            }
            i++;
        }
        if (state) {
            i--; // go back to previous wagon because we moved forward in while loop
            return {(*i).getWagNum(), seat_num};
        }
        return {0, 0};
    }
    pair<int, int> getPassengerPlace(Passenger passenger){
        /*
        return wagon and seat number of a given passenger
        return pair 0,0 if passenger was not found on the train
        */
        for (auto i=wagons.begin(); i!=wagons.end(); i++){
            if ((*i).getPassengerSeat(passenger)!=0)
                return {(*i).getWagNum(), (*i).getPassengerSeat(passenger)};
        }
        return {0, 0};
    }
    void deleteSeat(pair<int, int> seat){
        // delete passenger from the train by given wagon and seat numbers
        for (auto i=wagons.begin(); i!=wagons.end(); i++){
            if ((*i).getWagNum() == seat.first)
                (*i).deleteSeat(seat.second);
        }
    }
    void showInfo(map <int, Passenger> passengers){
        // print information about train, about every wagon and each passenger on it
        cout << "Train from " << dep_stat << " to " << arr_stat << " on ";
        date.print_date();
        cout << endl;
        for (auto i=wagons.begin(); i!=wagons.end(); i++){
            cout << "Wagon " << (*i).getWagNum() << " info: \n";
            (*i).showInfo(passengers);
            cout << endl;
        }
    }
    void infoToFile(ofstream &info_file, map <int, Passenger> passengers){
        // output to file full information about train, each wagon and each passenger
        info_file << "Train: Code: " << code << "; Date: " << date.getString();
        info_file << "; Departure station: " << dep_stat << "; Arrival station: ";
        info_file << arr_stat << "; Distance: " << distance << " km\n";
        for (auto i=wagons.begin(); i!=wagons.end(); i++)
            (*i).infoToFile(info_file, passengers, dep_stat, arr_stat, date);
        info_file << endl;
    }
};

// additional functions
void sort_names(list<Passenger> &names){
    // sort list of passengers passed by reference
    Passenger tmp;
    for (auto i=names.begin(); i!=names.end(); i++){
        for (auto j=i; j!=names.end(); j++){
            if ((*i).getName().compare((*j).getName()) >= 0){
                tmp = *i;
                *i = *j;
                *j = tmp;
            }
        }
    }
}
bool isZero(pair<int, int> p){ 
    // check if pair is zero
    return p.first == 0 && p.second == 0;
}
vector<string> splitString(string str, char separator){
    /*
    split string by a certain separator 
    return vector of strings between separators
    */
    vector<string> splitted_list;
    string substr;
    int start_pos = 0;
    int end_pos = str.find(separator, start_pos); // find first appearance of separator
    while (end_pos != -1){ 
        substr = str.substr(start_pos, end_pos-start_pos);
        if (substr.length() != 0) // check if length is not equal to zero to omit empty substrings (they are equal if there are two or more separators in row)
            splitted_list.push_back(substr);
        start_pos = end_pos + 1;
        end_pos = str.find(separator, start_pos);
    }
    if (start_pos != str.length())
        splitted_list.push_back(str.substr(start_pos, str.length() - start_pos));
    return splitted_list;
}
void printSeatInfo(Passenger passenger, pair<int, int> seat){
    // print general information about passenger that occupies seat
    cout << "Passenger " << passenger.getName() << " with id " << passenger.getID();
    cout << " occupies seat " << seat.second << " in wagon " << seat.first << endl;
}
void toLowerCase(string &str){
    // lower all capital letters
    for (int i=0; i!=str.size(); i++){
        if (str[i] <= 90)
            str[i] += 32;
    }
}



void readInitialData(list<Train>&trains, map<int, Passenger>&passengers){
    // read information from the file
    // save information to list of trains and map of passengers with keys theirs ids, and values - passengers
    ifstream info_file;
    info_file.open("info.txt");
    if (!info_file) {
        throw "Files doesn't exist.\n";
    }
    else{
        string line, key;
        vector<string> information, info;
        Train train;
        Wagon wagon;
        int i = 1;
        while (!info_file.eof()){
            info_file >> key; // read first word(until space) in line to identify what is next information about
            if (key == "Train:"){
                if (train.getCode() != 0){ // for case when information about previous train was filled
                    train.addWagon(wagon); // add last wagon to it
                    trains.push_back(train); // add train to list of trains
                    wagon = Wagon();
                }
                getline(info_file, line);
                information = splitString(line, ';');
                int code;
                Date date;
                string dep_stat, arr_stat;
                code = stoi(splitString(information[0])[1]);
                date = Date::convertToDate(splitString(information[1])[1]);
                info = splitString(information[2]);
                dep_stat = info[2];
                if (info.size() != 3){ // for case when departure station name is not one word
                    for (int i=3; i!=info.size(); i++)
                        dep_stat += ' ' + info[i];
                }
                info = splitString(information[3]);
                arr_stat = info[2];
                if (info.size() != 3){ // for case when arrival station name is not one word
                    for (int i=3; i!=info.size(); i++)
                        arr_stat += ' ' + info[i];
                }
                double distance = stod(splitString(information[4])[1]);
                train = Train (code, date, dep_stat, arr_stat, distance);
            }
            else if(key == "Wagon:"){
                if (wagon.getWagNum() != 0) // for case when information about previous wagon was filled
                    train.addWagon(wagon); // add wagon to current train
                getline(info_file, line);
                information = splitString(line, ';');
                int num_wag, seats_num;
                num_wag = stoi(splitString(information[0])[1]);
                seats_num = stoi(splitString(information[1])[2]);
                wagon = Wagon (num_wag, seats_num);
                
            }
            else if (key == "Passenger:"){
                getline(info_file, line);
                information = splitString(line, ';');
                int id, age, seat_number; 
                string name, address;
                double fee, bag_weight;
                char gender;
                id = stoi(splitString(information[0])[1]);
                info = splitString(information[1]);
                name = info[1] + ' ' + info[2];
                if (info.size() != 3){
                    for (int i=3; i!=info.size(); i++)
                        name += ' ' + info[i];
                }
                
                info = splitString(information[2]);
                address = info[1];
                if (info.size() != 2){
                    for (int i=2; i!=info.size(); i++)
                        address += ' ' + info[i];
                }
                age = stoi(splitString(information[3])[1]);
                gender = splitString(information[4])[1][0];
                bag_weight = stoi(splitString(information[5])[2]);
                seat_number = stoi(splitString(information[6])[2]);
                fee = stoi(splitString(information[7])[1]);
                if (passengers.find(id) == passengers.end()) // check if passenger was already created, and if not
                    passengers[id] = Passenger(id, name, age, address, gender, bag_weight); // create passenger
                // add trip to passenger
                passengers[id].addTrip(Trip(train.getDate(), fee, train.getDep(), train.getArr(), train.getDistance(), seat_number, wagon.getWagNum()));
                wagon.setSeat(seat_number, id);
            }
        }
        train.addWagon(wagon); // add last created wagon to last created train
        trains.push_back(train); // add last created train to list of trains
        
        
    info_file.close();
    }
}

int mainMenu(){
    // print options for executing and return number of option
    int option;
    do {
        cout << "\nWelcome to menu. This is options of what you can do\n";
        cout << "1.\tAdd new passenger’s trip to a train\n";
        cout << "2.\tRemove a passenger’s trip from a train\n";
        cout << "3.\tShow trips of a passenger\n";
        cout << "4.\tShow list of passengers in a specific train\n";
        cout << "5.\tShow an alphabetically ordered list of passengers in all the trains\n";
        cout << "6.\tShow passengers of cities\n";
        cout << "7.\tEnd program\n";
        cout << "Choose option you want: ";
        cin >> option;
        if (option < 1 || option > 7){
            cout << "Wrong input\nChoose between 1 and 7\n";
        }
    } while (option < 1 || option > 7);
    return option;
}


pair<int, int> addNewPassengerTrip(list <Train> &trains, map <int, Passenger> &passengers){
    /*
    ask user to introduce information about train and id of passenger
    if passenger already exists on train, return his/her seat with pair wagon number, seat number
    if not, create passenger(if he/she does not exist in passengers map), assign to him/her first free seat, return that seat as pair of wagon and seat numbers
    if wrong train data introduced, offer to input it again, otherwise return zero wagon and seat numbers
    */
    int day, month, year, id;
    string dep_stat, arr_stat, name, repeat;
    double fee;
    pair <int, int> seat;
    Passenger person;
    bool train_found = false;
    cout << "Introduce the information about the trip:\n";
    cout << "Write the date: ";
    cin >> day >> month >> year;
    Date date(day, month, year);

    cin.ignore(); // ignore \n in previous line
    cout << "Write the departure station: ";
    getline(cin, dep_stat); // used to get string with spaces
    cout << "Write the arrival station: ";
    getline(cin, arr_stat);
    cout << "Introduce the id of the passenger: ";
    cin >> id;
    if (passengers.find(id) == passengers.end())
        passengers[id] = Passenger::createPassenger(id);
    list<Train>::iterator i = trains.begin();
    while (i != trains.end() && !train_found){
        if ((*i).getDep()==dep_stat && (*i).getArr()==arr_stat && (*i).getDate()==date){
            seat = (*i).getPassengerPlace(passengers[id]);
            if (!isZero(seat)){ // if it is not 0,0 that means that passenger occupies some seat
                cout << "Passenger " << passengers[id].getName() << " already exist on train\n";
                printSeatInfo(passengers[id], seat);
                return seat;
            }
            else {
                seat = (*i).setFirstFreeSeat(id);
                if (!isZero(seat)){
                    cout << "Introduce the price of trip: ";
                    cin >> fee;
                    passengers[id].addTrip(Trip (date, fee, dep_stat, arr_stat, (*i).getDistance(), seat.second, seat.first));
                    printSeatInfo(passengers[id], seat);
                    return seat;
                }
            }
            train_found = true; // if we got here, that means that in else seat is 0, 0, which means that there is no free seats
        }
        i++;
    }
    if (!train_found)
        cout << "There is no such train\n";
    else {
        cout << "Unfortunately, there is no unoccupied seats in train from " << dep_stat;
        cout << " to " << arr_stat << " on " << date.getString();
    }
    cout << "\nDo you want to get another train? (yes/no) ";
    cin >> repeat;
    toLowerCase(repeat);
    while (repeat != "yes" && repeat != "no"){
        cout << "There is no such option\n";
        cout << "Do you want to get another train? (yes/no) ";
        cin >> repeat;
        toLowerCase(repeat);
    }
    if (repeat == "yes")
        return addNewPassengerTrip(trains, passengers);
    return {0, 0};
}

void removePassengerTrip(list <Train> &trains, map <int, Passenger> &passengers){
    /*
    ask to introduce train information and passenger id
    if passenger is on train, he/she is deleted from train and he/she no longer has this trip
    if passenger is not on train, inform user about it
    */
    int day, month, year, id;
    string dep_stat, arr_stat;
    bool train_found = false;
    pair<int, int> seat;
    cout << "Write the date: ";
    cin >> day >> month >> year;
    Date date(day, month, year);
    cin.ignore();
    cout << "Write the departure station: ";
    getline(cin, dep_stat);
    cout << "Write the arrival station: ";
    getline(cin, arr_stat);
    cout << "Introduce the id of the passenger: ";
    cin >> id;
    if (passengers.find(id) == passengers.end())
        cout << "There is no passenger with id " << id << endl;
    else {
        list<Train>::iterator i = trains.begin();
        while (i != trains.end() && !train_found){
            if ((*i).getDep()==dep_stat && (*i).getArr()==arr_stat && (*i).getDate()==date){
                seat = (*i).getPassengerPlace(passengers[id]);
                if (isZero(seat)){
                    cout << "There is no passenger " << passengers[id].getName() << " with id " << id;
                    cout << " in train on ";
                    date.print_date();
                    cout << " from " << dep_stat << " to " << arr_stat << endl;
                }
                else {
                    (*i).deleteSeat(seat);
                    passengers[id].deleteTrip(date, dep_stat, arr_stat);
                    cout << "Passenger " << passengers[id].getName() << " with id " << id;
                    cout << " was deleted from the seat " << seat.second << " in wagon " << seat.first << endl;
                }
                train_found = true;
            }
            i++;
        }
        if (!train_found)
            cout << "There is no such train\n";
    }
}

void showTripsOfPassenger(map <int, Passenger> passengers){
    // print all trips of passenger given by id
    // if no trips performed or passenger does not exist, inform user about it
    int id;
    cout << "Introduce the id of the passenger: ";
    cin >> id;
    if (passengers.find(id) == passengers.end())
        cout << "There is no such passenger\n";
    else {
        cout << "Passenger with id " << id << " is " << passengers[id].getName();
        cout << "\nTrip information:\n";
        passengers[id].showAllTrips();
    }
}

void showListOfPassengers(list <Train> trains, map <int, Passenger> passengers){ 
    /*
    by code of train, print all wagons' information and all passengers' information inside of them
    if there is no train with such code, inform user about it
    */
    int code;
    cout << "Introduce the code of the train: ";
    cin >> code;
    bool state = false;
    list<Train>::iterator i = trains.begin();
    while (!state && i != trains.end()){
        if ((*i).getCode() != code)
            i++;
        else
            state = true;
    }
    if (state){
        cout << "Train with code " << code << " is from " << (*i).getDep();
        cout << " to " << (*i).getArr() << " on ";
        (*i).getDate().print_date();
        cout << endl;
        (*i).showInfo(passengers);
    }
    else    
        cout << "There is no such train\n";
}

list<Passenger> orderedListOfPassengers(map <int, Passenger> passengers){
    // return sorted list of passengers by their names
    list<Passenger> names; 
    for (auto i = passengers.begin(); i!=passengers.end(); i++)
        names.push_back((*i).second);
    
    sort_names(names);
    return names;
}

map<string, list<Passenger>> passengersCities(map <int, Passenger> passengers){
    /*
    return map where keys are city names and values are list of passengers who visited that city 
    (whose arrival station was that city)
    */
    map<string, list<Passenger>> cities_passengers;
    list<string> cities;
    list<Passenger>::iterator it;
    for (auto i=passengers.begin(); i!=passengers.end(); i++){
        cities = (*i).second.getCities();
        for (auto j=cities.begin(); j!=cities.end(); j++){
            if (find(cities_passengers[*j].begin(), cities_passengers[*j].end(), (*i).second) == cities_passengers[*j].end())
                cities_passengers[*j].push_back((*i).second);
        }
    }
    return cities_passengers;
} 

void endProgram(list<Train>&trains, map<int, Passenger>&passengers){
    /*
    store information about trains and passengers in Output.txt file in such way
    that is can be read by this program later as input file
    */
    ofstream f;
    f.open("Output.txt");
    for (auto i=trains.begin(); i!=trains.end(); i++)
        (*i).infoToFile(f, passengers);
    f.close();
}

int main(){
    try {
        map <int, Passenger> passengers;
        list <Train> trains;
        list <Wagon> wagons;
        list <Passenger> ordered;
        map <string, list <Passenger>> allCities;
        pair<int, int> seat;
        readInitialData(trains, passengers);
        int option = mainMenu();
        while (option != 7){
            switch (option){
                case 1:
                    seat = addNewPassengerTrip(trains, passengers);
                    if (!isZero(seat))
                        printf("Seat %d in wagon %d is occupied\n", seat.second, seat.first);
                    break;
                case 2:
                    removePassengerTrip(trains, passengers);
                    break;
                case 3:
                    showTripsOfPassenger(passengers);
                    break;
                case 4:
                    showListOfPassengers(trains, passengers);
                    break;
                case 5:
                    ordered = orderedListOfPassengers(passengers);
                    for (auto i = ordered.begin(); i!=ordered.end(); i++){
                        (*i).printPassengerInfo();
                        cout << endl;
                    }
                    break;
                case 6:
                    allCities = passengersCities(passengers);
                    for (auto i=allCities.begin(); i!=allCities.end(); i++){
                        cout << "Passengers who visited " << (*i).first << ": ";
                        for (auto j=(*i).second.begin(); j!=(*i).second.end(); j++){
                            cout << (*j).getName() << "; ";
                        }
                        cout << endl;
                    }
                    break;
            }
            option = mainMenu();
        }
        endProgram(trains, passengers);
        cout << "Data was successfully saved\nGoodbye\n";
    }
    catch (const char *e) {
        cout << "Error: " << e << endl;
    }
}