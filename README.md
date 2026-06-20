<h1 align="center">Three-Body Problem — Gravitational Simulator</h1>

<p align="center">
  An interactive real-time gravitational simulator built in <strong>C++</strong> and <strong>Qt 6</strong>,
  capable of simulating the motion of N celestial bodies under mutual gravitational attraction.
</p>

> **Group project** (4 people, group L2D2) — *L2 Computer Science, Université Paris Cité*
> Supervised by M. Bouzy Bruno · Academic year 2025–2026

---

## Preview

https://github.com/user-attachments/assets/6cec903e-4456-4554-87c9-44a98eb79678


##  Examples of predefined systems 

#### Figure-Eight (∞)
<img width="731" height="363" alt="image" src="https://github.com/user-attachments/assets/31f2bbb1-bb35-4afd-9a15-c20d8342cde0" />


#### Galaxy (15 bodies)
<img width="731" height="689" alt="image" src="https://github.com/user-attachments/assets/ae0e4d56-6a0c-4370-afe2-273c73263a5d" />


#### Double binary suns
<img width="731" height="731" alt="image" src="https://github.com/user-attachments/assets/171cb3b0-8312-4f82-a342-3d5f513d1f8c" />


#### Solar System

<img width="1158" height="724" alt="image" src="https://github.com/user-attachments/assets/eb4dce30-0189-4bad-8b7a-dc1b6b2eb22a" />

---

## Features

### Real-Time Simulation
- Gravitational N-body simulation based on **Newton's law of universal gravitation**
- Smooth rendering at **~60 FPS** via Qt's `QPainter` and a `QTimer` loop
- Trajectory traces drawn for each body with **color-coded paths**
- **Radial glow effect** around each body for visual clarity

### Interactive Controls
- **Pan** — click and drag to move the camera
- **Zoom** — scroll wheel to zoom in/out
- **Click on a body** — opens a real-time parameter panel *(position, velocity, mass)*
- **Speed slider** — accelerate the simulation without affecting physical accuracy
- **Play / Pause / Restart** buttons

### Predefined Templates *(10 systems)*
| Template | Description |
|---|---|
| Sun / Earth | Stable circular orbit |
| Sun / Earth / Moon | Three-body with satellite |
| Sun / Earth / Mars | Three planets |
| Binary suns | Two stars orbiting each other |
| Binary suns + planet | Small planet in a binary system |
| Triple suns | Chaotic three-star system |
| Figure-Eight (∞) | Famous periodic choreography |
| Double binary suns | Four-star system |
| Galaxy (15 bodies) | Star cluster simulation |
| Solar System | Sun + 8 planets |

### Numerical Integrators *(switchable at runtime)*
| Method | Description |
|---|---|
| **Runge-Kutta 4** *(default)* | Most accurate — 4-step estimation |
| Symplectic Euler | Better energy conservation than explicit |
| Explicit Euler | Fastest but least accurate |

### Custom Experiments
- Create experiments with **any number of bodies**, each with custom mass, position, velocity and color
- **Random generation** for quick experimentation
- Save configurations as **personal templates** *(persisted in JSON across sessions)*
- Modify and re-launch any predefined template without altering the original

### History & Export
- Full **experiment history** with date, duration, total energy, and per-body data
- **Export to PDF** — trajectory charts and data tables
- Re-launch any past experiment from its initial conditions
- Save any experiment as a named personal template

### Display Options
- Toggle **velocity vectors** on/off
- Toggle **reference grid** on/off
- Toggle **body name labels** on/off
- Reset camera to origin

---

## Getting Started (Windows)

> **Requirements:** Windows 10/11 64-bit — no installation needed, just extract and run.

1. Download the release folder 
2. Navigate to `release/`, **scroll to the bottom of the folder** and double-click **`three_body_problem.exe`**

> If Windows shows a security warning (*"Windows protected your PC"*), click **More info** → **Run anyway**.
> This appears because the executable is not digitally signed.

---

## Project Structure

```
three-body-problem-simulator/
│
├── src/                        # C++ source files
│   ├── main.cpp                # Entry point
│   ├── corps.h / corps.cpp     # Body class — physics engine core
│   ├── vect.h / vect.cpp       # 2D vector with operator overloading
│   ├── integrateur.h / .cpp    # Abstract integrator + 3 implementations
│   ├── modele.h / modele.cpp   # Template system + JSON persistence
│   ├── simview.h / simview.cpp # Qt rendering widget (QPainter)
│   ├── startexperience.h / .cpp# Simulation loop (QTimer)
│   ├── mainwindow.h / .cpp     # Main window
│   ├── constants.h / .cpp      # Predefined bodies and templates
│   └── ...                     # Dialogs, history, body panel
│
├── release/                    # Windows executable + required DLLs
│   └── three_body_problem.exe
│
├── .gitignore
└── README.md
```

---

## Architecture

The codebase follows a clear separation between the **physics engine** and the **UI layer**.

```
Physics Engine                    UI Layer
──────────────                    ────────
Vect          ←─ used by ─→      SimView (QPainter rendering)
Corps         ←─ used by ─→      BodyPanel (real-time params)
Integrateur   ←─ used by ─→      MainWindow (integrator selector)
Modele        ←─ used by ─→      TemplateDialog / HistoryDialog
StartExperience (QTimer loop) ←→ MainWindow (play/pause/speed)
```

Key design decisions:
- **Strategy pattern** for integrators — swap the numerical method at runtime with no recompilation
- **Signal/slot architecture** (Qt) for loose coupling between all components
- **Static integrator pointer** shared across all `Corps` instances for consistent physics
- **JSON persistence** via `QJsonDocument` for custom template storage across sessions

---

## Code Overview

| Class | Role |
|---|---|
| `Vect` | 2D vector with `+` and `*` operator overloading |
| `Corps` | Celestial body — holds position, velocity, mass, trace, and computes gravitational acceleration |
| `Integrateur` | Abstract base class for numerical integration |
| `EulerExplicite` | Explicit Euler method |
| `EulerSymplectique` | Symplectic Euler — better energy conservation |
| `RungeKutta4` | 4th-order Runge-Kutta — default and most accurate |
| `Modele` | Named configuration of bodies — predefined or user-created |
| `StartExperience` | Simulation loop — orchestrates physics steps at ~60 FPS |
| `SimView` | Qt rendering widget — draws background, grid, traces, bodies, velocity vectors |
| `MainWindow` | Main window — connects all components via signals and slots |
| `HistoryDialog` | Experiment log with PDF export |
| `BodyPanel` | Real-time body parameter panel, refreshed every 100ms |
| `AddExperienceDialog` | Dynamic form to create custom experiments |
| `TemplateDialog` | Predefined and custom template browser |
| `RandomGenerator` | Random system generator (2–5 bodies) |

---

## What We Learned

This was a **12-week L2 group project** at Université Paris Cité, developed from scratch by a team of 4. It gave us hands-on experience with:

- **Learning C++ and Qt 6 independently** from documentation and online resources
- **Object-oriented design** in a real multi-file project (strategy pattern, signal/slot, separation of concerns)
- **Numerical methods** — implementing and comparing Euler variants and Runge-Kutta 4, and observing their effects on trajectory stability
- **Structured development cycle** — specifications, technical design, weekly meetings with supervisor, SVN version control, full documentation
- **UI/UX design** — building an intuitive interface for a scientifically complex subject

---

---
