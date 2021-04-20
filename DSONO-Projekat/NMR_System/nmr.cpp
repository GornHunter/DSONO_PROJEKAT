#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<ctime>
#include<chrono>
#include<thread>
#include<algorithm>
#include "../Module/module.cpp"
#include "../FaultDetectionUnit/fd.cpp"
#include "../CheckResults/check_results.cpp"
#include "../GenerateCheckumMatrix/generateRowChecksumMatrix.cpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

vector<Module> loadModules(vector<Module> modules, int numOdModules){
    for(int i = 1;i <= numOdModules;i++){
        modules.push_back(Module(i, false));
    }

    return modules;
}


int checkResultsNMR(vector<int> voter){
    int res = checkIfSameResults(voter);

    int num;
    int cnt = 0;
    if(res != -1 && res != -2){
        for(int i = 0;i < voter.size();i++){
            if(voter[i] != -1)
                cnt++;
            if(cnt == res){
                num = i;
                break;
            }
        }
        return num+1;
    }

    return res;
}

int main(){
    srand((unsigned) time(0));

    //ulazni parametri
    vector<int> a;
    vector<int> b;

    int dim = 3;
    a = generateRowChecksumMatrix(a, dim);
    a = generateColumnChecksumMatrix(a, dim);

    b = generateRowChecksumMatrix(b, dim);
    b = generateColumnChecksumMatrix(b, dim);

    bool fault = false;
    //sansa da se kvar na modulu dogodi je 5%
    int chanceOfFault = 5;
    int numOfModules;

    vector<Module> modules = vector<Module>();
    vector<int> voter = vector<int>();

    while(1){
        std::cout << "How many modules will your system have? ";
        std::cin >> numOfModules;

        if(numOfModules >= 3)
            break;

        std::system(CLEAR);
        std::cout << endl;
        std::cout << "Number of modules must be greater or equal to 3." << endl;
    }

    modules = loadModules(modules, numOfModules);

    std::system("clear");

    std::cout << "Simulation is starting..." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));

    while(1){
        int cnt = 0;
        for(int i = 0;i < modules.size();i++){
            //ovaj if kaze da se tu toku izvrsavanja jedne for petlje samo sme desiti kvar na jednom modulu
            if(fault == false && cnt == 0){
                if((rand() % 100 + 1) <= chanceOfFault){
                    //rezultat kvara je promena vrednosti ulaza
                    //a = 2;
                    fault = true;
                    cnt++;
                }
            }

            if(!modules[i].getFaulty()){
                voter.push_back(modules[i].doCalculation(a, b, dim, modules[i].getId(), 1, fault));
                //posto se kvar dogodio na jednom modulu vracamo originalnu vrednost ulaza ostalim modulima
                //a = 5;
            }
            else
                voter.push_back(modules[i].doCalculation(a, b, dim, modules[i].getId(), 1, fault));
                
            fault = false;
        }

        fault = false;
        std::cout << "--------------------------------------------------------------" << endl;

        //provera da li su primljeni rezultati jednaki. Ako nisu pronadji modul koji je kvaran i maskiraj rezultat
        int res = checkResultsNMR(voter);
        if(res != -1 && res != -2){
            std::cout << "Fault has been discovered on module " + to_string(res) + " so it's result has been masked." << endl;
            //postavljamo modul sa pogresnim rezultatom kao kvaran
            modules[res-1].setFaulty(true);

            vector<int> v;
            for(int i = 0;i < voter.size();i++){
                if(voter[i] != -1)
                    v.push_back(voter[i]);
            }

            if(v[0] != v[1] && v[0] != v[2])
                std::cout << "System output is " + to_string(v[1]) << endl;
            else
                std::cout << "System output is " + to_string(v[0]) << endl;
        }
        else if(res == -2){
            std::cout << "Simulation is ending because there are 2 modules left and both have produced different results so the voter can't determine which one is true." << endl << endl;
            break;
        }
        else{
            vector<int> v;
            for(int i = 0;i < voter.size();i++){
                if(voter[i] != -1)
                    v.push_back(voter[i]);
            }

            std::cout << "System output is " + to_string(v[0]) << endl;
        }

        char c;
        std::cout << endl;
        std::cout << "Do you want to continued with the simualtion?(y/n) ";
        std::cin >> c;
        if(c == 'y' || c == 'Y'){
            std::system("clear");

            voter.clear();
            std::cout << endl;

            continue;
        }
        else{
            break;
        }
    }

    return 0;
}