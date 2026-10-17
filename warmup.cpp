// =====================================================================
//  C++ WARM-UP  ·  African Olympiad Academy
//
//  The question descriptions are in README.md. Read them there.
//  This file holds the data, one worked example, and your answers.
//
//  BUILD AND RUN:   g++ -std=c++17 -Wall -o run warmup.cpp && ./run
//            or:    ./run.sh
//
//  Work on ONE question at a time. Write it, run it, check the output
//  against the README, commit it, move on.
// =====================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

/**
 * THE RECORD
 * One delivery: who brought it, how much, and what grade it was given.
 */
struct Delivery {
    string farmer;
    double kg;
    char   grade;
};


/**
 * THE DATA
 * Do not change these. Every expected answer in the README comes fromint exactly this data.
 */

// Q1 — one morning's weights, in the order they were weighed
vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};
int findFarmer(const vector<Delivery> log, string name);
// Q2, Q3, Q4, Q7, Q8 — the day's logbook
double payment(double kg, char grade, double total_cost);
vector<Delivery> logbook = {
    {"Keza",    45.5, 'A'},
    {"Bonu",    80.0, 'B'},
    {"Isanda",  20.0, 'A'},
    {"Keza",    12.0, 'C'},
    {"Onyinye", 66.5, 'B'},
    {"Karimi",  31.0, 'A'},
    {"Karimi",  31.0, 'A'},
    {"Keza",    18.5, 'B'},
    {"Bonu",    50.0, 'C'},
    {"Isanda",  20.0, 'A'},
    {"Onyinye", 72.0, 'A'}
};   // yes, one of these rows is in here twice. Q8 is about that.

// Q5 — records as the volunteers typed them, before any checking. Several of these are wrong. That is the point.
struct RawRecord {
    string id;
    string kg;        // text, because a volunteer can type anything
    char   grade;
};

vector<RawRecord> rawRecords = {
    {"F012", "45.5",  'A'},
    {"F7",   "20",    'A'},
    {"F033", "heavy", 'B'},
    {"F021", "0",     'C'},
    {"F044", "80",    'b'},
    {"F055", "",      'A'},
    {"F066", "31.5",  'D'},
    {"F077", "92",    'B'}
};

// Q6 — an Igisoro board. 16 pits, in sowing order.
//      Position 0 is unused so that board[1] really is pit 1.
vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};


// ---------------------------------------------------------------------
//  A HELPER YOU MAY FIND USEFUL
// ---------------------------------------------------------------------
void printBoard(const vector<int> b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}


int main() {

    // =================================================================
    //  WORKED EXAMPLE  ·  not a question
    //
    //  This is the house style: walk the data once, keep what you need
    //  as you go, print at the end. Read it before you start Q1.
    //
    //  It answers: how many deliveries were grade A, and what was the
    //  heaviest single delivery in the whole logbook?
    // =================================================================

    int gradeACount = 0;
    Delivery heaviest = logbook[0];        // start from a REAL entry,
                                           // never from a made-up 0
    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;                  // keep the WHOLE record,
        }                                  // not just the number
    }

    cout << "=== Worked example ===\n";
    cout << "Grade A deliveries: " << gradeACount << "\n";
    cout << "Heaviest: " << heaviest.farmer << " with "
         << heaviest.kg << " kg\n\n";


    // =================================================================
    //  Q1  ·  THE WEIGHING SESSION          (see README)
    //  Uses: morningWeights
    // =================================================================
    size_t count = 0;
    int valid_count = 0;
    double Total_weight = 0;
    double heaviest_weight = morningWeights[0];
    int heaviest_weight_pos = 0;
    int longest_run = 0;
    vector<int> longest_run_history ={};
    while (count < morningWeights.size()) {
        Total_weight += morningWeights[count];
        if ((morningWeights[count] > 0) && (morningWeights[count] <= 80)){
            valid_count += 1;
            longest_run += 1;
        }
        else{
            longest_run_history.push_back(longest_run);
            longest_run = 0;
        }
        if (morningWeights[count] > heaviest_weight){
            heaviest_weight = morningWeights[count];
            heaviest_weight_pos = count;
        }
        
        count ++;
    }
    longest_run = *max_element(longest_run_history.begin(),longest_run_history.end());
    cout << "=== Q1 ===\n";
    cout << "Total: " <<  Total_weight  << " kg"<<"\n";
    cout << "valid: " << valid_count << " of 12" <<"\n";
    cout << "Heaviest: " << heaviest_weight << " kg at position " << heaviest_weight_pos <<"\n";
    cout << "Longest valid run : " << longest_run <<"\n";



    cout << "\n";


    // =================================================================
    //  Q2  ·  GRADE SUMMARY                 (see README)
    //  Uses: logbook
    // =================================================================
    int adeliveries = 0;
    int bdeliveries = 0;
    int cdeliveries = 0; 
    count = 0;
    double Total_weighta = 0;
    double Total_weightb = 0;
    double Total_weightc = 0;

    while(count < logbook.size()) {
        if (logbook[count].grade == 'A'){
            adeliveries += 1;
            Total_weighta += logbook[count].kg;
        }
        if (logbook[count].grade == 'B'){
            bdeliveries += 1;
            Total_weightb += logbook[count].kg;
        }
        if (logbook[count].grade == 'C'){
            cdeliveries += 1;
            Total_weightc += logbook[count].kg;
        
        }
        count++;
    }
    vector<double> averages = {Total_weighta/adeliveries, Total_weightb/bdeliveries, Total_weightc/cdeliveries};
    string winner;
    if (averages[0]==*max_element(averages.begin(),averages.end())){
        winner = "A";
    }
    if (averages[1]==*max_element(averages.begin(),averages.end())){
        winner = "B";
    }
    if (averages[2]==*max_element(averages.begin(),averages.end())){
        winner = "C";
    }
    cout << "=== Q2 ===\n";
    cout << "Grade A:" << adeliveries << " deliveries, " << Total_weighta << " kg total, " << averages[0] << " kg average" << "\n";
    cout << "Grade B:" << bdeliveries << " deliveries, " << Total_weightb << " kg total, " << averages[1] << " kg average" << "\n";
    cout << "Grade C:" << cdeliveries << " deliveries, " << Total_weightc << " kg total, " << averages[2] << " kg average" << "\n";
    cout << "Best average: grade " << winner << "\n";






    cout << "\n";


    // =================================================================
    //  Q3  ·  WHO IS WHO                    (see README)
    //  Uses: logbook, and the findFarmer function you write below main
    // =================================================================
    count = 0;
    map<string,int> frequency = {};
    map<string,double> Total_individual_weight ={};
    while (count < logbook.size()){
        auto it = frequency.find(logbook[count].farmer);
        auto ob = Total_individual_weight.find(logbook[count].farmer);
        if(it == frequency.end()){
            frequency.insert({logbook[count].farmer,1});
        }
        else{
            frequency[logbook[count].farmer] += 1;
        }
        if(ob == Total_individual_weight.end()){
            Total_individual_weight.insert({logbook[count].farmer,logbook[count].kg});
        }
        else{
            Total_individual_weight[logbook[count].farmer] += logbook[count].kg;
        }
        count++;
    }
    auto most_delivery  = max_element(frequency.begin(), frequency.end(),[](const auto& a, const auto& b){return a.second < b.second;});
    auto most_kg = max_element(Total_individual_weight.begin(),Total_individual_weight.end(),[](const auto& a, const auto& b){return a.second < b.second;});
    cout << "this is keza"<<frequency["Keza"] << "\n";
    cout << "=== Q3 ===\n";
    cout << "findFarmer(Isanda) = " << findFarmer(logbook, "Isanda") << "\n";
    cout << "findFarmer(Mukamana) = " << findFarmer(logbook, "Mukamana") << "\n";
    cout << "Most deliveries: " << most_delivery-> first << " (" << most_delivery->second << ")"<< "\n";
    cout << "Most kg: "<< most_kg-> first<< " ("<< most_kg->second<< ")"<<"\n";

    // =================================================================
    //  Q4  ·  PAYMENT RUN WITH A DAILY CAP  (see README)
    //  Uses: logbook, and the payment function you write below main
    // =================================================================
    double total_cost = 0;
    cout << "=== Q4 ===\n";
    count = 0;
    while (count < logbook.size()){
        if (total_cost < 100000){
        cout << logbook[count].farmer << " " << logbook[count].kg << " kg" << " grade " << logbook[count].grade << " -> " << payment(logbook[count].kg, logbook[count].grade, total_cost) << "\n";
        }
        else{
        cout << logbook[count].farmer << " " << logbook[count].kg << " kg" << " grade " << logbook[count].grade << " -> " << payment(logbook[count].kg, logbook[count].grade, total_cost) << "  (halved)"<< "\n";

        }
        total_cost += payment(logbook[count].kg, logbook[count].grade, total_cost);
        count++;

    }
    cout << "Total paid: " << total_cost << "\n";
    cout << "\n";


    // =================================================================
    //  Q5  ·  THE VALIDATION REPORT         (see README)
    //  Uses: rawRecords
    // =================================================================

    cout << "=== Q5 ===\n";





    cout << "\n";

    // =================================================================
    //  Q6  ·  IGISORO: A FULL TURN          (see README)
    //  Uses: board
    // =================================================================

    cout << "=== Q6 ===\n";



    
    // =================================================================
    //  STRETCH  ·  optional
    // =================================================================

    // =================================================================
    //  Q7  ·  SORT THE LOGBOOK              (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q7 ===\n";





    // =================================================================
    //  Q8  ·  SPOTTING DOUBLE-ENTRIES       (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q8 ===\n";




    
    return 0;
}



// =====================================================================
//  FUNCTIONS YOU WRITE
//
//  C++ reads a file top to bottom, so a function must be DECLARED above
//  the place that calls it. These two are declared here at the bottom,
//  which main() cannot see — so move them ABOVE main(), or leave a
//  one-line declaration up there. Working that out is part of Q3.
// =====================================================================

// Q3:  return the position of the first delivery by this farmer,
//      or -1 if the farmer is not in the log at all.
//
// int findFarmer(const vector<Delivery> &log, string name) {
//
// }

int findFarmer ( const vector<Delivery> log, string name){
        int i = 0;
        while (i < log.size()) {
            if (log[i].farmer == name){
                return i;
            }
            i++;
        }
        return -1;

}

double payment(double kg, char grade, double total_cost){    
    double payment= 450 * kg;
    if(total_cost < 100000){
        if(grade == 'A'){
            payment *= 1.1;
        }
        if(grade == 'C'){
            payment *= 0.8;
        }
        return payment;
    }
    else{
        if(grade == 'A'){
            payment *= 1.1;
        }
        if(grade == 'C'){
            payment *= 0.8;
        }
        return payment/2;
    }
}
// Q4:  what one delivery earns, before any cap is applied.
//      Grade A pays 10% above the rate, B pays the rate,
//      anything else pays 20% below it. The rate is 450.
//
// double payment(double kg, char grade) {
//
// }
