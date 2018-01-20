# Software_Engineering-RingBuffer

(1) Implement ring buffer

   : The ring buffer simply stores an integer number.

(2) Simulate the following situations and analyze whether they are problems in terms of real-time system

  * (a) When the average processing speed is faster than the average generation speed of data
  * (b) the average generation rate of data is equal to the average processing speed.
  * (c) When the average processing speed is slower than the average generation speed of data



(3) Considerations when simulating

- Data generator and data processor should be implemented as independent threads.
- The generated data disappears if it is not read until the next data occurs.
- Data generation, data consumption time: Data generation and consumption according to average time T and dispersion sigma
    
    - Gaussian distributions according to sigma


- When simulating, the size of buffer, average time difference according to (a), (b), (c)

- Data generator generates data in the form of 0, 1, 2, 3, 4, 5, 6, ......

- Therefore, the data demolisher can immediately know whether data is missing or not
