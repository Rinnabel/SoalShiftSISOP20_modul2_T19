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
- Program tersebut dijalankan pada pukul 22.43.02. file path .sh yang dijalankan adalah program bash untuk membuat directory. Pada awalnya tidak ada directory bernama “test”. Kemudian setelah program berjalan, dibuatlah directory bernama “test”.

**Kesulitan :**
- Belum pernah mengerjakan soal yang serupa, kurang referensi untuk mengerjakan soal yang diberikan, bingung.

# Nomor 2

Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
1. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].
2. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalahdetik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].
3. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).
4. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yangmenterminasi ini lalu akan mendelete dirinya sendiri.
5. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()



