## Program Domain

### Input Parameters

1. **Integer**: `Mode`  
   Defines the operational mode of the system:
   - `Carnage = 0`
   - `Semaphore = 1`
   - `Traffic = 2`

2. **Integer**: `Bridge Length`  
   Specifies the length of the bridge.

3. **Real**: `Average Car Spawning Time`  
   The mean time interval between car arrivals.

4. **Real**: `Lower Bound Velocity of Cars`  
   The minimum velocity at which cars travel.

5. **Real**: `Upper Bound Velocity of Cars`  
   The maximum velocity at which cars travel.

6. **Real in [0, 1]**: `Probability of Ambulance`  
   The probability of an ambulance appearing.

### Mode-Specific Parameters

**Mode Semaphore:**

- **Real**: `Semaphore_i Duration (Green Time)`  
  The duration of the green light for Semaphore \(i\).

- **Real**: `Semaphore_j Duration (Green Time)`  
  The duration of the green light for Semaphore \(j\).

**Mode Traffic:**

- **Integer**: `K_i`  
  Parameter \(K_i\) specific to Traffic mode.

- **Integer**: `K_j`  
  Parameter \(K_j\) specific to Traffic mode.
