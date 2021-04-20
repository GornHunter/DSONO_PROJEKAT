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
#include "../Comparator/comparator.cpp"
#include "../CheckResults/check_results.cpp"
#include "../GenerateCheckumMatrix/generateRowChecksumMatrix.cpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

vector<Module> loadModules(vector<Module> modules, int numOdModules, int option){
    for(int i = 1;i <= numOdModules;i++){
        if(option == 1 || option == 3)
            modules.push_back(Module(i, false));
        else if(option == 2)
            modules.push_back(Module(i));
    }

    return modules;
}

int checkIfSameResultsTD(vector<int> voter){
    //-1 vrednost u voteru znaci da postoji kvar na paru modula i da taj par ne ucestvuju i glasanju
    int i = count(voter.begin(), voter.end(), -1);
    if(i == 1){
        if(voter[0] == -1){
            if(voter[1] != voter[2])
                return -2;
        }
        else if(voter[1] == -1){
            if(voter[0] != voter[2])
                return -2;
        }
        else if(voter[2] == -1){
                if(voter[0] != voter[1])
                    return -2;
        }
    }
    else if(i == 2){
        return -3;
    }
    else{
        return checkIfSameResults(voter);
    }

    return -1;
}

int main(){
    srand((unsigned) time(0));

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
    //sansa da se modul popravi je 10%
    int chanceOfRepair = 10;
    int numOfModules = 6;

    vector<Module> modules = vector<Module>();

    vector<int> voter = vector<int>();
    Comparator comparator;
    vector<Module> pair1 = vector<Module>();
    vector<Module> pair2 = vector<Module>();
    vector<Module> pair3 = vector<Module>();

    modules = loadModules(modules, numOfModules, 3);

    //razvrstavamo module u 3 para
    pair1.push_back(modules[0]);
    pair1.push_back(modules[1]);

    pair2.push_back(modules[2]);
    pair2.push_back(modules[3]);

    pair3.push_back(modules[4]);
    pair3.push_back(modules[5]);

    std::system("clear");

    std::cout << "Simulation is starting..." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));

    int resSS;

    int res1a;
    int res1b;

    int res2a;
    int res2b;

    int res3a;
    int res3b;

    while(1){
        int rng = (rand() % 100 + 1);
        if(rng <= chanceOfFault){
            fault = true;

            //ovde su pokrivene razlicite kombinacije gde se kavar moze javiti(na jednom, drugom ili oba modula za svaki od tri para modula)
            if(rng == 1){
                if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                    rng = (rand() % 3 + 1);
                    if(rng == 1){
                        res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                        fault = false;
                        res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
                    }
                    else if(rng == 2){
                        res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
                        fault = false;
                        res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                    }
                    else{
                        res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                        res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
                        fault = false;
                    }
                }

                fault = false;
                if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                    res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                    res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
                }

                if(!pair3[0].getFaulty() && !pair3[1].getFaulty()){
                    res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                    res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
                }
            }
            else if(rng == 2 || rng == 3){
                if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                    rng = (rand() % 3 + 1);
                    if(rng == 1){
                        res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                        fault = false;
                        res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
                    }
                    else if(rng == 2){
                        res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
                        fault = false;
                        res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                    }
                    else{
                        res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                        res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
                        fault = false;
                    }
                }

                fault = false;
                if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                    res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                    res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
                }

                if(!pair3[0].getFaulty() && !pair3[1].getFaulty()){
                    res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                    res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
                }
            }
            else if(rng == 4 || rng == 5){
                if(!pair3[0].getFaulty() && !pair3[1].getFaulty()){
                    rng = (rand() % 3 + 1);
                    if(rng == 1){
                        res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                        fault = false;
                        res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
                    }
                    else if(rng == 2){
                        res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
                        fault = false;
                        res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                    }
                    else{
                        res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                        res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
                        fault = false;
                    }
                }

                fault = false;
                if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                    res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                    res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
                }

                if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                    res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                    res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
                }
            }
        }
        else{
            fault = false;

            if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                res1a = pair1[0].doCalculation(a, b, dim, pair1[0].getId(), 3, fault);
                res1b = pair1[1].doCalculation(a, b, dim, pair1[1].getId(), 3, fault);
            }

            if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                res2a = pair2[0].doCalculation(a, b, dim, pair2[0].getId(), 3, fault);
                res2b = pair2[1].doCalculation(a, b, dim, pair2[1].getId(), 3, fault);
            }

            if(!pair3[0].getFaulty() && !pair3[1].getFaulty()){
                res3a = pair3[0].doCalculation(a, b, dim, pair3[0].getId(), 3, fault);
                res3b = pair3[1].doCalculation(a, b, dim, pair3[1].getId(), 3, fault);
            }
        }

        
        if(!pair1[0].getFaulty() && !pair1[1].getFaulty())
            std::cout << "Pair 1(modules " + to_string(pair1[0].getId()) + " and " + to_string(pair1[1].getId()) + "): Results of calculation between checksum matrices a and b are " + to_string(res1a) + " and " + to_string(res1b) << endl;

        if(!pair2[0].getFaulty() && !pair2[1].getFaulty())
            std::cout << "Pair 2(modules " + to_string(pair2[0].getId()) + " and " + to_string(pair2[1].getId()) + "): Results of calculation between checksum matrices a and b are " + to_string(res2a) + " and " + to_string(res2b) << endl;

        if(!pair3[0].getFaulty() && !pair3[1].getFaulty())
            std::cout << "Pair 3(modules " + to_string(pair3[0].getId()) + " and " + to_string(pair3[1].getId()) + "): Results of calculation between checksum matrices a and b are " + to_string(res3a) + " and " + to_string(res3b) << endl;

        std::cout << "--------------------------------------------------------------" << endl;

        //do glasaca dolazi po jedan rezultat iz svakog para modula
        voter.push_back(res1a);
        voter.push_back(res2a);
        voter.push_back(res3a);

        //proverava se da li se vrednosti unutar svaakog para razlikuju ili ne(ukoliko se razlikuju taj par ne ucestvuje u glasanju)
        if(!comparator.checkIfEqual(res1a, res1b)){
            if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                    if(res1a != res2a){
                        pair1[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair1[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res1b != res2a){
                        pair1[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair1[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
                else{
                    if(res1a != res3a){
                        pair1[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair1[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res1b != res3a){
                        pair1[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair1[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
            }
            voter.erase(voter.begin());
            voter.insert(voter.begin(), -1);
        }
        if(!comparator.checkIfEqual(res2a, res2b)){
            if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                if(!pair1[0].getFaulty() && !pair1[1].getFaulty()){
                    if(res2a != res1a){
                        pair2[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair2[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res2b != res1a){
                        pair2[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair2[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
                else{
                    if(res2a != res3a){
                        pair2[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair2[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res2b != res3a){
                        pair2[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair2[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
            }
            voter.erase(voter.begin()+1);
            voter.insert(voter.begin()+1, -1);
        }
        if(!comparator.checkIfEqual(res3a, res3b)){
            if(!pair3[0].getFaulty() && !pair3[1].getFaulty()){
                if(!pair2[0].getFaulty() && !pair2[1].getFaulty()){
                    if(res3a != res2a){
                        pair3[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair3[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res3b != res2a){
                        pair3[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair3[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
                else{
                    if(res3a != res1a){
                        pair3[0].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair3[0].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                    else if(res3b != res1a){
                        pair3[1].setFaulty(true);
                        std::cout << "Comparator dsicovered fault on module " + to_string(pair3[1].getId()) + " so the value of whole pair isn't accounted into final voting." << endl;
                    }
                }
            }
            voter.erase(voter.begin()+2);
            voter.insert(voter.begin()+2, -1);
        }
        else{
        }

        //std::cout << "Voter: " << to_string(voter[0]) + " " + to_string(voter[1]) + " " + to_string(voter[2]) << endl;

        //glasac proverava da li su primljene vrednosti od svih parova jednake ili ne(ukoliko neka nije jednaka taj par modula se proglasava neispravnim)
        int res = checkIfSameResultsTD(voter);
        if(res != -1 && res != -2 && res != -3){
            std::cout << "Voter discovered fault on pair " + to_string(res) + " so the result is being masked." << endl;

            if(res == 1){
                pair1[0].setFaulty(true);
                pair1[1].setFaulty(true);
                res1a = -1;
                res1b = -1;
                std::cout << "System output is " + to_string(voter[1]) << endl;
            }
            else if(res == 2){
                pair2[0].setFaulty(true);
                pair2[1].setFaulty(true);
                res2a = -1;
                res2b = -1;
                std::cout << "System output is " + to_string(voter[0]) << endl;
            }
            else if(res == 3){
                pair3[0].setFaulty(true);
                pair3[1].setFaulty(true);
                res3a = -1;
                res3b = -1;
                std::cout << "System output is " + to_string(voter[0]) << endl;
            }
            else{
            }
        }
        else if(res == -2){
            std::cout << "Simulation is ending because there are 2 pairs left and both have produced different results so the voter can't determine which one is true." << endl << endl;
            break;
        }
        else if(res == -3){
            std::cout << "Simulation is ending becasue there are faults on 2 pair of modules and voter can't determine if the remaining's pair result is true or not." << endl << endl;
            break;
        }
        else{
            if(voter[0] != -1)
                std::cout << "System output is " + to_string(voter[0]) << endl;
            else
                std::cout << "System output is " + to_string(voter[1]) << endl;
        }

        char c;
        std::cout << endl;
        std::cout << "Do you want to continued with the simualtion?(y/n) ";
        std::cin >> c;
        if(c == 'y' || c == 'Y'){
            std::system(CLEAR);

            //ukoliko je neki modul kvaran postoji sansa da se popravi
            int rng = (rand() % 100 + 1);
            if(rng <= chanceOfRepair){
                if(pair1[0].getFaulty()){
                    std::cout << "Module " + to_string(pair1[0].getId()) + " is fixed and back in function." << endl;
                    pair1[0].setFaulty(false);
                }
                if(pair1[1].getFaulty()){
                    std::cout << "Module " + to_string(pair1[1].getId()) + " is fixed and back in function." << endl;
                    pair1[1].setFaulty(false);
                }
            }

            rng = (rand() % 100 + 1);
            if(rng <= chanceOfRepair){
                if(pair2[0].getFaulty()){
                    std::cout << "Module " + to_string(pair2[0].getId()) + " is fixed and back in function." << endl;
                    pair2[0].setFaulty(false);
                }
                if(pair2[1].getFaulty()){
                    std::cout << "Module " + to_string(pair2[1].getId()) + " is fixed and back in function." << endl;
                    pair2[1].setFaulty(false);
                }
            }

            rng = (rand() % 100 + 1);
            if(rng <= chanceOfRepair){
                if(pair3[0].getFaulty()){
                    std::cout << "Module " + to_string(pair3[0].getId()) + " is fixed and back in function." << endl;
                    pair3[0].setFaulty(false);
                }
                if(pair3[1].getFaulty()){
                    std::cout << "Module " + to_string(pair3[1].getId()) + " is fixed and back in function." << endl;
                    pair3[1].setFaulty(false);
                }
            }

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