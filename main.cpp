#include <iostream>
#include <string>
using namespace std;

int main () {

//? M = (Q, sigma, gamma, EI, F, T)
//! -> CALCULA OS ESTADOS DA MAQUINA E SUAS REPRESENTACOES UNARIAS [x]
//* O array que armazena os estados unarios possui n+1 elementos, o elemento 0 é desconsiderado,
//* para possibilitar o acesso direto do estado n na posicao Q[n] do array de estados
    string dir[2] = {"1", "11"}; //* 1 = D, 2 = E
    int nQ = 0;
    while(nQ < 1 || nQ > 20) {
        cout << "Insira o numero de estados (ate 20) da maquina :" << endl;
        cin >> nQ;
    }

    string Q[nQ + 1] = {};

//# -> CRIA AS REPRESENTAÇÕES UNARIAS
    Q[0] = "x";
    for (size_t i = 1; i <= nQ; i++) {
            Q[i] = "1";
        for(int j = 1; j < i; j++) Q[i] = Q[i] + "1";
        cout << i  << " <==> " << Q[i] << endl;
    }

//! -> CALCULA O ALFABETO SIGMA E SUAS REPRESENTACOES UNARIAS [x] processar dps de ler gamma
    string str, sigma = "";
    bool repeated;
    cout << "Insira o alfabeto da maquina (apenas caracteres de 0-9 e a-z):" << endl;
    getchar();
    getline (cin, str);

//# -> VALIDA A FORMATACAO DA ENTRADA
    for (int i = 0; i < str.length(); i++) {
        repeated = false;
        if((i%2 == 1 && str[i] != ' ') || (i%2 == 0 && str[i] == ' ') || (isupper(str[i]))) {
            cout << "Formato incorreto";
            exit(0);
        }
        else if (isalnum(str[i])) {
            for( int j = 0; j < sigma.length(); j++) {
                    if (sigma[j] == str[i]) repeated = true;
            }
            if (repeated == false) {
                sigma += str[i];
            }
        }
    }
//# -> CALCULA A REPRESENTACAO UNARIA DO ALFABETO
    string sigmaR[sigma.length()];
    for(int i = 0; i < sigma.length(); i++) {
        sigmaR[i] = "1";
        for (int j = 0; j < i; j++) sigmaR[i] += "1";
        cout << sigma[i] << " " << sigmaR[i] << endl;
    }


//! -> CALCULA O ALFABETO DA FITA E SUAS REPRESENTACOES UNARIAS [x]
    str = "";
    string gamma = "";
    cout << "Insira o alfabeto da fita (apenas caracteres de A-Z):" << endl;
    getline(cin, str);

//# -> VALIDA A FORMATACAO DE ENTRADA
    for (int i = 0; i < str.length(); i++) {
//* -> O PRIMEIRO CARACTER DEVE SER O BETA ($)
        if (str[0] != '$') {
            cout << "Formato incorreto";
            exit(0);
        }
        else if (i == 0 ) {
            gamma += str[0];
            i++;
        }
        repeated = false;
        if(str[i] && ((i%2 == 1 && str[i] != ' ') || (i%2 == 0 && str[i] == ' ') || (islower(str[i]) && str[i] != '$'))) {
            cout << "Formato incorreto";
            exit(0);
        }
        else if (isalpha(str[i])) {
            for( int j = 0; j < gamma.length(); j++) {
                    if (gamma[j] == str[i]) repeated = true;
            }
            if (repeated == false) {
                gamma += str[i];
            }
        }
    }
//# -> CALCULA A REPRESENTACAO UNARIA DO ALFABETO DA FITA
 string gammaR[gamma.length()];
    for(int i = 0; i < gamma.length(); i++) {
        gammaR[i] = "1";
        for (int j = 0; j < i + sigma.length(); j++) gammaR[i] += "1";
        gammaR[i] += sigma[sigma.length()];
        cout << gamma[i] << " <-> " << gammaR[i] << endl;
    }

//! -> ESTADO INICIAL [x]
    int nEI = 0;
    cout << "Insira o estado inicial da maquina :" << endl;
    while (nEI < 1 || nEI > nQ) {
        cin >> nEI;
        getchar();
    }
    string EI = Q[nEI];
    cout << EI << endl;

//! -> ESTADOS FINAIS, DE 1 A Q [x]
    string sEF, EF, EFR, EA;
    bool multiple = false;
    int estadoAtual;
    cout << "Insira o(s) estado(s) final(is) da maquina: " << endl;
    getline(cin, sEF);
    for (int i = 0; i < sEF.length(); i++) {
        estadoAtual = 0;
        EA = "";
        if (isdigit(sEF[i])) {
            EA = sEF[i];
            if (i+1 <= sEF.length() && isdigit(sEF[i + 1])) {
                EA += sEF[i+1];
                i++;
            }
            estadoAtual = stoi(EA);
            cout << estadoAtual << endl;
            if (multiple) EFR += '0';
            for (size_t j = 0; j < estadoAtual; j++) {
                EFR += '1';
            }
        }
        else if (sEF[i] == ' ') {
            multiple = true;
        }
    }
    cout << EFR << endl;

//! -> NUMERO DE TRANSICOES DA MAQUINA [x]
    int nT = 0;
    cout << "Insira o numero de transicoes da maquina :" << endl;
    while (nT < 1 || nT > (nQ * sigma.length() * gamma.length())) {
        cin >> nT;
        getchar();
    }
    cout << nT << endl;

//! -> n TRANSICOES DA MAQUINA [x]
    string t, TR[nT], se;
    int k, epos, pe;
    for (size_t i = 0; i < nT; i++) {
        k = 0;
        cout << "Insira a transicao da maquina :" << endl;
        se = "";
        getline(cin, t);
//# -> ESTADO ATUAL
        if (isdigit(t[k])) {
            se = t[k];
            if (isdigit(t[k+1])) {
                se += t[k+1];
                k++;
            }  
            epos = stoi(se);
            TR[i] = Q[epos];
            k++;
        }
//# -> ESPAÇO
        if (t[k] == ' ') {
            TR[i] += '0';
            k++;
        }

//# -> SIMBOLO LIDO
        bool found = false;
        for (size_t j = 0; j < sigma.length(); j++) {
            if (found) break;
            if (t[k] == sigma[j]) {
                TR[i] += sigmaR[j];
                found = true;
            }
        }       
        
        if (!found) {
            for (size_t j = 0; j < gamma.length(); j++) {
                if (found) break;
                if (t[k] == gamma[j]) {
                    TR[i] += gammaR[j];
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "SL nao encontrado." << endl;
            exit(0);
        }
        else k++;

//# -> ESPAÇO
        if (t[k] == ' ') {
            TR[i] += '0';
            k++;
        }

//# -> PROXIMO ESTADO
        if (isdigit(t[k])) {
            se = t[k];
            if (isdigit(t[k+1])) {
                se += t[k+1];
                k++;
            }  
            epos = stoi(se);
            TR[i] += Q[epos];
            k++;
        }

//# -> ESPAÇO
        if (t[k] == ' ') {
            TR[i] += '0';
            k++;
        }

//# -> SIMBOLO ESCRITO
        found = false;
        for (size_t j = 0; j < sigma.length(); j++) {
            if (found) break;
            if (t[k] == sigma[j]) {
                TR[i] += sigmaR[j];
                found = true;
            }
        }       
        
        if (!found) {
            for (size_t j = 0; j < gamma.length(); j++) {
                if (found) break;
                if (t[k] == gamma[j]) {
                    TR[i] += gammaR[j];
                    found = true;
                }
            }
        }
        if (!found){
            cout << "SE nao encontrado." << endl;
            exit(0);
        }        
        else k++;

//# -> ESPAÇO
        if (t[k] == ' ') {
            TR[i] += '0';
            k++;
        }

//# -> DIREÇÃO
        if (t[k] == 'D') TR[i] += dir[0];
        else if (t[k] == 'E') TR[i] += dir[1];
        else {
            cout << "Direcao invalida! " << endl;
            exit(0);
        }
        cout << "transicao " << i << ": " << TR[i] << endl;
    }

//! -> OUTPUT []
//? M<R> = F 00 T<1> 00 T<2> 00...00 T<n>
string MR;
    MR = EFR;
    MR += "00";
    for (size_t i = 0; i < nT; i++) {
        MR += TR[i];
        if (i != nT - 1) MR += "00";
    }
    cout << MR << endl;
    return 0;
}