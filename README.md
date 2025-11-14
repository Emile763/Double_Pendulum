# Global Description
Project from 2024\
Real time simulation of a double pendulum. The equations are approximated using the Runge–Kutta 4 method.


https://github.com/user-attachments/assets/e4951b28-b939-4dc8-b605-e715a6ff9c9d


# How To Compile
At the root of the repository:
```console
mkdir build
cd build
cmake ..
cmake --build .
# To launch
./DoublePendulumApp
```
# How To Use
<kbd>Left Click</kbd>  : Change the first weight angle.\
<kbd>Right Click</kbd> : Change the second weight angle.

# Physics
<img width="592" height="393" alt="image" src="https://github.com/user-attachments/assets/0fbe9f3d-5d43-4131-bf10-af879b50a7c2" />\
**Lagrange's Equations**\
<img width="396" height="260" alt="image" src="https://github.com/user-attachments/assets/a7a1629a-58fb-40eb-b60d-be3cf67acc82" />

**Applied to the double pendulum problem**\
The system's motions are not subject to constraints in the chosen coordinate system.
<img width="506" height="224" alt="image" src="https://github.com/user-attachments/assets/e916152c-92df-42f3-8e00-451254208cf8" />\
Velocity and height:\
<img width="679" height="255" alt="image" src="https://github.com/user-attachments/assets/ffe71b53-40cd-46ed-bada-ea868f7bcd32" />\
Kinetic and potential energy:\
<img width="596" height="120" alt="image" src="https://github.com/user-attachments/assets/18f2cfaf-d8c9-4ebf-9b12-0a9621245e9d" />\
Derivatives:\
<img width="780" height="330" alt="image" src="https://github.com/user-attachments/assets/73534db5-594d-4869-bf47-6cecb73ced03" />\
Which lead to the Lagrange's equations of the pendulum:\
<img width="1727" height="352" alt="image" src="https://github.com/user-attachments/assets/8b74559a-82b7-4551-8350-6aa2f59ee676" />\
The angular accelerations can be expressed as a function of the other parameters:\
<img width="1846" height="280" alt="image" src="https://github.com/user-attachments/assets/24a319e4-6a39-42d8-b552-1da5b58fb62d" />
The expression can be further simplified knowing that:\
<img width="485" height="254" alt="image" src="https://github.com/user-attachments/assets/37014516-208c-4914-a1f4-b72bce74a8e9" />\
Wich leads to:\
<img width="1725" height="185" alt="image" src="https://github.com/user-attachments/assets/8e827876-a225-4da2-ab44-e6edbae02f5f" />

**Runge Kutta 4**\
The equations can be approximated using the Runge–Kutta 4 method.\
<img width="270" height="175" alt="image" src="https://github.com/user-attachments/assets/93c6ffd6-3a63-4c1f-b57e-5a6c2c24f181" />\
<img width="462" height="290" alt="image" src="https://github.com/user-attachments/assets/1bff9b94-6d12-460d-887c-10161f25b771" />


