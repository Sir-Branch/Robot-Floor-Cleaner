# Robot-Floor-Cleaner
Realizado Marzo 2016

Input format via command line arguments:

  Simulation Modes(-mode):
  
    - Graphic Simulation(Mode 0):
      The program will show in real time how the floor is cleaned showing clean and dirty tiles, 
      robots and their corresponding movement
      
    - Statistics Simulation(Mode 1): 
      The program will plot the average time of cleaning en function of the amount of robots(n) 
      for the floor size. The program starts for n = 1 (One robot), and will iterate until the 
      difference in average time between n and n+1 is less than 0.1 seconds. For each n(amount of robots) 
      1000 simulations will be carried out and the time will then be averaged.
      
  Floor Size(floor doesn't need to be square):
  
    -Width(-w)  <=70
    -Height(-h) <=100
    
  Number Robots(-n):
  
    Must be <= 1000
  
  Examples of input:
  
  -h 15 -n 10 -w 15 -mode 1 
  
  Will simulate in statistics mode a floor of 15x15 tile up till 10 robots or until 
  time difference < 0.1sec


  -mode 0 -n 2 -h 20 -w 20
  
  Will simulate in graphics mode a floor of 20x20 tiles until the floor is completely clean.
  
