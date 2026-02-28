 #include <stdio.h>
 #include <time.h>
 #include <stdlib.h> 
 #include "telemetry.h"

 int main(){

     srand(time(NULL));
   
    int secim = 0;
    float batarya_sicakligi =0.0;
    int sarj_yuzdesi=0;
    char kapi_durumu=0;
    int fren_pedali=0;

    printf("--- ELEKTROMOBIL GUVENLIK KONTROLU---\n");

    printf("Batarya Sicakligini Girin : ");
    scanf("%f",&batarya_sicakligi);

    printf("Sarj Yuzdesini Girin (0-100) : ");
    scanf("%d", &sarj_yuzdesi);

    printf("Kapi Durumunu Girin (A: Acik , K: Kapali) : ");
    scanf(" %c", &kapi_durumu);

    printf("Fren Pedali Durumunu Girin (1: Basili , 0 : Degil) : ");
    scanf("%d", &fren_pedali);

    if(batarya_sicakligi < -100 || batarya_sicakligi > 200){
        printf("Batarya sicakligi -100'den kucuk veya 200'den buyuk olamaz.\n");
    }
    else if(sarj_yuzdesi< 0 || sarj_yuzdesi > 100){
        printf("Hatali Sensor Verisi: Sarj %%0'dan kucuk veya %%100'den buyuk olamaz!\n");
    }
    else if(kapi_durumu != 'A'&& kapi_durumu != 'K'){
        printf("Hatali Kapi Durumu Verisi: Kapi durumu acik (A) veya kapali (K) olabilir.\n");
    }

    else if(batarya_sicakligi > 60){
        printf("KRITIK HATA : Motor Asiri Isindi! Surus Engellendi.\n");

    }
    else if(sarj_yuzdesi < 10){
        printf("UYARI: Batarya Kritik Seviyede! Surus Baslatilamaz.\n");
    }
    else if(kapi_durumu == 'A'){
        printf("HATA: Kapilar Acik! Lutfen Kapatiniz.\n ");
    }
    else if(fren_pedali == 0){
        printf("BILGI: Guvenlik icin frene tekrar basarak deneyin.\n");
    }
    else {
        printf("BASARILI: SISTEM HAZIR. MOTOR BASLATILIYOR...\n");
        sistemi_kur(batarya_sicakligi, sarj_yuzdesi);

        
    //                               ANA MENÜ DÖNGÜSÜ 
    while (1) {
        printf("\n--- TUFAN ELEKTROMOBIL SURUS SIMULASYONU ---\n");
        printf("1. Gaza Bas\n");
        printf("2. Frene Bas\n");
        printf("3. Rejeneratif Frenleme Yap\n");
        printf("4. Anlik Telemetri ve İstatistikleri Oku\n");
        printf("5. Sistemi Kapat\n");
        printf("Seciminiz: ");

        // Terminalin Çökmesini Engelleyen Scanf Kontrolü (Buffer Bug Çözümü) 
        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n'); 
            printf("[HATA] Gecersiz girdi! Lutfen 1-5 arasi bir sayi girin.\n");
            continue;
        }

        switch (secim) {
            case 1: gaza_bas(); break; 
            case 2: frene_bas(); break; 
            case 3: rejen_fren(); break; 
            case 4: telemetri_ve_istatistik_yazdir(); break; 
            case 5: 
                sistemi_kapat(); 
                return 0; 
            default:
                printf("[UYARI] Hatali secim yaptiniz!\n");
        }
    }

    }




    return 0;

}
