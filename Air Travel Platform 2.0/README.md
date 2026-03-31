# Airline Ticket Reservation Platform / Version 2.0 🎟️

## 📘 README (Português)

Versão 2.0 do AEROFIX introduz arquitetura cliente/servidor:

- `backend/` contém o servidor C++ que processa reservas via HTTP
- `frontend/` contém interface web estática HTML/CSS/JavaScript
- Integrações:
  - `httplib.h` para servidor HTTP
  - `json.hpp` para parse JSON

### Estrutura de pastas

- `Air Travel Platform 2.0/backend/`
  - `Dockerfile` (opcional containerização)
  - `httplib.h` (biblioteca HTTP)
  - `json.hpp` (parser JSON)
  - `main.cpp` (lógica do servidor e endpoints)
- `Air Travel Platform 2.0/frontend/`
  - `index.html` (interface do usuário)
  - `script.js` (fetch para backend e manipulação de UI)
  - `style.css` (estilo visual)

### Como compilar e executar

1. Backend:
   - `cd "Air Travel Platform 2.0/backend"`
   - `g++ -std=c++17 -O2 -o server main.cpp`
   - `./server` (Windows: `server.exe`)
2. Frontend:
   - Abra `Air Travel Platform 2.0/frontend/index.html` no navegador ou execute servidor estático.
3. Teste:
   - Use a UI para selecionar classe/assentos e disparar requisições ao backend.

### Futuras melhorias (PT)
- Persistência em banco de dados (SQLite/PostgreSQL)
- Autenticação de usuário (JWT)
- Rotas múltiplas e gerenciamento de preços
- Validação de input no frontend

---

## 📘 README (English)

AEROFIX version 2.0 introduces a client/server architecture:

- `backend/`: C++ server handling reservations via HTTP
- `frontend/`: static web UI (HTML/CSS/JS)
- Uses `httplib.h` and `json.hpp` for API functionality

### Folder structure

- `Air Travel Platform 2.0/backend/`
  - `Dockerfile` (optional containerization)
  - `httplib.h` and `json.hpp`
  - `main.cpp` (server endpoints)
- `Air Travel Platform 2.0/frontend/`
  - `index.html` (browser UI)
  - `script.js` (fetch calls and DOM updates)
  - `style.css` (styles)

### Build & run

1. In backend folder:
   - `g++ -std=c++17 -O2 -o server main.cpp`
   - `./server` (or `server.exe` on Windows)
2. Open `frontend/index.html` in browser
3. Use the web UI to make class/seat reservation requests directly against backend

### Future improvements (EN)
- DB persistence (SQLite/PostgreSQL)
- User auth (JWT)
- Multi-route and dynamic pricing
- Input validation in frontend