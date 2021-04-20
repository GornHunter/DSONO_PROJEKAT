#include<vector>

int checkIfSameResults(std::vector<int> voter){
    //int current = voter[0];
    //int index = 0;

    std::vector<int> v;

    for(int i = 0;i < voter.size();i++){
        if(voter[i] != -1)
            v.push_back(voter[i]);
    }

    int current = v[0];
    int index = 0;

    //posto TMR sistem moze prikriti najvise jedan kvar ukoliko se desi da ostanu 2 modula i oba proizvedu razlicite vrednosti simulacija se zavrsava jer
    //glasac ne moze utvrditi koji je tacan rezultat
    if(v.size() == 2){
        if(v[0] != v[1])
            return -2;
    }

    for (int i = 1; i < v.size(); i++) {
        if (current != v[i]) {
            if(i+1 <= v.size()-1){
                if(current != v[i+1])
                    return index + 1;
                    //found = current;
                else{
                    index = i;
                    current = v[i];
                }
            }
            else{
                if(index-1 >= 0){
                    if(current != v[index-1])
                        return index + 1;
                        //found = current;
                }
                else{
                    return i+1;
                    //found = current;
                }
            }
        }
    }

    return -1;
}