# Aerofix - Flight Seat Reservation System ✈️

> **Lightweight Seat Allocation Engine** — C++ REST API backend with vanilla JavaScript frontend for intelligent airplane seat reservation

<div style="display: inline-block; margin-bottom: 15px;">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/HTTPLib-FF6B6B?style=for-the-badge&logo=server&logoColor=white" alt="HTTPLib" />
  <img src="https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="HTML5" />
  <img src="https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white" alt="CSS3" />
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript" />
  <img src="https://img.shields.io/badge/REST_API-FF6C37?style=for-the-badge&logo=rest&logoColor=white" alt="REST API" />
</div>

**Aerofix** is a lightweight flight seat reservation system with intelligent seat allocation algorithms for individual, couple, and family bookings. Built with **C++ backend** (httplib header-only) and **vanilla JavaScript frontend**.

Perfect for demonstrating REST API design, algorithmic thinking, and client-server architecture without framework dependencies.

> 📚 **Documentation:** 🇺🇸 English | [🇧🇷 Português](README.pt-BR.md)

---

## 📋 Table of Contents

- [Aerofix - Flight Seat Reservation System ✈️](#aerofix---flight-seat-reservation-system-️)
  - [📋 Table of Contents](#-table-of-contents)
  - [🎯 Overview](#-overview)
  - [🏗️ Architecture](#️-architecture)
  - [🛠️ Technologies \& Stack](#️-technologies--stack)
  - [📁 Folder Structure](#-folder-structure)
  - [🚀 Setup \& Installation](#-setup--installation)
    - [Prerequisites](#prerequisites)
      - [Windows (MinGW)](#windows-mingw)
      - [Linux](#linux)
      - [macOS](#macos)
  - [🔨 Compilation \& Execution](#-compilation--execution)
    - [Backend](#backend)
    - [Frontend](#frontend)
    - [Test API](#test-api)
  - [📡 REST API Endpoints](#-rest-api-endpoints)
    - [GET /assentos](#get-assentos)
    - [POST /reservar/individual](#post-reservarindividual)
    - [POST /reservar/familia](#post-reservarfamilia)
    - [POST /reservar/casal](#post-reservarcasal)
  - [✨ Features \& Algorithms](#-features--algorithms)
    - [Individual  ✈️](#individual--️)
    - [Family 👨‍👩‍👧‍👦](#family-)
    - [Couple 💑](#couple-)
    - [Recommendation Engine](#recommendation-engine)
  - [🎫 Class Restrictions](#-class-restrictions)
  - [🛫 Booking Workflow](#-booking-workflow)
  - [🤝 How to Contribute](#-how-to-contribute)
  - [🗺️ Roadmap](#️-roadmap)
  - [👨‍💻 Author](#-author)

---

## 🎯 Overview

Aerofix features:

✅ **Smart Seat Allocation** — Dynamic algorithms for individual, couple & family bookings  
✅ **Two Classes** — Economy (restricted seats) & Executive (all seats)  
✅ **Real-time Updates** — In-memory seat management with instant availability  
✅ **Auto-Recommendation** — Smart seat suggestions with simulation mode  
✅ **RESTful API** — Clean endpoints with JSON communication  
✅ **Framework-Free** — Pure C++, vanilla JS & HTML5  
✅ **CORS Enabled** — Full cross-origin support  

---

## 🏗️ Architecture

```
Frontend                      Backend
(Vanilla JS/HTML5)           (C++ + httplib)
     ↓                            ↓
  index.html         →  GET /assentos
  script.js          →  POST /reservar/individual
  style.css          →  POST /reservar/familia
                     →  POST /reservar/casal
                     ↓
              In-Memory Seat Array
              (10 rows × 6 columns)
```

---

## 🛠️ Technologies & Stack

| Component | Tech | Purpose |
|-----------|------|---------|
| Backend | C++17 | Core server |
| Server | httplib.h | HTTP handling |
| Data | nlohmann/json | JSON parsing |
| Frontend | HTML5/CSS3/JS | UI |
| API | REST | Communication |

---

## 📁 Folder Structure

```
Aerofix-backend-project/
├── Air Travel Platform 2.0/        
│   ├── backend/
│   │   ├── main.cpp
│   │   ├── aerofix_api.exe
│   │   ├── httplib.h
│   │   ├── json.hpp
│   │   └── Dockerfile
│   └── frontend/
│       ├── index.html
│       ├── script.js
│       └── style.css
├── Air Travel Platform 1.1/        
├── Air Travel Platform 1.0/        
├── README.md                       (English)
├── README.pt-BR.md                 (Portuguese)
└── License
```

---

## 🚀 Setup & Installation

### Prerequisites
- **C++17 Compiler** (GCC, Clang, MinGW)
- **Code Editor** (VS Code recommended)
- **Browser** (Chrome, Firefox, Safari, Edge)

#### Windows (MinGW)
```bash
# Download: https://www.mingw-w64.org/
g++ --version
```

#### Linux
```bash
sudo apt install build-essential g++
g++ --version
```

#### macOS
```bash
xcode-select --install
```

---

## 🔨 Compilation & Execution

### Backend

```bash
cd "Air Travel Platform 2.0/backend"

# Windows
g++ -std=c++17 -O2 -o aerofix_api.exe main.cpp
./aerofix_api.exe

# Linux/macOS
g++ -std=c++17 -O2 -o aerofix_api main.cpp
./aerofix_api
```

**Output:** `Iniciando servidor Aerofix Backend na porta 8080...`

### Frontend

```bash
cd "Air Travel Platform 2.0/frontend"

# VS Code Live Server (recommended)
# Right-click index.html → Open with Live Server

# Or Python
python -m http.server 8000

# Or Node.js
npx http-server
```

### Test API

```bash
curl http://localhost:8080/assentos
```

---

## 📡 REST API Endpoints

### GET /assentos

Get all seats status

```bash
curl http://localhost:8080/assentos
```

Status: `"O"` = Available, `"X"` = Booked

### POST /reservar/individual

Book individual seat

```bash
curl -X POST http://localhost:8080/reservar/individual \
  -H "Content-Type: application/json" \
  -d '{
    "classe": 1,
    "nome": "João Silva",
    "fileira": 3,
    "coluna": "B",
    "simular": false
  }'
```

**Or with auto-recommendation:**
```json
{
  "classe": 2,
  "nome": "Maria Costa",
  "recomendacao": true,
  "pertoJanela": true,
  "simular": false
}
```

### POST /reservar/familia

Book family (3-5 people)

```bash
curl -X POST http://localhost:8080/reservar/familia \
  -H "Content-Type: application/json" \
  -d '{
    "classe": 1,
    "numPessoas": 4,
    "nomes": ["Ana", "Bruno", "Carlos", "Diana"],
    "simular": false
  }'
```

### POST /reservar/casal

Book couple (2 people)

```bash
curl -X POST http://localhost:8080/reservar/casal \
  -H "Content-Type: application/json" \
  -d '{
    "escolhaProximidade": 2,
    "nomes": ["Luis", "Ana"],
    "simular": false
  }'
```

**Proximity options:**
- `1` = Window seats (opposite sides)
- `2` = Adjacent seats

---

## ✨ Features & Algorithms

### Individual  ✈️
- Manual or auto-recommend
- Window preference (Executive only)
- Real-time validation
- Simulation mode

### Family 👨‍👩‍👧‍👦
- Groups 3-5 people
- Adjacent seating
- Intelligent distribution
- Class constraints

### Couple 💑
- Separated (windows)
- Adjacent (same row)

### Recommendation Engine
- Smart seat finding
- Window priority
- Class validation
- Instant feedback

---

## 🎫 Class Restrictions

| Class | A | B | C | D | E | F |
|-------|---|---|---|---|---|---|
| **Economy** | ❌ | ✅ | ✅ | ✅ | ✅ | ❌ |
| **Executive** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |

---

## 🛫 Booking Workflow

```
Select Type
    ↓
Choose Class
    ↓
View Seats
    ↓
Select Seats
    ↓
Confirm
    ↓
Success
```

---

## 🤝 How to Contribute

1. Fork repository
2. Create branch: `git checkout -b feature/X`
3. Commit: `git commit -m 'Add X'`
4. Push: `git push origin feature/X`
5. Pull Request

---

## 🗺️ Roadmap

- ✅ v2.0 - Web interface
- ⏳ v2.1 - Payment integration
- ⏳ v3.0 - Multiple flights, DB
- ⏳ v4.0 - Mobile app, full features

---

## 👨‍💻 Author

**Nicolas Harnisch** — [@NicolasHarnisch](https://github.com/NicolasHarnisch)

---

**⭐ If helpful, please star this repository!**
