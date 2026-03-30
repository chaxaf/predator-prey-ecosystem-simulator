# Predator-Prey Ecosystem Simulator

## Overview

This project is a C++/SFML ecosystem simulation centered on predator-prey dynamics.

The simulation models the interaction between **scorpions**, **gerbils**, **food sources**, **waves**, and **obstacles** inside a 2D environment. It combines object-oriented design, real-time graphical rendering, configurable simulation parameters, and automated tests.

A second behavior layer extends the basic predator-prey system with **neuronal scorpions** and **wave-emitting gerbils**. In this mode, gerbils emit waves that can be detected by sensor-equipped scorpions, which then estimate prey direction and react according to an internal state machine.

## Main Features

- Real-time 2D ecosystem simulation using SFML
- Predator-prey interactions between scorpions and gerbils
- Food generation and energy-based survival / reproduction mechanics
- Obstacles and collision handling
- Wave propagation model
- Neuronal scorpion behavior with sensor-based target estimation
- Statistics and live population graphs
- JSON-based configuration files
- Unit tests and graphical test targets

## Tech Stack

- **Language:** C++11
- **Graphics / windowing:** SFML
- **Build system:** SCons
- **Testing:** Catch2 (single-header version included in `extlib/`)
- **Configuration:** JSON files in `res/`

## Repository Structure

```text
predator-prey-ecosystem-simulator/
├── src/                       # Core source code
│   ├── Animal/                # Scorpions, gerbils, neuronal variants
│   ├── Environment/           # Environment, food, waves, entities
│   ├── Interface/             # Drawable / Updatable interfaces
│   ├── JSON/                  # JSON parsing / serialization helpers
│   ├── Obstacle/              # Obstacles and colliders
│   ├── Random/                # Random distributions
│   ├── Stats/                 # Population statistics and graphs
│   ├── Tests/                 # Unit and graphical tests
│   ├── Utility/               # Math / helper utilities
│   ├── Application.cpp
│   ├── Application.hpp
│   ├── Config.cpp
│   ├── Config.hpp
│   ├── FinalApplication.cpp   # Main final simulation entry point
│   └── SConscript
├── res/                       # Runtime assets and JSON configs
├── extlib/
│   └── Catch/
│       └── include/
│           └── catch.hpp
├── SConstruct
├── .gitignore
└── README.md
```

## Build and Run

### Requirements

- C++11 compiler (`g++` or `clang++`)
- [SFML](https://www.sfml-dev.org/)
- [SCons](https://scons.org/)

### Build

```bash
scons application
```

### Run

```bash
scons application-run
```

A custom configuration file can also be passed with:

```bash
scons application-run --cfg=res/app.json
```

## Available Targets

The build script defines several useful targets, including:

- `application` — final simulation
- `UnitTests` — unit test suite
- `ChasingTest`
- `Vec2dTest`
- `ColliderTest`
- `TargetInSightTest`
- `EatableTest`
- `MatableTest`
- `EnvTest`
- `PPSTest`
- `ReproductionTest`
- `WaveTest`
- `NeuronalTest`

## Configuration

Simulation parameters are stored in `res/` JSON files, including for example:

- `app.json`
- `app2.json`
- `app3.json`
- `appPPS.json`
- `appTest.json`
- `reprod.json`

These files control parameters such as simulation dimensions, timing, animal properties, and test scenarios.

## What the Code Demonstrates

This project is a strong example of:

- object-oriented C++ design across multiple interacting subsystems
- simulation of agent-based behavior
- state-based behavioral logic
- graphical rendering and event handling with SFML
- configuration-driven execution
- separation between runtime code, tests, and assets

## Notes for a Public GitHub Repo

This repository has been cleaned for presentation purposes:

- removed build artifacts
- removed macOS metadata files
- removed duplicate archives and temporary project files
- kept the source code, assets, configs, and test infrastructure

## Author

- Charlotte Heibig
