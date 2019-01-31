# Answers
1. The CPU utilization should be 100%. There are two processes and each of them will take 100% CPU usage. They are executed in order and there is no time gap between these two processes.
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2     RUN:cpu      READY          1            
  3     RUN:cpu      READY          1            
  4     RUN:cpu      READY          1            
  5     RUN:cpu      READY          1            
  6        DONE    RUN:cpu          1            
  7        DONE    RUN:cpu          1            
  8        DONE    RUN:cpu          1            
  9        DONE    RUN:cpu          1            
 10        DONE    RUN:cpu          1            

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```

2. It will need 10 time stamps to complete both processes.
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2     RUN:cpu      READY          1            
  3     RUN:cpu      READY          1            
  4     RUN:cpu      READY          1            
  5        DONE     RUN:io          1            
  6        DONE    WAITING                     1 
  7        DONE    WAITING                     1 
  8        DONE    WAITING                     1 
  9        DONE    WAITING                     1 
 10*       DONE       DONE                       

Stats: Total Time 10
Stats: CPU Busy 5 (50.00%)
Stats: IO Busy  4 (40.00%)
```

3. It will need only 6 time stamps to complete both processes because CPU in IO waiting time is used for the other process. It will improve the CPU utilization. 
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING    RUN:cpu          1          1 
  3     WAITING    RUN:cpu          1          1 
  4     WAITING    RUN:cpu          1          1 
  5     WAITING    RUN:cpu          1          1 
  6*       DONE       DONE                       

Stats: Total Time 6
Stats: CPU Busy 5 (83.33%)
Stats: IO Busy  4 (66.67%)
```

4. The CPU work process will wait until IO process is done. 
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING      READY                     1 
  3     WAITING      READY                     1 
  4     WAITING      READY                     1 
  5     WAITING      READY                     1 
  6*       DONE    RUN:cpu          1            
  7        DONE    RUN:cpu          1            
  8        DONE    RUN:cpu          1            
  9        DONE    RUN:cpu          1            

Stats: Total Time 9
Stats: CPU Busy 5 (55.56%)
Stats: IO Busy  4 (44.44%) 
```

5. It will get same results as question4. 
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING    RUN:cpu          1          1 
  3     WAITING    RUN:cpu          1          1 
  4     WAITING    RUN:cpu          1          1 
  5     WAITING    RUN:cpu          1          1 
  6*       DONE       DONE                       

Stats: Total Time 6
Stats: CPU Busy 5 (83.33%)
Stats: IO Busy  4 (66.67%)
```
6. Not effective enought. When the first IO request finished, the issued process will not continue to next IO request. It will stay ready until the other three CPU work processes completed. 
```
Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs 
  1      RUN:io      READY      READY      READY          1            
  2     WAITING    RUN:cpu      READY      READY          1          1 
  3     WAITING    RUN:cpu      READY      READY          1          1 
  4     WAITING    RUN:cpu      READY      READY          1          1 
  5     WAITING    RUN:cpu      READY      READY          1          1 
  6*      READY    RUN:cpu      READY      READY          1            
  7       READY       DONE    RUN:cpu      READY          1            
  8       READY       DONE    RUN:cpu      READY          1            
  9       READY       DONE    RUN:cpu      READY          1            
 10       READY       DONE    RUN:cpu      READY          1            
 11       READY       DONE    RUN:cpu      READY          1            
 12       READY       DONE       DONE    RUN:cpu          1            
 13       READY       DONE       DONE    RUN:cpu          1            
 14       READY       DONE       DONE    RUN:cpu          1            
 15       READY       DONE       DONE    RUN:cpu          1            
 16       READY       DONE       DONE    RUN:cpu          1            
 17      RUN:io       DONE       DONE       DONE          1            
 18     WAITING       DONE       DONE       DONE                     1 
 19     WAITING       DONE       DONE       DONE                     1 
 20     WAITING       DONE       DONE       DONE                     1 
 21     WAITING       DONE       DONE       DONE                     1 
 22*     RUN:io       DONE       DONE       DONE          1            
 23     WAITING       DONE       DONE       DONE                     1 
 24     WAITING       DONE       DONE       DONE                     1 
 25     WAITING       DONE       DONE       DONE                     1 
 26     WAITING       DONE       DONE       DONE                     1 
 27*       DONE       DONE       DONE       DONE                       

Stats: Total Time 27
Stats: CPU Busy 18 (66.67%)
Stats: IO Busy  12 (44.44%)
```

7. When the IO request completed, the IO process will immediately take the CPU usage. In this case, it will reduce time cost and improve CPU utilization. 
```
Time     PID: 0     PID: 1     PID: 2     PID: 3        CPU        IOs 
  1      RUN:io      READY      READY      READY          1            
  2     WAITING    RUN:cpu      READY      READY          1          1 
  3     WAITING    RUN:cpu      READY      READY          1          1 
  4     WAITING    RUN:cpu      READY      READY          1          1 
  5     WAITING    RUN:cpu      READY      READY          1          1 
  6*     RUN:io      READY      READY      READY          1            
  7     WAITING    RUN:cpu      READY      READY          1          1 
  8     WAITING       DONE    RUN:cpu      READY          1          1 
  9     WAITING       DONE    RUN:cpu      READY          1          1 
 10     WAITING       DONE    RUN:cpu      READY          1          1 
 11*     RUN:io       DONE      READY      READY          1            
 12     WAITING       DONE    RUN:cpu      READY          1          1 
 13     WAITING       DONE    RUN:cpu      READY          1          1 
 14     WAITING       DONE       DONE    RUN:cpu          1          1 
 15     WAITING       DONE       DONE    RUN:cpu          1          1 
 16*       DONE       DONE       DONE    RUN:cpu          1            
 17        DONE       DONE       DONE    RUN:cpu          1            
 18        DONE       DONE       DONE    RUN:cpu          1            

Stats: Total Time 18
Stats: CPU Busy 18 (100.00%)
Stats: IO Busy  12 (66.67%)
```

8.
Case1 - IO_RUN_IMMEDIATE VS. IO_RUN_LATER:   
Same results between IO_RUN_IMMEDIATE and IO_RUN_LATER because IO request completed after CPU request completed.
IO_RUN_IMMEDIATE
```
Time     PID: 0     PID: 1        CPU        IOs 
1     RUN:cpu      READY          1            
2      RUN:io      READY          1            
3     WAITING    RUN:cpu          1          1 
4     WAITING    RUN:cpu          1          1 
5     WAITING    RUN:cpu          1          1 
6     WAITING       DONE                     1 
7*     RUN:io       DONE          1            
8     WAITING       DONE                     1 
9     WAITING       DONE                     1 
10     WAITING       DONE                     1 
11     WAITING       DONE                     1 
12*       DONE       DONE                       

Stats: Total Time 12
Stats: CPU Busy 6 (50.00%)
Stats: IO Busy  8 (66.67%)
```
IO_RUN_LATER
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING    RUN:cpu          1          1 
  4     WAITING    RUN:cpu          1          1 
  5     WAITING    RUN:cpu          1          1 
  6     WAITING       DONE                     1 
  7*     RUN:io       DONE          1            
  8     WAITING       DONE                     1 
  9     WAITING       DONE                     1 
 10     WAITING       DONE                     1 
 11     WAITING       DONE                     1 
 12*       DONE       DONE                       

Stats: Total Time 12
Stats: CPU Busy 6 (50.00%)
Stats: IO Busy  8 (66.67%)
```
Case1 - SWITCH_ON_IO VS. SWITCH_ON_END:  
When SWITCH_ON_END, the CPU process will run after IO process completed and cause longer time cost. 
SWITCH_ON_IO
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING    RUN:cpu          1          1 
  4     WAITING    RUN:cpu          1          1 
  5     WAITING    RUN:cpu          1          1 
  6     WAITING       DONE                     1 
  7*     RUN:io       DONE          1            
  8     WAITING       DONE                     1 
  9     WAITING       DONE                     1 
 10     WAITING       DONE                     1 
 11     WAITING       DONE                     1 
 12*       DONE       DONE                       

Stats: Total Time 12
Stats: CPU Busy 6 (50.00%)
Stats: IO Busy  8 (66.67%)
```
SWITCH_ON_END
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING      READY                     1 
  4     WAITING      READY                     1 
  5     WAITING      READY                     1 
  6     WAITING      READY                     1 
  7*     RUN:io      READY          1            
  8     WAITING      READY                     1 
  9     WAITING      READY                     1 
 10     WAITING      READY                     1 
 11     WAITING      READY                     1 
 12*       DONE    RUN:cpu          1            
 13        DONE    RUN:cpu          1            
 14        DONE    RUN:cpu          1            

Stats: Total Time 14
Stats: CPU Busy 6 (42.86%)
Stats: IO Busy  8 (57.14%)
```
Case2 - IO_RUN_IMMEDIATE VS. IO_RUN_LATER:   
Same, both processes have IO requests. 
IO_RUN_IMMEDIATE
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING    RUN:cpu          1          1 
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6*     RUN:io    WAITING          1          1 
  7     WAITING    WAITING                     2 
  8*    WAITING     RUN:io          1          1 
  9     WAITING    WAITING                     2 
 10     WAITING    WAITING                     2 
 11*    RUN:cpu    WAITING          1          1 
 12        DONE    WAITING                     1 
 13*       DONE       DONE                       

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  11 (84.62%)
```
IO_RUN_LATER
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING    RUN:cpu          1          1 
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6*     RUN:io    WAITING          1          1 
  7     WAITING    WAITING                     2 
  8*    WAITING     RUN:io          1          1 
  9     WAITING    WAITING                     2 
 10     WAITING    WAITING                     2 
 11*    RUN:cpu    WAITING          1          1 
 12        DONE    WAITING                     1 
 13*       DONE       DONE                       

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  11 (84.62%)
```
Case2 - SWITCH_ON_IO VS. SWITCH_ON_END:
SWITCH_ON_IO
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING    RUN:cpu          1          1 
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6*     RUN:io    WAITING          1          1 
  7     WAITING    WAITING                     2 
  8*    WAITING     RUN:io          1          1 
  9     WAITING    WAITING                     2 
 10     WAITING    WAITING                     2 
 11*    RUN:cpu    WAITING          1          1 
 12        DONE    WAITING                     1 
 13*       DONE       DONE                       

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  11 (84.62%)
```
SWITCH_ON_END
```
Time     PID: 0     PID: 1        CPU        IOs 
  1      RUN:io      READY          1            
  2     WAITING      READY                     1 
  3     WAITING      READY                     1 
  4     WAITING      READY                     1 
  5     WAITING      READY                     1 
  6*     RUN:io      READY          1            
  7     WAITING      READY                     1 
  8     WAITING      READY                     1 
  9     WAITING      READY                     1 
 10     WAITING      READY                     1 
 11*    RUN:cpu      READY          1            
 12        DONE    RUN:cpu          1            
 13        DONE     RUN:io          1            
 14        DONE    WAITING                     1 
 15        DONE    WAITING                     1 
 16        DONE    WAITING                     1 
 17        DONE    WAITING                     1 
 18*       DONE     RUN:io          1            
 19        DONE    WAITING                     1 
 20        DONE    WAITING                     1 
 21        DONE    WAITING                     1 
 22        DONE    WAITING                     1 
 23*       DONE       DONE                       

Stats: Total Time 23
Stats: CPU Busy 6 (26.09%)
Stats: IO Busy  16 (69.57%)
```

Case3 - IO_RUN_IMMEDIATE VS. IO_RUN_LATER:  
IO_RUN_IMMEDIATE 
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6     WAITING    WAITING                     2 
  7*    RUN:cpu    WAITING          1          1 
  8*       DONE     RUN:io          1            
  9        DONE    WAITING                     1 
 10        DONE    WAITING                     1 
 11        DONE    WAITING                     1 
 12        DONE    WAITING                     1 
 13*       DONE    RUN:cpu          1            

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  9 (69.23%)
```
IO_RUN_LATER
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6     WAITING    WAITING                     2 
  7*    RUN:cpu    WAITING          1          1 
  8*       DONE     RUN:io          1            
  9        DONE    WAITING                     1 
 10        DONE    WAITING                     1 
 11        DONE    WAITING                     1 
 12        DONE    WAITING                     1 
 13*       DONE    RUN:cpu          1            

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  9 (69.23%)
```
Case3 - SWITCH_ON_IO VS. SWITCH_ON_END:
SWITCH_ON_IO
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING     RUN:io          1          1 
  4     WAITING    WAITING                     2 
  5     WAITING    WAITING                     2 
  6     WAITING    WAITING                     2 
  7*    RUN:cpu    WAITING          1          1 
  8*       DONE     RUN:io          1            
  9        DONE    WAITING                     1 
 10        DONE    WAITING                     1 
 11        DONE    WAITING                     1 
 12        DONE    WAITING                     1 
 13*       DONE    RUN:cpu          1            

Stats: Total Time 13
Stats: CPU Busy 6 (46.15%)
Stats: IO Busy  9 (69.23%)
```
SWITCH_ON_END
```
Time     PID: 0     PID: 1        CPU        IOs 
  1     RUN:cpu      READY          1            
  2      RUN:io      READY          1            
  3     WAITING      READY                     1 
  4     WAITING      READY                     1 
  5     WAITING      READY                     1 
  6     WAITING      READY                     1 
  7*    RUN:cpu      READY          1            
  8        DONE     RUN:io          1            
  9        DONE    WAITING                     1 
 10        DONE    WAITING                     1 
 11        DONE    WAITING                     1 
 12        DONE    WAITING                     1 
 13*       DONE     RUN:io          1            
 14        DONE    WAITING                     1 
 15        DONE    WAITING                     1 
 16        DONE    WAITING                     1 
 17        DONE    WAITING                     1 
 18*       DONE    RUN:cpu          1            

Stats: Total Time 18
Stats: CPU Busy 6 (33.33%)
Stats: IO Busy  12 (66.67%)
```
