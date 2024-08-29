# Library Information 
**Author**     : Ahmad Sony Alfathani  
**Version**    : V.1.1  
**Date**       : Augt 28, 2024  
**Description**: This library version is used to read LDR module  
**Status**     : Still updating  

| No | Function | Example | Description |Status |
|----|----------|-------------|--------| --------|
| 1  | #include <LDR.h> | #include <LDR.h> | Membuat library sendiri Bernama LDR.h | Oke |
| 2  | LDR ldrku(LDRPIN, LDRTYPE); | LDR ldrku(13, 5); | digunakan untuk membuat objek dari kelas LDR | Oke | 
| 3  | ldrku.begin(resolusiADC); | ldrku.begin(12); | menginisialisasi penggunaan sensor LDR default resolsusi 12 bit| oke | 
| 4  | ldrku.readIntensitas(mode); | ldrku.readIntensitas(1); | Mendapatkan nilai intensitas Cahaya mode=1 (luk) atau mode=2(KLux) | oke | 
| 5  | dhtku.readState(threshold); | dhtku.readState(5000); | Mendapatkan status terang (“0”) atau gelap (“1”), berdasarkan threshold tertentu dalam lux | oke | 
