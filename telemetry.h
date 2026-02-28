#ifndef TELEMETRY_H  
#define TELEMETRY_H  

#define MAX_KAYIT 100  


//// FONKSİYON PROTOTİPLERİ (İMZALARI)

void sistemi_kur(float baslangic_sicaklik ,int baslangic_sarj ); // Batarya sicakligi ve Şarj verilerini alarak sistemi sürüse hazirlar.
void gaza_bas(); //Araci rastgele bir miktarda hizlandirir, bataryayi azaltir ve sicakligi artirir.
void frene_bas(); // Araci rastgele yavaşlatir ve motorun sogumasini simüle eder.
void rejen_fren();// Enerji geri kazanimli frendir; hizi duşururken bataryayi biraz doldurur.
void telemetri_ve_istatistik_yazdir(); //O anki güncel hizi, sicakliği ve gecmiste kac kere gaza/frene basildiginin ortalamasini ekrana yansitir.
void sistemi_kapat();

#endif 
