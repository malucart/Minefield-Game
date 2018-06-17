#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

const int MAX = 100;
//funções
void Campo_Inicial(char M[][MAX], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            M[i][j] = ' ';
        }
    }
}
char Contador_de_Minas(char M[][MAX], char A[][MAX], int x, int y)
{
    char cont = '0';
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
         {
            if(M[x+i][y+j] == 'B')
                cont++;
            if (A[x+i][y+j] == 'B')
                cont++;
         }
    }

    return cont;
}
void Imprimir_Campo(char M[][MAX], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if(M[i][j] == 'B')
            {
                cout << "[ ]";
            }
            else
                cout << "[" << M[i][j] << "]";
        }
        cout << endl;
    }
}
void Campo_Final(char M[][MAX], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
                cout << "[" << M[i][j] << "]";
        }
        cout << endl;
    }
}


int main ()
{
    //Leitura de arquivo
    ifstream arquivotxt;
    arquivotxt.open("arquivo.txt");
    //Aleatoriedade
    srand (time(NULL));
    //Declaração de variaveis relacionadas ao tempo
    clock_t inicio, fim;
    double tempo;
    //Declaração de variaveis
    char Matriz[MAX][MAX], Aux[MAX][MAX];
    int horizontal, vertical;
    int minas, x, y;
    int opcao;

    cout << "Escolha como quer jogar: \n (1) Jogador \n (2) Jogadores \n (3) Jogo por leitura TXT \n";
    cin >> opcao;
    //opções do usuario
    switch(opcao){
        case 1:
            horizontal = rand() % 20 + 1 ;
            vertical = rand() % 20 + 1;
            Campo_Inicial(Matriz, horizontal, vertical);
            minas = rand() % (horizontal*vertical) + 1;
            for (int i = 0; i < minas; i++){
                x = rand() % horizontal + 1;
                y = rand() % vertical + 1;
                Matriz[x-1][y-1] = 'B';
            }
            break;
        case 2:
            system("cls");
            cout << "JOGADOR OPONENTE" << endl;
            cout << "Informe a dimensao do campo: " << endl;
            cout << " Horizontal: ";
            cin >> horizontal;
            cout << " Vertical: ";
            cin >> vertical; cout << endl;


            Campo_Inicial(Matriz, horizontal, vertical);

            system("cls"); //Apaga a tela


            cout << "JOGADOR OPONENTE" << endl;
            cout << "informe quantas minas havera no campo: ";
            cin >> minas;

            while(minas >= (horizontal*vertical)){

                cout << "Quantidades de minas invalida, por favor, tente novamente: ";
                cin>>minas;
            }

            for(int i = 0; i < minas; i++){
                cout << "Informe a coordenada (x,y) da mina: " << endl;
                cout << "X: "; cin >> x;
                while(x > horizontal || x <= 0){
                    cout << "Coordenada X invalida, por favor, tente novamente: ";
                    cin>>x;
                }
                cout << "y: "; cin >> y;
                while(y > vertical || y <=0){
                    cout << "Coordenada Y invalida, por favor, tente novamente: ";
                    cin>>y;
                }

                if(Matriz[x-1][y-1] == 'B'){
                    cout << "Ja existe uma bomba nessa coordenada, tente novamente!  \n";
                    i--;
                    continue;
                }

                Matriz[x-1][y-1] = 'B';

            }

            break;
        case 3:
            arquivotxt >> horizontal;
            arquivotxt >> vertical;
            arquivotxt >> minas;
            for(int i = 0; i < minas; i++){
                arquivotxt >> x >> y;
                Matriz[x-1][y-1] = 'B';

            }
            break;
    }
    //Declaração de variaveis
    bool explodiu = false;
    char escolha;
    int tentativas = minas;
    //inicio da contagem de tempo
    inicio = clock();
    while(explodiu == false)
    {
        system("cls"); //Apaga a tela
        cout << "JOGADOR DESAFIANTE" << endl;

        Imprimir_Campo(Matriz,horizontal,vertical);

        cout << "Dimensao: " << horizontal << "x" << vertical << endl << "Tentativas: " << tentativas << endl;
        if(tentativas == 0){
            cout << "Suas tentativas acabaram, desmarque um possivel lugar de bomba\n";
        }
        cout << "Escolha qual acao deseja fazer \n (L) - Indicar um local como livre de mina \n (M) - Marcar um local como possivel local de mina \n (D) - Desmarcar possivel local de mina\n";
        cin >> escolha;

        switch (escolha){
            case 'L':
                cout << "Indique uma coordenada (x,y) para local livre de mina: \n";
                cout << "x: "; cin >> x; cout << "y: "; cin >> y;
                x--; y--;
                if (Matriz[x][y] == 'B'){
                    //fim da contagem de tempo
                    fim = clock();
                    Matriz[x][y] = '*';
                    explodiu = true;
                }
                else{
                    Matriz[x][y] = Contador_de_Minas(Matriz, Aux, x, y);
                }
                break;
            case 'M':

                if(tentativas == 0)
                   break;

                cout << "Indique uma coordenada (x,y) para possivel local de mina: \n";
                cout << "x: "; cin >> x; cout << "y: "; cin >> y;
                x--; y--;
                if (Matriz[x][y] == 'B'){
                    minas--;
                    tentativas--;
                    Aux[x][y] = 'B';
                    Matriz[x][y] = 'M';
                }
                else{
                    Matriz[x][y] = 'M';
                    tentativas--;
                }
                break;
            case 'D':
                cout << "Indique uma coordenada (x,y) para ser desmarcado como possivel local de mina: \n";
                cout << "x: "; cin >> x; cout << "y: "; cin >> y;
                x--; y--;
                if(Matriz[x][y] == 'M'){
                    if(Aux[x][y] == 'B'){
                        minas++;
                        tentativas++;
                        Matriz[x][y] = 'B';
                        Aux[x][y] = ' ';
                    }
                    else{
                        Matriz[x][y] = ' ';
                        tentativas++;
                    }
                }
                break;
        }
        if (minas == 0){
            //Fim da contagem de tempo
            fim = clock();
            break;
        }
    }
    system("cls");
    //TELA FINAL

    cout << "JOGADOR DESAFIANTE" << endl;
    Campo_Final(Matriz, horizontal, vertical);
    if(explodiu == true){
    cout << "JOGADOR DESAFIANTE PERDEU! \n";
    }
    else
        cout << "JOGADOR DESAFIANTE VENCEU! \n";
    //Calculo e impressão do tempo total em segundos
    tempo = (fim - inicio)/CLOCKS_PER_SEC;
    cout << "Tempo de conclusao: " << tempo << "s" << endl;

    return 0;
}
