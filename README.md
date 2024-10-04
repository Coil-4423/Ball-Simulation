# Ball Simulation with Gravity (SFML + CMake)

This project simulates balls moving inside a sphere using **CMake** and **SFML**. The simulation includes a customizable gravity system and real-time rendering of the balls' interactions.

<img src="https://github.com/user-attachments/assets/75764f76-177b-405e-accc-226638d1373b" alt="Screenshot" width="400"/>
<img src="https://github.com/user-attachments/assets/2c4269eb-ddcd-4e07-b81c-663429c2bc9b" alt="Simulation" width="400"/>

## Features
- **Ball Simulation**: Simulates small balls inside a larger sphere, with adjustable ball size and gravity.
- **Gravity System**: Easily toggle gravity on/off during the simulation.
- **Customizable Settings**: Change the size of the balls, gravity strength, and more by adjusting constants in the code.

## How to Use
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/ball-simulation.git
   cd ball-simulation
   ```

2. **Build the Project**:
   Ensure you have CMake and SFML installed.
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Simulation**:
   After building, run the simulation executable:
   ```bash
   ./BallSimulation
   ```

4. **Toggle Gravity**: Press the **`G`** key during the simulation to turn gravity on or off.

## Customization

### Adjust Ball Size
To change the size of the balls in the simulation, modify these constants in `ball.hpp`:
```cpp
const float SMALL_BALL_RADIUS = 2.0f;  // Set size for small balls
const float LARGE_BALL_RADIUS = 2.0f;  // Set size for the large ball
const float SPHERE_RADIUS = 10.0f;     // Set size for the sphere
```

### Modify Gravity Strength
In `gravity.hpp`, you can change the gravity force applied to the balls:
```cpp
velocity.y -= 0.5f;  // Adjust the gravity force here
```

## Dependencies
- **SFML**: Simple and Fast Multimedia Library (for rendering and handling window events)
- **CMake**: Build system for compiling the project

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.

