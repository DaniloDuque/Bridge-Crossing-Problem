## Program Domain

### Input Parameters

1. **Integer**: `Mode`  
   Defines the operational mode of the system:
   - `Carnage = 0`
   - `Semaphore = 1`
   - `Traffic = 2`

2. **Integer**: `Bridge Length`  
   Specifies the length of the bridge.

3. **Real**: `Average Left Side Car Spawning Time`  
   The mean time interval between car arrivals on the left side.

4. **Real**: `Average Right Side Car Spawning Time`  
   The mean time interval between car arrivals on the right side.

5. **Real**: `Lower Bound Velocity of Left Side Cars`  
   The minimum velocity at which left-side cars travel.

6. **Real**: `Upper Bound Velocity of Left Side Cars`  
   The maximum velocity at which left-side cars travel.

7. **Real**: `Lower Bound Velocity of Right Side Cars`  
   The minimum velocity at which right-side cars travel.

8. **Real**: `Upper Bound Velocity of Right Side Cars`  
   The maximum velocity at which right-side cars travel.

9. **Real [0, 1]**: `Probability of Left Side Ambulance`  
   The probability of an ambulance appearing on the left side.

10. **Real [0, 1]**: `Probability of Right Side Ambulance`  
    The probability of an ambulance appearing on the right side.

### Mode-Specific Parameters

**Mode Semaphore:**

- **Real**: `Left Semaphore Duration (Green Time)`  
  The duration of the green light for the left semaphore.

- **Real**: `Right Semaphore Duration (Green Time)`  
  The duration of the green light for the right semaphore.

**Mode Traffic:**

- **Integer**: `K_i`  
  Parameter \(K_i\) specific to Traffic mode.

- **Integer**: `K_j`  
  Parameter \(K_j\) specific to Traffic mode.
