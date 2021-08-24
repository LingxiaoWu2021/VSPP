## NAME FORMAT:
- La-Bb-Vc-0d:
  1. a: length of the planning horizon (days);
  2. b: number of berths;
  3. c: number of vessel arrivals;
  4. d: index of the instance in a group of the same a,b, and c (d=1,...,5).

## PARAMETERS:
- Variables:
  1. S:    number of shifts
  2. K:    number of vessel arrivals
  3. T:    number of time steps
  4. B:    number of berths
  5. I:    number of pilotage tasks
  6. NCPN: number of non-simultaneity task pairs
  7. HWPN: number of task pairs with headway restrictions

- Vectors and Matrices:
  1.  BRT[B]:        available times of berths
  2.  Chaocu[B]:     time steps when vessels of Grade IV or V originally occupying the berths sail out of the channel; "-1" represents no such vessel exists at a berth
  3.  HDT[B]:        time steps when vessels originally occupying the berths leave berths plus headways required between any of their followers
  4.  E[I][2]:       time windows for starting pilotage tasks
  5.  BRK[S][2]:     time windows for starting rest periods in the shifts
  6.  VLL[K]:        levels of vessels; Level 0 for vessels of Grades 1; Level 1 for vessels of Grades 2,3; Level 2 for vessels of Grades 4,5
  7.  F[I][I]:       minimum headway between any two pilotage tasks
  8.  D[I+1]:        durations of tasks; D[I] represents the duration of rest periods
  9.  H[K][B]:       handling times of vessels at the berths 
  10. Q[I+1][I+1]:   minimum setup times between activities; "I" represents rest periods
  11. ST[S][2]:      time windows of shifts
  12. C1[K]:         large penalty costs for rejecting a vessel; they are used to create initial columns in the BMP
  13. C2[I][T]:      costs for starting tasks at different time steps
  14. C3[K][B]:      berth handling costs
  15. C4[S]:         costs for assigning a pilot in the shifts
  16. ODS[2][NCPN]:  task pairs with non-simultaneity requirements
  17. Hset[2][HWPN]: task pairs with headway requirements




