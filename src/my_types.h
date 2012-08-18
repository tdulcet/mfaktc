/*
This file is part of mfaktc.
Copyright (C) 2009, 2010, 2011, 2012  Oliver Weihe (o.weihe@t-online.de)

mfaktc is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

mfaktc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
                                
You should have received a copy of the GNU General Public License
along with mfaktc.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 72bit (3x 24bit) integer
D=d0 + d1*(2^24) + d2*(2^48) */
typedef struct
{
  unsigned int d0,d1,d2;
}int72;

/* 144bit (6x 24bit) integer
D=d0 + d1*(2^24) + d2*(2^48) + ... */
typedef struct
{
  unsigned int d0,d1,d2,d3,d4,d5;
}int144;


/* int72 and int96 are the same but this way the compiler warns
when an int96 is passed to a function designed to handle 72 bit int.
The applies to int144 and int192, too. */

/* 96bit (3x 32bit) integer
D= d0 + d1*(2^32) + d2*(2^64) */
typedef struct
{
  unsigned int d0,d1,d2;
}int96;

/* 192bit (6x 32bit) integer
D=d0 + d1*(2^32) + d2*(2^64) + ... */
typedef struct
{
  unsigned int d0,d1,d2,d3,d4,d5;
}int192;


typedef struct
{
  char progressheader[256];            /* userconfigureable progress header */
  char progressformat[256];            /* userconfigureable progress line */
  int class_number;                    /* the number of the last processed class */
  int grid_count;                      /* number of grids processed in the last processed class */
  unsigned long long int class_time;   /* time (in ms) needed to process the last processed class */
  float cpu_wait;                      /* percentage CPU was waiting for the GPU */
  int output_counter;                  /* count how often the status line was written since last headline */
  int class_counter;                   /* number of finished classes of the current job */
  double ghzdays;                      /* primenet GHZdays for the current assignment (current stage) */
  char kernelname[30];
}stats_t;


typedef struct
{
  cudaStream_t stream[NUM_STREAMS_MAX];
  unsigned int *h_ktab[NUM_STREAMS_MAX+CPU_STREAMS_MAX];
  unsigned int *d_ktab[NUM_STREAMS_MAX];
  unsigned int *h_RES;
  unsigned int *d_RES;
  
  unsigned int exponent;               /* the exponent we're currently working on */
  int bit_min;                         /* where do we start TFing */
  int bit_max_assignment;              /* the upper size of factors we're searching for */
  int bit_max_stage;                   /* as above, but only for the current stage */
  
  int sieve_primes;                    /* the actual number of odd primes using for sieving */
  int sieve_primes_adjust;             /* allow automated adjustment of sieve_primes? */
  int sieve_primes_upper_limit;        /* the upper limit of sieve_primes for the current exponent */
  int sieve_primes_min, sieve_primes_max; /* user configureable sieve_primes min/max */
  
  char workfile[51];                   /* allow filenames up to 50 chars... */
  char resultfile[51];                 /* allow filenames up to 50 chars... */
  int num_streams, cpu_streams;
  
  int compcapa_major;                  /* compute capability major */
  int compcapa_minor;                  /* compute capability minor */
  
  int checkpoints, checkpointdelay, mode, stages, stopafterfactor;
  int threads_per_grid_max, threads_per_grid;

#ifdef CHECKS_MODBASECASE
  unsigned int *d_modbasecase_debug;
  unsigned int *h_modbasecase_debug;
#endif  

  int printmode;
  int allowsleep;
  
  int print_timestamp;
  
  int quit;
  int verbosity;                       /* 0 = reduced number of screen prints, 1 = default, >1 current unused */
  
  int selftestsize;
  
  stats_t stats;                       /* stuff for statistics, etc. */
  
  char V5UserID[51];                   /* primenet V5UserID and ComputerID */
  char ComputerID[51];                 /* currently only used for screen/result output */
  
}mystuff_t;                            /* FIXME: propper name needed */



enum GPUKernels
{
  AUTOSELECT_KERNEL,
  _71BIT_MUL24,
  _75BIT_MUL32,
  _95BIT_MUL32,
  BARRETT76_MUL32,
  BARRETT79_MUL32,
  BARRETT92_MUL32
};

enum MODES
{
  MODE_NORMAL,
  MODE_SELFTEST_SHORT,
  MODE_SELFTEST_FULL
};

#define RET_CUDA_ERROR 1000000001
#define RET_QUIT       1000000002



#define TESLA  100
#define FERMI  200
#define KEPLER 300
