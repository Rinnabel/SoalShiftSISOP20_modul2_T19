# SoalShiftSISOP2020_modul2_T19

## Nama Angggota

- Adeela Nurul Fadhila [05311840000001]
- Muhammad Zulfikar Fauzi [05311840000012]

# Nomor 1

Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

**a.** Program menerima 4 argumen berupa:

```
        Detik: 0-59 atau * (any value)
        Menit: 0-59 atau * (any value)
        Jam: 0-23 atau * (any value)
        Path file .sh
```

**b.** Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai

**c.** Program hanya menerima 1 config cron

**d.** Program berjalan di background (daemon)

**e.** Tidak boleh menggunakan fungsi system()

Contoh: `./program \* 34 7 /home/somi/test.sh` (script bash test.sh akan dijalankan setiap jam 07.34 waktu lokal)

Asumsi Soal:

Soal ini mengharuskan kami untuk membuat sebuah program C yang mirip-mirip seperti crontab. Program ini hanya menerima 4 argumen, yaitu detik, menit, jam, dan file yang berupa .sh. Jika argumen lebih dari 4, atau tidak sesuai dengan ketentuannya, maka akan menghasilkan output yang berupa pesan error. Kemudian program tersebut berjalan di background (daemon) dan tidak menggunakan fungsi system().

#### Link code soal 1 :

##### Source code :

**Pembahasan**\
(Fungsi yang sudah dijelaskan diatasnya tidak akan dijelaskan guna mempersingkat laporan dan efisiensi waktu)

``` c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
```
- Merupakan berbagai library yang digunakan untuk source code ini.
``` c
int main(int argc, char *argv[]) {
```
- Deklarasi main yang dapat mengambil argumen ( int argc untuk jumlah argumen, argv pointer ke argumen yang diberikan)
``` c
if (argc != 5) {
```
- If untuk cek jika argumen yang dimasukkan sudah sesuai kriteria, yaitu jumlahnya 5. (nama program, detik, menit, jam, dan path file .sh)
``` c
printf("Masukin yang bener dong!\n");
``` 
- Error message (Masukin yang bener dong)  jika argumen berjumlah tidak benar menggunakan printf.
``` c
exit(EXIT_FAILURE);
```
- Program akan berhenti ( exit )
``` c
struct tm t;
time_t tm;
``` 
- Deklarasi tipe data struct
``` c
pid_t pid, sid;
``` 
- Deklarasi tipe data pid_t dengan nama variabel pid dan sid
``` c
pid = fork();
```
- Melakukan fungsi fork pada pid, fork adalah fungsi yang menghasilkan child process dari suatu pid
``` 
if (pid < 0) {
``` 
- If untuk cek jika pid kurang dari 0
``` c
if (pid > 0) {
``` 
- If untuk cek jika pid lebih dari 0
``` c
exit(EXIT_SUCCESS);
```
- Fungsi exit untuk mengindikaskan jika program sukses
``` c
umask(0);
```
- Umask untuk memberi akses rwx terhadap semua file yang dibuat oleh daemon kepada kita
``` c
sid = setsid();
```
- Setsid untuk membuat session id baru pada sid
``` c
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```
- Kumpulan fungsi close untuk menghilangkan interaksi user dengan program daemon
``` c
while (1) {
```
- Perulangan while dengan kondisi 1(true)
``` c
tm = time(NULL);
t = *localtime(&tm);
``` 
- tm berisi waktu epoch. t mengubah/mengkorversi waktu epoch menjadi sesuai dengan localtime di pc.
``` c
if ((t.tm_sec == atoi(argv[1])) || (strcmp(argv[1], "*") == 0) && (t.tm_min == atoi(argv[2])) || (strcmp(argv[2], "*") == 0) && (t.tm_hour == atoi(argv[3])) || (strcmp(argv[3], "*") == 0)) {
``` 
- If yang digunakan untuk mengecek inputan argumen. Argumen dicek satu persatu dan dilakukan proses yang sesuai. Bernilai true apabila argumen yang diinputkan sama dengan * atau waktunya sesuai dengan waktu saat ini.
``` c
if (fork() == 0) {
	execl("/bin/bash", "bash", argv[4], NULL);
``` 
- patch file .sh dijalankan menggunakan exexcl
``` c
sleep(1);
``` 
- program di sleep tiap 1 detik

**Screenshot hasil :**\
![](soal1/soal1.png)



