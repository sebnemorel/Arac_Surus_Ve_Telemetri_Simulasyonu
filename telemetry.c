//STANDART KÜTÜPANELER

#include <stdio.h> 

#include <stdlib.h>   // rastele sayi ( rand ) 
#include <time.h>     // rastele sayi ( rand ) 
                    

//KENDİ KÜTÜPHANEMİZ

#include "telemetry.h" //Kendi yazdığımız rehber dosyayı buraya bağlar.


// SENSÖR VERİ ALMA VE KONTROL
static float guncel_hiz = 0.0; //Anlık Hız
static int batarya_yuzdesi = 0; //Kalan Şarj
static float  motor_sicakligi = 0.0; //Motorun Anlık Sıcaklığı
static float batarya_sicakligi =0.0; //Bataryanın Anlık Sıcaklığı
static float ortam_sicakligi = 20.0;

//DİZİLERLE VERİ KAYDI
static float hizlanma_kayitlari[MAX_KAYIT];
static float yavaslama_kayitlari[MAX_KAYIT];
static float rejen_kayitlari[MAX_KAYIT];//Rejeneratif frenleme yapıldığındaki yavaşlama miktarını saklar.

static int hiz_sayac = 0;
static int yavas_sayac = 0;
static int rejen_sayac =0;
//Bu sayaçlar, dizilerin o an kaçıncı sırasında olduğumuzu tutar.


//VERİLERİ AKTARMA

void sistemi_kur(float baslangic_sicaklik,int baslangic_sarj){
    motor_sicakligi = baslangic_sicaklik;
    batarya_sicakligi = baslangic_sicaklik;
    batarya_yuzdesi = baslangic_sarj;
}

// MENÜ SEÇENEKLERİ VE TERMAL ETKİLERİ
void gaza_bas() {

    
    if(batarya_yuzdesi <= 0.1f){

        printf("Batarya Tükendi! Araç hareket ettirilemiyor.\n");
            return;
    }

    float artis = (rand() % 81 + 20) / 10.0f;

    guncel_hiz += artis;


    

    if(guncel_hiz >= 70.0f){ 
        guncel_hiz = 70.0f;      
    }

    batarya_yuzdesi -= 2.0f;     
    motor_sicakligi += 5.0f;     
    batarya_sicakligi += 2.0f;

    if (hiz_sayac < MAX_KAYIT) { 
    hizlanma_kayitlari[hiz_sayac] = artis; 
    hiz_sayac++;
    }

    printf(" Gaza basildi. Araç %.1f km/s hizlandi.\n", artis);

    if (motor_sicakligi > 90.0f || batarya_sicakligi > 70.0f) { printf("KRITIK HATA: Asiri Isinma!\n"); exit(0); }
}
void frene_bas(){
    if(guncel_hiz <= 0.0){
        printf("Ara zaten duruyor!");
        guncel_hiz = 0.0;
        return;
    }

    float yavaslama = (rand() % 101 + 50) / 10.0f;
    guncel_hiz -= yavaslama;
    if (guncel_hiz < 0.0f) guncel_hiz = 0.0f;

    motor_sicakligi -=3.0f;
    if (motor_sicakligi < ortam_sicakligi) 
    motor_sicakligi = ortam_sicakligi;

    batarya_sicakligi -=1.0f;
    if(batarya_sicakligi < ortam_sicakligi)
     batarya_sicakligi = ortam_sicakligi;

     if(yavas_sayac < MAX_KAYIT){

        yavaslama_kayitlari[yavas_sayac] = yavaslama;
        yavas_sayac++;
     }
     
     printf("Frene basildi. Arac %.1f km/s yavasladi.\n", yavaslama);

     if (motor_sicakligi > 90.0f || batarya_sicakligi > 70.0f) {
         printf("KRITIK HATA: Asiri Isinma!\n"); exit(0); }


}
void rejen_fren(){
    if (guncel_hiz <= 0.0f) {
        printf("[UYARI] Arac dururken rejeneratif fren yapilamaz!\n");
        return;
    }


    float yavaslama = (rand() % 81 + 20) / 10.0f;
    guncel_hiz -= yavaslama;
    if (guncel_hiz < 0.0f) 
    guncel_hiz = 0.0f;

    batarya_yuzdesi += 1.0f;
    if(batarya_yuzdesi  > 100.0)
     batarya_yuzdesi = 100.0;
    
    motor_sicakligi -= 2.0f;
    if(motor_sicakligi < ortam_sicakligi)
    motor_sicakligi = ortam_sicakligi;

    batarya_sicakligi += 1.0f;
    if(batarya_sicakligi > 70.0)
    batarya_sicakligi = 70.0;

    if(rejen_sayac < MAX_KAYIT){
        rejen_kayitlari[rejen_sayac] = yavaslama;
        rejen_sayac ++;
    }

    printf("Rejeneratif fren yapildi. Batarya sarj oluyor.\n");

}
void telemetri_ve_istatistik_yazdir() {
    float gaz_toplam = 0, fren_toplam = 0, rejen_toplam = 0;

    for(int i=0; i<hiz_sayac; i++) gaz_toplam += hizlanma_kayitlari[i];
    for(int i=0; i<yavas_sayac; i++) fren_toplam += yavaslama_kayitlari[i];
    for(int i=0; i<rejen_sayac; i++) rejen_toplam += rejen_kayitlari[i];

    printf("\n--- ANLIK TELEMETRI ---\n");
    printf("Hiz: %.1f km/s | Batarya: %%%.1f | Motor: %.1f C | Batarya: %.1f C\n", 
            guncel_hiz, batarya_yuzdesi, motor_sicakligi, batarya_sicakligi );
    
    printf("\n--- SURUS ISTATISTIKLERI ---\n");
    printf("Gaza Basma: %d (Ort: %.2f)\n", hiz_sayac, (hiz_sayac > 0 ? gaz_toplam/hiz_sayac : 0) );
    printf("Frene Basma: %d (Ort: %.2f)\n", yavas_sayac, (yavas_sayac > 0 ? fren_toplam/yavas_sayac : 0));
    printf("Rejen. Fren: %d (Ort: %.2f)\n", rejen_sayac, (rejen_sayac > 0 ? rejen_toplam/rejen_sayac : 0));
}
void sistemi_kapat() {
    printf("\n Sistem kapatiliyor... Son Surus Istatistikleri:\n");
    telemetri_ve_istatistik_yazdir(); 
    printf(" Motor guvenli bir sekilde kapatildi. Iyi gunler!\n"); 
}




