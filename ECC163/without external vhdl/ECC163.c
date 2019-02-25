//Orlando, G. and C. Paar, 2000. An efficient squaring architecture for GF(2m)

#if defined(AUGH_SYNTHESIS) && !defined(STDIO8)

	#include <augh.h>
	
	uint1_t finish;

	uint32_t stdin;
	uint32_t stdout;

	static inline uint32_t read32() {
		uint32_t u32;
		fifo_read(stdin, &u32);
		return u32;
	}

	static inline void write32(uint32_t u32) {
		fifo_write(stdout, &u32);
	}

	static inline void write8(uint8_t u8) {
		fifo_write(stdout, &u8);
	}


#endif

//mendefinisikan boolean
#define TRUE 1
#define FALSE 0

//mendefinisikan dua pangkat	
#define pow2(a, b) do {\
	b = 0x01 << a;\
}while(0)
	
//mengambil MSB dan menaruhnya di LSB
#define MtoL(a, b) do {\
	pow2(31, b);\
	b = a&b;\
	b = b >> 31;\
}while(0)

//mencari nilai absolut
#define absolut(a,b,c) do {\
	if(a>b)			\
	{				\
		c = a-b;	\
	} else			\
	{				\
		c = b-a;	\
	}				\
}while(0)

static uint16_t LU_Table[256] = { 
0x0000, 0x0001, 0x0004, 0x0005, 0x0010, 0x0011, 0x0014, 0x0015, 
0x0040, 0x0041, 0x0044, 0x0045, 0x0050, 0x0051, 0x0054, 0x0055, 
0x0100, 0x0101, 0x0104, 0x0105, 0x0110, 0x0111, 0x0114, 0x0115, 
0x0140, 0x0141, 0x0144, 0x0145, 0x0150, 0x0151, 0x0154, 0x0155, 
0x0400, 0x0401, 0x0404, 0x0405, 0x0410, 0x0411, 0x0414, 0x0415, 
0x0440, 0x0441, 0x0444, 0x0445, 0x0450, 0x0451, 0x0454, 0x0455, 
0x0500, 0x0501, 0x0504, 0x0505, 0x0510, 0x0511, 0x0514, 0x0515, 
0x0540, 0x0541, 0x0544, 0x0545, 0x0550, 0x0551, 0x0554, 0x0555, 
0x1000, 0x1001, 0x1004, 0x1005, 0x1010, 0x1011, 0x1014, 0x1015, 
0x1040, 0x1041, 0x1044, 0x1045, 0x1050, 0x1051, 0x1054, 0x1055, 
0x1100, 0x1101, 0x1104, 0x1105, 0x1110, 0x1111, 0x1114, 0x1115, 
0x1140, 0x1141, 0x1144, 0x1145, 0x1150, 0x1151, 0x1154, 0x1155, 
0x1400, 0x1401, 0x1404, 0x1405, 0x1410, 0x1411, 0x1414, 0x1415, 
0x1440, 0x1441, 0x1444, 0x1445, 0x1450, 0x1451, 0x1454, 0x1455, 
0x1500, 0x1501, 0x1504, 0x1505, 0x1510, 0x1511, 0x1514, 0x1515, 
0x1540, 0x1541, 0x1544, 0x1545, 0x1550, 0x1551, 0x1554, 0x1555, 
0x4000, 0x4001, 0x4004, 0x4005, 0x4010, 0x4011, 0x4014, 0x4015, 
0x4040, 0x4041, 0x4044, 0x4045, 0x4050, 0x4051, 0x4054, 0x4055, 
0x4100, 0x4101, 0x4104, 0x4105, 0x4110, 0x4111, 0x4114, 0x4115, 
0x4140, 0x4141, 0x4144, 0x4145, 0x4150, 0x4151, 0x4154, 0x4155, 
0x4400, 0x4401, 0x4404, 0x4405, 0x4410, 0x4411, 0x4414, 0x4415, 
0x4440, 0x4441, 0x4444, 0x4445, 0x4450, 0x4451, 0x4454, 0x4455, 
0x4500, 0x4501, 0x4504, 0x4505, 0x4510, 0x4511, 0x4514, 0x4515, 
0x4540, 0x4541, 0x4544, 0x4545, 0x4550, 0x4551, 0x4554, 0x4555, 
0x5000, 0x5001, 0x5004, 0x5005, 0x5010, 0x5011, 0x5014, 0x5015, 
0x5040, 0x5041, 0x5044, 0x5045, 0x5050, 0x5051, 0x5054, 0x5055, 
0x5100, 0x5101, 0x5104, 0x5105, 0x5110, 0x5111, 0x5114, 0x5115, 
0x5140, 0x5141, 0x5144, 0x5145, 0x5150, 0x5151, 0x5154, 0x5155, 
0x5400, 0x5401, 0x5404, 0x5405, 0x5410, 0x5411, 0x5414, 0x5415, 
0x5440, 0x5441, 0x5444, 0x5445, 0x5450, 0x5451, 0x5454, 0x5455, 
0x5500, 0x5501, 0x5504, 0x5505, 0x5510, 0x5511, 0x5514, 0x5515, 
0x5540, 0x5541, 0x5544, 0x5545, 0x5550, 0x5551, 0x5554, 0x5555};


//titik awal G sumbu x
static uint32_t G_x[6] = 
{ 0x5C94EEE8, 0xDE4E6D5E, 0xAA07D793, 0x7BBC11AC, 0xFE13C053, 0x00000002};

//titik awal G sumbu y
static uint32_t G_y[6] = 
{ 0xCCDAA3D9, 0x0536D538, 0x321F2E80, 0x5D38FF58, 0x89070FB0, 0x00000002};  

//pereduksi
static uint32_t f[6] = {0x000000C9, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000008}; // variabel pereduksi = z163 + z7 + z6 + z3 + 1

uint32_t in1_add[6], in2_add[6], out_add[6];
uint32_t in_sqr[6], out_sqr[6];
uint32_t in1_mult[6], in2_mult[6], out_mult[6];
uint32_t in_invers[6], out_invers[6];
uint32_t in_modred[11], out_modred[6];
  
static inline void add()
{
	uint8_t i;

	for(i = 0; i <= 5; i++)
	{
		out_add[i] = in1_add[i]^in2_add[i];
		
	}
}

//dari ECC Guide
static inline void modred()
{
	uint32_t T;
	uint8_t i;
	uint8_t j;
	
	for(i = 6; i <= 10; i++)
	{
		j = 16-i;
		T = in_modred[j];
		in_modred[j - 6] = in_modred[j - 6]^(T << 29);
		in_modred[j - 5] = in_modred[j - 5]^(T << 4)^(T << 3)^T^(T >> 3);
		in_modred[j - 4] = in_modred[j - 4]^(T >> 28)^(T >> 29);
	}
	T = in_modred[5] >> 3; //mengekstrak bit ke 3-31 dari In[5]
	in_modred[0] = in_modred[0]^(T << 7)^(T << 6)^(T << 3)^T;
	in_modred[1] = in_modred[1]^(T >> 25)^(T >> 26);
	in_modred[5] = in_modred[5]&0x00000007; //menghilangkan bit tereduksi dari In[5]
	
	for(i = 0; i<= 5; i++)
	{
		out_modred[i] = in_modred[i];	
	}
}

//variabel untuk fungsi invers
uint8_t deg_u, deg_v;
uint32_t b[6], c[6], u[6], v[6], xjv[6], xjc[6], temp[6];

static inline void get_u()
{
	uint8_t indeks1, indeks2;
	uint8_t i;
	uint32_t mask_u;

	if(deg_u > deg_v){
		indeks1 = deg_u % 32;
		pow2(indeks1+1, mask_u);
		mask_u = mask_u - 1;

		indeks2 = deg_u / 32;
		indeks2 = 5-indeks2;
		for (i = 0; i<= indeks2; i++){
			if(i == indeks2){
				u[5-i] = u[5-i] & mask_u;
			}else{
				u[5-i] = 0;
			}
		}
	}
	else{
		indeks1 = deg_v % 32;
		pow2(indeks1+1, mask_u);
		mask_u = mask_u - 1;

		indeks2 = deg_v / 32;
		indeks2 = 5-indeks2;
		for (i = 0; i<= indeks2; i++){
			if(i == indeks2){
				u[5-i] = u[5-i] & mask_u;
			}else{
				u[5-i] = 0;
			}
		}
	}
}
// dari algoritma lopez halaman 8 Software Implementation of ECC over Binary Field
static inline void invers()
{
	uint32_t tempow;
	uint32_t mask_shift;

	uint8_t i, j, k, increment;
	uint8_t pangkat_ditemukan; //untuk menentukan apakah lokasi pangkat telah ditemukan
	uint8_t loc_degu = 0;
	uint8_t loc_degv = 0;
	
	//inisialisasi
	b[0] = 0x00000001;
	deg_u = 1; //supaya masuk ke loop

	for(i = 0; i <= 5; i++){
		v[i] = f[i];
		u[i] = in_invers[i];
	}
	
	while(deg_u != 0)
	{
		//inisialisasi untuk penemuan pangkat
		pangkat_ditemukan = 0;
		i = loc_degu;

		while((pangkat_ditemukan == 0)&&(i<=5))
		{// mencari pangkat u
			j = 0; //dicek dari most significant bit = 0
		
			while((pangkat_ditemukan == 0)&&(j != 32)) //loop ketika pangkat belum ditemukan atau elemen 32 bit belum semua dicek
			{	
				pow2(31-j, tempow); //(2 pangkat 31-j) dilakukan operasi 'and' dengan elemen array u untuk menentukan bit pangkat apakah telah ditemukan
				tempow = u[5-i]&tempow;
				if(tempow != 0){
					pangkat_ditemukan = 1;
					deg_u = 32*(5-i)+31-j;
				}
				if((i == 5)&&(j == 31)) //jika nol
				{
					pangkat_ditemukan = 1;
					deg_u = 0;
				}
				j++;
			}
			loc_degu = i;
			i++;
		}
		
		//inisialisasi untuk penemuan pangkat
		i = loc_degv;
		pangkat_ditemukan = 0;

		while((pangkat_ditemukan == 0)&&(i<=5))
		{//lalu mencari pangkat v
			j = 0; 
			while((pangkat_ditemukan == 0)&&(j != 32))
			{	
				pow2(31-j, tempow); 
				tempow = v[5-i]&tempow;
				if(tempow != 0){
					pangkat_ditemukan = 1;
					deg_v = 32*(5-i)+31-j;
				}
				if((i == 5)&&(j == 31)) //jika nol
				{
					pangkat_ditemukan = 1;
					deg_v = 0;
				}
				j++;
			}
			loc_degv = i;
			i++;
		}

		absolut(deg_v, deg_u, k);
		
		if(deg_u < deg_v)
		{
			//menukar u dengan v
			for(i = 0; i <= 5; i++)
			{
				temp[i] = u[i];	
				u[i] = v[i];
				v[i] = temp[i];
			}
			
			//menukar b dengan c
			for(i = 0; i <= 5; i++)
			{
				temp[i] = b[i];	
				b[i] = c[i];
				c[i] = temp[i];
			}
		}

		if(deg_v == 0){
			deg_u = 0;
		}

		if(k<=31)
		{	
			if(k == 0){
				for(i = 0; i<=5; i++){
					u[i] = u[i] ^ v[i];
					b[i] = b[i] ^ c[i];
				}
			}else{
				//melakukan pergeseran ke MSB sebanyak k bit
				xjv[5] = (v[5] << k) ^ (v[4]>>(32-k));
				xjv[4] = (v[4] << k) ^ (v[3]>>(32-k));
				xjv[3] = (v[3] << k) ^ (v[2]>>(32-k));
				xjv[2] = (v[2] << k) ^ (v[1]>>(32-k));
				xjv[1] = (v[1] << k) ^ (v[0]>>(32-k));
				xjc[5] = (c[5] << k) ^ (c[4]>>(32-k));
				xjc[4] = (c[4] << k) ^ (c[3]>>(32-k));
				xjc[3] = (c[3] << k) ^ (c[2]>>(32-k));
				xjc[2] = (c[2] << k) ^ (c[1]>>(32-k));
				xjc[1] = (c[1] << k) ^ (c[0]>>(32-k));

				xjv[0] = v[0] << k;
				xjc[0] = c[0] << k;
			
				//u = u + (x^j)v, b = b + (x^j)c.
				for(i = 0; i<= 5; i++)
				{	
					u[i] = u[i] ^ xjv[i];
					b[i] = b[i] ^ xjc[i];
				}
			}
		} 
		else if(k>31 && k<=63)
		{
			k = k % 32;
			if(k == 0){
				u[5] = u[5] ^ v[4]; b[5] = b[5] ^ c[4];
				u[4] = u[4] ^ v[3]; b[4] = b[4] ^ c[3];
				u[3] = u[3] ^ v[2]; b[3] = b[3] ^ c[2];
				u[2] = u[2] ^ v[1]; b[2] = b[2] ^ c[1];
				u[1] = u[1] ^ v[0]; b[1] = b[1] ^ c[0];

			}else{
				//melakukan pergeseran ke MSB sebanyak k bit
				xjv[5] = (v[4] << k) ^ (v[3]>>(32-k));
				xjv[4] = (v[3] << k) ^ (v[2]>>(32-k));
				xjv[3] = (v[2] << k) ^ (v[1]>>(32-k));
				xjv[2] = (v[1] << k) ^ (v[0]>>(32-k));
				xjc[5] = (c[4] << k) ^ (c[3]>>(32-k));
				xjc[4] = (c[3] << k) ^ (c[2]>>(32-k));
				xjc[3] = (c[2] << k) ^ (c[1]>>(32-k));
				xjc[2] = (c[1] << k) ^ (c[0]>>(32-k));

				xjv[1] = v[0] << k; xjv[0] = 0;
				xjc[1] = c[0] << k; xjc[0] = 0;

				//u = u + (x^j)v, b = b + (x^j)c.
				for(i = 1; i<= 5; i++)
				{	
					u[i] = u[i] ^ xjv[i];
					b[i] = b[i] ^ xjc[i];
				}
			}
		} 
		else if(k>63 && k<=95)
		{
			k = k % 64;
			if(k == 0){
				u[5] = u[5] ^ v[3]; b[5] = b[5] ^ c[3];
				u[4] = u[4] ^ v[2]; b[4] = b[4] ^ c[2];
				u[3] = u[3] ^ v[1]; b[3] = b[3] ^ c[1];
				u[2] = u[2] ^ v[0]; b[2] = b[2] ^ c[0];
			}else{
				//melakukan pergeseran ke MSB sebanyak k bit

				xjv[5] = (v[3] << k) ^ (v[2]>>(32-k));
				xjv[4] = (v[2] << k) ^ (v[1]>>(32-k));
				xjv[3] = (v[1] << k) ^ (v[0]>>(32-k));
				xjc[5] = (c[3] << k) ^ (c[2]>>(32-k));
				xjc[4] = (c[2] << k) ^ (c[1]>>(32-k));
				xjc[3] = (c[1] << k) ^ (c[0]>>(32-k));

				xjv[2] = v[0] << k; xjv[1] = 0; xjv[0] = 0;
				xjc[2] = c[0] << k; xjc[1] = 0; xjc[0] = 0;

				//u = u + (x^j)v, b = b + (x^j)c.
				for(i = 2; i<= 5; i++)
				{	
					u[i] = u[i] ^ xjv[i];
					b[i] = b[i] ^ xjc[i];
				}
			}
		} 
		else if(k>95 && k<=127)
		{
			k = k % 96;
			if(k == 0){
				u[5] = u[5] ^ v[2]; b[5] = b[5] ^ c[2];
				u[4] = u[4] ^ v[1]; b[4] = b[4] ^ c[1];
				u[3] = u[3] ^ v[0]; b[3] = b[3] ^ c[0];
			}else{
				//melakukan pergeseran ke MSB sebanyak k bit

				xjv[5] = (v[2] << k) ^ (v[1]>>(32-k));
				xjv[4] = (v[1] << k) ^ (v[0]>>(32-k));
				xjc[5] = (c[2] << k) ^ (c[1]>>(32-k));
				xjc[4] = (c[1] << k) ^ (c[0]>>(32-k));
		
				xjv[3] = v[0] << k; xjv[2] = 0; xjv[1] = 0; xjv[0] = 0;
				xjc[3] = c[0] << k; xjc[2] = 0; xjc[1] = 0; xjc[0] = 0;

				//u = u + (x^j)v, b = b + (x^j)c.
				for(i = 3; i<= 5; i++)
				{	
					u[i] = u[i] ^ xjv[i];
					b[i] = b[i] ^ xjc[i];
				}
			}
		}
		else if(k>127 && k<=159)
		{
			k = k % 128;
			if(k == 0){
				u[5] = u[5] ^ v[1]; b[5] = b[5] ^ c[1];
				u[4] = u[4] ^ v[0]; b[4] = b[4] ^ c[0];
			}else{
				//melakukan pergeseran ke MSB sebanyak k bit
				xjv[5] = (v[1] << k) ^ (v[0]>>(32-k));
				xjc[5] = (c[1] << k) ^ (c[0]>>(32-k));

				xjv[4] = v[0] << k; xjv[3] = 0; xjv[2] = 0; xjv[1] = 0; xjv[0] = 0;
				xjc[4] = c[0] << k; xjc[3] = 0; xjc[2] = 0; xjc[1] = 0; xjc[0] = 0;

				for(i = 4; i<= 5; i++)
				{	
					u[i] = u[i] ^ xjv[i];
					b[i] = b[i] ^ xjc[i];
				}
			}
		}
		else if(k>159 && k<=191)
		{
			k = k % 160;
			if(k == 0){
				u[5] = u[5] ^ v[0]; b[5] = b[5] ^ c[0];
			}else{
				//melakukan pergeseran ke MSB sebanyak k bit

				xjv[5] = v[0] << k; xjv[4] = 0; xjv[3] = 0; xjv[2] = 0; xjv[1] = 0; xjv[0] = 0;
				xjc[5] = c[0] << k; xjc[4] = 0; xjc[3] = 0; xjc[2] = 0; xjc[1] = 0; xjc[0] = 0;

				//u = u - (x^j)v, b = b - (x^j)c.

				u[5] = u[5] ^ xjv[5];
				b[5] = b[5] ^ xjc[5];
			}
		}

		get_u();
	}

	for(i = 0; i <= 5; i++)
	{
		out_invers[i] = b[i];
	}
}

// High-Speed Software Multiplication in F2m, Left to Right Comb Method
static inline void mult()
{
	uint8_t i, j, k, l;
	uint32_t T[11];
	uint32_t temp_in1[6], temp_pow, temp_T[11];
	
	for(j = 0; j <= 10; j++)
	{
		T[j] = 0;
	}

	for(j = 0; j <= 31; j++)
	{
		l = 31-j;
		for(i = 0; i <= 5; i++)
		{
			pow2(l,temp_pow);
			temp_in1[i] = in1_mult[i] & temp_pow; 
			if(temp_in1[i] > 0)
			{
				for(k = 0; k <= 5; k++)
				{
					T[k+i] = T[k+i]^in2_mult[k];
				}
			}
		}
		if(l > 0)
		{
			for(i = 0; i < 10; i++)
			{
				MtoL(T[i], temp_T[i]);
			}
			for(i = 0; i < 10; i++)
			{
				T[i+1] = (T[i+1] << 1) | temp_T[i];	
				if(i == 0){
					T[i] = T[i] << 1;
				}
				
			}
		}
	}

	for(i = 0; i <= 10; i++)in_modred[i]=T[i];
	modred();
	for(i = 0; i <= 5; i++)out_mult[i]=out_modred[i];
}

//fungsi didapat dari EFFICIENT IMPLEMENTATION OF ELLIPTIC CURVE CRYPTOGRAPHY IN WIRELESS SENSORS oleh Dahab dan Lopez halaman 10
static inline void sqr_rdc()
{
	uint32_t sqr_arr[11];
	uint8_t selector;
	uint32_t temp;					//penampung 
	uint8_t i, j;					//untuk iterasi
	
	for(i = 0; i <= 5; i++){
		for(j = 0; j <= 3; j++){
			selector = (in_sqr[i] >> (8*j)) & 0x000000FF;
			if(j == 0){
				sqr_arr[2*i] = 0x00000000 ^ LU_Table[selector];
			}else if(j == 1){
				temp = 0x00000000 ^ LU_Table[selector];
				temp = temp << 16;
				sqr_arr[2*i] = temp ^ sqr_arr[2*i];
			}else if((j == 2) && (i < 5)){
				sqr_arr[2*i+1] = 0x00000000 ^ LU_Table[selector];
			}else if((j == 3) && (i < 5)){
				temp = 0x00000000 ^ LU_Table[selector];
				temp = temp << 16;
				sqr_arr[2*i+1] = temp ^ sqr_arr[2*i+1];
			}
		}
	}  

	for(i = 0; i <= 10; i++)in_modred[i]=sqr_arr[i];
	modred();
	for(i = 0; i <= 5; i++)out_sqr[i]=out_modred[i];
}

// Didapat dari Fast Multiplication on Elliptic Curves over GF (2 m ) without Precomputation -> Projective Version

#if defined(AUGH_SYNTHESIS)
void augh_main ()
#else
int main ()
#endif
{
	uint32_t X1[6], Z1[6], X2[6], Z2[6], T1[6], T2[6], T3[6], T4[6];
	uint8_t i, j, k;
	uint32_t sign;
	uint32_t priv_key[6], temp_priv[6], X_key[6], Y_key[6];
	
	augh_port_out(finish);
    
	finish = 0;
	
	do {
		for(i = 0; i <= 5; i++)
		{
			priv_key[i] = read32();	
		}
		
		//Step 3 page 7
		for(i = 0; i <= 5; i++)X1[i]=G_x[i];
		Z1[0] = 1; Z1[1] = 0; Z1[2] = 0; Z1[3] = 0; Z1[4] = 0; Z1[5] = 0;
		for(i = 0; i <= 5; i++)in_sqr[i]=G_x[i];sqr_rdc();
		for(i = 0; i <= 5; i++)X2[i]=out_sqr[i];
		for(i = 0; i <= 5; i++)in_sqr[i]=X2[i];sqr_rdc(); 
		for(i = 0; i <= 5; i++)X2[i]=out_sqr[i];
		X2[0] = X2[0] + 1;
	
		for(i = 0; i <= 5; i++)in_sqr[i]=G_x[i]; sqr_rdc(); for(i = 0; i <= 5; i++)Z2[i]=out_sqr[i];
	
		//Step 4 Page 7
		for(k = 0; k <= 161; k++)
		{
			j = (161-k)/32;
			pow2((161-k)%32, sign);
			temp_priv[j] = sign &  priv_key[j];
		
			if(temp_priv[j] == sign){
				//adding
				for(i = 0; i <= 5; i++)T1[i]=G_x[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
				mult(); 
				for(i = 0; i <= 5; i++)X1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X2[i];
				mult(); 
				for(i = 0; i <= 5; i++)Z1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
				mult(); 
				for(i = 0; i <= 5; i++)T2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_add[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_add[i]=X1[i];
				add(); 
				for(i = 0; i <= 5; i++)Z1[i]=out_add[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=Z1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)Z1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
				mult(); 
				for(i = 0; i <= 5; i++)X1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_add[i]=T2[i];
				for(i = 0; i <= 5; i++)in2_add[i]=X1[i];
				add(); 
				for(i = 0; i <= 5; i++)X1[i]=out_add[i];
			
				//doubling
				T1[0] = 1; T1[1] = 0; T1[2] = 0; T1[3] = 0; T1[4] = 0; T1[5] = 0;
				for(i = 0; i <= 5; i++)in_sqr[i]=X2[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)X2[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=Z2[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)Z2[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
				mult(); 
				for(i = 0; i <= 5; i++)T1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X2[i];
				mult(); 
				for(i = 0; i <= 5; i++)Z2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=T1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)T1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=X2[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)X2[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_add[i]=X2[i];
				for(i = 0; i <= 5; i++)in2_add[i]=T1[i];
				add(); 
				for(i = 0; i <= 5; i++)X2[i]=out_add[i];
			
			}else{
				//adding
				for(i = 0; i <= 5; i++)T1[i]=G_x[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X2[i];
				mult(); 
				for(i = 0; i <= 5; i++)X2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
				mult(); 
				for(i = 0; i <= 5; i++)Z2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X2[i];
				mult(); 
				for(i = 0; i <= 5; i++)T2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_add[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_add[i]=X2[i];
				add(); 
				for(i = 0; i <= 5; i++)Z2[i]=out_add[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=Z2[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)Z2[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
				mult(); 
				for(i = 0; i <= 5; i++)X2[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_add[i]=T2[i];
				for(i = 0; i <= 5; i++)in2_add[i]=X2[i];
				add(); 
				for(i = 0; i <= 5; i++)X2[i]=out_add[i];
			
				//doubling
				T1[0] = 1; T1[1] = 0; T1[2] = 0; T1[3] = 0; T1[4] = 0; T1[5] = 0;
				for(i = 0; i <= 5; i++)in_sqr[i]=X1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)X1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=Z1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)Z1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
				mult(); 
				for(i = 0; i <= 5; i++)T1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
				for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
				mult(); 
				for(i = 0; i <= 5; i++)Z1[i]=out_mult[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=T1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)T1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in_sqr[i]=X1[i];
				sqr_rdc(); 
				for(i = 0; i <= 5; i++)X1[i]=out_sqr[i];

				for(i = 0; i <= 5; i++)in1_add[i]=X1[i];
				for(i = 0; i <= 5; i++)in2_add[i]=T1[i];
				add(); 
				for(i = 0; i <= 5; i++)X1[i]=out_add[i];
			}
		}
	
		for(i = 0; i <= 5; i++)T1[i]=G_x[i];
		for(i = 0; i <= 5; i++)T2[i]=G_y[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=Z2[i];
		mult(); 
		for(i = 0; i <= 5; i++)T3[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=Z1[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
		mult(); 
		for(i = 0; i <= 5; i++)Z1[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_add[i]=X1[i];
		for(i = 0; i <= 5; i++)in2_add[i]=Z1[i];
		add(); 
		for(i = 0; i <= 5; i++)Z1[i]=out_add[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
		mult(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
		mult(); 
		for(i = 0; i <= 5; i++)X1[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_add[i]=X2[i];
		for(i = 0; i <= 5; i++)in2_add[i]=Z2[i];
		add(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_add[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=Z2[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=Z1[i];
		mult(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in_sqr[i]=T1[i];
		sqr_rdc(); 
		for(i = 0; i <= 5; i++)T4[i]=out_sqr[i];

		for(i = 0; i <= 5; i++)in1_add[i]=T2[i];
		for(i = 0; i <= 5; i++)in2_add[i]=T4[i];
		add(); 
		for(i = 0; i <= 5; i++)T4[i]=out_add[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=T3[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=T4[i];
		mult(); 
		for(i = 0; i <= 5; i++)T4[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=T3[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=T1[i];
		mult(); 
		for(i = 0; i <= 5; i++)T3[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in_invers[i]=T3[i];
		invers();
		for(i = 0; i <= 5; i++)T3[i]=out_invers[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=T3[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=T4[i];
		mult(); 
		for(i = 0; i <= 5; i++)T4[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=T3[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=X1[i];
		mult(); 
		for(i = 0; i <= 5; i++)X2[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_add[i]=X2[i];
		for(i = 0; i <= 5; i++)in2_add[i]=T1[i];
		add(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_add[i];

		for(i = 0; i <= 5; i++)in1_mult[i]=T4[i];
		for(i = 0; i <= 5; i++)in2_mult[i]=Z2[i];
		mult(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_mult[i];

		for(i = 0; i <= 5; i++)in1_add[i]=Z2[i];
		for(i = 0; i <= 5; i++)in2_add[i]=T2[i];
		add(); 
		for(i = 0; i <= 5; i++)Z2[i]=out_add[i];

		X2[5] = X2[5] & 0x0000000F;
		Z2[5] = Z2[5] & 0x0000000F;

		for(i = 0; i <= 5; i++)X_key[i]=X2[i];
		for(i = 0; i <= 5; i++)Y_key[i]=Z2[i];

		for(i = 0; i <= 5; i++)write32(X_key[i]);	
		for(i = 0; i <= 5; i++)write32(Y_key[i]);	
		
		finish = 1;
		finish = 0;
			
	} while(1);


	#if !defined(AUGH_SYNTHESIS)
	return  0;
	#endif
}
