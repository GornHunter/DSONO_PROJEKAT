class Comparator{
    public:
        Comparator();
        ~Comparator();
        bool checkIfEqual(int result1, int result2);
};

Comparator::Comparator(){}

Comparator::~Comparator(){}

bool Comparator::checkIfEqual(int result1, int result2){
    if(result1 != result2)
        return false;

    return true;
}