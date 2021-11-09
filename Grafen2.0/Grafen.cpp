// Grafen.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream> 


using namespace std;
int main()
{
    ofstream GrafLMP, GrafXYZ;
    const double PI = 3.14159265;
    double ALPHA, DELTA, dx, dy, R, r, xmax, ymax, fxmax, fxmin, fymax, fymin, fzmax, fzmin, xx,n,yymax,xxmax,Tx,Ty;
    int k = 1, k1, l, T, k2, J, k3, k4 = 0, m = 0, yy, b, IJ[10000][2], kp, jj,PL1T[10000], PL3T[10000],PL4T[20000];
    bool Fl1 = true, Fl2, PF = false, Fl3,Fl4;
    char c;
    char* locale = setlocale(LC_ALL, "");
    double N, N2;
    cout << "Введите размер пластины" << endl;
    cin >> N;
    float PL1[10000][4], PL3[10000][4], PL4[20000][4];
    bool PL11[10000], PL33[10000];

    PL1[0][1] = 0.0;
    PL1[0][2] = 0.0;
    PL1[0][3] = 0.0;
    PL1[1][3] = 0.0;
    l = 0;

    //Создание первой пластины графена
    xmax = PL1[0][1];
    ymax = PL1[0][2];
    T = 2 * N;
    while (PL1[k][2] < N)
    {
        for (int i = k - 1; PL1[i][1] < N; i++)
        {

            if (Fl1 == true)
            {

                if (PL1[i][1] == 0)
                {
                    k = k + 1;
                    PL1[i + 1][1] = PL1[i][1] + 2 * 1.42;
                    Fl1 = false;
                }
                else
                {
                    k = k + 1;
                    PL1[i + 1][1] = PL1[i][1] + 1.42;
                    Fl1 = false;
                }
            }

            else
            {
                if (PL1[i][1] - PL1[i - 1][1] > 1.43)
                {
                    PL1[i + 1][1] = PL1[i][1] + 1.42;
                    k = k + 1;

                }
                else
                {
                    PL1[i + 1][1] = PL1[i][1] + 2 * 1.42;
                    k = k + 1;

                }
            }
            PL1[i + 1][2] = PL1[i][2];
            if (xmax < PL1[i + 1][1])
            {
                xmax = PL1[i + 1][1];
                xxmax = xmax;
            }
            if (PL1[i + 1][1] - N > 2.13)
            {
                k = k - 1;
                break;
            }
        }
        if (PL1[k-1][2] == 0)
        {
            m = k;
        }
        T = k - l;
        Fl1 = true;
        PL1[k][2] = PL1[k - 1][2] + sqrt(3) * 1.42 * 0.5;

        if (PL1[k][2] > ymax)
        {
            ymax = PL1[k][2];
            yymax = ymax;
        }

        if (PL1[k][2] > N)
        {
            ymax = PL1[k - 1][2];
            break;

        }

        if (PL1[k - T][1] == 0)
        {
            PL1[k][1] = 1.42 * 0.5;
        }
        else
        {
            PL1[k][1] = 0;
        }
        l = k;
        k = k + 1;

    }




    for (int i = 0; i < k; i++)
    {
        PL1[i][0] = i + 1;
    }

    for (int i = 0; i < k; i++)
    {
        PL1[i][3] = 0;
        PL1T[i] = 1;
    }

    k1 = k;
    cout << endl;

    //Создание второй пластины графена
    

    for (int i = 0; i < k; i++)
    {
        PL3[i][1] = PL1[i][1];
        PL3[i][2] = PL1[i][2];

    }

    for (int i = 0; i < k; i++)
    {
        PL3[i][0] = k1 + 1 + i;
    }

    for (int i = 0; i < k; i++)
    {
        PL3[i][3] = 3.33;
    }



    
    //Смещение оси вращения в центры пластин

    cout << "Поворот будет осуществляться относительно 1) центра шестиугольника(введите '1') или 2) атома (введите '2')? :" << endl;
    cin >> c;
    cout << endl;
    if ((c !='1') and (c != '2'))
    {
       
        while (true)
        {
            cout << "Ошибка! Нет такого варианта. Поворот будет осуществляться относительно 1) центра шестиугольника(введите '1') или 2) атома (введите '2')?:" << endl;
            cin >> c;
            cout << endl;
            if ((c == '1') or (c == '2'))
            {
                break;
            }
        }

    }

    if (c == '2')
    {
        xmax = PL1[m / 2][1];
        b = 0;
        while (PL1[b][2] < ymax / 2)
        {
            b = b + T;
        }
        if (PL1[b][1] == 0)
        {
            ymax = PL1[b][2];
        }
        else
        {
            for (int i = b; i < k; i++)
            {
               
                if (PL1[i][1] == 0)
                {
                    ymax = PL1[i][2];
                    break;
                }
            }
        }
    }
    if (c == '1')
    {
        if (PL1[m / 2][1] - (PL1[m / 2 - 1][1])<1.43)
        {
            xmax = PL1[m / 2][1]+1.42;
        }
        else
        {
            xmax= PL1[m / 2][1]-1.42;
        }
        b = 0;
        while (PL1[b][2] < ymax / 2)
        {
            b = b + T;
        }
        if (PL1[b][1] == 0)
        {
            ymax = PL1[b][2];
        }
        else
        {
            for (int i = b; i < k; i++)
            {
                
                if (PL1[i][1] == 0)
                {
                    ymax = PL1[i][2];
                    break;
                }
            }
        }

    }




    /*
    xx = 0;
    yy = 0;
    n = xmax / 1.42;
    m = 1;
    while (xx< xmax/2.84)
    {
        xx = xx + 1.5 + 0.5 * pow(-1, m-1);
        m = m + 1;
        
    }
    xmax = xx * 1.42;

    while (yy < ymax / (1.42 * sqrt(3)))
    {
        yy = yy + 2;
    }
    ymax = yy * (1.42 * sqrt(3))/2;
    */

    for (int i = 0; i < k1; i++)
    {
        PL1[i][1] = PL1[i][1] - xmax;
        PL1[i][2] = PL1[i][2] - ymax;
        PL3[i][1] = PL3[i][1] - xmax;
        PL3[i][2] = PL3[i][2] - ymax;
    }
    



    //Задание поворота второй пластины графена относительно оси OZ
    cout << "Задайте угол поворота" << endl;
    cin >> ALPHA;
    fxmin = PL1[0][1];
    fxmax = PL1[0][1];
    fymin = PL1[0][2];
    fymax = PL1[0][2];
    for (int i = 0; i < k; i++)
    {
        Tx = PL3[i][1];
        Ty = PL3[i][2];
        PL3[i][0] = k1 + i + 1;
        PL3[i][1] = Tx * cos(ALPHA * PI / 180) - Ty * sin(ALPHA * PI / 180);
        PL3[i][2] = Tx * sin(ALPHA * PI / 180) + Ty * cos(ALPHA * PI / 180);
       // PL3[i][3] = PL3[i][3];
        PL3T[i] = 1;
        k3 = PL3[i][0];
        if (PL3[i][1] > fxmax)
        {
            fxmax = PL3[i][1];
        }

        if (PL3[i][1] < fxmin)
        {
            fxmin = PL3[i][1];
        }

        if (PL3[i][2] > fymax)
        {
            fymax = PL3[i][2];
        }

        if (PL3[i][2] < fymin)
        {
            fymin = PL3[i][2];
        }
    }

    cout << endl;


    //Поиск близких атомов

    for (int i = 0; i < k1; i++)
    {
        PL11[i] = false;
        PL33[i] = false;
    }

    cout << "Введите расстояние между атомами С и Н" << endl;
    cin >> r;
    cout << endl;
    J = 0;
    cout << "Задайте погрешность" << endl;
    cin >> DELTA;
    kp = 0;
    for (int i = 0; i < k1; i++)
    {
        for (int j = 0; j < k1; j++)
        {
            dx = abs(PL3[i][1] - PL1[j][1]);
            dy = abs(PL3[i][2] - PL1[j][2]);
            R = sqrt(pow(dx, 2) + pow(dy, 2));
            if (R <= DELTA)
            {
                IJ[kp][0] = i;
                IJ[kp][1] = j;
                kp = kp + 1;
                PL11[j] = true;
                PL33[i] = true;
                break;

            }
        }
    }
    /*
    for (int i = 0; i < k1; i++)
    {
        for (int j = 0; j < k1; j++)
        {
            dx = abs(PL3[i][1] - PL1[j][1]);
            dy = abs(PL3[i][2] - PL1[j][2]);
            R = sqrt(pow(dx, 2) + pow(dy, 2));
            if (R <= DELTA)
            {
                IJ[kp][0] = i;
                IJ[kp][1] = j;
                kp = kp + 1;
                PL11[j] = true;
                PL33[i] = true;
                break;

            }
        }
    }

    */
    
    Fl3 = false;
    Fl4 = false;
    for (int i = 0; i < k1; i++)
    { 
        if (PL11[i] == true)
        {
            if ((PL1[i][1] != PL1[0][1]) and (PL1[i][1] != PL1[T - 1][1]) and (PL1[i][1] != PL1[T][1]) and (PL1[i][1] != PL1[2*T-1][1]))
            {
                if ((PL1[i][2] != PL1[0][2]) and (PL1[i][2] != PL1[k1][2]))
                {
                    PL11[i + T] = false;
                    PL11[i - T] = false;
                }
                else
                {
                    if (PL1[i][2] == PL1[0][2])
                    {
                        PL11[i + T] = false;
                    }
                    if (PL1[i][2] == PL1[k1][2])
                    {
                        PL11[i - T] = false;
                    }
                }
                if (PL1[i + 1][1] - PL1[i][1] < 1.44)
                {
                    PL11[i + 1] = false;
                }
                else
                {
                    PL11[i - 1] = false;
                }
            }
            else 
            {
                /*
                if (PL1[i][1] == PL1[0][1])
                {
                    if ((PL1[i][2] != PL1[0][2]) and (PL1[i][2] != PL1[k1][2]))
                    {
                        PL11[i + T] = false;
                        PL11[i - T] = false;
                    }
                    else
                    {
                        if (PL1[i][2] == PL1[0][2])
                        {
                            PL11[i + T] = false;
                        }
                        if (PL1[i][2] == PL1[k1][2])
                        {
                            PL11[i - T] = false;
                        }
                    }
                }
                */
                if(PL1[i][1] == PL1[T - 1][1])
                {
                    if ((PL1[i][2] != PL1[0][2]) and (PL1[i][2] != PL1[k1][2]))
                    {
                        PL11[i + T] = false;
                        PL11[i - T] = false;
                    }
                    else
                    {
                        if (PL1[i][2] == PL1[0][2])
                        {
                            PL11[i + T] = false;
                        }
                        if (PL1[i][2] == PL1[k1][2])
                        {
                            PL11[i - T] = false;
                        }
                    }

                    if (PL1[i][1] - PL1[i-1][1] < 1.44)
                    {
                        PL11[i - 1] = false;
                    }
                }
                if (PL1[i][1] == PL1[T][1])
                {
                    if ((PL1[i][2] != PL1[0][2]) and (PL1[i][2] != PL1[k1][2]))
                    {
                        PL11[i + T] = false;
                        PL11[i - T] = false;
                    }
                    else
                    {
                        if (PL1[i][2] == PL1[0][2])
                        {
                            PL11[i + T] = false;
                        }
                        if (PL1[i][2] == PL1[k1][2])
                        {
                            PL11[i - T] = false;
                        }
                    }
                    PL11[i + 1] = false;
                }
                if (PL1[i][1] == PL1[2 * T - 1][1])
                {
                    if ((PL1[i][2] != PL1[0][2]) and (PL1[i][2] != PL1[k1][2]))
                    {
                        PL11[i + T] = false;
                        PL11[i - T] = false;
                    }
                    else
                    {
                        if (PL1[i][2] == PL1[0][2])
                        {
                            PL11[i + T] = false;
                        }
                        if (PL1[i][2] == PL1[k1][2])
                        {
                            PL11[i - T] = false;
                        }
                    }
                    
                    if (PL1[i][1] - PL1[i - 1][1] < 1.44)
                    {
                        PL11[i - 1] = false;
                    }

                }

            }

        }
        
    }
    
    jj = 0;
    for (int i = 0; i < k1; i++)
    {
        for (int j =0 ; j < kp; j++)
        {
            if (i == IJ[j][1])
            {
                if (PL11[i] == false)
                {
                    PL33[IJ[j][0]] = false;
                }
                //jj = jj + 1;
            }
        }
    }
    
    for (int i = 0; i < k1; i++)
    {
        if (PL11[i] == false)
        {
            PL4[i][1] = PL1[i][1];
            PL4[i][2] = PL1[i][2];
            PL4[i][3] = PL1[i][3] - r;
            PL4[i][0] = k3 + J + 1;
            PL4T[i] = 2;
            J = J + 1;
            k4 = k4 + 1;
        }
        else
        {
            
            PL1[i][3] = PL1[i][3] + 0.95;
            PL4[i][3] = -909909;
        }


    }

    for (int i = k1; i < 2 * k1; i++)
    {
        if (PL33[i-k1] == false)
        {
            PL4[i][1] = PL3[i - k1][1];
            PL4[i][2] = PL3[i - k1][2];
            PL4[i][3] = PL3[i - k1][3] + r;
            PL4[i][0] = k3 + J + 1;
            PL4T[i] = 2;
            J = J + 1;
            k4 = k4 + 1;
        }
        else
        {
            
            PL3[i-k1][3] = PL3[i-k1][3] - 0.95;
            PL4[i][3] = -909909;
        }
    }



    fzmin = -50;
    fzmax = 50;


    GrafXYZ.open("GrafXYZ.xyz");

    GrafXYZ << 2 * k + k4 << endl;
    GrafXYZ << "#XYZ format" << endl; // запись результатов в файл в формате XYZ

    for (int i = 0; i < k; i++)
    {
        //GrafXYZ << PL1T[i] << "     ";
        GrafXYZ << "C" << "     ";
        for (int j = 1; j < 4; j++)
        {
            GrafXYZ << PL1[i][j] << "     ";
        }
        GrafXYZ << endl;
    }

    for (int i = 0; i < k; i++)
    {
        //GrafXYZ << PL3T[i] << "     ";
        GrafXYZ << "C" << "     ";
        for (int j = 1; j < 4; j++)
        {
            GrafXYZ << PL3[i][j] << "     ";
        }
        GrafXYZ << endl;
    }

    for (int i = 0; i < 2 * k; i++)
    {

        if (PL4[i][3] != -909909)
        {
            //GrafXYZ << PL4T[i] << "     ";
            GrafXYZ << "H" << "     ";
        }
        for (int j = 1; j < 4; j++)
        {
            if (PL4[i][3] != -909909)
            {

                GrafXYZ << PL4[i][j] << "     ";
            }

        }
        if (PL4[i][3] != -909909)
        {
            GrafXYZ << endl;
        }

    }


    GrafXYZ.close();


    GrafLMP.open("GrafLMP"); // запись результатов в файл в формате LAMMPS
    GrafLMP << "#Lammps format" << endl;
    GrafLMP << 2 * k + k4 << " atoms" << endl;
    GrafLMP << endl;
    GrafLMP << "2 atom types" << endl;
    GrafLMP << fxmin << " " << fxmax << " " << "xlo " << "xhi" << endl;
    GrafLMP << fymin << " " << fymax << " " << "ylo " << "yhi" << endl;
    GrafLMP << fzmin << " " << fzmax << " " << "zlo " << "zhi" << endl;
    GrafLMP << endl;
    GrafLMP << "Atoms #atomic" << endl;
    GrafLMP << endl;

    for (int i = 0; i < k; i++)
    {
        GrafLMP << PL1[i][0] << " ";
        GrafLMP << PL1T[i] << " ";

        for (int j = 1; j < 4; j++)
        {
            GrafLMP << PL1[i][j] << " ";
        }
        GrafLMP << endl;
    }

    for (int i = 0; i < k; i++)
    {
        GrafLMP << PL3[i][0] << " ";
        GrafLMP << PL3T[i] << " ";
        for (int j = 1; j < 4; j++)
        {
            GrafLMP << PL3[i][j] << " ";
        }
        GrafLMP << endl;
    }

    for (int i = 0; i < 2 * k; i++)
    {
        if (PL4[i][3] != -909909)
        {
            GrafLMP << PL4[i][0] << " ";
            GrafLMP << PL4T[i] << " ";
        }

        for (int j = 1; j < 4; j++)
        {
            if (PL4[i][3] != -909909)
            {

                GrafLMP << PL4[i][j] << " ";
            }

        }
        if (PL4[i][3] != -909909)
        {
            GrafLMP << endl;
        }

    }


    GrafLMP.close();


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
