#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DOSYA_YOLU  "devre.txt"
#define DEGER "deger.txt"
#include <time.h>

struct eleman{
    char name;
    int deger;

};

struct kapi{
    int g;
    char name[10];
    struct eleman in[5];
    struct eleman cout;
    int delay;

};

int dosyadanOku(FILE *log1,FILE *f,struct eleman g[4],struct eleman out[2],struct kapi kapilar[6]);
void iliklendirme(FILE *log1,FILE *p,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac);
void Higher(FILE *log1,FILE *sim,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut);
void Lower(FILE *log1,FILE *sim,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut);
void Goster(FILE *log1,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut);
void komutK (FILE *sim,FILE *f,FILE *p,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac);
void Simulation(FILE *log1,FILE *sim);

int main()
{   time_t z;
    struct tm *zaman;
    struct kapi kapilar[6];
    struct eleman g[4],out[2];
    char komut[6],komut2;
    int n,sayac=0,i,j;
    FILE *f;
    FILE *p;
    FILE *sim;
    FILE *log1;
    log1=fopen("log1.txt","w");
    printf(">");
    scanf("%s",&komut);
            if(komut[0]=='y' || komut[0]=='Y') {//yükleme
                time(&z);
                zaman=localtime(&z);
                fprintf(log1,"%s %c devre.txt yuklendi.",asctime(zaman),komut[0]);
                 n=dosyadanOku(log1,f,g,out,kapilar);

            }
            //ana giris eleman sayisi
                else{ printf("Devre yuklenmeden program calisamaz.");
                    exit(1);
                }
    char s[6];
    for(i=0;i<6;i++){ //kapı sayisi
        for(j=0;j<strlen(kapilar[i].name);j++){
            s[j]=kapilar[i].name[j];
        }
        s[j]='\0';

        if((strcmp(s,"NOR")== 0))
            sayac++;
        if((strcmp(s,"XOR")== 0))
            sayac++;
        if((strcmp(s,"NAND")== 0))
            sayac++;
        if((strcmp(s,"AND")== 0))
            sayac++;
        if((strcmp(s,"OR")== 0))
            sayac++;
        if((strcmp(s,"NOT")== 0))
            sayac++;
    }

    printf("\n>");
    fflush(stdin);
    scanf("%s",&komut);

    if(komut[0]=='I' || komut[0]=='i'){
                time(&z);
                zaman=localtime(&z);
                fprintf(log1,"\n%s %c deger.txt degerler atandi.",asctime(zaman),komut[0]);
            iliklendirme(log1,p,n,g,out,kapilar,sayac); //iliklendirme komutu
    }
            else{
                printf("Iliklendirme yapilmadan program calisamaz.");
                exit(1);
            }
                fflush(stdin);
                while(komut[0] != 'C' && komut[0] != 'c'){
                    printf("\n\n>");
                    gets(komut);

                    if(komut[0]=='G' || komut[0]=='g'){
                        i=1;
                        komut2=komut[i];
                        if(komut2=='*'){//tum ucların seviyesi gösterilir.
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c%c ",asctime(zaman),komut[0],komut2);
                         Goster(log1,n,g,out,kapilar,sayac,komut2);
                        }

                            else{
                                    if(komut[i]=='\t')
                                        i++;

                                    komut2=komut[i];
                                    time(&z);
                                    zaman=localtime(&z);
                                    fprintf(log1,"\n%s %c%c ",asctime(zaman),komut[0],komut2);
                                Goster(log1,n,g,out,kapilar,sayac,komut2);
                                i++;
                               while(komut[i] != '\0'){
                                    if(komut[i]=='\t')
                                        i++;
                                    komut2=komut[i];
                                    komut2=komut[i];
                                    time(&z);
                                    zaman=localtime(&z);
                                    fprintf(log1,"\n%s %c%c ",asctime(zaman),komut[0],komut2);
                                    Goster(log1,n,g,out,kapilar,sayac,komut2);
                                    i++;
                               }
                            }
                                //ilgili ucun seviyesi gösterilir. */
                }

                    if(komut[0]=='H' || komut[0]=='h'){// ilgili ucu 1 yapar.
                            i=1;
                            while(komut[i] != '\0'){
                                if(komut[i]=='\t')
                                    i++;
                            komut2=komut[i];
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c%c  %c 1'e yukseltildi. ",asctime(zaman),komut[0],komut2,komut2);
                            Higher(log1,sim,n,g,out,kapilar,sayac,komut2);
                        i++;
                            }
                    }
                    if(komut[0]=='l' || komut[0]=='L'){ //ilgili ucu 0 yapar.
                           i=1;
                            while(komut[i] != '\0'){
                                if(komut[i]=='\t')
                                    i++;
                            komut2=komut[i];
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c%c  %c 0'a indirgendi. ",asctime(zaman),komut[0],komut2,komut2);
                            Lower(log1,sim,n,g,out,kapilar,sayac,komut2);
                        i++;
                            }

                    }
                    if(komut[0]=='s' || komut[0]=='S'){//devreyi simüle eder.
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c   ",asctime(zaman),komut[0]);
                            Simulation(log1,sim);
                    }
                    if(komut[0]=='K' || komut[0]=='k'){//komut.txt dosyasi içindeki komutları konsoldan icra eder
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c komut1.txt icindeki komutlar konsoldan icra edildi.",asctime(zaman),komut[0]);
                    komutK(sim,f,p,n,g,out,kapilar,sayac);
                    }
                }
                    if(komut[0]=='C' || komut[0]=='c'){ //programi kapatır.
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(log1,"\n%s %c Programdan cikildi.",asctime(zaman),komut[0]);
                        exit(1);
                    }

    fclose(log1);
    return 0;
}

int dosyadanOku(FILE *log1,FILE *f,struct eleman g[4],struct eleman out[2],struct kapi kapilar[6]){

    char s[10],s1[10],c,c1;
    struct eleman g1[4];
    FILE *baskaDosya;
    int a,i=0,j,n=0,b,b1,sayac=0,n1=0,temp,h;

    if(f=fopen(DOSYA_YOLU,"r")){

        fscanf(f,"%s",s);

        a=strcmp(s,".include");
        if(a==0){
    if(baskaDosya=fopen(DOSYA_YOLU,"r")){

                if(baskaDosya=fopen("baska_dosya.txt","r")){
                    fscanf(baskaDosya,"%s",s1);
                    fscanf(baskaDosya,"%c",&c1);
                        while(c1 != '#'){
                                if(c1 == '\t')
                                goto loop2;
                            g1[n1].name=c1;
                            n1++;
                            loop2:fscanf(baskaDosya,"%c",&c1); //tab geciliyor.
                        }


                        while(strcmp(s1,".kapi") != 0){ //.kapi okunana kadar boş geçiyor.
                             fscanf(baskaDosya,"%s",s1);
                        }
                     loop1:fscanf(baskaDosya,"%s",s1);
                     strcpy(kapilar[i].name,s1);

                     fscanf(baskaDosya,"%c",&c1);//tab geciliyor.
                     fscanf(baskaDosya,"%d",&b1);//gecikme aliniyor.
                     kapilar[i].g=b1;


                     fscanf(baskaDosya,"%c",&c1); //tab geciliyor.
                     fscanf(baskaDosya,"%c",&c1); //cikis aliniyor.
                     kapilar[i].cout.name=c1;


                     fscanf(baskaDosya,"%c",&c1); //tab geciliyor.
                     for(j=0;j<kapilar[i].g;j++){//girisler okunuyor
                      fscanf(baskaDosya,"%c",&c1);
                      kapilar[i].in[j].name=c1;
                      fscanf(baskaDosya,"%c",&c1); //tab geciyor.
                     }

                        if(c1== '\t')
                            fscanf(baskaDosya,"%c",&c1);

                     fscanf(baskaDosya,"%d",&b1);
                     kapilar[i].delay=b1;


                     fscanf(baskaDosya,"%s",s1);
                     if(strcmp(s1,".son") != 0){
                        i++;
                        goto loop1;
                     }
                    i++;
                      fscanf(f,"%s",s);
                      fscanf(f,"%s",s);
                      //fclose(baskaDosya);
                }
                else printf("Dosya acilamadi.");

            }
        }

       a=strcmp(s,".giris");
        if(a==0){ //girisler okunuyor.
                fscanf(f,"%c",&c);
            while(c != '#'){
                if(c=='\t') //tablar atlanýyor.
                    goto loop;

                g[n].name=c;
                n++;
                loop: fscanf(f,"%c",&c);


            }
        }
            temp=n;
            int temp1=0;
            for(h=0;h<n1;h++){
                for(j=0;j<temp;j++){
                    if(g1[h].name != g[j].name)
                        temp1++;
                }
                if(temp1==temp){
                    g[n]=g1[h];
                    n++;
                }
            }
            while(c != '.'){ //yorum satirlari dikkate alýnmýyor.
                fscanf(f,"%c",&c);
            }

            fscanf(f,"%s",s);
            a=strcmp(s,"cikis");
            fscanf(f,"%c",&c);//tab gecicek
              if(a==0){
                  fscanf(f,"%c",&c);
                  out[0].name=c;
                    }//cikislar okunuyor

                fscanf(f,"%c",&c);
             while(c != '.'){//yorum satirlari dikkate alýnmoyýr.
                fscanf(f,"%c",&c);
            }
            fscanf(f,"%s",s);
            a=strcmp(s,"kapi");

            while(a==0){ //kapilar tanýmlaniyor.

                    fscanf(f,"%c",&c); //tablari geçmek için


                fscanf(f,"%s",s);
                for(j=0;j<strlen(s);j++){
                    kapilar[i].name[j]=s[j];
                }
                kapilar[i].name[j]='\0'; //son elemana sonlandırma kararkteri atiliyor.
                fscanf(f,"%c",&c); //tablari geçmek için

                fscanf(f,"%d",&b);
                kapilar[i].g=b;

                fscanf(f,"%c",&c); //tablarý geçmek için.
                fscanf(f,"%c",&c);
                kapilar[i].cout.name=c;

                fscanf(f,"%c",&c); //tablarý geçmek için.
                for(j=0;j<b;j++){
                    fscanf(f,"%c",&c);
                    kapilar[i].in[j].name=c;
                    fscanf(f,"%c",&c);
                    }


                fscanf(f,"%d",&b);
                kapilar[i].delay=b;


                i++;
                fscanf(f,"%s",s);

            a=strcmp(s,".kapi");
            sayac++;
 }
        fclose(f);
        }
         else
        printf("\nDosya acilamadi.");

        return n;
    }




void iliklendirme(FILE *log1,FILE *p,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac){
time_t z;
    struct tm *zaman;
char c;
int b,i,j,h;

if(p=fopen(DEGER,"r")){

    do{
    i=fscanf(p,"%c",&c);
    fscanf(p,"%d",&b);

        for(j=0;j<n;j++){
            if(g[j].name== c)
                g[j].deger=b;
        }

        if(out[0].name== c)
            out[0].deger=b;


        for(j=0;j<sayac;j++){
            for(h=0;h<kapilar[j].g;h++){
                if(kapilar[j].in[h].name== c)
                    kapilar[j].in[h].deger=b;
            }
        if(kapilar[j].cout.name == c)
            kapilar[j].cout.deger=b;
        }

    } while(i != EOF);

    fclose(p);

} else
    printf("\nDosya acilamadi.");

}

void Higher(FILE *log1,FILE *sim,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut){
    time_t z;
    struct tm *zaman;
    int j,h,i,a,index[6],boyut=0,temp,temp1,d,ns1,ilkdeger;
    int ns=0;
    char s[5],cikis[6],c;
    sim=fopen("sim.txt","w");

    fprintf(sim," %d.ns***%c:0->1",ns,komut);
    for(j=0;j<n;j++){
            if(g[j].name== komut)
                g[j].deger=1;
        }

        for(j=0;j<sayac;j++){
            for(h=0;h<kapilar[j].g;h++){
                if(kapilar[j].in[h].name== komut){
                    kapilar[j].in[h].deger=1;
                    index[boyut]=j;
                    cikis[boyut]=kapilar[j].cout.name;
                    boyut++;
                        }
            }
            }
        int boyut1=boyut;
        for(i=0;i<boyut1;i++){
            for(j=0;j<sayac;j++){
                for(h=0;h<kapilar[j].g;h++){
                    if(cikis[i]==kapilar[j].in[h].name){
                        index[boyut]=j;
                        boyut=boyut+1;
                    }
                }
            }
        }

        for(i=0;i<boyut;i++){ //kapilari gecikme sürelerine göre almak icin siraladik.
            for(j=0;j<boyut;j++){
                if(kapilar[index[i]].delay<kapilar[index[j]].delay){
                   temp=index[i];
                   index[i]=index[j];
                   index[j]=temp;
                }
            }
        }

        for(i=0;i<boyut;i++){
            if(i==boyut-1)
                break;
            for(h=0;h<kapilar[index[i]].g;h++){ //yanlis siralama onlendi.
                if(kapilar[index[i+1]].cout.name==kapilar[index[i]].in[h].name){
                    temp=index[i+1];
                    index[i+1]=index[i];
                    index[i]=temp;
                }
            }
                if(strcmp(kapilar[index[i]].name,kapilar[index[i+1]].name)==0){
                    temp=index[i+1];
                    index[i+1]=index[i+2];
                    index[i+2]=temp;
                }
        }

        for(i=0;i<boyut;i++){
            strcpy(s,kapilar[index[i]].name);


                                if(strcmp(s,"AND") == 0)
                                    a=1;
                                if(strcmp(s,"OR") == 0)
                                    a=2;
                                if(strcmp(s,"XOR") == 0)
                                    a=3;
                                if(strcmp(s,"NOT") == 0)
                                    a=4;
                                if(strcmp(s,"NAND") == 0)
                                    a=5;
                                if(strcmp(s,"NOR") == 0)
                                    a=6;


                                switch(a){

                                case 1: temp=1; //AND kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++)
                                            temp=temp*kapilar[index[i]].in[j].deger;
                                    if(temp==0)
                                        kapilar[index[i]].cout.deger=0;
                                    else if(temp==1)
                                        kapilar[index[i]].cout.deger=1;

                                    c=kapilar[index[i]].cout.name;
                                    d= kapilar[index[i]].cout.deger;
                                        for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                            for(h=0;h<kapilar[j].g;h++){
                                                if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }
                                        ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;
                                case 2: temp=0; //OR kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                    }
                                        if(temp != 0)
                                        kapilar[index[i]].cout.deger=1;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;

                                case 3: temp=0;  //XOR kapisi.
                                        temp1=0;
                                         ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                        if(kapilar[index[i]].in[j].deger==0)
                                            temp1++;
                                    }
                                            if(temp==temp1)
                                                kapilar[index[i]].cout.deger=1;
                                            else if(temp == kapilar[index[i]].g-1 || temp1 == kapilar[index[i]].g-1 )
                                                kapilar[i].cout.deger=0;

                                                c=kapilar[index[i]].cout.name;
                                                d= kapilar[index[i]].cout.deger;
                                                    for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                        for(h=0;h<kapilar[j].g;h++){
                                                            if(kapilar[j].in[h].name==c)
                                                            kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);

                                        break;
                                case 4: ilkdeger=kapilar[index[i]].cout.deger;
                                    if(kapilar[index[i]].in[0].deger==0) //NOT kapisi.
                                            kapilar[index[i]].cout.deger=1;
                                        else if(kapilar[index[i]].in[0].deger ==1)
                                            kapilar[index[i]].cout.deger=0;

                                            c=kapilar[index[i]].cout.name;
                                            d= kapilar[index[i]].cout.deger;
                                                for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                    for(h=0;h<kapilar[j].g;h++){
                                                        if(kapilar[j].in[h].name==c)
                                                        kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;

                                case 5: temp=1; //NAND kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++)
                                            temp=temp*kapilar[index[i]].in[j].deger;
                                    if(temp==0)
                                        kapilar[index[i]].cout.deger=1;
                                    else if(temp==1)
                                        kapilar[index[i]].cout.deger=0;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;

                                case 6:  temp=0; //NOR kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                    }
                                        if(temp != 0)
                                        kapilar[index[i]].cout.deger=0;

                                        else
                                            kapilar[index[i]].cout.deger=1;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }

                                        ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;
                                }
        }

    fclose(sim);

}

void Lower(FILE *log1,FILE *sim,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut){
    time_t z;
    struct tm *zaman;
    int j,h,i,a,index[6],boyut=0,temp,temp1,d,ns1,ilkdeger;
    int ns=0;
    char s[5],cikis[6],c;
    sim=fopen("sim.txt","w");
    fprintf(sim," %d.ns***%c:0->1",ns,komut);

    for(j=0;j<n;j++){
            if(g[j].name== komut)
                g[j].deger=0;
        }

        for(j=0;j<sayac;j++){
            for(h=0;h<kapilar[j].g;h++){
                if(kapilar[j].in[h].name== komut){
                    kapilar[j].in[h].deger=0;
                    index[boyut]=j;
                    cikis[boyut]=kapilar[j].cout.name;
                    boyut++;
                        }
            }
            }
        int boyut1=boyut;
        for(i=0;i<boyut1;i++){
            for(j=0;j<sayac;j++){
                for(h=0;h<kapilar[j].g;h++){
                    if(cikis[i]==kapilar[j].in[h].name){
                        index[boyut]=j;
                        boyut=boyut+1;
                    }
                }
            }
        }

        for(i=0;i<boyut;i++){ //kapilari gecikme sürelerine göre almak icin siraladik.
            for(j=0;j<boyut;j++){
                if(kapilar[index[i]].delay<kapilar[index[j]].delay){
                   temp=index[i];
                   index[i]=index[j];
                   index[j]=temp;
                }
            }
        }

        for(i=0;i<boyut;i++){
            if(i==boyut-1)
                break;
            for(h=0;h<kapilar[index[i]].g;h++){ //yanlis siralama onlendi.
                if(kapilar[index[i+1]].cout.name==kapilar[index[i]].in[h].name){
                    temp=index[i+1];
                    index[i+1]=index[i];
                    index[i]=temp;
                }
            }
                if(strcmp(kapilar[index[i]].name,kapilar[index[i+1]].name)==0){
                    temp=index[i+1];
                    index[i+1]=index[i+2];
                    index[i+2]=temp;
                }
        }

        for(i=0;i<boyut;i++){
            strcpy(s,kapilar[index[i]].name);


                                if(strcmp(s,"AND") == 0)
                                    a=1;
                                if(strcmp(s,"OR") == 0)
                                    a=2;
                                if(strcmp(s,"XOR") == 0)
                                    a=3;
                                if(strcmp(s,"NOT") == 0)
                                    a=4;
                                if(strcmp(s,"NAND") == 0)
                                    a=5;
                                if(strcmp(s,"NOR") == 0)
                                    a=6;


                                switch(a){

                                case 1: temp=1; //AND kapisi.
                                     ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++)
                                            temp=temp*kapilar[index[i]].in[j].deger;
                                    if(temp==0)
                                        kapilar[index[i]].cout.deger=0;
                                    else if(temp==1)
                                        kapilar[index[i]].cout.deger=1;

                                    c=kapilar[index[i]].cout.name;
                                    d= kapilar[index[i]].cout.deger;
                                        for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                            for(h=0;h<kapilar[j].g;h++){
                                                if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }
                                        ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);

                                    break;
                                case 2: temp=0; //OR kapisi.
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                    }
                                        if(temp != 0)
                                        kapilar[index[i]].cout.deger=1;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }
                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;

                                case 3: temp=0;  //XOR kapisi.
                                        temp1=0;
                                         ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                        if(kapilar[index[i]].in[j].deger==0)
                                            temp1++;
                                    }
                                            if(temp==temp1)
                                                kapilar[index[i]].cout.deger=1;
                                            else if(temp != temp1)
                                                kapilar[i].cout.deger=0;

                                                c=kapilar[index[i]].cout.name;
                                                d= kapilar[index[i]].cout.deger;
                                                    for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                        for(h=0;h<kapilar[j].g;h++){
                                                            if(kapilar[j].in[h].name==c)
                                                            kapilar[j].in[h].deger=d;
                                            }
                                        }

                                        ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;
                                case 4:  ilkdeger=kapilar[index[i]].cout.deger;
                                    if(kapilar[index[i]].in[0].deger==0) //NOT kapisi.
                                            kapilar[index[i]].cout.deger=1;
                                        else if(kapilar[index[i]].in[0].deger ==1)
                                            kapilar[index[i]].cout.deger=0;

                                            c=kapilar[index[i]].cout.name;
                                            d= kapilar[index[i]].cout.deger;
                                                for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                    for(h=0;h<kapilar[j].g;h++){
                                                        if(kapilar[j].in[h].name==c)
                                                        kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                       fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;
                                case 5: temp=1; //NAND kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++)
                                            temp=temp*kapilar[index[i]].in[j].deger;
                                    if(temp==0)
                                        kapilar[index[i]].cout.deger=1;
                                    else if(temp==1)
                                        kapilar[index[i]].cout.deger=0;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }

                                         ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;

                                case 6:  temp=0; //NOR kapisi.
                                 ilkdeger=kapilar[index[i]].cout.deger;
                                    for(j=0;j<kapilar[index[i]].g;j++){
                                        if(kapilar[index[i]].in[j].deger==1)
                                            temp++;
                                    }
                                        if(temp != 0)
                                        kapilar[index[i]].cout.deger=0;

                                        else if(temp == 0)
                                        kapilar[index[i]].cout.deger=1;

                                        c=kapilar[index[i]].cout.name;
                                        d= kapilar[index[i]].cout.deger;
                                            for(j=0;j<sayac;j++){ //cikis degerini her yerde degistiriyor.
                                                for(h=0;h<kapilar[j].g;h++){
                                                    if(kapilar[j].in[h].name==c)
                                                    kapilar[j].in[h].deger=d;
                                            }
                                        }

                                        ns1=0;
                                        if(i != 0){
                                        for(j=0;j<kapilar[index[i]].g;j++){
                                            if(komut == kapilar[index[i]].in[j].name)
                                               ns1++;
                                        }
                                        }
                                        if(ns1 == 0)
                                        ns=kapilar[index[i]].delay+ns;
                                            else {
                                                int fark=(kapilar[index[i]].delay-ns);
                                                ns=fark+ns;
                                            }
                                        fprintf(sim,"   %d.ns***%c:%d->%d",ns,c,ilkdeger,d);
                                        break;
                                }
        }
    fclose(sim);

}

void Goster(FILE *log1,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac,char komut){
    time_t z;
    struct tm *zaman;
    int i,j,a=0,temp=0;
    if(komut == '*'){ //tum uclar yazdiriyor.
        for(i=0;i<n;i++){
            printf("\n%c -> %d",g[i].name,g[i].deger);
            fprintf(log1,"%c -> %d",g[i].name,g[i].deger);
        }

        for(i=0;i<sayac;i++){
            printf("\n%c -> %d",kapilar[i].cout.name,kapilar[i].cout.deger);
            fprintf(log1,"%c -> %d",kapilar[i].cout.name,kapilar[i].cout.deger);
    }
}

    else{ //gönderilen ucları yazdiriyor.
        for(i=0;i<n;i++){
            if(komut == g[i].name){
                 printf("\n%c -> %d",g[i].name,g[i].deger);
                 fprintf(log1,"%c -> %d",g[i].name,g[i].deger);
        }
        }

         for(i=0;i<sayac;i++){
                if(komut== kapilar[i].cout.name){
            printf("\n%c -> %d",kapilar[i].cout.name,kapilar[i].cout.deger);
            fprintf(log1,"%c -> %d",kapilar[i].cout.name,kapilar[i].cout.deger);
    }
         }
}
}

void komutK(FILE *sim,FILE *f,FILE *p,int n,struct eleman g[n],struct eleman out[2],struct kapi kapilar[6],int sayac){
    FILE *k;
    FILE *y;
    y=fopen("log.komut1.txt","w");
    time_t z;
    struct tm *zaman;
    char komut,c,ns=0;
    int i;

    if(k=fopen("komut1.txt","r")){
        fscanf(k,"%c",&c);
            if(c=='y' || c=='Y') {//yükleme
                    time(&z);
                    zaman=localtime(&z);
                    fprintf(y,"%s %c devre.txt yuklendi.",asctime(zaman),c);
                    dosyadanOku(y,f,g,out,kapilar);
            }//ana giris eleman sayisi
                else{ printf("Devre yuklenmeden program calisamaz.");
                    exit(1);
            }
            i=fscanf(k,"%c",&c);
            while(i != EOF){
                i=fscanf(k,"%c",&c);
                if(c=='I' || c=='i')
                    break;
            }

            if(c=='I' || c=='i'){
                    time(&z);
                    zaman=localtime(&z);
                    fprintf(y,"\n%s %c deger.txt yuklendi.",asctime(zaman),c);
                iliklendirme(y,p,n,g,out,kapilar,sayac); //iliklendirme komutu
            }
            else{
                printf("Iliklendirme yapilmadan program calisamaz.");
                exit(1);
            }


            while(c != 't'){
              fscanf(k,"%c",&c);
            }

            i=0;
            while(i != 2){
              fscanf(k,"%c",&c);
              i++;
            }


                while(i != EOF){
                            i=fscanf(k,"%c",&c);
                    if(c=='G' || c=='g'){
                        fscanf(k,"%c",&c);
                            if(c == '*'){
                                komut=c;
                                    time(&z);
                                    zaman=localtime(&z);
                                    fprintf(y,"\n%s G%c ",asctime(zaman),komut);
                                Goster(y,n,g,out,kapilar,sayac,komut);
                            }
                            else{
                                printf("%c",c);
                                fscanf(k,"%c",&c);
                                komut=c;
                                time(&z);
                                zaman=localtime(&z);
                                fprintf(y,"\n%s G%c ",asctime(zaman),komut);
                                Goster(y,n,g,out,kapilar,sayac,komut);

                            }
                }

                    if(c=='H' || c=='h'){// ilgili ucu 1 yapar.
                            fscanf(k,"%c",&c);//tab geciliyor
                                if(c == '\t')
                                fscanf(k,"%c",&c);
                            komut=c;
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(y,"\n%s H%c %c 1'e yukseltildi.",asctime(zaman),komut,komut);
                            Higher(y,sim,n,g,out,kapilar,sayac,komut);

                            }
                    if(c=='l' || c=='L'){ //ilgili ucu 0 yapar.
                            fscanf(k,"%c",&c);//tab geciliyorç
                            fscanf(k,"%c",&c);
                            komut=c;
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(y,"\n%s I%c %c 0'a indirgendi. ",asctime(zaman),komut,komut);
                            Lower(y,sim,n,g,out,kapilar,sayac,komut);
                            }
                            if(c=='S' || c=='s'){
                            time(&z);
                            zaman=localtime(&z);
                            fprintf(y,"\n%s %c ",asctime(zaman),c);
                            Simulation(y,sim);
                    }
                    }


                    fclose(k);
                    fclose(y);
                    }
                    else
                            printf("Dosya acilamadi.");
                }


void Simulation(FILE *log1,FILE *sim){
    char c,s[20];
    int i;
    time_t z;
    struct tm *zaman;
    if(sim=fopen("sim.txt","r")){
        fscanf(sim,"%c",&c); //ilk bosluk gecildi.
         while(i != EOF){
            i=fscanf(sim,"%s",s);
            fprintf(log1,"%s    ",s);
            printf("\n%s",s);
            i=fscanf(sim,"%c",&c);
         }


    } else printf("Dosya acilamadi.");

}

