#include<iostream>

class Module
{
     private:
        int id;
        bool faulty;
    
    public:
        Module();
        Module(int id);
        Module(int id, bool faulty);
        ~Module();
        void setId(int id);
        int getId();
        void setFaulty(bool faulty);
        bool getFaulty();
        int doCalculation(std::vector<int> a, std::vector<int> b, int dim, int id, int option, bool fault);
};

Module::Module(){}

Module::Module(int id) : id(id){}

Module::Module(int id, bool faulty) : id(id), faulty(faulty){}

Module::~Module(){}

void Module::setId(int id){
    this->id = id;
}

int Module::getId(){
     return this->id;
}

void Module::setFaulty(bool faulty){
    this->faulty = faulty;
}

bool Module::getFaulty(){
    return this->faulty;
}

//u ovoj metodi moze se uraditi bilo koji vid proracuna - radi jednostavnosti sam uradio sabiranje da bi se moglo lakse pratiti
int Module::doCalculation(std::vector<int> a, std::vector<int> b, int dim, int id, int option, bool fault){
    std::vector<int> c = std::vector<int>();
    int retVal = 1;

    for(int i = 1;i <= (dim+1)*(dim+1);i++)
        c.push_back(i);

    if(!this->getFaulty()){
        for(int i = 0;i < dim+1;i++){
            for(int j = 0;j < dim+1;j++){
                c[i*(dim+1)+j] = a[i*(dim+1)+j] + b[i*(dim+1)+j]; 
            }
        }

        //ukoliko se desio kvar promenice se vrednost jednog elementa matrice
        if(fault)
            c[rand()%((dim+1)*(dim+1))] = 0;

        int sum = 0;
        int row;
        //provera da li redovi jednaki vektoru sabiranja redova
        for(int i = 0;i <= dim;i++){
            for(int j = 0;j < dim;j++){
                sum += c[i*(dim+1)+j];
            }
            int res = c[i*(dim+1)+dim];
            if(sum != res){
                row = i+1;
                break;
            }
            sum = 0;
        }

        //provera da li su kolone jednake vektoru sabiranja kolona
        //ukoliko se desi greska ispisuje se gde se desila(red i kolona)
        int column = 1;
        int cnt = 0;
        sum = 0;
        for(int i = 0;i <= dim;i++){
            for(int j = 0;j < dim;j++){
                sum += c[cnt];
                cnt += dim+1;
            }
            int n = c[(dim+1)*dim+i];
            if(sum != n){
                std::cout << "Error happened on intersection of row " + std::to_string(row) + " and column " + std::to_string(column) + " while adding 2 checksum matrices due to fault on module " + std::to_string(id) << std::endl;
                retVal = 0;
                break;
            }
            column++;
            cnt = 0;
            cnt += i+1;
            sum = 0;
        }
    }

    //ove provere su samo za regulisanje ispisa jer se ponekad desavalo da se ispise nesto sto ne bi trebalo
    if(!fault && this->getFaulty())
        retVal = -1;

    if(fault)
        c[0] = -1;

    if(option != 3 && retVal != -1 && !this->getFaulty())
        std::cout << "Module " + std::to_string(id) + ": Result of calculation between checksum matrices a and b is " + std::to_string(retVal) << std::endl;

    return retVal;
}