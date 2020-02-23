# Announcement

Beberapa file yang harus ada dalam repositori tersebut diantaranya:
* Direktori src yang berisi source code yang anda buat.
* File output yang berisi hasil uji dijkstra algorithm pada data uji.
* Makefile. Buatlah sehingga kompilasi program dapat dilakukan hanya dengan pemanggilan command ’make’ saja.
* File README.md yang berisi:
    * Petunjuk penggunaan program.
    * Pembagian tugas. Sampaikan dalam list pengerjaan untuk setiap mahasiswa. Sebagai contoh: XXXX mengerjakan fungsi YYYY, ZZZZ, dan YYZZ.
    * Laporan pengerjaan, dengan struktur laporan sesuai dengan deskripsi pada bagian sebelumnya.
    
# Petunjuk Penggunaan Program

# Pembagian Tugas
- Fata Nugraha (13517109) mengerjakan refactor dari fungsi dijkstra serial, fungsi untuk memparalelkan dijkstra, dan bashfile untuk kompilasi, serta pengujian pada server.
- Edward Alexander jaya (13517115) mengerjakan fungsi dijkstra serial, fungsi untuk memparalelkan dijkstra, dan fungsi file eksternal, serta pengujian pada server.

# Laporan Pengerjaan
#### Deksripsi Solusi Paralel
- Setiap proses melakukan satu atau lebih algoritma dijkstra. Jumlah algoritma dijkstra pada setiap proses ditentukan dari jumlah node (N) dan jumlah proses.
- Contoh:
Pada matriks dengan jumlah node (N) = 1000 dan jumlah proses = 6, **terdapat 1 proses yang menjadi main process** dan **5 proses lainnya yang melakukan algoritma dijkstra.** Oleh karena itu, terdapat 1000 / 5 = 200 kali algoritma dijkstra yang akan dijalankan setiap proses. 
-- **Proses dengan rank (id proses) = 0 menjadi main process**
-- **Proses dengan rank = 1 hingga proses dengan rank = 5 menjadi proses yang menjalankan algoritma dijkstra:**
  - Proses dengan rank = 1 menjalankan algoritma dijkstra dengan node asal 0 hingga 199.
  - Proses dengan rank = 2 menjalankan algoritma dijkstra dengan node asal 200 sampai 399.
  - Proses dengan rank = 3 menjalankan algoritma dijkstra dengan node asal 400 sampai 599.
  - Proses dengan rank = 4 menjalankan algoritma dijkstra dengan node asal 600 sampai 799.
  - Proses dengan rank = 5 menjalankan algoritma dijkstra dengan node asal 800 sampai 999. 
   
  -- **Main process menyatukan semua hasil dari algoritma dijkstra setelah proses dengan rank = 1 sampai proses dengan rank = 5 selesai menjalankan tugasnya.**

#### Analisis Solusi Paralel
Program paralel diawali dengan beberapa baris kode:

    MPI_Status Stat;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();'

`MPI_Status` nantinya digunakan untuk fungsi `MPI_Recv`. Variabel `numtasks` adalah jumlah proses yang berjalan. Variabel `rank` digunakan sebagai nomor pengidentifikasi proses yang berjalan.

`MPI_Barrier` digunakan untuk mencegah semua proses melanjutkan program. Pencegahan tersebut akan dicabut (di-unblock) jika semua proses sudah menjalankan `MPI_Barrier`. Hal ini berguna dalam sinkronisasi waktu mulai pengerjaan dijkstra.

Setelah start_time dijalankan, terdapat inisialisasi beberapa variabel:

    int jobs = N/(numtasks-1);
    long* dataRecv;
    int destinationRank = 0;
    
`int jobs` adalah variabel yang menyimpan jumlah tugas yang harus dijalankan oleh satu proses. `long* dataRecv` digunakan untuk menyimpan data yang diterima oleh `MPI_Recv`. `int destinationRank` digunakan sebagai target pada `MPI_Send`.

Selanjutnya, terdapat dua kasus pada program ini, yaitu proses dengan rank = 0 yang menjalankan program dan proses dengan rank selain 0 yang sedang menjalankan program.

Berikut adalah kode program jika rank proses = 0:

     if (!rank){
        dataRecv = (long*) malloc(sizeof(long) * N*jobs);
        while ( count < numtasks-1 ){
            MPI_Recv(dataRecv, N*jobs, MPI_LONG, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
            printf("Received from process %d ", Stat.MPI_SOURCE);
            for (int i = 0; i < jobs; ++i) {
                for (int j = 0; j < N; ++j) {
                    graph[Stat.MPI_SOURCE * jobs - jobs + i][j] = dataRecv[i * N + j];
                }
            }
            count++;
        }
        free(dataRecv);
    }

Singkatnya, `dataRecv` diberikan alokasi sebanyak N (jumlah node) dikali dengan `jobs`. `MPI_Recv` menerima `dataRecv` dan variabel `graph` yang bertipe `**long` menyimpan jarak terpendek dari dijkstra sejumlah `jobs` (dikerjakan oleh satu proses). Variabel `graph` pada akhirnya menyimpan seluruh jarak terpendek dari setiap node ke node lain. 

Variabel `count` digunakan untuk menghitung jumlah proses yang sudah selesai menjalankan dijkstra. Jika sudah, maka kondisi `while (count < numtasks -1)` tidak terpenuhi kembali.

Berikut adalah kode program jika rank proses bukan 0:

    long *dataSend = (long*) malloc(sizeof(long*) * N * jobs);
        int count = 0;
        for (int i = rank*jobs-jobs; i < rank*jobs; ++i)
        {   
            dijkstra(graph, i);
            for (int j = 0; j < N; j++) {
                dataSend[count * N + j] = graph[i][j];
            }
            count++;
            // printf("Print job %d from rank %d\n", i, rank);
        }
        MPI_Send(dataSend, N*jobs, MPI_LONG, destinationRank, tag, MPI_COMM_WORLD);
        free(dataSend);

Singkatnya, setiap proses menjalankan fungsi dijkstra. Fungsi dijkstra mengubah nilai dari `graph[<node yang dikerjakan>]` menjadi jarak terpendek dari node yang dikerjakan ke semua node. 

`MPI_Send` digunakan untuk mengirim data berupa jarak terpendek dari node yang dikerjakan ke semua node dan diterima oleh `MPI_Recv` pada proses dengan rank = 0.

Sebenarnya terdapat solusi yang lebih cepat, yaitu dengan meng-assign setiap process untuk mengambil task lain ketika process tersebut sudah selesai, bukan dengan membagi task di awal. Hal ini mungkin dengan menggunakan `pragma omp task`, namun use casenya pada shared memory model.

#### Jumlah Thread yang Digunakan
- Terdapat enam proses yang digunakan pada program ini.
- IP server dimulai dari 167.205.35.150 sampai 167.205.35.155. Jika digunakan command `lscpu`, terlihat bahwa setiap server (artinya setiap IP) memiliki jumlah CPU core sebanyak satu. Dengan alasan tersebut, terdapat enam proses yang bisa dijalankan.
#### Pengukuran Kinerja untuk tiap Kasus Uji
Berikut adalah hasil pengujian yang dikerjakan pada server 13517115@167.205.35.150:
- **N = 100**
  | Tipe  |  Percobaan 1 | Percobaan 2  | Percobaan 3  |
  |---|---|---|---|
  | Serial |  0.012495 s |  0.013546 s |  0.013202 s |
  | Paralel  |  0.011397 s | 0.009392 s  | 0.011365 s |
- **N = 500**
  | Tipe  |  Percobaan 1 | Percobaan 2  | Percobaan 3  |
  |---|---|---|---|
  | Serial |  1.637802 s  |  1.531207 s |  1.663832 s |
  | Paralel  |  1.567543 s | 1.368517 s  |  1.004626 s |
- **N = 1000**
  | Tipe  |  Percobaan 1 | Percobaan 2  | Percobaan 3  |
  |---|---|---|---|
  | Serial | 13.642516 s | 14.617350 s | 14.184775 s  |
  | Paralel  | 4.268241 s  |  5.128194 s | 4.290042 s|
- **N = 3000**
  | Tipe  |  Percobaan 1 | Percobaan 2  | Percobaan 3  |
  |---|---|---|---|
  | Serial | 480.282249 s  |  481.598290 s |  396.111461 s|
  | Paralel  | 278.312732 s | 308.372772 s |  198.770362 s|

#### Analisis Perbandingan Kinerja Serial dan Paralel
- 


