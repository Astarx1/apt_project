#define FVECTOR std::vector<float>
#define FMATRIX std::vector< FVECTOR >


typedef struct SLU {
    FMATRIX L;
    FMATRIX U;
} LU;

class PlayerUpdated : Player {
public:
    std::map<int, Game> games;
}

class championship {
public:
std::map<int, PlayerUpdated> participant; 
}



int main() {
}