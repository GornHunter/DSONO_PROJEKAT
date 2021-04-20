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

int main(){
    srand((unsigned) time(0));

    //ulazni parametri
    vector<int> a;
    vector<int> b;

    //dimenzije matrice(mora biti kvadratna matrica)
    int dim = 3;
    a = generateRowChecksumMatrix(a, dim);
    a = generateColumnChecksumMatrix(a, dim);

    b = generateRowChecksumMatrix(b, dim);
    b = generateColumnChecksumMatrix(b, dim);

    bool fault = false;
    //sansa da se kvar na modulu dogodi je 5%
    int chanceOfFault = 5;
    //sansa da se modul popravi je 10%
    int chanceOfRepair = 10;
    int numOfModules;

    vector<Module> modules = vector<Module>();

    //prekidac(na kome ce biti smesten aktivni modul - module koji vrsi proracune)
    vector<Module> switchSS = vector<Module>();
    vector<Module> redundatnModules = vector<Module>();
    vector<Module> faultyModules = vector<Module>();
    Module activeModule;
    FD faultDetectionUnit;

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

    //kazemo da je prvi modul aktivni modul a ostali redundantni
    activeModule = modules[0];
    for(int i = 1;i < modules.size();i++){
        redundatnModules.push_back(modules[i]);
    }
    switchSS.push_back(activeModule);

    system("clear");

    std::cout << "Simulation is starting..." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));

    int res;

    while(1){
        if(fault == false){
            if((rand() % 100 + 1) <= chanceOfFault){
                fault = true;
            }
        }

        res = activeModule.doCalculation(a, b, dim, activeModule.getId(), 2, fault);

        //ukoliko FD otkrije kvar na modulu taj modul se iskljucuje iz sistema dok se ne popravi
        if(faultDetectionUnit.faultDetected(fault)){
            //ukoliko ostane jos jedan redundantan modul sistem ce nastaviti racunaje. Ako se na zadnjem modulu dogodi kvar sistem prestaje da radi.
            if(redundatnModules.size() >= 1){
                std::cout << "FD unit detected fault on module " + to_string(activeModule.getId()) + " and switch removed that module and replaced it with new module." << endl;
                    
                //ako se dogodi kvar na jednom od modula prekidac ga uklanja(nije vise kativan) i zamenjuje ga redundantnim modulom(on se onda proglasava aktivnim)
                faultyModules.push_back(activeModule);
                switchSS.clear();
                activeModule = redundatnModules[0];
                switchSS.push_back(activeModule);
                redundatnModules.erase(redundatnModules.begin());
            }
            else{
                std::cout << "Simulation is ending since fault happened on module " + to_string(activeModule.getId()) + " and there are no more redundant modules to replace it with." << endl << endl;
                break;
            }
        }

        //res = activeModule.doCalculation(a, b, dim, activeModule.getId(), 2, fault);

        fault = false;
        std::cout << "--------------------------------------------------------------" << endl;

        std::cout << "System output is " + to_string(res) << endl;

        char c;
        std::cout << endl;
        std::cout << "Do you want to continued with the simualtion?(y/n) ";
        std::cin >> c;
        if(c == 'y' || c == 'Y'){
            std::system("clear");

            //ukoliko se popravi kvaran modul vrati ga u funkciju i smesti u redundantne module
            if(faultyModules.size() > 0){
                //sansa da se kvaran modul popravi
                if((rand() % 100 + 1) <= chanceOfRepair){
                    std::cout << endl;
                    std::cout << "Module " + to_string(faultyModules[0].getId()) + " has been repaired and is back in function." << endl;
                    redundatnModules.push_back(faultyModules[0]);
                    faultyModules.erase(faultyModules.begin());
                }
            }

            continue;
        }
        else{
            break;
        }
    }

    return 0;
}