#include <iostream>

using namespace std;
int nactipole(char pole[][16],unsigned int delka);
void vypispole(char pole[][16],unsigned int delka);
int zkontrolujpole(char pole[][16],unsigned int delka);
void vynulujpompole(bool helf[][16][16],unsigned int delka);
void vyplnpompole(bool helf[][16][16],unsigned int delka,char pole[][16]);
void vyplnpompole2(bool helf[][16][16],unsigned int delka,char pole[][16]);
void doplnpismenka(char pole[][16],bool help[][16][16],int &pomoc,bool &zmena,unsigned int delka);
void vyplnuj(char polee[][16],unsigned int delka,int &reseni,bool helf[][16][16],char prvni[][16]);
int main()
{
    char pole[16][16],prvni[16][16];
    bool helf[16][16][16];
    unsigned int delka=16;
    int reseni=0;

    cout << "Zadejte hexadoku:"<< endl;
    if(nactipole(pole,delka)!=0)
    {
        cout <<"Nespravny vstup."<<endl;
        return 0;
    }
    if(zkontrolujpole(pole,delka)!=0)
    {
        cout <<"Nespravny vstup."<<endl;
        return 0;
    }

    vyplnuj(pole,delka,reseni,helf,prvni);

    if(reseni==1)
    {
        vypispole(prvni,delka);
    }
    if(reseni==0)
    {
        cout<< "Reseni neexistuje."<<endl;
    }
    if(reseni>1)
    {
        cout << "Celkem reseni: "<<reseni<<endl;
    }
    return 0;
}

int nactipole(char pole[][16],unsigned int delka)
{
    string radek;
    getline(cin,radek,'\n');
    if(cin.good() && radek=="+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+")
    {
        for(unsigned int i=0;i<delka;i++)
        {
            getline(cin,radek,'\n');
            if(cin.fail() || radek.length()!=65)
                return 1;
            if(radek[0]!='|')
                return 1;

            for(unsigned int j=0;j<delka;j++)
            {
                if((radek[j*4+2]>='a' && radek[j*4+2]<='p')|| radek[j*4+2]==' ')
                {
                    pole[i][j]=radek[j*4+2];
                }
                else
                {
                    return 1;
                }

                if(j%4==0)
                {
                    if(radek[j*4]!='|')
                    return 1;
                }
                else
                {
                    if(radek[j*4]!=' ')
                    return 1;
                }
                if(radek[j*4+1]!=' ' || radek[j*4+3]!=' ')
                    return 1;
            }
            if(radek[64]!='|')
                return 1;
            getline(cin,radek,'\n');
            if((i+1)%4==0 && i!=0)
            {
                if(radek!="+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+")
                return 1;

            }
            else
            {
               if(radek!="+   +   +   +   +   +   +   +   +   +   +   +   +   +   +   +   +")
                return 1;
            }


        }
    }
    else
        return 1;
    return 0;
}
void vypispole(char pole[][16],unsigned int delka)
{
    cout << "+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
    for(unsigned int i=0;i<delka;i++)
    {
        for(unsigned int j=0;j<delka;j++)
        {
            if(j%4==0)
            {
                if(j==0)
                {
                   cout <<"| "<<pole[i][j];
                }
                else
                {
                    cout <<" | "<<pole[i][j];
                }
            }
            else
            {
                cout<<"   "<<pole[i][j];
            }
        }
        cout <<" |"<<endl;
        if((i+1)%4==0 && i!=0)
        {
            cout<<"+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
        }
        else
        cout << "+   +   +   +   +   +   +   +   +   +   +   +   +   +   +   +   +"<<endl;
    }
}

int zkontrolujpole(char pole[][16],unsigned int delka)
{
    for(unsigned int i=0;i<delka;i++)
    {
       for(unsigned int j=0;j<delka;j++)
       {
           for(unsigned int k=0;k<delka;k++)
           {
               if(j!=k)
               {
                    if((pole[i][j]==pole[i][k]) && pole[i][j]!=' ')
                    {
                     return 1;
                    }

                    if((pole[j][i]==pole[k][i]) && pole[j][i]!=' ')
                    {
                       return 1;
                    }
               }
           }
           if(pole[i][j]!=' ')
           {
               for(unsigned int a=(i/4)*4;a<((i/4)*4+4);a++)
               {
                   for(unsigned int b=(j/4)*4;b<((j/4)*4+4);b++)
                   {
                       if(a!=i && b!=j)
                       {
                           if(pole[i][j]==pole[a][b])
                           {
                               return 1;
                           }
                       }
                   }
               }
           }
       }
    }
    return 0;
}

void vyplnuj(char polee[][16],unsigned int delka,int &reseni,bool helf[][16][16],char prvni[][16])
{
    char pole[16][16];
    for(unsigned int i=0;i<delka;i++)
    {
        for(unsigned int j=0;j<delka;j++)
        {
            pole[i][j]=polee[i][j];
        }
    }
    vynulujpompole(helf,delka);
    for(;;)
    {
    vyplnpompole(helf,delka,pole);
    int pomoc;
    bool zmena;
    zmena=false;
    pomoc=0;
    doplnpismenka(pole,helf,pomoc,zmena,delka);


    if(pomoc==0)
    {
        if(reseni==0)
        {
           for(unsigned int i=0;i<delka;i++)
           {
               for(unsigned int j=0;j<delka;j++)
               {
                   prvni[i][j]=pole[i][j];
               }
           }
        }
        reseni++;
        break;
    }
    bool zmena2;
    zmena2=false;

    if(zmena==false)
    {
        vyplnpompole2(helf,delka,pole);
        doplnpismenka(pole,helf,pomoc,zmena2,delka);

        if(zmena2==false)
        {
            unsigned int ii=0;
            unsigned int jj=0;
            unsigned int konecnypocet=16;
            unsigned int varianty[16];
            for(unsigned int i=0;i<delka;i++)
            {
                for(unsigned int j=0;j<delka;j++)
                {
                    if(pole[i][j]==' ')
                    {
                        unsigned int pocet=0;
                        for(unsigned int k=0;k<delka;k++)
                        {
                            if(helf[i][j][k]==true)
                            {
                                 pocet++;
                            }
                        }
                        if(pocet<konecnypocet)
                        {
                            konecnypocet=pocet;
                            ii=i;
                            jj=j;
                            if(konecnypocet==2)
                            {
                                break;
                            }
                        }
                    }
                }

            }
            unsigned int pocet=0;
            for(unsigned int k=0;k<delka;k++)
            {
                if(helf[ii][jj][k]==true)
                {
                    varianty[pocet]=k;
                    pocet++;
                }
            }
            for(unsigned int k=0;k<konecnypocet;k++)
            {
                pole[ii][jj]=' ';

                    pole[ii][jj]='a'+varianty[k];
                    vyplnuj(pole,delka,reseni,helf,prvni);

            }

            break;
        }
    }


    }
}

void vynulujpompole(bool helf[][16][16],unsigned int delka)
{
    for(unsigned int i=0;i<delka;i++)
    {
        for(unsigned int j=0;j<delka;j++)
        {
            for(unsigned int k=0;k<delka;k++)
            {
                helf[i][j][k]=true;
            }
        }
    }
}
void vyplnpompole(bool helf[][16][16],unsigned int delka,char pole[][16])
{
    for(unsigned int i=0;i<delka;i++)
    {
        for(unsigned int j=0;j<delka;j++)
        {
            if(pole[i][j]!=' ')
            {
                int pom=(int)(pole[i][j]-'a');
                for(unsigned int k=0;k<delka;k++)
                {
                    helf[k][j][pom]=false;
                    helf[i][k][pom]=false;
                    helf[i][j][k]=false;
                }
                for(unsigned int a=(i/4)*4;a<((i/4)*4+4);a++)
                {
                    for(unsigned int b=(j/4)*4;b<((j/4)*4+4);b++)
                    {
                        helf[a][b][pom]=false;
                    }
                }
            }
        }
    }
}
void vyplnpompole2(bool helf[][16][16],unsigned int delka,char pole[][16])
{
    int jednickyradek,radek,radekmax,jednickysloupec,sloupec,sloupecmax,radeksouradnice=0,sloupecsouradnice=0;
    for(unsigned int k=0;k<delka;k++)
    {
        for(unsigned int i=0;i<4;i++)
        {
            for(unsigned int j=0;j<4;j++)
            {
                jednickyradek=0;
                jednickysloupec=0;
                radekmax=1;
                sloupecmax=1;
                for(unsigned int a=0;a<4;a++)
                {
                    radek=0;
                    sloupec=0;
                    for(unsigned int b=0;b<4;b++)
                    {
                        if(helf[(i*4)+a][j*4+b][k]==true)
                        {
                            radek++;
                            jednickyradek++;
                        }
                        if(helf[i*4+b][j*4+a][k]==true)
                        {
                            sloupec++;
                            jednickysloupec++;
                        }
                    }
                    if(radekmax<radek)
                    {
                        radekmax=radek;
                        radeksouradnice=i*4+a;
                    }
                    if(sloupecmax<sloupec)
                    {
                        sloupecmax=sloupec;
                        sloupecsouradnice=j*4+a;
                    }
                }
                if((jednickyradek>1&& jednickyradek<5) && jednickyradek==radekmax)
                {
                   for(unsigned int z=0;z<delka;z++)
                   {
                       if(z<j*4 || z>j*4+3)
                       {
                           helf[radeksouradnice][z][k]=false;
                       }
                   }
                }
                if((jednickysloupec>1 && jednickysloupec <5) &&jednickysloupec==sloupecmax)
                {
                   for(unsigned int z=0;z<delka;z++)
                   {
                       if(z<i*4 || z>i*4+3)
                       {
                           helf[z][sloupecsouradnice][k]=false;
                       }
                   }
                }
            }
        }
    }
}

void doplnpismenka(char pole[][16],bool helf[][16][16],int &pomoc,bool &zmena,unsigned int delka)
{
    for(unsigned int i=0;i<delka;i++)
    {
        for(unsigned int j=0;j<delka;j++)
        {
            if(pole[i][j]==' ')
            {
                pomoc=pomoc+1;
                unsigned int pom=0,kk;
                for(unsigned int k=0;k<delka;k++)
                {
                    if(helf[i][j][k]==true)
                    {
                        pom++;
                        kk=k;
                    }
                }
                if(pom==1)
                {
                    pole[i][j]=kk+'a';
                    vyplnpompole(helf,delka,pole);
                    zmena=true;
                }
            }
        }
    }
    int sloupec,radek,rii,rjj,sii,sjj;
    for(unsigned int k=0;k<delka;k++)
    {
        for(unsigned int i=0;i<delka;i++)
        {
            radek=0;
            sloupec=0;
            for(unsigned int j=0;j<delka;j++)
            {
                if(helf[i][j][k]==true)
                {
                    radek++;
                    rii=i;
                    rjj=j;
                }
                if(helf[j][i][k]==true)
                {
                    sloupec++;
                    sii=j;
                    sjj=i;
                }
            }
            if(sloupec==1)
            {
                pole[sii][sjj]='a'+k;
                vyplnpompole(helf,delka,pole);
                zmena=true;
            }
            if(radek==1)
            {
                pole[rii][rjj]='a'+k;
                vyplnpompole(helf,delka,pole);
                zmena=true;
            }
        }
    }
    int jednicky=0,ii=0,jj=0;
    for(unsigned int k=0;k<delka;k++)
    {
        for(unsigned int i=0;i<4;i++)
        {
            for(unsigned int j=0;j<4;j++)
            {
                jednicky=0;
                for(unsigned int a=0;a<4;a++)
                {
                    for(unsigned int b=0;b<4;b++)
                    {
                        if(helf[(i*4)+a][j*4+b][k]==true)
                        {
                            jednicky++;
                            ii=(i*4)+a;
                            jj=j*4+b;
                        }
                    }
                }
                if(jednicky==1)
                {
                    pole[ii][jj]='a'+k;
                    vyplnpompole(helf,delka,pole);
                    zmena=true;
                }
            }
        }
    }

}
