class FD{
    public:
        FD();
        ~FD();
        bool faultDetected(bool fault);
};

FD::FD(){}

FD::~FD(){}

bool FD::faultDetected(bool fault){
    if(fault)
        return true;
    
    return false;
}