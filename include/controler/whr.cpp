#include <vector>
#include <iostream>

#define FVECTOR std::vector<float>
#define FMATRIX std::vector< FVECTOR >

#define INITIAL_PRIOR_WINS 0.5
#define HESSIAN_EPSILON 0.1 
#define LINK_STRENGTH 1000.0
#define Q 0.025

typedef struct SLU {
    FMATRIX L;
    FMATRIX U;
    void show() {
        std::cout << "Matrix L : " << std::endl;
        for (int i=0; i < L.size(); i++) {
            for (int j=0; j < L.size(); j++)
                std::cout << L[i][j] << " - ";
            std::cout << std::endl;
        }

        std::cout << "\nMatrix U : " << std::endl;
        for (int i=0; i < U.size(); i++) {
            for (int j=0; j < U.size(); j++)
                std::cout << U[i][j] << " - ";
            std::cout << std::endl;
        }
    }
    void show_product(bool inverse=false) {
        int n = L.size();
        FMATRIX H(n, FVECTOR(n)); 
        if (inverse) {
            FMATRIX tmp = L;
            L = U;
            U = tmp;
        } 

        for (int i=0; i < U.size(); i++) {
            for (int j=0; j < U.size(); j++)
                for (int k=0; k < U.size(); k++)
                    for (int g=0; g < U.size(); g++)
                        H[i][j] += L[i][k]*U[g][j]; 
        } 

        for (int i=0; i < H.size(); i++) {
            for (int j=0; j < H.size(); j++)
                std::cout << H[i][j] << " - ";
            std::cout << std::endl;
        }

        if (inverse) {
            FMATRIX tmp = L;
            L = U;
            U = tmp;
        } 
    }
} LU;

class Game {};
class Player {};

std::vector<Game> GetPlayerGames(int id) {
    return std::vector<Game>();
}

std::vector<Game> ComputeNaturalRating(std::vector<Game> gs) {
	return gs;
}

FMATRIX ComputeHessian(int id_player) {
    std::vector<Game> g;

    for (int i = 0; i < g.size(); ++i) {

    }
}

LU LU_decomposition(FMATRIX H) {
    int n = H.size();
    FMATRIX L(n, FVECTOR(n)); 
    FMATRIX U(n, FVECTOR(n));

    U[0][0] = H[0][0];
    U[0][1] = H[0][1];
    L[0][0] = 1;

    n--;
    for (int i = 1; i < n; i++) {
        L[i][i] = 1;
        L[i][i-1] = H[i][i-1]/U[i-1][i-1];
        U[i][i] = H[i][i] - L[i][i]*U[i-1][i];
        U[i][i] = H[i][i+1];
    }

    L[n][n-1] = H[n][n-1]/U[n-1][n-1];
    U[n][n] = H[n][n] - L[n][n]*U[n-1][n];

    LU ret;
    ret.L = L;
    ret.U = U;
    return ret;
}

LU UL_decomposition(FMATRIX H) {
    int n = H.size();
    FMATRIX L(n, FVECTOR(n)); 
    FMATRIX U(n, FVECTOR(n));

    n--;
    //std::cout << "L[" << n <<" ][ "<< n << "] - " << H[n][n] << std::endl;    
    L[n][n] = H[n][n];
    U[n][n] = 1;
    for (int i = n-1; i >= 0; --i) {
        //std::cout << "L[" << i <<" ][ "<< i+1 << "] - " << H[i][i+1] << std::endl;    
        L[i+1][i] = H[i+1][i];
        //std::cout << "L[" << i <<" ][ "<< i << "] - " << 1 << std::endl;    
        U[i][i] = 1;
        //std::cout << "U[" << i <<" ][ "<< i+1 << "] - " << H[i][i+1] << "/" << L[i+1][i+1] << std::endl;
        U[i][i+1] = H[i][i+1]/L[i+1][i+1];
        //std::cout << "L[" << i <<" ][ "<< i+1 << "] - " << H[i][i+1] << "-" << U[i][i+1] << "*" << L[i][i-1]<< std::endl;
        L[i][i] = H[i][i] - U[i][i+1]*L[i][i-1];
    }
    
    L[1][0] = H[0][0];

    LU ret;
    ret.L = L;
    ret.U = U;
    return ret;    
}


FVECTOR find_X(FVECTOR G, LU H) {
    int n = H.L.size();
    FVECTOR Y(n);
    Y[0] = G[0];

    for (int i = 0; i < n; ++i) {
        Y[i] = G[i]-H.L[i][i-1]*Y[i-1];
    }

    FVECTOR X(n);

    X[n] = Y[n] / H.U[n][n];
    n--;
    for (int i = n-1; i >= 0; --i) {
        X[i] = (Y[i] - H.L[i+1][i]*X[i+1])/H.L[i][i];
    }

    return X;
}

FVECTOR find_Xp(FVECTOR G, LU H) {
    int n = H.L.size();
    FVECTOR Y(n);
    Y[n] = G[n];

    for (int i = n-1; i > 0; ++i) {
        Y[i] = G[i]-H.U[i][i+1]*Y[i+1];
    }

    FVECTOR X(n);

    X[0] = Y[0] / H.U[n][n];
    n--;
    for (int i = n-1; i >= 0; --i) {
        X[i] = (Y[i] - H.L[i+1][i]*X[i+1])/H.L[i][i];
    }

    return X;    
}


int main() {
    FMATRIX H(10, FVECTOR(10));
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            H[i][j] = 0.1;
    LU ul = UL_decomposition(H);
    ul.show();
    ul.show_product(true);
    LU_decomposition(H); 
}