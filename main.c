#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *isim;
    char *soyIsim;
    int *no;
    char *stajKontrol;
}OgrenciBilgi;

typedef struct
{
    char *isim;
    char *faaliyetAlani;
    int *vergiNo;

}FirmaBilgi;

struct tarih
{
    int gun;
    int ay;
    int yil,toplamGun;
};

int ogrenciSayisi(FILE *fpOgr,int *pgecici);
void ogrenciListeleme(FILE *fpOgr,int *pgecici2);
void ogrenciDuzenleme(FILE *fpOgr,FILE *fpYedekOgr);

void firmaListeleme(FILE *fpFirma);
void firmaDuzenleme(FILE *fpOgr,FILE *fpYedekFirma);

void ogrenciSilme(FILE *fpOgr,FILE *fpYedekOgr);
void firmaSilme(FILE *fpFirma,FILE *fpYedekFirma);

void stajEkleme(FILE *fpOgr,FILE *fpFirma,FILE *fpStaj);
void stajListeleme(FILE *fpStaj);

int TarihFarki(struct tarih Bitis, struct tarih Baslangic, struct tarih *Fark,struct tarih *Toplam);

int main()
{
    FILE *fpOgr,*fpYedekOgr,*fpYedekFirma,*fpStaj;
    OgrenciBilgi ogrenci;
    char isim[20],soyIsim[20];
    ogrenci.isim = &isim;
    ogrenci.soyIsim = &soyIsim;

    OgrenciBilgi ogrenciKontrol;
    char isimKontrol[20],soyIsimKontrol[20];
    ogrenciKontrol.isim = &isimKontrol;
    ogrenciKontrol.soyIsim = &soyIsimKontrol;

    FILE *fpFirma;
    FirmaBilgi firma;
    char firmaIsim[20],firmaFaaliyet[20];
    firma.isim = &firmaIsim;
    firma.faaliyetAlani = &firmaFaaliyet;

    FirmaBilgi firmaKontrol;
    int firmaKontrolNo;
    char firmaKontIsim[20],firmaKontFaaliyet[20];
    firmaKontrol.isim = &firmaKontIsim;
    firmaKontrol.faaliyetAlani = &firmaKontFaaliyet;
    firmaKontrol.vergiNo = &firmaKontrolNo;

    int secenek,ogrSayi=0,menu,faaliyetNo,verginoKontrolu =0,yedekOgr=0;
    printf("--------Staj Yonetim Programi--------\n\n");

    while (1)
    {
    printf("  ***** Ogrenci Islemleri *****\n\n");
    printf("->  Ogrenci Eklemek icin 1'e basiniz.\n");
    printf("->  Ogrenci Listelemek icin 2'ye basiniz.\n");
    printf("->  Ogrenci Duzenlemek icin 3'e basiniz.\n");
    printf("->  Ogrenci Silmek icin 4'e basiniz.\n");

    printf("\n  ***** Firma Islemleri *****\n\n");
    printf("->  Firma Eklemek icin 5'e basiniz.\n");
    printf("->  Firma Listelemek icin 6'ya basiniz.\n");
    printf("->  Firma Duzenlemek icin 7'ye basiniz.\n");
    printf("->  Firma Silmek icin 8'e basiniz.\n");

    printf("\n  ***** Staj Islemleri *****\n\n");
    printf("->  Staj eklemek icin 9'a basiniz.\n");
    printf("->  Staj bilgilerini listelemek icin 10'a basiniz.\n");
    printf("\n->  Yapmak istediginiz islemi seciniz: ");

    scanf("%d",&secenek);
    verginoKontrolu =0;
        switch (secenek)
        {
            case 1:
            fpOgr = fopen("ogrenciBilgileri.txt","a+");
            if (fpOgr == NULL)
            {
                printf("Dosya acilamadi!\n");
                exit(1);
            }
            printf("\n--------Ogrenci Kayit Sistemi--------\n\n");
            printf("Ogrenci Adi giriniz: ");
            scanf("%s",isim);
            printf("Ogrenci Soy Adi giriniz: ");
            scanf("%s",soyIsim);
            fseek(fpOgr,0,SEEK_END);
            if( ftell(fpOgr)!=0 )
            {
               ogrenciSayisi(fpOgr,&ogrSayi);
            }
            ogrenci.no = &ogrSayi;
            *ogrenci.no = *ogrenci.no +1;

            rewind(fpOgr);
            while(!feof(fpOgr))
            {
                fscanf(fpOgr,"%s %s %d\n",ogrenciKontrol.isim,ogrenciKontrol.soyIsim,&ogrenciKontrol.no);
                if(*ogrenci.no == ogrenciKontrol.no)
                {
                    *ogrenci.no = *ogrenci.no + 1;
                    rewind(fpOgr);
                }
            }
            printf("Ogrenci Numarasi: %d\n",*ogrenci.no);
            fprintf(fpOgr,"%s %s %d\n",ogrenci.isim,ogrenci.soyIsim,*ogrenci.no);
            fclose(fpOgr);
            break;

            case 2:
            printf("\n-----------Ogrenci Listesi-----------\n\n");
            ogrenciListeleme(fpOgr,&ogrSayi);
            break;

            case 3:
            printf("\n-------Ogrenci Bilgi Duzenleme-------\n\n");
            ogrenciDuzenleme(fpOgr,fpYedekOgr);
            break;

            case 4:
            printf("\n--------Ogrenci Bilgi Silme--------\n\n");
            ogrenciSilme(fpOgr,fpYedekOgr);
            break;

            case 5:
            fpFirma = fopen("firmaBilgileri.txt","a+");
            if (fpFirma == NULL)
            {
                printf("Dosya acilamadi!\n");
                exit(1);
            }
            printf("\n---------Firma Kayit Sistemi---------\n\n");
            printf("Firma Adi giriniz: ");
            scanf("%s",firma.isim);

            printf("Faaliyet Alani giriniz.Yazilim icin 1'i, donanim icin 2'yi tuslayiniz. ");
            scanf("%d",&faaliyetNo);
            while (faaliyetNo!=1 && faaliyetNo!=2)
            {
                printf("Gecerli tuslama yapiniz: ");
                scanf("%d",&faaliyetNo);
            }
            if(faaliyetNo == 1)
            strcpy(firma.faaliyetAlani,"yazilim");

            if(faaliyetNo == 2)
            strcpy(firma.faaliyetAlani,"donanim");

            int firmaNumarasi;
            firma.vergiNo = &firmaNumarasi;
            printf("Firma Vergi Numarasini giriniz: ");
            scanf("%d",*&firma.vergiNo);

            rewind(fpFirma);
            while(!feof(fpFirma))
            {
                fscanf(fpFirma,"%s %s %d\n",firmaKontrol.isim,firmaKontrol.faaliyetAlani,*&firmaKontrol.vergiNo);
                if( *firma.vergiNo == *firmaKontrol.vergiNo)
                {
                    printf("Bu vergi numarasi zaten mevcut...\n");
                    verginoKontrolu = 1;
                    break;
                }
            }

            if(verginoKontrolu == 1)
            {
                verginoKontrolu == 0;
                break;
            }

            fseek(fpFirma,0,SEEK_END);

            fprintf(fpFirma,"%s %s %d\n",firma.isim,firma.faaliyetAlani,*firma.vergiNo);
            fclose(fpFirma);

            break;

            case 6:
            printf("\n------------Firma Listesi------------\n\n");
            firmaListeleme(fpFirma);
            break;
            case 7:
            printf("\n--------Firma Bilgi Duzenleme--------\n\n");
            firmaDuzenleme(fpFirma,fpYedekFirma);
            break;

            case 8:
            printf("\n--------Firma Bilgi Silme--------\n\n");
            firmaSilme(fpFirma,fpYedekFirma);
            break;

            case 9:
            printf("\n--------Staj Ekleme--------\n\n");
            stajEkleme(fpOgr,fpFirma,fpStaj);
            break;

            case 10:
            printf("\n--------Staj Listesi--------\n\n");
            stajListeleme(fpStaj);
            break;
    }
    printf("-------------------------------------\n");
    printf("\nMenuye donmek icin 1'e programi kapatmak icin 2'ye basiniz: ");
    scanf("%d",&menu);
    printf("\n");

        if(menu == 2)
        {
        break;
        }

    }
    return 0;
}

int ogrenciSayisi(FILE *fpOgr,int *pgecici)
{
    fpOgr = fopen("ogrenciBilgileri.txt","a");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    int gecici;
    fclose(fpOgr);


    fpOgr = fopen("ogrenciBilgileri.txt","r");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    fseek(fpOgr,0,SEEK_END);
    if( ftell(fpOgr) == 0 )
    {
        printf("Ogrenci sayisi: 0");
        return *pgecici = 0;
    }


    OgrenciBilgi ogrenci2;
    char isim[50],soyIsim[50];
    ogrenci2.isim = &isim;
    ogrenci2.soyIsim = &soyIsim;


    *pgecici=0;

    rewind(fpOgr);

    while(!feof(fpOgr))
    {
        fscanf(fpOgr,"%s %s %d\n",ogrenci2.isim,ogrenci2.soyIsim,&ogrenci2.no);
    }

    fclose(fpOgr);
    return *pgecici;
}

void ogrenciListeleme(FILE *fpOgr,int *pgecici2)
{
    fpOgr = fopen("ogrenciBilgileri.txt","a");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    int gecici;
    fclose(fpOgr);


    fpOgr = fopen("ogrenciBilgileri.txt","r");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    OgrenciBilgi ogrenci3;
    char isim[50],soyIsim[50];
    ogrenci3.isim = &isim;
    ogrenci3.soyIsim = &soyIsim;

    fseek(fpOgr,0,SEEK_END);
    if(ftell(fpOgr) == 0)
    {
        printf("Sistemde Kayitli Ogrenci Yok...\n");
        return 0;
    }

    rewind(fpOgr);
    while(!feof(fpOgr))
    {
        fscanf(fpOgr,"%s %s %d\n",ogrenci3.isim,ogrenci3.soyIsim,&ogrenci3.no);
        printf("%s %s %d\n",ogrenci3.isim,ogrenci3.soyIsim,ogrenci3.no);
    }

    fclose(fpOgr);
}

void ogrenciDuzenleme(FILE *fpOgr,FILE *fpYedekOgr)
{
    OgrenciBilgi ogrenci4;
    char isim4[20],soyIsim4[20];
    ogrenci4.isim = &isim4;
    ogrenci4.soyIsim = &soyIsim4;
    int numara,durum = 0;
    printf("\nBilgilerini degistireceginiz ogrencinin numarasini giriniz: ");
    scanf("%d",&numara);
    fpOgr = fopen("ogrenciBilgileri.txt","r");
    if(fpOgr == NULL)
    {
        puts("Dosya acilamadi");
        exit(1);
    }


    fpYedekOgr = fopen("YedekOgrenciBilgileri.txt","w");
    if(fpYedekOgr == NULL)
    {
        puts("Dosya acilamadi");
        exit(1);
    }


    int imlec=0,ogrNoKpy=0,numara2;

    OgrenciBilgi ogrKontrol3;
    char isim3[20],soyIsim3[20];
    ogrKontrol3.isim = &isim3;
    ogrKontrol3.soyIsim = &soyIsim3;
    ogrenci4.no = &numara2;
    int kontrolImlec;
    fseek(fpOgr,0,SEEK_END);
    kontrolImlec = ftell(fpOgr);
    rewind(fpOgr);

    while(ftell(fpOgr)<kontrolImlec)
    {
        fscanf(fpOgr,"%s %s %d\n",ogrenci4.isim,ogrenci4.soyIsim,*&ogrenci4.no);
        if(numara != *ogrenci4.no)
        {
            fprintf(fpYedekOgr,"%s %s %d\n",ogrenci4.isim,ogrenci4.soyIsim,*ogrenci4.no);
        }

        else
        {
            fflush(stdin);
            imlec=ftell(fpOgr);
            printf("Ogrencinin Yeni Adi: ");
            scanf("%s",ogrenci4.isim);
            printf("Ogrencinin Yeni Soyadi: ");
            scanf("%s",ogrenci4.soyIsim);
            printf("Ogrencinin Yeni Numarasi: ");
            scanf("%d",*&ogrenci4.no);
            printf("\n");

            rewind(fpOgr);
            while(!feof(fpOgr))
            {
                fscanf(fpOgr,"%s %s %d\n",ogrKontrol3.isim,ogrKontrol3.soyIsim,&ogrKontrol3.no);
                if(numara == *ogrenci4.no)
                continue;
                if( *ogrenci4.no == ogrKontrol3.no)
                {
                    fclose(fpOgr);
                    fclose(fpYedekOgr);
                    remove("YedekOgrenciBilgileri.txt");
                    printf("Girilen ogrenci numarasi kullanilamaz, devam etmek icin bir tusa basin...\n");
                    getch();
                    return 0;
                }
            }
            fseek(fpOgr,imlec,SEEK_SET);
            fprintf(fpYedekOgr,"%s %s %d\n",ogrenci4.isim,ogrenci4.soyIsim,*ogrenci4.no);
            durum=1;
        }
    }


    fclose(fpOgr);
    fclose(fpYedekOgr);

    if(durum == 1)
    {
        remove("ogrenciBilgileri.txt");
        rename("YedekOgrenciBilgileri.txt","ogrenciBilgileri.txt");
        printf("Ogrenci bilgileri degistirildi, devam etmek icin bir tusa basin...\n");
    }
    else
    {
        remove("YedekOgrenciBilgileri.txt");
        printf("Ilgili ogenci bulunamadi, devam etmek icin bir tusa basin...\n");
    }
    getch();
    fflush(stdin);
}

void firmaListeleme(FILE *fpFirma)
{
    fpFirma = fopen("firmaBilgileri.txt","a");
    if (fpFirma == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fclose(fpFirma);


    fpFirma = fopen("firmaBilgileri.txt","r+");
    if (fpFirma == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    FirmaBilgi firma3;
    fseek(fpFirma,0,SEEK_END);

    char firmaIsim2[50], firmaFaaliyet2[50];
    firma3.isim = &firmaIsim2;
    firma3.faaliyetAlani = &firmaFaaliyet2;

    if(ftell(fpFirma)==0)
    {
        printf("Sistemde Kayitli Firma Yok...\n");
        return 0;
    }

    rewind(fpFirma);
    while(!feof(fpFirma))
    {
        fscanf(fpFirma,"%s %s %d\n",firma3.isim,firma3.faaliyetAlani,&firma3.vergiNo);

        printf("%s %s %d\n",firma3.isim,firma3.faaliyetAlani,firma3.vergiNo);
    }

    fclose(fpFirma);
}

void firmaDuzenleme(FILE *fpFirma,FILE *fpYedekFirma)
{
    FirmaBilgi firma4;
    char firmaIsim3[20], firmaFaaliyet3[20];
    firma4.isim = &firmaIsim3;
    firma4.faaliyetAlani = &firmaFaaliyet3;
    int vergiNumarasi;
    firma4.vergiNo = &vergiNumarasi;
    int faaliyetNo;

    int imlec1=0,imlec2=0;

    FirmaBilgi firmaKontrol3;
    char isim3[20],faaliyetAlani3[20];
    firmaKontrol3.isim = &isim3;
    firmaKontrol3.faaliyetAlani = &faaliyetAlani3;

    fpFirma = fopen("firmaBilgileri.txt","r");
    if (fpFirma == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    fpYedekFirma = fopen("YedekFirmaBilgileri.txt","w");
    if (fpYedekFirma == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fseek(fpFirma,0,SEEK_END);
    if(ftell(fpFirma) == 0)
    {
        printf("Sistemde Kayitli Firma Yok...\n");
        return 0;
    }

    int vergiNo,degisimDurum=0;
    printf("\nBilgilerini degistireceginiz firmanin vergi numarasini giriniz: ");
    scanf("%d",&vergiNo);
    fseek(fpFirma,0,SEEK_END);
    imlec2 = ftell(fpFirma);
    rewind(fpFirma);
    while(ftell(fpFirma)<imlec2)
    {
        fscanf(fpFirma,"%s %s %d\n",firma4.isim,firma4.faaliyetAlani,*&firma4.vergiNo);
        if(vergiNo != *firma4.vergiNo)
        {
            fprintf(fpYedekFirma,"%s %s %d\n",firma4.isim,firma4.faaliyetAlani,*firma4.vergiNo);
        }
        else
        {
            fflush(stdin);
            printf("Firmanin Yeni Adi : ");
            scanf("%s",firma4.isim);

            printf("Firmanin Yeni Faaliyet Alanini giriniz.Yazilim icin 1, donanim icin 2'yi tuslayiniz. ");
            scanf("%d",&faaliyetNo);
            while (faaliyetNo !=1 && faaliyetNo != 2)
            {
                printf("Gecerli tuslama yapiniz: ");
                scanf("%d",&faaliyetNo);
            }
            if(faaliyetNo == 1)
            strcpy(firma4.faaliyetAlani,"yazilim");

            if(faaliyetNo == 2)
            strcpy(firma4.faaliyetAlani,"donanim");

            printf("Firmanin Yeni Vergi Numarasini Giriniz: ");
            scanf("%d",*&firma4.vergiNo);
            printf("\n");
            imlec1 = ftell(fpFirma);
            rewind(fpFirma);
                while(!feof(fpFirma))
                {
                    fscanf(fpFirma,"%s %s %d\n",firmaKontrol3.isim,firmaKontrol3.faaliyetAlani,&firmaKontrol3.vergiNo);
                    if(*firma4.vergiNo == vergiNo)
                        continue;
                    if(*firma4.vergiNo == firmaKontrol3.vergiNo)
                    {
                        fclose(fpFirma);
                        fclose(fpYedekFirma);
                        remove("YedekFirmaBilgileri.txt");
                        printf("Girilen firma vergi numarasi kullanilamaz, devam etmek icin bir tusa basin...\n");
                        getch();
                        return 0;
                    }
                }

            fprintf(fpYedekFirma,"%s %s %d\n",firma4.isim,firma4.faaliyetAlani,*firma4.vergiNo);
            fseek(fpFirma,imlec1,SEEK_SET);
            degisimDurum=1;
        }
    }

    fclose(fpFirma);
    fclose(fpYedekFirma);

    if(degisimDurum == 1)
    {
        remove("firmaBilgileri.txt");
        rename("YedekFirmaBilgileri.txt","firmaBilgileri.txt");
        printf("Firma bilgileri degistirildi, devam etmek icin bir tusa basin...\n");
    }

    else
    {
        remove("YedekFirmaBilgileri.txt");
        puts("Ilgili firma bulunamadi, devam etmek icin bir tusa basin...");
    }
    getch();
    fflush(stdin);
}


void ogrenciSilme(FILE *fpOgr,FILE *fpYedekOgr)
{
    int numara,durum=0;
    printf("\nBilgileri silinecek ogrencinin numarasini giriniz: ");
    scanf("%d",&numara);
    fpOgr = fopen("ogrenciBilgileri.txt","r");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fpYedekOgr = fopen("YedekOgrenciBilgileri.txt","w");
    if (fpYedekOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
        OgrenciBilgi ogrenci6;
        int ogrenci6No;
        char isim6[20],soyIsim6[20];
        ogrenci6.isim = &isim6;
        ogrenci6.soyIsim = &soyIsim6;
        ogrenci6.no = &ogrenci6No;

    rewind(fpOgr);
    while(!feof(fpOgr))
    {
        fscanf(fpOgr,"%s %s %d\n",ogrenci6.isim,ogrenci6.soyIsim,*&ogrenci6.no);
        if(numara != *ogrenci6.no)
        {
            fprintf(fpYedekOgr,"%s %s %d\n",ogrenci6.isim,ogrenci6.soyIsim,*ogrenci6.no);
        }
        else
        {
            fflush(stdin);
            durum=1;
        }
    }
    fclose(fpOgr);
    fclose(fpYedekOgr);
    if(durum == 1)
    {
        remove("ogrenciBilgileri.txt");
        rename("YedekOgrenciBilgileri.txt","ogrenciBilgileri.txt");
        printf("Ogrenci bilgileri silindi, devam etmek icin bir tusa basin...\n");
    }
    else
    {
        remove("YedekOgrenciBilgileri.txt");
        printf("Ilgili ogrenci bulunamadi, devam etmek icin bir tusa basin...\n");
    }
    getch();
    fflush(stdin);
}

void firmaSilme(FILE *fpFirma,FILE *fpYedekFirma)
{
int vergiNo,durum=0;
printf("\nBilgileri silinecek firmanin vergi numarasini giriniz: ");
scanf("%d",&vergiNo);
fpFirma = fopen("firmaBilgileri.txt","r");
if (fpFirma == NULL)
{
    printf("Dosya acilamadi!\n");
    exit(1);
}

fpYedekFirma = fopen("YedekOgrenciBilgileri.txt","w");
if (fpYedekFirma == NULL)
{
    printf("Dosya acilamadi!\n");
    exit(1);
}
    FirmaBilgi firma6;
    int firma6No;
    char firmaIsim6[20],firmaFaaliyet6[20];
    firma6.isim = &firmaIsim6;
    firma6.faaliyetAlani = &firmaFaaliyet6;
    firma6.vergiNo = &firma6No;



while(!feof(fpFirma))
{
    fscanf(fpFirma,"%s %s %d\n",firma6.isim,firma6.faaliyetAlani,*&firma6.vergiNo);
    if(vergiNo != *firma6.vergiNo)
    {
        fprintf(fpYedekFirma,"%s %s %d\n",firma6.isim,firma6.faaliyetAlani,*firma6.vergiNo);
    }
    else
    {
        fflush(stdin);
        durum=1;
    }
}
fclose(fpFirma);
fclose(fpYedekFirma);
if(durum == 1)
{
    remove("firmaBilgileri.txt");
    rename("YedekOgrenciBilgileri.txt","firmaBilgileri.txt");
    printf("Firma bilgileri silindi, devam etmek icin bir tusa basin...\n");
    getch();
}
else
{
    remove("YedekOgrenciBilgileri.txt");
    printf("Ilgili firma bulunamadi...\n");
}
fflush(stdin);
}

void stajEkleme(FILE *fpOgr,FILE *fpFirma,FILE *fpStaj)
{
    fpOgr = fopen("ogrenciBilgileri.txt","r");
    if (fpOgr == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fpFirma = fopen("firmaBilgileri.txt","r");
    if (fpFirma == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fpStaj = fopen("stajBilgileri.txt","a+");
    if (fpStaj == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    int ogrenciNo;
    OgrenciBilgi ogrencix;
    char isimx[20],soyIsimx[20],stajKontrol[20];
    ogrencix.isim = &isimx;
    ogrencix.soyIsim = &soyIsimx;
    ogrencix.stajKontrol = &stajKontrol;

    OgrenciBilgi ogrencix2;
    int ogrenci2No;
    char isimx2[20],soyIsimx2[20];
    ogrencix2.isim = &isimx2;
    ogrencix2.soyIsim = &soyIsimx2;
    ogrencix2.no = &ogrenci2No;

    FirmaBilgi firmaKontrol;
    char firmaIsimKontrol[20],firmaFaaliyetKontrol[20];
    firmaKontrol.isim = &firmaIsimKontrol;
    firmaKontrol.faaliyetAlani = &firmaFaaliyetKontrol;
    int vergiNo;
    firmaKontrol.vergiNo = &vergiNo;

    FirmaBilgi firmaKontrol2;
    char firmaIsimKontrol2[20],firmaFaaliyetKontrol2[20];
    firmaKontrol2.isim = &firmaIsimKontrol2;
    firmaKontrol2.faaliyetAlani = &firmaFaaliyetKontrol2;
    int vergiNo2;
    firmaKontrol2.vergiNo = &vergiNo2;

    int istenilenOgr,istenilenFirma,durum=1;

    printf("Staj Listesine eklenecek ogrenicinin numarasini girin: ");
    scanf("%d",&istenilenOgr);
    durum = 1;
    rewind(fpOgr);
    while(1)
    {
    while(!feof(fpOgr))
    {
        fscanf(fpOgr,"%s %s %d\n",ogrencix2.isim,ogrencix2.soyIsim,*&ogrencix2.no);
        if( *ogrencix2.no == istenilenOgr )
        {
            durum = 3;
            break;
        }
    }

    if(durum != 3)
    {

        printf("Ogrenci Sistemde Kayitli degil...\n");
        fclose(fpFirma);
        fclose(fpOgr);
        fclose(fpStaj);
        return 0;
    }
    else
        break;
    }

    durum = 1;

        while(1)
        {
        printf("Yazilim staji yapilan firmanin vergi numarasini giriniz: ");
        scanf("%d",&istenilenFirma);

        rewind(fpFirma);
        while(!feof(fpFirma))
        {
            fscanf(fpFirma,"%s %s %d\n",firmaKontrol.isim,firmaKontrol.faaliyetAlani,*&firmaKontrol.vergiNo);
            if(strcmp(firmaKontrol.faaliyetAlani,"yazilim")== 0 && istenilenFirma == *firmaKontrol.vergiNo)
            {
                durum=2;
                break;
            }
        }
        if(durum == 1)
        {
            printf("Girdiginiz firma yazilim firmasi degil. \n");
            printf("Lutfen yazilim firmasi giriniz.\n");

        }
        else
        {
           break;
        }
        }
    durum = 1;

        while(1)
    {
        printf("Donanim staji yapilan firmanin vergi numarasini giriniz: ");
        scanf("%d",&istenilenFirma);
        rewind(fpFirma);
        while(!feof(fpFirma))
        {
            fscanf(fpFirma,"%s %s %d\n",firmaKontrol2.isim,firmaKontrol2.faaliyetAlani,*&firmaKontrol2.vergiNo);
            if(strcmp(firmaKontrol2.faaliyetAlani,"donanim")== 0 && istenilenFirma == *firmaKontrol2.vergiNo)
            {
                durum=2;
                break;
            }
        }
        if(durum == 1)
        {
            printf("Girdiginiz firma donanim firmasi degil.\n");
            printf("Lutfen donanim firmasi giriniz.\n");

        }
        else
        break;
    }

    int toplamHafta,yazilimKontrol=0,donanimKontrol=0;
    struct tarih yazilimBaslangic,yazilimBitis,yazilimFark,yazilimToplam,donanimBaslangic,donanimBitis,donanimFark,donanimToplam;
    printf("\nYazilim stajin baslangic tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
    scanf("%d%d%d",&yazilimBaslangic.gun,&yazilimBaslangic.ay,&yazilimBaslangic.yil);
    printf("Yazilim stajin bitis tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
    scanf("%d%d%d",&yazilimBitis.gun,&yazilimBitis.ay,&yazilimBitis.yil);

    while(yazilimBitis.yil<yazilimBaslangic.yil || yazilimBaslangic.ay<1 || yazilimBaslangic.ay>12 || yazilimBitis.ay<1 || yazilimBitis.ay>12)
    {
        printf("Girdiginiz tarihleri kontrol ediniz.");
        printf("\nYazilim stajin baslangic tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
        scanf("%d%d%d",&yazilimBaslangic.gun,&yazilimBaslangic.ay,&yazilimBaslangic.yil);
        printf("Yazilim stajin bitis tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
        scanf("%d%d%d",&yazilimBitis.gun,&yazilimBitis.ay,&yazilimBitis.yil);
    }

    printf("Donanim stajin baslangic tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
    scanf("%d%d%d",&donanimBaslangic.gun,&donanimBaslangic.ay,&donanimBaslangic.yil);
    printf("Donanim stajin bitis tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
    scanf("%d%d%d",&donanimBitis.gun,&donanimBitis.ay,&donanimBitis.yil);

    while(donanimBitis.yil<donanimBaslangic.yil || donanimBaslangic.ay<1 || donanimBaslangic.ay>12 || donanimBitis.ay<1 || donanimBitis.ay>12)
    {
            printf("Girdiginiz tarihleri kontrol ediniz.");
            printf("\nDonanim stajin baslangic tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
            scanf("%d%d%d",&donanimBaslangic.gun,&donanimBaslangic.ay,&donanimBaslangic.yil);
            printf("Donanim stajin bitis tarihini araya bosluk birakarak gun,ay,yil sirasiyla giriniz: ");
            scanf("%d%d%d",&donanimBitis.gun,&donanimBitis.ay,&donanimBitis.yil);
    }
    int donanimHafta,yazilimHafta;
    yazilimToplam.toplamGun=TarihFarki(yazilimBitis,yazilimBaslangic,&yazilimFark,&yazilimToplam);
    yazilimHafta=(yazilimToplam.toplamGun/7);

    donanimToplam.toplamGun=TarihFarki(donanimBitis,donanimBaslangic,&donanimFark,&donanimToplam);
    donanimHafta=(donanimToplam.toplamGun/7);

    if(donanimHafta >= 2)
    {
        donanimKontrol=1;
    }
    if(yazilimHafta >= 4)
    {
        yazilimKontrol=1;
    }
    toplamHafta = donanimHafta+yazilimHafta;

    if(donanimKontrol == 1 && yazilimKontrol == 1 && toplamHafta >= 12)
    {
        strcpy(ogrencix.stajKontrol,"Gecerli");
    }
    else
    {
        strcpy(ogrencix.stajKontrol,"Gecersiz");
    }
    rewind(fpOgr);
    while(!feof(fpOgr))
    {
        fscanf(fpOgr,"%s %s %d\n",ogrencix.isim,ogrencix.soyIsim,*&ogrencix.no);
        if(*ogrencix.no == istenilenOgr)
        {
            break;
        }

    }
    fseek(fpStaj,0,SEEK_END);
    fprintf(fpStaj,"%s %s %d ",ogrencix.isim,ogrencix.soyIsim,*ogrencix.no);
    fprintf(fpStaj,"%s %s %d ",firmaKontrol.isim,firmaKontrol.faaliyetAlani,*firmaKontrol.vergiNo);
    fprintf(fpStaj,"%s %s %d ",firmaKontrol2.isim,firmaKontrol2.faaliyetAlani,*firmaKontrol2.vergiNo);
    fprintf(fpStaj,"%s\n",ogrencix.stajKontrol);

    fclose(fpFirma);
    fclose(fpOgr);
    fclose(fpStaj);

}

void stajListeleme(FILE *fpStaj)
{
    fpStaj = fopen("stajBilgileri.txt","a+");
    if (fpStaj == NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    fseek(fpStaj,0,SEEK_END);
    if(ftell(fpStaj) == 0)
    {
        printf("Kayitli staj bilgisi bulunmamakta...\n");
        return 0;

    }

    OgrenciBilgi ogrenciStaj;
    char isimStaj[20],soyIsimStaj[20],stajKontrol[20];
    ogrenciStaj.isim = &isimStaj;
    ogrenciStaj.soyIsim = &soyIsimStaj;
    ogrenciStaj.stajKontrol = &stajKontrol;

    FirmaBilgi firmaStaj;
    char firmaIsimStaj[20],firmaFaaliyetStaj[20];
    firmaStaj.isim = &firmaIsimStaj;
    firmaStaj.faaliyetAlani = &firmaFaaliyetStaj;

    FirmaBilgi firmaStaj2;
    char firmaIsimStaj2[20],firmaFaaliyetStaj2[20];
    firmaStaj2.isim = &firmaIsimStaj2;
    firmaStaj2.faaliyetAlani = &firmaFaaliyetStaj2;
    int tercih;
    while(1)
    {
        printf("Stajini tamamlamis ogrencileri listelemek icin 1'e basiniz.\n");
        printf("Stajini tamamlamamis ogrencileri listelemek icin 2'ye basiniz.\n");
        printf("Tercih: ");
        scanf("%d",&tercih);
        if(tercih == 1)
        {
            rewind(fpStaj);
            while(!feof(fpStaj))
            {
                fscanf(fpStaj,"%s %s %d ",ogrenciStaj.isim,ogrenciStaj.soyIsim,&ogrenciStaj.no);
                fscanf(fpStaj,"%s %s %d ",firmaStaj.isim,firmaStaj.faaliyetAlani,&firmaStaj.vergiNo);
                fscanf(fpStaj,"%s %s %d ",firmaStaj2.isim,firmaStaj2.faaliyetAlani,&firmaStaj2.vergiNo);
                fscanf(fpStaj,"%s\n",ogrenciStaj.stajKontrol);
                if(strcmp(ogrenciStaj.stajKontrol,"Gecersiz") == 0)
                    continue;
                printf("\nOgrenci: %s %s %d \n",ogrenciStaj.isim,ogrenciStaj.soyIsim,ogrenciStaj.no);
                printf("Yazilim Firma: %s %s %d \n",firmaStaj.isim,firmaStaj.faaliyetAlani,firmaStaj.vergiNo);
                printf("Donanim Firma: %s %s %d \n",firmaStaj2.isim,firmaStaj2.faaliyetAlani,firmaStaj2.vergiNo);
                printf("Staj Gecerlilik Durumu: %s\n\n",ogrenciStaj.stajKontrol);
        }
            break;
        }

        if(tercih == 2)
        {
            rewind(fpStaj);
            while(!feof(fpStaj))
            {
                fscanf(fpStaj,"%s %s %d ",ogrenciStaj.isim,ogrenciStaj.soyIsim,&ogrenciStaj.no);
                fscanf(fpStaj,"%s %s %d ",firmaStaj.isim,firmaStaj.faaliyetAlani,&firmaStaj.vergiNo);
                fscanf(fpStaj,"%s %s %d ",firmaStaj2.isim,firmaStaj2.faaliyetAlani,&firmaStaj2.vergiNo);
                fscanf(fpStaj,"%s\n",ogrenciStaj.stajKontrol);
                if(strcmp(ogrenciStaj.stajKontrol,"Gecerli") == 0)
                    continue;
                printf("\nOgrenci: %s %s %d \n",ogrenciStaj.isim,ogrenciStaj.soyIsim,ogrenciStaj.no);
                printf("Yazilim Firma: %s %s %d \n",firmaStaj.isim,firmaStaj.faaliyetAlani,firmaStaj.vergiNo);
                printf("Donanim Firma: %s %s %d \n",firmaStaj2.isim,firmaStaj2.faaliyetAlani,firmaStaj2.vergiNo);
                printf("Staj Gecerlilik Durumu: %s\n\n",ogrenciStaj.stajKontrol);
            }
            break;
        }
        else
            printf("Yanlis tuslama yaptiniz...\n");
    }
    fclose(fpStaj);
}

int TarihFarki(struct tarih Bitis, struct tarih Baslangic, struct tarih *Fark, struct tarih *Toplam)
{
    if(Baslangic.gun>Bitis.gun)
    {
        Bitis.ay=Bitis.ay-1;
        Bitis.gun=Bitis.gun+30;
    }
    Fark->gun=Bitis.gun-Baslangic.gun;
    if(Baslangic.ay>Bitis.ay)
    {
        Bitis.yil=Bitis.yil-1;
        Bitis.ay=Bitis.ay+12;
    }
    Fark->ay=Bitis.ay-Baslangic.ay;

    Fark->yil=Bitis.yil-Baslangic.yil;
    Toplam->toplamGun = (((Fark->yil)*365)+((Fark->ay)*30)+(Fark->gun));
    return Toplam->toplamGun;
}


