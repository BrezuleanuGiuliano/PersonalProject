#include<bits/stdc++.h>
#include <winbgim.h>
#include <stdio.h>
using namespace std;
ifstream fin("citire.in");
ofstream fout("citire.out");
struct nod
{
    char info[105];
    nod* st,*dr;
};
int latime, inaltime;
char s[500];
int nrNiveluri(nod *a)
{
    if(a==NULL)return 0;
    else
    {
        int n1=nrNiveluri(a->st);
        int n2=nrNiveluri(a->dr);
        return 1+max(n1,n2);
    }
}

int nrColoane(nod *a)
{
    if(a==NULL)return 0;
    else
    {
        int n1=nrColoane(a->st);
        int n2=nrColoane(a->dr);
        return 1+n1+n2;
    }
}
int paranteze_numitor(nod *a)
{
    if(a==NULL)
        return 0;
    else if(a->st==NULL&&a->dr==NULL)
        return 0;
    else
    {
        if(strcmp(a->info,"lim\0")==0||strcmp(a->info,"g\0")==0||strcmp(a->info,"f\0")==0||strcmp(a->info,"sum\0")==0||strcmp(a->info,"integr\0")==0||strcmp(a->info,"`\0")==0||strcmp(a->info,"log\0")==0||strcmp(a->info,"arctg\0")==0||strcmp(a->info,"arcctg\0")==0||strcmp(a->info,"arcsin\0")==0||strcmp(a->info,"arccos\0")==0||strcmp(a->info,"arctg\0")==0||strcmp(a->info,"abs\0")==0||strcmp(a->info,"rad\0")==0||strcmp(a->info,"ctg\0")==0||strcmp(a->info,"sin\0")==0||strcmp(a->info,"cos\0")==0||strcmp(a->info,"ln\0")==0||strcmp(a->info,"lg\0")==0)
            return 4+paranteze_numitor(a->st);
        else if(strcmp(a->info,"-\0")==0&&(strcmp(a->dr->info,"-\0")==0||strcmp(a->dr->info,"+\0")==0))
            return 4+max(paranteze_numitor(a->st),paranteze_numitor(a->dr));
        else
            return paranteze_numitor(a->st)+paranteze_numitor(a->dr);

    }

}
int marime_y1(nod *a,int ok)
{
    if(a==NULL)
        return 0;
    else
    {
        if(a->st==NULL&&a->dr==NULL)return 4+textheight(a->info)/2;
        else if(strcmp(a->info,"sum\0")==0)
            if(ok==0)
                return 8+max(48,marime_y1(a->st,ok));
            else return 8+marime_y1(a->st,ok);
        else if(strcmp(a->info,"rad\0")==0)
            return marime_y1(a->st,ok)+32;
        else if(strcmp(a->info,"log\0")==0||strcmp(a->info,"lim\0")==0)
            return marime_y1(a->dr,ok)+marime_y1(a->st,ok)+8;
        else if(strcmp(a->info,"`\0")==0)
            return marime_y1(a->st,ok)+8+paranteze_numitor(a);

        else if(a->dr==NULL&&ok!=2)
            return marime_y1(a->st,ok);
        else if(a->dr==NULL&&ok==2)
            return marime_y1(a->st,ok);
        else
        {
            int n1=marime_y1(a->st,ok);
            int n2=marime_y1(a->dr,ok);
            if(ok==0)
            {
                if(strcmp(a->info,"/\0")==0)
                    return n1+n2+16+paranteze_numitor(a);
                else if(strcmp(a->info,"^\0")==0)
                    return n1+marime_y1(a->dr,0);
            }
            else if(ok==1)
            {
                if(strcmp(a->info,"^\0")==0)
                    return n1+marime_y1(a->dr,0)+paranteze_numitor(a);
                else if(strcmp(a->info,"/\0")==0)
                    return marime_y1(a->st,0)+8+paranteze_numitor(a);
                else
                    return max(marime_y1(a->st,1),marime_y1(a->dr,1));
            }
            if(ok==2)
            {
                if(strcmp(a->info,"^\0")==0)
                    return n1;
                else if(strcmp(a->info,"/\0")==0)
                    return marime_y1(a->dr,0)+8;
                else
                    return max(marime_y1(a->st,2),marime_y1(a->dr,2));
            }
            else if(strcmp(a->dr->info,"/\0")==0&&strcmp(a->st->info,"^\0")==0)
                return 8+max(marime_y1(a->st,1),marime_y1(a->dr->st,0))+max(marime_y1(a->dr->dr,0),marime_y1(a->st,2));
            else if(strcmp(a->dr->info,"^\0")==0&&strcmp(a->st->info,"/\0")==0)
                return 8+max(marime_y1(a->dr,1),marime_y1(a->st->st,0))+max(marime_y1(a->st->dr,0),marime_y1(a->dr,2));
            else if(strcmp(a->dr->info,"/\0")==0&&strcmp(a->st->info,"/\0")==0)
                return 16+max(marime_y1(a->dr->st,0),marime_y1(a->st->st,0))+max(marime_y1(a->dr->dr,0),marime_y1(a->st->dr,0));
            else if(strcmp(a->dr->info,"/\0")==0)
                return 16+max(marime_y1(a->dr->st,0),marime_y1(a->st,1))+max(marime_y1(a->dr->dr,0),marime_y1(a->st,2));
            else if(strcmp(a->st->info,"/\0")==0)
                return 16+max(marime_y1(a->dr,1),marime_y1(a->st->st,0))+max(marime_y1(a->dr,2),marime_y1(a->st->dr,0));
            else
                return max(marime_y1(a->st,1),marime_y1(a->dr,1))+max(marime_y1(a->st,2),marime_y1(a->dr,2))+paranteze_numitor(a);


        }
    }
}
int cautare_fracd(nod *a)
{
    if(a==NULL)
        return 0;
    else if(a->dr==NULL)
        return cautare_fracd(a->st);
    else
    {

        if(strcmp(a->info,"log\0")==0||strcmp(a->info,"lim\0")==0)
            return cautare_fracd(a->st)+marime_y1(a->dr,0);
        else if(strcmp(a->info,"^\0")==0)
            return cautare_fracd(a->st);
        else if(strcmp(a->info,"/\0")==0)
            return marime_y1(a->dr,0) ;
        else
        {
            int n1=cautare_fracd(a->st);
            int n2=cautare_fracd(a->dr);
            if(n1>=n2)
                return cautare_fracd(a->st);
            if(n1<n2)
                return cautare_fracd(a->dr);
        }
    }
}
int cautare_fracs(nod *a)
{
    if(a==NULL)
        return 0;
    else if(a->st==NULL&&a->dr==NULL)return 4+textheight(a->info)/2;
    else if(strcmp(a->info,"rad\0")==0||strcmp(a->info,"`\0")==0)
        return cautare_fracs(a->st)+8;
    if(strcmp(a->info,"sum\0")==0)
        return 8+max(48,cautare_fracs(a->st));
    if(strcmp(a->info,"log\0")==0||strcmp(a->info,"lim\0")==0)
        return cautare_fracs(a->st);
    else if(a->dr==NULL)
        return cautare_fracs(a->st);
    else
    {
        if(strcmp(a->info,"/\0")==0)
            return 16+marime_y1(a->st,0) ;
        else if(strcmp(a->info,"^\0")==0)
            return marime_y1(a->dr,0)+cautare_fracs(a->st);
        else if(a->st!=NULL&&strcmp(a->st->info,"^\0")==0)
            return max (marime_y1(a->st->dr,0)+cautare_fracs(a->st->st),cautare_fracs(a->dr));
        else if(a->dr!=NULL&&strcmp(a->dr->info,"^\0")==0)
            return max (marime_y1(a->dr->dr,0)+cautare_fracs(a->dr->st),cautare_fracs(a->st));
        else if(a->st!=NULL&&strcmp(a->st->info,"^\0")==0&&a->dr!=NULL&&strcmp(a->dr->info,"^\0")==0)
            return max (marime_y1(a->st->dr,0)+cautare_fracs(a->st->st),marime_y1(a->dr->dr,0)+cautare_fracs(a->dr->st));
        else if(strcmp(a->info,"^\0")==0)
            return marime_y1(a,0)-marime_y1(a->st,0);
        else
        {
            int n1=cautare_fracs(a->st);
            int n2=cautare_fracs(a->dr);
            if(n1>n2)
                return cautare_fracs(a->st);
            if(n1<=n2)
                return cautare_fracs(a->dr);
        }
    }
}


int marime_y(nod *a)
{
    if(a==NULL)
        return 0;
    else
    {
        if(a->st==NULL&&a->dr==NULL)return 4+textheight(a->info)/2;
        else if(strcmp(a->info,"log\0")==0||strcmp(a->info,"lim\0")==0)
            return marime_y(a->dr)+marime_y(a->st);
        else if(strcmp(a->info,"sum\0")==0)
            return max(48,marime_y(a->st));
        else if(strcmp(a->info,"rad\0")==0)
            return marime_y(a->st)+16;

        if(a->dr==NULL)
            return marime_y(a->st);
        else if(a->st==NULL)
            return marime_y(a->dr);
        else
        {
            int n1=marime_y(a->st);
            int n2=marime_y(a->dr);

            if(strcmp(a->info,"/\0")==0)
                return n1+paranteze_numitor(a->dr)+n2+16;
            else if(strcmp(a->info,"^\0")==0)
                return n1+n2+paranteze_numitor(a);
            else if(strcmp(a->info,"`\0")==0)
                return n1+8+paranteze_numitor(a);
            else if(a->st!=NULL&&strcmp(a->st->info,"^\0")==0)
                return 10+max(marime_y1(a->st->dr,0)+cautare_fracs(a->st->st),cautare_fracs(a->dr))+max(cautare_fracd(a->dr),cautare_fracd(a->st));
            else if(a->dr!=NULL&&strcmp(a->dr->info,"^\0")==0)
                return 10+max(marime_y1(a->dr->dr,0)+cautare_fracs(a->dr->st),cautare_fracs(a->st))+max(cautare_fracd(a->st),cautare_fracd(a->dr));
            else if(a->dr!=NULL&&a->st!=NULL&&strcmp(a->dr->info,"/\0")==0&&strcmp(a->st->info,"/\0")==0)
                return 16+max(marime_y(a->dr->st),marime_y(a->st->st))+max(marime_y(a->dr->dr),marime_y(a->st->dr));
            else if(strcmp(a->dr->info,"/\0")==0)
                return 16+max(marime_y(a->dr->st),cautare_fracs(a->st))+max(marime_y(a->dr->dr),cautare_fracd(a->st));
            else if(strcmp(a->st->info,"/\0")==0)
                return 16+max(marime_y(a->st->st),cautare_fracs(a->dr))+max(marime_y(a->st->dr),cautare_fracd(a->dr));
            else
                return max(cautare_fracs(a->st),cautare_fracs(a->dr))+max(cautare_fracd(a->st),cautare_fracd(a->dr))+paranteze_numitor(a);
        }
    }
}

int marime_x(nod *a)
{
    if(a==NULL)
        return 0;
    else
    {
        if(a->st==NULL&&a->dr==NULL)
            return 12+textwidth(a->info);
        else
        {
            int n1=marime_x(a->st);
            int n2=marime_x(a->dr);
            if(strcmp(a->info,"/\0")==0)
                return max(n1,n2)+marime_y(a)/2;
            else if(strcmp(a->info,"^\0")==0||strcmp(a->info,"abs\0")==0)
                return n1+n2+n1/100+16;
            else if(strcmp(a->info,"rad\0")==0)
            {
                if(a->dr)
                    return marime_x(a->st)+marime_x(a->st)/100+textwidth(a->dr->info)*75/100+24;
                else
                    return marime_x(a->st)+marime_x(a->st)/100+24;
            }
            else if(strcmp(a->info,"*\0")==0)
                return n1+n2+n1/100+n2/100+16;
            else if(strcmp(a->info,"-\0")==0&&(strcmp(a->dr->info,"-\0")==0||strcmp(a->dr->info,"+\0")==0))
                return n1+n2+n2/100+48;
            else if(strcmp(a->info,"log\0")==0)
                return n1+n1/100+textwidth(a->info)+n2+18+paranteze_numitor(a);
            else if(strcmp(a->info,"sum\0")==0)
                return n1+n1/100+textwidth(a->info)+paranteze_numitor(a)+max(marime_y(a->st)*8/10,48);
            else if(strcmp(a->info,"lim\0")==0)
                return n1+textwidth("x->")+max(marime_x(a->dr),16)+32;

            else if(strcmp(a->info,"integr\0")==0||strcmp(a->info,"arctg\0")==0||strcmp(a->info,"arcctg\0")==0||strcmp(a->info,"arcsin\0")==0||strcmp(a->info,"arccos\0")==0||strcmp(a->info,"tg\0")==0||strcmp(a->info,"ctg\0")==0||strcmp(a->info,"sin\0")==0||strcmp(a->info,"cos\0")==0||strcmp(a->info,"ln\0")==0||strcmp(a->info,"lg\0")==0)
                return n1+n1/100+textwidth(a->info)+18+paranteze_numitor(a);
            else
                return 12+2*textwidth(a->info)+n1+n2;
        }
    }
}

void deseneazaNod(char elem[], int xc, int yc, int latime, int inaltime)
{
    char arr[50];
    sprintf(arr,"%s",elem);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,LIGHTCYAN);
    fillellipse(xc,yc,textwidth(arr)+2, textheight("M")/2+6);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    setbkcolor(LIGHTCYAN);
    setcolor(BLUE);
    settextjustify(1,1);
    outtextxy(xc,yc+4,arr);
}

void deseneazaArbore(nod *a, int niv, int stanga, int latime, int inaltime)
{
    if(a!=NULL)
    {
        int n1=nrColoane(a->st);
        int xc=stanga+latime*n1+latime/2;
        int yc=niv*inaltime-inaltime/2;

        if (a->st!=NULL)
        {
            int xcs=stanga+latime*nrColoane(a->st->st)+latime/2;
            setcolor(WHITE);
            line(xc,yc,xcs,yc+inaltime);
        }
        if (a->dr!=NULL)
        {
            int xcd=stanga+latime*(n1+1)+latime*nrColoane(a->dr->st)+latime/2;
            setcolor(WHITE);
            line(xc,yc,xcd,yc+inaltime);
        }
        deseneazaNod(a->info,xc,yc,latime, inaltime);
        deseneazaArbore(a->st,niv+1,stanga, latime, inaltime);
        deseneazaArbore(a->dr,niv+1,stanga+latime*(n1+1), latime, inaltime);
    }
}

int prioritate(char op)
{
    if(op=='+'||op=='-')
        return 1;
    else if(op=='^')return 3;
    else
        return 2;
}
bool isop(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')return 1;
    return 0;
}

void rsd(nod *NOD)
{
    if(NOD!=NULL)
    {
        fout<<NOD->info<<' ';
        rsd(NOD->st);
        rsd(NOD->dr);
    }
}
bool paranteza(char s[])
{
    int ct=0;
    for(int i=0; s[i]; i++)
        if(s[i]=='(')ct++;
        else if(s[i]==')')
            if(ct>0)ct--;
            else return 0;
    return ct==0;
}

nod *rez(int st,int dr,char s[])
{
    int i=st,j=dr;
    char op=0;
    int prior=5;
    int poz=-1;
    if(isop(s[i]))
        i++;
    while(i<=j)
    {
        if(s[i]=='(')
        {
            int ct=1;
            i++;
            while(i<=j&&ct!=0)
            {
                if(s[i]=='(')ct++;
                if(s[i]==')')ct--;
                i++;
            }
            i--;
        }
        else
        {
            if(isop(s[i]))
            {
                if(prioritate(s[i])<=prior)
                {
                    prior=prioritate(s[i]);
                    op=s[i];
                    poz=i;
                }
            }
        }
        i++;
    }
    int k=0;
    nod*r;
    if(poz==-1)
    {
        if(s[st]=='('&&s[dr]==')')
            r=rez(st+1,dr-1,s);
        else
        {
            if(isop(s[st]))
            {
                r=new nod;
                int l;
                if(s[st]=='-')
                    l=st;
                else
                    l=st+1;
                for(l; l<=dr&&s[l]!='('; l++)
                    r->info[k++]=s[l];
                r->info[k]=NULL;
                if(l<=dr)
                    if(s[dr]==')')
                        r->dr=rez(l+1,dr-1,s);
                    else
                        r->dr=rez(l,dr,s);
                else
                    r->dr=NULL;
                r->st=NULL;

            }
            else if(s[st]=='f')
            {
                r=new nod;
                r->info[0]='f';
                r->info[1]=NULL;
                r->st=rez(st+1,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='g')
            {
                r=new nod;
                r->info[0]='g';
                r->info[1]=NULL;
                r->st=rez(st+1,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='s'&&s[st+1]=='i'&&s[st+2]=='n')
            {
                r=new nod;
                r->info[0]='s';
                r->info[1]='i';
                r->info[2]='n';
                r->info[3]=NULL;
                r->st=rez(st+3,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='s'&&s[st+1]=='u'&&s[st+2]=='m')
            {
                r=new nod;
                r->info[0]='s';
                r->info[1]='u';
                r->info[2]='m';
                r->info[3]=0;
                i=st+3;
                int ct=1;
                while(ct&&i<=j)
                {
                    i++;
                    if(s[i]=='(')ct++;
                    if(s[i]==')')ct--;
                }
                if(s[i+1]=='(')
                {
                    r->st=rez(st+3,i,s);
                    r->dr=rez(i+1,j,s);
                }
                else
                {
                    r->st=rez(st+3,j,s);
                    r->dr=0;
                }
            }
            else if(s[st]=='l'&&s[st+1]=='i'&&s[st+2]=='m')
            {
                r=new nod;
                r->info[0]='l';
                r->info[1]='i';
                r->info[2]='m';
                r->info[3]=0;
                i=st+3;
                int ct=1;
                while(ct&&i<=j)
                {
                    i++;
                    if(s[i]=='(')ct++;
                    if(s[i]==')')ct--;
                }
                if(s[i+1]=='(')
                {
                    r->st=rez(st+3,i,s);
                    r->dr=rez(i+1,j,s);
                }
                else
                {
                    r->st=rez(st+3,j,s);
                    r->dr=0;
                }
            }
            else if(s[st]=='c'&&s[st+1]=='o'&&s[st+2]=='s')
            {
                r=new nod;
                r->info[0]='c';
                r->info[1]='o';
                r->info[2]='s';
                r->info[3]=NULL;
                r->st=rez(st+3,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='t'&&s[st+1]=='g')
            {
                r=new nod;
                r->info[0]='t';
                r->info[1]='g';
                r->info[2]=NULL;
                r->st=rez(st+2,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='c'&&s[st+1]=='t'&&s[st+2]=='g')
            {
                r=new nod;
                r->info[0]='c';
                r->info[1]='t';
                r->info[2]='g';
                r->info[3]=NULL;
                r->st=rez(st+3,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='l'&&s[st+1]=='o'&&s[st+2]=='g')
            {
                r=new nod;
                r->info[0]='l';
                r->info[1]='o';
                r->info[2]='g';
                r->info[3]=NULL;
                i=st+3;
                int ct=1;
                while(ct&&i<=j)
                {
                    i++;
                    if(s[i]=='(')ct++;
                    if(s[i]==')')ct--;
                }
                r->dr=rez(st+3,i,s);
                r->st=rez(i+1,j,s);
            }
            else if(s[st]=='l'&&s[st+1]=='n'||s[st+1]=='g')
            {
                r=new nod;
                r->info[0]='l';
                if(s[st+1]=='n')
                    r->info[1]='n';
                else r->info[1]='g';
                r->info[2]=NULL;
                r->st=rez(st+2,j,s);
                r->dr=NULL;
            }
            else if(s[st]=='r'&&s[st+1]=='a'&&s[st+2]=='d')
            {
                r=new nod;
                r->info[0]='r';
                r->info[1]='a';
                r->info[2]='d';
                r->info[3]=0;
                i=st+3;
                int ct=1;
                while(ct&&i<=j)
                {
                    i++;
                    if(s[i]=='(')ct++;
                    if(s[i]==')')ct--;
                }
                if(s[i+1]=='(')
                {
                    r->dr=rez(st+3,i,s);
                    r->st=rez(i+1,j,s);
                }
                else
                {
                    r->st=rez(st+3,j,s);
                    r->dr=0;
                }
            }
            else if(s[st]=='i'&&s[st+1]=='n'&&s[st+2]=='t'&&s[st+3]=='e'&&s[st+4]=='g'&&s[st+5]=='r')
            {
                r=new nod;
                r->info[0]='i';
                r->info[1]='n';
                r->info[2]='t';
                r->info[3]='e';
                r->info[4]='g';
                r->info[5]='r';
                r->info[6]=0;
                r->st=rez(st+6,j,s);
                r->dr=0;
            }
            else if(s[st]=='a'&&s[st+1]=='r'&&s[st+2]=='c'&&s[st+3]=='s'&&s[st+4]=='i'&&s[st+5]=='n')
            {
                r=new nod;
                r->info[0]='a';
                r->info[1]='r';
                r->info[2]='c';
                r->info[3]='s';
                r->info[4]='i';
                r->info[5]='n';
                r->info[6]=0;
                r->st=rez(st+6,j,s);
                r->dr=0;
            }
            else if(s[st]=='a'&&s[st+1]=='r'&&s[st+2]=='c'&&s[st+3]=='c'&&s[st+4]=='o'&&s[st+5]=='s')
            {
                r=new nod;
                r->info[0]='a';
                r->info[1]='r';
                r->info[2]='c';
                r->info[3]='c';
                r->info[4]='o';
                r->info[5]='s';
                r->info[6]=0;
                r->st=rez(st+6,j,s);
                r->dr=0;
            }
            else if(s[st]=='a'&&s[st+1]=='r'&&s[st+2]=='c'&&s[st+3]=='c'&&s[st+4]=='t'&&s[st+5]=='g')
            {
                r=new nod;
                r->info[0]='a';
                r->info[1]='r';
                r->info[2]='c';
                r->info[3]='c';
                r->info[4]='t';
                r->info[5]='g';
                r->info[6]=0;
                r->st=rez(st+6,j,s);
                r->dr=0;
            }
            else if(s[st]=='a'&&s[st+1]=='r'&&s[st+2]=='c'&&s[st+3]=='t'&&s[st+4]=='g')
            {
                r=new nod;
                r->info[0]='a';
                r->info[1]='r';
                r->info[2]='c';
                r->info[3]='t';
                r->info[4]='g';
                r->info[5]=0;
                r->st=rez(st+5,j,s);
                r->dr=0;
            }
            else if(s[st]=='a'&&s[st+1]=='b'&&s[st+2]=='s')
            {
                r=new nod;
                r->info[0]='a';
                r->info[1]='b';
                r->info[2]='s';
                r->info[3]=0;
                r->st=rez(st+3,j,s);
                r->dr=0;
            }
            else if(s[dr]=='`')
            {
                r=new nod;
                r->info[0]='`';
                r->info[1]=0;
                r->st=rez(st+1,dr-2,s);
                r->dr=0;
            }
            else
            {
                r=new nod;
                for(int l=st; l<=dr; l++)
                    r->info[k++]=s[l];
                r->info[k]=NULL;
                r->st=NULL;
                r->dr=NULL;
            }
        }
    }
    else
    {
        r=new nod;
        r->info[0]=op;
        r->info[1]=NULL;
        r->st=rez(st,poz-1,s);
        r->dr=rez(poz+1,dr,s);
    }
    return r;
}
struct Pair
{
    bool corect;
    int poz;
    char mesaj[105];
};
Pair estecorect(char s[],int st,int dr)
{
    Pair eroare;
    eroare.poz=-1;
    eroare.corect=1;
    eroare.mesaj[0]=0;
    if(strlen(s)==0)
    {
        eroare.corect=0;
        strcpy(eroare.mesaj,"Nu exista un sir");
        return eroare;
    }
    if(!paranteza(s))
    {
        eroare.corect=0;
        strcpy(eroare.mesaj,"Sirul nu este parantezat corect");
        return eroare;
    }
    int n=dr;
    if(isop(s[st])&&s[st]!='-'&&s[st]!='+')
    {
        eroare.poz=st;
        eroare.corect=0;
        strcpy(eroare.mesaj,"exista operatori fara parametri");
        return eroare;
    }
    if(s[st]=='`')
    {
        eroare.poz=st;
        eroare.corect=0;
        strcpy(eroare.mesaj,"exista o derivata fara parametri");
        return eroare;
    }
    if(s[st]=='.'||s[st]==',')
    {
        eroare.poz=st;
        eroare.corect=0;
        strcpy(eroare.mesaj,"un numar zecimal nu are parte intreaga");
        return eroare;
    }
    if(isop(s[n-1]))
    {
        eroare.poz=n-1;
        eroare.corect=0;
        strcpy(eroare.mesaj,"exista operatori fara parametri");
        return eroare;
    }
    if(s[n-1]=='`'&&s[n-2]!=')')
    {
        eroare.poz=n-1;
        eroare.corect=0;
        strcpy(eroare.mesaj,"exista o derivata cu paranteze incorecte");
        return eroare;
    }
    if(s[n-1]=='`')
    {
        int j=n-2;
        int ct=1;
        while(ct&&j>=st)
        {
            j--;
            if(s[j]=='(')ct--;
            if(s[j]==')')ct++;
        }
        if(j>st&&s[j-1]>='a'&&s[j-1]<='z')
        {
            eroare.poz=j;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o derivata cu paranteze incorecte");
            return eroare;
        }
    }
    if(s[n-1]=='.'||s[n-1]==',')
    {
        eroare.poz=n-1;
        eroare.corect=0;
        strcpy(eroare.mesaj,"un numar zecimal nu are parte zecimala la pozitia");
        return eroare;
    }
    if(n>=2)
    {
        if((s[n-2]=='t'||s[n-2]=='l')&&s[n-1]=='g')
        {
            eroare.poz=n;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o functie matematica cu paranteze incorecte");
            return eroare;
        }
        if(s[n-2]=='l'&&s[n-1]=='n')
        {
            eroare.poz=n;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o functie matematica cu paranteze incorecte");
            return eroare;
        }
    }
    if(n>=3)
        if(strcmp(s+n-3,"sum")==0||strcmp(s+n-3,"sin")==0||strcmp(s+n-3,"cos")==0||strcmp(s+n-3,"ctg")==0||strcmp(s+n-3,"log")==0||strcmp(s+n-3,"rad")==0||strcmp(s+n-3,"abs")==0)
        {
            eroare.poz=n;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o functie matematica cu paranteze incorecte");
            return eroare;
        }
    if(n>=5&&strcmp(s+n-5,"arctg")==0)
    {
        eroare.poz=n;
        eroare.corect=0;
        strcpy(eroare.mesaj,"exista o functie matematica cu paranteze incorecte");
        return eroare;
    }
    if(n>=6)
        if(strcmp(s+n-6,"arcsin")==0||strcmp(s+n-6,"arccos")==0||strcmp(s+n-6,"arcctg")==0||strcmp(s+n-6,"integr")==0)
        {
            eroare.poz=n;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o functie matematica cu paranteze incorecte");
            return eroare;
        }
    for(int i=st; i<n-1; i++)
    {
        if(i>0&&(s[i]=='.'||s[i]==','))
        {
            if(s[i-1]<'0'||s[i-1]>'9')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"un numar zecimal nu are parte intreaga la pozitia");
                return eroare;
            }
            if(s[i+1]<'0'||s[i+1]>'9')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"un numar zecimal nu are parte zecimala");
                return eroare;
            }
            int k=i+1;
            while(s[k]!='.'&&s[k]!=','&&s[k]>='0'&&s[k]<='9')k++;
            if(s[k]=='.'||s[k]==',')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"un numar nu este scris corect");
                return eroare;
            }
        }
        if(!isop(s[i])&&(s[i]<'a'||s[i]>'z')&&(s[i]>'9'||s[i]<'0')&&s[i]!='('&&s[i]!=')'&&s[i]!='`'&&s[i]!='.'&&s[i]!=',')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista carcactere necorespunzatoare");
            return eroare;
        }
        if((s[i]>='0'&&s[i]<='9'&&s[i+1]>='a'&&s[i+1]<='z')||(s[i+1]>='0'&&s[i+1]<='9'&&s[i]>='a'&&s[i]<='z'))
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"nu exista un operator intre doi termeni");
            return eroare;
        }
        if(s[i]=='('&&s[i+1]==')')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista paranteze fara parametri");
            return eroare;
        }
        if(isop(s[i])&&isop(s[i+1]))
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista operatori fara parametri");
            return eroare;
        }
        if(s[i]=='('&&isop(s[i+1])&&s[i+1]!='-'&&s[i+1]!='+')
        {
            eroare.poz=i+1;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista operatori fara parametri");
            return eroare;
        }
        if(isop(s[i])&&s[i+1]==')')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista operatori fara parametri");
            return eroare;
        }
        if(s[i]==')'&&s[i+1]!=')'&&!isop(s[i+1])&&s[i+1]!='`')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"nu exista operator dupa o paranteza");
            return eroare;
        }
        if(s[i]=='`'&&s[i-1]!=')')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"exista o derivata cu paranteze incorecte");
            return eroare;
        }
        if(s[i]=='`'&&!isop(s[i+1])&&s[i+1]!=')')
        {
            eroare.poz=i;
            eroare.corect=0;
            strcpy(eroare.mesaj,"nu exista un operator dupa o derivata");
            return eroare;
        }
        if(s[i]=='`')
        {
            int j=i-1;
            int ct=1;
            while(ct&&j>=st)
            {
                j--;
                if(s[j]=='(')ct--;
                if(s[j]==')')ct++;
            }
            if(j>st&&s[j-1]>='a'&&s[j-1]<='z')
            {
                eroare.poz=j;
                eroare.corect=0;
                strcpy(eroare.mesaj,"exista o derivata cu paranteze incorecte");
                return eroare;
            }
        }
        if(i>st&&s[i]=='('&&!isop(s[i-1])&&s[i-1]!='(')
        {
            if(s[i-1]<'a'||s[i-1]>'z')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"nu exista operator inainte de o paranteza");
                return eroare;
            }
            int j=i-1;
            while(j>=st&&s[j]>='a'&&s[j]<='z')
                j--;
            j++;
            if(i==j+1&&s[j]!='g'&&s[j]!='f')
            {
                eroare.poz=j;
                eroare.corect=0;
                strcpy(eroare.mesaj,"nu exista functia scrisa");
                return eroare;
            }
            else if(i!=j+1)
            {
                if(i-j==2)
                    if(strncmp(s+j,"lg",2)&&strncmp(s+j,"ln",2)&&strncmp(s+j,"tg",2))
                    {
                        eroare.poz=j;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"nu exista functia scrisa");
                        return eroare;
                    }
                if(i-j==3)
                    if(strncmp(s+j,"sum",3)&&strncmp(s+j,"lim",3)&&strncmp(s+j,"sin",3)&&strncmp(s+i-3,"cos",3)&&strncmp(s+j,"ctg",3)&&strncmp(s+j,"log",3)&&strncmp(s+j,"rad",3)&&strncmp(s+j,"abs",3))
                    {
                        eroare.poz=j;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"nu exista functia scrisa");
                        return eroare;
                    }
                if(i-j==5&&strncmp(s+j,"arctg",5))
                {
                    eroare.poz=j;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
                if(i-j==6)
                    if(strncmp(s+j,"arcsin",6)&&strncmp(s+j,"arccos",6)&&strncmp(s+j,"arcctg",6)&&strncmp(s+j,"integr",6))
                    {
                        eroare.poz=j;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"nu exista functia scrisa");
                        return eroare;
                    }
                if(i-j>6||i-j==4)
                {
                    eroare.poz=j;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
            }
        }
        if(i<n-6)
        {
            if(s[i]=='i'&&s[i+1]=='n'&&s[i+2]=='t'&&s[i+3]=='e'&&s[i+4]=='g'&&s[i+5]=='r'&&s[i+6]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(integr) nu are parametri");
                return eroare;
            }
            if(s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='s'&&s[i+4]=='i'&&s[i+5]=='n'&&s[i+6]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(arcsin) nu are parametri");
                return eroare;
            }
            if(s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='o'&&s[i+5]=='s'&&s[i+6]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(arccos) nu are parametri");
                return eroare;
            }
            if(s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='t'&&s[i+5]=='g'&&s[i+6]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(arcctg) nu are parametri");
                return eroare;
            }
        }
        if(i<n-5)
            if(s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='t'&&s[i+4]=='g'&&s[i+5]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(arctg) nu are parametri");
                return eroare;
            }
        if(i<n-3)
        {
            if(s[i]=='s'&&s[i+1]=='i'&&s[i+2]=='n'&&s[i+3]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(sin) nu are parametri");
                return eroare;
            }
            if(s[i]=='c'&&s[i+1]=='o'&&s[i+2]=='s'&&s[i+3]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(cos) nu are parametri");
                return eroare;
            }
            if(s[i]=='c'&&s[i+1]=='t'&&s[i+2]=='g'&&s[i+3]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(ctg) nu are parametri");
                return eroare;
            }
            if(s[i]=='r'&&s[i+1]=='a'&&s[i+2]=='d')
            {
                if(i>st&&s[i-1]>='a'&&s[i-1]<='z')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
                if(s[i+3]!='(')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(rad) nu are parametri");
                    return eroare;
                }
                if(s[i+3]=='('&&s[i+4]==')')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(rad) nu are parametri");
                    return eroare;
                }
                int noui=i+3;
                int ct=1;
                while(noui<n&&ct!=0)
                {
                    noui++;
                    if(s[noui]=='(')ct++;
                    if(s[noui]==')')ct--;
                }
                if(s[noui+1]!='(')
                    i=i+3;
                else
                {
                    if(s[noui+2]==')')
                    {
                        eroare.poz=i;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"functia rad nu are destule argumente");
                        return eroare;
                    }
                    eroare=estecorect(s,i+3,noui+1);
                    if(eroare.corect==0)return eroare;
                    i=noui+1;
                }
            }
            if(s[i]=='l'&&s[i+1]=='i'&&s[i+2]=='m')
            {
                if(i>st&&s[i-1]>='a'&&s[i-1]<='z')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
                if(s[i+3]!='(')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(lim) nu are parametri");
                    return eroare;
                }
                if(s[i+3]=='('&&s[i+4]==')')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(lim) nu are parametri");
                    return eroare;
                }
                int noui=i+3;
                int ct=1;
                while(noui<n&&ct!=0)
                {
                    noui++;
                    if(s[noui]=='(')ct++;
                    if(s[noui]==')')ct--;
                }
                if(s[noui+1]!='(')
                    i=i+3;
                else
                {
                    if(s[noui+2]==')')
                    {
                        eroare.poz=i;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"functia lim nu are destule argumente");
                        return eroare;
                    }
                    eroare=estecorect(s,i+3,noui+1);
                    if(eroare.corect==0)return eroare;
                    i=noui+1;
                }

            }
            if(s[i]=='a'&&s[i+1]=='b'&&s[i+2]=='s'&&s[i+3]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(abs) nu are parametri");
                return eroare;
            }
            if(s[i]=='s'&&s[i+1]=='u'&&s[i+2]=='m')
            {
                if(i>st&&s[i-1]>='a'&&s[i-1]<='z')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
                if(s[i+3]!='(')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(sum) nu are parametri");
                    return eroare;
                }
                if(s[i+3]=='('&&s[i+4]==')')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"o functie matematica(sum) nu are parametri");
                    return eroare;
                }
                int noui=i+3;
                int ct=1;
                while(noui<n&&ct!=0)
                {
                    noui++;
                    if(s[noui]=='(')ct++;
                    if(s[noui]==')')ct--;
                }
                if(s[noui+1]!='(')
                    i=i+3;
                else
                {
                    if(s[noui+2]==')')
                    {
                        eroare.poz=i;
                        eroare.corect=0;
                        strcpy(eroare.mesaj,"functia sum nu are destule argumente");
                        return eroare;
                    }
                    eroare=estecorect(s,i+3,noui+1);
                    if(eroare.corect==0)return eroare;
                    i=noui+1;
                }
            }
            if(s[i]=='l'&&s[i+1]=='o'&&s[i+2]=='g')
            {
                if(i>st&&s[i-1]>='a'&&s[i-1]<='z')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"nu exista functia scrisa");
                    return eroare;
                }
                if(s[i+3]!='(')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"functia log nu are destule argumente");
                    return eroare;
                }
                int noui=i+3;
                int ct=1;
                while(noui<n&&ct!=0)
                {
                    noui++;
                    if(s[noui]=='(')ct++;
                    if(s[noui]==')')ct--;
                }
                if(s[noui+1]!='(')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"functia log nu are destule argumente");
                    return eroare;
                }
                if(s[noui+2]==')')
                {
                    eroare.poz=i;
                    eroare.corect=0;
                    strcpy(eroare.mesaj,"functia log nu are destule argumente");
                    return eroare;
                }
                eroare=estecorect(s,i+3,noui+1);
                if(eroare.corect==0)return eroare;
                i=noui+1;
            }
        }
        if(i<n-2)
        {
            if(s[i]=='l'&&s[i+1]=='n'&&s[i+2]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(ln) nu are parametri");
                return eroare;
            }
            if((s[i]=='l'||s[i]=='t')&&s[i+1]=='g'&&s[i+2]!='(')
            {
                eroare.poz=i;
                eroare.corect=0;
                strcpy(eroare.mesaj,"o functie matematica(lg/tg) nu are parametri");
                return eroare;
            }
        }
    }
    return eroare;
}
void deseneazaParanteza(int susX, int susY, int josX, int josY, int curbaMaximaX)
{



    int inaltime = josY - susY;
    int mijlocY = (susY + josY) / 2;

    for (int y = susY; y <= josY; y++)
    {
        float t = (float)(y - susY) / inaltime;
        int x = (1 - t) * (1 - t) * susX + 2 * (1 - t) * t * curbaMaximaX + t * t * josX;
        putpixel(x, y, WHITE);
    }
}
void deseneazaSemnIntegrala(int left, int right, int top, int bottom)
{

    int midY = (top + bottom) / 2;


    int width = right - left;
    int height = bottom - top;

    int arcRadius = width / 6;
    int arcHeight = height / 2;

    arc(left + 2*arcRadius, midY - arcHeight+arcRadius, 0, 180, arcRadius);

    arc(left, midY + arcHeight-arcRadius, 180, 360, arcRadius);

    line(left + arcRadius, midY - arcHeight+arcRadius, left + arcRadius, midY + arcHeight -arcRadius);



}
void deseneazaSimbolInfinit(int centruX, int centruY, int inaltime)
{

    int latime = inaltime * 2;


    setcolor(WHITE);


    ellipse(centruX - latime / 4, centruY, 0, 360, latime / 4, inaltime / 2);
    ellipse(centruX + latime / 4, centruY, 0, 360, latime / 4, inaltime / 2);
}
char* cautare_variabila(nod *a)
{
    if(a==NULL)
        return "x1";
    else
    {
        if(isalpha(a->info[0])&&strlen(a->info)==1&&a->dr==NULL&&a->st==NULL)
        {
            return a->info;
        }
        else
        {
            if(a->st&&strcmp(cautare_variabila(a->st),"x1")!=0)
                return cautare_variabila(a->st);
            else if(a->dr&&strcmp(cautare_variabila(a->dr),"x1")!=0)
                return cautare_variabila(a->dr);
            else
                return "x1";


        }
    }
}
void deseneazaSemnSuma(int left, int right, int top, int bottom,nod *a)
{

    int midY = (top + bottom) / 2;

    if(a->dr)
    {
        top=top+16;
        bottom=bottom-16;
        right=right-16;


        deseneazaSimbolInfinit(left+(right-left)/2,top-10,12);
        char s[10];
        strcpy(s,cautare_variabila(a));
        strcat(s,"=");
        strcat(s,a->dr->info);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(left+(right-left)/2-10,bottom,s);


    }

    int width = right - left;
    int height = bottom - top;


    line(left,top,right,top);
    line(left,bottom,right,bottom);
    line(left,top,left+width*2/3,midY);
    line(left+width*2/3,midY,left,bottom);

}

void deseneazaRadical(int susX, int susY, int josX, int josY, int stangamax)
{
    int mijlocY=(susY+josY)/2;
    line(josX,josY,stangamax,mijlocY);
    line(josX,josY,josX,susY);
    line(josX,susY,susX,susY);


}
void deseneazaExpresieGrafic2(nod* a,int y,float marimefont,int stanga)
{
    if (a == NULL) return;
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
    setcolor(WHITE);
    char expresie[105];
    sprintf(expresie, "%s", a->info);
    if (strcmp(a->info, "/") == 0)
    {

        deseneazaExpresieGrafic2(a->st, y-cautare_fracd(a->st)-16,marimefont,stanga +12+(max(marime_x(a->st),marime_x(a->dr))-20)/2-marime_x(a->st)/2+marime_y(a)/4);
        if(marimefont==3)
            line(stanga, y+3, stanga +max(marime_x(a->st),marime_x(a->dr))-20+marime_y(a)/2, y+3);
        else
            line(stanga, y, stanga +max(marime_x(a->st),marime_x(a->dr))-20+marime_y(a)/2, y);
        deseneazaExpresieGrafic2(a->dr, y+paranteze_numitor(a->dr)+cautare_fracs(a->dr),marimefont,stanga + 12+(max(marime_x(a->st),marime_x(a->dr))-20)/2-marime_x(a->dr)/2+marime_y(a)/4);
    }
    else if (strcmp(a->info, "^") == 0)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        setbkcolor(BLACK);
        setcolor(WHITE);
        if(nrColoane(a->st)>1||a->st->info[0]=='-')
        {
            deseneazaParanteza(stanga+marime_x(a)-marime_x(a->dr)-12-marime_x(a->st)/100,y-cautare_fracs(a->st)-paranteze_numitor(a),stanga+marime_x(a)-marime_x(a->dr)-12-marime_x(a->st)/100,y+cautare_fracd(a->st)+16,stanga+marime_x(a)-marime_x(a->dr)+marime_x(a->st)/100-8);
            deseneazaParanteza(stanga+marime_x(a->st)/150-6,y-cautare_fracs(a->st)-paranteze_numitor(a),stanga-6,y+cautare_fracd(a->st)+16,stanga-8-marime_x(a->st)/100-8);

            //line(stanga+marime_x(a)-marime_x(a->dr)-12,y-cautare_fracs(a->st),stanga+marime_x(a)-marime_x(a->dr)-12,y+cautare_fracd(a->st)+12);
            //line(stanga-8,y-marime_y(a->st)+cautare_fracd(a->st),stanga-8,y+cautare_fracd(a->st)+16);


        }

        deseneazaExpresieGrafic2(a->dr,y-cautare_fracs(a->st)-cautare_fracd(a->dr)-paranteze_numitor(a),1,stanga+marime_x(a)-marime_x(a->dr));
        ///Aici ai mai putea face cu -marime_y+cautare_fracd(a->st), in loc de -cautare_fracs(a->st),si la marimefont poti pune 1 daca vrei sa fie mic sau il lasi daca vrei aceasi marime peste tot
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+12);


    }
    else if (strcmp(a->info, "*") == 0)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        setbkcolor(BLACK);
        setcolor(WHITE);
        if(nrColoane(a->st)==1&&nrColoane(a->dr)==1)
        {
            outtextxy(stanga,y-10, a->st->info);
            outtextxy(stanga+marime_x(a->st),y-16,".");
            outtextxy(stanga+marime_x(a)-marime_x(a->dr),y-10,a->dr->info);



        }
        else
        {
            int ok=0;
            if(nrColoane(a->st)>1&&strcmp(a->st->info,"lim\0")!=0&&strcmp(a->st->info,"*\0")!=0&&strcmp(a->st->info,"f\0")!=0&&strcmp(a->st->info,"g\0")!=0&&strcmp(a->st->info,"log\0")!=0&&strcmp(a->st->info,"sum\0")!=0&&strcmp(a->st->info,"`\0")!=0&&strcmp(a->dr->info,"integr\0")!=0&&strcmp(a->dr->info,"abs\0")!=0&&strcmp(a->st->info,"/\0")!=0&&strcmp(a->st->info,"ctg\0")!=0&&strcmp(a->st->info,"tg\0")!=0&&strcmp(a->st->info,"cos\0")!=0&&strcmp(a->st->info,"sin\0")!=0&&strcmp(a->st->info,"ctg\0")!=0&&strcmp(a->st->info,"arctg\0")!=0&&strcmp(a->st->info,"arccos\0")!=0&&strcmp(a->st->info,"arcsin\0")!=0&&strcmp(a->st->info,"ln\0")!=0&&strcmp(a->st->info,"lg\0")!=0&&strcmp(a->st->info,"rad\0")!=0&&strcmp(a->st->info,"^\0")!=0)
            {
                deseneazaParanteza(stanga+marime_x(a->st)-marime_x(a->st)/100,y-cautare_fracs(a->st)-paranteze_numitor(a->dr)+4,stanga+marime_x(a->st)-marime_x(a->st)/100,y+cautare_fracd(a->st)+16,stanga+marime_x(a->st)+marime_x(a->st)/100+8);
                deseneazaParanteza(stanga+marime_x(a->st)/100,y-cautare_fracs(a->st)-paranteze_numitor(a->dr)+4,stanga+marime_x(a->st)/100,y+cautare_fracd(a->st)+16,stanga-marime_x(a->st)/100-8);
                ok++;
            }
            if(nrColoane(a->dr)>1&&strcmp(a->dr->info,"lim\0")!=0&&strcmp(a->dr->info,"g\0")!=0&&strcmp(a->dr->info,"f\0")!=0&&strcmp(a->dr->info,"*\0")!=0&&strcmp(a->dr->info,"sum\0")!=0&&strcmp(a->dr->info,"integr\0")!=0&&strcmp(a->dr->info,"`\0")!=0&&strcmp(a->dr->info,"log\0")!=0&&strcmp(a->dr->info,"rad\0")!=0&&strcmp(a->dr->info,"abs\0")!=0&&strcmp(a->dr->info,"^\0")!=0&&strcmp(a->dr->info,"/\0")!=0&&strcmp(a->dr->info,"sin\0")!=0&&strcmp(a->dr->info,"cos\0")!=0&&strcmp(a->dr->info,"arcsin\0")!=0&&strcmp(a->dr->info,"arccos\0")!=0&&strcmp(a->dr->info,"tg\0")!=0&&strcmp(a->dr->info,"ctg\0")!=0&&strcmp(a->dr->info,"arctg\0")!=0&&strcmp(a->dr->info,"arcctg\0")!=0&&strcmp(a->dr->info,"ln\0")!=0&&strcmp(a->dr->info,"lg\0")!=0)
            {

                deseneazaParanteza(stanga+marime_x(a)-8,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga+marime_x(a)-8,y+cautare_fracd(a->dr)+16,stanga+marime_x(a)+marime_x(a->dr)/100);
                deseneazaParanteza(stanga+marime_x(a->st)+marime_x(a->st)/100+8+marime_x(a->dr)/100,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga+marime_x(a->st)+marime_x(a->st)/100+8+marime_x(a->dr)/100,y+cautare_fracd(a->dr)+16,stanga+marime_x(a->st)+marime_x(a->st)/100);
                ok+=2;

            }

            if(ok==1)
            {
                deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a->st)+marime_x(a->st)/100+32);
                outtextxy(stanga+marime_x(a->st)+marime_x(a->st)/100+8, y-16, ".\0");
                deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a->st)/100+8);

            }
            if(ok==2)
            {
                if(nrColoane(a->st)>1&&strcmp(a->st->info,"*\0")!=0)
                    outtextxy(stanga+marime_x(a)-marime_x(a->dr)-32, y-16, ".\0");

                if(nrColoane(a->st)==1)
                {
                    deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr));
                    deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+12);
                }
                else if(nrColoane(a->st)>1&&strcmp(a->st->info,"*\0")==0&&(nrColoane(a->st->st)==1||nrColoane(a->st->dr)==1))
                {
                    outtextxy(stanga+marime_x(a)-marime_x(a->dr)-32, y-16, ".\0");
                    deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a->st)+marime_x(a->dr)/100+26);
                    deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);
                }
                else
                {
                    deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr)+marime_x(a->dr)/100+4);
                    deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);
                }
            }
            if(ok==3)
            {
                deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr)+8);
                deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a->st)/100+8);
            }
            if(ok==0)
            {

                if(strcmp(a->dr->info,"^\0")==0&&strcmp(a->st->info,"^\0")==0)
                {
                    deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a->st));
                    deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);

                }
                else
                {
                    outtextxy(stanga+marime_x(a)-marime_x(a->dr)-20, y-16, ".\0");
                    deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr)+6);
                    deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);

                }

            }
        }

    }
    else if(strcmp(a->info,"-\0")==0&&a->st==NULL)
    {
        if(strcmp(a->dr->info,"-\0")==0||strcmp(a->dr->info,"+\0")==0)
        {
            deseneazaParanteza(stanga+marime_x(a)-marime_y(a->dr)/50+min(marime_x(a->dr)/100,8)-16,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga-marime_y(a->dr)/50+min(marime_x(a->dr)/100,8)+marime_x(a)-16,y+cautare_fracd(a->dr)+16,stanga+marime_x(a)+min(marime_x(a->dr)/100,8)-8);
            deseneazaParanteza(stanga+marime_x(a->st)+32+marime_y(a->dr)/50,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga+marime_x(a->st)+32+marime_y(a->dr)/50,y+cautare_fracd(a->dr)+16,stanga+marime_x(a->st)+20-marime_y(a->dr)/100);
        }
        outtextxy(stanga+marime_x(a->st)+8, y-10, "-\0");
        deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr)-4);

    }
    else if(strcmp(a->info,"-\0")==0&&(strcmp(a->dr->info,"-\0")==0||strcmp(a->dr->info,"+\0")==0))
    {
        deseneazaParanteza(stanga+marime_x(a)-marime_y(a->dr)/50+min(marime_x(a->dr)/100,8)-16,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga-marime_y(a->dr)/50+min(marime_x(a->dr)/100,8)+marime_x(a)-16,y+cautare_fracd(a->dr)+16,stanga+marime_x(a)+min(marime_x(a->dr)/100,8)-8);
        deseneazaParanteza(stanga+marime_x(a->st)+32+marime_y(a->dr)/50,y-cautare_fracs(a->dr)-paranteze_numitor(a->dr)+4,stanga+marime_x(a->st)+32+marime_y(a->dr)/50,y+cautare_fracd(a->dr)+16,stanga+marime_x(a->st)+20-marime_y(a->dr)/100);

        outtextxy(stanga+marime_x(a->st)+8, y-10, "-\0");
        deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr)-4);
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);

    }
    else if(strcmp(a->info,"-\0")==0||strcmp(a->info,"+\0")==0)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        setbkcolor(BLACK);
        setcolor(WHITE);
        outtextxy(stanga+marime_x(a->st), y-10, expresie);

        deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr));
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);

    }
    else if(strcmp(a->info,"f\0")==0||strcmp(a->info,"g\0")==0||strcmp(a->info,"arctg\0")==0||strcmp(a->info,"arcctg\0")==0||strcmp(a->info,"arcsin\0")==0||strcmp(a->info,"arccos\0")==0||strcmp(a->info,"tg\0")==0||strcmp(a->info,"ctg\0")==0||strcmp(a->info,"sin\0")==0||strcmp(a->info,"cos\0")==0||strcmp(a->info,"ln\0")==0||strcmp(a->info,"lg\0")==0)
    {
        deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-16,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-8);
        deseneazaParanteza(stanga+textwidth(expresie)+8+marime_x(a->st)/150,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+textwidth(expresie)+8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+textwidth(expresie)-marime_x(a->st)/150);

        outtextxy(stanga, y-10, expresie);
        if(strcmp(a->info,"f\0")==0)
            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)+4);
        else
            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a));

    }
    else if (strcmp(a->info, "abs") == 0)
    {
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+12);
        line(stanga+marime_x(a)-marime_x(a->dr)-16,y-cautare_fracs(a->st)-paranteze_numitor(a),stanga+marime_x(a)-marime_x(a->dr)-16,y+cautare_fracd(a->st)+16);
        line(stanga,y-cautare_fracs(a->st)-paranteze_numitor(a),stanga,y+cautare_fracd(a->st)+16);

    }
    else if (strcmp(a->info, "rad") == 0)
    {
        int distanta=0;
        if(a->dr&&strcmp(a->dr->info,"2")!=0)
        {
            int mij=(y-cautare_fracs(a->st)-paranteze_numitor(a)+y+cautare_fracd(a->st)+8)/2;
            deseneazaExpresieGrafic2(a->dr,mij-cautare_fracd(a->dr)-10,1,stanga-marime_x(a->st)/100);
            distanta=textwidth(a->dr->info)*75/100;
        }

            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+distanta+16+marime_x(a->st)/100);
        deseneazaRadical(stanga+marime_x(a)-16,y-cautare_fracs(a->st)-paranteze_numitor(a),stanga+distanta,y+cautare_fracd(a->st)+8,stanga-marime_x(a->st)/100-8+distanta);


    }
    else if (strcmp(a->info, "log") == 0)
    {

        if(strcmp(a->dr->info,"e")==0)
        {
            if(nrColoane(a->st)>1)
            {
                deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-32,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-32,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-24);
                deseneazaParanteza(stanga+textwidth(expresie)-8+marime_x(a->st)/150+marime_x(a->dr),y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+marime_x(a->dr)+textwidth(expresie)-8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+marime_x(a->dr)-16+textwidth(expresie)-marime_x(a->st)/150);

            }
            outtextxy(stanga+16, y-10, "ln");
            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)-16);
        }

        else if(strcmp(a->dr->info,"10")==0)
        {
            if(nrColoane(a->st)>1)
            {
                deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-32,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-32,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-24);
                deseneazaParanteza(stanga+textwidth(expresie)-8+marime_x(a->st)/150+marime_x(a->dr),y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+marime_x(a->dr)+textwidth(expresie)-8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+marime_x(a->dr)-16+textwidth(expresie)-marime_x(a->st)/150);

            }
            outtextxy(stanga+16, y-10, "lg");
            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)-16);
        }

        else
        {
            if(nrColoane(a->st)>1)
            {
                deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-16,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-8);
                deseneazaParanteza(stanga+textwidth(expresie)+8+marime_x(a->st)/150+marime_x(a->dr),y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+marime_x(a->dr)+textwidth(expresie)+8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+marime_x(a->dr)+textwidth(expresie)-marime_x(a->st)/150);

            }

            outtextxy(stanga, y-10, expresie);
            deseneazaExpresieGrafic2(a->dr,y+cautare_fracs(a->dr),1,stanga+marime_x(a)-marime_x(a->st)-marime_x(a->dr)-12);

            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a));
        }


    }
    else if (strcmp(a->info, "`") == 0)
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        setbkcolor(BLACK);
        setcolor(WHITE);
        if((nrColoane(a->st)>1||a->st->info[0]=='-')&&strcmp(a->st->info,"f\0")!=0&&strcmp(a->st->info,"g\0")!=0)
        {
            deseneazaParanteza(stanga+marime_x(a->st)-marime_x(a->st)/100-6,y-cautare_fracs(a->st)-paranteze_numitor(a->st),stanga+marime_x(a->st)-marime_x(a->st)/100-6,y+cautare_fracd(a->st)+16,stanga+marime_x(a->st)+marime_x(a->st)/100+6);
            deseneazaParanteza(stanga+marime_x(a->st)/150,y-cautare_fracs(a->st)-paranteze_numitor(a->st),stanga+marime_x(a->st)/100,y+cautare_fracd(a->st)+16,stanga-marime_x(a->st)/100-8);


        }
        outtextxy(stanga+marime_x(a->st),y-cautare_fracs(a->st)-cautare_fracd(a->dr)-paranteze_numitor(a->st)-8,"'");
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+12);
    }
    else if (strcmp(a->info, "integr") == 0)
    {
        if(nrColoane(a->st)>1)
        {
            deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16-textwidth(expresie)*3/6,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-textwidth(expresie)*3/6-marime_y(a->st)/150+marime_x(a)-16,y+cautare_fracd(a->st)+16,stanga-textwidth(expresie)*3/6+marime_x(a)+marime_x(a->st)/150-8);
            deseneazaParanteza(stanga+textwidth(expresie)*3/6+8+marime_x(a->st)/150,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+textwidth(expresie)*3/6+8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+textwidth(expresie)*3/6-marime_x(a->st)/150);
        }
        char s[10];
        strcpy(s,"d");
        strcat(s,cautare_variabila(a));

        if(strcmp(s,"dx1")==0)
            strcpy(s+2,s+3);
        outtextxy(stanga-textwidth(expresie)*3/6+marime_x(a)+marime_x(a->st)/150-12,y-10,s);
        deseneazaSemnIntegrala(stanga,stanga+textwidth(expresie)*4/6,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,y+cautare_fracd(a->st)+16);
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)-textwidth(expresie)*3/6);
    }
    else if (strcmp(a->info, "sum") == 0)
    {

        if(marime_y(a->st)*8/10<48)
        {
            deseneazaSemnSuma(stanga,stanga+48,y-48,y,a);
            deseneazaExpresieGrafic2(a->st,y-20,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)-8);
            deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16,y-44,stanga-marime_y(a->st)/150+marime_x(a)-16,y,stanga+marime_x(a)+marime_x(a->st)/150-8);
            deseneazaParanteza(stanga+48+8+marime_x(a->st)/150,y-44,stanga+48+8+marime_x(a->st)/150,y,stanga+marime_y(a->st)*8/10-marime_x(a->st)/150);

        }
        else
        {
            if(nrColoane(a->st)>1)
            {
                deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-16,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-8);
                deseneazaParanteza(stanga+marime_y(a->st)*8/10+8+marime_x(a->st)/150,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+marime_y(a->st)*8/10+8+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+marime_y(a->st)*8/10-marime_x(a->st)/150);
            }
            deseneazaSemnSuma(stanga,stanga+marime_y(a->st)*8/10,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,y+cautare_fracd(a->st)+16,a);
            deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a));
        }
    }
    else if (strcmp(a->info, "lim") == 0)
    {
        if(nrColoane(a->st)>1)
        {
            deseneazaParanteza(stanga+marime_x(a)-marime_y(a->st)/150-16,y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga-marime_y(a->st)/150+marime_x(a)-16,y+cautare_fracd(a->st)+16,stanga+marime_x(a)+marime_x(a->st)/150-8);
            deseneazaParanteza(stanga+textwidth(expresie)+10+marime_x(a->st)/150+max(16,marime_x(a->dr)),y-cautare_fracs(a->st)-paranteze_numitor(a->st)+4,stanga+max(16,marime_x(a->dr))+textwidth(expresie)+10+marime_x(a->st)/150,y+cautare_fracd(a->st)+16,stanga+max(16,marime_x(a->dr))+textwidth(expresie)-marime_x(a->st)/150);

        }
        char s[100];
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        if(strcmp(cautare_variabila(a),"x1")==0)
            strcpy(s,"x");
        else
            strcpy(s,cautare_variabila(a));
        strcat(s,"->");
        if(a->dr)
        {
            strcat(s,a->dr->info);
            outtextxy(stanga,y+cautare_fracs(a->dr),s);
        }
        else
        {
            outtextxy(stanga,y+12,s);
            deseneazaSimbolInfinit(stanga+30,y+23,8);

        }

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        if(nrColoane(a->st)==1)
        {
            outtextxy(stanga+5, y-10, expresie);
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a)-20);

        }
        else{

            outtextxy(stanga, y-10, expresie);
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga+marime_x(a)-marime_x(a->st)-paranteze_numitor(a));
        }



    }
    else
    {
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, marimefont);
        setbkcolor(BLACK);
        setcolor(WHITE);
        outtextxy(stanga+marime_x(a->st)-8, y-10, expresie);

        deseneazaExpresieGrafic2(a->dr,y,marimefont,stanga+marime_x(a)-marime_x(a->dr));
        deseneazaExpresieGrafic2(a->st,y,marimefont,stanga);

    }
}


const int LATIME_FEREASTRA = 1920;
const int INALTIME_FEREASTRA = 1000;


const int LATIME_BUTON = 40;
const int INALTIME_BUTON = 40;


const int POZITIE_MENIU_X = LATIME_FEREASTRA - 300;

const int POZITIE_MENIU_Y = INALTIME_FEREASTRA - 250;

void afiseazaInstructiuni(char titlu[],  char instructiuni[])
{

    cleardevice();

    int width = getmaxx();
    int height = getmaxy();
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("background.jpg", 0, 0, getmaxx(), getmaxy());

    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    outtextxy(width / 2 - textwidth(titlu) / 2, 20, titlu);


    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    int yOffset = 100;
    char* token = strtok(instructiuni, "\n");

    while (token)
    {
        outtextxy(960-textwidth(token)/2, yOffset, token);
        yOffset += textheight(token) + 10;
        token = strtok(NULL, "\n");
    }

    while(!(GetAsyncKeyState(VK_BACK)))
    {

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            closegraph();
            exit(0);
        }
    }


    return;




}

void deseneazaSageata(int x, int y, const char* directie)
{
    setcolor(WHITE);
    if (strcmp(directie, "SUS") == 0)
    {
        line(x + 20, y + 40, x + 40, y + 20);
        line(x + 40, y + 20, x + 60, y + 40);
    }
    else if (strcmp(directie, "JOS") == 0)
    {
        line(x + 20, y + 20, x + 40, y + 40);
        line(x + 40, y + 40, x + 60, y + 20);
    }
    else if (strcmp(directie, "STANGA") == 0)
    {
        line(x + 40, y + 20, x + 20, y + 40);
        line(x + 20, y + 40, x + 40, y + 60);
    }
    else if (strcmp(directie, "DREAPTA") == 0)
    {
        line(x + 20, y + 20, x + 40, y + 40);
        line(x + 40, y + 40, x + 20, y + 60);
    }
}


void deseneazaMeniuButoane()
{
    setfillstyle(SOLID_FILL, CYAN);

    bar(POZITIE_MENIU_X + 70, POZITIE_MENIU_Y, POZITIE_MENIU_X + 130, POZITIE_MENIU_Y + 60);
    rectangle(POZITIE_MENIU_X + 69, POZITIE_MENIU_Y-1, POZITIE_MENIU_X + 131, POZITIE_MENIU_Y + 61);
    deseneazaSageata(POZITIE_MENIU_X + 60, POZITIE_MENIU_Y, "SUS");


    bar(POZITIE_MENIU_X + 70, POZITIE_MENIU_Y + 100, POZITIE_MENIU_X + 130, POZITIE_MENIU_Y + 160);
    rectangle(POZITIE_MENIU_X + 69, POZITIE_MENIU_Y + 99, POZITIE_MENIU_X + 131, POZITIE_MENIU_Y + 161);
    deseneazaSageata(POZITIE_MENIU_X + 60, POZITIE_MENIU_Y + 100, "JOS");

    bar(POZITIE_MENIU_X, POZITIE_MENIU_Y + 50, POZITIE_MENIU_X + 60, POZITIE_MENIU_Y + 110);
    rectangle(POZITIE_MENIU_X-1, POZITIE_MENIU_Y + 51, POZITIE_MENIU_X + 59, POZITIE_MENIU_Y + 109);
    deseneazaSageata(POZITIE_MENIU_X, POZITIE_MENIU_Y + 40, "STANGA");

    bar(POZITIE_MENIU_X + 140, POZITIE_MENIU_Y + 50, POZITIE_MENIU_X + 200, POZITIE_MENIU_Y + 110);
    rectangle(POZITIE_MENIU_X + 139, POZITIE_MENIU_Y + 49, POZITIE_MENIU_X + 201, POZITIE_MENIU_Y + 111);
    deseneazaSageata(POZITIE_MENIU_X + 140, POZITIE_MENIU_Y + 40, "DREAPTA");
}
void intToCharArray(int number, char* buffer) {
    sprintf(buffer, "%d", number);
}
void afiseazaMesajEroare(char s[],int poz)
{
    cleardevice();
    setcolor(WHITE);
    rectangle(100, 250, 1850, 650);
    setfillstyle(SOLID_FILL, CYAN);
    bar(101, 251, 1849, 649);
    setbkcolor(CYAN);
    setcolor(WHITE);

    outtextxy(150, 300, "FORMULA INTRODUSA NU ESTE CORECTA" );
    outtextxy(150, 350, "Eroarea este urmatoarea:" );
    setcolor(RED);
    outtextxy(150, 400, s );
    setcolor(WHITE);
    char pozi[100];
    strcpy(pozi,"Greseala se afla la pozitia: ");
    char aux[10];
    intToCharArray(poz,aux);
    strcat(pozi,aux);

    outtextxy(150, 450, pozi );




}


void deseneazaButon1(int x1, int y1, int latime, int inaltime,  char* text)
{
    rectangle(x1, y1, x1 + latime, y1 + inaltime);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(x1 + latime/2-textwidth(text)/2, y1 + inaltime / 4, text);

}


void deseneazaMeniuPrincipal()
{
    closegraph();
    initwindow(LATIME_FEREASTRA,INALTIME_FEREASTRA,"Vizualizator Formula Matematica si Arbore");

    setcolor(WHITE);
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("background.jpg", 0, 0, getmaxx(), getmaxy());
    setfillstyle(SOLID_FILL, CYAN);

    deseneazaButon1(600, 350, 600, 50, "VIZUALIZARE ARBORE");

    deseneazaButon1(600, 550, 600, 50, "VIZUALIZARE FORMULA");


}
bool clickPeButon(int x1, int y1, int latime, int inaltime, int mouseX, int mouseY)
{
    return mouseX >= x1 && mouseX <= x1 + latime && mouseY >= y1 && mouseY <= y1 + inaltime;
}


nod *radcal,*radfis;
void gestioneazaMiscarea(nod* rad,char s[500])
{
    Pair verif;
    verif=estecorect(s,0,strlen(s));

    if(verif.corect)
    {

        setcolor(WHITE);
        setbkcolor(BLACK);
        cleardevice();
        int ok=0;
        while (!(GetAsyncKeyState(VK_BACK)))
        {
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                closegraph();
                exit(0);
            }


            if(ok==0)
            {
                cleardevice();
                deseneazaMeniuPrincipal();
                ok=1;

            }


            if (ismouseclick(WM_LBUTTONDOWN))
            {
                int mouseX, mouseY;
                getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
                if(clickPeButon(600, 550, 600, 50,mouseX,mouseY))
                {

                    setcolor(WHITE);
                    setbkcolor(BLACK);
                    cleardevice();

                    int x = LATIME_FEREASTRA / 2-marime_x(rad)/2, y = INALTIME_FEREASTRA / 2;
                    deseneazaMeniuButoane();
                    deseneazaExpresieGrafic2(rad,y,3,x);
                    int unitate_x=marime_x(rad)/4;
                    int unitate_y=marime_y(rad)/4;
                    while (!(GetAsyncKeyState(VK_BACK)))
                    {
                        if (GetAsyncKeyState(VK_ESCAPE))
                        {
                            closegraph();
                            exit(0);
                        }

                        if (GetAsyncKeyState(VK_UP))
                        {
                            cleardevice();
                            deseneazaMeniuButoane();
                            y =  y - unitate_y;
                            deseneazaExpresieGrafic2(rad,y,3,x);
                        }
                        else if (GetAsyncKeyState(VK_DOWN))
                        {
                            cleardevice();
                            deseneazaMeniuButoane();
                            y = y + unitate_y;
                            deseneazaExpresieGrafic2(rad,y,3,x);
                        }
                        else if (GetAsyncKeyState(VK_LEFT))
                        {
                            cleardevice();
                            deseneazaMeniuButoane();
                            x =  x - unitate_x;
                            deseneazaExpresieGrafic2(rad,y,3,x);
                        }
                        else if (GetAsyncKeyState(VK_RIGHT))
                        {
                            cleardevice();
                            deseneazaMeniuButoane();
                            x =  x + unitate_x;
                            deseneazaExpresieGrafic2(rad,y,3,x);
                        }
                        delay(0);
                    }
                    cleardevice();


                }
                else if(clickPeButon(600, 350, 600, 50,mouseX,mouseY))
                {
                    setcolor(WHITE);
                    setbkcolor(BLACK);
                    cleardevice();
                    latime=LATIME_FEREASTRA/nrColoane(rad);
                    inaltime=INALTIME_FEREASTRA/nrNiveluri(rad);
                    deseneazaArbore(rad,1,0,latime,inaltime);
                    while (!(GetAsyncKeyState(VK_BACK)))
                    {
                        if (GetAsyncKeyState(VK_ESCAPE))
                        {
                            closegraph();
                            exit(0);
                        }
                    }
                    closegraph();
                    initwindow(LATIME_FEREASTRA,INALTIME_FEREASTRA,"Vizualizator Formula Matematica si Arbore");
                    cleardevice();
                }

            }
        }
        return;

    }



    else
    {
        afiseazaMesajEroare(verif.mesaj,verif.poz);
        while(!(GetAsyncKeyState(VK_ESCAPE)))
        {
        }
        exit(0);
    }


}

void deseneazaButon(int x1, int y1, int latime, int inaltime,  char* text)
{
    rectangle(x1, y1, x1 + latime, y1 + inaltime);
    floodfill(x1+1,y1+1,WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    if(strcmp("integr",text)==0||strcmp("arccos",text)==0||strcmp("arctg",text)==0||strcmp("arcsin",text)==0||strcmp("arcctg",text)==0)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(x1 + latime /8, y1 + inaltime / 3, text);
    }
    else
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(x1 + latime/2-textwidth(text)/2, y1 + inaltime / 4, text);
    }
}



void interfataTrigonometrie(char * expresie)
{
    int latimeButon = 120, inaltimeButon = 60;
    int xStart = 490, yStart = 500;  // Începe din dreptul butonului "TRIG"

    setfillstyle(SOLID_FILL, BLACK);
    bar(xStart, yStart, xStart + 2 * (latimeButon + 10), yStart + 4 * (inaltimeButon + 10));

    setcolor(WHITE);
    char* functiiTrigonometrice[] = {"sin", "cos", "tg", "ctg", "arcsin", "arccos", "arctg", "arcctg"};

    for (int i = 0; i < 8; i++)
    {
        int x1 = xStart + (i % 2) * (latimeButon + 10);
        int y1 = yStart + (i / 2) * (inaltimeButon + 10);
        setfillstyle(SOLID_FILL, MAGENTA);
        setbkcolor(MAGENTA);
        deseneazaButon(x1, y1, latimeButon, inaltimeButon, functiiTrigonometrice[i]);
    }

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            for (int i = 0; i < 8; i++)
            {
                int x1 = xStart + (i % 2) * (latimeButon + 10);
                int y1 = yStart + (i / 2) * (inaltimeButon + 10);
                if (clickPeButon(x1, y1, latimeButon, inaltimeButon, mouseX, mouseY))
                {
                    strcat(expresie,functiiTrigonometrice[i]);
                    cleardevice();
                    return;
                }
            }
        }
    }
}


int calculeazacoordcaracter(int xstart,char s[],int poz)
{
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    for(int i=0; i<poz; i++)
    {
        char sir[2] = {s[i], '\0'};
        xstart+=textwidth(sir);

    }


    return xstart;

}



void interfataCalculator(char* expresie)
{
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, 1920, 1080);
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    rectangle(100, 50, 1800, 150);
    if(expresie[0]==NULL)
        outtextxy(110, 70, "Introdu expresia matematica:");
    else
        outtextxy(110, 70, expresie);

    int xStart = 100, yStart = 200;
    int latimeButon = 120, inaltimeButon = 60;

    char butoane[4][6] =
    {
        {'7', '8', '9', '+', '^','x'},
        {'4', '5', '6', '-', '`','y'},
        {'1', '2', '3', '*', '(',')'},
        {'.', '0', 'C', '/', 'f','g'}
    };

    char* butoaneAvansate[] = {"log", "ln", "lg", "lim", "sum","TRIG","rad","abs","integr"};
    setfillstyle(SOLID_FILL, CYAN);
    setbkcolor(CYAN);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int x1 = xStart + j * (latimeButon + 10);
            int y1 = yStart + i * (inaltimeButon + 10);
            char buton[2] = {butoane[i][j], '\0'};

            deseneazaButon(x1, y1, latimeButon, inaltimeButon, buton);
        }
    }
    setfillstyle(SOLID_FILL, MAGENTA);
    setbkcolor(MAGENTA);
    for (int i = 0; i < 9; i++)
    {
        int x1 = 100 + (i % 3) * (latimeButon + 10);
        int y1 = 500 + (i / 3) * (inaltimeButon + 10);
        deseneazaButon(x1, y1, latimeButon, inaltimeButon, butoaneAvansate[i]);
    }
    setfillstyle(SOLID_FILL, RED);
    setbkcolor(RED);
    deseneazaButon(100, 800, 500, 50, "Vizualizeaza");
    deseneazaButon(1600,200,200,50,"Preview");



    int index = strlen(expresie);


    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            closegraph();
            exit(0);
        }
        if (kbhit())
        {
            char c = getch();
            if (c == '\r')
                break;
            if (c == '\b' && index > 0)
            {
                index--;
                expresie[index] = '\0';
            }
            else if (isprint(c))
            {
                expresie[index++] = c;
                expresie[index] = '\0';
            }
            setfillstyle(SOLID_FILL, BLACK);
            setbkcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            bar(110, 70, 1790, 140);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

            outtextxy(110, 70, expresie);
        }

        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    int x1 = xStart + j * (latimeButon + 10);
                    int y1 = yStart + i * (inaltimeButon + 10);
                    if (clickPeButon(x1, y1, latimeButon, inaltimeButon, mouseX, mouseY))
                    {
                        char c = butoane[i][j];
                        if (c != 'C')
                        {
                            expresie[index++] = c;
                            expresie[index] = '\0';
                            setfillstyle(SOLID_FILL, BLACK);
                            setfillstyle(SOLID_FILL, BLACK);
                            setbkcolor(BLACK);
                            bar(110, 70, 1790, 140);
                            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                            outtextxy(110, 70, expresie);
                        }
                        else
                        {
                            strcpy(expresie,"\0");
                            interfataCalculator(expresie);
                        }
                    }
                }
            }

            for (int i = 0; i < 9; i++)
            {
                int x1 = 100 + (i % 3) * (latimeButon + 10);
                int y1 = 500 + (i / 3) * (inaltimeButon + 10);
                if (clickPeButon(x1, y1, latimeButon, inaltimeButon, mouseX, mouseY))
                {
                    if (strcmp(butoaneAvansate[i], "TRIG") == 0)
                    {
                        interfataTrigonometrie(expresie);
                        interfataCalculator(expresie);
                        setfillstyle(SOLID_FILL, BLACK);
            setbkcolor(BLACK);
                    }
                    else
                    {
                        strcat(expresie, butoaneAvansate[i]);
                        index=strlen(expresie);
                        setfillstyle(SOLID_FILL, BLACK);
                        setbkcolor(BLACK);

                        bar(110, 70, 1790, 140);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

                        outtextxy(110, 70, expresie);
                    }
                }
            }

            Pair verif;
            verif=estecorect(expresie,0,strlen(expresie));
            if (clickPeButon(100, 800, 500, 50, mouseX, mouseY))
            {
                if(verif.corect==0)
                {
                    rectangle(899,299,1801,901);

                    setfillstyle(SOLID_FILL, CYAN);
                    bar(900, 300, 1800, 900);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(925, 325, 1775, 875);
                    rectangle(926,326,1774,874);
                    settextstyle(1, HORIZ_DIR,2);
                    setcolor(RED);
                    outtextxy(1350-textwidth(verif.mesaj)/2,600,verif.mesaj);

                    int poz_greseala=calculeazacoordcaracter(110,expresie,verif.poz);
                    line(poz_greseala,100,poz_greseala,135);
                    line(poz_greseala,100,poz_greseala-7,120);
                    line(poz_greseala,100,poz_greseala+7,120);
                    setcolor(WHITE);
                }
                else
                {


                    radcal=rez(0,strlen(expresie)-1,expresie);
                    gestioneazaMiscarea(radcal,expresie);
                    cleardevice();
                    closegraph();
                    initwindow(LATIME_FEREASTRA,INALTIME_FEREASTRA,"Vizualizator Formula Matematica si Arbore");
                    interfataCalculator(expresie);

                }
            }
            else if (clickPeButon(1600,200,200,50, mouseX, mouseY))
            {
                rectangle(899,299,1801,901);

                setfillstyle(SOLID_FILL, CYAN);
                bar(900, 300, 1800, 900);
                setfillstyle(SOLID_FILL, BLACK);
                bar(925, 325, 1775, 875);
                rectangle(926,326,1774,874);
                if(verif.corect==1)
                {
                    radcal=rez(0,strlen(expresie)-1,expresie);

                    if(marime_x(radcal)<1400&&cautare_fracd(radcal)<300&&cautare_fracs(radcal)<300)
                        deseneazaExpresieGrafic2(radcal,600,3,1350-marime_x(radcal)/4);
                    else
                        outtextxy(1350-textwidth("Expresia este prea mare")/2,600,"Expresia este prea mare");

                }
                else
                {
                    int poz_greseala=calculeazacoordcaracter(110,expresie,verif.poz);
                    setcolor(RED);
                    line(poz_greseala+10,100,poz_greseala+10,135);
                    line(poz_greseala+10,100,poz_greseala+3,120);
                    line(poz_greseala+10,100,poz_greseala+18,120);
                    setcolor(WHITE);
                    settextstyle(1, HORIZ_DIR,2);
                    setcolor(RED);
                    outtextxy(1350-textwidth(verif.mesaj)/2,600,verif.mesaj);
                    setcolor(WHITE);
                }

            }
        }
    }
    return;
}

bool stare=0;
void creeazaFereastraStart()
{

    while(!(GetAsyncKeyState(VK_ESCAPE)))
    {
        if(stare==0)
        {
            readimagefile("background.jpg", 0, 0, getmaxx(), getmaxy());


            settextstyle(BOLD_FONT, HORIZ_DIR, 8);
            setcolor(LIGHTCYAN);

            outtextxy(getmaxx() / 2 - textwidth("Vizualizator de Formule") / 2, 200 - textheight("Vizualizator de Formule") / 2, "Vizualizator de Formule");



            deseneazaButon1(600, 350, 700, 50, "Vizualizare din fisier");
            deseneazaButon1(600, 450, 700, 50, "Calculator stiintific");
            deseneazaButon1(600, 550, 700, 50, "Instructiuni de folosire");
            stare=1;
        }






        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

            if (clickPeButon(600, 350, 700, 50, mouseX, mouseY))
            {
                radfis=rez(0,strlen(s)-1,s);
                gestioneazaMiscarea(radfis,s);
                cleardevice();
                stare=0;

            }
            if (clickPeButon(600, 450, 700, 50, mouseX, mouseY))
            {
                char expresie[500];
                strcpy(expresie,"\0");
                interfataCalculator(expresie);
                cleardevice();


            }
            if (clickPeButon(600, 550, 700, 50, mouseX, mouseY)||GetAsyncKeyState(VK_TAB))
            {
                char titlu[30],instructiuni[1000000];

                strcpy(titlu, "Instructiuni de folosire");

                strcpy(instructiuni, "log(x)(y)-logaritmul format din baza x si formula y \n ln(x)-logaritm natural din x \n lg(x)-logaritm din baza 10 din x \n rad(x)-radical de ordinul 2 din a \n rad(x)(y)-radicalul de ordinul y din x \n sum(x)(y)-suma de la y pana la infinit din x \n sum(x)-suma din x \n lim(a)(b)-limita cu x->a din b \n lim(a)-limita cu x->infinit din a \n (x)`-derivata din x \n integr(x)-integrala din x \n abs(x)-modul din x \n x^y-x la puterea y \n x/y-x de impartit la y \n sin(x)-sinus din x \n cos(x)-cosinus din x \n tg(x)-tangenta din x \n ctg(x)-cotangenta din x \n arcsin(x)-arcsinus din x \n arccos(x)-arccosinus din x \n arctg(x)-arctangenta din x \n arcctg(x)-arccotangenta din x \n f(x)-functia f de x \n g(x)-functia g de x\n_____________________________________________________________________________\nApasati ESC pentru a inchide aplicatia\nApasati Back pentru a reveni la meniul anterior\n\n\nProiect realizat de: Brezuleanu Petru Giuliano si Ciocan Radu \0");
                afiseazaInstructiuni(titlu, instructiuni);
                cleardevice();
                stare=0;



            }

        }


    }




    closegraph();
    exit(0);
}
int main()
{
    /*
       fin.getline(s,500);
       rad=rez(0,strlen(s)-1);
       rsd(rad);
       latime=LATIME_FEREASTRA/nrColoane(rad);
       inaltime=INALTIME_FEREASTRA/nrNiveluri(rad);
    */
    fin.getline(s,500);
    initwindow(LATIME_FEREASTRA,INALTIME_FEREASTRA,"Vizualizator Formula Matematica si Arbore");
    creeazaFereastraStart();
    //gestioneazaMiscarea(rad,s);

    /*initwindow(LATIME_FEREASTRA,INALTIME_FEREASTRA,"Vizualizator Formula Matematica si Arbore");
    setcolor(WHITE);
    setbkcolor(BLACK);
    cleardevice();
    rectangle(1,1,LATIME_FEREASTRA-1,INALTIME_FEREASTRA-1);

    interfataCalculator(s);
    cout<<s;*/
    //deseneazaExpresieGrafic2(rad,INALTIME_FEREASTRA/2,3,LATIME_FEREASTRA/2-marime_x(rad)/2-marime_x(rad)/8);
    //deseneazaArbore(rad,1,0,latime,inaltime);

    return 0;
}
